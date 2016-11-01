#ifndef HASH_C
#define HASH_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include "hash.h"
#include "records.h"

void initHashtable(int hsize , int L) {									// initialize L hashtables of <hsize> buckets of 100 length that increase dynamically
    int i , j;
    BucketArray = malloc(L * sizeof (Bucket ));
    for(i=0; i<L; i++){
		BucketArray[i] = malloc(hsize * sizeof (Bucket *));
	}
    for (i = 0; i < L ; i++) {
		for(j=0; j< hsize; j++){
			BucketArray[i][j] = malloc(sizeof (Bucket));
			BucketArray[i][j]->bucketarray = malloc(100 * sizeof (BucketMember));
			BucketArray[i][j]->count = 0;
			BucketArray[i][j]->size = 100;
		}
    }
    global_bucket_key = malloc( L * sizeof(BucketMember));
    for(i=0; i<L; i++){
		global_bucket_key[i] = malloc(sizeof(BucketMember));
		global_bucket_key[i]->key = 0;
	}
	
}

    
void freememory(int L) {
    int i , j;
    for(j=0; j<L; j++){
		for (i = 0; i < Infos.startbucketsize; i++) {
			free(BucketArray[j][i]->bucketarray);
		}
		for (i = 0; i < Infos.startbucketsize; i++) {
			free(BucketArray[j][i]);
		}
		free(BucketArray[j]);
	}
}

int find_bucket_cosine(int id , cos_items_ptr items_ptr , Ri_ptr rptr , int K , int table){						// find to which bucket ''belongs'' the given vector
	int i,j , table_slot , power;
	double sum;
	table_slot = 0;
	for(i=0 ; i<K; i++){
		sum = 0;
		for(j=0 ; j< items_ptr->total_dimensions; j++){
			sum = sum + (items_ptr->item_array[id][j] * rptr[table]->values[j][i]) ;
		}
		if(sum>=0) {
			power = pow(2 , K-(i+1) );
			table_slot += power;
		}
	}
	return table_slot;
}

int find_query_bucket_cosine(int id , query_items_ptr qptr  , Ri_ptr rptr , int K , int table , int dimensions){		 // find to which bucket ''belongs'' the given vector , applied to queries
	int i,j , table_slot , power;
	double sum;
	table_slot = 0;
	for(i=0 ; i<K; i++){
		sum = 0;
		for(j=0 ; j< dimensions; j++){
			sum = sum + (qptr[id].q_vectors[j] * rptr[table]->values[j][i]) ;
		}
		if(sum>=0) {
			power = pow(2 , K-(i+1) );
			table_slot += power;
		}
	}
	return table_slot;
}

void find_distance_cosine( query_items_ptr qptr , int item , int table , int table_slot , int total_dim){					// find the distance between vectors with the  cosine metric
	double distance , sum , a , b , min;
	int i,j , item_id= -1;
	for(j=0; j<BucketArray[table][table_slot]->count; j++){
	//	if( BucketArray[table][table_slot]->bucketarray[j].v_ptr != NULL) {
			a=0;
			b=0;
			sum=0;
			for(i=0; i<total_dim; i++){																									// cosine distance computation
				sum += qptr[item].q_vectors[i] + BucketArray[table][table_slot]->bucketarray[j].v_ptr->vector_coords[i] ;
				a += pow( qptr[item].q_vectors[i] , 2);
				b += pow(BucketArray[table][table_slot]->bucketarray[j].v_ptr->vector_coords[i] , 2);
			}
			a = sqrt(a);
			b = sqrt(b);
			distance = sum/(a+b);
			if(j==0) min = distance ; 		
			if(distance<= min) {
				min = distance;
				item_id = BucketArray[table][table_slot]->bucketarray[j].key;
				}
	
	
		//}
	}
	dptr[item].q_distance[table] = min;
	dptr[item].q_dist_id[table] = item_id;
//	printf("minimal cosine distance between query item %d and vector %d : %f \n" , item , dptr[item].q_dist_id[table] , dptr[item].q_distance[table]);
	
}

int mod (long a, long b)
{
   int ret = a % b;
   if(ret < 0)
     ret+=b;
   return ret;
}

int find_bucket_euclidean(int id , cos_items_ptr items_ptr , Ri_ptr rptr , int K , int table , random_t_ptr tptr , random_rptr randomr , int hsize){
	int  table_slot   , w=4  , i , j;
	double sum;
	double function_h , function_f;
	long M_v = pow( 2 , 32);
	M_v = M_v - 5;
	table_slot = 0;
	function_f = 0;
	for(i=0 ; i<K; i++){
		sum = 0;
		for(j=0 ; j< items_ptr->total_dimensions; j++){
			sum = sum + (items_ptr->item_array[id][j] * rptr[table]->values[j][i]) ;
		}
		function_h = sum;
		function_h = (function_h + tptr[table].t[i])/w ;
		function_f += function_h * randomr[table].r_euc[i] ; 
//		printf("%f %f %ld B\n" , function_f  , function_h , randomr[table].r_euc[i]);
	}
	function_f = mod( function_f , M_v);
	function_f = mod( function_f , hsize);
	table_slot = function_f;
//	printf("tableslot in find buck %d\n" , table_slot);
	
//	sleep(3);
	return table_slot;

}

int find_query_buckets_euclidean(int id , query_items_ptr qptr , random_t_ptr tptr , random_rptr randomr , Ri_ptr rptr , int table , int total_dim  , int K  ,  int hsize){
	double sum ;
	int  table_slot   , w=4   , j , z;
	double function_h , function_f;
	long M_v = pow( 2 , 32);
	M_v = M_v - 5;	
	table_slot = 0;
	function_f = 0;
	for(j=0; j<K; j++){
		sum = 0;
		for(z=0; z<total_dim; z++){
			sum = sum + (qptr[id].q_vectors[z] * rptr[table]->values[z][j]) ;
		}
		function_h = sum;
		function_h = (function_h + tptr[table].t[id])/w ;
		function_f += function_h * randomr[table].r_euc[id] ; 
	}
	function_f = mod( function_f , M_v);
	function_f = mod( function_f , hsize);
	table_slot = function_f;
//			printf("query element :%d should go to search in bucket %d \n" , i , table_slot);
	return table_slot;
} 
	
	
void find_distance_euclidean( int id , query_items_ptr qptr , int item , int table , int table_slot , int total_dim ){
	double distance=0 , min = 1;
	int i , j , got_in=0  , in= 0; //, item_id
	for(j=0; j<BucketArray[table][table_slot]->count; j++){
		//if( BucketArray[table][table_slot]->bucketarray[j].v_ptr != NULL) {
			distance = 0;
			got_in=1;
			for(i=0; i<total_dim; i++){
				if( BucketArray[table][table_slot]->bucketarray[j].key == 432  && i==0) {
		//			printf("found the item :%d  query : %d \n" , BucketArray[table][table_slot]->bucketarray[j].key , item);
					in=1;
//					sleep(3);
				}
				distance += pow( (qptr[id].q_vectors[i] - BucketArray[table][table_slot]->bucketarray[j].v_ptr->vector_coords[i]) , 2);
			}
			distance = sqrt( distance );
			if(in){
//				printf("distance for the item :%f\n" , distance);
//				sleep(3);
			}
			if(j==0) min = distance ; 
			if(distance<=min){
				min = distance;
//				printf("new minimal distance %f between query vector %d and item with id %d \n" , distance , item  , BucketArray[table][table_slot]->bucketarray[j].key);
//				item_id = BucketArray[table][table_slot]->bucketarray[j].key;
				dptr[item].q_distance[table] = min;
				dptr[item].q_dist_id[table] = BucketArray[table][table_slot]->bucketarray[j].key;
			}
		//}else break;
	}
//	printf("item_idS%d 	item%d      %f \n" ,query_id , item_id ,  min);

//	sleep(1);
	if(!got_in) printf(" dist 0  , no bucket elements \n");
//	sleep(7);
	}
	


int searchHashtable_cosine(int id ,cos_items_ptr items_ptr , Ri_ptr rptr , int K , int table ) {
	int j , tableslot  , slot;
	tableslot = find_bucket_cosine(id , items_ptr , rptr , K , table);
    for (j = 0; j < BucketArray[table][tableslot]->size; j++) {
        if (BucketArray[table][tableslot]->bucketarray[j].key == id) {
			printf("key : %d \n" , BucketArray[table][tableslot]->bucketarray[j].key );
            printf("found item with id%d at bucket %d  , at table : %d , j:%d\n" , id , tableslot , table+1 , j);
            slot = j;
            break;
        }
    }
    
    for(j=0; j< items_ptr->total_dimensions; j++){;
		printf("%f " ,  BucketArray[table][tableslot]->bucketarray[slot].v_ptr->vector_coords[j]);
		
		}
	return slot; 
 
  
}
int searchHashtable_euclidean(int id ,cos_items_ptr items_ptr , Ri_ptr rptr , int K , int table , random_t_ptr tptr , random_rptr randomr  , int hsize){
	int j , tableslot , slot  ;
	tableslot = find_bucket_euclidean(id , items_ptr , rptr , K , table , tptr , randomr , hsize);
	 for (j = 0; j < BucketArray[table][tableslot]->size; j++) {
        if (BucketArray[table][tableslot]->bucketarray[j].key == id) {
			printf("mega size : %d \n" ,  BucketArray[table][tableslot]->size);
			printf("key : %d \n" , BucketArray[table][tableslot]->bucketarray[j].key );
            printf("found item with id%d at bucket %d  , at table : %d , j:%d\n" , id , tableslot , table+1 , j);
            slot = j;
            break;
        }
    }
    
    for(j=0; j< items_ptr->total_dimensions; j++){;
		printf("%f " ,  BucketArray[table][tableslot]->bucketarray[slot].v_ptr->vector_coords[j]);
		
		}
	return slot; 
	
	
	
	}


void bucketentry( vector_ptr vptr , int position , int z,  int table ) {				// prepare vector to be put in the hashtable
    BucketMember temps;
    temps.v_ptr = malloc(sizeof(struct vectors));
    temps.v_ptr->vector_coords = malloc(sizeof(double) * 100);
    temps.v_ptr->vector_coords = vptr[z].vector_coords ;
    temps.key = global_bucket_key[table]->key;
    global_bucket_key[table]->key ++;
//    printf("%d->%d " , temps.key , position );
    putinbucket(temps, position , table);
}


void putinbucket(BucketMember temp, int position , int table) {											// put vector in the hashtable
    if (BucketArray[table][position]->count == BucketArray[table][position]->size) {
        BucketArray[table][position]->size *= 2;
        BucketArray[table][position]->bucketarray = realloc(BucketArray[table][position]->bucketarray, BucketArray[table][position]->size * sizeof (BucketMember));
        BucketArray[table][position]->bucketarray[BucketArray[table][position]->count++] = temp;
    } else {
        BucketArray[table][position]->bucketarray[BucketArray[table][position]->count++] = temp;
        Infos.countentries++;
    }
}

void real_distance(query_items_ptr  qptr , cos_items_ptr items_ptr , FILE *fp , int metric_space){		// exantlhtikh 
	int i,j,z , min_id;
	double a , b , sum , distance , min;
	fprintf(fp , "%s" , "\n");
	fprintf(fp , "%s" , "\n");
	fprintf(fp , "%s" , "real min_distance:");
	fprintf(fp , "%s" , "\n");
	if(metric_space){
		for(j=0; j<qptr[0].q_elements - 1; j++){
			for(i=0; i<items_ptr->current_items; i++){
				distance = 0;
				for(z=0; z<items_ptr->total_dimensions; z++){
					distance += pow( (qptr[j].q_vectors[z] - items_ptr->item_array[i][z]) , 2);
				}
				distance = sqrt( distance );
				if(i==0) min = distance;
				if(distance<min) {
					min = distance;	
					min_id = i;
				}
			}
			fprintf(fp , "%s %d %s %d %s %f" , "query" , j , "vector" , min_id , "distance:" , min);
			fprintf(fp , "%s" , "\n");
		}
	}else if(!metric_space){
		for(j=0; j<qptr[0].q_elements - 1; j++){
			for(i=0; i<items_ptr->current_items; i++){
				sum = 0;
				a=0;
				b=0;
				for(z=0; z<items_ptr->total_dimensions; z++){
					sum += qptr[j].q_vectors[i] + items_ptr->item_array[i][z] ;
					a += pow( qptr[j].q_vectors[i] , 2);
					b += pow(items_ptr->item_array[i][z] , 2);
				}
				a = sqrt(a);
				b = sqrt(b);
				distance = sum/(a+b);
				if(i==0) min = distance;
				if(distance<min) {
					min = distance;	
					min_id = i;
				}
					
			}
			fprintf(fp , "%s %d %s %d %s %f" , "query" , j , "vector" , min_id , "distance:" , min);
			fprintf(fp , "%s" , "\n");
		}
	}
	
	
	
	}

#endif 

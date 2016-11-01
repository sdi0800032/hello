#ifndef CSTRUCT_C
#define CSTRUCT_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include "hash.h"
#include "records.h"

#define M -1
#define N 1

cos_items_ptr allocate_space_items( int num ){
	cos_items_ptr ptr;
	int elements , i;
	if(num>0) elements = num;
	else{
		printf("invalid number of items \n");
		return NULL;
	}
	ptr = malloc(sizeof (struct COS_items));
	ptr->item_array = malloc(sizeof(double) * elements );
	for(i=0; i<elements; i++){
		ptr->item_array[i] = malloc(sizeof(double) * 256 );		
	}
	ptr->current_items = 0;
	ptr->current_dimension = 0;
	return ptr;
}

Ri_ptr allocate_space_Ri(int K , int dimensions , int L){
	int i , j;
	Ri_ptr rptr;
	rptr = malloc( L * sizeof(struct R_i));
	for(i=0; i<L; i++){
		rptr[i] = malloc(sizeof(struct R_i));
	}
	for(i=0; i< L; i++){
		rptr[i]->values = malloc(sizeof(double)*dimensions);
		for(j=0; j<dimensions; j++){
			rptr[i]->values[j] = malloc(sizeof(double)*K);
		}
		rptr[i]->current_Rdimension=0;
		rptr[i]->current_Kposition = 0;
	}
	return rptr;
}



query_items_ptr allocate_space_query( char *filename , int dimensions  , int L){			// allocate space for the items in the query file
	query_items_ptr qptr ;
	int i  , radius = 0  ; //, j;
	FILE *fp;
	char *token;
	char * line = NULL;
	size_t len = 0;
    ssize_t read;
    double item_coords;
    int elements=0 , current_items = 0 , current_dimension=0;
	fp = fopen( filename , "r");
	if( fp == NULL) 		return NULL;
	while ((read = getline(&line, &len, fp)) != -1) {
		elements++;
	}
	fclose(fp);
	printf("found %d query vectors \n" , elements-1);
	qptr = malloc( sizeof(struct query_vectors ) * elements );
	dptr = malloc(sizeof(struct query_distance) * elements ) ;
	for(i=0; i<elements; i++){																// allocate space to store all the minimum_distances between the query objects and the vectors in the L different hashtables
		dptr[i].q_distance = malloc( sizeof(double) * L);
		dptr[i].q_dist_id = malloc(sizeof(int) * L);
		dptr[i].q_current_items = 0;
	}
	for(i=0; i < elements ; i++){
		qptr[i].q_elements = elements ;
		qptr[i].q_vectors = malloc(sizeof(double) * dimensions );
	}
	fp = fopen(filename, "r");
	read = getline(&line, &len, fp);						//first line contains the radius
	token = strtok(line, ":");	
	token = strtok(NULL, "	");
	radius = atoi(token);
	 while ((read = getline(&line, &len, fp)) != -1) {
        token = strtok(line, "	");					
        while( token != NULL ) {
			token = strtok(NULL, "	");
			if(token!=NULL){
				item_coords = atof( token );			
				qptr[current_items].q_vectors[current_dimension] = item_coords;
				current_dimension ++;
			}
		}
		qptr[current_items].q_radius = radius;
		current_items ++ ;
		current_dimension = 0;
	}
/*	printf("given radius is %d\n" , radius);
	sleep(3);
	for(i=0; i<elements-1 ; i++ ) {
		for(j=0; j<dimensions; j++){
			printf("%f " , qptr[i].q_vectors[j]);
		}
	} */
	return qptr;
}	

void store_item_coords( double num , cos_items_ptr ptr ){
	ptr->item_array[ptr->current_items][ptr->current_dimension] = num;
	ptr->current_dimension ++ ;
}


void store_Ri_coords( double num , Ri_ptr rptr , int table){
	rptr[table]->values[rptr[table]->current_Rdimension][rptr[table]->current_Kposition] = num;
	rptr[table]->current_Rdimension ++ ;
	
	}


void build_Ri( int dimensions , int K , Ri_ptr rptr , cos_items_ptr items_ptr , int elements , int L , vector_ptr vptr , int hsize , int metricspace , double R , random_t_ptr tptr , random_rptr randomr ){
	double random_value_1 , random_value_2;
	double r , log_value ;
	double x_1 , val , sqrt_val;														
	int i , j , t;
	initHashtable( hsize , L);
	srand(time(NULL));
	for(t=0 ; t<L; t++){														// do the operations L times ( for the L hashtables )
		for( j=0 ; j<K ; j++){													// we need K hi
			for( i =0; i<dimensions ; i++ ){									// create Ri in N(0,1)^d (in X dimensions)
				while(1){
					random_value_1 = M + (rand()/(RAND_MAX + 1.0 )) *(N-M);			// -1 to 1
					random_value_2 =  M + (rand()/(RAND_MAX + 1.0))*(N-M);	
					r = pow( random_value_1 , 2) + pow(random_value_2 , 2) ;
					if( r < 1 ) break ; 										// acceptable pair
				}
				log_value = log(r);
				val = (-2)*log_value/r; 
				sqrt_val = sqrt(val);
				x_1 = sqrt_val * random_value_1;
				store_Ri_coords( x_1 , rptr , t);
			}
			rptr[t]->current_Kposition ++;
			rptr[t]->current_Rdimension = 0;
			
		}
		rptr[t]->current_Kposition = 0 ;
		rptr[t]->current_Rdimension = 0;
		if(!metricspace) build_Hi_cosine( items_ptr , rptr , elements , K  , L , vptr , t);
		else if(metricspace) build_Hi_euclidean(items_ptr , rptr , elements , K  , L , vptr , t , R , hsize , tptr , randomr , hsize);
	}
	
}
	
	
void build_Hi_cosine( cos_items_ptr items_ptr , Ri_ptr rptr , int total_items , int K , int L , vector_ptr vptr , int table){
	int z , i , j , table_slot , power;
	double sum ;
	for(z=0; z<total_items; z++){
		table_slot = 0;
		for(i=0; i<K; i++){
			sum = 0.0;
			for(j=0; j< items_ptr->total_dimensions; j++){
				sum = sum + (items_ptr->item_array[z][j] * rptr[table]->values[j][i]) ;
				if(i==(K-1)) vptr[z].vector_coords[j] = items_ptr->item_array[z][j] ;		// store the vector just once ( in one loop only)
				
			}
			if(sum>=0) {
				power = pow(2 , K-(i+1) );
				table_slot += power;
			}
		// insert in hash_Table item:z in slot: table_slot			
		}
		bucketentry( vptr , table_slot , z , table );
//		printf("testing table_slot for item %d: %d\n" , z , table_slot);	
	}
}
    
double create_t(int w){
	double random_value_1;
	int A = 0 , B = w;
	random_value_1 = A + (rand()/(RAND_MAX + 1.0 )) *(B-A);	
	return random_value_1;
	
	}
	

void build_Hi_euclidean( cos_items_ptr items_ptr , Ri_ptr rptr , int total_items , int K , int L , vector_ptr vptr , int table , double R , int tablesize , random_t_ptr tptr , random_rptr randomr , int hsize ){
	double t;
	int w = 4 , z , i , j   , table_slot;
	double sum;
	double h[K] , function_f;
	long r[K];
	long M_v = pow( 2 , 32);
	M_v -= 5;
	for(i=0; i<K; i++){
		r[i] = rand();
		randomr[table].r_euc[i] = r[i];
	}
	
	// change_w(R) 				: change w depending on R , not yet implemented
	for(z=0; z<total_items; z++){
		function_f = 0;
		sum = 0;
		for(i=0; i<K; i++){
			if(z==0){
				t = create_t(w);
				tptr[table].t[i] = t;
			}
			sum = 0.0;
			for(j=0; j< items_ptr->total_dimensions; j++){
				sum = sum + (items_ptr->item_array[z][j] * rptr[table]->values[j][i]) ;
				if(i==(K-1)) vptr[z].vector_coords[j] = items_ptr->item_array[z][j] ;		// store the vector just once ( in one loop only) | created vptr to assign directly to bucket elements
				
			}
			sum = (sum + tptr[table].t[i])/w;
			h[i] = sum;
			function_f +=  h[i] * randomr[table].r_euc[i];
//			if(z==0 && table==0) printf("%f %f %ld A\n" ,function_f , h[i] ,randomr[table].r_euc[i] );
		}
		function_f = mod( function_f , M_v);
		function_f = mod( function_f , hsize);
		table_slot = function_f;
		bucketentry( vptr , table_slot , z , table);
	}
	
	
	}
    
    
    
#endif    

#ifndef COSINE_EUCL_C
#define COSINE_EUCL_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "hash.h"
#include "records.h"
#include <math.h>



void cosine_eucl(char *path , char *query_file , char *output_file , int K , int L ){
	int hsize, i , table ;
	double R = 10  ;
	int metric_space , j;
	char *buffer;
	double item_coords;
	Ri_ptr ri_coords;
	cos_items_ptr items_ptr;
	vector_ptr vptr;
	random_rptr randomr;
	query_items_ptr qptr;
	int elements=-2 ;				// starting at -2 to ignore the 2 titles in the euclidean files
	char * line = NULL;
    size_t len = 0;
    ssize_t read;
	char *token;
    printf("%s %s %d %d\n",path , query_file , L , K);
    hsize = pow( 2 , K);
    FILE* fp ;
    fp = fopen(path, "r");
    if( fp == NULL) {
		printf("error opening file , exiting ... \n");
	}
	while ((read = getline(&line, &len, fp)) != -1) {		// searched how many items are in file to dynamically allocate array of ''element'' size
		elements++;
	}
	printf("Items in file :%d\n",elements);					
	items_ptr = allocate_space_items( elements ) ;
	printf("allocating space for %d elements..\n" , elements);
	fclose(fp);
	fp = fopen(path, "r");
    if( fp == NULL) {
		printf("error opening file , exiting ... \n");
	}
	read = getline(&line, &len, fp);
	read = getline(&line, &len, fp);						// skip 2 lines (titles)
	 while ((read = getline(&line, &len, fp)) != -1) {
//       printf("%s", line);
        token = strtok(line, "	");					
//        printf( "%s\n", token );
        while( token != NULL ) {
//			printf( "%s\n", token );
			token = strtok(NULL, "	");
			if(token!=NULL){
				item_coords = atof( token );				
				store_item_coords( item_coords , items_ptr );			// save item coords in our structure
				}
		}
		items_ptr->current_items ++; 
		items_ptr->total_dimensions = items_ptr->current_dimension; 
		items_ptr->current_dimension = 0;
    }
    ri_coords = allocate_space_Ri( K , items_ptr->total_dimensions , L);
    vptr = malloc(sizeof(struct vectors) * elements);
    for(i=0; i< elements; i++){
		vptr[i].vector_coords = malloc( sizeof(double) * items_ptr->total_dimensions);
	}
	printf("pick metric space : cosine or euclidean ? \n" );
	buffer = malloc(sizeof(char)*15);
	scanf("%s" , buffer);
	while(1){
		if(!strcmp( buffer , "cosine")){
			metric_space = 0;								// identifier for cosine
			break;
		}
		else if( !strcmp( buffer , "euclidean")){
			metric_space = 1;								// identifier for euclidean
			break;
			}
		else {
			printf("please enter either ' cosine ' or ' euclidean ' \n");
			scanf("%s" , buffer);		
		}	
	} 
	if(metric_space) {
		tptr = malloc(sizeof(struct random_T) * L );
		for( i = 0 ; i<L ; i++){
			tptr[i].t = malloc( sizeof(double) * K) ;
		}
		randomr = malloc(sizeof(struct random_r) * L );
		for( i = 0 ; i<L ; i++){
			randomr[i].r_euc = malloc( sizeof(long) * K) ;
		}
		
	}
	fclose(fp);
	hash_ptr = malloc( sizeof( struct hashing_functions ) * L );
	for(i=0; i<L; i++){
		hash_ptr[i].hash_h = malloc( sizeof(double) * K );
	}
	build_Ri( items_ptr->total_dimensions  , K , ri_coords , items_ptr , elements , L , vptr , hsize , metric_space , R , tptr , randomr );
	qptr = allocate_space_query( query_file , items_ptr->total_dimensions , L);
	if(qptr == NULL){
		printf("error proccessing query file , exiting \n");
		}
	int id , slot;
	double min ;
	int min_id;
	if(!metric_space) {
		for(table=0; table<L ; table++){
	//		find_query_buckets_euclidean( qptr , tptr , randomr , ri_coords , table , items_ptr->total_dimensions , K , qptr[0].q_elements ,  hsize );	
			for(id=0; id<qptr[0].q_elements-1 ; id++){
				slot = find_query_bucket_cosine( id ,  qptr  , ri_coords ,  K ,  table , items_ptr->total_dimensions);
				find_distance_cosine(  qptr , id ,  table ,  slot , items_ptr->total_dimensions);
			}
		}
	}else if(metric_space){
		for(table=0; table<L ; table++){
			for(id=0; id<qptr[0].q_elements-1 ; id++){
				slot = find_query_buckets_euclidean(id ,  qptr ,tptr , randomr , ri_coords ,table , items_ptr->total_dimensions ,K ,hsize);
				find_distance_euclidean( id , qptr , id ,  table , slot , items_ptr->total_dimensions);
			}
		
		}
	}
	fp = fopen( output_file , "w+");
	for(j=0; j<qptr[0].q_elements - 1; j++){
		for(i=0; i<L; i++){
			if(i==0) min = dptr[j].q_distance[i];
			if(dptr[j].q_distance[i]<= min ) {
				min = dptr[j].q_distance[i];	
				min_id = dptr[j].q_dist_id[i];		
			}
		}
		fprintf( fp , "%s %d %s %d %s %f" , "query" , j , "vector" , min_id , "distance:" , min);
		fprintf(fp , "%s" , "\n");
//		printf("query%d vector%d	%f \n" , j , min_id , min);
		
	}
	real_distance( qptr , items_ptr , fp , metric_space);
	
		
	fclose(fp);
}

#endif

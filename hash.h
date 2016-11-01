#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
//#include <math.h>
#include <string.h>
#include "records.h"


//Vectors

query_items_ptr allocate_space_query( char * , int , int);
cos_items_ptr allocate_space_items( int ) ;
Ri_ptr allocate_space_Ri(int , int , int);
void store_item_coords( double  , cos_items_ptr) ;
void build_Ri( int , int , Ri_ptr , cos_items_ptr , int , int  , vector_ptr , int , int , double , random_t_ptr , random_rptr ) ;
void store_Ri_coords( double , Ri_ptr , int );
void build_Hi_cosine( cos_items_ptr , Ri_ptr , int , int  , int , vector_ptr , int);
void build_Hi_euclidean( cos_items_ptr , Ri_ptr , int , int  , int , vector_ptr , int , double , int , random_t_ptr , random_rptr  , int);
double create_t(int);




// HASHTABLE
void initHashtable(int , int );
int find_bucket_cosine(int  , cos_items_ptr  , Ri_ptr  , int  , int);
int find_bucket_euclidean(int  , cos_items_ptr  , Ri_ptr  , int  , int , random_t_ptr , random_rptr , int);
int searchHashtable_cosine(int ,cos_items_ptr  , Ri_ptr  , int ,int);
int searchHashtable_euclidean(int ,cos_items_ptr  , Ri_ptr  , int ,int , random_t_ptr , random_rptr , int);
void bucketentry( vector_ptr , int , int , int );
void bucketentry1( number_ptr nptr , int  , int); 
void bucketentry2( matrix_ptr mptr , int  , int , int);
void putinbucket(BucketMember, int , int);
void freememory();
int mod (long a, long b);





//query
void queryfile_parsing( FILE *) ;
int find_query_buckets_euclidean(int , query_items_ptr  , random_t_ptr  , random_rptr  , Ri_ptr  , int , int   , int , int);
void find_distance_euclidean( int , query_items_ptr , int , int  ,int , int);
int find_query_bucket_cosine(int , query_items_ptr   , Ri_ptr  , int  , int , int);
void find_distance_cosine( query_items_ptr  , int  , int  , int  , int );
void real_distance( query_items_ptr , cos_items_ptr , FILE* , int);


//matrix
void matrix(char* ,int ,int ,char *,char *);
int find_median(int ,int ,int **,int );
int Pow(int);
int metric_hash(int **,int **,int ,int ,int ,int ,int );
int metric_hash2(int *,int **,int **,int ,int ,int ,int );
void metric_Search(char *,int ,int ,int **,int ,int **,char *);


///hamming
void hamming(char *,int ,int ,char *,char *);
int hamming_hash(int ,int ,char number[64],int **,int );
void hamming_Search(char *,int ,int ,int **,int ,int ,char **,char *);
int find_distance(char *,char *,int ,int );
int find_normal_distance(char **,char *,int ,int );

//cosine euclidean

void cosine_eucl(char * , char * , char * , int  , int  );

#endif

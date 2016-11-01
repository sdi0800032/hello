#ifndef RECORDS_H
#define RECORDS_H

struct vectors {
  double *vector_coords;
};

typedef struct vectors *vector_ptr;


struct COS_items {
	double **item_array;
	int current_items;
	int current_dimension;
	int total_dimensions;
};

struct R_i {
	double **values;
	int current_Rdimension;
	int current_Kposition;
	};

struct random_T{
	double *t;	
};

struct random_r{
	long *r_euc;	
};

struct hashing_functions{
	long *hash_h;	
};

struct query_vectors{
	double *q_vectors;
	int q_elements;
	int q_radius;
};

struct query_distance{
	double *q_distance;
	int *q_dist_id;
	int q_current_items;
};



/////////domi me ta stoixeia pou hashing gia metric spaces

struct matrix{
  int *matrix_distances;	////pinakas me oles tis apostaseis
	char *id;		///// onoma tou entry
	int position;	///// seira me tin opoia mpike sto hashtable
};

typedef struct matrix *matrix_ptr;

/////////domi me ta stoixeia pou hashing gia hamming spaces

struct number{
	char *id;	////onoma tous entry
	char *name;	////o duadikos arithmos tou entry
	int position; ///// seira me tin opoia mpike sto hashtable
};

typedef struct number *number_ptr;

typedef struct COS_items *cos_items_ptr;	// array of vectors
typedef struct R_i **Ri_ptr;				// L arrays of D r_i's ( L:sizeo f HT , D: total dimensions of vectors)
typedef struct random_T *random_t_ptr ;
typedef struct random_r *random_rptr ;
typedef struct hashing_functions *hash_h_ptr;
typedef struct query_vectors *query_items_ptr;
typedef struct query_distance *query_dist_ptr ;




//objects of the bucket
struct bucketmember{
        int key;
        vector_ptr v_ptr;
		number_ptr n_ptr;
		matrix_ptr m_ptr;
};


typedef struct bucketmember BucketMember;
BucketMember **global_bucket_key ;
//the bucket
struct bucket {
        BucketMember * bucketarray;
        int count;
        int size;
};

typedef struct bucket Bucket;

//o pinakas twn bucket kathe thesh deixnei se ena bucket
Bucket *** BucketArray;
Bucket * p;
hash_h_ptr hash_ptr;
random_t_ptr tptr;
query_dist_ptr dptr;

struct infos {
     int startbucketsize ;
     int countentries;
} Infos;




#endif

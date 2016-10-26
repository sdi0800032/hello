struct vectors {
  double *vector_coords;
};

typedef struct vectors *vector_ptr;



//objects of the bucket
struct bucketmember{
        int key;
        vector_ptr v_ptr;
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


struct infos {
     int startbucketsize ;
     int countentries;
} Infos;

+ sunarthseis



void initHashtable(int hsize , int L) {
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
    global_bucket_key = malloc( L * sizeof(BucketMember));					// to global key agnohse to einai dikh m paradoxh isws na mh to xreiazesai
    for(i=0; i<L; i++){
		global_bucket_key[i] = malloc(sizeof(BucketMember));
		global_bucket_key[i]->key = 0;
	}
	
}



void bucketentry( vector_ptr vptr , int position , int z , int table) {
    BucketMember temps;
    temps.v_ptr = malloc(sizeof(struct vectors));
    temps.v_ptr->vector_coords = malloc(sizeof(double) * 100);
    temps.v_ptr->vector_coords = vptr[z].vector_coords ;
    temps.key = global_bucket_key[table]->key;
    global_bucket_key[table]->key ++;
    putinbucket(temps, position , table);
}


void putinbucket(BucketMember temp, int position , int table) {
    if (BucketArray[table][position]->count == BucketArray[table][position]->size) {
        BucketArray[table][position]->size *= 2;
        BucketArray[table][position]->bucketarray = realloc(BucketArray[table][position]->bucketarray, BucketArray[table][position]->size * sizeof (BucketMember));
        BucketArray[table][position]->bucketarray[BucketArray[table][position]->count++] = temp;
    } else {
        BucketArray[table][position]->bucketarray[BucketArray[table][position]->count++] = temp;
        Infos.countentries++;
    }

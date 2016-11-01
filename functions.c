#ifndef FUNCTIONS_C
#define FUNCTIONS_C


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "hash.h"
//#include <math.h>
#define LINESZ 4096









///////dimiourgei kainourgio entry tou hashtable gia metric spaces kai to stelnei stin putinbucket gia na to valei sto hashtable

void bucketentry2( matrix_ptr mptr , int position , int z , int table) {
    BucketMember temps;
    temps.m_ptr = malloc(sizeof(struct matrix));
    temps.m_ptr->matrix_distances = malloc(sizeof(int) * 1000);
    temps.m_ptr->id= malloc(sizeof(char) * 100);
    temps.m_ptr->matrix_distances= mptr->matrix_distances ;
    temps.m_ptr->id = mptr->id;
    temps.m_ptr->position = mptr->position;
    temps.key = global_bucket_key[table]->key;
    global_bucket_key[table]->key ++;
    putinbucket(temps, position , table);
}

///////dimiourgei kainourgio entry tou hashtable gia hamming spaces kai to stelnei stin putinbucket gia na to valei sto hashtable

void bucketentry1( number_ptr nptr , int position , int table) {
    BucketMember temps;
    temps.n_ptr = malloc(sizeof(struct number));
    temps.n_ptr->name= malloc(sizeof(char) * 100);
    temps.n_ptr->id= malloc(sizeof(char) * 100);
    temps.n_ptr->name = nptr->name ;
    temps.n_ptr->id = nptr->id;
	temps.n_ptr->position=nptr->position;
    temps.key = global_bucket_key[table]->key;
    global_bucket_key[table]->key ++;
    putinbucket(temps, position , table);
}


#endif



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hash.h"
#include "records.h"
//#include <math.h>
#define LINESZ 1024




int main(int argc, char** argv){

	char path[256],query[256],output[256];
	int i=0;
	int k=0,L=0;
	char gramma[50],gramma2[50];
	for(i=0;i<argc;i++){
		if(strcmp(argv[i],"-d")==0){
				strcpy(path,argv[i+1]);
				printf("%s\n",path);
		}
		if(strcmp(argv[i],"-q")==0){
				strcpy(query,argv[i+1]);
				printf("%s\n",query);
		}
		if(strcmp(argv[i],"-o")==0){
				strcpy(output,argv[i+1]);
				printf("%s\n",output);
		}
		if(strcmp(argv[i],"-k")==0){
			sscanf(argv[i+1], "%d", &k);
		}
		if(strcmp(argv[i],"-L")==0){
			sscanf(argv[i+1], "%d", &L);
		}
	}
	i=0;
	if(L==0){
		L=5;
	}
	if(k==0){
		k=4;
	}
	printf(" k : %d L : %d \n",k,L);
 	FILE* stream = fopen(path, "r");


	fscanf(stream,"%s %s ",gramma,gramma2);
	printf("%s  \n", gramma2);

	if(strcmp(gramma2,"hamming")==0){
		hamming(path,k,L,query,output);
	}
	if(strcmp(gramma2,"matrix")==0){
		matrix(path,k,L,query,output);
	}
	if(strcmp(gramma2,"euclidean")==0){
		cosine_eucl(path, query, output, k  ,L  );
		//matrix(path,k,L,query,output);
	}
	return 1;
}



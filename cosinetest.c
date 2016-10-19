#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "Cstruct.h"


int main(int argc, char** argv){
	double item_coords;
	cos_items_ptr items_ptr;
	int elements=-2 ;				// starting at -2 to ignore the 2 titles in the euclidean files
	char * line = NULL;
    size_t len = 0;
    ssize_t read;
	char path[256];
	char *token;
    strcpy(path,argv[1]);
    printf("%s\n",path);
    FILE* fp ;
    fp = fopen(path, "r");
    if( fp == NULL) {
		printf("error opening file , exiting ... \n");
		return 0;
	}
	while ((read = getline(&line, &len, fp)) != -1) {
		elements++;
	}
	printf("Items in file :%d\n",elements);					// searched how many items are in file to dynamically allocate array of ''element'' size
	items_ptr = allocate_space( elements ) ;
	printf("allocating space for %d elements..\n" , elements);
	sleep(5);
	fclose(fp);
	fp = fopen(path, "r");
    if( fp == NULL) {
		printf("error opening file , exiting ... \n");
		return 0;
	}
	read = getline(&line, &len, fp);
	read = getline(&line, &len, fp);						// skip 2 lines (titles)
	 while ((read = getline(&line, &len, fp)) != -1) {
        printf("%s", line);
        token = strtok(line, "	");					
        printf( "%s\n", token );
        while( token != NULL ) {
			printf( "%s\n", token );
			token = strtok(NULL, "	");
			if(token!=NULL){
				item_coords = atof( token );				// xanoume akrivia edw
				store_coords( item_coords , items_ptr );			// save item coords in our structure
				}
		}
		items_ptr->current_items ++; 
		items_ptr->total_dimensions = items_ptr->current_dimension; 
		items_ptr->current_dimension = 0;
    }
	build_Ri( items_ptr->total_dimensions );
    fclose(fp);
    return 1;
}

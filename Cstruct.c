#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include "Cstruct.h"

cos_items_ptr allocate_space( int num){
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


void store_coords( double num , cos_items_ptr ptr ){
	double coords;
	coords = num;
	ptr->item_array[ptr->current_items][ptr->current_dimension] = coords;
	printf("test_print double in array : %f || %f \n" , coords , ptr->item_array[ptr->current_items][ptr->current_dimension]);
	ptr->current_dimension ++ ;
}


void build_Ri( int dimensions ){
	double random_value_1 , random_value_2;
	double r , log_value , power_value;
	double x_1 ;
	int i;
//	srand(time(NULL));
	for( i =0; i<dimensions ; i++ ){
		while(1){
			random_value_1 = -1 + ((double)rand()/(double)RAND_MAX )*(2);			// -1 to 1
			printf ( "%f\n", random_value_1);
			random_value_2 =  -1 + ((double)rand()/(double)RAND_MAX)*(2);	
			printf ( "%f\n", random_value_2);
			
			r = pow(random_value_1 , 2) + pow(random_value_2 , 2) ;
			if( r < 1 ) break ; 		// acceptable pair
		}
		power_value = pow( r , 2.0);
//		printf("R = %f \n" , r);
//		printf("r^2 = %f \n" , power_value);
		log_value = log(0.108554);
//		printf("log(r^2) = %f \n" , log_value);
		x_1 = sqrt( (-2*log_value)/power_value) * random_value_1;

//		printf("TEST %f \n" , x_1);
	}
	
}
	
	
    
    

    
    
    
    

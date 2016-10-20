#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include "Cstruct.h"

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

Ri_ptr allocate_space_Ri(int K , int dimensions){
	int i;
	Ri_ptr rptr;
	rptr = malloc(sizeof(struct R_i));
	rptr->values = malloc(sizeof(double)*dimensions);
	for(i=0; i<dimensions; i++){
		rptr->values[i] = malloc(sizeof(double)*K);
	}
	rptr->current_Rdimension=0;
	rptr->current_Kposition = 0;
	return rptr;
}
	
	

void store_item_coords( double num , cos_items_ptr ptr ){
	double coords;
	coords = num;
	ptr->item_array[ptr->current_items][ptr->current_dimension] = coords;
//	printf("test_print double in array(items) : %f || %f \n" , coords , ptr->item_array[ptr->current_items][ptr->current_dimension]);
	ptr->current_dimension ++ ;
}


void store_Ri_coords( double num , Ri_ptr rptr){
	rptr->values[rptr->current_Rdimension][rptr->current_Kposition] = num;
//	printf("test_print double in array(R_i) : %f || %f \n" , num , rptr->values[rptr->current_Rdimension][rptr->current_Kposition]);
//	printf("test dimension / K %d %d \n" , rptr->current_Rdimension , rptr->current_Kposition);
//	sleep(1);
	rptr->current_Rdimension ++ ;
	
	}


void build_Ri( int dimensions , int K , Ri_ptr rptr , cos_items_ptr items_ptr , int elements){
	double random_value_1 , random_value_2;
	double r , log_value , power_value;
	double x_1 , val;														
	int i , j;
	for( j=0 ; j<K ; j++){	
			srand(time(NULL));												// we need K hi
		for( i =0; i<dimensions ; i++ ){									// create Ri in N(0,1)^d (in X dimensions)
			while(1){
				random_value_1 = M + ( (double)rand()/((double)RAND_MAX + 1.0 ))*(N-M);			// -1 to 1
//				printf ( "%f\n", random_value_1);
				random_value_2 =  -1 + ((double)rand()/((double)RAND_MAX + 1.0))*(N-M);	
	//			printf ( "%f\n", random_value_2);
				
				r = pow(random_value_1 , 2) + pow(random_value_2 , 2) ;
				if( r < 1 ) break ; 		// acceptable pair
			}
			power_value = pow( r , 2.0);
			
//			printf("R = %f \n" , r);
//			printf("r^2 = %f \n" , power_value);
			log_value = log(power_value);
//			printf("log(r^2) = %f \n" , log_value);
			val = (log_value*(-2)) / power_value ; 
//			printf(" -2 log / r^2 = %f\n" , val);
			x_1 = sqrt(val) * random_value_1;
//			printf("TEST %f \n" , x_1);
			store_Ri_coords( x_1 , rptr );
		}
		rptr->current_Kposition ++;
		rptr->current_Rdimension = 0;
		
	}
	rptr->current_Kposition = 0 ;
	rptr->current_Rdimension = 0;
	build_Hi( items_ptr , rptr , elements , K );
	
}
	
	
void build_Hi( cos_items_ptr items_ptr , Ri_ptr rptr , int total_items , int K ){
	int z , i , j , table_slot , power;
	double sum = 0.0 ;
	for(z=0; z<total_items; z++){
		table_slot = 0;
		for(i=0; i<K; i++){
			for(j=0; j< items_ptr->total_dimensions; j++){
		//		printf("%f   first\n" , items_ptr->item_array[z][j]);
		//		printf("%f second\n" , rptr->values[j][i]);
		//		printf("%f test sum  %f \n" , items_ptr->item_array[z][j] * rptr->values[j][i] , sum);
				sum += items_ptr->item_array[z][j] * rptr->values[j][i] ;
				
			}
		//	printf("testsum %f\n" , sum);
			if(sum>=0) {
				power = pow(2 , K-(i+1) );
//				printf("%d test power \n" , power);
				table_slot += power;
			}
		// insert in hash_Table item:z in slot: table_slot			
	}
	printf("testing table_slot for item %d: %d\n" , z , table_slot);		
	}
}
    

    
    
    
    

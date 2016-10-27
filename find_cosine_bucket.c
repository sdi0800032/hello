int find_bucket_cosine(int id , cos_items_ptr items_ptr , Ri_ptr rptr , int K , int table){
	int i,j , table_slot , power;
	double sum;
	table_slot = 0;
	
	
	for(i=0 ; i<K; i++){
		sum = 0;
		for(j=0 ; j< items_ptr->total_dimensions; j++){
			sum = sum + (items_ptr->item_array[id][j] * rptr[table]->values[j][i]) ;
		}
		if(sum>=0) {
			power = pow(2 , K-(i+1) );
			table_slot += power;
		}
	}
	
	
	return table_slot;
}

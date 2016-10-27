int searchHashtable_cosine(int id ,cos_items_ptr items_ptr , Ri_ptr rptr , int K , int table ) {
	int j , tableslot  , slot;
	tableslot = find_bucket_cosine(id , items_ptr , rptr , K , table);
    for (j = 0; j < BucketArray[table][tableslot]->size; j++) {
        if (BucketArray[table][tableslot]->bucketarray[j].key == id) {
			printf("key : %d \n" , BucketArray[table][tableslot]->bucketarray[j].key );
            printf("found item with id%d at bucket %d  , at table : %d , j:%d\n" , id , tableslot , table+1 , j);
            slot = j;
            break;
        }
    }
    
    for(j=0; j< items_ptr->total_dimensions; j++){;
		printf("%f " ,  BucketArray[table][tableslot]->bucketarray[slot].v_ptr->vector_coords[j]);
		
		}
	return slot; 
 
  
}

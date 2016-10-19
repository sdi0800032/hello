

struct COS_items {
	double **item_array;
	int current_items;
	int current_dimension;
	int total_dimensions;
};

typedef struct COS_items *cos_items_ptr;


cos_items_ptr allocate_space( int ) ;
void store_coords( double  , cos_items_ptr) ;
void build_Ri( int ) ;

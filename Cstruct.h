

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

typedef struct COS_items *cos_items_ptr;
typedef struct R_i *Ri_ptr;


cos_items_ptr allocate_space_items( int ) ;
Ri_ptr allocate_space_Ri(int , int);
void store_item_coords( double  , cos_items_ptr) ;
void build_Ri( int , int , Ri_ptr , cos_items_ptr , int) ;
void store_Ri_coords( double , Ri_ptr );
void build_Hi( cos_items_ptr , Ri_ptr , int , int  );

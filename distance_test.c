//
//  testa distance!
//
//

#include "max.h"



int main( void )
{
    int nearest_wall;
    int distance;
    
    int initialize = initialize_max();
    
    while(1){
        distance = get_distance();
        printf("Distance: %d \n", distance);
    }
    
    brick_uninit(); //funktion från biblioteket
    return(0);

}




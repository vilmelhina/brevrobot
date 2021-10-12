//
//  testa distance!
//
//

#include "max.h"



int main( void )
{
    int nearest_wall;
    int distance;
    int angle;
    
    int initialize = initialize_max();
    
    while(1){
        distance = get_distance();
        angle = get_angle();
        printf("Distance: %d Angle: %d\n", distance, angle);
    }
    
    brick_uninit(); //funktion från biblioteket
    return(0);

}




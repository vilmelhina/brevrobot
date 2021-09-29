//
//  max.c
//  
//
//  Created by Vilhelmina Andersson on 2021-09-29.
//

#include "max.h"

int main( void )
{
    int initialize = initialize();
    while(!TouchReturnValue){
        TouchReturnValue = sensor_get_value(0, touchSensor, 0);
        
        printf("Gyro0: %d , Gyro1: %d \n", getAngle() );
    
    }//Så länge touch sensorn inte är intryckt kommer while loopen köras
    

    brick_uninit();
    printf( "dying...\n" );
    return ( 0 );

}

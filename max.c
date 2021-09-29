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
    
    /*Registrerar en sensor på sensor variabeln*/
    touchSensor = sensor_search( LEGO_EV3_TOUCH ); //
    gyroSensor = sensor_search(LEGO_EV3_GYRO);
    /*Man kan antingen använda "Brick" bibliotekets förbyggda modes*/
    touch_set_mode_touch(touchSensor);
    
    /*eller kolla i sensor.h filen på vilka modes som finns för alla olika sensorer*/
    sensor_set_mode(gyroSensor, LEGO_EV3_GYRO_GYRO_G_AND_A);
    
    while(!TouchReturnValue){
        TouchReturnValue = sensor_get_value(0, touchSensor, 0);
        
        printf("Gyro0: %d , Gyro1: %d \n", getAngle() );
    
    }//Så länge touch sensorn inte är intryckt kommer while loopen köras
    

    brick_uninit();
    printf( "dying...\n" );
    return ( 0 );

}

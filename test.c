//
//  max.c
//  testar alla de simpla funktionerna som vi ska skriva
//
//  Created by Vilhelmina Andersson on 2021-09-29.
//

#include <stdio.h>
#include "brick.h"
#include <unistd.h>

#define Sleep( msec ) usleep(( msec ) * 1000 ) /*Definerar sleep där Sleep(1000)= 1 sekund*/

#define MOTOR_RIGHT        OUTA
#define MOTOR_LEFT        OUTB
#define MOTOR_C            OUTC
#define MOTOR_D            OUTD
#define SENSOR_TOUCH    IN1
#define SENSOR_GYRO        IN2
#define SENSOR_3        IN3
#define SENSOR_4        IN4
#define MOTOR_BOTH         ( MOTOR_LEFT | MOTOR_RIGHT ) /* Bitvis ELLER ger att båda motorerna styrs samtidigt */

POOL_T touchSensor;
int TouchReturnValue = 0;
int max_hastighet;         /* variabel för max hastighet på motorn */
POOL_T gyroSensor;


int main( void )
{
    if ( !brick_init()) return ( 1 ); /*Instansierar klossen och tillåter remote-connection*/
    printf( "*** ( EV3 ) Hello! ***\n" );
    Sleep(2000);

    if(!sensor_is_plugged((SENSOR_TOUCH|SENSOR_GYRO), SENSOR_TYPE__NONE_)) {
        printf("Stoppa in sensorer i port 1 och 2\n");
        brick_uninit();
        return(0);
    }
    
    touchSensor = sensor_search( LEGO_EV3_TOUCH );  // Registrerar en touch sensor på touchSensor-variabeln
    gyroSensor = sensor_search(LEGO_EV3_GYRO);
    touch_set_mode_touch(touchSensor); //anger vilken "mode" sensorn skall ha
    sensor_set_mode(gyroSensor, LEGO_EV3_GYRO_GYRO_G_AND_A); /*eller kolla i sensor.h filen på vilka modes som finns för alla olika sensorer*/
    
    tacho_set_speed_sp( MOTOR_BOTH, max_hastighet * 0.3 );  // Sätter hastigheten på båda motorerna till 50% av maxhastigheten
    
    tacho_run_forever(  MOTOR_BOTH );
    Sleep( 5000 );
    tacho_stop( MOTOR_BOTH );
    
    brick_uninit();
    printf( "dying...\n" );
    return ( 0 );

}



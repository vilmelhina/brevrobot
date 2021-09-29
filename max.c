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

int get_angle();
void drop_off();
int measure_distance();
int get_max_speed();
int time_forward(int, int);
void go(int,int);

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
    
    //testa getAngle tills touch trycks in
    while(!TouchReturnValue){
        TouchReturnValue = sensor_get_value(0, touchSensor, 0);
        
        printf("Gyro: %d\n", get_angle() );
    
    }
    //testa drop_off
    drop_off();
    
    //testa measure_distance tills touch sensorn trycks in
    /*while(!TouchReturnValue){
        TouchReturnValue = sensor_get_value(0, touchSensor, 0);
        
        printf("Distance: %d\n", measure_distance() );
    
    }*/ //KOMMENTERA UT NÄR FUNKTIONEN ÄR KLAR
    
    //testa get_max_speed och time_forward och go
    /*int speed = 0.3 * get_max_speed();
    int distance = 20;
    time_forward(speed,distance);
     go(speed,time);
     */
    //KOMMENTERA UT NÄR FUNKTIONERNA ÄR KLARA
    
    brick_uninit();
    printf( "dying...\n" );
    return ( 0 );

}

int get_angle(){
    int angle = sensor_get_value(0, gyroSensor, 0);
    return angle;
}

void drop_off(){
    if ( tacho_is_plugged( MOTOR_BOTH, TACHO_TYPE__NONE_ )) {  /* TACHO_TYPE__NONE_ = Alla typer av motorer */
        max_hastighet = tacho_get_max_speed( MOTOR_LEFT, 0 );    /* Kollar maxhastigheten som motorn kan ha */
        tacho_reset( MOTOR_BOTH );
    } else {
        printf( "Anslut vänster motor i port A,\n"
        "Anslut höger motor i port B.\n"
        );
          brick_uninit();
    }
    tacho_set_speed_sp( MOTOR_C, max_hastighet * (0.5) );  // Sätter hastigheten på båda motor c till positiv
    tacho_run_forever(  MOTOR_C );
    Sleep( 3000 );
    tacho_stop( MOTOR_C );
    tacho_set_speed_sp( MOTOR_C, max_hastighet * (-0.5) );  // Sätter hastigheten på båda motor c till negativ
    tacho_run_forever(  MOTOR_C );
    Sleep( 3000 );
    tacho_stop( MOTOR_C );
}

int measure_distance(){
    return 0;
}

int get_max_speed(){
    return 0;
}

int time_forward(int speed, int distance){
    return 0;
}

void go(int speed, int time){
    
}

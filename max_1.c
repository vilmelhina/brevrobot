//
//  max_1.c
//  uppgift 1!!!!!!!!
//
//

#include <stdio.h>
#include "brick.h"
#include <unistd.h>

#define Sleep( msec ) usleep(( msec ) * 1000 ) /*Definerar sleep där Sleep(1000)= 1 sekund*/

#define MOTOR_RIGHT       OUTA
#define MOTOR_LEFT        OUTB
#define MOTOR_C           OUTC
#define MOTOR_D           OUTD
#define SENSOR_TOUCH      IN1
#define SENSOR_GYRO       IN2
#define SENSOR_US         IN3
#define SENSOR_4          IN4
#define MOTOR_BOTH        ( MOTOR_LEFT | MOTOR_RIGHT ) /* Bitvis ELLER ger att båda motorerna styrs samtidigt */

POOL_T touch_sensor;
POOL_T gyro_sensor;
POOL_T sonic_sensor;

int max_hastighet;         /* variabel för max hastighet på motorn */

void initialize_max();
int find_wall();
void go(int);
void turn_to_angle(int);
void go_until_distance(int);
void drop_off();
int initialize_max();

int main( void )
{
    int nearest_wall;
    
    //starta upp grejerna
    int initialize = initialize_max();
    
    //hitta närmaste väggen
    nearest_wall = find_wall();
    
    //snurra till 90 grader från närmaste väggen
    turn_to_angle(nearest_wall + 90); //ändra till -90 för uppgift 2 & 4
    
    //åk 250cm
    go(250);
    
    //hitta närmaste väggen
    nearest_wall = find_wall();
    turn_to_angle(nearest_wall); //för uppgift 3 och 4, nearest_wall + 180
    go_until_distance(30);
    
    //lämna av paketet
    drop_off();
    
    brick_uninit(); //funktion från biblioteket
    return(0);

}


//en funktion som startar upp och registrerar sensorer och lägen på sensorer, allt som behöver göras innan programmet börjar. Detta kommer i huvudsak från filerna exempelGyroTouch.c och exempelMotorTouch-2.c
int initialize_max(){
    if ( !brick_init()) return ( 1 ); /* Initialiserar EV3-klossen */
    printf( "*** ( EV3 ) Hello! ***\n" );
    Sleep( 2000 );
    
    if ( tacho_is_plugged( MOTOR_BOTH, TACHO_TYPE__NONE_ )) {  /* TACHO_TYPE__NONE_ = Alla typer av motorer */
        max_hastighet = tacho_get_max_speed( MOTOR_LEFT, 0 );    /* Kollar maxhastigheten som motorn kan ha */
        tacho_reset( MOTOR_BOTH );
    } else {
        printf( "Anslut vänster motor i port A,\n"
        "Anslut höger motor i port B.\n"
        );
        Sleep( 2000 );
          brick_uninit();
        return ( 0 );  /* Stänger av sig om motorer ej är inkopplade */
    }
    
    //kolla att touch och gyro är inkopplade!!!
    if(!sensor_is_plugged((SENSOR_TOUCH|SENSOR_GYRO), SENSOR_TYPE__NONE_)) {
        printf("Stoppa in sensorer i port 1 och 2\n");
        brick_uninit();
        return(0);
    }
    
    // TOUCH SENSOR
    touch_sensor = sensor_search( LEGO_EV3_TOUCH ); // Registrerar en touch sensor på touch_sensor-variabeln
    touch_set_mode_touch(touch_sensor); // anger vilken "mode" sensorn skall ha
    
    //SONIC SENSOR
    sonic_sensor = sensor_search(LEGO_EV3_US);
    us_set_mode_us_dist_cm(sonic_sensor);
    
    //GYRO SENSOR
    /*Registrerar en sensor på sensor variabeln*/
    gyro_sensor = sensor_search(LEGO_EV3_GYRO);
    sensor_set_mode(gyro_sensor, LEGO_EV3_GYRO_GYRO_G_AND_A);
    
    
    return 0;
}

//hittar vinkeln till närmaste väggen och returnerar det värdet
int find_wall(){
    int angle = sensor_get_value(0, gyro_sensor, 0);
    int min_angle = angle;
    int min_distance = sensor_get_value(0, us_sensor,0);
    int current_distance;
    
    for (int i=0; i<361; i++) {
        current_distance = sensor_get_value(0, us_sensor,0); //avstånd fram just nu
        int angle = sensor_get_value(0, gyro_sensor, 0); //uppdatera vinkeln den står i just nu
        
        if(current_distance < min_distance) {
            min distance = current_distance;
            min_angle = angle;
        }
        turn_to_angle(angle + 1); //vrid 1 grad
    }
    
    return min_angle; //return the angle that had the smallest distance forward
}

//åker det givna avståndet rakt framåt (modifierad version av koden VILLE & ELIN skrev)
void go(int distance){
    float speedPercentage = 0.3; //den ska åka 30% av maxhastigheten
    int seconds = (distance/0.15) * 1000; //räknar ut antal millisekunder den ska åka
    tacho_set_speed_sp( MOTOR_BOTH, max_hastighet * speedPercentage ); //sätter hastigheten
    tacho_run_forever(  MOTOR_BOTH ); //startar motorerna
    Sleep( seconds * 1000 ); //väntar i så många sekunder som räknats ut
    tacho_stop( MOTOR_BOTH ); //stoppar motorerna
}

//vrider sig till den givna vinkeln
void turn_to_angle(int goal_angle){
    int current_angle = sensor_get_value(0, gyro_sensor, 0);
    
    tacho_set_speed_sp( MOTOR_RIGHT, max_hastighet * (-0.1) );
    tacho_set_speed_sp( MOTOR_LEFT, max_hastighet * (0.1) );
    tacho_run_forever(  MOTOR_BOTH ); //start turning
    
    while (goal_angle != current_angle) {
        current_angle = sensor_get_value(0, gyro_sensor, 0);
    }
    tacho_stop( MOTOR_BOTH ); //stop turning
}

//åker framåt tills väggen framför är så nära som det givna värdet
void go_until_distance(int distance_goal){
    int distance = sensor_get_value(0, us_sensor,0);
    
    tacho_set_speed_sp( MOTOR_RIGHT, max_hastighet * (0.3) );
    tacho_set_speed_sp( MOTOR_LEFT, max_hastighet * (0.3) );
    tacho_run_forever(  MOTOR_BOTH ); //start driving
    
    while(distance > distance_goal){
        distance = sensor_get_value(0, us_sensor,0);
    }
    
    tacho_stop( MOTOR_BOTH ); //stop driving
}

//lastar av sin post!
void drop_off(){
    // sänk ner gaffeln
    // ta upp gaffeln igen
}

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

#define MOTOR_RIGHT       OUTA
#define MOTOR_LEFT        OUTB
#define MOTOR_C           OUTC
#define MOTOR_D           OUTD
#define SENSOR_TOUCH      IN1
#define SENSOR_GYRO       IN2
#define SENSOR_3          IN3
#define SENSOR_4          IN4
#define MOTOR_BOTH        ( MOTOR_LEFT | MOTOR_RIGHT ) /* Bitvis ELLER ger att båda motorerna styrs samtidigt */

POOL_T touchSensor;
POOL_T gyroSensor;

void initialize_max();
int nearest_wall();
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
    initialize_max();
    
    //hitta närmaste väggen
    nearest_wall = find_wall();
    
    //snurra till 90 grader från närmaste väggen
    turn_to_angle(nearest_wall + 90); //ändra till -90 för uppgift 2
    
    //åk 250cm
    go(250);
    
    //hitta närmaste väggen
    nearest_wall = find_wall();
    turn_to_angle(nearest_wall); //för uppgift 3 och 4, nearest_wall + 180
    go_until_distance(30);
    
    //lämna av paketet
    drop_off();

}


initialize_max(){
    
}

void initialize_max(){
    
}
int nearest_wall(){
    return 0;
}
int find_wall(){
    return 0;
}
void go(int distance){
    
}
void turn_to_angle(int angle){
    
}
void go_until_distance(int distance){
    
}
void drop_off(){
    return 0;
}

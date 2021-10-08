//
//  max_4.c
//  uppgift 4!
//
//

#include "max.h"



int main( void )
{
    int nearest_wall;
    
    //starta upp grejerna
    int initialize = initialize_max();
    
    //hitta närmaste väggen
    nearest_wall = find_wall();
    
    //snurra till 90 grader från närmaste väggen
    turn_to_angle(nearest_wall + 270); // till höger
    
    //åk 250cm
    go(250);
    
    //hitta närmaste väggen
    nearest_wall = find_wall();
    turn_to_angle(nearest_wall + 180); 
    go_until_distance(300);
    
    //lämna av paketet
    drop_off();
    
    brick_uninit(); //funktion från biblioteket
    return(0);

}



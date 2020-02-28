#include "STD_TYPES.h"
#include "sysctl.h"
#include "gpio.h"
#include "SWITCH.h"
#include "SWITCH_config.h"


/*
  Creating an array of switch struct that holds switches in the system
*/
const switchmap_t switchMap [SWITCH_NUM] = {
  {SWITCH_LEFTDOOR_PIN,SWITCH_LEFTDOOR_PORT,SWITCH_LEFTDOOR_PULL_STATE},
  {SWITCH_RIGHTDOOR_PIN,SWITCH_RIGHTDOOR_PORT,SWITCH_RIGHTDOOR_PULL_STATE}
};


/* 
  Description: This function shall return an element of switch from switchMap array
  
  Input: switchNum which holds the index of the switch in the switch array 
  
  Output: Address of switch struct that maps the switchNum 

 */
extern switchmap_t * getSwitchMap (u8 switchNum)
{
  return &switchMap[switchNum];
}

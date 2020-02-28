#include "STD_TYPES.h"
#include "sysctl.h"
#include "gpio.h"
#include "Lamp.h"
#include "Lamp_config.h"



/*
  Creating an array of Lamp struct that holds Lamps in the system
*/
const lampmap_t lampMap [Lamps_NUM] = {
  {Lamp_DIMMER_PIN,Lamp_DIMMER_PORT,Lamp_DIMMER_ON,Lamp_DIMMER_OFF}
};


/* 
  Description: This function shall return an element of Lamp from LampMap array
  
  Input: LampNum which holds the index of the Lamp in the Lamp array 
  
  Output: Address of Lamps struct that maps the LampNum 

 */
extern lampmap_t * getLampMap (u8 lampNum)
{
  return &lampMap[lampNum];
}

#define pinSet 1
#define pinReset 0

#define switchState u8

#define PRESSED  1
#define RELEASED 0 

typedef struct 
{
  u8 pin;
  u32 port;
  u32 pullState;
} switchmap_t;

/* 
  Description: This function shall initiate the specified switch num by setting its
  pin, port, mode and configuration in a GPIO object and passing it to GPIO module
  
  Input: switchNum which holds the index of the switch in the switch array 
  
  Output: errStat

 */
extern errStat Switch_Init(u8 switchNum);

/* 
  Description: This function shall return the specified switch state which can be 
  PRESSED or RELEASED
  
  Input: 
        1- switchNum which holds the index of the switch in the switch array 
        2- switchValue a pointer that containes the switch value 
        
  Output: errStat

 */
extern errStat Switch_GetSwitchState(u8 switchNum, switchState* switchValue);

/* 
  Description: This function shall return an element of array switch
  
  Input: switchNum which holds the index of the switch in the switch array 
  
  Output: Address of switch struct that maps the switchNum 

 */
extern switchmap_t * getSwitchMap (u8 switchNum);

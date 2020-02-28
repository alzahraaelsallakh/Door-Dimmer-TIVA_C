#define pinSet 0xff
#define pinReset 0x00

typedef struct 
{
  u8 pin;
  u32 port;
  u32 ON;
  u32 OFF;
} lampmap_t;


/* 
  Description: This function shall initiate the specified lamp num by setting its
  pin, port, mode and configuration in a GPIO object and passing it to GPIO module
  
  Input: lampNum which holds the index of the lamp in the lamp array 
  
  Output: errStat

 */
extern errStat Lamp_init(u8 lampNum);

/* 
  Description: This function shall turn on the specified lamp 
  
  Input: lampNum which holds the index of the lamp in the lamp array 
  
  Output: errStat

 */
extern errStat Lamp_SwitchOn(u8 lampNum);

/* 
  Description: This function shall turn off the specified lamp 
  
  Input: lampNum which holds the index of the lamp in the lamp array 
  
  Output: errStat

 */
extern errStat Lamp_SwitchOff(u8 lampNum);

/* 
  Description: This function shall return an element of lamp from lampMap array
  
  Input: lampNum which holds the index of the lamp in the lamp array 
  
  Output: Address of lamps struct that maps the lampNum 

 */
extern lampmap_t * getLampMap (u8 lampNum);

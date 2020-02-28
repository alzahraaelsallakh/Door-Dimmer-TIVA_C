#include "STD_TYPES.h"
#include "sysctl.h"
#include "gpio.h"
#include "SWITCH.h"
#include "SWITCH_config.h"
#include "leftDoor.h"

extern errStat LeftDoor_ReadStatus (u8* leftDoorStatus)
{
  errStat status = ERR_STAT_OK;
  
  status = Switch_GetSwitchState (SWITCH_LEFTDOOR,leftDoorStatus);
  
  return status;
}
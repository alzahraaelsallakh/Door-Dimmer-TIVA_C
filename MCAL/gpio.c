#include "STD_TYPES.h"
#include "gpio.h"

/******************************************************************************
    \param ui32Port is the base address of the GPIO port.                      
                                                                               
    This function shall determine if a GPIO port base address is valid.        
                                                                               
    \return Returns \b true if the base address is valid and \b false          
    otherwise.                                                                 
                                                                               
/******************************************************************************/
static u8
_GPIOBaseValid(u32 ui32Port)
{
    return((ui32Port == GPIO_PORTA_BASE) ||
           (ui32Port == GPIO_PORTB_BASE) ||
           (ui32Port == GPIO_PORTC_BASE) ||
           (ui32Port == GPIO_PORTD_BASE) ||
           (ui32Port == GPIO_PORTE_BASE) ||
           (ui32Port == GPIO_PORTF_BASE);
}
/******************************************************************************

    Sets the direction and mode of the specified pin(s).

    \param ui32Port is the base address of the GPIO port
    \param ui8Pins is the bit-packed representation of the pin(s).
    \param ui32PinIO is the pin direction and/or mode.

    This function configures the specified pin(s) on the selected GPIO port
    as either input or output under software control, or it configures the
    pin to be under hardware control.

    The parameter \e ui32PinIO is an enumerated data type that can be one of
    the following values:

    - GPIO_DIR_MODE_IN
    - GPIO_DIR_MODE_OUT
    - GPIO_DIR_MODE_HW

/******************************************************************************/
errStat GPIO_DirModeSet(u32 ui32Port, u8 ui8Pins, u32 ui32PinIO)
{
    /*
      Check the arguments.
    */
    if (_GPIOBaseValid(ui32Port) && ((ui32PinIO == GPIO_DIR_MODE_IN) || (ui32PinIO == GPIO_DIR_MODE_OUT) ||(ui32PinIO == GPIO_DIR_MODE_HW)))
    {
      /*
        Set the pin direction and mode.
      */
      HWREG(ui32Port + GPIO_O_DIR) = ((ui32PinIO & 1) ?
                                      (HWREG(ui32Port + GPIO_O_DIR) | ui8Pins) :
                                      (HWREG(ui32Port + GPIO_O_DIR) & ~(ui8Pins)));
      HWREG(ui32Port + GPIO_O_DEN) |= ui8Pins;
      return ERR_STAT_OK;
    }
    return ERR_STAT_NOK;
}

/******************************************************************************
  
  ! Reads the values present of the specified pin(s).
  !
  ! \param ui32Port is the base address of the GPIO port.
  ! \param ui8Pins is the bit-packed representation of the pin(s).
  !
  ! \return Returns  the state of the specified
  ! pin, where bit 0 of the byte represents GPIO port pin 0, bit 1 represents
  ! GPIO port pin 1, and so on.  Any bit that is not specified by \e ui8Pins
  ! is returned as a 0.  Bits 31:8 should be ignored.
  
/******************************************************************************/
errStat GPIO_PinRead(u32 ui32Port, u8 ui8Pins, u8* ui8Val)
{
    /*
       Check the arguments.
    */
    if (_GPIOBaseValid(ui32Port))
    {
      /*
         Return the pin value(s).
      */
      *ui8Val = (HWREG(ui32Port + (GPIO_O_DATA + (ui8Pins << 2))));
      return ERR_STAT_OK;
    }
    return ERR_STAT_NOK;
}

/******************************************************************************
  
  ! Writes a value to the specified pin(s).
  !
  ! \param ui32Port is the base address of the GPIO port.
  ! \param ui8Pins is the bit-packed representation of the pin(s).
  ! \param ui8Val is the value to write to the pin(s).
  !
  ! Writes the corresponding bit values to the output pin(s) specified by
  ! \e ui8Pins.  Writing to a pin configured as an input pin has no effect.
  !
  ! The pin(s) are specified using a bit-packed byte, where each bit that is
  ! set identifies the pin to be accessed, and where bit 0 of the byte
  ! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
  !
  ! \return None.
  
/******************************************************************************/
errStat GPIO_PinWrite(u32 ui32Port, u8 ui8Pins, u8 ui8Val)
{
    /*
       Check the arguments.
    */
    if(_GPIOBaseValid(ui32Port))
    {
      /*
         Write the pins.
      */
      HWREG(ui32Port + (GPIO_O_DATA + (ui8Pins << 2))) = ui8Val;
      return ERR_STAT_OK;
    }
    return ERR_STAT_NOK;
}

/******************************************************************************

  ! Sets the pad configuration for the specified pin(s).

  ! \param ui32Port is the base address of the GPIO port.
  ! \param ui8Pins is the bit-packed representation of the pin(s).
  ! \param ui32Strength specifies the output drive strength.
  ! \param ui32PinType specifies the pin type.
  !
  ! This function sets the drive strength and type for the specified pin(s)
  ! on the selected GPIO port.  For pin(s) configured as input ports, the
  ! pad is configured as requested, but the only real effect on the input
  ! is the configuration of the pull-up or pull-down termination.
  !
  ! The parameter \e ui32Strength can be one of the following values:
  !
  ! - \b GPIO_STRENGTH_2MA
  ! - \b GPIO_STRENGTH_4MA
  ! - \b GPIO_STRENGTH_8MA
  ! - \b GPIO_STRENGTH_8MA_SC
  ! - \b GPIO_STRENGTH_6MA
  ! - \b GPIO_STRENGTH_10MA
  ! - \b GPIO_STRENGTH_12MA
  !
  !
  ! The parameter \e ui32PinType can be one of the following values:
  !
  ! - \b GPIO_PIN_TYPE_STD
  ! - \b GPIO_PIN_TYPE_STD_WPU
  ! - \b GPIO_PIN_TYPE_STD_WPD
  ! - \b GPIO_PIN_TYPE_OD
  ! - \b GPIO_PIN_TYPE_ANALOG
  ! - \b GPIO_PIN_TYPE_WAKE_HIGH
  ! - \b GPIO_PIN_TYPE_WAKE_LOW
  
/******************************************************************************/
errStat GPIO_PadConfigSet(u32 ui32Port, u8 ui8Pins, u32 ui32Strength, u32 ui32PinType)
{
    u8 ui8Bit;

    /*
       Check the arguments.
    */
    if (
        (_GPIOBaseValid(ui32Port)) &&
        (
         (ui32Strength == GPIO_STRENGTH_2MA) ||
         (ui32Strength == GPIO_STRENGTH_4MA) ||
         (ui32Strength == GPIO_STRENGTH_6MA) ||
         (ui32Strength == GPIO_STRENGTH_8MA) ||
         (ui32Strength == GPIO_STRENGTH_8MA_SC) ||
         (ui32Strength == GPIO_STRENGTH_10MA) ||
         (ui32Strength == GPIO_STRENGTH_12MA)
         ) &&
        (
         (ui32PinType == GPIO_PIN_TYPE_STD) ||
         (ui32PinType == GPIO_PIN_TYPE_STD_WPU) ||
         (ui32PinType == GPIO_PIN_TYPE_STD_WPD) ||
         (ui32PinType == GPIO_PIN_TYPE_OD) ||
         (ui32PinType == GPIO_PIN_TYPE_WAKE_LOW) ||
         (ui32PinType == GPIO_PIN_TYPE_WAKE_HIGH) ||
         (ui32PinType == GPIO_PIN_TYPE_ANALOG)
         )
       )
    {

      for(ui8Bit = 0; ui8Bit < 8; ui8Bit++)
      {
          if(ui8Pins & (1 << ui8Bit))
          {
              HWREG(ui32Port + GPIO_O_PC) = (HWREG(ui32Port + GPIO_O_PC) &
                                             ~(0x3 << (2 * ui8Bit)));
              HWREG(ui32Port + GPIO_O_PC) |= (((ui32Strength >> 5) & 0x3) <<
                                              (2 * ui8Bit));
          }
      }

      /*
         Set the output drive strength.
      */
      HWREG(ui32Port + GPIO_O_DR2R) = ((ui32Strength & 1) ?
                                       (HWREG(ui32Port + GPIO_O_DR2R) |
                                        ui8Pins) :
                                       (HWREG(ui32Port + GPIO_O_DR2R) &
                                        ~(ui8Pins)));
      HWREG(ui32Port + GPIO_O_DR4R) = ((ui32Strength & 2) ?
                                       (HWREG(ui32Port + GPIO_O_DR4R) |
                                        ui8Pins) :
                                       (HWREG(ui32Port + GPIO_O_DR4R) &
                                        ~(ui8Pins)));
      HWREG(ui32Port + GPIO_O_DR8R) = ((ui32Strength & 4) ?
                                       (HWREG(ui32Port + GPIO_O_DR8R) |
                                        ui8Pins) :
                                       (HWREG(ui32Port + GPIO_O_DR8R) &
                                        ~(ui8Pins)));
      HWREG(ui32Port + GPIO_O_SLR) = ((ui32Strength & 8) ?
                                      (HWREG(ui32Port + GPIO_O_SLR) |
                                       ui8Pins) :
                                      (HWREG(ui32Port + GPIO_O_SLR) &
                                       ~(ui8Pins)));


      /*
         Set the pin type.
      */
      HWREG(ui32Port + GPIO_O_ODR) = ((ui32PinType & 1) ?
                                      (HWREG(ui32Port + GPIO_O_ODR) | ui8Pins) :
                                      (HWREG(ui32Port + GPIO_O_ODR) & ~(ui8Pins)));
      HWREG(ui32Port + GPIO_O_PUR) = ((ui32PinType & 2) ?
                                      (HWREG(ui32Port + GPIO_O_PUR) | ui8Pins) :
                                      (HWREG(ui32Port + GPIO_O_PUR) & ~(ui8Pins)));
      HWREG(ui32Port + GPIO_O_PDR) = ((ui32PinType & 4) ?
                                      (HWREG(ui32Port + GPIO_O_PDR) | ui8Pins) :
                                      (HWREG(ui32Port + GPIO_O_PDR) & ~(ui8Pins)));
      HWREG(ui32Port + GPIO_O_DEN) = ((ui32PinType & 8) ?
                                      (HWREG(ui32Port + GPIO_O_DEN) | ui8Pins) :
                                      (HWREG(ui32Port + GPIO_O_DEN) & ~(ui8Pins)));


      HWREG(ui32Port + GPIO_O_WAKELVL) = ((ui32PinType & 0x200) ?
                                          (HWREG(ui32Port + GPIO_O_WAKELVL) |
                                           ui8Pins) :
                                          (HWREG(ui32Port + GPIO_O_WAKELVL) &
                                           ~(ui8Pins)));
      HWREG(ui32Port + GPIO_O_WAKEPEN) = ((ui32PinType & 0x300) ?
                                          (HWREG(ui32Port + GPIO_O_WAKEPEN) |
                                           ui8Pins) :
                                          (HWREG(ui32Port + GPIO_O_WAKEPEN) &
                                           ~(ui8Pins)));

     
      return ERR_STAT_OK;
    }
    return ERR_STAT_NOK;
}


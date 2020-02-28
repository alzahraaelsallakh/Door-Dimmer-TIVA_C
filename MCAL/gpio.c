#include "STD_TYPES.h"
#include "hw_gpio.h"
#include "hw_types.h"
#include "gpio.h"

//*****************************************************************************
//
//! \internal
//! Checks a GPIO base address.
//!
//! \param ui32Port is the base address of the GPIO port.
//!
//! This function determines if a GPIO port base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
static u8
_GPIOBaseValid(u32 ui32Port)
{
    return((ui32Port == GPIO_PORTA_BASE) ||
           (ui32Port == GPIO_PORTA_AHB_BASE) ||
           (ui32Port == GPIO_PORTB_BASE) ||
           (ui32Port == GPIO_PORTB_AHB_BASE) ||
           (ui32Port == GPIO_PORTC_BASE) ||
           (ui32Port == GPIO_PORTC_AHB_BASE) ||
           (ui32Port == GPIO_PORTD_BASE) ||
           (ui32Port == GPIO_PORTD_AHB_BASE) ||
           (ui32Port == GPIO_PORTE_BASE) ||
           (ui32Port == GPIO_PORTE_AHB_BASE) ||
           (ui32Port == GPIO_PORTF_BASE) ||
           (ui32Port == GPIO_PORTF_AHB_BASE));
}
//*****************************************************************************
//
//! Sets the direction and mode of the specified pin(s).
//!
//! \param ui32Port is the base address of the GPIO port
//! \param ui8Pins is the bit-packed representation of the pin(s).
//! \param ui32PinIO is the pin direction and/or mode.
//!
//! This function configures the specified pin(s) on the selected GPIO port
//! as either input or output under software control, or it configures the
//! pin to be under hardware control.
//!
//! The parameter \e ui32PinIO is an enumerated data type that can be one of
//! the following values:
//!
//! - \b GPIO_DIR_MODE_IN
//! - \b GPIO_DIR_MODE_OUT
//! - \b GPIO_DIR_MODE_HW
//!
//! where \b GPIO_DIR_MODE_IN specifies that the pin is programmed as a
//! software controlled input, \b GPIO_DIR_MODE_OUT specifies that the pin is
//! programmed as a software controlled output, and \b GPIO_DIR_MODE_HW
//! specifies that the pin is placed under hardware control.
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \note GPIOPadConfigSet() must also be used to configure the corresponding
//! pad(s) in order for them to propagate the signal to/from the GPIO.
//!
//! \note A subset of GPIO pins on Tiva devices, notably those used by the
//! JTAG/SWD interface and any pin capable of acting as an NMI input, are
//! locked against inadvertent reconfiguration.  These pins must be unlocked
//! using direct register writes to the relevant GPIO_O_LOCK and GPIO_O_CR
//! registers before this function can be called.  Please see the ``gpio_jtag''
//! example application for the mechanism required and consult your part
//! datasheet for information on affected pins.
//!
//! \return None.
//
//*****************************************************************************
errStat GPIO_DirModeSet(u32 ui32Port, u8 ui8Pins, u32 ui32PinIO)
{
    //
    // Check the arguments.
    //
    if (_GPIOBaseValid(ui32Port) && ((ui32PinIO == GPIO_DIR_MODE_IN) || (ui32PinIO == GPIO_DIR_MODE_OUT) ||(ui32PinIO == GPIO_DIR_MODE_HW)))
    {
      //
      // Set the pin direction and mode.
      //
      HWREG(ui32Port + GPIO_O_DIR) = ((ui32PinIO & 1) ?
                                      (HWREG(ui32Port + GPIO_O_DIR) | ui8Pins) :
                                      (HWREG(ui32Port + GPIO_O_DIR) & ~(ui8Pins)));
      HWREG(ui32Port + GPIO_O_AFSEL) = ((ui32PinIO & 2) ?
                                        (HWREG(ui32Port + GPIO_O_AFSEL) |
                                         ui8Pins) :
                                        (HWREG(ui32Port + GPIO_O_AFSEL) &
                                         ~(ui8Pins)));
      HWREG(ui32Port + GPIO_O_DEN) |= ui8Pins;
      return ERR_STAT_OK;
    }
    return ERR_STAT_NOK;
}

//*****************************************************************************
//
//! Reads the values present of the specified pin(s).
//!
//! \param ui32Port is the base address of the GPIO port.
//! \param ui8Pins is the bit-packed representation of the pin(s).
//!
//! The values at the specified pin(s) are read, as specified by \e ui8Pins.
//! Values are returned for both input and output pin(s), and the value
//! for pin(s) that are not specified by \e ui8Pins are set to 0.
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \return Returns a bit-packed byte providing the state of the specified
//! pin, where bit 0 of the byte represents GPIO port pin 0, bit 1 represents
//! GPIO port pin 1, and so on.  Any bit that is not specified by \e ui8Pins
//! is returned as a 0.  Bits 31:8 should be ignored.
//
//*****************************************************************************
errStat GPIO_PinRead(u32 ui32Port, u8 ui8Pins, u8* ui8Val)
{
    //
    // Check the arguments.
    //
    if (_GPIOBaseValid(ui32Port))
    {
      //
      // Return the pin value(s).
      //
      *ui8Val = (HWREG(ui32Port + (GPIO_O_DATA + (ui8Pins << 2))));
      return ERR_STAT_OK;
    }
    return ERR_STAT_NOK;
}

//*****************************************************************************
//
//! Writes a value to the specified pin(s).
//!
//! \param ui32Port is the base address of the GPIO port.
//! \param ui8Pins is the bit-packed representation of the pin(s).
//! \param ui8Val is the value to write to the pin(s).
//!
//! Writes the corresponding bit values to the output pin(s) specified by
//! \e ui8Pins.  Writing to a pin configured as an input pin has no effect.
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \return None.
//
//*****************************************************************************
errStat GPIO_PinWrite(u32 ui32Port, u8 ui8Pins, u8 ui8Val)
{
    //
    // Check the arguments.
    //
    if(_GPIOBaseValid(ui32Port))
    {
      //
      // Write the pins.
      //
      HWREG(ui32Port + (GPIO_O_DATA + (ui8Pins << 2))) = ui8Val;
      return ERR_STAT_OK;
    }
    return ERR_STAT_NOK;
}

//*****************************************************************************
//
//! Sets the pad configuration for the specified pin(s).
//!
//! \param ui32Port is the base address of the GPIO port.
//! \param ui8Pins is the bit-packed representation of the pin(s).
//! \param ui32Strength specifies the output drive strength.
//! \param ui32PinType specifies the pin type.
//!
//! This function sets the drive strength and type for the specified pin(s)
//! on the selected GPIO port.  For pin(s) configured as input ports, the
//! pad is configured as requested, but the only real effect on the input
//! is the configuration of the pull-up or pull-down termination.
//!
//! The parameter \e ui32Strength can be one of the following values:
//!
//! - \b GPIO_STRENGTH_2MA
//! - \b GPIO_STRENGTH_4MA
//! - \b GPIO_STRENGTH_8MA
//! - \b GPIO_STRENGTH_8MA_SC
//! - \b GPIO_STRENGTH_6MA
//! - \b GPIO_STRENGTH_10MA
//! - \b GPIO_STRENGTH_12MA
//!
//! where \b GPIO_STRENGTH_xMA specifies either 2, 4, or 8 mA output drive
//! strength, and \b GPIO_OUT_STRENGTH_8MA_SC specifies 8 mA output drive with
//! slew control.
//!
//! Some Tiva devices also support output drive strengths of 6, 10, and 12
//! mA.
//!
//! The parameter \e ui32PinType can be one of the following values:
//!
//! - \b GPIO_PIN_TYPE_STD
//! - \b GPIO_PIN_TYPE_STD_WPU
//! - \b GPIO_PIN_TYPE_STD_WPD
//! - \b GPIO_PIN_TYPE_OD
//! - \b GPIO_PIN_TYPE_ANALOG
//! - \b GPIO_PIN_TYPE_WAKE_HIGH
//! - \b GPIO_PIN_TYPE_WAKE_LOW
//!
//! where \b GPIO_PIN_TYPE_STD* specifies a push-pull pin, \b GPIO_PIN_TYPE_OD*
//! specifies an open-drain pin, \b *_WPU specifies a weak pull-up, \b *_WPD
//! specifies a weak pull-down, and \b GPIO_PIN_TYPE_ANALOG specifies an analog
//! input.
//!
//! The \b GPIO_PIN_TYPE_WAKE_* settings specify the pin to be used as a
//! hibernation wake source.  The pin sense level can be high or low.  These
//! settings are only available on some Tiva devices.
//!
//! The pin(s) are specified using a bit-packed byte, where each bit that is
//! set identifies the pin to be accessed, and where bit 0 of the byte
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//!
//! \note A subset of GPIO pins on Tiva devices, notably those used by the
//! JTAG/SWD interface and any pin capable of acting as an NMI input, are
//! locked against inadvertent reconfiguration.  These pins must be unlocked
//! using direct register writes to the relevant GPIO_O_LOCK and GPIO_O_CR
//! registers before this function can be called.  Please see the ``gpio_jtag''
//! example application for the mechanism required and consult your part
//! datasheet for information on affected pins.
//!
//! \return None.
//
//*****************************************************************************
errStat GPIO_PadConfigSet(u32 ui32Port, u8 ui8Pins, u32 ui32Strength, u32 ui32PinType)
{
    u8 ui8Bit;

    //
    // Check the arguments.
    //
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

      //
      // Set the GPIO peripheral configuration register first as required.  This
      // register only appears in TM4E111 and later device classes, but is a
      // harmless write on older devices. Walk pins 0-7 and clear or set the
      // provided PC[EDMn] encoding.
      //
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

      //
      // Set the output drive strength.
      //
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

      //
      // Set the 12-mA drive select register.  This register only appears in
      // TM4E111 and later device classes, but is a harmless write on older
      // devices.
      //
      HWREG(ui32Port + GPIO_O_DR12R) = ((ui32Strength & 0x10) ?
                                        (HWREG(ui32Port + GPIO_O_DR12R) |
                                         ui8Pins) :
                                        (HWREG(ui32Port + GPIO_O_DR12R) &
                                         ~(ui8Pins)));

      //
      // Set the pin type.
      //
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

      //
      // Set the wake pin enable register and the wake level register.  These
      // registers only appear in TM4E111 and later device classes, but are
      // harmless writes on older devices.
      //
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

      //
      // Set the analog mode select register.
      //
      HWREG(ui32Port + GPIO_O_AMSEL) =
          ((ui32PinType == GPIO_PIN_TYPE_ANALOG) ?
           (HWREG(ui32Port + GPIO_O_AMSEL) | ui8Pins) :
           (HWREG(ui32Port + GPIO_O_AMSEL) & ~(ui8Pins)));
     
      return ERR_STAT_OK;
    }
    return ERR_STAT_NOK;
}


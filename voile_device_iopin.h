/**
 * @file voile_device_iopin.h
 * @author JimmyWang
 * @brief Define functions for device IOpin in voile library
 * @version	V0.0.0
 * @date 20231018
 * @par History
 * Version|Auther|Date|Describe
 * ------|----|------|-------- 
 * V0.0.0|JimmyWang|20231018|First update.
 * @defgroup IOpin
 * 
 */
#ifndef __VOILE_DEVICE_IO_H__
#define __VOILE_DEVICE_IO_H__

#include "voile_devicelist.h"
#include <stdint.h>

#define COMBINE3(a, b, c) a##b##c

#ifndef __voile_return
#define __voile_return

/**
 * @enum voileFunctionReturn
 * @brief Return value meaning
 * 
 */
enum voileFunctionReturn{
    success = 0,
    nomalError = -1,
    inputRangeError = -2,
    hardwareUnsupportedError = -3,
};

#endif // !__voile_return


#ifndef __voile_io_enum
#define __voile_io_enum

/**
 * @enum voileIOmode
 * @brief IO mode selectors
 * 
 */
enum voileIOmode{
    IOmodeInput = 0,
    IOmodeQuasiBidirectional = 1,
    IOmodePushPull = 2,
    IOmodeOpenDrain = 3,
};

#endif // !__voile_io_enum


/**
 * @def IOpin_Init(device, enum voileIOmode mode, bool value)
 * @brief Initialise or reinitialise a IO and set IO mode and default output value
 * @ingroup IOpin
 * 
 * @param[in] name :[micro]IOpin device
 * @param[in] mode :[enum voileIOmode]Which mode select to use @ref voileIOmode
 * @param[in] value :[bool]If 0 clear the IO, 1 set it.
 * @return @ref voileFunctionReturn
 *
 * @par Sample
 * @code
 * IOpin_Init(myIO, IOmodeOpenDrain, 1);
 * @endcode
 * 
 * @details 
 * If your hardward unsupport the mode you slect, function will use equivalent mode. \n 
 * If equivalent mode unsupport, function will return hardware-unsupported-error and downgrade to most similar mode. \n
 * For details: \n 
 * Input mode equivalent mode: open-drain and output high, quasi-bidirectional and output high. \n 
 * Quasi-bidirectional equivalent mode: open-drain wtih pullup resistor. \n 
 * Downgrade: open-drain without resistor, input when output high and push-pull when output low, push-pull. \n
 * Open-drain equivalent mode: input when output high and push-pull when output low. \n
 * Downgrade: quasi-bidirectional, push-pull. \n 
 * Push-pull downgrade: quasi-bidirectional, open-drain wtih pullup resistor, open-drain wtihout pullup resistor.
 * 
 */
#define IOpin_Init(device, mode, value) COMBINE3(__, device, _Init)(device##_, mode, value)


/**
 * @def IOpin_Write(device, bool value)
 * @brief Drive a single IO high/low
 * @ingroup IOpin
 * 
 * @param[in] name :[micro]IOpin device
 * @param[in] value :[bool]If 0 clear the IO, 1 set it.
 * @return @ref voileFunctionReturn
 *
 * @par Sample
 * @code
 * IOpin_Write(myIO, IO_RESET);
 * @endcode
 *  
 */
#define IOpin_Write(device, value)  COMBINE3(__, device, _Write)(device##_, value)


/**
 * @def IOpin_Read(device, bool *value)
 * @brief Get state of a single specified IO
 * @ingroup IOpin
 * 
 * @param[in] name :[micro]IOpin device
 * @param[out] value :[bool *]Current state of the GPIO. 0 for low, 1 for high
 * @return @ref voileFunctionReturn
 *
 * @par Sample
 * @code
 * IOpin_Read(myIO, &value);
 * @endcode
 *  
 */
#define IOpin_Read(device, value)  COMBINE3(__, device, _Read)(device##_, value)


/**
 * @def IOpin_ReadToReturn(device)
 * @brief Get state of a single specified IO
 * @ingroup IOpin
 * 
 * @param[in] name :[micro]IOpin device
 * @return [bool]Current state of the GPIO. 0 for low, 1 for high
 *
 * @par Sample
 * @code
 * value = IOpin_ReadToReturn(myIO);
 * @endcode
 *  
 */
#define IOpin_ReadToReturn(device)  COMBINE3(__, device, _ReadToReturn)(device##_)


#endif // !__VOILE_DEVICE_IO_H__

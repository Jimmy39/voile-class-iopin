/**
 * @file voile_class_iopin.h
 * @author JimmyWang
 * @brief Define class ioPin for any single io
 * @version	V0.0.3
 * @date 20231023
 * @par History
 * Version|Auther|Date|Describe
 * ------|----|------|--------
 * V0.0.3|JimmyWang|20231023|[backward incompatible]Use struct instead micro.Add toggle function.
 * V0.0.2|JimmyWang|20231020|[backward incompatible]Chang rule of macro function
 * V0.0.1|JimmyWang|20231019|Add io mode input pull up or down
 * V0.0.0|JimmyWang|20231018|First update.
 * 
 */
#ifndef __VOILE_CLASS_IO_H__
#define __VOILE_CLASS_IO_H__

#include "voile_common.h"


#ifndef __voile_io_enum
#define __voile_io_enum

/**
 * @enum voileIOmode
 * @brief IO mode selectors
 * 
 */
enum voileIOmode{
    IOmodeInput = 0,
    IOmodeInputWithPullUpResistor = 1,
    IOmodeInputWithPullDownResistor = 2,
    IOmodeQuasiBidirectional = 3,
    IOmodePushPull = 4,
    IOmodeOpenDrain = 5,
};

#endif // !__voile_io_enum


typedef const uint8_t voile_ioPin_pin_t;


/**
 * @brief Functions of ioPin
 * 
 */
struct voile_ioPin_Func_t
{

    /**
     * @brief Initialise or reinitialise a IO, set io mode and default output value
     * 
     * @param[in] name :[struct voile_ioPin *]ioPin object
     * @param[in] mode :[enum voileIOmode]Which mode select to use @ref voileIOmode
     * @param[in] value :(option)[bool]If 0 clear the IO, 1 set it. Input mode will ignore this param.
     * @return voileFunctionReturn
     *
     * @par Sample
     * @code
     * led.Func->Init(&myIo, IOmodePushPull, 0);
     * led.Func->Init(&myIo_2, IOmodeInputWithPullUpResistor);
     * @endcode
     * 
     * @details 
     * If your hardward unsupport the mode you slect, function will return hardware-unsupported-error and downgrade to most similar mode. \n
     * For details: \n 
     * - The input mode with pull up or down resistor will downgrade to input with nothing. \n 
     * - The quasi-bidirectional mode: will downgrade to open-drain then push-pull. \n
     * - The open-drain mode will downgrade to quasi-bidirectional then push-pull. \n 
     * - The push-pull mode will downgrade to quasi-bidirectional then open-drain. \n 
     * 
     * 
     */
    enum voileFunctionReturn const (*Init)(void *, enum voileIOmode, ...);
    
    /**
     * @brief Drive a single io high/low
     * 
     * @param[in] name :[struct voile_ioPin *]ioPin object
     * @param[in] value :[bool]If 0 clear the IO, 1 set it.
     * @return voileFunctionReturn
     *
     * @par Sample
     * @code
     * myIo.Func->Write(&led, 0);
     * @endcode
     *  
     */
    enum voileFunctionReturn const (*Write)(void *, bool);

    /**
     * @brief Get state of a single io
     * 
     * @param[in] name :[struct voile_ioPin *]ioPin object
     * @param[out] value :[bool *]Current state of the GPIO. 0 for low, 1 for high
     * @return voileFunctionReturn
     *
     * @par Sample
     * @code
     * bool i;
     * led.Func->Read(&myIo, &i);
     * @endcode
     *  
     */
    enum voileFunctionReturn const (*Read)(void *, bool *);

    /**
     * @brief Get state of a single io
     * 
     * @param[in] name :[struct voile_ioPin *]ioPin object
     * @return [bool]Current state of the GPIO. 0 for low, 1 for high
     *
     * @par Sample
     * @code
     * led.Func->ReadToReturn(&myIo);
     * @endcode
     *  
     */
    bool const (*ReadToReturn)(void *);
    
    /**
     * @brief Toggle a single io
     * 
     * @param[in] name :[struct voile_ioPin *]ioPin object
     * @return voileFunctionReturn
     *
     * @par Sample
     * @code
     * led.Func->Toggle(&myIo);
     * @endcode
     *  
     */
    enum voileFunctionReturn const (*Toggle)(void *);
};


/**
 * @brief Single io
 * 
 */
struct voile_ioPin
{
    voile_ioPin_pin_t pin;                  ///< to identify pins
    const struct voile_ioPin_Func_t *Func;  ///< functions of ioPin
};


/**
 * @brief Declaer ioPin object
 * @details
 * Any hardware operation library used ioPin class 
 * need a micro function names DECLAER_OBJECT_ioPin_'library name'(object) 
 * to declaer object
 * 
 */
#define DECLAER_OBJECT_ioPin(object) COMBINE(DECLAER_OBJECT_ioPin_, object##_lib)(object)


/**
 * @brief Define ioPin object
 * @details
 * Any hardware operation library used ioPin class 
 * need a micro function names DECLAER_OBJECT_ioPin_'library name'(object) 
 * to define object
 * 
 */
#define DEFINE_OBJECT_ioPin(object) COMBINE(DEFINE_OBJECT_ioPin_, object##_lib)(object)

#endif // !__VOILE_CLASS_IO_H__

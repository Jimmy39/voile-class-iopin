/**
 * @file voile_interface_iopin.h
 * @author JimmyWang
 * @brief Define class ioPin for any single io
 * 
 */
#ifndef __VOILE_INTERFACE_IOPIN_H__
#define __VOILE_INTERFACE_IOPIN_H__

#include "voile_common.h"


#ifndef __voile_io_enum
#define __voile_io_enum

/**
 * @brief IO mode selectors
 * 
 */
typedef enum {
    IOmodeInput = 0,
    IOmodeInputWithPullUpResistor = 1,
    IOmodeInputWithPullDownResistor = 2,
    IOmodeQuasiBidirectional = 3,
    IOmodePushPull = 4,
    IOmodeOpenDrain = 5,
} voile_io_mode_t;

#endif // !__voile_io_enum

/**
 * @brief Operate the pin
 * 
 */
typedef const struct {

    /**
     * @brief Initialise or reinitialise a IO, set io mode and default output value
     * 
     * @param[in] this :[voile_const_ioPin_t *]This ioPin object.
     * @param[in] mode :[voileIOmode_t]Which mode select to use @ref voileIOmode_t
     * @param[in] value :[bool](option when input mode)If 0 clear the IO, 1 set it. Input mode will ignore this param.
     * @return [voile_status_t]The status of function.
     *
     * @par Sample
     * @code {.C}
     * myIo.Operate->Init(&myIo, IOmodePushPull, 0);
     * myIo2.Operate->Init(&myIo_2, IOmodeInputWithPullUpResistor);
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
     */
    voile_status_t (*Init)(void *, enum voileIOmode, ...);
    
    /**
     * @brief Drive a single io high/low
     * 
     * @param[in] this :[voile_const_ioPin_t *]This ioPin object.
     * @param[in] value :[bool]If 0 clear the IO, 1 set it.
     * @return [voile_status_t]The status of function.
     *
     * @par Sample
     * @code {.C}
     * myIo.Operate->Write(&myIo, 0);
     * @endcode
     *  
     */
    voile_status_t (*Write)(void *, bool);

    /**
     * @brief Get state of a single io
     * 
     * @param[in] this :[voile_const_ioPin_t *]This ioPin object.
     * @param[out] value :[bool *]Current state of the GPIO. 0 for low, 1 for high.
     * @return [voile_status_t]The status of function.
     *
     * @par Sample
     * @code {.C}
     * bool i;
     * myIo.Operate->Read(&myIo, &i);
     * @endcode
     *  
     */
    voile_status_t (*Read)(void *, bool *);
    
    /**
     * @brief Toggle a single io
     * 
     * @param[in] this :[voile_const_ioPin_t *]This ioPin object.
     * @return [voile_status_t]The status of function.
     *
     * @par Sample
     * @code {.C}
     * myIo.Operate->Toggle(&myIo);
     * @endcode
     *  
     */
    voile_status_t (*Toggle)(void *);

} voile_const_ioPin_Operate_t;


/**
 * @brief Get something from io
 * 
 */
typedef struct {

    /**
     * @brief Get state of a single io
     * 
     * @param[in] this :[voile_const_ioPin_t *]This ioPin object.
     * @return [bool]Current state of the GPIO. 0 for low, 1 for high.
     *
     * @par Sample
     * @code {.C}
     * myIo.Get->Read(&myIo);
     * @endcode
     *  
     */
    bool (*Read)(void *);

} voile_const_ioPin_Get_t;


/**
 * @brief Single io
 * 
 */
typedef const struct {

    // Operate ioPin
    voile_const_ioPin_Operate_t *Operate;
    // Get something from io
    voile_const_ioPin_Get_t *Get;

} voile_const_ioPin_t;


#endif // !__VOILE_INTERFACE_IOPIN_H__

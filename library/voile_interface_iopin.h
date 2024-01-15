/**
 * @file voile_interface_iopin.h
 * @author JimmyWang
 * @brief Define class ioPin for any single io
 * @version alpha-240114
 * 
 */
#ifndef __VOILE_INTERFACE_IOPIN_H__
#define __VOILE_INTERFACE_IOPIN_H__

#include "voile_common.h"


#ifndef __voile_io_enum
#define __voile_io_enum

struct voile_ioPin_Operate_struct;
typedef const struct voile_ioPin_Operate_struct voile_const_ioPin_Operate_t;
struct voile_ioPin_Get_struct;
typedef const struct voile_ioPin_Get_struct voile_const_ioPin_Get_t;

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


/**
 * @brief IO mode selectors
 * 
 */
typedef enum {
    IOuninit = 0,
    IOmodeInput = 1,
    IOmodeInputWithPullUpResistor = 2,
    IOmodeInputWithPullDownResistor = 3,
    IOmodeQuasiBidirectional = 4,
    IOmodePushPull = 5,
    IOmodeOpenDrain = 6,
    IOmodeError = 7,
} voile_io_mode_t;

#endif // !__voile_io_enum

/**
 * @brief Operate the pin
 * 
 */
struct voile_ioPin_Operate_struct {

    /**
     * @brief Initialise or reinitialise a IO, and enable it
     * 
     * @param[in] this :[voile_const_ioPin_t *] This ioPin object.
     * @return [voile_status_t] The status of function.
     *
     * @par Sample
     * @code {.C}
     * myIo.Operate->Init(&myIo);
     * @endcode
     * 
     * @note 
     * - You should set mode and write value for output befor init. \n
     * - In some hardware that does not support atomic operations, this function may initialize and enable the entire port.
     * 
     */
    voile_status_t (*Init)(voile_const_ioPin_t *);

    /**
     * @brief Set mode for sigle io
     * 
     * @param[in] this :[voile_const_ioPin_t *] This ioPin object.
     * @param[in] mode :[voile_io_mode_t] Which mode select to use.
     * @return [voile_status_t] The status of function.
     *
     * @par Sample
     * @code {.C}
     * myIo.Operate->SetMode(&myIo, IOmodePushPull);
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
    voile_status_t (*SetMode)(voile_const_ioPin_t *, voile_io_mode_t);
    
    /**
     * @brief Drive a single io high/low
     * 
     * @param[in] this :[voile_const_ioPin_t *] This ioPin object.
     * @param[in] value :[bool] If 0 clear the IO, 1 set it.
     * @return [voile_status_t] The status of function.
     *
     * @par Sample
     * @code {.C}
     * myIo.Operate->Write(&myIo, 0);
     * @endcode
     *  
     */
    voile_status_t (*Write)(voile_const_ioPin_t *, bool);

    /**
     * @brief Get state of a single io input
     * 
     * @param[in] this :[voile_const_ioPin_t *] This ioPin object.
     * @param[out] value :[bool *] Current state of the GPIO input. 0 for low, 1 for high.
     * @return [voile_status_t] The status of function.
     *
     * @par Sample
     * @code {.C}
     * bool i;
     * myIo.Operate->Read(&myIo, &i);
     * @endcode
     *  
     */
    voile_status_t (*Read)(voile_const_ioPin_t *, bool *);
    
    /**
     * @brief Toggle a single io
     * 
     * @param[in] this :[voile_const_ioPin_t *] This ioPin object.
     * @return [voile_status_t] The status of function.
     *
     * @par Sample
     * @code {.C}
     * myIo.Operate->Toggle(&myIo);
     * @endcode
     *  
     */
    voile_status_t (*Toggle)(voile_const_ioPin_t *);

    /**
     * @brief Get state of a single io output
     * 
     * @param[in] this :[voile_const_ioPin_t *] This ioPin object.
     * @param[out] value :[bool *] Current state of the GPIO output. 0 for low, 1 for high.
     * @return [voile_status_t] The status of function.
     *
     * @par Sample
     * @code {.C}
     * bool i;
     * myIo.Operate->ReadRegister(&myIo, &i);
     * @endcode
     *  
     */
    voile_status_t (*ReadRegister)(voile_const_ioPin_t *, bool *);

};


/**
 * @brief Get something from io
 * 
 */
struct voile_ioPin_Get_struct {

    /**
     * @brief Get mode of a single
     * 
     * @param[in] this :[voile_const_ioPin_t *] This ioPin object.
     * @return [voile_io_mode_t] The mode of the single io.
     *
     * @par Sample
     * @code {.C}
     * if (myIo.Get->Mode(&myIo) == IOuninit) {
     *  ;
     * }
     * @endcode
     *  
     */
    bool (*Mode)(voile_const_ioPin_t *);

    /**
     * @brief Get state of a single io input
     * 
     * @param[in] this :[voile_const_ioPin_t *] This ioPin object.
     * @return [bool] Current state of the GPIO input. 0 for low, 1 for high.
     *
     * @par Sample
     * @code {.C}
     * bool i = myIo.Get->Read(&myIo);
     * @endcode
     *  
     */
    bool (*Read)(voile_const_ioPin_t *);

    /**
     * @brief Get state of a single io output
     * 
     * @param[in] this :[voile_const_ioPin_t *] This ioPin object.
     * @param[out] value :[bool *] Current state of the GPIO output. 0 for low, 1 for high.
     * @return [voile_status_t] The status of function.
     *
     * @par Sample
     * @code {.C}
     * bool i = myIo.Get->ReadRegister(&myIo);
     * @endcode
     *  
     */
    bool (*ReadRegister)(voile_const_ioPin_t *);

};



#endif // !__VOILE_INTERFACE_IOPIN_H__

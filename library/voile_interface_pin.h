/*!
  @file voile_interface_pin.h
  @brief Define interface of pin for any single io
  @details

  To use, copy voile_interface_pin.h and depends libries, creat voile_conf.h for defining micro. Then include voile_interface_pin.h.

  @depends
  [voile-common](https://github.com/Jimmy39/voile-common)
  @author Jimmy Wang
  @version alpha-240227
  @todo Edit comment and add sample

  @license MIT License

  Copyright (c) 2024 Jimmy Wang

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
 */

#ifndef __VOILE_INTERFACE_PIN_H__
#define __VOILE_INTERFACE_PIN_H__

#include "voile_common.h"

#ifdef __VOILE_PIN_CONF
#include "voile_pin_conf.h"
#endif

#ifndef __voile_io_enum__
#define __voile_io_enum__

/**
 * @brief IO mode selectors
 *
 *
 */
typedef enum {

    IOuninit = 0,

    /// As return value: The I/O is input mode, and both pull-up and pull-down resistors are disabled. \n
    /// As input parameter: Set the I/O mode to input and disable pull-up and pull-down resistors.
    IOmodeInput,

    /// As return value: The I/O is input mode, pull-up resistor is enabled and pull-down resistor is disabled. \n
    /// As input parameter: Set the I/O mode to input, enable pull-up resistor and disable pull-down resistor.
    IOmodeInputWithPullUpResistor,

    /// As return value: The I/O is input mode, pull-down resistor is enabled and pull-up resistor is disabled. \n
    /// As input parameter: Set the I/O mode to input, enable pull-down resistor
    /// and disable pull-up resistor.
    IOmodeInputWithPullDownResistor,


    /// As return value: The I/O is quasi-bidirectional mode. \n
    /// As input parameter: Set the I/O mode to quasi-bidirectional mode.
    IOmodeQuasiBidirectional,

    /// As return value: The I/O is push-pull mode. \n
    /// As input parameter: Set the I/O mode to push-pull mode.
    IOmodePushPull,

    /// As return value: The I/O is open drain mode. \n
    /// As input parameter: Set the I/O mode to open drain mode.
    IOmodeOpenDrain,

    ///  As input value: Do nothing
    IOmodeHold,

    /// io_mode number should less than IOmodeError.
    IOmodeError

} voile_io_mode_t;

#endif  // !__voile_io_enum__

/**
 @brief Single io
 */
typedef const struct voile_pin_interface_struct *voile_const_pin_t;

struct voile_pin_interface_struct {

    void (*init)(voile_const_pin_t *);

    voile_io_mode_t (*setMode)(voile_const_pin_t *, voile_io_mode_t);

    void (*write)(voile_const_pin_t *, bool);

    bool (*read)(voile_const_pin_t *);

    void (*toggle)(voile_const_pin_t *);

    bool (*readRegister)(voile_const_pin_t *);
};

#ifndef __UNSUPPORT_INLINE

/**
 * @brief Initialise or reinitialise a IO, and enable it
 *
 * @param[in] pin_p :[voile_const_pin_t *] The pointer of pin_p object.
 *
 * @sample
 * @code {.C}
 *
 * pin_init(&myIo);
 * @endcode
 *
 * @details
 * @par Details
 * Initialise or reinitialise a IO, and enable it. \n
 * If there is a configuration error in the devicelist.h, a error will be returned via ```voile_errorno``` \n
 * - ```hardwareUnsupportedError``` means that you are using a feature not supported by the hardware. For example, if you are initializing an I/O expansion chip but using pins that are only in input mode to drive the I/O expansion chip, this error would be triggered. \n
 * - ```configError``` means that there are invalid parameters in the configuration of devicelist.h. \n
 *
 * @note You should set mode and write value for output befor init.
 * @note In some hardware that does not support atomic operations, this function may initialize and enable the entire port.
 *
 *
 */
static inline void pin_init(voile_const_pin_t *pin_p) {
    (*pin_p)->init(pin_p);
}

/**
 * @brief Set mode for sigle io
 *
 * @param[in] this :[voile_const_pin_t *] This pin object.
 * @param[in] mode :[voile_io_mode_t] Which mode select to use.
 *
 * @details
 * | Value | As input | As output |
 * | --- | --- | --- |
 * | IOuninit | *Behavior is undefined.* If this I/O can be independently
 * initialized and deinitialized, it will be deinitialized. | The I/O is
 * uninitialized. | If your hardward unsupport the mode you slect, function will
 * return hardware-unsupported-error and downgrade to most similar mode. \n
 * For details: \n
 * - The input mode with pull-up or pull-down resistor will downgrade to input
 * with nothing. \n
 * - The quasi-bidirectional mode: will downgrade to open-drain then push-pull.
 * \n
 * - The open-drain mode will downgrade to quasi-bidirectional then push-pull.
 * \n
 * - The push-pull mode will downgrade to quasi-bidirectional then open-drain.
 * \n
 *
 */
static inline voile_io_mode_t pin_setMode(
    voile_const_pin_t *pin_p, voile_io_mode_t mode) {

    return ((*pin_p)->setMode(pin_p, mode));
}

/**
   * @brief Drive a single io high/low
   *
   * @param[in] this :[voile_const_pin_t *] This pin object.
   * @param[in] value :[bool] If 0 clear the IO, 1 set it.
   *
   *
   */
static inline void pin_write(voile_const_pin_t *pin_p, bool value) {
    (*pin_p)->write(pin_p, value);
}

/**
   * @brief Get state of a single io input
   *
   * @param[in] this :[voile_const_pin_t *] This pin object.
   * @return [bool *] Current state of the GPIO input. 0 for low, 1 for high.

   *
   */
static inline bool pin_read(voile_const_pin_t *pin_p) {
    return ((*pin_p)->read(pin_p));
}

/**
   * @brief Toggle a single io
   *
   * @param[in] this :[voile_const_pin_t *] This pin object.

   *
   */
static inline void pin_toggle(voile_const_pin_t *pin_p) {
    (*pin_p)->toggle(pin_p);
}

/**
   * @brief Get state of a single io output
   *
   * @param[in] this :[voile_const_pin_t *] This pin object.
   * @return value :[bool *] Current state of the GPIO output. 0 for low, 1
   * for high.

   *
   */
static inline bool pin_readRegister(voile_const_pin_t *pin_p) {
    return ((*pin_p)->readRegister(pin_p));
}

/**
   * @brief Get mode of a single
   *
   * @param[in] this :[voile_const_pin_t *] This pin object.
   * @return [voile_io_mode_t] The mode of the single io.

   */
static inline voile_io_mode_t pin_getMode(voile_const_pin_t *pin_p) {
    return ((*pin_p)->setMode(pin_p, IOmodeHold));
}

#endif  // !__UNSUPPORT_INLINE


#endif  // !__VOILE_INTERFACE_pin_H__

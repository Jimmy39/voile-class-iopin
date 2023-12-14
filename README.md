# voile-interface-iopin
Define public interface of struct ioPin in voile library for any single io

IOpin can be uesd for GPIO, IO expansion chip and even 74595 or 74164.

```C
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
```

## Define
This struct only have pulic interface.**Do not use it define anything.**

These libraries are used for definition:

[voile-iopin-rp2040](https://github.com/Jimmy39/voile-iopin-rp2040): For MCU RP2040

For more information, see [voile-library](https://github.com/Jimmy39/voile-library)

## Declare
Declare struct ```voile_const_ioPin_xxx_t``` as this struct in _devicelist.h_

```C
extern voile_const_ioPin_t myIo;
```

## Use

There is a docs created by doxygen.

[https://jimmy39.github.io/voile-interface-iopin/index.html](https://jimmy39.github.io/voile-interface-iopin/index.html)

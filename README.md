# voile-internal-iopin
Define class ioPin in voile library for any single io

```C
/**
 * @brief Single io
 * 
 */
typedef const{
    voile_ioPinOperations_t *Operations;   ///< Operations for ioPin
} voile_ioPin_t;
```

IOpin can be uesd for GPIO, IO expansion chip and even 74595 or 74164.

There is a docs created by doxygen.https://jimmy39.github.io/voile-class-iopin/index.html

For more information of voile library, see [voile-library](https://github.com/Jimmy39/voile-library)

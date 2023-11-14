# voile-class-iopin
Define class ioPin for any single io

```C
/**
 * @brief Single io
 * 
 */
struct voile_ioPin_t{
    const struct voile_ioPinOperations_t *Operations;   ///< Operations of ioPin
};
```

IOpin can be uesd for GPIO, IO expansion chip and even 74595 or 74164.

There is a docs created by doxygen.https://jimmy39.github.io/voile-class-iopin/index.html

For more information of voile library, see [voile-library](https://github.com/Jimmy39/voile-library)

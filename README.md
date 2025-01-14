# Fortune's Palette Compression

This library provides a **fast palette compression implementation** for C++ in a single, header-only file. Simply drag and drop the `palette.hpp` file located in the `src` folder into your project, and you're good to go!

You can see how to use the library in action in the `src/main.cpp` file.

---

## Features
- **Header-only**: No additional dependencies; just include the file.
- **Fast compression**: Compresses flat vectors efficiently with same-size dimensions.
- **Simple API**: Minimalistic and easy-to-understand interface.

---

## Minimal Usage Example

Here's a quick example demonstrating how to use the library:

```cpp
#include "palette.hpp"
#include <iostream>

using namespace Fort;

void main()
{
    // Create a PaletteCompression instance, passing in the diameter of our vector
    const int vectorDiameter = 64;
    PaletteCompression paletteCompression(vectorDiameter);

    // Create a vector of size vectorDiameter^3, set a random location to a value
    std::vector<uint16_t> uncompressedVector(vectorDiameter * vectorDiameter * vectorDiameter, 0);
    const int x = 3, y = 7, z = 10;
    uncompressedVector[y + (x * vectorDiameter) + (z * vectorDiameter * vectorDiameter)] = 25; 

    // Now palette compress our uncompressed vector
    paletteCompression.PaletteCompressVector(uncompressedVector);

    // Modify a value in the still compressed vector to 4
    const int x2 = 12, y2 = 25, z2 = 54;
    paletteCompression.SetNum(x2, y2, z2, 4);

    // Let's uncompress our palette compressed vector
    uncompressedVector.clear();
    paletteCompression.DecompressVector(uncompressedVector);

    // Print out results
    std::cout << uncompressedVector[y +  (x * vectorDiameter) +  (z * vectorDiameter * vectorDiameter)];  // 25
    std::cout << uncompressedVector[y2 + (x2 * vectorDiameter) + (z2 * vectorDiameter * vectorDiameter)]; // 4
    // 25
    // 4
}
```

## Current Limitations
- The library currently only supports flat vectors with same-size dimensions.
- The library only works in c++. Rust port soon!
- Future versions might address this and other limitations — **pull requests are welcome!**

---

## Usage Tips
- You can change the return type and the type the library decompresses to by changing RETURN_TYPE at the top of the FORT namespace in palette.hpp

---

# Fortune's Palette Compression

This library provides a **fast palette compression implementation** for C++ in a single, header-only file. Simply drag and drop the `palette.hpp` file into your project, and you're good to go!

You can see how to use the library in action in the `main.cpp` file.

---

## Features
- **Header-only**: No additional dependencies; just include the file.
- **Fast compression**: Compresses flat vectors efficiently with same-size dimensions.
- **Simple API**: Minimalistic and easy-to-understand interface.

---

## Current Limitations
- The library currently only supports flat vectors with same-size dimensions.
- Future versions might address this limitation — **pull requests are welcome!**

---

## Minimal Usage Example

Here's a quick example demonstrating how to use the library:

```cpp
#include "palette.hpp"
#include <iostream>

void main() {
    // Create a PaletteCompression instance, passing in the diameter of our vector
    const int vectorDiameter = 64;
    PaletteCompression paletteCompression(vectorDiameter);

    // Create a vector, set a random location to a value
    std::vector<uint16_t> uncompressedVector(VECTOR_VOLUME, 0);
    const int x = 3, y = 7, z = 10;
    uncompressedVector[y + (x * vectorDiameter) + (z * vectorDiameter * vectorDiameter)] = 25; 

    // Now palette compress our vector, passing in our uncompressed vector
    paletteCompression.PaletteCompressVector(uncompressedVector);

    // Modify a value in the still compressed vector to 4
    const int x2 = 3, y2 = 7, z2 = 10;
    paletteCompression.SetNum(x2, y2, z2, 4);

    // Let's uncompress our palette compressed vector
    uncompressedVector.clear();
    paletteCompression.DecompressVector(uncompressedVector);

    // Print out results
    std::cout << uncompressedVector[y +  (x * vectorDiameter) +  (z * vectorDiameter * vectorDiameter)];  // 25
    std::cout << uncompressedVector[y2 + (x2 * vectorDiameter) + (z2 * vectorDiameter * vectorDiameter)]; // 4
}

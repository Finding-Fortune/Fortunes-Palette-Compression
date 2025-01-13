#include "palette.hpp"

// STL libs used in this example
#include <iostream>
#include <vector>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For seeding srand()

// Namespace for palette compression library
using namespace Fort;

// Constants
#define VECTOR_DIAMETER 64
#define VECTOR_AREA     VECTOR_DIAMETER * VECTOR_DIAMETER
#define VECTOR_VOLUME   VECTOR_DIAMETER * VECTOR_DIAMETER * VECTOR_DIAMETER

// Functions used in this example
void SetNum(std::vector<uint16_t>& uncompressedVector, const uint8_t x, const uint8_t y, const uint8_t z, const uint16_t NewNum);
uint16_t GetNum(std::vector<uint16_t>& uncompressedVector, const uint8_t x, const uint8_t y, const uint8_t z);



int main()
{
    // In this file, we will test the palette compression defined in palette.hpp

    // Create a PaletteCompression instance, passing in the diameter of our vector
    PaletteCompression paletteCompression(VECTOR_DIAMETER);

    // Create a vector with random numbers 0-5 that is 64^3 big (262144 total elements)
    std::vector<uint16_t> uncompressedVector(VECTOR_VOLUME, 0);

    // Seed the random number generator
    std::srand(std::time(nullptr));

    // Fill the vector with random numbers between 0 and 5
    for (int x = 0; x < VECTOR_DIAMETER; ++x)
    for (int y = 0; y < VECTOR_DIAMETER; ++y)
    for (int z = 0; z < VECTOR_DIAMETER; ++z) 
    {
        SetNum(uncompressedVector, x, y, z, std::rand() % 6);
    }

    // Set 3 numbers manually just to double check they are correct
    SetNum(uncompressedVector,  1,  1,  1, 1);
    SetNum(uncompressedVector, 23, 43, 12, 2);
    SetNum(uncompressedVector, 63, 63, 63, 3);

    // Print out the results
    std::cout << "Values in the uncompressed vector at random locations:" << std::endl;
    std::cout << "Uncompressed Vector Location ( 1,  1,  1) value: " << GetNum(uncompressedVector,  1,  1,  1) << std::endl;
    std::cout << "Uncompressed Vector Location (23, 43, 12) value: " << GetNum(uncompressedVector, 23, 43, 12) << std::endl;
    std::cout << "Uncompressed Vector Location (63, 63, 63) value: " << GetNum(uncompressedVector, 63, 63, 63) << std::endl;
    std::cout << std::endl;

    // Now palette compress our vector, passing in our vector's diameter
    paletteCompression.PaletteCompressVector(uncompressedVector);

    // Lets check those same values but get them from our palette compressed vector
    std::cout << "Values in the compressed vector at the same random locations:" << std::endl;
    std::cout << "Compressed Vector Location ( 1,  1,  1) value: " << paletteCompression.GetNum( 1,  1,  1) << std::endl;
    std::cout << "Compressed Vector Location (23, 43, 12) value: " << paletteCompression.GetNum(23, 43, 12) << std::endl;
    std::cout << "Compressed Vector Location (63, 63, 63) value: " << paletteCompression.GetNum(63, 63, 63) << std::endl;
    std::cout << std::endl;

    // Lets also try modifying one of the values in the palette compressed vector, setting it to the value 4. 
    // This has to be an existing value in the vector, or else the entire vector has to be 
    // decompressed and recompressed
    paletteCompression.SetNum(23, 43, 12, 4);
    std::cout << "Compressed Vector Modified Value at Location (23, 43, 12) value: " << paletteCompression.GetNum(23, 43, 12) << std::endl;
    std::cout << std::endl;

    // Finally, lets clear our uncompressed vector. Then we will decompress our palette compressed vector,
    // returning results into the uncompressedVector once again so it should match
    uncompressedVector.clear();
    paletteCompression.DecompressVector(uncompressedVector);

    // Lets test the results one last time on the decompressed vector!
    std::cout << "Values in the now decompressed vector at the same random locations:" << std::endl;
    std::cout << "Decompressed Vector Location ( 1,  1,  1) value: " << GetNum(uncompressedVector,  1,  1,  1) << std::endl;
    std::cout << "Decompressed Vector Location (23, 43, 12) value: " << GetNum(uncompressedVector, 23, 43, 12) << std::endl;
    std::cout << "Decompressed Vector Location (63, 63, 63) value: " << GetNum(uncompressedVector, 63, 63, 63) << std::endl;
    std::cout << std::endl;

    return 0;
}



void SetNum(std::vector<uint16_t>& uncompressedVector, const uint8_t x, const uint8_t y, const uint8_t z, const uint16_t NewNum)
{
    uncompressedVector[y + (x * VECTOR_DIAMETER) + (z * VECTOR_AREA)] = NewNum; 
}

uint16_t GetNum(std::vector<uint16_t>& uncompressedVector, const uint8_t x, const uint8_t y, const uint8_t z)
{
    return uncompressedVector[y + (x * VECTOR_DIAMETER) + (z * VECTOR_AREA)]; 
}
#ifndef PALETTE_HPP
#define PALETTE_HPP

#include <iostream>
#include <vector>
#include <map>
#include <set>



namespace Fort
{

struct PaletteCompressedBlocks
{
    // If there is only 1 unique block type ID in the entire chunk, it will just be set to this
    int16_t SingleBlockTypeID = -1;
    // Palette compressed blocks of the current chunk
    std::vector<uint64_t> compressedBlocks;
    // Each index in PaletteToBlockID maps a bit compressed block to an actual block ID.
    // I.E. if index 0 is equal to the block ID for grass, then if a compressed bit section in compressedBlocks
    // is equal to 0, it is a grass block.
    std::vector<uint16_t> PaletteToBlockID;
    // And reverse. Given a BlockID, determine what its ID is bit compressed
    std::map<uint16_t, unsigned int> BlockToPalette;
};


class PaletteCompression
{
private:
    PaletteCompressedBlocks blocks;
    const int vectorDiameter;
    const int vectorArea;
    const int vectorVolume;

public:
    PaletteCompression(const int VectorDiameter) : 
    vectorDiameter(VectorDiameter), 
    vectorArea(VectorDiameter * VectorDiameter), 
    vectorVolume(VectorDiameter * VectorDiameter * VectorDiameter)
    {
        std::cout << "Palette instance created.\n";
    }

    void PaletteCompressVector(std::vector<uint16_t>& uncompressedBlocks)
    {
        blocks.compressedBlocks.clear();
        blocks.PaletteToBlockID.clear();
        blocks.BlockToPalette.clear();

        if(blocks.SingleBlockTypeID != -1)
        { 
            std::cout << "Error: Blocks SingleBlockTypeID is not -1" << std::endl;
            return;
        }

        auto& blockToPaletteRef = blocks.BlockToPalette;
        auto& compressedBlocksRef = blocks.compressedBlocks;

        // Get the unique block IDs in chunk
        std::set<uint16_t> uniqueBlocks;
        for (const uint8_t block : uncompressedBlocks) 
        {
            uniqueBlocks.insert(block);
        }

        if(uniqueBlocks.size() == 1) blocks.SingleBlockTypeID = *uniqueBlocks.begin();
        else if(uniqueBlocks.size() == 0)
        {
            std::cout << "Error! Nothing is inside of the vector to palette compress!\n";
            return;
        }

        // Build palette from our set of unique block IDs in chunk
        for(const auto block : uniqueBlocks)
        {   
            blocks.PaletteToBlockID.push_back(block);
            blockToPaletteRef[block] = blockToPaletteRef.size();
        }

        /* Perform bit compression now that palette is created */

        // Size of our palette
        const unsigned int paletteSize = uniqueBlocks.size();
        // Given the size of our palette, how many bits is a single block now that it is palette compressed?
        const unsigned int bitBlockSize = (paletteSize <= 1 ? 1 : static_cast<unsigned int>(std::ceil(std::log2(paletteSize))));
        // How many total palette compressed blocks can fit into a single one of our 64 bit integers when we compress them?
        const unsigned int blocksPerInt = std::floor(64.0f / static_cast<float>(bitBlockSize));

        uint64_t currentPackedBlock = 0;
        unsigned int currentBit = 0;
        unsigned int blocksPerIntCount = 0;

        compressedBlocksRef.reserve((uncompressedBlocks.size() + blocksPerInt - 1) / blocksPerInt);

        // Actually loop through and do the compression now
        for (const uint16_t block : uncompressedBlocks) 
        {
            if (blocksPerIntCount == blocksPerInt) 
            {
                compressedBlocksRef.push_back(currentPackedBlock);
                currentPackedBlock = 0;
                currentBit = 0;
                blocksPerIntCount = 0;
            }

            const uint64_t packedBlock = static_cast<uint64_t>(blockToPaletteRef[block]) << currentBit;
            currentPackedBlock |= packedBlock;

            currentBit += bitBlockSize;
            blocksPerIntCount++;
        }

        // Handle the last packed block if it's not empty
        if (currentBit > 0) 
        {
            compressedBlocksRef.push_back(currentPackedBlock);
        }
    } // End 



    void DecompressVector(std::vector<uint16_t>& uncompressedBlocks)
    {
        const unsigned int maxChunkSize = vectorVolume;

        const unsigned int paletteSize = blocks.PaletteToBlockID.size(); // Ensure this represents the number of unique block types
        const unsigned int bitBlockSize = (paletteSize <= 1 ? 1 : static_cast<unsigned int>(std::ceil(std::log2(paletteSize))));

        const uint64_t mask = (1ULL << bitBlockSize) - 1; 
        const unsigned int blocksPerInt = std::floor(64.0f / static_cast<float>(bitBlockSize));

        for (const uint64_t packedBlock : blocks.compressedBlocks) 
        for (unsigned int i = 0; i < blocksPerInt; i++) 
        {
            const uint64_t blockData = (packedBlock >> (i * bitBlockSize)) & mask;

            if(uncompressedBlocks.size() < maxChunkSize) // If we don't go over our block limit 
                uncompressedBlocks.push_back(static_cast<uint8_t>(blocks.PaletteToBlockID[blockData]));
        }
    } // End DecompressVector



    uint16_t GetNum(const uint8_t x, const uint8_t y, const uint8_t z) const noexcept
    {
        if(blocks.SingleBlockTypeID != -1) return blocks.SingleBlockTypeID;
        else 
        {
            const unsigned int index = y + (x * vectorDiameter) + (z * vectorArea);
            const unsigned int paletteSize = blocks.PaletteToBlockID.size(); // Ensure this represents the number of unique block types
            const unsigned int bitBlockSize = (paletteSize <= 1 ? 1 : static_cast<unsigned int>(std::ceil(std::log2(paletteSize))));
            const unsigned int blocksPerInt = std::floor(64.0f / static_cast<float>(bitBlockSize));

            const unsigned int intIndex = index / blocksPerInt;
            const unsigned int bitOffset = (index % blocksPerInt) * bitBlockSize;

            if (intIndex < blocks.compressedBlocks.size()) 
            {
                const uint64_t mask = (1ULL << bitBlockSize) - 1;
                const uint64_t blockData = (blocks.compressedBlocks[intIndex] >> bitOffset) & mask;
                return static_cast<uint8_t>(blocks.PaletteToBlockID[blockData]);
            }

            return 0; // Return a default or error value if index is out of bounds
        }
    }

    void SetNum(const uint8_t x, const uint8_t y, const uint8_t z, const uint16_t newNum)
    {
        const unsigned int index = y + (x * vectorDiameter) + (z * vectorArea);
        const unsigned int paletteSize = blocks.PaletteToBlockID.size(); // Ensure this represents the number of unique block types
        const unsigned int bitBlockSize = (paletteSize <= 1 ? 1 : static_cast<unsigned int>(std::ceil(std::log2(paletteSize))));
        const unsigned int blocksPerInt = std::floor(64.0f / static_cast<float>(bitBlockSize));

        const unsigned int intIndex = index / blocksPerInt;
        const unsigned int bitOffset = (index % blocksPerInt) * bitBlockSize;

        if (intIndex < blocks.compressedBlocks.size()) 
        {
            const uint64_t mask = (1ULL << bitBlockSize) - 1;
            uint64_t currentPackedBlock = blocks.compressedBlocks[intIndex];

            // Clear the existing block data at this position
            currentPackedBlock &= ~(mask << bitOffset);

            // Set the new block data
            const uint64_t packedBlock = static_cast<uint64_t>(blocks.BlockToPalette[newNum]);
            currentPackedBlock |= (packedBlock << bitOffset);
            blocks.compressedBlocks[intIndex] = currentPackedBlock;
        }
    }

};



};

#endif // PALETTE_HPP
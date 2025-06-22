#include "decompressor.h"
#include <fstream>
#include <vector>
#include <zlib.h>

bool Decompressor::decompressFile(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream in(inputFile, std::ios::binary);
    if (!in) {
        return false;
    }

    std::ofstream out(outputFile, std::ios::binary);
    if (!out) {
        return false;
    }

    std::vector<char> buffer(std::istreambuf_iterator<char>(in), {});
    uLong sourceLen = buffer.size();
    uLong destLen = sourceLen * 4; // Estimation
    std::vector<char> decompressedData(destLen);

    if (uncompress(reinterpret_cast<Bytef*>(decompressedData.data()), &destLen, 
                   reinterpret_cast<const Bytef*>(buffer.data()), sourceLen) != Z_OK) {
        return false;
    }

    out.write(decompressedData.data(), destLen);
    return true;
}

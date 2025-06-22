#include "compressor.h"
#include <fstream>
#include <vector>
#include <zlib.h>

bool Compressor::compressFile(const std::string& inputFile, const std::string& outputFile) {
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
    uLong destLen = compressBound(sourceLen);
    std::vector<char> compressedData(destLen);

    if (compress(reinterpret_cast<Bytef*>(compressedData.data()), &destLen, 
                 reinterpret_cast<const Bytef*>(buffer.data()), sourceLen) != Z_OK) {
        return false;
    }

    out.write(compressedData.data(), destLen);
    return true;
}

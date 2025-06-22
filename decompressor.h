#ifndef DECOMPRESSOR_H
#define DECOMPRESSOR_H

#include <string>

class Decompressor {
public:
    static bool decompressFile(const std::string& inputFile, const std::string& outputFile);
};

#endif // DECOMPRESSOR_H

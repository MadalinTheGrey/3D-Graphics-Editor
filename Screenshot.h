#pragma once
#include <cstdint>

struct BmpHeader {
    char bitmapSignatureBytes[2] = { 'B', 'M' }; //format bitmap
    uint32_t sizeOfBitmapFile = 54 + 1040*685*3; //54 pixel header, img size = 1040*685 *3(pixel = 3bites)
    uint32_t reservedBytes = 0;
    uint32_t pixelDataOffset = 54;
} bmpHeader;
struct BmpInfoHeader {
    uint32_t sizeOfThisHeader = 40;
    int32_t width = 1040; // in pixels
    int32_t height = 685; // in pixels
    uint16_t numberOfColorPlanes = 1; // must be 1
    uint16_t colorDepth = 24;
    uint32_t compressionMethod = 0;
    uint32_t rawBitmapDataSize = 0; // generally ignored
    int32_t horizontalResolution = 3780; // in pixel per meter
    int32_t verticalResolution = 3780; // in pixel per meter
    uint32_t colorTableEntries = 0;
    uint32_t importantColors = 0;
} bmpInfoHeader;
struct Pixel {
    uint8_t blue = 255;
    uint8_t green = 255;
    uint8_t red = 0;
};
bool save;
void SaveScreenShot(bool w = 0);
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jpeglib.h>
#include <png.h>
#include <b64/cencode.h> 
#include "dataprocessing.h"

#define MAX_ENCODED_IMAGES 10
#define MAX_ENCODED_IMAGE_LENGTH 5000 // Adjust the value as needed
char Encoded_Images[MAX_ENCODED_IMAGES][MAX_ENCODED_IMAGE_LENGTH] = {0};
int numEncodedImages = 0;



void addEncodedImage(const char* encodedData, size_t encodedDataSize) {
    if (numEncodedImages >= MAX_ENCODED_IMAGES) {
        printf("Max number of encoded images reached.\n");
        return;
    }

    size_t copySize = encodedDataSize < MAX_ENCODED_IMAGE_LENGTH ? encodedDataSize : MAX_ENCODED_IMAGE_LENGTH - 1;
    memcpy(Encoded_Images[numEncodedImages], encodedData, copySize);
    Encoded_Images[numEncodedImages][copySize] = '\0';
    numEncodedImages++;
}



void processJPEGFile(const char* file) {
    FILE* fp = fopen(file, "rb");
    if (!fp) {
        printf("Error opening file: %s\n", file);
        return;
    }

    // Create a JPEG decompression struct
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);

    // Set the input file for the decompression
    jpeg_stdio_src(&cinfo, fp);

    // Read the JPEG header and start the decompression
    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);

    // Determine the image size and allocate memory for the image data
    int width = cinfo.output_width;
    int height = cinfo.output_height;
    int numComponents = cinfo.output_components; // 3 for RGB, 4 for RGBA
    size_t jpegDataSize = width * height * numComponents;
    unsigned char* jpegData = (unsigned char*)malloc(jpegDataSize);

    // Read the image data
    JSAMPARRAY rowBuffer = (*cinfo.mem->alloc_sarray)((j_common_ptr)&cinfo, JPOOL_IMAGE, width * numComponents, 1);
    size_t bytesRead = 0;
    while (cinfo.output_scanline < height) {
        jpeg_read_scanlines(&cinfo, rowBuffer, 1);
        memcpy(jpegData + bytesRead, rowBuffer[0], width * numComponents);
        bytesRead += width * numComponents;
    }

    // Finish decompression
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(fp);

 // Encode the JPEG data using Base64
    base64_encodestate state;
    base64_init_encodestate(&state);
    size_t encodedSize = base64_encode_blockend(0, &state); // Determine the size needed for the encoded data
    char* encodedData = (char*)malloc(encodedSize);
    if (!encodedData) {
        printf("Memory allocation failed.\n");
        free(jpegData);
        return;
    }

    int bytesEncoded = base64_encode_block((const char*)jpegData, jpegDataSize, encodedData, &state);
    bytesEncoded += base64_encode_blockend(encodedData + bytesEncoded, &state);
    encodedData[bytesEncoded] = '\0';

    // Add the encoded data to the Encoded_Images array
    addEncodedImage(encodedData, bytesEncoded);

    // Clean up allocated memory
    free(jpegData);
    free(encodedData);
}

void processPNGFile(const char* file) {
    FILE* fp = fopen(file, "rb");
    if (!fp) {
        printf("Error opening file: %s\n", file);
        return;
    }

    // Create a PNG read struct
    png_structp pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!pngPtr) {
        fclose(fp);
        printf("Failed to create PNG read struct.\n");
        return;
    }

    // Create a PNG info struct
    png_infop infoPtr = png_create_info_struct(pngPtr);
    if (!infoPtr) {
        fclose(fp);
        png_destroy_read_struct(&pngPtr, NULL, NULL);
        printf("Failed to create PNG info struct.\n");
        return;
    }

    // Set the custom read function to handle fread
    png_set_read_fn(pngPtr, fp, (png_rw_ptr)fread);

    // Set the function to handle reading errors
    setjmp(png_jmpbuf(pngPtr));

    // Read the PNG header
    png_read_info(pngPtr, infoPtr);

    // Get image info
    int width = png_get_image_width(pngPtr, infoPtr);
    int height = png_get_image_height(pngPtr, infoPtr);
    int bitDepth = png_get_bit_depth(pngPtr, infoPtr);
    int colorType = png_get_color_type(pngPtr, infoPtr);
    int numChannels = png_get_channels(pngPtr, infoPtr);

    // Allocate memory for the PNG data
    size_t pngDataSize = width * height * numChannels;
    unsigned char* pngData = (unsigned char*)malloc(pngDataSize);

    // Set up row pointers
    png_bytep* rowPointers = (png_bytep*)malloc(height * sizeof(png_bytep));
    for (int i = 0; i < height; i++) {
        rowPointers[i] = pngData + i * width * numChannels;
    }

    // Read the PNG image data
    png_read_image(pngPtr, rowPointers);

    // Finish reading
    png_read_end(pngPtr, NULL);

    // Clean up
    png_destroy_read_struct(&pngPtr, &infoPtr, NULL);
    free(rowPointers);
    fclose(fp);

    // Encode the PNG data using Base64
    base64_encodestate state;
    base64_init_encodestate(&state);
    size_t encodedSize = base64_encode_blockend(0, &state); // Determine the size needed for the encoded data
    char* encodedData = (char*)malloc(encodedSize);
    if (!encodedData) {
        printf("Memory allocation failed.\n");
        free(pngData);
        return;
    }

    int bytesEncoded = base64_encode_block((const char*)pngData, pngDataSize, encodedData, &state);
    bytesEncoded += base64_encode_blockend(encodedData + bytesEncoded, &state);
    encodedData[bytesEncoded] = '\0';

    // Add the encoded data to the Encoded_Images array
    addEncodedImage(encodedData, bytesEncoded);

    // Clean up allocated memory
    free(pngData);
    free(encodedData);
}
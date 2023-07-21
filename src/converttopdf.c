#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libharu/hpdf.h>

void createPDFPage(const char* encodedData) {
    /* Initialize PDFlib */
    HPDF_Doc pdf;
    HPDF_Page page;
    HPDF_Image image;
    HPDF_STATUS status;

    /* Create a new PDF document */
    pdf = HPDF_New(NULL, NULL);
    if (!pdf) {
        printf("Error: Could not initialize libharu.\n");
        return;
    }

    /* Create a new page */
    page = HPDF_AddPage(pdf);
    if (!page) {
        printf("Error: Could not create PDF page.\n");
        HPDF_Free(pdf);
        return;
    }

    printf("PDF page created successfully.\n");

    /* Decode the Base64-encoded data */
    size_t encodedLength = strlen(encodedData);
    unsigned char* decodedData = (unsigned char*)malloc(encodedLength);
    size_t decodedLength = HPDF_Base64Decode((const HPDF_BYTE*)encodedData, encodedLength, decodedData);

    printf("Data decoded successfully. Decoded length: %zu\n", decodedLength);

    /* Embed the decoded data as an image */
    image = HPDF_LoadPngImageFromMem(pdf, decodedData, decodedLength);
    if (!image) {
        printf("Error: Could not load the decoded image data as a PNG image.\n");
        free(decodedData);
        HPDF_Free(pdf);
        return;
    }

    printf("Image loaded successfully.\n");

    /* Get the image size */
    HPDF_REAL image_width = HPDF_Image_GetWidth(image);
    HPDF_REAL image_height = HPDF_Image_GetHeight(image);

    /* Get the page size */
    HPDF_REAL page_width = HPDF_Page_GetWidth(page);
    HPDF_REAL page_height = HPDF_Page_GetHeight(page);

    /* Calculate the scale factor to fit the image within the page */
    HPDF_REAL scale_x = page_width / image_width;
    HPDF_REAL scale_y = page_height / image_height;
    HPDF_REAL scale = scale_x < scale_y ? scale_x : scale_y;

    /* Place the image on the page */
    status = HPDF_Page_DrawImage(page, image, 0, 0, image_width * scale, image_height * scale);
    if (status != HPDF_OK) {
        printf("Error: Could not place the image on the PDF page.\n");
    }

    printf("Image placed on the PDF page successfully.\n");

    /* Save the PDF to a file */
    status = HPDF_SaveToFile(pdf, "output.pdf");
    if (status != HPDF_OK) {
        printf("Error: Could not save the PDF to the output file.\n");
    }

    /* Clean up the decoded data and release resources */
    free(decodedData);
    HPDF_Free(pdf);

    printf("PDF file generated successfully.\n");
}

int main() {
    /* Assuming you have the encoded data for the PNG image */
    const char* encodedData = "Base64-encoded-data"; // Replace "Base64-encoded-data" with the actual Base64-encoded string of the PNG image

    /* Create the PDF page and embed the image */
    createPDFPage(encodedData);

    return 0;
}

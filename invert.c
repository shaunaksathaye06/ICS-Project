#include <stdio.h>
#include <stdlib.h>

#define IMAGE_WIDTH 28
#define IMAGE_HEIGHT 28
#define IMAGE_SIZE (IMAGE_WIDTH * IMAGE_HEIGHT)

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input.raw> <output.raw>\n", argv[0]);
        return 1;
    }

    const char *input_filename = argv[1];
    const char *output_filename = argv[2];

    FILE *in_file = fopen(input_filename, "rb");
    if (!in_file) {
        perror("Error opening input file");
        return 1;
    }

    unsigned char pixels[IMAGE_SIZE];
    size_t read = fread(pixels, sizeof(unsigned char), IMAGE_SIZE, in_file);
    fclose(in_file);

    if (read != IMAGE_SIZE) {
        fprintf(stderr, "Error: Expected %d bytes, but read %zu bytes.\n", IMAGE_SIZE, read);
        return 1;
    }

    // Invert each pixel
    for (int i = 0; i < IMAGE_SIZE; i++) {
        pixels[i] = 255 - pixels[i];
    }

    FILE *out_file = fopen(output_filename, "wb");
    if (!out_file) {
        perror("Error opening output file");
        return 1;
    }

    fwrite(pixels, sizeof(unsigned char), IMAGE_SIZE, out_file);
    fclose(out_file);

    printf("Image inverted and saved to %s\n", output_filename);
    return 0;
}

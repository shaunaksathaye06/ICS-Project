#include <stdio.h>
#include <stdlib.h>

#define IMAGE_WIDTH 28
#define IMAGE_HEIGHT 28
#define IMAGE_SIZE (IMAGE_WIDTH * IMAGE_HEIGHT)

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image.raw>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    unsigned char pixels[IMAGE_SIZE];
    size_t read = fread(pixels, sizeof(unsigned char), IMAGE_SIZE, file);
    fclose(file);

    if (read != IMAGE_SIZE) {
        fprintf(stderr, "Error: Expected %d bytes but read %zu bytes.\n", IMAGE_SIZE, read);
        return 1;
    }

    printf("Pixel values (28x28):\n");
    for (int row = 0; row < IMAGE_HEIGHT; row++) {
        for (int col = 0; col < IMAGE_WIDTH; col++) {
            printf("%3d ", pixels[row * IMAGE_WIDTH + col]);
        }
        printf("\n");
    }

    return 0;
}

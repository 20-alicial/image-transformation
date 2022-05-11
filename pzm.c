#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include "project2.h"
#include <math.h>

// skips 'a' number of chars
void skipf(int a, FILE *f)
{
    // pull n chars out of f, disregard them
    for (int i=0; i<a; i++)
        getc(f);
}

int main(int argc, char*argv[])
{
    FILE *f = fopen(argv[1],"r");

    skipf(4,f);

    // Byte 4:5 Time
    uint16_t time = read2(f);

    // Byte 6:9 Date
    uint32_t date = read4(f);

    // Byte 10:13, width & height
    uint16_t w = read2(f);
    uint16_t h = read2(f);

    skipf(4,f);

    // Byte 18
    uint8_t eighteen = getchar();

    int is_grey = eighteen&0X02;
    int rle  = eighteen&0X01;

    skipf(3,f);
   
    // Byte 22
    char *description = read_string(f);
    
    // Color info
    uint32_t runs = read4(f);

    int run_bytes = runs*4;

    int pixel_bytes;
    if (is_grey==1) {
        pixel_bytes=runs;
        } else if (is_grey==0) {
            pixel_bytes= runs*3;
        }

    printf("{\n  \"filename\" : \"%s\",",argv[1]);
    printf("{\n  \"date\" : \"%d%d%d\",",date);
    printf("{\n  \"time\" : \"%d%d\",",time);
    printf("{\n  \"width\" : \"%d\",",w);
    printf("{\n  \"height\" : \"%d\",",h);
    printf("\n  \"grayscale\" : ");
    if (is_grey==1) {
        printf("true,");
    } else {
        printf("false,");
    }
    printf("{\n  \"rle\" : ");
    if (rle==1) {
        printf("true,");
    } else {
        printf("false,");
    }
    printf("{\n  \"description\" : \"%s\",",description);
    printf("{\n  \"runs\" : \"%u\",",runs);
    printf("{\n  \"run-bytes\" : \"%d\",",run_bytes);
    printf("{\n  \"pixel-bytes\" : \"%d\",",pixel_bytes);

}
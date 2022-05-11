#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include "project2.h"
#include <math.h>

int main(int argc, char*argv[])
{
    // Initializing variables
     char a = '.'; // for future expansion


    // Bytes 0:1, magic!
    char c = getchar();
    char d = getchar();
    if (c!='P' || d!='Z') {
        fprintf(stderr, "%s: expected PZ file\n", argv[0]);
        exit(1);
    }
    printf("PZ");

    // Bytes 2:3, future expansion
    printf("%c%c",a,a);
    getchar();
    getchar();

    // Byte 4:5 Time
    struct tm *local_time;
    time_t t = time(NULL);
    local_time = localtime(&t);
    int hour = local_time->tm_hour;
    int min = local_time->tm_min;
    putchar(hour);
    putchar(min);

    getchar();
    getchar();

    // Byte 6:9 Date
    int year = 1900+local_time->tm_year;
    int month = 1+local_time->tm_mon;
    int date = local_time->tm_mday;

    putchar(year>>8);
    putchar(year);
    putchar(month);
    putchar(date);

    getchar();
    getchar();
    getchar();
    getchar();

    // Byte 10:11 & 12:13, width & height
    int w = byte_to_int2();
    int h = byte_to_int2();
    //printf("w: %d, h: %d", w, h);
    int_to_byte2(w);
    int_to_byte2(h);
    // putchar(w>>8);
    // putchar(w&255);
    // putchar(h>>8);
    // putchar(h&255);

    // Byte 14:17, future expansion
    printf("%c%c%c%c", a,a,a,a);
    getchar();
    getchar();
    getchar();
    getchar();

    // Byte 18, grey data
    int eighteen = getchar();

    int is_grey;
    if (eighteen == 3) {
        is_grey=1;
    }
    if (eighteen == 1) {
        is_grey=0;
    }
    putchar(eighteen);

    // Byte 19:21, future expansion
    printf("%c%c%c", a,a,a);
    getchar();
    getchar();
    getchar();

    //Byte 22:??, get char and prints the string
    char getc = 1;
    while (getc != '\0') 
    {
    getc = getchar();
    putchar(getc);
    //printf("char: %c\n", getc);
    }

    // ---- GETTING COLOR INFORMATION
    // Runs
    unsigned int run = byte_to_int4();
    //printf("run: %d\n", run);

    // Malloc and fill run Length Array
    unsigned int* len_arr = (unsigned int*)malloc(sizeof(unsigned int)*run);
    if (len_arr == NULL) {
        fprintf(stderr, "Memory allocation failed: len_arr");
    }
    
    for (int i=0; i<run; i++)
    {
    len_arr[i] = byte_to_int4();
    }

    //Malloc and fill RGB Array
    struct rgb* rgb_arr = (struct rgb*)malloc(sizeof(unsigned int)*run);
    if (rgb_arr== NULL) {
        fprintf(stderr, "Memory allocation failed: rgb_arr");
    }

    for (int i=0; i<run; i++) {
        int r = getchar();
        int g = getchar();
        int b = getchar();
        struct rgb c;
        c.r = r;
        c.g = g;
        c.b = b;
        rgb_arr[i] = c;
    }

    // ---- PRINTING COLOR INFORMATION
    // print runs
    int_to_byte4(run);

    // print len array
    for (int i = 0; i < run; i++) {
    int_to_byte4(len_arr[i]);
    //printf("run: %d \n",len_arr[i]);
    }

    // print rgb array
    if (is_grey == 0) {
        for (int i=0; i<run; i++) {
        int neg_r = 255 - rgb_arr[i].r;
        int neg_g = 255 - rgb_arr[i].g;
        int neg_b = 255 - rgb_arr[i].b;
        putchar(neg_r); 
        putchar(neg_g); 
        putchar(neg_b);
        }
    }

    if (is_grey == 1) {
        for (int i=0; i<run; i++) {
        int neg_r = 255 - rgb_arr[i].r;
        putchar(neg_r); 
        }
    }
    
    return 0; 

}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include "project2.h"
#include <math.h>

// turns a rgb grey
struct rgb turn_grey(struct rgb c)
{
    int red = c.r, green = c.g, blue = c.b;
    int l = 0.2126 * red + 0.7152 * green + 0.0722 * blue;
    int lum = (int) trunc(l);
    struct rgb grey;
    grey.r = lum;
    grey.g = lum;
    grey.b = lum;
    return grey;

}

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
    skip(2);

    // Byte 4:5 Time
    struct tm *local_time;
    time_t t = time(NULL);
    local_time = localtime(&t);
    int hour = local_time->tm_hour;
    int min = local_time->tm_min;
    putchar(hour);
    putchar(min);
    skip(2);

    // Byte 6:9 Date
    int year = 1900+local_time->tm_year;
    int month = 1+local_time->tm_mon;
    int date = local_time->tm_mday;

    putchar(year>>8);
    putchar(year);
    putchar(month);
    putchar(date);
    skip(4);

    // Byte 10:11 & 12:13, width & height
    int w = byte_to_int2();
    int h = byte_to_int2();
    int_to_byte2(w);
    int_to_byte2(h);
   

    // Byte 14:17, future expansion
    printf("%c%c%c%c", a,a,a,a);
    skip(4);

    // Byte 18, grey data
    putchar(3);
    skip(4);

    // Byte 19:21, future expansion
    printf("%c%c%c", a,a,a);
    skip(3);
    
    //Byte 22:??, get char and prints the string
    char getc = 1;
    while (getc != '\0') 
    {
    getc = getchar();
    putchar(getc);
    } 

    // ---- GETTING COLOR INFORMATION
    // Runs
    unsigned int run = byte_to_int4();

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
        rgb_arr[i] = turn_grey(c);
    }

    // ---- PRINTING COLOR INFORMATION

    int_to_byte4(run);

  
    for (int i = 0; i < run; i++) {
    int_to_byte4(len_arr[i]);
  
    }

    // print rgb array
    for (int i=0; i<run; i++) {
        int grey = rgb_arr[i].r;
        putchar(grey);
    }

    return 0; 

}

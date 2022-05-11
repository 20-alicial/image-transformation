#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include "project2.h"
#include <math.h>

// Takes an array of rgb and its image size, outputs the number of runs
int run_num(struct rgb * arr, int pixels)
{
  int runs = 1;
  struct rgb prev;
  prev = arr[0]; 

 for (int i = 0; i < pixels; i++) {
    if (rgb_eq(arr[i], prev)) {
            continue;
        } else {
            runs += 1;
            prev = arr[i];
        }
    } return runs;
 }

// Takes an array, number of runs, its size 
// outputs the number of a pointer to an array of run lengths
int *arr_run_len(struct rgb * arr, int pixels, int runs)
{
  struct rgb prev;
  prev = arr[0];  
  int length = 1;
  int lc = 0;

  int *run_lengths = (int *) malloc(sizeof(int) * runs);
    for (int i = 1; i < pixels; i++) {
        if (rgb_eq(arr[i], prev)) {
            length += 1;
            continue;
        } else {
            run_lengths[lc] = length;
            lc++;
            length = 1;
            prev = arr[i]; 
        }
        // missing the very last item in array. print it out.
        run_lengths[runs-1] = length;
    } return run_lengths;
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
    int width = byte_to_int2();
    int height = byte_to_int2();
    //printf("w: %d, h: %d", w, h);
    int_to_byte2(width);
    int_to_byte2(height);

    printf("%c%c%c%c", a,a,a,a);
    skip(4);
    
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

    printf("%c%c%c", a,a,a);
    skip(3);

    //Byte 22:??, get char and prints the string
    char getc = 1;
    while (getc != '\0') 
    {
    getc = getchar();
    putchar(getc);
    }



// ---- GETTING & PRINTING COLOR INFORMATION

    // Runs
    unsigned int run = byte_to_int4();
    //printf("original run: %d\n", run);

    // Malloc and fill run Length Array
    unsigned int* len_arr = (unsigned int*)malloc(sizeof(unsigned int)*run);
    if (len_arr == NULL) {
        fprintf(stderr, "Memory allocation failed: len_arr");
    }
    
    for (int i=0; i<run; i++)
    {
    len_arr[i] = byte_to_int4();
   //printf("%d", len_arr[i]);
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
        //printf("%d %d %d\n", c.r, c.g, c.b);
    }


     struct rgb* expanded = (struct rgb*)malloc(sizeof(struct rgb)*width*height);
     if (expanded== NULL) {
        fprintf(stderr, "Memory allocation failed: expanded");
        }

    // creates expanded array of colors
    int count = 0;
     for (int j=0; j<run; j++) {
        for (int k=len_arr[j]; k>0; k--) {
            expanded[count]=rgb_arr[j];
            count ++;
      }
    }

    // Creating array of flipped image
    // The order of each row is reversed (i.e arr[width-1] becomes arr[0])
    struct rgb* flip_arr = (struct rgb*)malloc(sizeof(unsigned int)*width*height);
        if (flip_arr== NULL) {
            fprintf(stderr, "Memory allocation failed: flip_arr");
        }

        int counter = 0;
        for (int i=1; i<=height; i++) {
            for (int k = (i*width-1); k>=width*(i-1); k--) {
                flip_arr[counter]=expanded[k];
                counter ++;
            //printf("%d %d %d\n", flip_arr[counter].r, flip_arr[counter].g, flip_arr[counter].b);
            }
        }

    int flip_run = run_num(flip_arr, width*height);
    //printf("%d/n", flip_run);
    
    // print new runs
    int_to_byte4(flip_run);

    int *flip_len_arr = arr_run_len(flip_arr, width*height, flip_run);

    // print new len array
    for (int i = 0; i < flip_run; i++) {
    int_to_byte4(flip_len_arr[i]);
    //printf("run: %d \n",flip_len_arr[i]);
    }

 // print rgb array of flipped
    if (is_grey == 0) {
        for (int i=0; i< width*height; i++) {
        if (rgb_eq(flip_arr[i], flip_arr[i+1])==0) {
            int r = flip_arr[i].r;
            int g = flip_arr[i].g;
            int b = flip_arr[i].b;
            putchar(r);
            putchar(g);
            putchar(b);
    }
    }}

 // print grey array of flipped
    if (is_grey == 1) {
        for (int i=0; i<flip_run; i++) {
        int r = flip_arr[i].r;
        putchar(r); 
        }
    }

    return 0;
}
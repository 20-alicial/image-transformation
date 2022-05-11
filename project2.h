#ifndef _PROJECT2_H_
#define _PROJECT2_H_

#include <stdint.h>

struct rgb {
  unsigned char r;
  unsigned char g;
  unsigned char b;
};

struct image {
  uint32_t w;
  uint32_t h;
  struct rgb *pixels; // array of length w*h
}; 

// an image's pixels are stored in "row order",
// with the top row first from left to right,
// then the next row underneath, etc.

/* implement these two utilities in project1-utils.c */

// compare two rgb structs for logical equality
int rgb_eq(struct rgb c1, struct rgb c2);

// check if one rgb is grey
int rgb_gray(struct rgb c1);

// check if image is all gray pixels
int img_grayscale(struct image *img);

/* you may add more utilities if you like, but don't change these two */

//takes an rgb struct prints the ascii symbol version
void rgb_to_binary(int r, int g, int b);

// turns an integer into a four byte big Endian integer and prints
void int_to_byte4(int n);

// turns a four byte big Endian integer into an int, returns int
unsigned int byte_to_int4();

// turns an integer into a two byte big Endian integer and prints
void int_to_byte2(int n);

// turns a two byte big Endian integer into an int and returns int
int byte_to_int2();

//Takes a RGB and converts it into a
// Takes an 3 byte RBG and prints each r,g,b as int
void rgb_print(struct rgb color);

// Calls getchar input number of times
void skip(int a);

#endif

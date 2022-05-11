#include "project2.h"
#include <stdio.h>

// compare two rgb structs for logical equality
int rgb_eq(struct rgb c1, struct rgb c2)
{
  if ((c1.r == c2.r) && (c1.g == c2.g) && (c1.b == c2.b)) {
    return 1;
  }
  return 0;
}

// check if one rgb is grey
int rgb_gray(struct rgb c1)
{
  if ((c1.r == c1.g) && (c1.g == c1.b)) {
    return 1;
  }
  return 0;
}
// check if image is all gray pixels
int img_grayscale(struct image *img)
{
  for (int i = 0; i < (img->w * img->h); i++) {
    if (rgb_gray(img->pixels[i])) {
      continue;
    } return 0;
  } return 1;
}

//takes an rgb struct prints the ascii symbol version
void rgb_to_binary(int r, int g, int b) 
{
 //int red = c.r, green = c.g, blue = c.b;
 putchar(r); 
 putchar(g); 
 putchar(b);
}

// turns an integer into a two byte big Endian integer and prints
void int_to_byte2(int n) 
{
  unsigned int bit1, bit2;
  bit1 = (n >> 8) & 0xff;
  bit2 = n & 0xfff;
  putchar(bit1);
  putchar(bit2);
}

// turns an integer into a four byte big Endian integer and prints
void int_to_byte4(int n) 
{
  unsigned int bit1, bit2, bit3, bit4;
  bit1 = (n >> 24) & 0xff;
  bit2 = (n >> 16) & 0xff;
  bit3 = (n >> 8) & 0xff;
  bit4 = n & 0xff;
  putchar(bit1);
  putchar(bit2);
  putchar(bit3);
  putchar(bit4);
}

// turns a two byte big Endian integer into an int and returns int
int byte_to_int2()
{
  int bit1 = (getchar() <<8);
  int bit2 = (getchar());

  int integer = bit1 + bit2;

  return integer;

}

// turns a four byte big Endian integer into an int and returns int 
unsigned int byte_to_int4()
{
  unsigned int bit1 = (getchar() <<24);
  //printf("bit1: %u\n", bit1);
  unsigned int bit2 = (getchar() <<16);
  //printf("bit2: %u\n", bit2);
  unsigned int bit3 = (getchar() <<8);
  //printf("bit3: %u\n", bit3);
  unsigned int bit4 = getchar();
  // printf("getchar: %d\n", c);
  //printf("bit4: %u\n", bit4);

  unsigned int integer = bit1 + bit2 + bit3 + bit4;

  return integer;

}

//Takes a RGB and converts it into a
// Takes an 3 byte RBG and prints each r,g,b as int
void rgb_print(struct rgb color)
{
  int r = color.r;
  int g = color.g;
  int b = color.b;
  printf("%d ", r); 
  printf("%d ", g);
  printf("%d ", b);
}

// Calls getchar input number of times
void skip(int a)
{
    for (int i=0; i<a; i++) {
        getchar();
    }
}
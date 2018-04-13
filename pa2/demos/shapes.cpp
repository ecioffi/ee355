#include <iostream>
#include <cmath>
#include "bmplib.h"

using namespace std;

// global variable. bad style but ok for this lab
unsigned char image[SIZE][SIZE][RGB];

// Fill in this function:
void draw_rectangle(int top, int left, int height, int width) {
  for(int i = top; i < top + height; i++){
    for(int j = left; j < left + width; j++){
      image[i][j][0] = 0;
      image[i][j][1] = 0;
    }
  }
}

void draw_triangle(int leftx, int lefty, int base, int height){
  for(int i = 0 ; i <height ; i++){
    for(int j = 0; j <(base*i/height); j ++){
      image[leftx-height+i][lefty + base*(height-i)/height/2 + j][0] = 0;  
    }
  }
}


int main() {
   // initialize the image to all white pixels
   for (int i=0; i < SIZE; i++) {
      for (int j=0; j < SIZE; j++) {
        if(i%32==0 || j%32==0)
          continue;
        for (int k=0; k < RGB; k++) {
         image[i][j][k] = 255;
         }
      }
   }
   
   // Main program loop here

   //draw_rectangle(5,5,100,100);
   
   //draw_triangle(400,100,200,200);
   
   showRGBBMP(image);
   // Write the resulting image to the .bmp file
   writeRGBBMP("output.bmp", image);
   
   return 0;
}

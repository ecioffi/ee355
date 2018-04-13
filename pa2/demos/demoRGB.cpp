#include <iostream>
#include <cmath>
#include "bmplib.h"

using namespace std;

int main() {
   unsigned char image[SIZE][SIZE][RGB];

   for (int i=0; i < SIZE; i++) {
      for (int j=0; j < SIZE; j++) {
        for (int k=0; k < RGB; k++) {
         image[i][j][k] = 255;
         }
      }
   }

   for(int i=0; i < SIZE; i++) {
      image[i][256][1] = 0;
      image[256][i][1] = 0;
      //every 20 steps, display
      if (i%20==0) showRGBBMP(image);
   }

   double r = 100;
    int iters = 0;
   for (double theta=0.0; theta < 2*M_PI; theta += .01) {
      double x = r*cos(theta);
      double y = r*sin(theta);
      x += SIZE/2;
      y += SIZE/2;
      image[(int)y][(int)x][2] = 0;
      //every 20 steps, display
      iters++; if (iters%20==0) showRGBBMP(image);
   }
   
   //at end, display complete image
   showRGBBMP(image);
   
   // save to file
   writeRGBBMP("crossRGB.bmp", image);
      
   return 0;
}

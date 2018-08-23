//-----------------------------------------------------------------------------|
// Authorship
//-----------------------------------------------------------------------------|
//
// Tim Lum
// twhlum@gmail.com
// Created:  2018.07.15
// Modified: 2018.08.22
//

/*
1.7 - RotateMatrix() - P.91
Given an image represented by an NxN matrix, where each pixel in the image is 4
bytes, write a method to rotate the image by 90 degrees.

Can you do this in place?



//-----------------------------------------------------------------------------|
// PROBLEM SETUP AND ASSUMPTIONS
//-----------------------------------------------------------------------------|

A left rotation may be performed by calling a right rotation 3 times.
  Only the right (clockwise) rotation shall be handled
The nature of the pixel is immaterial; we may handle the pixel as a 32-bit int
Since the problem specifies an N x N matrix, we address a square aspect ratio

  To move a pixel

     0   1    X         0   1    X
   +---+---+          +---+---+     ([0][0] becomes [1][0])
0  | 1 | 2 |       0  | 4 | 1 |     ([1][0] becomes [1][1])
   +---+---+          +---+---+
1  | 4 | 3 |       1  | 3 | 2 |
   +---+---+          +---+---+
Y                  Y

Output format is ambiguous, though it is implied that the data itself should be
rotated. However, displaying the "image" and its rotated result may also be
acceptable.



//-----------------------------------------------------------------------------|
// NAIVE APPROACH
//-----------------------------------------------------------------------------|

Iterate across every pixel within a quadrant and for (4) times
  Identify the 4 sister-pixels
  And swap them in turn

     0   1   2    X    [X][Y]               is sister to
   +---+---+---+       [XMax - X][Y]        which is sister to
0  | 1 | 2 | 3 |       [XMax - X][YMax - Y] which is sister to
   +---+---+---+       [X][YMax-Y]
1  | 8 | 9 | 4 |
   +---+---+---+
2  | 7 | 6 | 5 |
   +---+---+---+

The global behavioral rule may be defined as:

The 90 degree rotational position of any pixel in a square matrix with coordinates:

X, Y

Is

(XMax - Y), X

     0   1   2    X
   +---+---+---+
0  | X | O | X |     0, 0 rotates 90 degrees to
   +---+---+---+     2, 0 which rotates 90 degrees to
1  | O | O | O |     2, 2 which rotates 90 degrees to
   +---+---+---+     0, 2
2  | X | O | X |
   +---+---+---+



//-----------------------------------------------------------------------------|
// OPTIMIZATIONS
//-----------------------------------------------------------------------------|

1) The orientation of the image may be stored as a separate value from 0 to 3.
   This may then be used to interpret the N, E, S, W orientation of the image
   without modifying the image itself.

Effectively, we may interject an orientation filter which appropriately redirects
array access based upon the rotational state of the image.

This has the added benefit of functioning on non-square arrays, and also facilitates
easy addition of -90 and 180 degree rotations.

From an image editing standpoint, interpretation rather than alteration of the base
data will also better preserve image information.



//-----------------------------------------------------------------------------|
// TIME COMPLEXITY
//-----------------------------------------------------------------------------|

Any solution which modifies the original body of data may not complete faster
than in a time complexity of:

O( n^2 )

A filter solution, however, only adds a constant time alteration to the random
access lookup of the parent data. As a "rotation" is merely the toggling of a
rotation byte, the filter may complete in a time complexity of:

O( 1 )



//-----------------------------------------------------------------------------|
// PSEUDOLOGIC
//-----------------------------------------------------------------------------|

For every call to rotate, add 1 to the rotation state.
For a call to display the image, read across the rows and columns in an
  appropriate fashion.



//-----------------------------------------------------------------------------|
// CODE (C++)
//-----------------------------------------------------------------------------|
*/
// Compile with:
// $ g++ --std=c++11 01_07_RotateMatrix.cpp -o RotateMatrix
// Run with:
// $ ./RotateMatrix

#include <string>
#include <iostream>
#include <iomanip>

#define WIDTH  3
#define HEIGHT 7

// Rotation control:
// 0 == Base image
// 1 == 90 degree clockwise rotation
// 2 == 180 degree rotation
// 3 == 270 degree rotation
int ROTATION = 0;

int IMAGE[ WIDTH ][ HEIGHT ];

// (+) --------------------------------|
// #printMatrix( )
// ------------------------------------|
// Desc:    Print a matrix
// Params:  None
// PreCons: None
// PosCons: None
// RetVal:  None
void printMatrix( ) {
   int xDim = WIDTH;
   int yDim = HEIGHT;
   if( ROTATION == 0 ) {
      // For rows 0 to MAX...
      for( int row = 0 ; row < yDim ; row++ ) {
         // Print column 0 to MAX
         for( int col = 0 ; col < xDim; col++ ) {
            std::cout << std::setw( 3 ) << IMAGE[ col ][ row ] << " ";
         }
         std::cout << std::endl << std::endl;
      }
   }

   else if( ROTATION == 1 ) {
      for( int col = 0 ; col < xDim ; col++ ) {
         for( int row = ( yDim - 1 ) ; row >= 0; row-- ) {
            std::cout << std::setw( 3 ) << IMAGE[ col ][ row ] << " ";
         }
         std::cout << std::endl << std::endl;
      }
   }

   else if ( ROTATION == 2 ) {
      for( int row = yDim-1 ; row >= 0 ; row-- ) {
         for( int col = ( xDim - 1 ) ; col >= 0 ; col-- ) {
            std::cout << std::setw( 3 ) << IMAGE[ col ][ row ] << " ";
         }
         std::cout << std::endl << std::endl;
      }
   }

   else if ( ROTATION == 3 ) {
      for( int col = ( xDim - 1 ) ; col >= 0 ; col-- ) {
         for( int row = 0 ; row < yDim ; row++ ) {
            std::cout << std::setw( 3 ) << IMAGE[ col ][ row ] << " ";
         }
         std::cout << std::endl << std::endl;
      }
   }
}

// (+) --------------------------------|
// #rotateMatrix( )
// ------------------------------------|
// Desc:    Rotates a matrix
// Params:  None
// PreCons: None
// PosCons: The rotation has been incremented
// RetVal:  None
void rotateMatrix( ) {
   ROTATION = ( ROTATION + 1 ) % 4;
}



//-----------------------------------------------------------------------------|
// DRIVER
//-----------------------------------------------------------------------------|

// (+) --------------------------------|
// #main( int, char* )
// ------------------------------------|
// Desc:    Code driver
// Params:  int arg1 - The number of command line arguments passed in
//          char* arg2 - The content of the command line arguments
// PreCons: None
// PosCons: None
// RetVal:  int - The exit code (0 for normal, -1 for error)
int main( int argc, char* argv[ ] ) {
   std::cout << "Test of rotateMatrix( )" << std::endl;
   int xDim = WIDTH;
   int yDim = HEIGHT;

   // For row 0 to MAX
   for( int row = 0 ; row < yDim ; row++ ) {
      for( int col = 0 ; col < xDim ; col++ ) {
         IMAGE[ col ][ row ] = ( xDim * row ) + col;
      }
   }
   printMatrix( );

   std::cout << std::endl;

   std::cout << "Rotating..." << std::endl << std::endl;
   rotateMatrix( );
   printMatrix( );

   std::cout << std::endl;

   std::cout << "Rotating..." << std::endl << std::endl;
   rotateMatrix( );
   printMatrix( );

   std::cout << std::endl;

   std::cout << "Rotating..." << std::endl << std::endl;
   rotateMatrix( );
   printMatrix( );

   std::cout << std::endl;

   std::cout << "Rotating..." << std::endl << std::endl;
   rotateMatrix( );
   printMatrix( );

   return( 0 );
} // Closing main( int, char* )

// End of file 01_07_RotateMatrix.cpp

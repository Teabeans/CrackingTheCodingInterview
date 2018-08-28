//-----------------------------------------------------------------------------|
// Authorship
//-----------------------------------------------------------------------------|
//
// Tim Lum
// twhlum@gmail.com
// Created:  2018.08.23
// Modified: 2018.08.28
//

/*
1.8 - ZeroMatrix( ) - P.91
Write an algorithm such that if an element in an N x N matrix is 0, its entire
row and column are set to 0.



//-----------------------------------------------------------------------------|
// PROBLEM SETUP AND ASSUMPTIONS
//-----------------------------------------------------------------------------|

A numeric matrix may be represented as an array of integer arrays in the form:
  int someMatrix[WIDTH][HEIGHT]



//-----------------------------------------------------------------------------|
// NAIVE APPROACH
//-----------------------------------------------------------------------------|

Iterate across the base array
Store the 0 coordinates to a data structure for future reference

-  -  -  -  -
-  0  -  -  - <- (1, 1)
-  -  -  -  -
-  -  -  0  - <- (3, 3)
-  -  -  -  -

With the scan complete, refer to the list of 0 cells, and tare (zero) those cells
which share the X and Y coordinates of the original 0 cells.

[ ] (1, 1)
[ ] (3, 3)

Perform this action for all of the original 0 cells.

-  0  -  0  -
0 (0) 0  0  0
-  0  -  0  -
0  0  0 (0) 0
-  0  -  0  -

[X] (1, 1)
[X] (3, 3)

To scan the array, this strategy will require time on the order of:

O( n^2 )

Where 'n' is the dimension of the square matrix.

Additionally, the taring of the cells will incur a cost of 2n for every 0-cell.
In the worst case, where all cells are already zeroed, this operation will require
time to complete on the order of:

O( ( 2n ) * n^2 )

Or

O( n^3 )

As a cubic expression, this represents a significant amount of work, particularly
since the worst-case dataset requires no operations to be complete.



//-----------------------------------------------------------------------------|
// OPTIMIZATIONS
//-----------------------------------------------------------------------------|

Unfortunately, there is no method by which we can - in the worst case - avoid
checking all of the cells in the grid at O( n^2 ) time complexity. If none of
the cells have a value of 0, we can only ascertain that by examining all of them.

However, the presence of 0 cells can inform several optimizations for how we
search across the grid based on the following observations.

?  -  -  -  0  -  -  -  - <- ( 4:0 )
-  -  -  -  -  -  -  -  -
-  -  -  -  -  -  -  -  -
-  -  -  -  -  -  -  -  -
0  -  -  -  ?  -  -  -  - <- ( 0:4 )
-  -  -  -  -  -  -  -  -
-  -  -  -  -  -  -  -  -
-  -  -  -  -  -  -  -  -
-  -  -  -  -  -  -  -  -

If cells 4:0 and 0:4 are 0-cells, the identity of cells 0:0 and 4:4 do not matter.
The end result will be the same regardless.

More broadly, we do not need to check the intersection of known 0-cells.

Even more broadly, we ideally only need enough 0-cells to determine the end-result.

An ideal search strategy, therefore, should attempt to optimize for two behaviors

1) Maximize intersections
2) Minimize "in-line" 0 discoveries

This suggests that there is a preferential order by which to check the squares:

1) Squares that share neither X nor Y coordinate with a known 0-cell
2) Squares that share either an X or Y coordinate with known 0-cells
3) Never check squares that share both an X and Y coordinate with known 0-cells

A description of this sequence may be as follows:

1st Priority: Scan from left to right, top to bottom until a 0 is encountered.

X  X  X  X  X  X  X  X  X
X  X  X  0  -  -  -  -  - <- Hit!
-  -  -  -  -  0  -  -  -
-  0  -  -  -  -  -  -  -
0  -  -  -  -  -  -  -  -
-  -  -  -  -  -  -  -  0
-  -  -  -  -  -  -  0  -
-  -  -  -  -  -  0  -  -
-  -  -  -  -  0  -  -  -

Upon discovery of a 0-cell, immediately move to the next line, skipping the column
of known 0-cells.

X  X  X  X  X  X  X  X  X
X  X  X  0  -  -  -  -  -
X  X  X  -  X  0  -  -  - <- Hit!
-  0  -  -  -  -  -  -  -
0  -  -  -  -  -  -  -  -
-  -  -  -  -  -  -  -  0
-  -  -  -  -  -  -  0  -
-  -  -  -  -  -  0  -  -
-  -  -  -  -  0  -  -  -

When no lines remain...

X  X  X  X  X  X  X  X  X
X  X  X  0  -  -  -  -  -
X  X  X  -  X  0  -  -  -
X  0  -  -  -  -  -  -  -
0  -  -  -  -  -  -  -  -
-  -  X  -  X  -  X  X  0 <- Hit!
-  -  X  -  X  -  X  0  - <- Hit!
-  -  X  -  X  -  0  -  - <- Hit!
-  -  X  -  X  0  -  -  - <- Not discovered

Second Priority: Return to the first 0-cell
Then read those cells in line that do not share a Y coordinate with a previously
discovered 0-cell

X  X  X  X  X  X  X  X  X
X  X  X  0  X  -  -  -  -
X  X  X  -  X  0  -  -  -
X  0  -  -  -  -  -  -  -
0  -  -  -  -  -  -  -  -
-  -  X  -  X  -  X  X  0
-  -  X  -  X  -  X  0  -
-  -  X  -  X  -  0  -  -
-  -  X  -  X  0  -  -  - <- Hit!

From this information, the solution may be inferred. It bears mention that not
every square needed to be examined to arrive at the solution.

 0  0  X  0  X  0  0  0  0   (0) == Original zeroes
 0  0  0 (0) 0  0  0  0  0
 0  0  0  0  0 (0) 0  0  0
 0 (0) 0  0  0  0  0  0  0
(0) 0  0  0  0  0  0  0  0
 0  0  0  0  0  0  0  0 (0)
 0  0  0  0  0  0  0 (0) 0
 0  0  0  0  0  0 (0) 0  0
 0  0  0  0  0 (0) 0  0  0

The best-case scenario for this search algorithm is any matrix state which
contains a descending diagonal:

0  -  -  -  -  -  -  -  -
-  0  -  -  -  -  -  -  -
-  -  0  -  -  -  -  -  -
-  -  -  0  -  -  -  -  -
-  -  -  -  0  -  -  -  -
-  -  -  -  -  0  -  -  -
-  -  -  -  -  -  0  -  -
-  -  -  -  -  -  -  0  -
-  -  -  -  -  -  -  -  0

Wherein only O( n ) squares will be examined before the solution may be inferred.

Most notably, the previously worst-case condition:

0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0

Now yields the fastest O( n ) search.

To facilitate this skipping behavior, a list of 1st priority columns to search
may be maintained.

0 - 1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 -9

The cell to check may be determined by referencing this list, rather than a
traditional for-loop.

As 0-cells are encountered, their column numbers are removed from the list, thus
shortening the number of cells to check on the first pass.

However the scan is accomplished, we should have identified enough 0-cells
(preferably the minimum needed) to ascertain the final result. For ease during
the write portion, it is advantagous to store the coordinates as two arrays
representing the row and column of discovered 0-cells.

Index    Col   Row
0        X     X   <- Hit! At 0:0
1        -     -
2        -     -
3        -     -
4        X     -
5        -     X   <- Hit! At 4:5
6        -     -
7        -     -
8        -     -

Note that the above table does not inform a reader of whether 0:0, 4:5, 0:5, or 4:0
are the original 0-cells. Note also that the end result does not differ.

The writing portion may experience similar efficiencies as the read portion,
again by use of a list.

We may observe that for every row we tare, future column tares do NOT need to
re-write to that row (or vice versus if the columns are tared first).

-  0  -  -  -  -  -  -  -
0 (0) 0  0  0  0  0  0  0 <- No further writes on this row
-  0  -  -  -  -  -  -  -
-  0  -  -  -  -  -  -  -
-  0  -  -  -  -  -  -  -
-  0  -  -  -  -  -  -  -
-  0  -  -  -  -  -  -  -
-  0  -  -  -  -  -  -  -
-  0  -  -  -  -  -  -  -
   ^- Writing this column afterwards, it may skip row 1

If all the rows are written first, a list may be built simultaneously with the
row writes to inform what cells the column writes must tare. For instance, if the
state of our observation table was as follows, we can make the following
observations as the rows are iterated over and tared:

[i]   Col   Row
0     X     X
1     X     X
2     X     - <- Add '2' to the list
3     X     X
4     X     X
5     X     - <- Add '5' to the list
6     X     X
7     X     X
8     X     - <- Add '8' to the list

List contents: 2 - 5 - 8

This process will result in the minimal number of cells that the column writes
must handle.

Critically, this write methodology ensures that no rewrites will occur, with one
exception.

Unfortunately, there is no means by which to avoid writing to a cell whose
contents were inferred (see minimal scan strategy above), but not observed.
In the worst case, O( n^2 ) write operations must still take place, representing
a significant amount of overwork for the original worst case scenario of a fully
0-celled matrix.

Philosophically, this makes sense: We cannot ensure that we have arrived at the
correct state without either looking at or touching all of the cells.



//-----------------------------------------------------------------------------|
// TIME COMPLEXITY
//-----------------------------------------------------------------------------|

The worst-case read (no 0-cells) may be accomplished on the order of:

O( n^2 )

However, this leads to the best-case write on the order of:

O( n ) - The list of writeable rows and columns is 0, no writes occur, although
it requires 2n scans of the row/column tally to confirm this.

The best-case read (diagonal 0-cells discovered) may be accomplished on the order of:

O( n )

Which leads to the worst-case write on the order of:

O( n^2 )



//-----------------------------------------------------------------------------|
// PSEUDOLOGIC
//-----------------------------------------------------------------------------|

|--------------------------------------|
| READ:
|--------------------------------------|
1ST PRIORITY
For each row
  Check prime columns
    If a 0-cell is found, mark its coordinates in the tally table
    Remove this column from list of prime columns
    break
Rows completed
   -  P  -  -  -  P  P  P - Prime   Col
-  X  X  X  X  0  ?  ?  ?           4
P  X  X  X  X  ?  X  X  X           -
-  X  X  0  ?  ?  ?  ?  ?           2
P  X  X  ?  X  ?  X  X  X           -
-  0  ?  ?  ?  ?  ?  ?  ?           0
P  ?  X  ?  X  ?  X  X  X           -
-  ?  X  ?  0  ?  ?  ?  ?           3
P  ?  X  ?  ?  ?  X  X  X           -

   4  -  2  6  0  -  -  -

2ND PRIORITY
For every row where a 0-cell was found
  Read prime columns from highest index back to 0-cell

   -  P  -  -  -  P  P  P - Prime   Col
-  X  X  X  X  0  X  X  X           4
P  X  X  X  X  ?  X  X  X           -
-  X  X  0  -  -  X  X  X           2
P  X  X  ?  X  ?  X  X  X           -
-  0  X  -  -  -  X  X  X           0
P  ?  X  ?  X  ?  X  X  X           -
-  ?  X  -  0  -  X  X  X           3
P  ?  X  ?  ?  ?  X  X  X           -

   4  -  2  6  0  -  -  -

3RD PRIORITY
For every column where a 0-cell was found
  Read prime rows from highest index back to 0-cell

   -  P  -  -  -  P  P  P - Prime   ColHits
-  X  X  X  X  0  X  X  X           4
P  X  X  X  X  X  X  X  X           -
-  X  X  0  -  -  X  X  X           2
P  X  X  X  X  X  X  X  X           -
-  0  X  -  -  -  X  X  X           0
P  X  X  X  X  X  X  X  X           -
-  ?  X  -  0  -  X  X  X           3
P  X  X  X  X  X  X  X  X           -

P  4  -  2  6  0  -  -  - RowHits
r
i
m
e

|--------------------------------------|
| WRITE:
|--------------------------------------|
For every writable row
  Tare the row
  Remove the row from the writable column
For every writable column
  Tare the remaining elements



//-----------------------------------------------------------------------------|
// CODE (C++)
//-----------------------------------------------------------------------------|
*/
// Compile with:
// $ g++ --std=c++11 01_08_ZeroMatrix.cpp -o ZeroMatrix
// Run with:
// $ ./ZeroMatrix

#include <string>
#include <iostream>
#include <iomanip> // For setw
#include <random> // For random number generation

#define WIDTH 10
#define HEIGHT 10

int MATRIX[ WIDTH ][ HEIGHT];

// (+) --------------------------------|
// #printMatrix( )
// ------------------------------------|
// Desc:    Print a matrix
// Params:  None
// PreCons: None
// PosCons: None
// RetVal:  None
void printMatrix( ) {
   int yDim = HEIGHT;
   int xDim = WIDTH;
   // For rows 0 to MAX...
   for( int row = 0 ; row < yDim ; row++ ) {
      // Print column 0 to MAX
      for( int col = 0 ; col < xDim; col++ ) {
         std::cout << std::setw( 3 ) << MATRIX[ col ][ row ] << " ";
      }
      std::cout << std::endl << std::endl;
   }
}

// (+) --------------------------------|
// #zeroMatrix( )
// ------------------------------------|
// Desc:    Expands the 0s in a matrix
// Params:  None
// PreCons: None
// PosCons: None
// RetVal:  None
void zeroMatrix( ) {
   // READ
   // Generate tally arrays and initialize them to false
   bool rowContainsZero[HEIGHT];
   for( int i = 0 ; i < HEIGHT ; i++ ) {
      rowContainsZero[i] = false;
   }
   bool colContainsZero[WIDTH];
   for( int i = 0 ; i < WIDTH ; i++ ) {
      colContainsZero[i] = false;
   }

   // For every row...
   for( int y = 0 ; y < HEIGHT ; y++ ) {
      // Check each column cell for a zero
      for( int x = 0 ; x < WIDTH ; x++ ) {
         if( MATRIX[x][y] == 0 ) {
            rowContainsZero[y] = true;
            colContainsZero[x] = true;
         }
      }
   } // Closing for - Matrix scanned, row and col tallies loaded

   // WRITE
   // Write all columns
   for( int x = 0 ; x < WIDTH ; x++ ) {
      if( colContainsZero[x] == true ) {
         for( int y = 0 ; y < HEIGHT ; y++ ) {
            MATRIX[x][y] = 0;
         }
      }
   } // Closing for - All columns zeroed

   // Write all rows
   for( int y = 0 ; y < HEIGHT ; y++ ) {
      if( rowContainsZero[y] == true ) {
         for( int x = 0 ; x < WIDTH ; x++ ) {
            MATRIX[x][y] = 0;
         }
      }
   } // Closing for - All rows zeroed
} // Closing zeroMatrix()



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
   std::cout << "Test of zeroMatrix( )" << std::endl;
   int xDim = WIDTH;
   int yDim = HEIGHT;

   // For row 0 to MAX
   for( int row = 0 ; row < yDim ; row++ ) {
      for( int col = 0 ; col < xDim ; col++ ) {
         MATRIX[ col ][ row ] = ( rand( ) % 20 );
      }
   }
   printMatrix( );

   std::cout << "ZeroMatrix()..." << std::endl << std::endl;
   zeroMatrix( );

   printMatrix( );

   return( 0 );
} // Closing main( int, char* )

// End of file 01_08_ZeroMatrix.cpp

#include <iostream>

// Returns the number of distinct pairs in an array adding up to value 'K'
// Assumes the array has been sorted by the time it reaches here
int numberOfPairs( int* array, int size, int tgtsum ) {
  int pairCount = 0;
  int indexHi = ( size - 1 );
  int indexLow = 0;
  while( indexHi > indexLow ) {
    int result = array[indexHi] + array[indexLow];

    if( result == tgtsum ) {
      pairCount++;
      int currValHi = array[ indexHi ];
      indexHi--;
      while( array[ indexHi ] == currValHi ) {
        indexHi--;
      }
    }

    else if( result > tgtsum ) {
      // Move the top down
      int currValHi = array[ indexHi ];
      indexHi--;
      while( array[ indexHi ] == currValHi ) {
        indexHi--;
      }
    }
    
    else if( result < tgtsum ) {
      // Move the bottom up
      int currValLow = array[ indexLow ];
      indexLow++;
      while( array[ indexLow ] == currValLow ) {
        indexLow++;
      }
    }
    
  } // All unique values summed and compared against K, matches tallied

  return( pairCount );
}

// To execute C++, please define "int main()"
int main() {

  int array[10];
  for( int i = 0 ; i < 10 ; i++ ) {
    array[i] = 90 + i;
  }
  
  for( int i = 0 ; i < 10 ; i++ ) {
    std::cout << array[i] << " ";
  }
  
  std::cout << std::endl;
  
  // Test of numberOfPairs
  int result = numberOfPairs( array, 10, 189 );
  std::cout << "Result: " << result << std::endl;

  
  
  
  
  return 0;
}

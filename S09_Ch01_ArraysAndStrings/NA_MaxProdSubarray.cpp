#include <iostream> // For cout
#include <iomanip> // For precision
#include <vector> //  For vector<T>
#include <random> // For rand()
#include <algorithm> // For max()

void printVector( std::vector<float>& vec );
float maxProdSubarray( std::vector<float> vec );

int main() {
  std::cout << "Hello, World!" << std::endl;

  std::cout << std::setprecision( 5 );
  // Declare and load 'numElements' sequential integers into the vector
  std::vector<float> vec;
  int numElements = 10;
  for( int i = 0 ; i < numElements ; i++ ) {
    vec.push_back( i * 0.5 );
  }
  
  // Print the contents of the vector
  printVector( vec );
  std::cout << std::endl;
  
  
  
  
  
  std::vector<float> vecRand;
  for( int i = 0 ; i < 20 ; i++ ) {
    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    vecRand.push_back( r * 2 );
  }
  
  printVector( vecRand );
  std::cout << std::endl << std::endl;
  
  float maxProd = maxProdSubarray( vecRand );
  std::cout << std::setprecision( 5 ) << "Max prod == " << maxProd << std::endl;
  
  return 0;
}

// Returns the maximal sum subarray, prints the index at which it occurs
float maxProdSubarray( std::vector<float> vec ) {
  float maxProd = vec[0];
  float endProd = vec[0];
  int maxProdIndex = 0;
  std::cout << "0" << " : " << endProd << std::endl;

//  i   == 0   1   2   3   4   5   6
//  vec == 1  .5  .5  .5  4  5  -10
//  end == 0  1  3  6  10 15 5

  // Starting at index 1
  for( int i = 1 ; i < (signed)vec.size() ; i ++ ) {
    // Calculate the current maximum product ending on this index
    endProd = std::max( vec[i] * endProd, vec[i] );
    std::cout << i << " : " << endProd << std::endl;

    // Maintain the highest product seen so far
    maxProd = std::max( endProd, maxProd );
    // Record the index, if necessary
    if( maxProd == endProd ) {
      maxProdIndex = i;
    }
  }
  
  std::cout << "maxProdIndex: " << maxProdIndex << std::endl;
  return( maxProd );
}

void printVector( std::vector<float>& vec) {
  for( float i : vec ) {
    std::cout << std::setprecision( 5 ) << i << " ";
  }
}

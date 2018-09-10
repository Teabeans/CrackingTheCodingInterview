#include <iostream> // For cout
#include <vector> //  For vector<T>
#include <random> // For rand()
#include <algorithm> // For max()

void printVector( std::vector<int>& vec );
int maxSumSubarray( std::vector<int> vec );

int main() {
  std::cout << "Hello, World!" << std::endl;

  // Declare and load 'numElements' sequential integers into the vector
  std::vector<int> vec;
  int numElements = 10;
  for( int i = 0 ; i < numElements ; i++ ) {
    vec.push_back( i );
  }
  
  // Print the contents of the vector
  printVector( vec );
  std::cout << std::endl;
  
  std::vector<int> vecRand;
  for( int i = 0 ; i < 100 ; i++ ) {
    vecRand.push_back( (std::rand() % 100) - 50 );
  }
  
  printVector( vecRand );
  std::cout << std::endl << std::endl;
  
  int maxSum = maxSumSubarray( vecRand );
  std::cout << "Max sum == " << maxSum << std::endl;
  
  return 0;
}

// Returns the maximal sum subarray, prints the index at which it occurs
int maxSumSubarray( std::vector<int> vec ) {
  int maxSum = vec[0];
  int maxSumIndex = vec[0];
  int endSum = vec[0];

//  i   == 0  1  2  3  4  5  6
//  vec == 0  1  2  3  4  5  -10
//  end == 0  1  3  6  10 15 5

  // Starting at index 1
  for( int i = 1 ; i < (signed)vec.size() ; i ++ ) {
    // Calculate the current maximum sum ending on this index
    endSum = std::max( vec[i] + endSum, vec[i] );
    // Maintain the highest sum seen so far
    maxSum = std::max( endSum, maxSum );
    // Record the index, if necessary
    if( maxSum == endSum ) {
      maxSumIndex = i;
    }
  }  
  std::cout << "maxSumIndex: " << maxSumIndex << std::endl;
  return( maxSum );
}

void printVector( std::vector<int>& vec) {
  for( int i : vec ) {
    std::cout << i << " ";
  }
}

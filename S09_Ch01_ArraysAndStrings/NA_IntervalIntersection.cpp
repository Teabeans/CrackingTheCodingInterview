#include <iostream> // For cout
#include <iomanip> // For precision
#include <vector> //  For vector<T>
#include <random> // For rand()
#include <algorithm> // For max()

void printVector( std::vector<float>& vec );
float maxProdSubarray( std::vector<float> vec );

int main() {
   
}



vector<int> intersectionOfTwoIntervals( vector<int> A, vector<int> B ) {
   vector<int> retVector;
   if( A[0] >= B[1] || A[1] <= B[0] ) {
      return( retVector );
   }

   int L = max( A[0], B[0] );
   int R = min( A[1], B[1] );

   retVector.push_back( L );
   retVector.push_back( R );

   return( retVector );
}

vector<vector<int>> intersectionOfTwoIntervalSets( vector<vector<int>> Aset, vector<vector<int>> Bset ) {
   int aCurrIndex = 0;
   int bCurrIndex = 0;
   vector<int> aCurr = Aset[aCurrIndex];
   vector<int> bCurr = Bset[bCurrIndex];
   vector<vector<int>> retVector;
   
   if ( Aset.size( ) == 0 || Bset.size( ) == 0 ) {
      return( retVector );
   }

   // While we have A comparisons to make...
   while( aCurrIndex < Aset.size( ) - 1 ) {
      // Assign the current A vector
      aCurr = Aset[ aCurrIndex ];

      // While B's right is less or equal to A's right
      while( bCurr[1] >= aCurr[1] ) {
         bCurr = Bset[ bCurrIndex ];
         vector<int> result = intersectionOfTwoIntervals( aCurr, bCurr );
         if( result.size( ) == 0 ) {
            // Do nothing
         }
         else {
            retVector.push_back( result );
         }
         bCurrIndex++
      } // Closing while - All valid B intervals compared for this A interval

      aCurrIndex++;
   }

   return( retVector );

}

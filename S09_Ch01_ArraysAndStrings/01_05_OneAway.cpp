//-----------------------------------------------------------------------------|
// Authorship
//-----------------------------------------------------------------------------|
//
// Tim Lum
// twhlum@gmail.com
// Created:  2018.07.23
// Modified: 2018.08.21
//

/*
1.5 - OneAway() - P.91
There are three types of edits that can be performed on strings: insert a character,
remove a character, or replace a character. Given two strings, write a function
to check if they are one edit (or zero edits) away.



//-----------------------------------------------------------------------------|
// PROBLEM SETUP AND ASSUMPTIONS
//-----------------------------------------------------------------------------|

A string may be represented as an array or linked list of chars.
  Many languages also support the string as a class
In the case of zero edits:
  - The string length and contents must be the same
In the case of an insertion or removal:
  - The lengths will differ by one
    - If it is longer, only one character may differ
    - If it is shorter, only one character may differ
In the case of a replacement:
  - The lengths must be the same, but one character may differ



//-----------------------------------------------------------------------------|
// NAIVE, BRUTE FORCE, TERRIBAD APPROACH
//-----------------------------------------------------------------------------|

Iterate down the two strings until a difference is detected
Utilize a series of if-then clauses to ascertain what type of difference is
being observed. Adjust one pointer accordingly and continue iterating down the
string until the end is reached (true) or another difference is detected (false)



//-----------------------------------------------------------------------------|
// OPTIMIZATIONS
//-----------------------------------------------------------------------------|

Observing that the prefix and suffix of the edit must be the same...
  - We may iterate from both the front and the rear of the string to determine where a delta(s) occurs
  - If the delta locations as detected from the front and rear are at different
    locations, then more than one edit is present.

Scanning from front and back for 2 or more edits case:
A B C D E F G
A B X X E F G
^           ^ - Start at front and end
    ^ ^       - Deltas found at index 2 and 3, more than 1 delta detected

Scanning from front for removal case:
A B C D E F G
A B D E F G
    ^ == Index 2

Scanning from back for removal case:
A B C D E F G
  A B D E F G
    ^ == Index 2

Delta detected at index 2 (front) and 2 (rear) - therefore one change

Scanning from front for insertion case (note that an insertion is the same as removal, but flipped)
A B C D E F G
A B C X D E F G
      ^ == Index 3

Scanning from back for insertion case
  A B C D E F G
A B C X D E F G
      ^ == Index 3

Delta detected at index 3 (front) and 3 (rear) - therefore one change

Scanning from front for replacement case
A B C D E F G
A B C X E F G
      ^ == Index 3

Scanning from back for replacement case
A B C D E F G
A B C X E F G
      ^ == Index 3

Delta detected at index 3 (front) and 3 (rear), therefore one change



//-----------------------------------------------------------------------------|
// TIME COMPLEXITY
//-----------------------------------------------------------------------------|

As the detection of one or two deltas may be achieved in a single pass across
both strings, we may expect this approach to complete in a time complexity of:

O( n )

Where 'n' is the length of the strings to search over.

It bears mention that this approach may complete substantially faster if the
edit locations are near to the head and tail of the string, with a best-case
scenario of the first and last characters differing.



//-----------------------------------------------------------------------------|
// PSEUDOLOGIC
//-----------------------------------------------------------------------------|

Compare string lengths for equivalence (+/- 1)
If the strings differ, label the longer and shorter
If the strings do not differ, arbitrarily label the longer and shorter
  Scan the two strings from the front and back, searching for a delta
Compare the delta locations
  If the front and rear deltas match, return true
  Otherwise return false



//-----------------------------------------------------------------------------|
// CODE (C++)
//-----------------------------------------------------------------------------|
*/
// Compile with:
// $ g++ --std=c++11 01_05_OneAway.cpp -o OneAway
// Run with:
// $ ./OneAway

#include <string>
#include <iostream>
#include <cmath>

// (+) --------------------------------|
// #oneAway( string, string )
// ------------------------------------|
// Desc:    Determines whether two strings are a single edit away from each other or not
// Params:  string arg1 - The first string to compare
//          string arg2 - The second string to compare
// PreCons: None
// PosCons: None
// RetVal:  bool true - The received strings are one (or zero) edits away from each other
//          bool false - The received strings are more than one edit from each other
bool oneAway( std::string string1, std::string string2 ) {
   // If the absolute difference between string1 and string2 is 2 or greater
   if ( abs( (string1.length( ) - string2.length( ) ) ) >= 2 ) {
      std::cout << "Excess edits detected by string length" << std::endl;
      // No single edit could yield this, therefore...
      return( false );
   }

   // Otherwise, establish a longer and shorter string
   std::string longer;
   std::string shorter;
   if( string1.length( ) >= string2.length( ) ) { // Note: Includes the equality case
      longer = string1;
      shorter = string2;
   }
   else {
      longer = string2;
      shorter = string1;
   }

   // Declare two variables to hold the delta locations (if any)
   int deltaFront = -1;
   int deltaRear  = -1;

   // Declare variable for number of comparisons to make
   int numComparisons = shorter.length( );

   // Begin traversing the strings looking for differences

   // Comparison from front
   for( int i = 0 ; i < numComparisons ; i++ ) {
      if( longer.at( i ) != shorter.at( i ) ) {
         deltaFront = i;
         break;
      }
   }

   std::cout << "DeltaFront @ [ " << deltaFront << " ]" << std::endl;

   if( deltaFront == -1 ) {
      // No deltas were detected
      return( true );
   }

   // Comparison from rear
   int shortIndex = shorter.length( );
   int longIndex = longer.length( );
   for( int i = 0 ; i < numComparisons ; i++ ) {
      shortIndex--;
      longIndex--;
      if( longer.at( longIndex ) != shorter.at( shortIndex ) ) {
         deltaRear = longIndex;
         break;
      }
   }

   std::cout << "DeltaRear  @ [ " << deltaRear << " ]" << std::endl;

   // Delta location from front and rear acquired

   if ( deltaFront != deltaRear ) {
      return( false );
   }
   // Otherwise...
   return( true );

} // Closing OneAway()



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
   std::cout << "Test of oneAway( )" << std::endl;
   bool test1 = oneAway( "This is a subtract", "This is  subtract" );
   bool test2 = oneAway( "ABCDEFG", "XBCDEFX" );
   bool test3 = oneAway( "This is an append", "This is an append!" );
   std::cout << "Test 1 : ( 1 expected )" << std::endl;
   std::cout << "           " << test1 << std::endl << std::endl;
   std::cout << "Test 2 : ( 0 expected )" << std::endl;
   std::cout << "           " << test2 << std::endl << std::endl;
   std::cout << "Test 3 : ( 1 expected )" << std::endl;
   std::cout << "           " << test3 << std::endl << std::endl;
   return( 0 );
} // Closing main( int, char* )

// End of file 01_05_OneAway.cpp

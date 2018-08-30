//-----------------------------------------------------------------------------|
// Authorship
//-----------------------------------------------------------------------------|
//
// Tim Lum
// twhlum@gmail.com
// Created:  2018.08.28
// Modified: 2018.08.29
//

/*
1.9 - StringRotation() - P.91
Assume you have a method isSubstring which checks if one word is a substring of
another. Given two strings s1 and s2, write code to check if s2 is a rotation of
s1 using only one call to isSubstring.

e.g. "waterbottle" is a rotation of "erbottlewat"



//-----------------------------------------------------------------------------|
// PROBLEM SETUP AND ASSUMPTIONS
//-----------------------------------------------------------------------------|

A string may be represented as an array or linked list of chars.
  Many languages also support the string as a class
A 'rotation' is achieved by moving the first character to the end position or
vice versus an unspecified number of times.
Two matching strings count as a rotation (ie. a "full" rotation)
Rotations do not contain a direction. For instance:
  WATERBOTTLE => BOTTLEWATER may represent
    Either (5) letters moved from front to back
    OR (6) letters moved from back to front



//-----------------------------------------------------------------------------|
// NAIVE APPROACH
//-----------------------------------------------------------------------------|

Treat every character in String1 as a starting point, then iterate across all
characters in String1 to see if a match can be found against String2.

D E F A B C <- Compare against this
A B C D E F
^ - Start here

DEFABC vs ABCDEF (No match!)

A B C D E F
  ^ - Start here

DEFABC vs BCDEFA (No match!)

A B C D E F
    ^ - Start here

DEFABC vs CDEFAB (No match!)

A B C D E F
    ^ - Start here

DEFABC vs DEFABC (Match!)

This solution operates, in the worst case, with a time complexity of:

O( n^2 )

Where 'n' reflects the number of characters in the strings.



//-----------------------------------------------------------------------------|
// OPTIMIZATIONS
//-----------------------------------------------------------------------------|

Observing first that two strings of differing lengths cannot be rotations of one
another, any two strings of differing lengths need not perform a comparison. They
may merely return (false).

Additionally, we may observe that doubling a rotated string may yield the original
unrotated string as a subset.

BOTTLEWATER, for instance, when doubled, becomes BOTTLE WATERBOTTLE WATER (spaces
added for clarity).

If we are doubling String1, then it is now possible to pass the comparison string
String2 to isSubstring(). If isSubstring() returns true, then S1 and S2 share a
rotational relationship with one another.

An additional memory savings might be realized by repeatedly "rotating" String1 in
the following fashion so as to avoid rewriting the string to twice its original
size:

Using the hypothetical (true) case below:

String1 == A B C A B C A B C D
String2 == A B C D A B C A B C

We begin by looking for a common feature (in this case, the first char of String2)

String1 == A B C A B C A B C D
           ^ Found a feature!
String2 == A B C D A B C A B C
           ^ Trying to match this

If no such common feature is found in 'N' observations, then no rotational
relationship exists

We may then attempt to iterate across both strings seeking a match of length N

String1 == A B C A B C A B C D
           ^ ^ ^ !
String2 == A B C D A B C A B C
           ^ ^ ^ !

If a mismatch occurs, we shift the sought-after feature of String2 and again look
for a matching feature in String1

String1 == A B C A B C A B C D
                 ^ ^ ^ ^ ^ ^ ^ Found a feature!
String2 == A B C D A B C A B C
                 ^ Reset to here

This process continues until 'N' uninterrupted matches are found between String1
and String2
OR
String2 exhausts its supply of features

String1 == A B C A B C A B C D
                       ^ Found a feature!
String2 == A B C D A B C A B C
           ^ Reset to here



//-----------------------------------------------------------------------------|
// TIME COMPLEXITY
//-----------------------------------------------------------------------------|

Either approach (doubling or iterative comparisons) shall complete in:

O( n )

Where 'n' is the number of characters in the string



//-----------------------------------------------------------------------------|
// PSEUDOLOGIC
//-----------------------------------------------------------------------------|

Compare string lengths for equality
Double String1
Call isSubstring on doubled string and String2
Return result



//-----------------------------------------------------------------------------|
// CODE (C++)
//-----------------------------------------------------------------------------|
*/
// Compile with:
// $ g++ --std=c++11 01_09_StringRotation.cpp -o StringRotation
// Run with:
// $ ./StringRotation

#include <iostream>
#include <string>

// NOTE: string.find(string) performs a similar function to isSubstring()
// It returns -1 on failure, but because its return type is unsigned, this value
// shall be the maximum integer value possible unless assigned to a signed int.

// (+) --------------------------------|
// #stringRotation( string )
// ------------------------------------|
// Desc:    Determines whether two strings are rotations of one another or not
// Params:  string arg1 - The first string to compare
//          string arg2 - The second string to compare
// PreCons: None
// PosCons: None
// RetVal:  bool true - The received strings are rotations of each other
//          bool false - The received strings are not rotations of each other
bool stringRotation( std::string string1, std::string string2) {
   // Compare string lengths for equality
   if ( string1.length( ) != string2.length( ) ) {
      return( false );
   }

   std::string dblString = string1 + string1;
   // The search (isSubstring( ))
   int retVal = dblString.find( string2 );
   // If string2 was not found within the doubled string...
   if( retVal == -1 ) {
      return( false );
   }
   // Otherwise...
   else {
      return( true );
   }

} // Closing stringRotation()



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
   std::cout << "Test of stringRotation( )" << std::endl << std::endl;

   std::string tuple1_0 = "WATERBOTTLE";
   std::string tuple1_1 = "BOTTLEWATER";

   std::cout << "Tuple1_0: " << tuple1_0 << std::endl;
   std::cout << "Tuple1_1: " << tuple1_1 << std::endl;
   std::cout << "Tuple1_0 vs Tuple1_1 (1 expected):" << std::endl;
   bool judgement = stringRotation( tuple1_0, tuple1_1 );
   std::cout << judgement << std::endl << std::endl;

   std::string tuple2_0 = "AGAMEMNON";
   std::string tuple2_1 = "HERCULES!";

   std::cout << "Tuple2_0: " << tuple2_0 << std::endl;
   std::cout << "Tuple2_1: " << tuple2_1 << std::endl;
   std::cout << "Tuple2_0 vs Tuple2_1 (0 expected):" << std::endl;
   judgement = stringRotation( tuple2_0, tuple2_1 );
   std::cout << judgement << std::endl << std::endl;

   return( 0 );
} // Closing main( int, char* )

// End of file 01_09_stringRotation.cpp

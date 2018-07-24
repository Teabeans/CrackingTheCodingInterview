//-----------------------------------------------------------------------------|
// Authorship
//-----------------------------------------------------------------------------|
//
// Tim Lum
// twhlum@gmail.com
// Created:  2018.07.23
// Modified: 2018.07.23
//

/*
1.5 - OneAway() - P.91
There are three types of edits that can be performed on strings: insert a character, remove a character, or replace a character. Given two strings, write a function to check if they are one edit (or zero edits) away.

Problem Setup and Assumptions:
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

Naive Approach:
  Write a series of if-then switches to determine the length of the strings
    Then determine the nature of the difference

Optimizations:
  - Observing that the prefix and suffix of the edit must be the same
    - We may iterate from both the front and the rear of the string to determine where the delta occurs
    - If more than one delta is observed, then we must be more than one edit away

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

Pseudo Logic:
  Compare string lengths for equivalence (+/- 1)
  If the strings differ, label the longer and shorter
  If the strings do not differ, arbitrarily label the longer and shorter
    Scan the two strings from the front and back, searching for a delta
  Compare the delta locations
    If the front and rear deltas match, return true
    Otherwise return false


Code (C++):
*/

#include <string>

// (+) --------------------------------|
// #OneAway(string, string)
// ------------------------------------|
// Desc:    Determines whether two strings are a single edit away from each other or not
// Params:  string arg1 - The first string to compare
//          string arg2 - The second string to compare
// PreCons: None
// PosCons: None
// RetVal:  bool true - The received strings are one (or zero) edits away from each other
//          bool false - The received strings are more than one edit from each other
bool OneAway(string string1, string string2) {
   // If the absolute difference between string1 and string2 is 2 or greater
   if ( |(string1.length( ) - string2.length( )| ) >= 2 ) {
      // No single edit could yield this, therefore...
      return( false );
   }

   // Otherwise
   string longer;
   string shorter;
   if (string1.length() >= string2.length()) { // Note: Includes the equality case
      longer = string1;
      shorter = string2;
   }
   else {
      longer = string2;
      shorter = string1;
   }

   // Begin traversing the strings looking for differences
   int deltaFront;
   int deltaRear;
   // Comparison from front
   for (int i = 0 ; i < shorter.length() ; i++) {
      if (longer.at(i) != shorter.at(i)) {
         deltaFront = i;
      }
   }

   // Comparison from rear
   int shortIndex;
   int longIndex;
   for (int i = 0 ; i < shorter.length() ; i++ ) {
      shortIndex = shorter.length() - i;
      longIndex = longer.length() - i;
      if (longer.at(longIndex) != shorter.at(shortIndex) {
         deltaRear = longIndex;
      }
   }

   // Delta location from front and rear acquired

   if (deltaFront != deltaRear) {
      return (false);
   }
   // Otherwise...
   return (true);

} // Closing OneAway()

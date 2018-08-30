//-----------------------------------------------------------------------------|
// AUTHORSHIP
//-----------------------------------------------------------------------------|
//
// Tim Lum
// twhlum@gmail.com
// Created:  2018.08.30
// Modified: 2018.08.30
//

/*
2.1 - removeDups( ) - P.94
Write code to remove duplicates from an unsorted linked list.

Extension: How would you solve this problem if a temporary buffer is not allowed?



//-----------------------------------------------------------------------------|
// PROBLEM SETUP AND ASSUMPTIONS
//-----------------------------------------------------------------------------|

A 'duplicate' shall be defined as a distinct node containing a duplicate value
  Having a logically duplicated node will result in a loop

More than 1 duplicate may exist in quantities greater than 2 (e.g. triplicates)

While a length field may be maintained within the Linked List class, for the
purposes of this problem, this shall be ignored. Length is assumed to be unknown.



//-----------------------------------------------------------------------------|
// OBSERVATIONS AND INFERENCES
//-----------------------------------------------------------------------------|

Every node in the list must be observed at least once to determine whether a
duplicate exists. We may not solve this problem in faster than an O( n ) time
complexity.



//-----------------------------------------------------------------------------|
// NAIVE, BRUTE FORCE, TERRIBAD APPROACH
//-----------------------------------------------------------------------------|

For every node, scan the entirety of the remaining list, removing any duplicates.

OR

For every node, scan the list from start to the current node, deleting duplicates.

Either strategy will complete in O( n^2 ) time.



//-----------------------------------------------------------------------------|
// OPTIMIZATIONS
//-----------------------------------------------------------------------------|

Ideally, we would like a means to determine whether the current node contains
a value we have seen previously. While the Linked List does contain this information
(within the list itself), access requires iteration through the either the list
remainder (suffix) or the list prior (prefix)

A hash table can provide an O( 1 ) lookup of previously encountered values.



//-----------------------------------------------------------------------------|
// TIME COMPLEXITY
//-----------------------------------------------------------------------------|

Utilizing a hash table, this function can complete in a time complexity of:

O( n )

Where 'n' corresponds to the length of the list



//-----------------------------------------------------------------------------|
// PSEUDOLOGIC
//-----------------------------------------------------------------------------|

Generate a hashtable of previously encountered elements

For every node
  Check if the node value exists in the hash table
  If it does, remove it from the list
  If it does not, add it to the hash table



//-----------------------------------------------------------------------------|
// CODE (C++)
//-----------------------------------------------------------------------------|
*/

#include <02_00_LinkedList.cpp>
#include <iostream>
#include <string>
#include <stringstream>
#include <iomanip>
#include <random>

// (+) --------------------------------|
// #removeDups(arg1)
// ------------------------------------|
// Desc:    Removes duplicate nodes from an unsorted linked list
// Params:  LinkedList arg1 - The list to prune
// PreCons: Assumes node values are in range 0 to 1000 (inclusive)
// PosCons: Successive duplicate nodes have been trimmed from the list
// RetVal:  None
void removeDups( LinkedList tgtList ) {
   bool hasBeenSeen[1001];
   for( int i = 0 ; i <= 1001 ; i++ ) {
      hasBeenSeen[i] = false;
   }
   nodeLL currNode = tgtList.head->next; // Load the first valid node of the list
   while( currNode->isSentinel == false ) {
      if ( hasBeenSeen[currNode.value] == true ) {
         std::cout << "Removing ( " << currNode.value << " )" << std::endl;
         nodeLL tempNodePtr = currNode.next;
         <remove currNode from list>
         currNode = tempNodePtr;
      }
      else if ( hasBeenSeen[currNode.value] == false ) {
         hasBeenSeen[currNode.value] = true;
         currNode = currNode.next;
      }
   } // Closing while - All nodes have been traversed
} // Closing removeDups( )



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
   std::cout << "Test of removeDups( ):" << std::endl << std::endl;

   std::cout << "Instantiating list..." << std::endl;
   LinkedList testList = LinkedList( );
   for( int i = 0 ; i < 100; i++ ) {
      int currVal = rand( 1001 );
      testList.insert( currVal );
   }
   testList.print( );

   std::cout << "Testing removeDups( )..." << std::endl;

   removeDups( testList );

   testList.print( );

   return( 0 );
} // Closing main( int, char* )

// End of file - 02_01_RemoveDups.cpp

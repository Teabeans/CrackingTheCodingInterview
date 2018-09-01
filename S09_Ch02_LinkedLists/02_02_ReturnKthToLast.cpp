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
2.2 - returnKthToLast( ) - P.94
Implement an algorithm to find the kth to last element of a single linked list.



//-----------------------------------------------------------------------------|
// PROBLEM SETUP AND ASSUMPTIONS
//-----------------------------------------------------------------------------|

Given a list:
0 - 1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9

The Kth to last position is represented by
0 - 1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 <- Sequence
9 - 8 - 7 - 6 - 5 - 4 - 3 - 2 - 1 - 0 <- Kth to last

Primarily, the problem lays in our inability to backtrack once the end of the
list has been found.



//-----------------------------------------------------------------------------|
// OBSERVATIONS AND INFERENCES
//-----------------------------------------------------------------------------|

Given that any solution must at least ascertain where the end of the list is,
it is unlikely that a solution can be found in a faster time complexity than:

O( n )

//-----------------------------------------------------------------------------|
// NAIVE, BRUTE FORCE, TERRIBAD APPROACH
//-----------------------------------------------------------------------------|

Traverse the list once to ascertain its length, then perform the appropriate
algebra to determine the number of traversals needed to land on the "Kth to last"
node. Traverse the list again this number of times and return the node.



//-----------------------------------------------------------------------------|
// OPTIMIZATIONS
//-----------------------------------------------------------------------------|

While using a runner technique may seem like an optimization:
  Establish a trailing runner that iterates K steps behind the forward runner
  When the forward runner runs off the end of the list...
  The trailing runner indicates the appropriate node to return.

Unfortunately, this strategy is exactly the same as the naive approach,
requiring O( 2n ) time to complete. Whether we increment through the list twice
with a single pointer or once with two pointers is quite immaterial to how long
it takes to complete.

Additionally, counting from the back (as in a recursive solution utilizing the
call stack) also appears to be an optimization, but cannot be relied on without
knowing if K is likely to be 'large' or 'small' relative to the list length.

Not only does the call stack incur potentially significant time and space
penalties, it isn't even guaranteed to run faster than multiple iterations over
the list (e.g. - Where N is approximately equal to K, we'd have to backtrack
over the list again to find a solution).

What is required is a means by which we may return to a node in a time faster
than O( n ) in the worst case.

Storing the node addresses to a hash table would allow this:
Index:   Node (Cardinal value):
[0]      0
[1]      1
[2]      2
etc.

At the end of the first iteration, we would have enough information to know:
1) The length of the list
2) The cardinal position of the kth to last element
3) The address of that element (or more specifically, the one just prior)

//-----------------------------------------------------------------------------|
// TIME COMPLEXITY
//-----------------------------------------------------------------------------|

This function can complete its read in a time complexity of:

O( n )

The identification and return of the node  may be completed in a time complexity of:

O( 1 )



//-----------------------------------------------------------------------------|
// PSEUDOLOGIC
//-----------------------------------------------------------------------------|

Generate a hashtable of node addresses
Iterate across the list, populating the address table
When the end is determined, ascertain the node number to remove
Consult the address table to locate the address of that node
Remove the node



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
// #returnKthToLast( LinkedList, int )
// ------------------------------------|
// Desc:    Removes the Kth to last element of a Linked List
// Params:  LinkedList arg1 - The list to remove from
//          int arg2 - The value 'K', a cardinal position from the list's end
// PreCons: None
// PosCons: The Kth to last element has been removed
// RetVal:  None
void returnKthToLast( LinkedList tgtList, int K ) {
   // Generate an address table
   nodeLL* addressTable[1000];
   int nodeNumber = 0;
   nodeLL* currNode = tgtList.head->next;
   while( currNode != nullptr ) {
      addressTable[nodeNumber] = currNode;
      nodeNumber++;
   } // Closing while - List traversed, address table populated
   nodeNumber = nodeNumber - K;
   tgtList.remove( nodeNumber );
} // Closing returnKthToLast( )



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
   std::cout << "Test of returnKthToLast( ):" << std::endl << std::endl;

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

// End of file - 02_02_ReturnKthToLast.cpp

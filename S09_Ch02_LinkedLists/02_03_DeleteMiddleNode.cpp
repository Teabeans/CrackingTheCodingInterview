//-----------------------------------------------------------------------------|
// AUTHORSHIP
//-----------------------------------------------------------------------------|
//
// Tim Lum
// twhlum@gmail.com
// Created:  2018.08.31
// Modified: 2018.08.31
//

/*
2.2 - deleteMiddleNode( node* ) - P.94
Implement an algorith to delete a node in the middle (i.e. any node but the first
and last node, not necessarily the exact middle) of a singly linked list, given
only access to that node.

Example:

Input: The node 'C' from the linked list:
  A -> B -> C -> D -> E -> F

Result: Nothing is returned, but the new linked list looks like:
  A -> B -> D -> E -> F



//-----------------------------------------------------------------------------|
// PROBLEM SETUP AND ASSUMPTIONS
//-----------------------------------------------------------------------------|

In C++ nomenclature, 'delete' is a specific act of memory deallocation. This is
not the question intent (as doing so is trivial, but also breaks the linked list
data structure).



//-----------------------------------------------------------------------------|
// OBSERVATIONS AND INFERENCES
//-----------------------------------------------------------------------------|

Multiple references may point to the same address

A correctly functioning linked list need only traverse from head to tail,
encountering the correct value sequence.

All nodes are assumed to be of the same class or struct (a 'node' class)

Two nodes with identical values and next pointers are, for the intents of this
question, indistinguishable from one another (they are the 'same')



//-----------------------------------------------------------------------------|
// NAIVE, BRUTE FORCE, TERRIBAD APPROACH
//-----------------------------------------------------------------------------|

Any attempt to access prior nodes in the list will likely be futile.

Similarly, any attempt to delete the targeted node outright will immediately
break the linked list when traversed from the head.



//-----------------------------------------------------------------------------|
// OPTIMIZATIONS
//-----------------------------------------------------------------------------|

Using the original example of the list

  A -> B -> C -> D -> E -> F
            ^ Target C for 'removal'

It is possible to copy all of the information from node 'D' to node 'C'.

This results in the following:
  A -> B -> D -> E -> F
            D ---^

While a node with the contents 'D' is now floating and inaccessible in memory,
the traversal of the linked list is as desired.

The original node 'D' may be deleted prior to overwriting node 'C' if so desired



//-----------------------------------------------------------------------------|
// TIME COMPLEXITY
//-----------------------------------------------------------------------------|

This function should complete its rewrite in a time complexity of:

O( 1 )



//-----------------------------------------------------------------------------|
// PSEUDOLOGIC
//-----------------------------------------------------------------------------|

Copy all values and pointers from the target node's next node to the target.



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
void deleteMiddleNode( LinkedList tgtList, int K ) {
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
} // Closing deleteMiddleNode( )



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

// End of file - 02_03_DeleteMiddleNode.cpp

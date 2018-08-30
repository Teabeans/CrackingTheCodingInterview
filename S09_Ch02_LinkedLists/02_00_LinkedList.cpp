//-------|---------|---------|---------|---------|---------|---------|---------|
//
// 02_00_LinkedList.cpp
//
//-------|---------|---------|---------|---------|---------|---------|---------|

//-----------------------------------------------------------------------------|
// AUTHORSHIP
//-----------------------------------------------------------------------------|
//
// Tim Lum
// twhlum@gmail.com
// Created:  2018.08.30
// Modified: 2018.08.30
//

//-----------------------------------------------------------------------------|
// ACKNOWLEDGMENTS
//-----------------------------------------------------------------------------|
//
// Template author:
// Tim Lum (github.com/Teabeans/Template_Cpp)
//
// Refer to ACKNOWLEDGEMENTS.txt
//

//-----------------------------------------------------------------------------|
// FILE DESCRIPTION
//-----------------------------------------------------------------------------|
//
// Implementation file for a Linked List class, for use with Chapter 2 of
// 'Cracking the Coding Interview'. Contains both a Linked List Node (nodeLL)
// structure and a Linked List (LinkedList) structure.
//
// A nodeLL contains:
//   bool isSentinel - Denotes the first node in the list
//   nodeLL* next
//   nodeLL* prev
//   int val
//
// A LinkedList contains:
//   nodeLL head - Denotes the head or handle on the Linked List
//   int length
//   int insert( int val ) - Insert a new node with given value at end of list
//   int insertAfter( int val, nodeLL* tgt ) - Insert a new node after the target
//   int insertBefore( int val, nodeLL* tgt ) - Insert a new node before the target
//   int remove( int val ) - Remove the first node bearing the target value
//   nodeLL* find( int val ) - Locates the first node bearing the target value
//   void print( ) - Prints the Linked List to console
//   std:string toString( ) - Returns the Linked List as a string representation
//   

//-----------------------------------------------------------------------------|
// PACKAGE FILES
//-----------------------------------------------------------------------------|
//
// None
//

//-----------------------------------------------------------------------------|
// USAGE
//-----------------------------------------------------------------------------|
//
// Include in other source code with
// #include <02_00_LinkedList.cpp>
//
// For standalone compilation:
// Un-comment method main() in the DRIVER section
//
// Compile with:
// $ g++ --std=c++11 02_00_LinkedList.cpp -o LinkedList
//
// Run with:
// $ ./LinkedList
//

//-----------------------------------------------------------------------------|
// ERRATA
//-----------------------------------------------------------------------------|
//
// The sorter is implemented here as a class. This is not necessary, and code
// logic for the sort may be refactored as static methods.
//
// Random number generation is currently pseudo-random.
//

//-----------------------------------------------------------------------------|
// LICENSE
//-----------------------------------------------------------------------------|
//
// Refer to LICENSE.txt
//

//-----------------------------------------------------------------------------|
// CODE STANDARDS
//-----------------------------------------------------------------------------|
//
// Refer to CODESTANDARDS.txt
//

//-----------------------------------------------------------------------------|
// IMPORTS / INCLUDES
//-----------------------------------------------------------------------------|

// For stringstreams
#include <sstream>

// For input/output
#include <iostream>

//-------------------------------------|
struct nodeLL {
//-------------------------------------|
   bool isSentinel;
   int value;
   nodeLL* next;
   nodeLL* prev;

//-------------------------------------|
   nodeLL( ) {
      this->isSentinel = false;
      this->value = -1;
      this->next = nullptr;
      this->prev = nullptr;
   }

//-------------------------------------|
   nodeLL( int val ) {
      this->isSentinel = false;
      this->value = val;
      this->next = nullptr;
      this->prev = nullptr;
   }

//-------------------------------------|
   nodeLL( int val, nodeLL* prev, nodeLL* next ) {
      this->isSentinel = false;
      this->value = val;
      // Set the four relevant pointers to the correct targets
      this->next = next;
      this->next->prev = this;
      this->prev = prev;
      this->prev->next = this;
   }

//-------------------------------------|
   ~nodeLL( ) {
      this->isSentinel = NULL;
      this->value = -1;
      this->next = nullptr;
      this->prev = nullptr;
   }
}; // Closing struct nodeLL

//-------------------------------------|
struct LinkedList {
//-------------------------------------|
   nodeLL* head;
   int length;

   int insert( int val );
   int insertAfter( int val, nodeLL* tgt );
   int insertBefore( int val, nodeLL* tgt );
   int remove( int val );
   nodeLL* find( int val );
   void print( );
   std::string toString( );

//-------------------------------------|
   LinkedList( ) {
      this->head = new nodeLL();
      head->next = this->head;
      head->prev = this->head;
      head->value = -1;
      head->isSentinel = true;
      length = 0;
   }

//-------------------------------------|
   ~LinkedList( ) {
      nodeLL* prevNode;
      nodeLL* currNode = this->head->next;
      while (currNode->isSentinel == false) {
         prevNode = currNode;
         currNode = currNode->next;
         delete prevNode;
      } // Closing while - We've returned to the sentinel
      delete this->head;
      // Head is statically allocated, will delete when it leaves scope
   }

}; // Closing struct LinkedList

//-------------------------------------|
   nodeLL* LinkedList::find( int searchVal ) {
      nodeLL* retPtr = nullptr;
      nodeLL* currNodePtr = this->head->next;
      for (int i = 0 ; i < length ; i++ ) {
         if ( currNodePtr->value == searchVal ) {
            retPtr = currNodePtr;
            return( retPtr );
         }
      } // Closing for - all comparisons complete, value not found
      return( retPtr );
   }

//-------------------------------------|
   int LinkedList::insert( int val ) {
      // Generate the new node
      nodeLL* newNode = new nodeLL( val, this->head->prev, this->head );
      // Insertion complete, increment the length
      this->length++;
      return( this->length );
   }

//-------------------------------------|
   int LinkedList::insertAfter( int val, nodeLL* tgt ) {
      // Hold the target
      nodeLL* tgtNodePtr = this->find( val );
      if ( tgtNodePtr == nullptr ) {
         std::cout << "[insertAfter( )] - Value not found" << std::endl;
         return ( this->length );
      }
      nodeLL* newNode = new nodeLL( val, tgtNodePtr, tgtNodePtr->next );
   }

//-------------------------------------|
   int LinkedList::insertBefore( int val, nodeLL* tgt ) {
      // Hold the target
      nodeLL* tgtNodePtr = this->find( val );
      if ( tgtNodePtr == nullptr ) {
         std::cout << "[insertAfter( )] - Value not found" << std::endl;
         return ( this->length );
      }
      nodeLL* newNode = new nodeLL( val, tgtNodePtr->prev, tgtNodePtr );
   }

//-------------------------------------|
   void LinkedList::print( ) {
      std::cout << this->toString( ) << std::endl;
   }

//-------------------------------------|
   int LinkedList::remove( int val ) {
      // Attempt to find the appropriate node for deletion
      nodeLL* tgtNodePtr = this->find( val );
      // If the value is not found, abort
      if ( tgtNodePtr == nullptr ) {
         return( this->length );
      }
      else {
         // Hold the nodes before and after the target
         nodeLL* prevNodePtr = tgtNodePtr->next;
         nodeLL* nextNodePtr = tgtNodePtr->prev;

         // Redirect pointers around the target
         prevNodePtr->next = nextNodePtr;
         nextNodePtr->prev = prevNodePtr;

         // Delete the target, decrement the length
         delete tgtNodePtr;
         this->length--;
         return( this->length );
      }
   }

//-------------------------------------|
   std::string LinkedList::toString( ) {
      std::stringstream tempStream;
      tempStream << "(HEAD)";
      nodeLL* currNodePtr = this->head->next;
      for ( int i = 0 ; i < this->length ; i++ ) {
         tempStream << " - " << currNodePtr->value;
         currNodePtr = currNodePtr->next;
      }
   }

//-----------------------------------------------------------------------------|
// DRIVER
//-----------------------------------------------------------------------------|

// Note: Do not include when running: For compilation testing purposes only.

/*
int main() {
   std::cout << "Hello, World!" << std::endl;
   return( 1 );
}
*/

// End of file - 02_00_LinkedList.cpp

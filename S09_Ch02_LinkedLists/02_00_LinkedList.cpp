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
// 'Cracking the Coding Interview'
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
      this->value = NULL;
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
      this->next.prev = this;
      this->prev = prev;
      this->prev.next = this;
   }

//-------------------------------------|
   ~nodeLL( ) {
      this->isSentinel = NULL;
      this->value = NULL;
      this->next = nullptr;
      this->prev = nullptr;
   }
} // Closing struct nodeLL

//-------------------------------------|
struct LinkedList {
//-------------------------------------|
   nodeLL head;
   int length;

   int insert( int val );
   int insertAfter( int val, nodeLL* tgt );
   int insertBefore( int val, nodeLL* tgt );
   int remove( int val );
   nodeLL* find( int val );
   void print( );
   std:string toString( );

//-------------------------------------|
   LinkedList( ) {
      head.next = this;
      head.prev = this;
      head.value = NULL;
      head.isSentinel = true;
      length = 0;
   }

//-------------------------------------|
   ~LinkedList( ) {
      nodeLL* prevNode;
      nodeLL* currNode = head->next;
      while (currNode->isSentinel == false) {
         prevNode = currNode;
         currNode = currNode->next;
         delete prevNode;
      } // Closing while - We've returned to the sentinel
      // Head is statically allocated, will delete when it leaves scope
   }

//-------------------------------------|
   nodeLL* find( int searchVal ) {
      nodeLL* retPtr = nullptr;
      nodeLL* currNodePtr = this->head.next;
      for (int i = 0 ; i < length ; i++ ) {
         if ( currNodePtr.value == searchVal ) {
            retPtr = currNodePtr;
            return( retPtr );
         }
      } // Closing for - all comparisons complete, value not found
      return( retPtr );
   }

//-------------------------------------|
   int insert( int val ) {
      // Generate the new node
      nodeLL* newNode = nodeLL( val, this->head.prev, this->head );

      // Insertion complete, increment the length
      this->length++;
      return( this->length );
   }

//-------------------------------------|
   int insertAfter( int val, nodeLL* tgt ) {
      // Hold the target
      nodeLL* tgtNodePtr = this->find( val );
      if ( tgtNodePtr == nullptr ) {
         std::cout << "[insertAfter( )] - Value not found" << std::endl;
         return ( this->length );
      }
      nodeLL* newNode = new nodeLL( val, tgtNodePtr, tgtNodePtr->next );
   }

//-------------------------------------|
   int insertBefore( int val, nodeLL* tgt ) {
      // Hold the target
      nodeLL* tgtNodePtr = this->find( val );
      if ( tgtNodePtr == nullptr ) {
         std::cout << "[insertAfter( )] - Value not found" << std::endl;
         return ( this->length );
      }
      nodeLL* newNode = new nodeLL( val, tgtNodePtr->prev, tgtNodePtr );
   }

//-------------------------------------|
   void print( ) {
      std::cout << this->toString( ) << std::endl;
   }

//-------------------------------------|
   int remove( int val ) {
      // Attempt to find the appropriate node for deletion
      nodeLL* tgtNodePtr = this->find( val );
      // If the value is not found, abort
      if ( tgtNodePtr == nullptr ) {
         return( this->length );
      }
      else {
         // Hold the nodes before and after the target
         nodeLL* prevNodePtr = tgtNodePtr.next;
         nodeLL* nextNodePtr = tgtNodePtr.prev;

         // Redirect pointers around the target
         prevNodePtr.next = nextNodePtr;
         nextNodePtr.prev = prevNodePtr;

         // Delete the target, decrement the length
         delete tgtNodePtr;
         this->length--;
         return( this->length );
      }
   }

//-------------------------------------|
   std::string toString( ) {
      stringstream tempStream;
      tempStream << "(HEAD)";
      nodeLL* currNodePtr = this.head.next;
      for ( int i = 0 ; i < this.length ; i++ ) {
         tempStream << " - " << currNodePtr.value;
         currNodePtr = currNodePtr.next;
      }
   }

} // Closing struct LinkedList

// End of file - 02_00_LinkedList.cpp

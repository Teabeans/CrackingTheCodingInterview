//-----------------------------------------------------------------------------|
// AUTHORSHIP
//-----------------------------------------------------------------------------|
//
// Tim Lum
// twhlum@gmail.com
// Created:  2018.07.23
// Modified: 2018.07.26
//

/*
8.1 - tripleStep() - P.134
A child is running up a staircase with n steps and can hop either 1 step,
2 steps, or 3 steps at a time. Implement a method to count how many possible
ways the child can run up the stairs.



//-----------------------------------------------------------------------------|
// PROBLEM SETUP AND ASSUMPTIONS
//-----------------------------------------------------------------------------|

- The step numbers may be numbered in reverse, from 0 as the top landing.
- The number of ways to overshoot the top landing may be defined as:
  - If MAX_JUMP == 1, (0) overshoot is possible
  - If MAX_JUMP == 2, (1) overshoot is possible (Step1:Jump2)
      - 1
  - If MAX_JUMP == 3, (3) overshoots are possible (1:2, 1:3, 2:3)
      - 2 + 1
  - If MAX_JUMP == 4, (6) overshoots are possible (1:2, 1:3, 1:4, 2:3, 2:4, 3:4)
      - 3 + 2 + 1
  - If MAX_JUMP == 5, (10) overshoots are possible
      - 4 + 3 + 2 + 1
  - Sum of sequence (MAX_JUMP-1) + (MAX_JUMP-2) + ... + (MAX_JUMP - MAX_JUMP)



//-----------------------------------------------------------------------------|
// NAIVE, BRUTE FORCE, TERRIBAD APPROACH
//-----------------------------------------------------------------------------|

Design a recursive solution which systematically iterates through all possible
combinations of 1 added to 2 added to 3, incrementing a counter when n is
reached successfully and backtracking when n is exceeded. This is very similar
in spirit to a recursive backtrack maze solver, and consists of repeatedly
asking "Is there a solution with 1 jump? 2 jump? 3 jump?" to the next function
call.

This is a sub-ideal solution due to the memory space requirement of the call
stack, as well as the repetitive solve time needed by higher level steps. As n
increases to very large numbers, you may imagine that steps 1-3 will become
quite tired of answering "Is there a solution from here?"

"YES! For the 3^nth time!" they'll shout by the end of it.



//-----------------------------------------------------------------------------|
// OPTIMIZATIONS
//-----------------------------------------------------------------------------|

1) Observing that the number of ways the child may reach:
    - step 0 from step 1 is 1 ( [1] ).
    - step 0 from step 2 is 2 ( [1,1], [2] ).
    - step 0 from step 3 is 4 ( [1,1,1], [1, 2], [2, 1], [3] ).
2) And further observing that the number of permutations FROM these steps are
   constant regardless of what was done prior (that is, there will ALWAYS be 1
   solution off step 1, 2 solutions off 2, and 4 solutions off step 3).
3) We may infer that the number of solutions from step 4 can be computed by:
   - Move from step 4 to step 3
      - + All permutations of step 3
   - Move from step 4 to step 2
      - + All permutations of step 2
   - Move from step 4 to step 1
      - + All permutations of step 1
4) More broadly, the options from step 'n' may be defined as:
   - (All options of n-1) + (All options of n-2) + (All options of n-3)
   - For values of n greater than 3.
5) Most broadly, assuming perhaps that the child may hop greater increments:
   - (All options of n - MAX_JUMP) + ... + (All options of n - 1)
      - For values of n greater than MAX_JUMP
      - OR subtract the number of ways there are to overshoot the last step
         - See above; Overshoot options == Sequence sum of MAX_JUMP-1 to 0
6) We may begin to formalize this approach in an array as follows:

Number of ways to move from Step 'n' to step 0
  0   1   2   3   4   5   6   7   8   9   ...   n
---------------------------------------------------
| 0 | 1 | 2 | 4 | ? | ? | ? | ? | ? | ? | ... | ? |
---------------------------------------------------

7) To validate, the solution to step 4 should be the sum of steps 3, 2, and 1
   - Then the solution to step 5 should be the sum of steps 4, 3, and 2
   - Until 'n' is reached.

Number of ways to move from Step 'n' to step 0 (manually filled in)
    0     1     2     3     4     5     6     7     8     9   ...     n
-------------------------------------------------------------------------
|   0 |   1 |   2 |   4 |   7 |  13 |  24 |  44 |  81 | 149 | ... |   ? |
-------------------------------------------------------------------------


//-----------------------------------------------------------------------------|
// TIME COMPLEXITY
//-----------------------------------------------------------------------------|

In order to compute the summation sequence after establishing the first 3 terms,
we may expect the algorithm to run in O(n) time, where n is the number of steps.

This problem will be solved extremely quickly due to the fact that even at
modest values of 'n', issues of integer overflow will begin to impede further
calculation of sequence numbers.



//-----------------------------------------------------------------------------|
// PSEUDO LOGIC
//-----------------------------------------------------------------------------|

Declare and initialize array of size n+1
Populate first 3 indices
For indices [4] to [n], calculate by:
   [i-1] + [i-2] + [i-3]



//-----------------------------------------------------------------------------|
// NINJA APPROACH
//-----------------------------------------------------------------------------|

Recognizing that this question is, in fact, requesting the sum of a Tribonacci
Sequence (http://mathworld.wolfram.com/TribonacciNumber.html), recursive
calculation may be bypassed in favor of a direct calculation using the
following:

Sum == (Term1) + (Term2) + (Term3)
Where:
Term1 == ((T1^n+1) / (T1-T2)(T1-T3))
Term2 == ((T2^n+1) / (T2-T1)(T2-T3))
Term3 == ((T3^n+1) / (T3-T1)(T3-T2))
And:
Term1 == Options from step 1 (1)
Term2 == Options from step 2 (2)
Term3 == Options from step 3 (4)

For a final runtime complexity of O(1)



//-----------------------------------------------------------------------------|
// CODE (C++)
//-----------------------------------------------------------------------------|
*/

// (+) --------------------------------|
// #tripleStep(int)
// ------------------------------------|
// Desc:    Calculates the number of ways to move up a staircase with jumps of
//          1 to 3 steps
// Params:  int arg1 - The number of steps in the staircase.
// PreCons: None
// PosCons: None
// RetVal:  The number of ways an individual may ascend the steps
int tripleStep(int steps) {
   // Handle corner cases where 'steps' is 0-3
   if (steps == 0) {
      return(0);
   }
   else if (steps == 1) {
      return(1);
   }
   else if (steps == 2) {
      return(2);
   }
   else if (steps == 3) {
      return(4);
   }

   // Handle corner case where solution is subject to overflow
   if (steps > 36) {
      return( -1 ); // Note: 3.83 billion at step 36, next step if 7.05 billion
   }

   // Values of 'steps' must be between 4 and 36, inclusive

   // Declare and initialize a memoization array for each step
   int combinations[steps + 1]; // Note: Allows access without index offset
   for ( int i = 0 ; i <= steps ; i++ ) {
      combinations[i] = 0;
   }

   // Populate options for the first three steps
   combinations[1] = 1;
   combinations[2] = 2;
   combinations[3] = 4;

   // Begin populating the memoization array
   for ( int i = 4 ; i <= steps ; i++ ) {
      combinations[i] = combinations[i-1] + combinations[i-2] + combinations[i-3];
   }

   // Return the value in the 'steps' indice
   return( combinations[steps] );

} // Closing tripleStep()

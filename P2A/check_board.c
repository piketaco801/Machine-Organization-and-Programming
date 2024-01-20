///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2021-23 Deb Deppeler
// Posting or sharing this file is prohibited, including any changes/additions.
//
// We have provided comments and structure for this program to help you get 
// started.  Later programs will not provide the same level of commenting,
// rather you will be expected to add same level of comments to your work.
// 09/20/2021 Revised to free memory allocated in get_board_size function.
// 01/24/2022 Revised to use pointers for CLAs
//
////////////////////////////////////////////////////////////////////////////////
// Main File:        (check_board.c)
// This File:        (check_board.c)
// Other Files:      (name of all other files if any)
// Semester:         CS 354 Fall 2023
// Instructor:       
//
// Author:           (sungwon mun)
// Email:            (smun4@wisc.edu)
// CS Login:         (sungwon)
// GG#:              (16)
//                   (See https://canvas.wisc.edu/groups for your GG number)
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   Track all work you do in your work log-p2a.pdf
//                   and fully credit all sources of help, including family, 
//                   friends, tutors, Peer Mentors, TAs, and Instructor.
//
// Online sources:   Avoid relying on eeb searches to solve your problems, 
//                   but if you do search, be sure to include Web URLs and 
//                   description of any information you find in your work log.
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *DELIM = ",";  // commas ',' are a common delimiter character for data strings

/* COMPLETED (DO NOT EDIT):       
 * Read the first line of input file to get the size of that board.
 * 
 * PRE-CONDITION #1: file exists
 * PRE-CONDITION #2: first line of file contains valid non-zero integer value
 *
 * fptr: file pointer for the board's input file
 * size: a pointer to an int to store the size
 *
 * POST-CONDITION: the integer whos address is passed in as size (int *) 
 * will now have the size (number of rows and cols) of the board being checked.
 */
void get_board_size(FILE *fptr, int *size) {      
   char *line1 = NULL;
   size_t len = 0;

   if ( getline(&line1, &len, fptr) == -1 ) {
      printf("Error reading the input file.\n");
      fclose(fptr);
      free(line1);
      exit(1);
   }

   char *size_chars = NULL;
   size_chars = strtok(line1, DELIM);
   *size = atoi(size_chars);

   // free memory allocated for reading first link of file
   free(line1);
   line1 = NULL;

}

/* TODO:
 * Returns 1 if and only if the board is in a valid Sudoku board state.
 * Otherwise returns 0.
 * 
 * A valid row or column contains only blanks or the digits 1-size, 
 * with no duplicate digits, where size is the value 1 to 9.
 * 
 * Note: p2A requires only that each row and each column are valid.
 * 
 * board: heap allocated 2D array of integers 
 * size:  number of rows and columns in the board
 */
//check if a specific row in the given Sudoku board is valid
int checkRow(int** board, int size, int row) {
    //Create an array to track the occurrences of each number
   int* counts = malloc( (size + 1) * sizeof(int));
   // Initialize: set the count of each number to 0
   for (int i = 0; i < size + 1; i++)
   {
      *(counts + i) = 0;
   }
   int valid = 1; // Flag to indicate if the row is valid
   // Check the validity of the row by examining each column
   for (int col = 0; col < size && valid; col++)
   {
      int val = *(*(board + row) + col);
      if(val < 0 || val > size) {
         valid = 0;
         break;
      }
      else if(val != 0) {
         *(counts + val)  += 1;

         if(*(counts + val) > 1){
            valid = 0;
            break;
         }
      }
   }

   free(counts);

   return valid;
}
// Function to check if a specific column in the given Sudoku board is valid
int checkCol(int** board, int size, int col) {
    // Create an array to track the occurrences of each number
   int* counts = malloc( (size + 1) * sizeof(int));
   // Initialize: set the count of each number to 0
   for (int i = 0; i < size + 1; i++)
   {
      *(counts + i) = 0;
   }
   int valid = 1;
   for (int row = 0; row < size && valid; row++)
   {
      int val = *(*(board + row) + col);
      if(val < 0 || val > size) {
         valid = 0;
         break;
      }
      else if(val != 0) {
         *(counts + val)  += 1;
         if(*(counts + val) > 1){
            valid = 0;
            break;
         }
      }
   }
   free(counts);
   return valid;
   
}
// Function to check if the given Sudoku board is valid
int valid_board(int **board, int size) {
    // If the Sudoku size is out of range, it's invalid
   if(size >= 10 || size < 1)
      return 0;
    // Check the validity of all rows and columns in the board
   for (int i = 0; i < size; i++)
   {
      if(!checkRow(board, size, i))
         return 0;
      if(!checkCol(board, size, i))
         return 0;
   }

   return 1;   
}    

/* TODO: COMPLETE THE MAIN FUNCTION
 * This program prints "valid" (without quotes) if the input file contains
 * a valid state of a Sudoku puzzle board wrt to rows and columns only.
 *
 * A single CLA is required, which is the name of the file 
 * that contains board data is required.
 *
 * argc: the number of command line args (CLAs)
 * argv: the CLA strings, includes the program name
 *
 * Returns 0 if able to correctly output valid or invalid.
 * Only exit with a non-zero result if unable to open and read the file given.
 */
int main( int argc, char **argv ) {              

   // TODO: Check if number of command-line arguments is correct.
   if(argc != 2) {
      printf("Usage: ./check_board <input_filename>\n");
      exit(1);
   }

   // Open the file and check if it opened successfully.
   FILE *fp = fopen(*(argv + 1), "r");
   if (fp == NULL) {
      printf("Can't open file for reading.\n");
      exit(1);
   }

   // Declare local variables.
   int size;

   // TODO: Call get_board_size to read first line of file as the board size.
   get_board_size(fp, &size);

   // TODO: Dynamically allocate a 2D array for given board size.
   // DO NOT create a 1D array of ints on the stack or heap
   // You must dyamically create a 1D arrays of pointers to other 1D arrays of ints
   int** board =  malloc( (size) * sizeof(int *));

   // Read the rest of the file line by line.
   // Tokenize each line wrt the delimiter character 
   // and store the values in your 2D array.
   char *line = NULL;
   size_t len = 0;
   char *token = NULL;
   for (int i = 0; i < size; i++) {

      if (getline(&line, &len, fp) == -1) {
         printf("Error while reading line %i of the file.\n", i+2);
         exit(1);
      }

      *(board + i) = malloc( (size) * sizeof(int));

      token = strtok(line, DELIM);
      for (int j = 0; j < size; j++) {
         // TODO: Complete the line of code below
         // to initialize your 2D array.
         /* ADD ARRAY ACCESS CODE HERE */
         *(*(board + i) + j) = atoi(token);
         token = strtok(NULL, DELIM);
      }

      free(line);
      line = NULL;
   }

   // TODO: Call the function valid_board and print the appropriate
   //       output depending on the function's return value.
   if(valid_board(board, size))
      printf("valid\n");
   else
       printf("invalid\n");

   // TODO: Free all dynamically allocated memory.
   for (int i = 0; i < size; i++)
   {
      free(*(board + i));
   }

   free(board);
   
   //Close the file.
   if (fclose(fp) != 0) {
      printf("Error while closing the file.\n");
      exit(1);
   } 
   return 0;   
   // test string    
}       



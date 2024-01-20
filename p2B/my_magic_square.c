///////////////////////////////////////////////////////////////////////////////
// Copyright 2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission, CS 354 Spring 2022, Deb Deppeler
////////////////////////////////////////////////////////////////////////////////
   
// add your own File Header information here (as provided in p2A or Commenting guide
/////////////////////////////////////////////////////////////////////////////
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
// Main File:        my_magic_square.c
// This File:        my_magic_square.c
// Other Files:      my_magic_square, magic_square3.txt
// Semester:         CS 354 Fall 2023
// Instructor:       Deb Deppeler
//
// Author:           Sungwon Mun
// Email:            smun4@wisc.edu
// CS Login:         sungwon
// GG#:              16
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

// Structure that represents a magic square
typedef struct {
    int size;           // dimension of the square
    int **magic_square; // pointer to heap allocated magic square
} MagicSquare;

/* TODO:
 * Promps the user for the magic square's size, read it,
 * check if it's an odd number >= 3 (if not, display the required
 * error message and exit)
 *
 * return the valid number
 */
//checks if the input is an odd integer and >= 3. input the size of the magic square.
int getSize() {
    printf("Enter magic square's size (odd integer >=3)\n");
    int inp;
    scanf("%d", &inp);
    
    if(inp < 3) {
        printf("Magic square size must be >= 3.\n");
        exit(1);
    }
    if(inp % 2 == 0) {
        printf("Magic square size must be odd.\n");
        exit(1);
    }
    return inp;
}
   
/* TODO:
 * Makes a magic square of size n,
 * and stores it in a MagicSquare (on the heap)
.*
 * It may use the Siamese magic square algorithm 
 * or alternate from assignment 
 * or another valid algorithm that produces a magic square.
 *
 * n - the number of rows and columns
 *
 * returns a pointer to the completed MagicSquare struct.
 */
//uses the "Siamese method" to construct the magic square. and generates a magic square of size 'n'.

MagicSquare *generateMagicSquare(int n) {
   MagicSquare* board = malloc(sizeof(MagicSquare));
    board->size = n;
	board->magic_square = malloc(sizeof(int*) * n);
for(int i = 0; i < n; i++) {
    *(board->magic_square + i) = malloc(sizeof(int) * n);
    // Initializing all values to 0
    for (int j = 0; j < n; j++) {
        *(*(board->magic_square + i) + j) = 0;
    }
}


    int row = 0;
int col = n / 2;

for (int num = 1; num <= n * n; num++) {
    *(*(board->magic_square + row) + col) = num;  // 현재 위치에 숫자 배치

    
    int nextRow = row - 1;
    int nextCol = col + 1;

    
    if (nextRow < 0 && nextCol >= n) {
        nextRow = row + 1;
        nextCol = col;
    }
    
    else if (nextRow < 0) {
        nextRow = n - 1;
    }
    
    else if (nextCol >= n) {
        nextCol = 0;
    }
    
    else {
       
        if (*(*(board->magic_square + nextRow) + nextCol) != 0) {
            nextRow = row + 1;
            nextCol = col;
        }
    }

    row = nextRow;
    col = nextCol;
}

return board;
}


/* TODO:  
 * Opens a new file (or overwrites the existing file)
 * and writes the magic square values to the file
 * in the specified format.
 *
 * magic_square - the magic square to write to a file
 * filename - the name of the output file
 */
//writes the generated magic square into a file.
void fileOutputMagicSquare(MagicSquare *magic_square, char *filename) {
   FILE* fp = fopen(filename, "w");
    fprintf(fp,"%d\n", magic_square->size);
    
    for(int i=0; i<magic_square->size; i++){
        for(int j=0; j<magic_square->size; j++) {
            if(j == magic_square->size-1) {
                fprintf(fp, "%d", *(*(magic_square->magic_square+i)+j));
            }else {
                fprintf(fp, "%d,", *(*(magic_square->magic_square+i)+j));
            }
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

/* TODO:
 * Generates a magic square of the user specified size and
 * outputs the square to the output filename.
 * 
 * Add description of required CLAs here
 */
	int main(int argc, char **argv) {
    // TODO: Check input arguments to get output filename
	// check number of arguments
	if(argc != 2) {
        printf("Usage: %s <output_filename>\n", *(argv + 0));
        exit(1);
    }
    char *filename = *(argv + 1);

    // TODO: Get magic square's size from user
	int numSize = getSize();
    // TODO: Generate the magic square by correctly interpreting 
    //       the algorithm(s) in the write-up or by writing or your own.  
    //       You must confirm that your program produces a 
    //       Magic Sqare as described in the linked Wikipedia page.
    MagicSquare* square = generateMagicSquare(numSize);
	// TODO: Output the magic square
	fileOutputMagicSquare(square, filename);
	//free all allocated array
    for(int i = 0; i < numSize; i++) {
        free(*(square->magic_square + i));
    }
    free(square->magic_square);
    free(square);
    
    return 0;
}


//    F23




////////////////////////////////////////////////////////////////////////////////
// This File:        (cache2Dcols.c)
// Other Files:      (name of all other files if any)
// Semester:         CS 354 Fall 2023
// Instructor:       deppeler
//
// Author:           (Sungwon Mun)
// Email:            (smun4@wisc.edu)
// CS Login:         (sungwon)
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   Fully acknowledge and credit all sources of help,
//                   including Peer Mentors, Instructors, and TAs.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   Avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of
//                   of any information you find.
////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

int arr2D[3000][500];

int main() {
    for (int col = 0; col < 500; col++) {
        for (int row = 0; row < 3000; row++) {
            arr2D[row][col] = row + col;
        }
    }
    return 0;
}


////////////////////////////////////////////////////////////////////////////////
// This File:        (cache1D.c)
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
int arr[100000];

int main() {
    for (int i = 0; i < sizeof(arr)/sizeof(int); i++) {
        arr[i] = i;
    }
    return 0;
}

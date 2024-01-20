///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2020-2023 Deb Deppeler based on work by Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission FALL 2023, CS354-deppeler
//
////////////////////////////////////////////////////////////////////////////////
// Main File:        my_div0_handler.c
// This File:        my_div0_handler.c
// Other Files:      
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
#include <signal.h>
// Global counter for the number of operations
int counter = 0;

void sigfpe_handler(int signum) {
    printf("Error: a division by 0 operation was attempted.\n"); // Notify division by zero
    printf("Total number of operations completed successfully: %d\n", counter); // Print number of successful operations
    printf("The program will be terminated.\n"); // Notify program termination
    exit(0); // Exit the program
}
// Handler function for SIGINT
void sigint_handler(int signum) { 
    printf("\nTotal number of operations completed successfully: %d\n", counter); // Print number of successful operations
    printf("The program will be terminated.\n"); // Notify program termination
    exit(0);
}

int main() { 
    struct sigaction sa; // Declare struct for signal handling
	// Set up SIGFPE handler
    sa.sa_handler = sigfpe_handler; // Assign sigfpe_handler to handle SIGFPE
    sigemptyset(&sa.sa_mask); // Initialize signal set to empty
    sa.sa_flags = 0; // Set flags to 0
    if (sigaction(SIGFPE, &sa, NULL) != 0) {
        perror("Failed to set SIGFPE handler");
        return 1;
    }
	// Set up SIGINT handler
    sa.sa_handler = sigint_handler; // Assign sigint_handler to handle SIGINT
    if (sigaction(SIGINT, &sa, NULL) != 0) {
        perror("Failed to set SIGINT handler");
        return 1;
    }

    while (1) { // Infinite loop for continuous operation
        char buf1[100], buf2[100]; // Buffers to store input strings

        printf("Enter first integer: ");
        if (fgets(buf1, 100, stdin) == NULL) // Read first integer as a string
            break;   // Break loop on EOF or error

        int numerator = atoi(buf1); // Convert first string to integer

        printf("Enter second integer: ");
		// Read second integer as a string
        if (fgets(buf2, 100, stdin) == NULL)
            break; // Break loop on EOF or error

        int denominator = atoi(buf2);

        if (denominator == 0) {
            raise(SIGFPE); // Raise SIGFPE signal if denominator is zero
        } else {
            int div = numerator / denominator; // Perform division
            int remain = numerator % denominator; // Calculate remainder
            printf("%d / %d is %d with a remainder of %d\n", numerator, denominator, div, remain);
            counter++; // Increment successful operation counter
        }
    }
    return 0; // Return success code
}


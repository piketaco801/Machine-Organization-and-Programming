///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2020-2023 Deb Deppeler based on work by Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission FALL 2023, CS354-deppeler
//
////////////////////////////////////////////////////////////////////////////////
// Main File:        send_signal.c
// This File:        send_signal.c
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

// Main function with command-line arguments
int main(int argc, char **argv) {
	// Check if the correct number of arguments is provided
    if (argc != 3) {
        printf("Usage: %s <signal type> <pid>\n", argv[0]);
        exit(1); // Exit with error code if arguments are incorrect
    }
	// Check if the first argument is "-u" for SIGUSR1
    if (strcmp(argv[1], "-u") == 0) {
		// Send SIGUSR1 signal to the process with the PID provided in argv[2]
        if (kill(atoi(argv[2]), SIGUSR1) == -1) {
            perror("Error: trouble with signalling SIGUSR1");
			// Exit with error code on failure
            exit(1);
        }
	// Check if the first argument is "-i" for SIGINT
    } else if (strcmp(argv[1], "-i") == 0) {
		// Send SIGINT signal to the process with the PID provided in argv[2]
        if (kill(atoi(argv[2]), SIGINT) == -1) {
            perror("Error: trouble with signalling SIGINT");
            exit(1);
        }
	// If the signal type is not recognized
    } else {
        printf("Error: signal type is invalid\n");
        exit(1);
    }
	// Return success code
    return 0; 
}

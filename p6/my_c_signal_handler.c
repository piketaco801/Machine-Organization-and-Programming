///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2020-2023 Deb Deppeler based on work by Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission FALL 2023, CS354-deppeler
//
////////////////////////////////////////////////////////////////////////////////
// Main File:        my_c_signal_handler.c
// This File:        my_c_signal_handler.c
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
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int ALARM_SECONDS = 5; // Define constant for alarm interval (5 seconds)
int sigusr1_counter = 0; // Global counter for SIGUSR1 signals

// Handler function for SIGALRM
void sig_handler(int sig) {
    time_t current_time; // Declare variable for current time
    if (time(&current_time) == (time_t)-1) {
        perror("Failed to get current time"); // Print error if time function fails
        exit(1); // Exit program with error code 1
    }

    char *time_str = ctime(&current_time); // Convert current time to string format
    if (time_str == NULL) {
        perror("Failed to convert time to string"); // Print error if ctime fails
        exit(1);
    }

    printf("PID: %d CURRENT TIME: %s", getpid(), time_str); // Print process ID and current time
    alarm(ALARM_SECONDS); // Reset alarm for another interval
}

// Handler function for SIGUSR1
void sig_user(int sig) {
    sigusr1_counter++; // Increment counter for SIGUSR1
    printf("SIGUSR1 handled and counted!\n"); // Print message indicating SIGUSR1 handling
}
// Handler function for SIGINT
void sig_int(int sig) { 
    printf("\nSIGINT handled.\n"); // Print message indicating SIGINT handling
    printf("SIGUSR1 was handled %d times. Exiting now.\n", sigusr1_counter); // Print total count of SIGUSR1 signals handled
    exit(0);// Exit program successfully
}

int main() {
    struct sigaction sa_alarm, sa_usr1, sa_int; // Declare sigaction structures for different signals

    memset(&sa_alarm, 0, sizeof(sa_alarm)); // Initialize sa_alarm to zeros
    sa_alarm.sa_handler = sig_handler; // Assign sig_handler to handle SIGALRM
	// Set up SIGALRM handler
    if (sigaction(SIGALRM, &sa_alarm, NULL) != 0) {
        perror("Error: binding SIGALRM Handler");
        return 1;
    }

    memset(&sa_usr1, 0, sizeof(sa_usr1));  // Initialize sa_usr1 to zeros
    sa_usr1.sa_handler = sig_user; // Assign sig_user to handle SIGUSR1
	// Set up SIGUSR1 handler
    if (sigaction(SIGUSR1, &sa_usr1, NULL) != 0) {
        perror("Error: binding SIGUSR1 Handler");
        return 1;
    }

    memset(&sa_int, 0, sizeof(sa_int)); // Initialize sa_int to zeros
    sa_int.sa_handler = sig_int; // Assign sig_int to handle SIGINT
	// Set up SIGINT handler
    if (sigaction(SIGINT, &sa_int, NULL) != 0) {
        perror("Error: binding SIGINT Handler");
        return 1;
    }

    printf("PID and time print every 5 seconds.\n"); // Inform user about alarm behavior
    printf("Type Ctrl-C to end the program.\n"); // Inform user how to terminate program

    alarm(ALARM_SECONDS); // Set initial alarm

    while (1) {
        pause(); // Pause program until a signal is received
    }

    return 0; // Return success code (though not reachable due to infinite loop)
}


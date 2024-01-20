////////////////////////////////////////////////////////////////////////////////////////////////
//
// Main File:        csim.c
// This File:        (csim.c)
// Other Files:      (name of all other files if any)
// Semester:         CS 354 Fall 2023
// Instructor:       Deppeler
//
// Author:           Sungwon Mun
// Email:            smun4@wisc.edu
// CS Login:         sungwon
//
///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2020-2023 Deb Deppeler based on work by Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission FALL 2023, CS354-deppeler
//
///////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// Copyright 2013,2019-2020
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission for Fall 2023
//
////////////////////////////////////////////////////////////////////////////////

/*
 * csim.c:
 * A cache simulator that can replay traces (from Valgrind) and output
 * statistics for the number of hits, misses, and evictions.
 * The replacement policy is LRU.
 *
 * Implementation and assumptions:
 *  1. Each load/store can cause at most one cache miss plus a possible eviction.
 *  2. Instruction loads (I) are ignored.
 *  3. Data modify (M) is treated as a load followed by a store to the same
 *  address. Hence, an M operation can result in two cache hits, or a miss and a
 *  hit plus a possible eviction.
 */

#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

/******************************************************************************/
/* DO NOT MODIFY THESE VARIABLES **********************************************/

//Globals set by command line args.
int b = 0; //number of (b) bits
int s = 0; //number of (s) bits
int E = 0; //number of lines per set

//Globals derived from command line args.
int B; //block size in bytes: B = 2^b
int S; //number of sets: S = 2^s

//Global counters to track cache statistics in access_data().
int hit_cnt = 0;
int miss_cnt = 0;
int evict_cnt = 0;

//Global to control trace output
int verbosity = 0; //print trace if set
/******************************************************************************/
// Add track value to calculate and find which line is least recently used.
int add_trk = 0;

//Type mem_addr_t: Use when dealing with addresses or address masks.
typedef unsigned long long int mem_addr_t;

//Type cache_line_t: Use when dealing with cache lines.
//TODO - COMPLETE THIS TYPE
typedef struct cache_line {
	char valid;
	mem_addr_t tag;
	//Add a data member as needed by your implementation for LRU tracking.
    int trk;
} cache_line_t;

//Type cache_set_t: Use when dealing with cache sets
//Note: Each set is a pointer to a heap array of one or more cache lines.
typedef cache_line_t* cache_set_t;

//Type cache_t: Use when dealing with the cache.
//Note: A cache is a pointer to a heap array of one or more sets.
typedef cache_set_t* cache_t;

// Create the cache we're simulating.
//Note: A cache is a pointer to a heap array of one or more cache sets.
cache_t cache;

/* TODO - COMPLETE THIS FUNCTION
 * init_cache:
 * Allocates the data structure for a cache with S sets and E lines per set.
 * Initializes all valid bits and tags with 0s.
 */
void init_cache() {
    // Calculate S and B using the provided s and b values.
    S = pow(2, s); //calculate the number of cache sets (S) as 2^s
    B = pow(2, b); //calculate the block size (B) as 2^b

    // Dynamically allocate cache (set)
    cache = (cache_t)malloc(sizeof(cache_set_t) * S); //Allocate memory for the cache sets.
    if (cache == NULL) { //if NULL print Memory allocation failed message and exit
        fprintf(stderr, "Memory allocation failed. Exiting...\n");
        exit(1);
    }
    for (int i = 0; i < S; i++) {
        // Dynamically allocate cache (line)
        *(cache + i) = (cache_set_t)malloc(sizeof(cache_line_t) * E); //Allocate memory for cache lines in each sets.
        if (*(cache + i) == NULL) { //if NULL exit
            fprintf(stderr, "Memory allocation failed. Exiting...\n"); //if NULL print Memomry allocation failed message and exit.
            exit(1);
        }
        for (int j = 0; j < E; j++) {
            //initialze cache line properties to default values
            (*(cache + i) + j)->valid = 0;  //set valid bit to 0
            (*(cache + i) + j)->tag = 0; //set tag to 0
            (*(cache + i) + j)->trk = 0; //set track information to 0
        }
    }
}


/* TODO - COMPLETE THIS FUNCTION
 * free_cache:
 * Frees all heap allocated memory used by the cache.
 */
void free_cache() {
//free cache line
    for(int i=0; i<S; i++){
        free(*(cache+i));
        *(cache+i) = NULL; //set the pointer is NULL to avoid accessing freed memory
    }
    //free cache set
    free(cache); //Finally, free the cache sets array itself.
    cache = NULL; //Set the cache pointer to NULL to indicate it's no longer valid
}


/* TODO - COMPLETE THIS FUNCTION
 * access_data:
 * Simulates data access at given "addr" memory address in the cache.
 *
 * If already in cache, increment hit_cnt
 * If not in cache, cache it (set tag), increment miss_cnt
 * If a line is evicted, increment evict_cnt
 */
void access_data(mem_addr_t addr) {
// Calculate the set index and tag bits
    mem_addr_t set_index = (addr >> b) & ((1 << s) - 1); //Calculate the set index
    mem_addr_t tag_bits = addr >> (b + s); //Calculate the tag bit

    // Pointer to the cache set
    cache_set_t cache_set = cache[set_index];

    // Check if the data is in the cache
    for (int i = 0; i < E; i++) {
        if (cache_set[i].valid && cache_set[i].tag == tag_bits) {
            // Cache hit
            hit_cnt++; //increment the hit count
            // Update LRU information here
            cache_set[i].trk = add_trk; //Update the line as recently used
            add_trk++; //increment the tracking count
            return;
        }
    }

    // Cache miss
    miss_cnt++; // increment miss count

    // Look for an empty line in the set
    for (int i = 0; i < E; i++) {
        if (!cache_set[i].valid) {
            // Found an empty line, cache the data
            cache_set[i].valid = 1; //Set the valid bit to indicate data presence
            cache_set[i].tag = tag_bits; //Set the tag bits fo the new data
            // Update LRU information here
            cache_set[i].trk = add_trk; //Update the line as least recently used
            add_trk++; //Increment track
            return;
        }
    }

    // If no empty line found, perform eviction (LRU replacement policy)
    evict_cnt++; //Increment the eviction count
    int lru_index = 0; //
    int min_trk = cache_set[0].trk;

    // Find the least recently used line
    for (int i = 1; i < E; i++) {
        if (cache_set[i].trk < min_trk) {
            min_trk = cache_set[i].trk;
            lru_index = i;
        }
    }

    // Evict the least recently used line and cache the data
    cache_set[lru_index].valid = 1;// Set the valid bit to indicate data presence
    cache_set[lru_index].tag = tag_bits;// Set the tag bits for the new data
    // Update LRU information here
    cache_set[lru_index].trk = add_trk; // Update the line as recently used
    add_trk++; // Increment the tracking counter
}


/* TODO - FILL IN THE MISSING CODE
 * replay_trace:
 * Replays the given trace file against the cache.
 *
 * Reads the input trace file line by line.
 * Extracts the type of each memory access : L/S/M
 * TRANSLATE each "L" as a load i.e. 1 memory access
 * TRANSLATE each "S" as a store i.e. 1 memory access
 * TRANSLATE each "M" as a load followed by a store i.e. 2 memory accesses
 */

void replay_trace(char* trace_fn) {
	char buf[1000];
	mem_addr_t addr = 0;
	unsigned int len = 0;
	FILE* trace_fp = fopen(trace_fn, "r");

	if (!trace_fp) {
		fprintf(stderr, "%s: %s\n", trace_fn, strerror(errno));
		exit(1);
	}

	while (fgets(buf, 1000, trace_fp) != NULL) {
		if (buf[1] == 'S' || buf[1] == 'L' || buf[1] == 'M') {
			sscanf(buf+3, "%llx,%u", &addr, &len);

			if (verbosity)
				printf("%c %llx,%u ", buf[1], addr, len);
			// TODO - MISSING CODE
			// GIVEN: 1. addr has the address to be accessed
			//        2. buf[1] has type of acccess(S/L/M)
			// call access_data function here depending on type of access
	char accessType = buf[1];  // Storing the second character of the buffer 'buf' in a variable 'accessType'. This character represents the type of access (S, L, M).
            // Checking if the access type is one of the valid options: 'S', 'L', or 'M'.
            if (accessType == 'S' || accessType == 'L' || accessType == 'M') {
                access_data(addr);  // Calling the function 'access_data' with the address 'addr'. This function is called for any valid access type.
                // Checking if the access type is 'M', which requires a special handling.
                if (accessType == 'M') {
                    access_data(addr);  // Calling the function 'access_data' a second time for the 'M' access type. This is because 'M' requires two accesses.
                }
            } else {
                // Handling an invalid access type that is not 'S', 'L', or 'M'.
                printf("Invalid letter\n");  // Printing an error message indicating an invalid access type.
                exit(0);  // Exiting the program with a status code of 0, indicating an abnormal termination due to invalid input.
            }
            // Checking the 'verbosity' flag to determine if additional output should be printed.
            if (verbosity)
                printf("\n");  // Printing a newline character for formatting purposes if verbosity is enabled.
        }
    }
    fclose(trace_fp);  // Closing the file pointed to by 'trace_fp'. This is important to free up resources and avoid memory leaks.
}



/*
 * print_usage:
 * Print information on how to use csim to standard output.
 */
void print_usage(char* argv[]) {
	printf("Usage: %s [-hv] -s <num> -E <num> -b <num> -t <file>\n", argv[0]);
	printf("Options:\n");
	printf("  -h         Print this help message.\n");
	printf("  -v         Verbose flag.\n");
	printf("  -s <num>   Number of s bits for set index.\n");
	printf("  -E <num>   Number of lines per set.\n");
	printf("  -b <num>   Number of b bits for word and byte offsets.\n");
	printf("  -t <file>  Trace file.\n");
	printf("\nExamples:\n");
	printf("  linux>  %s -s 4 -E 1 -b 4 -t traces/yi.trace\n", argv[0]);
	printf("  linux>  %s -v -s 8 -E 2 -b 4 -t traces/yi.trace\n", argv[0]);
	exit(0);
}


/*
 * print_summary:
 * Prints a summary of the cache simulation statistics to a file.
 */
void print_summary(int hits, int misses, int evictions) {
	printf("hits:%d misses:%d evictions:%d\n", hits, misses, evictions);
	FILE* output_fp = fopen(".csim_results", "w");
	assert(output_fp);
	fprintf(output_fp, "%d %d %d\n", hits, misses, evictions);
	fclose(output_fp);
}


/*
 * main:
 * Main parses command line args, makes the cache, replays the memory accesses
 * free the cache and print the summary statistics.
 */
int main(int argc, char* argv[]) {
	char* trace_file = NULL;
	char c;

	// Parse the command line arguments: -h, -v, -s, -E, -b, -t
	while ((c = getopt(argc, argv, "s:E:b:t:vh")) != -1) {
		switch (c) {
			case 'b':
				b = atoi(optarg);
				break;
			case 'E':
				E = atoi(optarg);
				break;
			case 'h':
				print_usage(argv);
				exit(0);
			case 's':
				s = atoi(optarg);
				break;
			case 't':
				trace_file = optarg;
				break;
			case 'v':
				verbosity = 1;
				break;
			default:
				print_usage(argv);
				exit(1);
		}
	}

	//Make sure that all required command line args were specified.
	if (s == 0 || E == 0 || b == 0 || trace_file == NULL) {
		printf("%s: Missing required command line argument\n", argv[0]);
		print_usage(argv);
		exit(1);
	}

	//Initialize cache.
	init_cache();

	//Replay the memory access trace.
	replay_trace(trace_file);

	//Free memory allocated for cache.
	free_cache();

	//Print the statistics to a file.
	//DO NOT REMOVE: This function must be called for test_csim to work.
	print_summary(hit_cnt, miss_cnt, evict_cnt);
	return 0;
}

// Fall 202309


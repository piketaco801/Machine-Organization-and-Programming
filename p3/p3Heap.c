////////////////////////////////////////////////////////////////////////////////////////////////
//
// Main File:        p3Heap.c
// This File:        p3Heap.c
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
//
// Copyright 2020-2023 Deb Deppeler based on work by Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission FALL 2023, CS354-deppeler
//
///////////////////////////////////////////////////////////////////////////////
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#include "p3Heap.h"
#include <stdbool.h>

/*
 * This structure serves as the header for each allocated and free block.
 * It also serves as the footer for each free block.
 */
typedef struct blockHeader
{

    /*
     * 1) The size of each heap block must be a multiple of 8
     * 2) heap blocks have blockHeaders that contain size and status bits
     * 3) free heap block contain a footer, but we can use the blockHeader
     *.
     * All heap blocks have a blockHeader with size and status
     * Free heap blocks have a blockHeader as its footer with size only
     *
     * Status is stored using the two least significant bits.
     *   Bit0 => least significant bit, last bit
     *   Bit0 == 0 => free block
     *   Bit0 == 1 => allocated block
     *
     *   Bit1 => second last bit
     *   Bit1 == 0 => previous block is free
     *   Bit1 == 1 => previous block is allocated
     *
     * Start Heap:
     *  The blockHeader for the first block of the heap is after skip 4 bytes.
     *  This ensures alignment requirements can be met.
     *
     * End Mark:
     *  The end of the available memory is indicated using a size_status of 1.
     *
     * Examples:
     *
     * 1. Allocated block of size 24 bytes:
     *    Allocated Block Header:
     *      If the previous block is free      p-bit=0 size_status would be 25
     *      If the previous block is allocated p-bit=1 size_status would be 27
     *
     * 2. Free block of size 24 bytes:
     *    Free Block Header:
     *      If the previous block is free      p-bit=0 size_status would be 24
     *      If the previous block is allocated p-bit=1 size_status would be 26
     *    Free Block Footer:
     *      size_status should be 24
     */
    int size_status;

} blockHeader;

/* Global variable - DO NOT CHANGE NAME or TYPE.
 * It must point to the first block in the heap and is set by init_heap()
 * i.e., the block at the lowest address.
 */
blockHeader *heap_start = NULL;
blockHeader *prev_heap = NULL;
blockHeader *end_heap;

/* Size of heap allocation padded to round to nearest page size.
 */
int alloc_size;

/*
 * Additional global variables may be added as needed below
 * TODO: add global variables needed by your function
 */

/*
 * Function for allocating 'size' bytes of heap memory.
 * Argument size: requested size for the payload
 * Returns address of allocated block (payload) on success.
 * Returns NULL on failure.
 *
 * This function must:
 * - Check size - Return NULL if size < 1
 * - Determine block size rounding up to a multiple of 8
 *   and possibly adding padding as a result.
 *
 * - Use BEST-FIT PLACEMENT POLICY to chose a free block
 *
 * - If the BEST-FIT block that is found is exact size match
 *   - 1. Update all heap blocks as needed for any affected blocks
 *   - 2. Return the address of the allocated block payload
 *
 * - If the BEST-FIT block that is found is large enough to split
 *   - 1. SPLIT the free block into two valid heap blocks:
 *         1. an allocated block
 *         2. a free block
 *         NOTE: both blocks must meet heap block requirements
 *       - Update all heap block header(s) and footer(s)
 *              as needed for any affected blocks.
 *   - 2. Return the address of the allocated block payload
 *
 *   Return if NULL unable to find and allocate block for required size
 *
 * Note: payload address that is returned is NOT the address of the
 *       block header.  It is the address of the start of the
 *       available memory for the requesterr.
 *
 * Tips: Be careful with pointer arithmetic and scale factors.
 */

void *balloc(int size)
{
    // TODO: Your code goes in here.
    //  Ensure the requested size for allocation is positive.
    //  Negative or zero sizes are not valid.
    if (size < 1 || size > alloc_size)
    {
        return NULL;
    }

    // Calculate the total size required for the allocation,
    // including the block header.
    int blockSize = size + sizeof(blockHeader);

    // Ensure the blockSize is a multiple of 8 for alignment.
    if (blockSize % 8 != 0)
    {
        blockSize += 8 - (blockSize % 8);
    }

    // first time allocating
    if (prev_heap == NULL)
        prev_heap = heap_start;

    // Start traversal from the beginning of the heap.
    blockHeader *current = prev_heap;
    int bestFitSize = 0;
    while (bestFitSize == 0)
    {
        int currentSize = current->size_status >> 3 << 3; // get the size of header

        if ((current->size_status & 1) != 0)
        {                                                             // if not free
            current = (blockHeader *)((void *)current + currentSize); // next header
            if (current->size_status == 1)
            {                         // reach to the end mark
                current = heap_start; // start from heap_start again
            }
        }
        else
        { // free

            if (blockSize > currentSize)
            {                                                             // not enough space
                current = (blockHeader *)((void *)current + currentSize); // next header
            }
            else
            { // enough space - break while loop
                bestFitSize = 1;
                break;
            }
        }
        // check block have gone through whole block
        if (current == prev_heap)
        {
            return NULL;
        }
    }

    // calculate size to store
    int currentSize = current->size_status >> 3 << 3;
    int freesize = currentSize - blockSize;

    // check if rest of size is enought for spliting
    if (freesize >= 8)
    {

        // split
        blockHeader *next = (blockHeader *)((void *)current + blockSize);

        next->size_status = freesize; // size of next block
        next->size_status += 2;       // updat p bit

        // change size and status of current block
        current->size_status = (current->size_status & 2) + blockSize;
        current->size_status += 1; // alloc

        // update footer of next block
        blockHeader *footer = (blockHeader *)((void *)next + freesize - 4);
        footer->size_status = freesize;
    }
    else
    { // exact size to store
        // change size
        current->size_status += 1;
    }

    prev_heap = current; // update previous pointer - next fit

    return ((void *)current) + sizeof(blockHeader); // return after header
}

/*
 * Function for freeing up a previously allocated block.
 * Argument ptr: address of the block to be freed up.
 * Returns 0 on success.
 * Returns -1 on failure.
 * This function should:
 * - Return -1 if ptr is NULL.
 * - Return -1 if ptr is not a multiple of 8.
 * - Return -1 if ptr is outside of the heap space.
 * - Return -1 if ptr block is already freed.
 * - Update header(s) and footer as needed.
 *
 * If free results in two or more adjacent free blocks,
 * they will be immediately coalesced into one larger free block.
 * so free blocks require a footer (blockHeader works) to store the size
 *
 * TIP: work on getting immediate coalescing to work after your code
 *      can pass the tests in partA and partB of tests/ directory.
 *      Submit code that passes partA and partB to Canvas before continuing.
 */

// TODO: Your code goes in here.
int bfree(void *ptr)
{
    // Check if the input pointer is NULL
    if (ptr == NULL)
        return -1;

    // Find the end of the heap
    blockHeader *end = heap_start;  // Initialize 'end' to the start of the heap
    int valid = 0;  // Initialize a flag 'valid' to 0

    // Loop to find the end of the heap
    while (valid == 0)
    {
    // Extract the size (ignoring the least 3 bits for alignment) from the size_status field
    int ss = end->size_status >> 3 << 3;

    if (end->size_status != 1)
    {
        // If the size_status is not 1, it means this is not the end mark of the heap.
        // Increment 'end' to the next block by adding the extracted size 'ss' to the current 'end' pointer.
        end = (blockHeader *)((void *)end + ss);
    }
    else
    {
        // If the size_status is 1, it signifies the end mark of the heap.
        // Update 'end_heap' to point to this end mark.
        end_heap = end;

        // Set the 'valid' flag to 1 to exit the loop.
        valid = 1;
    }
}


    // Get the header of the block to be freed
    blockHeader *point = (blockHeader *)((void *)ptr - sizeof(blockHeader));

    // Get the size of the block from its header
    int size = point->size_status >> 3 << 3;

    // Check if the size is a multiple of 8
    if (size % 8 != 0)
        return -1;

    // Check if the pointer is outside of the heap space
    if (point < heap_start || point > end_heap)
        return -1;

    // Check if the block is already freed
    if ((point->size_status & 1) == 0)
        return -1;

    // Mark the block as free by clearing the least significant bit
    point->size_status -= 1;

    // Set the footer of the current block
    blockHeader *cfooter = (blockHeader *)((void *)point + size - 4);
    cfooter->size_status = size;

    int freeSize = size; // Variable to store the size of the free block
    int noprev = 0;      // Flag to check if the previous block is coalesced

    // Check the p bit (second least significant bit) in the size_status field
    int p = (point->size_status) & 2;

    blockHeader *prev = NULL; // Pointer to the previous block

    if (p == 0)
    { // Previous block is free
        // Get to the footer of the previous block
        blockHeader *pfooter = (blockHeader *)((void *)point - 4);

        int prevsize = pfooter->size_status;
        // Get the header of the previous block
        prev = (blockHeader *)((void *)pfooter - prevsize + 4);

        // Update freeSize to include the size of the previous block
        freeSize += prevsize;

        // Update the header of the previous block with the new size
        prev->size_status += freeSize - prevsize;

        // Update the footer of the previous block
        blockHeader *pnfooter = (blockHeader *)((void *)prev + freeSize - 4);
        pnfooter->size_status = freeSize;

        // Update the previous_heap pointer (used for next fit)
        prev_heap = prev;
    }
    else
    {
        noprev = 1; // Previous block coalescing does not occur
    }

    // Find the header of the next block
    blockHeader *next;

    if (noprev)
    {
        next = (blockHeader *)((void *)point + size);
    }
    else
    { // Previous block coalesced
        next = (blockHeader *)((void *)prev + freeSize);
    }

    // Clear the p bit (second least significant bit) in the size_status field of the next block
    next->size_status -= 2;

    // Check the status of the next block (least significant bit in size_status)
    int a = (next->size_status) & 1;

    if (a == 0)
    { // Next block is empty
        if (next->size_status != 1)
        { // Check if it's not the end mark
            // Get the size of the next block
            int nextsize = next->size_status >> 3 << 3;

            // Update freeSize to include the size of the next block
            freeSize += nextsize;

            if (noprev)
            {
                // Update the size in the header of the current block
                point->size_status += freeSize - size;

                // Update the footer of the current block
                blockHeader *nfooter = (blockHeader *)((void *)next + nextsize - 4);
                nfooter->size_status = freeSize;

                // Update the prev_heap pointer (used for next fit)
                prev_heap = point;
            }
            else
            {
                // Get the size of the previous block
                int presize = prev->size_status >> 3 << 3;

                // Update the size in the header of the previous block
                prev->size_status += freeSize - presize;

                // Update the footer of the current block
                blockHeader *nfooter = (blockHeader *)((void *)next + nextsize - 4);
                nfooter->size_status = freeSize;

                // Update the prev_heap pointer (used for next fit)
                prev_heap = prev;
            }
        }
    }

    // Successfully freed the block
    return 0;
}

/*
 * Initializes the memory allocator.
 * Called ONLY once by a program.
 * Argument sizeOfRegion: the size of the heap space to be allocated.
 * Returns 0 on success.
 * Returns -1 on failure.
 */
int init_heap(int sizeOfRegion)
{

    static int allocated_once = 0; // prevent multiple myInit calls

    int pagesize;   // page size
    int padsize;    // size of padding when heap size not a multiple of page size
    void *mmap_ptr; // pointer to memory mapped area
    int fd;

    blockHeader *end_mark;

    if (0 != allocated_once)
    {
        fprintf(stderr,
                "Error:mem.c: InitHeap has allocated space during a previous call\n");
        return -1;
    }

    if (sizeOfRegion <= 0)
    {
        fprintf(stderr, "Error:mem.c: Requested block size is not positive\n");
        return -1;
    }

    // Get the pagesize from O.S.
    pagesize = getpagesize();

    // Calculate padsize as the padding required to round up sizeOfRegion
    // to a multiple of pagesize
    padsize = sizeOfRegion % pagesize;
    padsize = (pagesize - padsize) % pagesize;

    alloc_size = sizeOfRegion + padsize;

    // Using mmap to allocate memory
    fd = open("/dev/zero", O_RDWR);
    if (-1 == fd)
    {
        fprintf(stderr, "Error:mem.c: Cannot open /dev/zero\n");
        return -1;
    }
    mmap_ptr = mmap(NULL, alloc_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (MAP_FAILED == mmap_ptr)
    {
        fprintf(stderr, "Error:mem.c: mmap cannot allocate space\n");
        allocated_once = 0;
        return -1;
    }

    allocated_once = 1;

    // for double word alignment and end mark
    alloc_size -= 8;

    // Initially there is only one big free block in the heap.
    // Skip first 4 bytes for double word alignment requirement.
    heap_start = (blockHeader *)mmap_ptr + 1;

    // Set the end mark
    end_mark = (blockHeader *)((void *)heap_start + alloc_size);
    end_mark->size_status = 1;

    // Set size in header
    heap_start->size_status = alloc_size;

    // Set p-bit as allocated in header
    // note a-bit left at 0 for free
    heap_start->size_status += 2;

    // Set the footer
    blockHeader *footer = (blockHeader *)((void *)heap_start + alloc_size - 4);
    footer->size_status = alloc_size;

    return 0;
}

/* STUDENTS MAY EDIT THIS FUNCTION, but do not change function header.
 * TIP: review this implementation to see one way to traverse through
 *      the blocks in the heap.
 *
 * Can be used for DEBUGGING to help you visualize your heap structure.
 * It traverses heap blocks and prints info about each block found.
 *
 * Prints out a list of all the blocks including this information:
 * No.      : serial number of the block
 * Status   : free/used (allocated)
 * Prev     : status of previous block free/used (allocated)
 * t_Begin  : address of the first byte in the block (where the header starts)
 * t_End    : address of the last byte in the block
 * t_Size   : size of the block as stored in the block header
 */

/* STUDENTS MAY EDIT THIS FUNCTION, but do not change function header.
 * TIP: review this implementation to see one way to traverse through
 *      the blocks in the heap.
 *
 * Can be used for DEBUGGING to help you visualize your heap structure.
 * It traverses heap blocks and prints info about each block found.
 *
 * Prints out a list of all the blocks including this information:
 * No.      : serial number of the block
 * Status   : free/used (allocated)
 * Prev     : status of previous block free/used (allocated)
 * t_Begin  : address of the first byte in the block (where the header starts)
 * t_End    : address of the last byte in the block
 * t_Size   : size of the block as stored in the block header
 */
void disp_heap()
{

    int counter;
    char status[6];
    char p_status[6];
    char *t_begin = NULL;
    char *t_end = NULL;
    int t_size;

    blockHeader *current = heap_start;
    counter = 1;

    int used_size = 0;
    int free_size = 0;
    int is_used = -1;

    fprintf(stdout,
            "*********************************** HEAP: Block List ****************************\n");
    fprintf(stdout, "No.\tStatus\tPrev\tt_Begin\t\tt_End\t\tt_Size\n");
    fprintf(stdout,
            "---------------------------------------------------------------------------------\n");

    while (current->size_status != 1)
    {
        t_begin = (char *)current;
        t_size = current->size_status;

        if (t_size & 1)
        {
            // LSB = 1 => used block
            strcpy(status, "alloc");
            is_used = 1;
            t_size = t_size - 1;
        }
        else
        {
            strcpy(status, "FREE ");
            is_used = 0;
        }

        if (t_size & 2)
        {
            strcpy(p_status, "alloc");
            t_size = t_size - 2;
        }
        else
        {
            strcpy(p_status, "FREE ");
        }

        if (is_used)
            used_size += t_size;
        else
            free_size += t_size;

        t_end = t_begin + t_size - 1;

        fprintf(stdout, "%d\t%s\t%s\t0x%08lx\t0x%08lx\t%4i\n", counter, status,
                p_status, (unsigned long int)t_begin, (unsigned long int)t_end, t_size);

        current = (blockHeader *)((char *)current + t_size);
        counter = counter + 1;
    }

    fprintf(stdout,
            "---------------------------------------------------------------------------------\n");
    fprintf(stdout,
            "*********************************************************************************\n");
    fprintf(stdout, "Total used size = %4d\n", used_size);
    fprintf(stdout, "Total free size = %4d\n", free_size);
    fprintf(stdout, "Total size      = %4d\n", used_size + free_size);
    fprintf(stdout,
            "*********************************************************************************\n");
    fflush(stdout);

    return;
}

// end p3Heap.c (Fall 2023)



#include <stdio.h>
#include <stdlib.h>
#include "circular-queue.h"

/* Initialize a new buffer.
    Return 1 if successful,
    Return 0 if memory allocation fails. */

unsigned char InitializeBuffer(circularbuffer* pcb)
{
    pcb->queue_size = QUEUE_SIZE;
    pcb->begin = 0;
    pcb->end = 0;
    pcb->tally = 0;
    pcb->members = calloc(pcb->queue_size, sizeof(membertype));
    if (pcb->members == NULL){
        return 0;
    } else {
        return 1;
    }
}

/* When we don't need a particular buffer anymore, we clean it up as follows */
void FreeBuffer(circularbuffer* pcb){
    free(pcb->members);
}


/* Define a function to check if buffer is full. 
    Return 1 if full.
    Return 0 if not full.
*/

unsigned char BufferFull(circularbuffer* pcb){
    if (pcb->tally == QUEUE_SIZE){
        return 1;
    } else {
        return 0;
    }
}

/* Define a function to check if buffer is empty.
    Return 1 if empty.
    Return 0 if not empty.
*/

unsigned char BufferEmpty(circularbuffer* pcb){
    if (pcb->tally == 0){
        return 1;
    } else {
        return 0;
    }
}

/* Define a function to add a new member to the buffer.
Return 1 if operation was successful, and 0 otherwise. */

unsigned char AddMember(circularbuffer* pcb, membertype* newmember){
    if (BufferFull(pcb) == 1){
        return 0;
    }

    pcb->members[pcb->end] = *newmember;
    pcb->end = ((pcb->end) + 1) % (pcb->queue_size);
    pcb->tally += 1;

    return 1;
}

/* Define a function to subtract a member from the buffer.
    The function will store the data dequeued from the buffer in 
    the location in memory pointed to by pointer 'dequeue', 
    as defined in the function.
    Return 1 if successful. Return 0 otherwise.

   If the buffer is empty, then there is no data to dequeue,
    so we return a default value, which is defined in the declaration
    of the variable empty_default.*/

unsigned char SubtractMember(circularbuffer* pcb, membertype* dequeue){
    if (BufferEmpty(pcb) == 1){
        membertype default_value = { .member_int = 99, .member_float = 9.99, .member_char = 9};
        *dequeue = default_value;
        return 0;
    }

    *dequeue = pcb->members[pcb->begin];
    pcb->begin = ((pcb->begin) + 1) % (pcb->queue_size);
    pcb->tally -= 1;

    return 1;
}

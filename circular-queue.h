#ifndef __CIRCULARQUEUE_H
#define __CIRCULARQUEUE_H

/* Define the size of the queue. Keep it to one byte (0 <= queue size <= 255) */
#define QUEUE_SIZE 255

/* Define the data type stored in the queue. 
    For now it a struct with an int, a float, and an unsigned char.*/
typedef struct {
    int member_int;
    float member_float;
    unsigned char member_char;
} membertype;

extern membertype default_value;

/* Define the structure of the circular buffer. */
typedef struct {
    unsigned char queue_size; /* Define the circumeference of the buffer */
    unsigned char begin; /* Define the starting point of the buffer */
    unsigned char end; /* Define the ending point of the buffer */
    unsigned char tally; /* Define a tally of occupied spaces */
    membertype* members; /* Define pointer to memory where buffer members will be stored */
} circularbuffer;

/* Forward Declaraions */
unsigned char InitializeBuffer(circularbuffer* pcb);
void FreeBuffer(circularbuffer* pcb);
unsigned char BufferFull(circularbuffer* pcb);
unsigned char BufferEmpty(circularbuffer* pcb);
unsigned char AddMember(circularbuffer* pcb, membertype* newmember);
unsigned char SubtractMember(circularbuffer* pcb, membertype* dequeue);
#endif

#include <stdio.h>
#include <stdlib.h>
#include "circular-queue.h"

int main(void)
{
    int i = 0;

    /* Define initial values for a member of a queue. */
    int m_int = 0;
    float m_float = 0.0;
    char m_char = 0;

    /* Initialize two separate buffers. */
    circularbuffer buff1;
    unsigned char init1 = InitializeBuffer(&buff1);

    circularbuffer buff2;
    unsigned char init2 = InitializeBuffer(&buff2);

    /* Print the initialization status of the newly created queues. */
    printf("Buffer1 queue size is %d, initialization %s\n", QUEUE_SIZE, init1?"Succeeded":"Failed");
    printf("Buffer2 queue size is %d, initialization %s\n", QUEUE_SIZE, init2?"Succeeded":"Failed");

    /* Define a space for data read from the queue. */
    membertype dequeue;

    /* Define some data to be put in the queue. */
    membertype member1 = { .member_int = 100, .member_float = 1.55, .member_char = 77};
    membertype member2 = { .member_int = 101, .member_float = 2.55, .member_char = 77};
    membertype member3 = { .member_int = 102, .member_float = 3.55, .member_char = 77};
    membertype member4 = { .member_int = 103, .member_float = 4.55, .member_char = 77};

    /* Attempt to add some data to both queues and print the results. */
    printf("Attempting to add member %d to buffer 1...\n", 1);
    if (AddMember(&buff1, &member1)){
        printf("\t...Success!\n");
    } else {
        printf("\t...FAILED\n");
    }
    printf("Attempting to add member %d to buffer 2...\n", 1);
    if (AddMember(&buff1, &member2)){
        printf("\t...Success!\n");
    } else {
        printf("\t...FAILED\n");
    }

    printf("Attempting to add member %d to buffer 1...\n", 2);
    if (AddMember(&buff2, &member3)){
        printf("\t...Success!\n");
    } else {
        printf("\t...FAILED\n");
    }
    printf("Attempting to add member %d to buffer 2...\n", 2);
    if (AddMember(&buff2, &member4)){
        printf("\t...Success!\n");
    } else {
        printf("\t...FAILED\n");
    }

    /* Attempt to load buffer 1 to capacity and beyond and print the results. */
    for(i = 3; i< 275; i++){
        m_int += 10;
        m_float += 1.001;
        m_char += 1;

        membertype iter = { .member_int = m_int, .member_float = m_float, .member_char = m_char};

        printf("Attempting to add member %d to buffer 1...\n", i);
        if (AddMember(&buff1, &iter)){ 
            printf("\t...Success!\n");
        } else {
            printf("\t...FAILED\n");
        }

        if (BufferFull(&buff1)) printf("Buffer Now Full\n");
        if (BufferEmpty(&buff1)) printf("Buffer Now Empty\n");
    }

    /* Attempt to read all the data from buffer 1 and then some. Print the results. */    
    for(i = 1; i < 300; i++){
        printf("Attempting to remove member %d from buffer 1...\n", i);
        if (SubtractMember(&buff1, &dequeue)){
            printf("\t...Success!\n");
        } else {
            printf("\t...FAILED\n");
        }

        printf("\tint: %d\n", dequeue.member_int);
        printf("\tfloat: %f\n", dequeue.member_float);
        printf("\tfloat: %d\n", (int)dequeue.member_char);

        if (BufferFull(&buff1)) printf("Buffer Full\n");
        if (BufferEmpty(&buff1)) printf("Buffer Empty\n");
    }

    /* Destroy the queues. */
    printf("Freeing buffer 1\n");
    FreeBuffer(&buff1);

    printf("Freeing buffer 2\n");
    FreeBuffer(&buff2);

    return 1;
}

#include "cqueue.h"

//===============================================
//==============[ cli ]==========================
//===============================================

void cli( void )
{
  // if an interrupt routine is able to modify
  // the queue, we must turn off interrupts here
}

//===============================================
//==============[ sti ]==========================
//===============================================

void sti( void )
{
  // if an interrupt routine is able to modify
  // the queue, we restore interrupts here
}

//===============================================
//==============[ CqueueAdd ]====================
//===============================================

// Add 1 member "e" to the circular queue "q"

int CqueueAdd( Cqueue* q, CqueueElement e )
{
  cli(); // Possibly turn off interrupts while messing with this.

  // Make sure the queue has space.
  if( q->count>=CQUEUESIZE )
  {
    sti();
    return FULL;
  }

  // New entries go to the head.
  q->array[q->head++]=e;
  q->count++;

  // Wrap the head around to zero if we reached the end.
  if( q->head>=CQUEUESIZE )
  {
    q->head=0;
  }

  sti();
  return 0;
}

//===============================================
//==============[ CqueueRemove ]=================
//===============================================

// Remove 1 member from the circular queue "q"

CqueueElement CqueueRemove( Cqueue* q )
{
  CqueueElement element;

  // Do nothing if the queue is empty.
  if( q->count==0 )
  {
    return EMPTY;
  }

  cli();  //Possibly turn off interrupts while messing with this.
  // We remove from the tail.
  element=q->array[q->tail++];
  q->count--;

  // Wrap around if we reached the array end.
  if( q->tail>=CQUEUESIZE )
  {
    q->tail=0;
  }
  sti();

  return element;
}

//===============================================
//==============[ CqueueCount ]==================
//===============================================

// Get the current count of members in the queue

int CqueueCount( Cqueue* q )
{
  return q->count;
}

//===============================================
//==============[ CqueueSize ]===================
//===============================================

// Get the maximum number of members the queue can hold.

int CqueueSize( void )
{
  return CQUEUESIZE;
}

//===============================================
//==============[ CqueueElementSize ]============
//===============================================

// get the number of bytes each member needs.

int CqueueElementSize( void )
{
  CqueueElement e;
  return sizeof(e);
}

//===============================================
//==============[ CqueueInit ]===================
//===============================================

// Setup a queue to a known state.

void CqueueInit( Cqueue* q,  CqueueElement * e  )
{
  int i;

  q->count=0;
  q->head=0;
  q->tail=0;
  q->array=e;
  for( i=0; i<CQUEUESIZE; i++ )
  {
    q->array[i]=0;
  }
}



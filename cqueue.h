#ifndef CQUEUE_H
#define CQUEUE_H

#define CQUEUESIZE 256
#define EMPTY 0xFFFF
#define FULL 0xFFFE

extern int SetVal( int v );
extern int GetVal( void );


typedef unsigned int CqueueElement;
typedef CqueueElement pCqueueElement[ CQUEUESIZE ];

typedef struct {
  CqueueElement * array;
  int head;
  int tail;
  int count;
} Cqueue;

extern int CqueueSize( void );
extern int CqueueElementSize( void );
extern int CqueueCount( Cqueue* q );
extern void CqueueInit( Cqueue* q, CqueueElement* e );
extern int CqueueAdd( Cqueue* q, CqueueElement e );
extern CqueueElement CqueueRemove( Cqueue * q );


#endif // CQUEUE_H

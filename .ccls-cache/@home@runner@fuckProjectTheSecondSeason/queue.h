#ifndef QUEUE_H
#define QUEUE_H
#include "Tree.h"

typedef struct
{
    TREENODE_T** data;
    int headIndex;
    int tailIndex;
    int count;
    int maxCapacity;
} QUEUE_T;


QUEUE_T* queueCreate(int capacity);


void queueDestroy(QUEUE_T* queue);


int queueSize(QUEUE_T* queue);


int queueEnqueue(QUEUE_T* queue, TREENODE_T* node);


int queueDequeue(QUEUE_T* queue);


#endif
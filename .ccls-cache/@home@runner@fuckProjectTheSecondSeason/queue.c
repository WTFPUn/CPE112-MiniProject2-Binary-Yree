#include"queue.h"
#include<stdio.h>
#include<stdlib.h>
#include "Tree.h"

QUEUE_T* queueCreate(int capacity)
{
    QUEUE_T* queue = (QUEUE_T*) calloc(1, sizeof(QUEUE_T));
    if (queue == NULL)
    {
        return NULL;
    }
    // make queue->data be tree node  
    queue->data = (TREENODE_T**) calloc(capacity, sizeof(TREENODE_T*));

    int i;
    for(i = 0; i <capacity ; i++)
    {
      queue->data[i] = newNodeCreate(0);
    }

    if (queue->data == NULL)
    {
        return NULL;
    }
    queue->headIndex = 0;
    queue->tailIndex = -1;
    queue->count = 0;
    queue->maxCapacity = capacity;
    return queue;
}

void queueDestroy(QUEUE_T* queue)
{
  if(queue != NULL){
    int i = 0;
        for (i = 0; i < queue->count; i++) 
        {
            free(queue->data[i]);
        }
        free(queue->data);
        free(queue);
  }
}

int queueSize(QUEUE_T* queue)
{
  if(queue == NULL)
  {
    return -1;
  }
  return queue->count;
  
}

int queueEnqueue(QUEUE_T* queue, TREENODE_T* node)
{
  if(queue == NULL)
  {
    return -1;
  }
  if(queue->count+1 > queue->maxCapacity)
  {
    return -2;
  }
  queue->data[(queue->tailIndex+1) % queue->maxCapacity] = node;
  queue->count +=1;
  queue->tailIndex = (queue->tailIndex+1) % queue->maxCapacity ;
  return 1;
}


int queueDequeue(QUEUE_T* queue)
{
   if(queue == NULL)
   {
    return -1;
   }
   if(queue->count == 0)
   {
    return -2;
   }
  queue->headIndex = (queue->headIndex+1) % queue->maxCapacity;
  queue->count -= 1;
  return 1;

}
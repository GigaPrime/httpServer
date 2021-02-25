#ifndef THREAD_H_
#define THREAD_H_

#include <stdlib.h>

struct Thread
{
    void* data;
    struct Thread* next;
};

struct Thread* createThread(void* data);
void* getData(struct Thread* thread);
void deleteThread(struct Thread* thread);

#endif //THREAD_H_

#include "/home/prime/Desktop/C_Projects/thread_pool/cmake-build-debug/Headers/Thread.h"    //@TODO change to content root

struct Thread* createThread(void* data)     // Kinda constructor :-)
{
    struct Thread* thread;
    thread = malloc(sizeof(*thread));
    thread->data = data;
    thread->next = NULL;
    return thread;
}

void* getData(struct Thread* thread)
{
    return thread->data;
}

void deleteThread(struct Thread* thread)
{
    free(thread);
    thread = NULL;      // To avoid further deletion/other usage
}
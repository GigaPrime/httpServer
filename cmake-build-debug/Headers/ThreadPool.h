#ifndef THREADPOOL_H_
#define THREADPOOL_H_

#include <stddef.h>         // Used for size_t

#include <pthread.h>        // Used for pthread mutexes and conditions
#include <stdbool.h>

#include "Thread.h"

struct ThreadPool
{
    struct Thread *previousThread;        // Kinda list elements'
    struct Thread *nextThread;            // pointers here
    size_t threadsCount;

    pthread_cond_t threadExecutionCondition;
    pthread_mutex_t threadMutex;
    bool isThreadInProgress;
};

struct ThreadPool* createThreadPool(size_t initialThreadsNumber);
void destroyThreadPool(struct ThreadPool* threadPool);
void handleTreadPool(struct ThreadPool* threadPool);
struct Thread* getThreadFromPool(struct ThreadPool* threadPool);
void addThreadToPool(struct ThreadPool* threadPool, void* data);    // void pointer for further cast to some data type pointer
void pauseThreadPool(struct ThreadPool* threadPool);

struct Thread* handleThreadQueue(struct ThreadPool* threadPool);

#endif //THREADPOOL_H_
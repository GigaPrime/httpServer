#include "/home/prime/Desktop/C_Projects/thread_pool/cmake-build-debug/Headers/ThreadPool.h"    //@TODO change to content root

struct ThreadPool* createThreadPool(size_t initialThreadsNumber)
{
    struct ThreadPool* threadPool = malloc(sizeof(struct ThreadPool));
    threadPool->threadsCount = initialThreadsNumber;
    threadPool->previousThread = NULL;
    threadPool->nextThread = NULL;

    pthread_mutex_init(&threadPool->threadMutex, NULL);
    pthread_cond_init(&threadPool->threadExecutionCondition, NULL);

    pthread_t libThread;
    for(size_t i = 0; i < initialThreadsNumber; i++)
    {
        pthread_create(&libThread, NULL, handleThreadQueue(threadPool), threadPool);
    }
}

void destroyThreadPool(struct ThreadPool* threadPool)
{
    pthread_mutex_lock(&threadPool->threadMutex);

    struct Thread* tmpThread;
    while(threadPool->previousThread != NULL)
    {
        tmpThread->next = threadPool->previousThread->next;     // current thread's data's
        deleteThread(threadPool->previousThread);               // lost here
    }

    threadPool->isThreadInProgress = false;
    pthread_cond_broadcast(&threadPool->threadExecutionCondition);
    pthread_mutex_unlock(&threadPool->threadMutex);
    pauseThreadPool(threadPool);
    pthread_mutex_destroy(&threadPool->threadMutex);
    pthread_cond_destroy(&threadPool->threadExecutionCondition);
    free(threadPool);
}

void handleTreadPool(struct ThreadPool* threadPool)
{
    struct Thread* thread;

    while(true)
    {
        pthread_mutex_lock(&threadPool->threadMutex);

        while(threadPool->previousThread == NULL && !threadPool->isThreadInProgress)
            pthread_cond_wait(&threadPool->threadExecutionCondition, &threadPool->threadMutex);

        if(!threadPool->isThreadInProgress)
            break;

        thread = handleThreadQueue(threadPool);
        threadPool->threadsCount++;
        pthread_mutex_unlock(&threadPool->threadMutex);

        pthread_mutex_lock(&threadPool->threadMutex);
        threadPool->threadsCount--;

        if(threadPool->isThreadInProgress &&
           threadPool->threadsCount == 0 &&
           threadPool->previousThread == NULL)
                pthread_mutex_unlock(&threadPool->threadMutex);
    }

    threadPool->threadsCount--;
    pthread_cond_signal(&threadPool->threadExecutionCondition);
    pthread_mutex_unlock(&threadPool->threadMutex);

    if(thread != NULL)
        deleteThread(thread);
}

struct Thread* getThreadFromPool(struct ThreadPool* threadPool)
{
    struct Thread* thread = threadPool->nextThread;     // @TODO Add pointers' checkup for NULL-value threads and pool
    return thread;
}

void addThreadToPool(struct ThreadPool* threadPool, void* data)
{
    struct Thread* thread = createThread(data);

    pthread_mutex_lock(&threadPool->threadMutex);
    if(threadPool->previousThread == NULL)
    {
        threadPool->previousThread = thread;
        thread->next = threadPool->nextThread;
    }
    else
    {
        threadPool->nextThread = thread;
        thread->next = threadPool->nextThread;
    }

    pthread_cond_broadcast(&threadPool->threadExecutionCondition);
    pthread_mutex_unlock(&threadPool->threadMutex);
}

void pauseThreadPool(struct ThreadPool* threadPool)
{
    pthread_mutex_lock(&threadPool->threadMutex);
    while(true)
    {
        if(threadPool->isThreadInProgress && threadPool->threadsCount != 0)
            pthread_cond_wait(&threadPool->threadExecutionCondition, &threadPool->threadMutex);
    }
    pthread_mutex_unlock(&threadPool->threadMutex);
}

struct Thread* handleThreadQueue(struct ThreadPool* threadPool)
{
    if(threadPool == NULL || threadPool->previousThread == NULL)
        return NULL;

    struct Thread* newThread = threadPool->nextThread;
    threadPool->nextThread = newThread->next;
    return newThread;
}
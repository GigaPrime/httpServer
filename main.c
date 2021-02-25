#include <stdio.h>

#include "/home/prime/Desktop/C_Projects/thread_pool/cmake-build-debug/Headers/ThreadPool.h"    //@TODO change to content root

int main(int argc, char* argv[])
{
    const int threadsAllowed = 4;

    struct ThreadPool* threadPool = createThreadPool(threadsAllowed);

    for(int i = 0; i < threadsAllowed; i++)
    {
        int* tmpData = &i;
        addThreadToPool(createThread(tmpData), tmpData);    // @TODO WTF???
    }

    pauseThreadPool(threadPool);    // Paranoiac for four threads only :-)

    for(int i = 0; i < threadsAllowed; i++)
    {
        printf(getData(getThreadFromPool(threadPool)));     // @TODO Debug needed
    }

    destroyThreadPool(threadPool);
    return 0;

    return 0;
}
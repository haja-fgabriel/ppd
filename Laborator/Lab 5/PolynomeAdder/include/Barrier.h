#pragma once

#include <mutex>
#include <condition_variable>

class Barrier
{
    std::mutex* mutex = new std::mutex;
    std::condition_variable* cv = new std::condition_variable;
    int count;

public:
    Barrier(int Count) : count{Count} {}
    
    ~Barrier()
    {
        delete mutex;
        delete cv;
    }

    void Wait()
    {
        std::unique_lock<std::mutex> lock(*mutex);
        if (--count == 0)
            cv->notify_all();
        else
            cv->wait(lock, [this] {return count == 0; });
    }
};

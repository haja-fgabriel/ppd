#pragma once

#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "Monome.h"
#include "Lista.h"

class Worker
{
    int i;
    bool& done;
    Lista& finalPolynome;
    std::queue<Monome>& queue;
    std::mutex& listLock;
    std::mutex& queueLock;
    std::condition_variable& cv;
    std::mutex& mutex;

public:
    Worker(
        int i, 
        bool& done, 
        Lista& FinalPolynome,
        std::condition_variable& cv, 
        std::mutex& canTakeMonomeMutex,
        std::queue<Monome>& queue, 
        std::mutex& listLock, 
        std::mutex& queueLock
    );
    
    void operator()();
};


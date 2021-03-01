#include "Worker.h"

#include <iostream>

#include <functional>

Worker::Worker(
    int i,
    bool& done,
    Lista& FinalPolynome,
    std::condition_variable& CanTakeMonome, 
    std::mutex& canTakeMonomeMutex,
    std::queue<Monome>& queue,
    std::mutex& listLock,
    std::mutex& queueLock
)
    : i{ i }, done{ done }, finalPolynome{ FinalPolynome }, cv{ CanTakeMonome }
    , queue{ queue }, listLock{listLock}, queueLock{queueLock}
    , mutex{canTakeMonomeMutex}
{
}

void Worker::operator()()
{
    std::unique_lock<std::mutex> lck(mutex);

    do
    {
        if (!done)
            cv.wait(lck, [this] {
                return done || !queue.empty();
            });
        //std::cout << "[DEBUG] Thread " << i << '\n';

        if (!queue.empty())
        {
            // extract latest monome
            queueLock.lock();
            Monome m = queue.front();
            queue.pop();
            queueLock.unlock();

            //std::cout << "[DEBUG] Thread " << i <<  " Monome " << m.Coefficient << " " << m.Degree << '\n';
            
            // append to list
            finalPolynome.adaugaInOrdine(m);
        }
    } while (!done || !queue.empty());
}
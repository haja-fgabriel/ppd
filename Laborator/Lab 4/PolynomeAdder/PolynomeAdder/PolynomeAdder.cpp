#include <iostream>
#include <cstring>
#include <ctime>
#include <queue>
#include <thread>
#include <condition_variable>

#include "FileUtils.h"
#include "Lista.h"
#include "Logging.h"
#include "Worker.h"

using namespace std;

int numThreads;
queue<Monome> monomes;
bool done;
bool producerNotStarted;
Lista l;
std::condition_variable cv;
std::mutex cvLock;
std::mutex listLock;
std::mutex queueLock;

void AddToList(int Degree, double Coeff)
{
    queueLock.lock();
    monomes.push({ Degree, Coeff });
    queueLock.unlock();

    cv.notify_one();
}

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        cerr << "Usage: " << argv[0] << " <num_input_files> <output_file> <num_threads> [--log-to-socket]" << endl;
        return 1;
    }

    numThreads = atoi(argv[3]);
    vector<Worker> workers;
    vector<thread> threads;
    for (int i = 1; i < numThreads; i++)
    {
        workers.push_back(Worker(i, done, l, cv, cvLock, monomes, listLock, queueLock));
        threads.push_back(thread(workers.back()));
    }

    clock_t begin = clock();

    int nInputFiles = atoi(argv[1]);
    for (int i = 1; i <= nInputFiles; i++)
    {
        char num[5];
        sprintf_s(num, "%03d", i);
        FileUtils::ReadFile("Polynome" + string(num) + ".txt", AddToList);
    }

    done = true;
    cv.notify_all();

    for (auto& t : threads)
    {
        if (t.joinable())
            t.join();
    }
    //cout << "[DEBUG] final queue size: " << monomes.size() << endl;

    clock_t end = clock();
    double time = 1.0 * (end - begin) / CLOCKS_PER_SEC;

    cout << "[DEBUG] Time: " << time << endl;
    if (argc >= 5 && strcmp(argv[4], "--log-to-socket") == 0)
    {
        SendLog(time);
    }

    FileUtils::WriteFile(argv[2], l);

    return 0;
}
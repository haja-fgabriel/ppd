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
int numReadingThreads;
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

void ReadFileThread(int Start, int End, int nt)
{
    for (int i = Start; i < End; i++)
    {
        char num[5];
        sprintf_s(num, "%03d", i);
        FileUtils::ReadFile("Polynome" + string(num) + ".txt", AddToList);
    }
}

int main(int argc, char** argv)
{
    if (argc < 4)
    {
        cerr << "Usage: " << argv[0] << " <num_input_files> <output_file> <num_threads> <num_reading_threads> [--log-to-socket]" << endl;
        return 1;
    }
    
    numReadingThreads = atoi(argv[4]);
    numThreads = atoi(argv[3]);
    vector<Worker> workers;
    vector<thread> threads;
    vector<thread> readingThreads;
    for (int i = 1; i <= numThreads - numReadingThreads; i++)
    {
        workers.push_back(Worker(i, done, l, cv, cvLock, monomes, listLock, queueLock));
        threads.push_back(thread(workers.back()));
    }

    clock_t begin = clock();

    int nInputFiles = atoi(argv[1]);
    int start = 1, _end, chunk = nInputFiles / numReadingThreads;
    int rest = nInputFiles % numReadingThreads;
    for (int i = 1; i <= numReadingThreads; i++)
    {
        _end = start + chunk;
        if (rest)
        {
            rest--;
            _end++;
        }
        readingThreads.push_back(thread(ReadFileThread, start, _end, i));
        start = _end;
    }

    done = true;
    cv.notify_all();

    for (auto& t : readingThreads)
    {
        if (t.joinable())
            t.join();
    }

    for (auto& t : threads)
    {
        if (t.joinable())
            t.join();
    }
    //cout << "[DEBUG] final queue size: " << monomes.size() << endl;

    clock_t end = clock();
    double time = 1.0 * (end - begin) / CLOCKS_PER_SEC;

    cout << "[DEBUG] Time: " << time << endl;
    if (argc >= 6 && strcmp(argv[5], "--log-to-socket") == 0)
    {
        SendLog(time);
    }

    FileUtils::WriteFile(argv[2], l);

    return 0;
}
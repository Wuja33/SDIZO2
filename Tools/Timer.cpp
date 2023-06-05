#include "Timer.h"
#include <windows.h>
#include <iostream>
#include <iomanip>
using namespace std;




Timer::Timer() : frequency(0), start(0), elapsed(0)
{
}

void Timer::run() {
    QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
    start = read_QPC();
}

void Timer::stop() {
    elapsed = read_QPC() - start;
}

void Timer::printResult() {
    cout << endl;

    cout << "Time [s] = " << fixed << setprecision(3) << (float)elapsed /
                                                         frequency << endl;
    cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) /
                                                 frequency << endl;
    cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) /
                                                 frequency << endl << endl;
}

long long int Timer::read_QPC()
{
    LARGE_INTEGER count;
    DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
    QueryPerformanceCounter(&count);
    SetThreadAffinityMask(GetCurrentThread(), oldmask);
    return((long long int)count.QuadPart);
}

double Timer::getTimeMs()
{
    return (1000.0 * elapsed) /frequency;
}
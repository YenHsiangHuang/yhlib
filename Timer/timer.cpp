#include "timer.h"
#include <iostream>

void printDuration(std::chrono::system_clock::duration& t,
                   const TimeMode& timeMode) {
    switch (timeMode) {
        case ms:
            std::cout
                << std::chrono::duration_cast<std::chrono::milliseconds>
                   (t).count()
                << " ms";
            break;
        case us:
            std::cout
                << std::chrono::duration_cast<std::chrono::microseconds>
                   (t).count()
                << " us";
            break;
        case ns:
            std::cout
                << std::chrono::duration_cast<std::chrono::nanoseconds>
                   (t).count()
                << " ns";
            break;
    }
}
void printDuration(std::chrono::system_clock::duration&& t,
                   const TimeMode& timeMode) {
    printDuration(t, timeMode);
}

struct TimerData {
    TimerData() { t_construct = std::chrono::system_clock::now(); }
    std::chrono::system_clock::time_point t_construct;
};

Timer::Timer(const std::string& message) : message(message) {
    data = std::make_shared<TimerData>();
}

Timer::~Timer() {
    auto t_destruct = std::chrono::system_clock::now();
    std::cout << "[" << message << " : \t"
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     t_destruct - data->t_construct)
                     .count()
              << " ms]" << std::endl;
}

struct TicTocData {
    std::chrono::system_clock::time_point startTime;
    std::string message;
};

void tic() { tictocHelper(ticFunc); }
void tic(const TimeMode& timeMode) { tictocHelper(ticFunc, timeMode); }
void tic(const std::string& message) { tictocHelper(ticFunc, ms, message); }
void tic(const TimeMode& timeMode, const std::string& message) {
    tictocHelper(ticFunc, timeMode, message);
}

void toc() { tictocHelper(tocFunc); }

void tictocHelper(const Caller caller, const TimeMode& timeMode,
                  const std::string& message) {
    static std::unique_ptr<TicTocData> ttd = std::make_unique<TicTocData>();
    static TimeMode storedTimeMode;
    switch (caller) {
        case ticFunc:
            ttd->startTime = std::chrono::system_clock::now();
            ttd->message = message;
            storedTimeMode = timeMode;
            break;
        case tocFunc:
            auto diffTime = std::chrono::system_clock::now() - ttd->startTime;
            std::cout << "[" << ttd->message << " : \t";
            printDuration(diffTime, storedTimeMode);
            std::cout << "]" << std::endl;
    }
}

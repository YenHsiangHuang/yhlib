#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <memory>
#include <string>

// General helper functions
enum TimeMode { ms, us, ns };
void printDuration(std::chrono::system_clock::duration& t, const TimeMode& timeMode);
void printDuration(std::chrono::system_clock::duration&& t, const TimeMode& timeMode);

// Timer
struct TimerData;

class Timer {
   public:
    Timer(const std::string& message = "timer");
    ~Timer();

    void setMessage(const std::string& message = "timer") {
        this->message = message;
    }

   private:
    std::string message;
    std::shared_ptr< TimerData > data;
};

// Tic-toc as in Matlab
struct TicTocData;

enum Caller { ticFunc, tocFunc };
void tic();
void tic(const TimeMode& timeMode);
void tic(const std::string& message);
void tic(const TimeMode& timeMode, const std::string& message);
void toc();
void tictocHelper(const Caller caller, const TimeMode& = ms,
                  const std::string& message = "timer");

#endif  // TIMER_H

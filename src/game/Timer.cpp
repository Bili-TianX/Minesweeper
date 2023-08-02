#include "Timer.h"

Timer::Timer() { reset(); }

void Timer::start() {
  begin = time(nullptr);
  running = true;
}

void Timer::stop() {
  end = time(nullptr);
  running = false;
}

void Timer::reset() {
  begin = 0, end = 0;
  running = false;
}

auto Timer::getElapsedSeconds() const -> int64_t {
  if (running) {
    return time(nullptr) - begin;
  }
  
  return end - begin;
}

auto Timer::isRunning() const -> bool { return running; }

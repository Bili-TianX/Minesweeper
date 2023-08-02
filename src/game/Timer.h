#pragma once

class Timer {
 public:
  Timer();

  void start();
  void stop();
  void reset();

  [[nodiscard]] auto getElapsedSeconds() const -> int64_t;
  [[nodiscard]] auto isRunning() const -> bool;

 private:
  int64_t begin{}, end{};
  bool running{};
};
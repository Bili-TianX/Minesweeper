#include "Difficulty.h"

const Difficulty Difficulty::EASY{9, 9, 10};

const Difficulty Difficulty::MEDIUM{16, 16, 40};

const Difficulty Difficulty::EXPERT{30, 16, 99};

auto Difficulty::contains(int x, int y) const -> bool {
  return 0 <= x && x < width && 0 <= y && y < height;
}

auto Difficulty::blockCount() const -> int {
  static const int size = width * height;
  return size;
}

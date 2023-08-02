/**
 * @brief 难度设置
 */
struct Difficulty {
  int width, height, mineCount;

  static const Difficulty EASY;
  static const Difficulty MEDIUM;
  static const Difficulty EXPERT;

  auto contains(int x, int y) const -> bool;

  auto blockCount() const -> int;
};

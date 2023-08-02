/**
 * @brief 难度设置
 */
struct Difficulty {
  int width, height, mineCount;

  static const Difficulty EASY;
  static const Difficulty MEDIUM;
  static const Difficulty EXPERT;

  [[nodiscard]] auto contains(int x, int y) const -> bool;

  [[nodiscard]] auto blockCount() const -> int;
};

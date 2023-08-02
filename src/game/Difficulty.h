/**
 * @brief 难度设置
 */
struct Difficulty {
  const int width, height, mineCount;

  static const Difficulty EASY;
  static const Difficulty MEDIUM;
  static const Difficulty EXPERT;
  static const Difficulty DEFAULT;

  [[nodiscard]] auto contains(int x, int y) const -> bool;

  [[nodiscard]] auto blockCount() const -> int;
};

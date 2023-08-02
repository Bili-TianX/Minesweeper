#pragma once

/**
 * @brief 方块类型
 */
enum class BlockType : int {
  ZERO = 0,
  ONE,
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  EIGHT,
  CLOSED,
  PRESSED,
  FLAG,
  QUESTION,
  MINE,
  EXPLODED_MINE
};

using BlockMap = std::vector<std::vector<BlockType>>;

using BlockPredicate = std::function<bool(int, int)>;

auto isHiddenBlock(BlockType block) -> bool;

auto isNumberBlock(BlockType block) -> bool;

auto isPositiveNumberBlock(BlockType block) -> bool;

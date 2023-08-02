#include "BlockType.h"

auto isHiddenBlock(BlockType block) -> bool {
  return block == BlockType::CLOSED || block == BlockType::FLAG ||
         block == BlockType::QUESTION;
}

auto isNumberBlock(BlockType block) -> bool {
  return block == BlockType::ZERO || isPositiveNumberBlock(block);
}

auto isPositiveNumberBlock(BlockType block) -> bool {
  return BlockType::ONE <= block && block <= BlockType::EIGHT;
}
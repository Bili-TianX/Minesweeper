#include "Game.h"

#include "../core/Options.h"

int opened_block_count = 0;

#define GO_LOSE(i, j)                    \
  revealMines();                         \
  view[j][i] = BlockType::EXPLODED_MINE; \
  PLAY_SOUND(lightbulb_explosion);       \
  changeStatus(GameStatus::LOSE)

Game::Game(Difficulty difficulty)
    : difficulty(difficulty),
      data(difficulty.height, std::vector<BlockType>(difficulty.width)),
      view(data) {
  init();
}

void Game::generate(int excludeX, int excludeY) {
  generateMines(excludeX, excludeY);
  generateNumbers();
}

void Game::init(bool all) {
  if (all) {
    for (auto& item : data) {
      std::fill(item.begin(), item.end(), BlockType::ZERO);
    }
  }

  for (auto& item : view) {
    std::fill(item.begin(), item.end(), BlockType::CLOSED);
  }

  timer.reset();
  remaining_mines = difficulty.mineCount;
}

void Game::generateMines(int excludeX, int excludeY) {
  static std::random_device rd;
  static std::mt19937 generator(rd());

  std::vector<int> v(difficulty.blockCount());
  std::iota(v.begin(), v.end(), 0);
  v.erase(
      std::find(v.begin(), v.end(), excludeX + excludeY * difficulty.width));

  std::shuffle(v.begin(), v.end(), generator);

  for (int i = 0; i < difficulty.mineCount; ++i) {
    auto [y, x] = std::div(v[i], difficulty.width);
    data[y][x] = BlockType::MINE;
  }
}

void Game::generateNumbers() {
  for (int y = 0; y < difficulty.height; ++y) {
    for (int x = 0; x < difficulty.width; ++x) {
      if (data[y][x] == BlockType::MINE) {
        continue;
      }

      data[y][x] =
          static_cast<BlockType>(countBlocksAround(x, y, [this](int x, int y) {
            return data[y][x] == BlockType::MINE;
          }));
    }
  }
}

auto Game::countBlocksAround(int x, int y,
                             const BlockPredicate& predicate) const -> int {
  int sum = 0;
  for (int dx = -1; dx <= 1; ++dx) {
    for (int dy = -1; dy <= 1; ++dy) {
      if (dx == 0 && dy == 0) {
        continue;
      }

      auto nx = x + dx;
      auto ny = y + dy;

      if (difficulty.contains(nx, ny) && predicate(nx, ny)) {
        ++sum;
      }
    }
  }
  return sum;
}

void Game::click(Qt::MouseButton button, int x, int y, bool press) {
  if (status == GameStatus::WIN || status == GameStatus::LOSE) {
    return;
  }

  if (status == GameStatus::INIT) {
    status = GameStatus::RUN;
    generate(x, y);
  }

  if (!timer.isRunning()) {
    timer.start();
  }

  switch (button) {
    case Qt::LeftButton:
      leftClick(x, y);
      break;
    case Qt::MiddleButton:
      middleClick(x, y, press);
      break;
    case Qt::RightButton:
      rightClick(x, y);
      break;
    default:
      break;
  }
}

void Game::leftClick(int x, int y) {
  if (view[y][x] != BlockType::CLOSED) {
    return;
  }

  if (data[y][x] == BlockType::MINE) {
    GO_LOSE(x, y);
  } else {  // data[y][x] is a number
    opened_block_count = 0;
    dfs(x, y);
    postDfs();
  }
}

auto Game::checkWin() const -> bool {
  for (int y = 0; y < difficulty.height; ++y) {
    for (int x = 0; x < difficulty.width; ++x) {
      if (isHiddenBlock(view[y][x]) && data[y][x] != BlockType::MINE) {
        return false;
      }
    }
  }

  return true;
}

void Game::middleClick(int x, int y, bool press) {
  if (press) {
    if (countBlocksAround(x, y, [=](auto x, auto y) {
          return view[y][x] == BlockType::CLOSED;
        }) > 0) {
      PLAY_SOUND(button_2);
      return;
    }
  }

  if (view[y][x] == BlockType::CLOSED) {
    return;
  }

  if (!isPositiveNumberBlock(view[y][x])) {
    PLAY_SOUND(incorrect_quick_opening);
    return;
  }

  auto flag_count = countBlocksAround(
      x, y, [=](auto x, auto y) { return view[y][x] == BlockType::FLAG; });

  if (static_cast<BlockType>(flag_count) != view[y][x]) {
    PLAY_SOUND(incorrect_quick_opening);
    return;
  }

  opened_block_count = 0;

  for (int dx = -1; dx <= 1; ++dx) {
    for (int dy = -1; dy <= 1; ++dy) {
      if (dx == 0 && dy == 0) {
        continue;
      }

      auto nx = x + dx;
      auto ny = y + dy;

      if (difficulty.contains(nx, ny) && data[ny][nx] == BlockType::MINE &&
          view[ny][nx] == BlockType::CLOSED) {
        GO_LOSE(nx, ny);
        return;
      }
      dfs(nx, ny);
    }
  }

  if (opened_block_count == 0) {
    PLAY_SOUND(incorrect_quick_opening);
  } else {
    postDfs();
  }
}

void Game::rightClick(int x, int y) {
  auto& block = view[y][x];

  switch (block) {
    case BlockType::CLOSED:
      block = BlockType::FLAG;
      PLAY_SOUND(setting_flag);
      --remaining_mines;
      break;
    case BlockType::FLAG:
      block = BlockType::QUESTION;
      PLAY_SOUND(setting_question);
      ++remaining_mines;
      break;
    case BlockType::QUESTION:
      block = BlockType::CLOSED;
      PLAY_SOUND(removing_question);
      break;
    default:
      break;
  }
}

void Game::dfs(int x, int y) {
  if (!difficulty.contains(x, y) || view[y][x] != BlockType::CLOSED) {
    return;
  }

  view[y][x] = data[y][x];
  ++opened_block_count;

  if (isPositiveNumberBlock(data[y][x])) {
    return;
  }

  for (int dx = -1; dx <= 1; ++dx) {
    for (int dy = -1; dy <= 1; ++dy) {
      if (dx == 0 && dy == 0) {
        continue;
      }

      dfs(x + dx, y + dy);
    }
  }
}

void Game::postDfs() {
  PLAY_SOUND(opened_block_count > 1 ? tiles_appearing : tile_opening);
  if (checkWin()) {
    changeStatus(GameStatus::WIN);
  }
}

void Game::changeStatus(GameStatus status) {
  this->status = status;

  timer.stop();
  emit statusChanged(status);
}

void Game::revealMines() {
  for (int y = 0; y < difficulty.height; ++y) {
    for (int x = 0; x < difficulty.width; ++x) {
      if (data[y][x] == BlockType::MINE) {
        view[y][x] = BlockType::MINE;
      }
    }
  }
}

auto Game::getElapsedTime() const -> int64_t {
  return timer.getElapsedSeconds();
}

auto Game::getData() const -> const BlockMap& { return data; }
auto Game::getView() const -> const BlockMap& { return view; }
auto Game::getStatus() const -> GameStatus { return status; }
auto Game::getDifficulty() const -> const Difficulty& { return difficulty; }
auto Game::getRemainingMineCount() const -> int { return remaining_mines; }

void Game::restartGame() {
  init(false);
  status = GameStatus::RUN;
}

void Game::newGame() {
  init();
  status = GameStatus::INIT;
}
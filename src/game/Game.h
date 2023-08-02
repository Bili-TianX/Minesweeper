#pragma once

#include "BlockType.h"
#include "Difficulty.h"
#include "GameStatus.h"
#include "Timer.h"

class Game : public QObject {
  Q_OBJECT

 public:
  explicit Game(Difficulty difficulty);

  void generate(int excludeX, int excludeY);

  void click(Qt::MouseButton button, int x, int y, bool press = false);

  [[nodiscard]] auto getElapsedTime() const -> const int;
  [[nodiscard]] auto getData() const -> const BlockMap&;
  [[nodiscard]] auto getView() const -> const BlockMap&;
  [[nodiscard]] auto getStatus() const -> const GameStatus;
  [[nodiscard]] auto getDifficulty() const -> const Difficulty&;
  [[nodiscard]] auto getRemainingMineCount() const -> const int;

  void restartGame();
  void newGame();

 private:
  void init(bool all = true);

  void generateMines(int excludeX, int excludeY);
  void generateNumbers();
  [[nodiscard]] auto countBlocksAround(int x, int y,
                                       const BlockPredicate& predicate) const
      -> int;

  void dfs(int x, int y);
  void postDfs();

  void leftClick(int x, int y);
  void middleClick(int x, int y, bool press = false);
  void rightClick(int x, int y);

  void changeStatus(GameStatus status);

  void revealMines();

  [[nodiscard]] auto checkWin() const -> bool;

  Difficulty difficulty;
  BlockMap data, view;
  GameStatus status = GameStatus::INIT;
  int remaining_mines = difficulty.mineCount;

  Timer timer;

  // 声音资源
  QSound incorrect_quick_opening{":/sounds/incorrect_quick_opening.wav"};
  QSound button_2{":/sounds/button_2.wav"};
  QSound tiles_appearing{":/sounds/tiles_appearing.wav"};
  QSound tile_opening{":/sounds/tile_opening.wav"};
  QSound setting_flag{":/sounds/setting_flag.wav"};
  QSound setting_question{":/sounds/setting_question.wav"};
  QSound removing_question{":/sounds/removing_question.wav"};
  QSound lightbulb_explosion{":/sounds/lightbulb_explosion.wav"};

 signals:
  void statusChanged(GameStatus status);
};
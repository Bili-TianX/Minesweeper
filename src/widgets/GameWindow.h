#pragma once

#include "../game/Game.h"

const int BLOCK_PIXEL_WIDTH = 64, BLOCK_PIXEL_HEIGHT = 64;

/**
 * @brief 游戏窗口
 */
class GameWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit GameWindow(Difficulty difficulty);

  [[nodiscard]] auto getGame() const -> const Game&;

 private:
  void paintEvent(QPaintEvent* event) override;

  void mouseDoubleClickEvent(QMouseEvent* event) override;

  void mousePressEvent(QMouseEvent* event) override;

  void mouseReleaseEvent(QMouseEvent* event) override;

  Game game;

  bool middle_button_pressed = false;
  int button_x = -1, button_y = -1;

  // QTimer timer{this};

  // 图像资源
  QMap<BlockType, QPixmap> block_images = {
      {BlockType::ZERO, QPixmap(":/images/blocks/0.png")},
      {BlockType::ONE, QPixmap(":/images/blocks/1.png")},
      {BlockType::TWO, QPixmap(":/images/blocks/2.png")},
      {BlockType::THREE, QPixmap(":/images/blocks/3.png")},
      {BlockType::FOUR, QPixmap(":/images/blocks/4.png")},
      {BlockType::FIVE, QPixmap(":/images/blocks/5.png")},
      {BlockType::SIX, QPixmap(":/images/blocks/6.png")},
      {BlockType::SEVEN, QPixmap(":/images/blocks/7.png")},
      {BlockType::EIGHT, QPixmap(":/images/blocks/8.png")},
      {BlockType::CLOSED, QPixmap(":/images/blocks/closed.png")},
      {BlockType::PRESSED, QPixmap(":/images/blocks/pressed.png")},
      {BlockType::FLAG, QPixmap(":/images/blocks/flag.png")},
      {BlockType::QUESTION, QPixmap(":/images/blocks/question.png")},
      {BlockType::MINE, QPixmap(":/images/blocks/mine.png")},
      {BlockType::EXPLODED_MINE, QPixmap(":/images/blocks/exploded_mine.png")},
  };

  QPixmap bg{":/images/bgTile.jpg"};
  QPixmap game_back{"images/bar/bm_icon_game_back.png"};
  QPixmap game_plus{"images/bar/bm_icon_game_plus.png"};
  QPixmap help{"images/bar/bm_icon_help.png"};
  QPixmap options{"images/bar/bm_icon_options.png"};
  QPixmap sound_off{"images/bar/bm_icon_sound_off.png"};
  QPixmap sound_on{"images/bar/bm_icon_sound_on.png"};

 private slots:
  void onGameStatusChanged(GameStatus status);
};
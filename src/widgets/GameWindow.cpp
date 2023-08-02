#include "GameWindow.h"

#include "GameFinishDialog.h"

GameWindow::GameWindow(Difficulty difficulty) : game(difficulty) {
  setFixedSize(BLOCK_PIXEL_WIDTH * difficulty.width,
               BLOCK_PIXEL_HEIGHT * difficulty.height);

  connect(&game, SIGNAL(statusChanged(GameStatus)), this,
          SLOT(onGameStatusChanged(GameStatus)));
}

void GameWindow::paintEvent(QPaintEvent* event) {
#define DRAW_BLOCK_SIZED(image, width, height)                             \
  painter.drawPixmap(                                                      \
      x* BLOCK_PIXEL_WIDTH + (BLOCK_PIXEL_WIDTH - (width)) / 2,            \
      y * BLOCK_PIXEL_HEIGHT + (BLOCK_PIXEL_HEIGHT - (height)) / 2, width, \
      height, image)

#define DRAW_BLOCK(image) \
  DRAW_BLOCK_SIZED(image, BLOCK_PIXEL_WIDTH, BLOCK_PIXEL_HEIGHT)

  auto view = game.getView();

  QPainter painter(this);

  painter.drawTiledPixmap(rect(), bg);

  for (int y = 0; y < view.size(); ++y) {
    for (int x = 0; x < view[y].size(); ++x) {
      auto block = view[y][x];

      if (block == BlockType::MINE) {
        DRAW_BLOCK(block_images[BlockType::CLOSED]);
        DRAW_BLOCK_SIZED(OPTIONS->getMineImage(), MINE_PIXEL_WIDTH,
                         MINE_PIXEL_HEIGHT);
      } else {
        DRAW_BLOCK(block_images[block]);
      }
    }
  }

  if (middle_button_pressed) {
    for (int dx = -1; dx <= 1; ++dx) {
      for (int dy = -1; dy <= 1; ++dy) {
        if (dx == 0 && dy == 0) {
          continue;
        }

        auto x = button_x + dx;
        auto y = button_y + dy;

        if (game.getDifficulty().contains(x, y) &&
            game.getView()[y][x] == BlockType::CLOSED) {
          DRAW_BLOCK(block_images[BlockType::PRESSED]);
        }
      }
    }
  }

  painter.end();
}

void GameWindow::mouseDoubleClickEvent(QMouseEvent* event) {
  if (event->button() != Qt::LeftButton) {
    return;
  }

  // translate it into a middle click
  QMouseEvent e(event->type(), event->localPos(), Qt::MiddleButton,
                event->buttons(), event->modifiers());

  mousePressEvent(&e);

  // for a visual press
  QTimer::singleShot(120, [=]() {
    middle_button_pressed = false;
    repaint();
  });
}

void GameWindow::mousePressEvent(QMouseEvent* event) {
  if (event->button() != Qt::MiddleButton) {
    return;
  }

  middle_button_pressed = true;

  button_x = event->x() / BLOCK_PIXEL_WIDTH;
  button_y = event->y() / BLOCK_PIXEL_HEIGHT;

  game.click(Qt::MiddleButton, button_x, button_y, true);

  repaint();
}

void GameWindow::mouseReleaseEvent(QMouseEvent* event) {
  auto x = event->x() / BLOCK_PIXEL_WIDTH;
  auto y = event->y() / BLOCK_PIXEL_HEIGHT;

  if (event->button() == Qt::MiddleButton) {
    middle_button_pressed = false;
  }

  game.click(event->button(), x, y);
  repaint();
}

auto GameWindow::getGame() const -> const Game& { return game; }

void GameWindow::onGameStatusChanged(GameStatus status) {
  int delay{};  // Wait sound

  switch (status) {
    case GameStatus::WIN:
      delay = 50;
      break;
    case GameStatus::LOSE:
      delay = 1300;
      break;
    default:
      return;
  }

  QTimer::singleShot(delay, [=]() {
    GameFinishDialog dialog(this, status);
    dialog.exec();

    switch (dialog.getResult()) {
      case GameFinishDialog::Result::NEW:
        game.newGame();
        break;
      case GameFinishDialog::Result::RESTART:
        game.restartGame();
        break;
      case GameFinishDialog::Result::EXIT:
        QApplication::exit(0);
        return;
    }

    repaint();
  });
}

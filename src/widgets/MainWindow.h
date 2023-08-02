#pragma once

#include "GameWindow.h"

class MainWindow : public QWidget {
  Q_OBJECT

 public:
  explicit MainWindow(Difficulty difficulty);

 private:
  QTimer timer{this};

  QVBoxLayout widget_layout{this};
  QHBoxLayout bar_layout, game_layout;

  QLabel icon_timer_label{"<img src=\":/images/bar/icon-timer.png\"/>", this};
  QLabel timer_label{this};
  QLabel icon_mine_label{"<img src=\":/images/bar/icon-mine.png\"/>", this};
  QLabel mine_label{this};

  QPushButton option_button{this};

  GameWindow game_window;

 private slots:
  void updateStatusBar();

  void onOptionButtonClicked();
};
#pragma once

#include "../game/GameStatus.h"

class GameFinishDialog : public QDialog {
 public:
  enum class Result { NEW, RESTART, EXIT };

  explicit GameFinishDialog(QWidget* parent, GameStatus status);

  [[nodiscard]] auto getResult() const -> const Result;

 private:
  void closeEvent(QCloseEvent* event) override;

  QVBoxLayout widget_layout{this};

  QLabel title_label{this};

  QPushButton new_button{"新游戏", this};
  QPushButton restart_button{"重新开始", this};
  QPushButton exit_button{"退出游戏", this};

  QSound MS_sting_win{":/sounds/MS_sting_win.wav"};
  QSound MS_sting_lose{":/sounds/MS_sting_lose.wav"};

  Result result;
};
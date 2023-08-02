#include "GameFinishDialog.h"

GameFinishDialog::GameFinishDialog(QWidget* parent, GameStatus status)
    : QDialog(parent) {
  setWindowTitle("游戏结束");

  if (status == GameStatus::WIN) {
    MS_sting_win.play();
    title_label.setText("<h2>你赢了</h2>");
  } else if (status == GameStatus::LOSE) {
    MS_sting_lose.play();
    title_label.setText("<h2>你输了</h2>");
  }

  title_label.setAlignment(Qt::AlignCenter);

  widget_layout.addStretch();
  widget_layout.addWidget(&title_label);
  widget_layout.addWidget(&new_button);
  widget_layout.addWidget(&restart_button);
  widget_layout.addWidget(&exit_button);
  widget_layout.addStretch();

  connect(&new_button, &QPushButton::clicked, this, [&]() {
    result = Result::NEW;
    accept();
  });
  connect(&restart_button, &QPushButton::clicked, this, [&]() {
    result = Result::RESTART;
    accept();
  });
  connect(&exit_button, &QPushButton::clicked, this, [&]() {
    result = Result::EXIT;
    accept();
  });

  adjustSize();
}

auto GameFinishDialog::getResult() const -> Result { return result; }

void GameFinishDialog::closeEvent(QCloseEvent* event) {
  if (QMessageBox::question(this, "确认", "是否要退出游戏？") ==
      QMessageBox::Yes) {
    result = Result::EXIT;
    accept();
  } else {
    event->ignore();
  }
}

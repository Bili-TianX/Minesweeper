#include "MainWindow.h"

MainWindow::MainWindow(Difficulty difficulty) : game_window(difficulty) {
  setWindowTitle("扫雷");

  icon_timer_label.setAlignment(Qt::AlignCenter);
  timer_label.setAlignment(Qt::AlignCenter);
  icon_mine_label.setAlignment(Qt::AlignCenter);
  mine_label.setAlignment(Qt::AlignCenter);

  option_button.setIcon(QIcon(":/images/bar/bm_icon_options"));
  option_button.setFixedSize(64, 64);
  option_button.setIconSize(option_button.size());

  bar_layout.addStretch(5);
  bar_layout.addWidget(&icon_timer_label);
  bar_layout.addStretch(1);
  bar_layout.addWidget(&timer_label);
  bar_layout.addStretch(2);
  bar_layout.addWidget(&icon_mine_label);
  bar_layout.addStretch(1);
  bar_layout.addWidget(&mine_label);
  bar_layout.addStretch(5);
  bar_layout.addWidget(&option_button);

  game_layout.addStretch();
  game_layout.addWidget(&game_window);
  game_layout.addStretch();

  widget_layout.addStretch();
  widget_layout.addLayout(&bar_layout);
  widget_layout.addLayout(&game_layout);
  widget_layout.addStretch();

  connect(&option_button, SIGNAL(clicked()), this,
          SLOT(onOptionButtonClicked()));
  connect(&timer, SIGNAL(timeout()), this, SLOT(updateStatusBar()));
  timer.start(50);
}

void MainWindow::updateStatusBar() {
  const Game& game = game_window.getGame();

  const auto [min, sec] = std::lldiv(game.getElapsedTime(), 60);

  timer_label.setText(QStringLiteral("%0:%1")
                          .arg(min, 2, 10, QLatin1Char('0'))
                          .arg(sec, 2, 10, QLatin1Char('0')));
  mine_label.setText(QStringLiteral("%0").arg(game.getRemainingMineCount()));
}

void MainWindow::onOptionButtonClicked() {
  // TODO
}

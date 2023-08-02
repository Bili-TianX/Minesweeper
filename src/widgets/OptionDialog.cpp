#include "OptionDialog.h"

#include "../core/Options.h"
#include "GameWindow.h"

OptionDialog::OptionDialog(QWidget* parent) : QDialog(parent) {
  setWindowTitle("设置");
  title_label.setAlignment(Qt::AlignCenter);

  sound_enable_input.setChecked(OPTIONS->isSoundEnabled());
  sound_enable_input.setFixedSize(64, 64);
  mine_count_input.setText(QString::number(OPTIONS->getMineCount()));
  mine_count_input.setAlignment(Qt::AlignCenter);
  mine_count_input.setValidator(new QIntValidator(this));

  preview_mine_style_label.setPixmap(OPTIONS->getMineImage());
  preview_mine_style_label.setAlignment(Qt::AlignCenter);

  static QStringList styles;

  if (styles.empty()) {
    for (int i = 0; i < MINE_STYLE_COUNT; ++i) {
      styles.append(QString::number(i));
    }
  }

  mine_style_input.addItems(styles);
  mine_style_input.setCurrentIndex(OPTIONS->getMineStyle());

  form.addRow("启用声音", &sound_enable_input);
  form.addRow("地雷数量", &mine_count_input);
  form.addRow("地雷样式", &mine_style_input);

  button_layout.addWidget(&confirm_button);
  button_layout.addWidget(&cancel_button);

  widget_layout.addWidget(&title_label);
  widget_layout.addLayout(&form);
  widget_layout.addWidget(&preview_mine_style_label);
  widget_layout.addLayout(&button_layout);

  connect(&confirm_button, SIGNAL(clicked()), this, SLOT(onConfirm()));
  connect(&cancel_button, SIGNAL(clicked()), this, SLOT(onCancel()));
  connect(&mine_style_input, SIGNAL(currentIndexChanged(int)), this,
          SLOT(onStyleChanged(int)));

  adjustSize();
}

void OptionDialog::onStyleChanged(int index) {
  preview_mine_style_label.setPixmap(
      OPTIONS->getMineImage(mine_style_input.currentText().toInt()));
}

void OptionDialog::onConfirm() {
  auto mine_count = mine_count_input.text().toInt();
  if (mine_count >= Difficulty::DEFAULT.blockCount() || mine_count == 0) {
    QMessageBox::critical(this, "错误", "地雷数量过多（或过少）");
    return;
  }

  if (OPTIONS->getMineCount() != mine_count) {
    QMessageBox::warning(this, "警告", "地雷数量将在游戏重启后生效");
  }

  OPTIONS->setSoundEnabled(sound_enable_input.isChecked());
  OPTIONS->setMineCount(mine_count);
  OPTIONS->setMineStyle(mine_style_input.currentText().toInt());
  accept();
}

void OptionDialog::onCancel() { reject(); }
#pragma once

class OptionDialog : public QDialog {
  Q_OBJECT
 public:
  explicit OptionDialog(QWidget* parent);

 private:
  QVBoxLayout widget_layout{this};
  QFormLayout form;
  QHBoxLayout button_layout;

  QLabel title_label{"设置", this};

  QCheckBox sound_enable_input{this};
  QLineEdit mine_count_input{this};
  QComboBox mine_style_input{this};

  QLabel preview_mine_style_label{this};
  QPushButton confirm_button{"确定", this}, cancel_button{"取消", this};

 private slots:
  void onStyleChanged(int index);

  void onConfirm();
  void onCancel();
};
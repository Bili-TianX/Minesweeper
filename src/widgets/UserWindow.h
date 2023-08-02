#pragma once

#include "../core/UserManager.h"

class UserWindow : public QDialog {
  Q_OBJECT

 public:
  UserWindow();

 private slots:

  void onLogin();

  void onRegister();

 private:
  UserManager manager;

  QVBoxLayout widget_layout{this};
  QFormLayout form;
  QHBoxLayout button_layout;

  QLabel title_label{"<h2>扫雷</h2>", this};

  QLineEdit account_input{this}, password_input{this};

  QPushButton login_button{"登录", this}, register_button{"注册", this},
      exit_button{"退出", this};
};
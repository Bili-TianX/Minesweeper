#pragma once

#include "../core/UserManager.h"

class RegisterDialog : public QDialog {
  Q_OBJECT
 public:
  RegisterDialog(QWidget* parent, UserManager* manager);

 private:
  UserManager* manager;

  QVBoxLayout widget_layout{this};
  QFormLayout form;
  QHBoxLayout button_layout;

  QLabel title_label{"<h2>注册</h2>", this};

  QLineEdit account_input{this}, password_input{this},
      confirm_password_input{this};

  QPushButton confirm_button{"确定", this}, cancel_button{"取消", this};

  QSqlDatabase database;

 private slots:
  void onConfirm();
};
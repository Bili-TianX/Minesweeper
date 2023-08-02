#include "UserWindow.h"

#include "RegisterDialog.h"

UserWindow::UserWindow() {
  setWindowTitle("登录");

  title_label.setAlignment(Qt::AlignCenter);
  password_input.setEchoMode(QLineEdit::Password);

  form.addRow("账号", &account_input);
  form.addRow("密码", &password_input);

  button_layout.addWidget(&login_button);
  button_layout.addWidget(&register_button);
  button_layout.addWidget(&exit_button);

  widget_layout.addStretch();
  widget_layout.addWidget(&title_label);
  widget_layout.addLayout(&form);
  widget_layout.addLayout(&button_layout);
  widget_layout.addStretch();

  connect(&login_button, SIGNAL(clicked()), this, SLOT(onLogin()));
  connect(&register_button, SIGNAL(clicked()), this, SLOT(onRegister()));
  connect(&exit_button, SIGNAL(clicked()), this, SLOT(reject()));

  adjustSize();
}

void UserWindow::onLogin() {
  auto account = account_input.text();
  auto password = password_input.text();

  auto user = manager.getUser(account);

  if (user) {
    if (password == user->password) {
      accept();
    } else {
      QMessageBox::critical(this, "错误", "密码错误");
    }
  } else {
    QMessageBox::critical(this, "错误", "未知的用户");
  }
}

void UserWindow::onRegister() {
  RegisterDialog dialog(this, manager);
  if (dialog.exec() == QDialog::Accepted) {
    QMessageBox::information(this, "提示", "注册成功");
  }
}
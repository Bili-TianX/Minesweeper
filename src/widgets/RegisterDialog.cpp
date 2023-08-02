#include "RegisterDialog.h"

RegisterDialog::RegisterDialog(QWidget* parent, const UserManager& manager)
    : QDialog(parent), manager(manager) {
  setWindowTitle("注册");

  title_label.setAlignment(Qt::AlignCenter);
  password_input.setEchoMode(QLineEdit::Password);
  confirm_password_input.setEchoMode(QLineEdit::Password);

  form.addRow("账号", &account_input);
  form.addRow("密码", &password_input);
  form.addRow("确认密码", &confirm_password_input);

  button_layout.addWidget(&confirm_button);
  button_layout.addWidget(&cancel_button);

  widget_layout.addStretch();
  widget_layout.addWidget(&title_label);
  widget_layout.addLayout(&form);
  widget_layout.addLayout(&button_layout);
  widget_layout.addStretch();

  connect(&confirm_button, SIGNAL(clicked()), this, SLOT(onConfirm()));
  connect(&cancel_button, SIGNAL(clicked()), this, SLOT(reject()));

  adjustSize();
}

void RegisterDialog::onConfirm() {
  auto account = account_input.text();
  auto password = password_input.text();
  auto confirm_password = confirm_password_input.text();

  if (account.isEmpty()) {
    QMessageBox::critical(this, "错误", "账号不能为空");
    return;
  }
  if (password.isEmpty()) {
    QMessageBox::critical(this, "错误", "密码不能为空");
    return;
  }

  auto user = manager.getUser(account);

  if (!user) {
    if (password == confirm_password) {
      manager.addUser({password, account});
      accept();
    } else {
      QMessageBox::critical(this, "错误", "两次输入的密码不一致");
    }
  } else {
    QMessageBox::critical(this, "错误", "用户已存在");
  }
}
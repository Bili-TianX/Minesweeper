#pragma once

struct User {
  QString account, password;
};

class UserManager {
 public:
  UserManager();

  [[nodiscard]] auto getUser(QStringView account) const -> std::optional<User>;

  void addUser(const User &user) const;

 private:
  void createTable() const;

  QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
};
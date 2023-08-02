#include "UserManager.h"

UserManager::UserManager() {
  database.setDatabaseName("database.db");
  database.open();
}

auto UserManager::getUser(QStringView account) const -> std::optional<User> {
  auto q = database.exec(
      QStringLiteral("SELECT * FROM users WHERE account=\"%0\"").arg(account));

  if (q.next()) {
    return std::make_optional<User>(
        {q.value(0).toString(), q.value(1).toString()});
  } else {
    return std::nullopt;
  }
}

void UserManager::addUser(const User &user) const {
  database.exec(
      QStringLiteral(
          "INSERT INTO users (account, password) VALUES (\"%0\", \"%1\");")
          .arg(user.account)
          .arg(user.password));
}

void UserManager::createTable() const {
  database.exec(QStringLiteral(R"(
CREATE TABLE IF NOT EXISTS users
(
    account  TEXT unique,
    password TEXT
);
)"));
}

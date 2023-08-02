#include "widgets/MainWindow.h"
#include "widgets/UserWindow.h"

auto main(int argc, char* argv[]) -> int {
  QApplication application(argc, argv);

  QApplication::setWindowIcon(QIcon(":/images/icon.ico"));
  QApplication::setFont(QFont(QApplication::font().family(), 16));

  QFile file(":/QSS/MacOS.qss");
  if (file.open(QIODevice::ReadOnly)) {
    application.setStyleSheet(QString(file.readAll()));
    file.close();
  }

  UserWindow w;
  if (w.exec() == QDialog::Accepted) {
    MainWindow w({Difficulty::DEFAULT.width, Difficulty::DEFAULT.height,
                  OPTIONS->getMineCount()});
    w.show();
    return QApplication::exec();
  }

  return 0;
}

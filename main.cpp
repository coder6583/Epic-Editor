#include "mainwindow.hpp"

int main(int argc, char * argv[])
{
  QApplication app(argc, argv);

  MainWindow window;

  window.showMaximized();
  window.setWindowTitle("Text Editor");
  window.show();

  QFontDatabase::addApplicationFont("Menlo-Regular.ttf");

  return app.exec();
}

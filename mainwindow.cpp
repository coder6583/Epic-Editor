#include "mainwindow.hpp"
#include <QColor>
#include <QFileInfo>
#include <iostream>
#include <string>
#include <sstream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), textedit(new QTextEdit), tabs(new QTabWidget), tree(new QTreeView),
          model(new QFileSystemModel)
{
  setStyleSheet("QTextedit{font : 16pt 'Menlo';}");

  this -> font.setFamily("Menlo");
  this -> font.setStyleHint(QFont::Monospace);
  this -> font.setFixedPitch(true);
  this -> font.setPointSize(16.0);
  QApplication::setStyle(QStyleFactory::create("Fusion"));
  QPalette p;
  p = qApp->palette();
  p.setColor(QPalette::Window, QColor(68,69,72));
  p.setColor(QPalette::Button, QColor(68,69,72));
  p.setColor(QPalette::Base, QColor(50, 50, 50));
  p.setColor(QPalette::Highlight, QColor(68,69,72));
  p.setColor(QPalette::ButtonText, QColor(55,55,55));
  p.setColor(QPalette::Text, QColor(240,240,240));
  
  qApp->setPalette(p);
  textedit->setPalette(p);

  QAction *quit = new QAction("&Quit", this);
  QAction *newwindow = new QAction("&New Window", this);
  QAction *newfile = new QAction("&New File", this);
  QAction *openfile = new QAction("&Open File", this);
  QAction *openfolder = new QAction("&Open Folder", this);
  QAction *reopenproject = new QAction("&Reopen Project", this);
  QAction *savefile = new QAction("&Save File", this);
  QAction *saveas = new QAction("&Save As", this);
  QAction *saveall = new QAction("&Save All", this);
  QAction *closetab = new QAction("&Close Tab", this);
  QAction *closepane = new QAction("&Close Pane", this);
  QAction *closewindow = new QAction("&Close Window", this);

  QAction *undo = new QAction("&Undo", this);
  QAction *redo = new QAction("&Redo", this);
  QAction *cut = new QAction("&Cut", this);
  QAction *copy = new QAction("&Copy", this);
  QAction *copypath = new QAction("&Copy Path", this);
  QAction *paste = new QAction("&Paste", this);
  QAction *pastewithoutreformatting = new QAction("&Paste Without Reformatting", this);
  QAction *selectall = new QAction("&Select All", this);
  QAction *togglecomment = new QAction("&Toggle Comment", this);

  QAction *fullscreen = new QAction("&Full Screen", this);
  QAction *increasefontsize = new QAction("&Increase Font Size", this);
  QAction *decreasefontsize = new QAction("&Decrease Font Size", this);
  QAction *resetfontsize = new QAction("&Reset Font Size", this);

  QAction *addselectionabove = new QAction("&Add Selection Above", this);
  QAction *addselectionbelow = new QAction("&Add Selection Below", this);
  QAction *singleselection = new QAction("&Single Selection", this);
  QAction *selectline = new QAction("&Select Line", this);
  QAction *selectword = new QAction("&Select Word", this);

  QAction *findinbuffer = new QAction("&Find In Buffer", this);
  QAction *replaceinbuffer = new QAction("&Replace In Buffer", this);
  QAction *findinproject = new QAction("&Find In Project", this);

  QMenu *file;
  file = menuBar() -> addMenu("&File");
  file -> addAction(newwindow);
  file -> addAction(newfile);
  file -> addAction(openfile);
  file -> addAction(openfolder);
  // file -> addAction(addprojectfolder);
  file -> addAction(reopenproject);
  // file -> addAction(reopenlastitem);
  file -> addSeparator();
  file -> addAction(savefile);
  file -> addAction(saveas);
  file -> addAction(saveall);
  file -> addSeparator();
  file -> addAction(closetab);
  file -> addAction(closepane);
  file -> addAction(closewindow);
  file -> addSeparator();
  file -> addAction(quit);

  QMenu *edit;
  edit = menuBar() -> addMenu("&Edit");
  edit -> addAction(undo);
  edit -> addAction(redo);
  edit -> addSeparator();
  edit -> addAction(cut);
  edit -> addAction(copy);
  edit -> addAction(copypath);
  edit -> addAction(paste);
  edit -> addAction(pastewithoutreformatting);
  edit -> addAction(selectall);
  edit -> addSeparator();
  edit -> addAction(togglecomment);

  QMenu *view;
  view = menuBar() -> addMenu("&View");
  view -> addAction(fullscreen);
  view -> addAction(increasefontsize);
  view -> addAction(decreasefontsize);
  view -> addAction(resetfontsize);

  QMenu *selection;
  selection = menuBar() -> addMenu("&Selection");
  selection -> addAction(addselectionabove);
  selection -> addAction(addselectionbelow);
  selection -> addAction(singleselection);
  selection -> addAction(selectline);
  selection -> addAction(selectword);

  QMenu *find;
  find = menuBar() -> addMenu("&Find");
  find -> addAction(findinbuffer);
  find -> addAction(replaceinbuffer);
  find -> addAction(findinproject);

  quit -> setShortcut(tr("CTRL+Q"));
  newwindow -> setShortcut(tr("CTRL+SHIFT+N"));
  newfile -> setShortcut(tr("CTRL+N"));
  openfile -> setShortcut(tr("CTRL+O"));
  openfolder -> setShortcut(tr("CTRL+SHIFT+O"));
  savefile -> setShortcut(tr("CTRL+S"));
  saveas -> setShortcut(tr("CTRL+SHIFT+S"));

  menuBar() -> setStyleSheet("background-color: #ffffff; selection-background-color: #b0b0b0");

  QPalette menubarpalette;
  // menubarpalette.setColor(menuBar() -> backgroundRole(), Qt::white);
  menubarpalette.setColor(menuBar() -> foregroundRole(), QColor(50, 50, 50));
  menuBar() -> setPalette(menubarpalette);

  tabs -> setCurrentWidget(textedit);
  tabs -> setTabsClosable(true);

  setCentralWidget(tabs);

  connect(quit, &QAction::triggered, this, &QApplication::quit);
  connect(newwindow, &QAction::triggered, this, &MainWindow::NewWindow);
  connect(newfile, &QAction::triggered, this, &MainWindow::NewFile);
  connect(tabs, SIGNAL(tabCloseRequested(int)), this, SLOT(deleteTab(int)));
  connect(openfile, &QAction::triggered, this, &MainWindow::OpenFile);
  connect(openfolder, &QAction::triggered, this, &MainWindow::OpenFolder);
  connect(this -> tree, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(ifdoubleclicked(QModelIndex)));
  connect(savefile, &QAction::triggered, this, &MainWindow::SaveFile);
  connect(saveas, &QAction::triggered, this, &MainWindow::SaveAs);
}

void MainWindow::deleteTab(int index)
{
  this -> tabs -> removeTab(index);
}

void MainWindow::ifdoubleclicked(QModelIndex item)
{
  QString file_name = item.data(QFileSystemModel::FilePathRole).toString();
  QFile file(file_name);
  file.open(QIODevice::ReadWrite | QFile::Text);
  QTextStream ReadFile(&file);
  QFileInfo openfilename(file_name);
  QTextEdit *newtextedit = new QTextEdit();
  //newtextedit -> setCurrentFont(this -> font);
  newtextedit -> setStyleSheet("font: 16pt Menlo;");
  highlighter = new Highlighter(newtextedit -> document());
  QFontMetricsF fm (font);
  auto stopWidth = 3 * fm.width(' ');
  newtextedit->setTabStopDistance(stopWidth);
  this -> m_textedit.insert(std::make_pair(openfilename.fileName(), newtextedit));
  newtextedit -> setText(ReadFile.readAll());
  std::cout << file_name.toStdString() << std::endl;
  this -> tabs -> addTab(this -> m_textedit[openfilename.fileName()],openfilename.fileName());
}

void MainWindow::NewWindow()
{
  MainWindow *nw = new MainWindow();

  nw -> showMaximized();
  nw -> setWindowTitle("untitled");
  nw -> show();
}

void MainWindow::NewFile()
{
  QTextEdit *newtextedit = new QTextEdit();
  newtextedit -> setStyleSheet("font: 16pt Menlo;");
  QFontMetricsF fm (font);
  auto stopWidth = 3 * fm.width(' ');
  newtextedit->setTabStopDistance(stopWidth);
  highlighter = new Highlighter(newtextedit -> document());
  this -> untitledcount++;
  QString tabtitle = "untitled" + QString::number(this -> untitledcount);
  this -> m_textedit.insert(std::make_pair(tabtitle, newtextedit));
  this -> tabs -> addTab(newtextedit, tabtitle);
}

void MainWindow::OpenFile()
{
  QString file_name = QFileDialog::getOpenFileName(this, "Open File", QDir::currentPath());
  QFile file(file_name);
  file.open(QIODevice::ReadWrite | QFile::Text);
  QTextStream ReadFile(&file);
  QFileInfo openfilename(file_name);
  QTextEdit *newtextedit = new QTextEdit();
  highlighter = new Highlighter(newtextedit -> document());
  QFontMetricsF fm (font);
  auto stopWidth = 3 * fm.width(' ');
  newtextedit->setTabStopDistance(stopWidth);
  this -> m_textedit.insert(std::make_pair(openfilename.fileName(), newtextedit));
  newtextedit -> setText(ReadFile.readAll());
  this -> tabs -> addTab(this -> m_textedit[openfilename.fileName()],openfilename.fileName());
}


void MainWindow::OpenFolder()
{
  QString folder_name = QFileDialog::getExistingDirectory(this, "Open Folder", QDir::currentPath());
  if(this -> folderIsOpen == true)
  {
    MainWindow *nw = new MainWindow();
    QFileInfo readFolder(folder_name);
    QDockWidget *dock = new QDockWidget(tr("Folder"), nw);
    dock -> setAllowedAreas(Qt::LeftDockWidgetArea);

    nw -> model -> setRootPath(folder_name);
    nw -> tree -> setModel(nw -> model);
    nw -> tree -> setRootIndex(nw -> model -> index(folder_name));
    std::cout << folder_name.toStdString() << std::endl;
    nw -> tree -> setHeaderHidden(true);
    nw -> tree -> setUniformRowHeights(false);
    nw -> tree -> hideColumn(1);
    nw -> tree -> hideColumn(2);
    nw -> tree -> hideColumn(3);

    dock -> setWidget(nw -> tree);
    dock -> setFeatures(QDockWidget::NoDockWidgetFeatures);
    nw -> addDockWidget(Qt::LeftDockWidgetArea, dock);
    dock -> show();

    nw -> showMaximized();
    nw -> setWindowTitle(readFolder.fileName());
    nw -> show();

    this -> folderIsOpen = true;
  }
  else if(this -> folderIsOpen == false )
  {
    QDockWidget *dock = new QDockWidget(tr("Folder"), this);
    QFileInfo readFolder(folder_name);
    dock -> setAllowedAreas(Qt::LeftDockWidgetArea);
    this -> model -> setRootPath(folder_name);

    this -> tree -> setModel(this -> model);
    this -> tree -> setRootIndex(this -> model -> index(folder_name));
    std::cout << folder_name.toStdString() << std::endl;
    this -> tree -> setHeaderHidden(true);
    this -> tree -> setUniformRowHeights(false);
    this -> tree -> hideColumn(1);
    this -> tree -> hideColumn(2);
    this -> tree -> hideColumn(3);

    dock -> setWidget(this -> tree);
    dock -> setFeatures(QDockWidget::NoDockWidgetFeatures);
    dock -> show();
    this -> addDockWidget(Qt::LeftDockWidgetArea, dock);

    this -> setWindowTitle(readFolder.fileName());

    this -> folderIsOpen = true;
  }
}

bool MainWindow::SaveFile()
{
  QString errorMessage;

  QGuiApplication::setOverrideCursor(Qt::WaitCursor);
  QString fileName = this -> tabs -> tabText(this -> tabs -> currentIndex());
  QString filePath = QDir::currentPath() + "/" + fileName;
  QSaveFile file(filePath);
  if(file.open(QFile::WriteOnly | QFile::Text))
  {
    QTextStream out(&file);
    std::cout << this -> m_textedit[this -> tabs -> tabText(this -> tabs -> currentIndex())] -> toPlainText().toStdString() << std::endl;
    // I have to direct this textedit so that it points to new
    out << this -> m_textedit[this -> tabs -> tabText(this -> tabs -> currentIndex())] -> toPlainText();
    if(!file.commit())
    {
      errorMessage = tr("Cannot write file %1:\n%2").arg(QDir::toNativeSeparators(filePath), file.errorString());
    }
  }
  else
  {
    errorMessage = tr("Cannot open file %1 for writing:\n%2").arg(QDir::toNativeSeparators(filePath), file.errorString());
  }
  QGuiApplication::restoreOverrideCursor();

  if(!errorMessage.isEmpty())
  {
    QMessageBox::warning(this, tr("Application"), errorMessage);
    return false;
  }
  return true;
}

bool MainWindow::save(const QString &filePath)
{
  QString errorMessage;

  QGuiApplication::setOverrideCursor(Qt::WaitCursor);
  std::stringstream filePathss(filePath.toStdString());
  std::string fileName;
  while(std::getline(filePathss, fileName, '/'));
  QSaveFile file(filePath);
  if(file.open(QFile::WriteOnly | QFile::Text))
  {
    QTextStream out(&file);
    // I have to direct this textedit so that it points to new
    out << this -> m_textedit[QString::fromStdString(fileName)] -> toPlainText();
    if(!file.commit())
    {
      errorMessage = tr("Cannot write file %1:\n%2").arg(QDir::toNativeSeparators(filePath), file.errorString());
    }
  }
  else
  {
    errorMessage = tr("Cannot open file %1 for writing:\n%2").arg(QDir::toNativeSeparators(filePath), file.errorString());
  }
  QGuiApplication::restoreOverrideCursor();

  if(!errorMessage.isEmpty())
  {
    QMessageBox::warning(this, tr("Application"), errorMessage);
    return false;
  }
  return true;
}

bool MainWindow::SaveAs()
{
  QFileDialog dialog(this);
  dialog.setWindowModality(Qt::WindowModal);
  dialog.setAcceptMode(QFileDialog::AcceptSave);
  if(dialog.exec() != QDialog::Accepted)
    return false;
  std::stringstream filePathss(dialog.selectedFiles().first().toStdString());
  std::string fileName;
  while(std::getline(filePathss, fileName, '/'));
  auto nodeHandler = this -> m_textedit.extract(this -> tabs -> tabText(this -> tabs -> currentIndex()));
  nodeHandler.key() = QString::fromStdString(fileName);
  this -> m_textedit.insert(std::move(nodeHandler));
  this -> tabs -> setTabText(this -> tabs -> currentIndex(), QString::fromStdString(fileName));
  return this -> save(dialog.selectedFiles().first());
}

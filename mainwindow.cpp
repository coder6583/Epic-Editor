#include "mainwindow.hpp"
#include <QColor>
#include <QFileInfo>
#include <iostream>
#include <string>
#include <sstream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), textedit(new QTextEdit), tabs(new QTabWidget), tree(new QTreeView),
          model(new QFileSystemModel)
{
  this -> setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
  this -> clipboard = QApplication::clipboard();
  this -> openedprojectsfile.open("openedfiles.txt", std::ofstream::app);
  if(!openedprojectsfile.is_open())
    return;

  setStyleSheet("QTextEdit{font : 16pt 'Menlo';}");

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
  //QAction *reopenproject = new QAction("&Reopen Project", this);
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
  // QAction *pastewithoutreformatting = new QAction("&Paste Without Reformatting", this);
  QAction *selectall = new QAction("&Select All", this);
  QAction *togglecomment = new QAction("&Toggle Comment", this);

  QAction *fullscreen = new QAction("&Full Screen", this);
  QAction *increasefontsize = new QAction("&Increase Font Size", this);
  QAction *decreasefontsize = new QAction("&Decrease Font Size", this);
  QAction *resetfontsize = new QAction("&Reset Font Size", this);

  // QAction *addselectionabove = new QAction("&Add Selection Above", this);
  // QAction *addselectionbelow = new QAction("&Add Selection Below", this);
  // QAction *singleselection = new QAction("&Single Selection", this);
  QAction *selectline = new QAction("&Select Line", this);
  QAction *selectword = new QAction("&Select Word", this);
  QAction *selectinsidebrackets = new QAction("&Select Inside Brackets", this);

  QAction *findinbuffer = new QAction("&Find In Buffer", this);
  QAction *replaceinbuffer = new QAction("&Replace In Buffer", this);
  QAction *findinproject = new QAction("&Find In Project", this);

  QMenu *file;
  file = menuBar() -> addMenu("&File");
  file -> addAction(newwindow);
  file -> addAction(newfile);
  file -> addAction(openfile);
  file -> addAction(openfolder);

  ReopenProjectMenu = file ->addMenu(tr("&Reopen Project"));
  // file -> addAction(addprojectfolder);
  //file -> addAction(reopenproject);
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

  ReopenProject();

  QMenu *edit;
  edit = menuBar() -> addMenu("&Edit");
  edit -> addAction(undo);
  edit -> addAction(redo);
  edit -> addSeparator();
  edit -> addAction(cut);
  edit -> addAction(copy);
  edit -> addAction(copypath);
  edit -> addAction(paste);
  // edit -> addAction(pastewithoutreformatting);
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
  // selection -> addAction(addselectionabove);
  // selection -> addAction(addselectionbelow);
  // selection -> addAction(singleselection);
  selection -> addAction(selectline);
  selection -> addAction(selectword);
  selection -> addAction(selectinsidebrackets);

  QMenu *find;
  find = menuBar() -> addMenu("&Find");
  find -> addAction(findinbuffer);
  find -> addAction(replaceinbuffer);
  find -> addAction(findinproject);
  find -> addAction(findinproject);

  quit -> setShortcut(tr("CTRL+Q"));
  newwindow -> setShortcut(tr("CTRL+SHIFT+N"));
  newfile -> setShortcut(tr("CTRL+N"));
  openfile -> setShortcut(tr("CTRL+O"));
  openfolder -> setShortcut(tr("CTRL+SHIFT+O"));
  savefile -> setShortcut(tr("CTRL+S"));
  saveas -> setShortcut(tr("CTRL+SHIFT+S"));
  closetab -> setShortcut(tr("CTRL+W"));
  closepane -> setShortcut(tr("CTRL+K, CTRL+W"));
  closewindow -> setShortcut(tr("CTRL+SHIFT+W"));
  undo -> setShortcut(tr("CTRL+Z"));
  redo -> setShortcuts({tr("CTRL+SHIFT+Z"), tr("CTRL+Y")});
  cut -> setShortcut(tr("CTRL+X"));
  copy -> setShortcut(tr("CTRL+C"));
  copypath -> setShortcut(tr("CTRL+SHIFT+C"));
  paste -> setShortcut(tr("CTRL+V"));
  selectall -> setShortcut(tr("CTRL+A"));
  togglecomment -> setShortcut(tr("CTRL+/"));
  fullscreen -> setShortcut(tr("F11"));
  increasefontsize -> setShortcut(tr("CTRL+SHIFT+;"));
  decreasefontsize -> setShortcut(tr("CTRL+-"));
  resetfontsize -> setShortcut(tr("CTRL+0"));
  selectline -> setShortcut(tr("CTRL+L"));
  selectword -> setShortcut(tr("CTRL+D"));
  selectinsidebrackets -> setShortcut(tr("CTRL+SHIFT+B"));
  findinbuffer -> setShortcut(tr("CTRL+F"));
  // addselectionabove -> setShortcut(Qt::ALT + Qt::SHIFT + Qt::Key_Up);

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
  connect(closetab, &QAction::triggered, this, &MainWindow::CloseTab);
  connect(closepane, &QAction::triggered, this, &MainWindow::ClosePane);
  connect(closewindow, &QAction::triggered, this, &MainWindow::CloseWindow);
  connect(undo, &QAction::triggered, this -> m_textedit[this -> tabs -> tabText(this -> tabs -> currentIndex())], &QTextEdit::undo);
  connect(redo, &QAction::triggered, this -> m_textedit[this -> tabs -> tabText(this -> tabs -> currentIndex())], &QTextEdit::redo);
  connect(cut, &QAction::triggered, this -> m_textedit[this -> tabs -> tabText(this -> tabs -> currentIndex())], &QTextEdit::cut);
  connect(copy, &QAction::triggered, this -> m_textedit[this -> tabs -> tabText(this -> tabs -> currentIndex())], &QTextEdit::copy);
  connect(copypath, &QAction::triggered, this, &MainWindow::CopyPath);
  connect(paste, &QAction::triggered, this -> m_textedit[this -> tabs -> tabText(this -> tabs -> currentIndex())], &QTextEdit::paste);
  connect(selectall, &QAction::triggered, this -> m_textedit[this -> tabs -> tabText(this -> tabs -> currentIndex())], &QTextEdit::selectAll);
  connect(togglecomment, &QAction::triggered, this, &MainWindow::ToggleComment);
  connect(fullscreen, &QAction::triggered, this, &MainWindow::FullScreen);
  connect(increasefontsize, &QAction::triggered, this, &MainWindow::IncreaseFontSize);
  connect(decreasefontsize, &QAction::triggered, this, &MainWindow::DecreaseFontSize);
  connect(resetfontsize, &QAction::triggered, this, &MainWindow::ResetFontSize);
  connect(selectline, &QAction::triggered, this, &MainWindow::SelectLine);
  connect(selectword, &QAction::triggered, this, &MainWindow::SelectWord);
  connect(selectinsidebrackets, &QAction::triggered, this, &MainWindow::SelectInsideBrackets);
  connect(findinbuffer, &QAction::triggered, this, &MainWindow::FindInBuffer);
  // connect(addselectionabove, &QAction::triggered, this, &MainWindow::AddSelectionAbove);
}

MainWindow::~MainWindow()
{
  openedprojectsfile.close();
}

// void MainWindow::keyPressEvent(QKeyEvent *event)
// {
//   qDebug() << event -> key();
//   if(event -> key() == Qt::Key_Q)
//   {
//     std::cout << "a" << std::endl;
//     m_textedit[this -> tabs -> tabText(this -> tabs -> currentIndex())] -> textCursor().insertText(")");
//   }
//   else
//   {
//     std::cout << "b" << std::endl;
//   }
// }

bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
  for(auto b = m_textedit.begin(); b != m_textedit.end(); ++b)
  {
    if(object == b -> second && event -> type() == QEvent::KeyPress)
    {
      QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
      if(keyEvent -> key() == Qt::Key_ParenLeft)
      {
        b -> second -> insertPlainText("()");
        b -> second -> moveCursor(QTextCursor::Left, QTextCursor::MoveAnchor);
        return true;
      }
      else if(keyEvent -> key() == 34)
      {
        QString fileString = b -> second -> toPlainText();
        if(fileString[b -> second -> textCursor().position() - 1] == "\"" && fileString[b -> second -> textCursor().position()] == "\"")
        {
          QTextCursor cursor = b -> second -> textCursor();
          cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor);
          b -> second -> setTextCursor(cursor);
          return true;
        }
        b -> second -> insertPlainText("\"\"");
        b -> second -> moveCursor(QTextCursor::Left, QTextCursor::MoveAnchor);
        return true;
      }
      else if(keyEvent -> key() == Qt::Key_BracketLeft)
      {
        b -> second -> insertPlainText("[]");
        b -> second -> moveCursor(QTextCursor::Left, QTextCursor::MoveAnchor);
        return true;
      }
      else if(keyEvent -> key() == Qt::Key_BraceLeft)
      {
        b -> second -> insertPlainText("{}");
        b -> second -> moveCursor(QTextCursor::Left, QTextCursor::MoveAnchor);
        return true;
      }
      else if(keyEvent -> key() == Qt::Key_Apostrophe)
      {
        QString fileString = b -> second -> toPlainText();
        if(fileString[b -> second -> textCursor().position() - 1] == "'" && fileString[b -> second -> textCursor().position()] == "'")
        {
          QTextCursor cursor = b -> second -> textCursor();
          cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor);
          b -> second -> setTextCursor(cursor);
          return true;
        }
        b -> second -> insertPlainText("''");
        b -> second -> moveCursor(QTextCursor::Left, QTextCursor::MoveAnchor);
        return true;
      }
      else if(keyEvent -> key() == Qt::Key_Return)
      {
        QString fileString = b -> second -> toPlainText();
        if(fileString[b -> second -> textCursor().position() - 1] == "{" && fileString[b -> second -> textCursor().position()] == "}")
        {
          b -> second -> insertPlainText("\n");
          b -> second -> insertPlainText("\t");
          b -> second -> insertPlainText("\n");
          QTextCursor cursor = b -> second -> textCursor();
          cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor);
          b -> second -> setTextCursor(cursor);
          return true;
        }
        else if(fileString[b -> second -> textCursor().position() - 1] == "(" && fileString[b -> second -> textCursor().position()] == ")")
        {
          b -> second -> insertPlainText("\n");
          b -> second -> insertPlainText("\t");
          b -> second -> insertPlainText("\n");
          QTextCursor cursor = b -> second -> textCursor();
          cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor);
          b -> second -> setTextCursor(cursor);
          return true;
        }
      }
      else if(keyEvent -> key() == Qt::Key_ParenRight)
      {
        QString fileString = b -> second -> toPlainText();
        if(fileString[b -> second -> textCursor().position() - 1] == "(" && fileString[b -> second -> textCursor().position()] == ")")
        {
          QTextCursor cursor = b -> second -> textCursor();
          cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor);
          b -> second -> setTextCursor(cursor);
          return true;
        }
      }
      else if(keyEvent -> key() == Qt::Key_BraceRight)
      {
        QString fileString = b -> second -> toPlainText();
        if(fileString[b -> second -> textCursor().position() - 1] == "{" && fileString[b -> second -> textCursor().position()] == "}")
        {
          QTextCursor cursor = b -> second -> textCursor();
          cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor);
          b -> second -> setTextCursor(cursor);
          return true;
        }
      }
      else if(keyEvent -> key() == Qt::Key_BracketRight)
      {
        QString fileString = b -> second -> toPlainText();
        if(fileString[b -> second -> textCursor().position() - 1] == "[" && fileString[b -> second -> textCursor().position()] == "]")
        {
          QTextCursor cursor = b -> second -> textCursor();
          cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor);
          b -> second -> setTextCursor(cursor);
          return true;
        }
      }
    }
  }

  return false;
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
  this -> openedfolderdir = openfilename.path();
  QTextEdit *newtextedit = new QTextEdit();
  newtextedit -> installEventFilter(this);
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
  newtextedit -> installEventFilter(this);
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
  newtextedit -> installEventFilter(this);
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
  this -> openedfolderdir = folder_name;
  QFileInfo readFolder(folder_name);
  std::string s_file;
  bool fileexists = false;
  std::ifstream if_openedfiles;
  if_openedfiles.open("openedfiles.txt");
  while(if_openedfiles >> s_file)
  {
    if(s_file == folder_name.toStdString())
    {
      std::cout << s_file << std::endl;
      std::cout << folder_name.toStdString() << std::endl;
      fileexists = true;
    }
  }
  if(!fileexists)
  {
    this -> openedprojectsfile << folder_name.toStdString() << "\n";
    std::cout << "a" << std::endl;
  }
  else if(fileexists)
    fileexists = false;
  if(this -> folderIsOpen == true)
  {
    MainWindow *nw = new MainWindow();
    QDockWidget *dock = new QDockWidget(tr("Folder"), nw);
    dock -> setAllowedAreas(Qt::LeftDockWidgetArea);

    nw -> model -> setRootPath(folder_name);
    nw -> tree -> setModel(nw -> model);
    nw -> tree -> setRootIndex(nw -> model -> index(folder_name));
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


void MainWindow::openfolder(QString folder_name)
{
  QFileInfo readFolder(folder_name);
  if(this -> folderIsOpen == true)
  {
    MainWindow *nw = new MainWindow();
    QDockWidget *dock = new QDockWidget(tr("Folder"), nw);
    dock -> setAllowedAreas(Qt::LeftDockWidgetArea);

    nw -> model -> setRootPath(folder_name);
    nw -> tree -> setModel(nw -> model);
    nw -> tree -> setRootIndex(nw -> model -> index(folder_name));
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
    dock -> setAllowedAreas(Qt::LeftDockWidgetArea);
    this -> model -> setRootPath(folder_name);
    std::cout << this -> filetoopen.toStdString() << std::endl;
    this -> tree -> setModel(this -> model);
    this -> tree -> setRootIndex(this -> model -> index(folder_name));
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

void MainWindow::ReopenProject()
{
  std::ifstream inputfiles;
  inputfiles.open("openedfiles.txt");
  std::string s, last_s;
  QSignalMapper *signalMapper = new QSignalMapper(this);
  while(inputfiles >> s)
  {
    last_s = "&" + s;
    this -> filetoopen = QString::fromStdString(s);
    QAction *tempAction = new QAction(QString::fromStdString(last_s), this);
    connect(tempAction, SIGNAL(triggered()), signalMapper, SLOT(map()));
    this -> ReopenProjectMenu -> addAction(tempAction);
    signalMapper -> setMapping (tempAction, this -> filetoopen);
  }
  connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(openfolder(QString)));
}

void MainWindow::CloseTab()
{
  this -> tabs -> removeTab(this -> tabs -> currentIndex());
}

void MainWindow::ClosePane()
{
  this -> tabs -> clear();
}

void MainWindow::CloseWindow()
{
  this -> close();
}

void MainWindow::CopyPath()
{
  clipboard -> setText(this -> openedfolderdir);
}

void MainWindow::ToggleComment()
{
  this -> m_textedit[this -> tabs -> tabText(this -> tabs -> currentIndex())] -> moveCursor(QTextCursor::StartOfLine);
  QString fileString = m_textedit[this -> tabs -> tabText(this -> tabs -> currentIndex())] -> toPlainText();
  if(fileString[this -> m_textedit[this -> tabs -> tabText(this -> tabs -> currentIndex())] -> textCursor().position()] == "/" &&
                  fileString[this -> m_textedit[this -> tabs -> tabText(this -> tabs -> currentIndex())] -> textCursor().position() + 1] == "/")
  {
    this -> m_textedit[this -> tabs -> tabText(this -> tabs -> currentIndex())] -> moveCursor(QTextCursor::Right);
    this -> m_textedit[this -> tabs -> tabText(this -> tabs -> currentIndex())] ->  textCursor().deleteChar();
    // this -> m_textedit[this -> tabs -> tabText(this -> tabs -> currentIndex())] -> moveCursor(QTextCursor::Right);
    this -> m_textedit[this -> tabs -> tabText(this -> tabs -> currentIndex())] ->  textCursor().deleteChar();
    this -> m_textedit[this -> tabs -> tabText(this -> tabs -> currentIndex())] ->  textCursor().deletePreviousChar();
    // this -> m_textedit[this -> tabs -> tabText(this -> tabs -> currentIndex())] -> moveCursor(QTextCursor::Right);
    // this -> m_textedit[this -> tabs -> tabText(this -> tabs -> currentIndex())] ->  textCursor().deletePreviousChar();
  }
  else
    this -> m_textedit[this -> tabs -> tabText(this -> tabs -> currentIndex())] -> insertPlainText("// ");

}

void MainWindow::FullScreen()
{
  if(this -> isFullScreen())
  {
    this -> showNormal();
    this -> showMaximized();
  }
  else if(!this -> isFullScreen())
  {
    this -> showFullScreen();
  }
}

void MainWindow::IncreaseFontSize()
{
  ++this -> fontsize;
  QTextCursor cursor = this -> m_textedit[this -> tabs -> tabText(this -> tabs -> currentIndex())]->textCursor();
  this -> m_textedit[this -> tabs -> tabText(this -> tabs -> currentIndex())]->selectAll();
  this -> m_textedit[this -> tabs -> tabText(this -> tabs -> currentIndex())]->setFontPointSize(this -> fontsize);
  this -> m_textedit[this -> tabs -> tabText(this -> tabs -> currentIndex())]->setTextCursor( cursor );
}

void MainWindow::DecreaseFontSize()
{
  --this -> fontsize;
  QTextCursor cursor = this -> m_textedit[this -> tabs -> tabText(this -> tabs -> currentIndex())]->textCursor();
  this -> m_textedit[this -> tabs -> tabText(this -> tabs -> currentIndex())]->selectAll();
  this -> m_textedit[this -> tabs -> tabText(this -> tabs -> currentIndex())]->setFontPointSize(this -> fontsize);
  this -> m_textedit[this -> tabs -> tabText(this -> tabs -> currentIndex())]->setTextCursor( cursor );
}

void MainWindow::ResetFontSize()
{
  QTextCursor cursor = this -> m_textedit[this -> tabs -> tabText(this -> tabs -> currentIndex())]->textCursor();
  this -> m_textedit[this -> tabs -> tabText(this -> tabs -> currentIndex())]->selectAll();
  this -> m_textedit[this -> tabs -> tabText(this -> tabs -> currentIndex())]->setFontPointSize(16);
  this -> m_textedit[this -> tabs -> tabText(this -> tabs -> currentIndex())]->setTextCursor( cursor );
}

void MainWindow::SelectLine()
{
  QTextCursor cursor = this -> m_textedit[this -> tabs -> tabText(this -> tabs -> currentIndex())] -> textCursor();
  cursor.select(QTextCursor::LineUnderCursor);
  this -> m_textedit[this -> tabs -> tabText(this -> tabs -> currentIndex())] -> setTextCursor(cursor);
}

void MainWindow::SelectWord()
{
  QTextCursor cursor = this -> m_textedit[this -> tabs -> tabText(this -> tabs -> currentIndex())] -> textCursor();
  cursor.select(QTextCursor::WordUnderCursor);
  this -> m_textedit[this -> tabs -> tabText(this -> tabs -> currentIndex())] -> setTextCursor(cursor);
}
void MainWindow::SelectInsideBrackets()
{
  QTextCursor cursor = this -> m_textedit[this -> tabs -> tabText(this -> tabs -> currentIndex())] -> textCursor();
  int cursorPos = cursor.position();
  int endCursorPos = cursor.position();
  int startCursorPos = cursor.position();
  QString doc = this -> m_textedit[this -> tabs -> tabText(this -> tabs -> currentIndex())] -> toPlainText();
  int docEnd = doc.size();
  QChar border;
  for(int i = cursor.position(); i > 0; --i)
  {
    // std::cout << doc[i].toStdString() << std::endl;
    if(doc[i] == '(' || doc[i] == '{' || doc[i] == '[')
    {
      border = doc[i];
      endCursorPos = i + 1;
      break;
    }
  }
  for(int i = cursorPos; i < docEnd; ++i)
  {
    if(border == '(')
    {
      if(doc[i] == ')')
      {
        startCursorPos = i;
        break;
      }
    }
    if(border == '{')
    {
      if(doc[i] == '}')
      {
        startCursorPos = i;
        break;
      }
    }
    if(border == '[')
    {
      if(doc[i] == ']')
      {
        startCursorPos = i;
        break;
      }
    }
  }
  cursor.setPosition(startCursorPos);
  cursor.setPosition(endCursorPos, QTextCursor::KeepAnchor);
  this -> m_textedit[this -> tabs -> tabText(this -> tabs -> currentIndex())] -> setTextCursor(cursor);
}

void MainWindow::FindInBuffer()
{
  finddock = new QDockWidget(tr("&Find In Buffer"), this);
  finddock -> setAllowedAreas(Qt::BottomDockWidgetArea);
  finddock -> setFeatures(QDockWidget::DockWidgetClosable);
  QWidget *layoutWidget = new QWidget();
  QGridLayout *layout = new QGridLayout();
  QLabel *label1 = new QLabel("Find In Buffer:", this);
  label1->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
  QLabel *label2 = new QLabel("Replace In Buffer:", this);
  label2->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
  QLineEdit *texttofind = new QLineEdit(this);
  QLineEdit *texttoreplace = new QLineEdit(this);
  QPushButton *button1 = new QPushButton("Find", this);
  QPushButton *button2 = new QPushButton("Replace", this);
  QPushButton *button3 = new QPushButton("Find All", this);
  QPushButton *button4 = new QPushButton("Replace All", this);

  layout -> addWidget(label1, 0, 0);
  layout -> addWidget(texttofind, 0, 1);
  layout -> addWidget(label2, 1, 0);
  layout -> addWidget(texttoreplace, 1, 1);
  layout -> addWidget(button1, 0, 2);
  layout -> addWidget(button3, 0, 3);
  layout -> addWidget(button2, 1, 2);
  layout -> addWidget(button4, 1, 3);
  layoutWidget -> setLayout(layout);

  finddock -> setWidget(layoutWidget);
  this -> addDockWidget(Qt::BottomDockWidgetArea, finddock);
  finddock -> show();
}

void MainWindow::find(const QString &text)
{
  QString fileString = m_textedit[this -> tabs -> tabText(this -> tabs -> currentIndex())] -> toPlainText();
}

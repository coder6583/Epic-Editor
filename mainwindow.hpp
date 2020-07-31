#include "highlighter.hpp"
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QToolBar>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMainWindow>
#include <QWidget>
#include <QDockWidget>
#include <QTextEdit>
#include <QTabWidget>
#include <QFileSystemModel>
#include <QTreeWidget>
#include <QStyleFactory>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QFileDialog>
#include <QModelIndex>
#include <QGuiApplication>
#include <QSaveFile>
#include <QMessageBox>
#include <vector>
#include <map>
#include <QFont>
#include <QFontMetricsF>
#include <QDebug>
#include <QFontDatabase>

class MainWindow : public QMainWindow
{
  Q_OBJECT;

  public:
     MainWindow(QWidget *parent = 0);

  private slots:
    void deleteTab(int index);
    void ifdoubleclicked(QModelIndex item);
    bool save(const QString &fileName);

    void NewWindow();
    void NewFile();
    void OpenFile();
    void OpenFolder();
    // void AddProjectFolder();
    // void ReopenProject();
    // void ReopenLastItem();
    bool SaveFile();
    bool SaveAs();
    // void SaveAll();
    //
    // void CloseTab();
    // void ClosePane();
    // void CloseWindow();
    // void Undo();
    // void Redo();
    // void Cut();
    // void Copy();
    // void CopyPath();
    // void Paste();
    // void PasteWithoutReformatting();
    // void SelectAll();
    // void ToggleComment();
    //
    // void FullScreen();
    // void IncreaseFontSize();
    // void DecreaseFontSize();
    // void ResetFontSize();
    //
    // void AddSelectionAbove();
    // void AddSelectionBelow();
    // void SingleSelection();
    // void SelectLine();
    // void SelectWord();
    //
    // void FindInBuffer();
    // void ReplaceInBuffer();
    // void FindInProject();

  private:
    QTextEdit *textedit;
    QTabWidget *tabs;
    QTreeView *tree;
    QFileSystemModel *model;
    std::map<QString, QTextEdit*> m_textedit;
    Highlighter *highlighter;
    QFont font;
    bool folderIsOpen = false;
    int untitledcount = 0;
};

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLineEdit;
class QPushButton;
class QLabel;
class QTableWidget;
class QMenuBar;
class QAction;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    QLineEdit *passwordEdit;
    QLineEdit *fileEdit;
    QPushButton *browseButton;
    QPushButton *encryptButton;
    QPushButton *decryptButton;
    QTableWidget *fileTable;
    QLabel *statusLabel;
    QLabel *passwordLabel;
    QMenuBar *menuBar;
    QAction *fichiersAction;
    QAction *parametresAction;

    void setupMenu();
    void setupUI();
    void addFileToTable(const QString &filename, const QString &size, const QString &state);
};

#endif // MAINWINDOW_H

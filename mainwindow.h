#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "crypteur.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_browseInputButton_clicked();
    void on_browseOutputButton_clicked();
    void on_encryptButton_clicked();
    void on_decryptButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

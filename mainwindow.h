#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "compressor.h"
#include "decompressor.h"
#include "crypteur.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void on_browseInputButton_clicked();
    void on_browseOutputButton_clicked();
    void on_encryptButton_clicked();
    void on_decryptButton_clicked();
};

#endif // MAINWINDOW_H

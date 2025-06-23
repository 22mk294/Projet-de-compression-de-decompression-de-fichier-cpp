#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Crypteur de Fichiers");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_browseInputButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Sélectionner un fichier d'entrée");
    if (!fileName.isEmpty()) {
        ui->inputFileLineEdit->setText(fileName);
    }
}

void MainWindow::on_browseOutputButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Sélectionner un fichier de sortie");
    if (!fileName.isEmpty()) {
        ui->outputFileLineEdit->setText(fileName);
    }
}

void MainWindow::on_encryptButton_clicked()
{
    QString inputFile = ui->inputFileLineEdit->text();
    QString outputFile = ui->outputFileLineEdit->text();
    QString key = ui->keyLineEdit->text();

    if (inputFile.isEmpty() || outputFile.isEmpty() || key.isEmpty()) {
        QMessageBox::warning(this, "Attention", "Veuillez remplir tous les champs.");
        return;
    }

    if (Crypteur::traiterFichier(inputFile.toStdString(), outputFile.toStdString(), key.toStdString())) {
        QMessageBox::information(this, "Succès", "Fichier chiffré avec succès.");
    } else {
        QMessageBox::critical(this, "Erreur", "Le chiffrement du fichier a échoué.");
    }
}

void MainWindow::on_decryptButton_clicked()
{
    QString inputFile = ui->inputFileLineEdit->text();
    QString outputFile = ui->outputFileLineEdit->text();
    QString key = ui->keyLineEdit->text();

    if (inputFile.isEmpty() || outputFile.isEmpty() || key.isEmpty()) {
        QMessageBox::warning(this, "Attention", "Veuillez remplir tous les champs.");
        return;
    }

    if (Crypteur::traiterFichier(inputFile.toStdString(), outputFile.toStdString(), key.toStdString())) {
        QMessageBox::information(this, "Succès", "Fichier déchiffré avec succès.");
    } else {
        QMessageBox::critical(this, "Erreur", "Le déchiffrement du fichier a échoué.");
    }
}

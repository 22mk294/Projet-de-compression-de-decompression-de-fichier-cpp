#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QDir> // Ajout pour utiliser QDir

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Application de Chiffrement et Déchiffrement ");
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

    if (inputFile.isEmpty() || key.isEmpty()) {
        QMessageBox::warning(this, "Attention", "Le fichier d'entrée et la clé sont requis.");
        return;
    }

    // Si le champ de sortie est vide, on ajoute .enc à l'extension
    if (outputFile.isEmpty()) {
        QFileInfo fileInfo(inputFile);
        outputFile = fileInfo.absolutePath() + "/" + fileInfo.completeBaseName() + ".enc";
    }

    CrypteurResult result = Crypteur::traiterFichier(inputFile, outputFile, key.toUtf8());
    if (result == Success) {
        QMessageBox::information(this, "Succès", "Fichier chiffré avec succès :\n" + outputFile);
    } else if (result == WriteError) {
        QMessageBox::critical(this, "Erreur", "Erreur d'écriture lors du chiffrement.");
    } else if (result == ReadError) {
        QMessageBox::critical(this, "Erreur", "Erreur de lecture du fichier d'entrée.");
    } else if (result == BadPassword) {
        QMessageBox::critical(this, "Erreur", "Mot de passe invalide ou vide.");
    } else {
        QMessageBox::critical(this, "Erreur", "Le chiffrement a échoué.");
    }
}

void MainWindow::on_decryptButton_clicked()
{
    QString inputFile = ui->inputFileLineEdit->text();
    QString outputFile = ui->outputFileLineEdit->text();
    QString key = ui->keyLineEdit->text();

    if (inputFile.isEmpty() || key.isEmpty()) {
        QMessageBox::warning(this, "Attention", "Le fichier d'entrée et la clé sont requis.");
        return;
    }

    // Si le champ de sortie est vide, on retire .enc et on restaure l'extension d'origine
    if (outputFile.isEmpty()) {
        QFileInfo fileInfo(inputFile);
        QString base = fileInfo.completeBaseName();
        QString ext = fileInfo.suffix().toLower() == "enc" ? fileInfo.completeBaseName().section('.', -1) : fileInfo.suffix();
        if (fileInfo.suffix().toLower() == "enc") {
            // Si le fichier s'appelle fichier.txt.enc, on restaure fichier.txt
            outputFile = fileInfo.absolutePath() + "/" + base;
        } else {
            // Sinon, on ajoute .dec
            outputFile = fileInfo.absolutePath() + "/" + fileInfo.fileName() + ".dec";
        }
    }

    CrypteurResult result = Crypteur::traiterFichier(inputFile, outputFile, key.toUtf8());
    if (result == Success) {
        QMessageBox::information(this, "Succès", "Fichier déchiffré avec succès :\n" + outputFile);
    } else if (result == BadPassword) {
        QMessageBox::critical(this, "Erreur", "Mot de passe incorrect : impossible de déchiffrer ce fichier.");
    } else if (result == WriteError) {
        QMessageBox::critical(this, "Erreur", "Erreur d'écriture lors du déchiffrement.");
    } else if (result == ReadError) {
        QMessageBox::critical(this, "Erreur", "Erreur de lecture du fichier d'entrée.");
    } else {
        QMessageBox::critical(this, "Erreur", "Le déchiffrement a échoué.");
    }
}

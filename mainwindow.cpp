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

    // Si le chemin de sortie est vide, on ouvre une boîte de dialogue "Enregistrer sous...".
    if (outputFile.isEmpty()) {
        QFileInfo fileInfo(inputFile);
        QString defaultName = fileInfo.dir().filePath(fileInfo.fileName() + ".enc");
        outputFile = QFileDialog::getSaveFileName(this, "Enregistrer le fichier chiffré", defaultName);

        // Si l'utilisateur a cliqué sur "Annuler", on arrête le processus.
        if (outputFile.isEmpty()) {
            return;
        }
    }

    // Appel corrigé avec les types Qt (QString, QByteArray)
    if (Crypteur::traiterFichier(inputFile, outputFile, key.toUtf8())) {
        QMessageBox::information(this, "Succès", "Fichier chiffré avec succès :\n" + outputFile);
    } else {
        QMessageBox::critical(this, "Erreur", "Le chiffrement a échoué. Vérifiez le fichier d'entrée et les permissions d'écriture.");
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

    // Si le chemin de sortie est vide, on ouvre une boîte de dialogue "Enregistrer sous...".
    if (outputFile.isEmpty()) {
        QFileInfo fileInfo(inputFile);
        QString defaultName;
        if (fileInfo.suffix().toLower() == "enc") {
            defaultName = fileInfo.dir().filePath(fileInfo.baseName());
        } else {
            defaultName = fileInfo.dir().filePath(fileInfo.fileName() + ".dec");
        }
        
        outputFile = QFileDialog::getSaveFileName(this, "Enregistrer le fichier déchiffré", defaultName);

        // Si l'utilisateur a cliqué sur "Annuler", on arrête le processus.
        if (outputFile.isEmpty()) {
            return;
        }
    }

    // Appel corrigé avec les types Qt (QString, QByteArray)
    if (Crypteur::traiterFichier(inputFile, outputFile, key.toUtf8())) {
        QMessageBox::information(this, "Succès", "Fichier déchiffré avec succès :\n" + outputFile);
    } else {
        QMessageBox::critical(this, "Erreur", "Le déchiffrement a échoué. Vérifiez le fichier, la clé et les permissions d'écriture.");
    }
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "compressor.h"
#include "decompressor.h"
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>
#include <QFileDialog>
#include <QTableWidgetItem>
#include <QIcon>
#include <QMenuBar>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupMenu();
    setWindowTitle("Fichiers");
    resize(550, 350);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupMenu() {
    menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    fichiersAction = new QAction("Fichiers", this);
    parametresAction = new QAction("Paramètres", this);

    menuBar->addAction(fichiersAction);
    menuBar->addAction(parametresAction);
}

void MainWindow::setupUI() {
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    // Label "Mot de passe"
    passwordLabel = new QLabel("Mot de passe:");

    passwordEdit = new QLineEdit();
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setPlaceholderText("Entrez le mot de passe");

    QHBoxLayout *passwordLayout = new QHBoxLayout();
    passwordLayout->addWidget(passwordLabel);
    passwordLayout->addWidget(passwordEdit);

    fileEdit = new QLineEdit("fichier.txt");
    browseButton = new QPushButton("Parcourir");

    QHBoxLayout *fileLayout = new QHBoxLayout();
    fileLayout->addWidget(fileEdit);
    fileLayout->addWidget(browseButton);

    encryptButton = new QPushButton("🔒 Chiffrer");
    decryptButton = new QPushButton("🔓 Déchiffrer");

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(encryptButton);
    buttonLayout->addWidget(decryptButton);

    fileTable = new QTableWidget(0, 3);
    QStringList headers = {"Archive", "Taille", "État"};
    fileTable->setHorizontalHeaderLabels(headers);
    fileTable->horizontalHeader()->setStretchLastSection(true);
    fileTable->verticalHeader()->hide();
    fileTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    fileTable->setSelectionMode(QAbstractItemView::NoSelection);
    fileTable->setFocusPolicy(Qt::NoFocus);
    fileTable->setShowGrid(false);

    // Ajout d’un fichier avec icône
    addFileToTable("fichier1.txt.enc", "4 Mo", "Chiffré");

    statusLabel = new QLabel("Déchiffrement réussi !");
    statusLabel->setStyleSheet("background-color: lightgreen; padding: 6px;");

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(buttonLayout);
    mainLayout->addLayout(passwordLayout);
    mainLayout->addLayout(fileLayout);
    mainLayout->addWidget(fileTable);
    mainLayout->addWidget(statusLabel);

    central->setLayout(mainLayout);

    // Parcourir
    connect(browseButton, &QPushButton::clicked, this, [=]() {
        QString fileName = QFileDialog::getOpenFileName(this, "Choisir un fichier");
        if (!fileName.isEmpty()) {
            fileEdit->setText(fileName);
        }
    });
}

void MainWindow::addFileToTable(const QString &filename, const QString &size, const QString &state) {
    int row = fileTable->rowCount();
    fileTable->insertRow(row);

    // Icône fichier
    QTableWidgetItem *fileItem = new QTableWidgetItem(QIcon::fromTheme("text-x-generic"), filename);
    fileTable->setItem(row, 0, fileItem);
    fileTable->setItem(row, 1, new QTableWidgetItem(size));
    fileTable->setItem(row, 2, new QTableWidgetItem(state));
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

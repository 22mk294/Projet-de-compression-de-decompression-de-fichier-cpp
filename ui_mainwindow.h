/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *inputFileLineEdit;
    QPushButton *browseInputButton;
    QLabel *label_2;
    QLineEdit *outputFileLineEdit;
    QPushButton *browseOutputButton;
    QLabel *label_3;
    QLineEdit *keyLineEdit;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *encryptButton;
    QPushButton *decryptButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        inputFileLineEdit = new QLineEdit(centralwidget);
        inputFileLineEdit->setObjectName("inputFileLineEdit");

        gridLayout->addWidget(inputFileLineEdit, 0, 1, 1, 1);

        browseInputButton = new QPushButton(centralwidget);
        browseInputButton->setObjectName("browseInputButton");

        gridLayout->addWidget(browseInputButton, 0, 2, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        outputFileLineEdit = new QLineEdit(centralwidget);
        outputFileLineEdit->setObjectName("outputFileLineEdit");

        gridLayout->addWidget(outputFileLineEdit, 1, 1, 1, 1);

        browseOutputButton = new QPushButton(centralwidget);
        browseOutputButton->setObjectName("browseOutputButton");

        gridLayout->addWidget(browseOutputButton, 1, 2, 1, 1);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        keyLineEdit = new QLineEdit(centralwidget);
        keyLineEdit->setObjectName("keyLineEdit");
        keyLineEdit->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(keyLineEdit, 2, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        encryptButton = new QPushButton(centralwidget);
        encryptButton->setObjectName("encryptButton");

        horizontalLayout->addWidget(encryptButton);

        decryptButton = new QPushButton(centralwidget);
        decryptButton->setObjectName("decryptButton");

        horizontalLayout->addWidget(decryptButton);


        verticalLayout->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Chiffreur de Fichiers", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Fichier d'entr\303\251e :", nullptr));
        browseInputButton->setText(QCoreApplication::translate("MainWindow", "Parcourir...", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Fichier de sortie :", nullptr));
        browseOutputButton->setText(QCoreApplication::translate("MainWindow", "Parcourir...", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Cl\303\251 :", nullptr));
        encryptButton->setText(QCoreApplication::translate("MainWindow", "Chiffrer", nullptr));
        decryptButton->setText(QCoreApplication::translate("MainWindow", "D\303\251chiffrer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

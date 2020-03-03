/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *loadButton;
    QLabel *filenameLabel;
    QPushButton *solveButton;
    QLabel *tableroLabel;
    QVBoxLayout *verticalLayout;
    QRadioButton *BTradioButton;
    QRadioButton *AC3radioButton;
    QRadioButton *FCradioButton;
    QLabel *statusLabel;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(519, 347);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy1);
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        loadButton = new QPushButton(centralWidget);
        loadButton->setObjectName(QString::fromUtf8("loadButton"));

        horizontalLayout->addWidget(loadButton);

        filenameLabel = new QLabel(centralWidget);
        filenameLabel->setObjectName(QString::fromUtf8("filenameLabel"));
        QFont font;
        font.setPointSize(12);
        filenameLabel->setFont(font);
        filenameLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(filenameLabel);

        solveButton = new QPushButton(centralWidget);
        solveButton->setObjectName(QString::fromUtf8("solveButton"));

        horizontalLayout->addWidget(solveButton);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 2);

        tableroLabel = new QLabel(centralWidget);
        tableroLabel->setObjectName(QString::fromUtf8("tableroLabel"));

        gridLayout->addWidget(tableroLabel, 1, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        BTradioButton = new QRadioButton(centralWidget);
        BTradioButton->setObjectName(QString::fromUtf8("BTradioButton"));
        BTradioButton->setChecked(true);

        verticalLayout->addWidget(BTradioButton);

        AC3radioButton = new QRadioButton(centralWidget);
        AC3radioButton->setObjectName(QString::fromUtf8("AC3radioButton"));

        verticalLayout->addWidget(AC3radioButton);

        FCradioButton = new QRadioButton(centralWidget);
        FCradioButton->setObjectName(QString::fromUtf8("FCradioButton"));

        verticalLayout->addWidget(FCradioButton);

        statusLabel = new QLabel(centralWidget);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));
        QFont font1;
        font1.setPointSize(16);
        statusLabel->setFont(font1);

        verticalLayout->addWidget(statusLabel);


        gridLayout->addLayout(verticalLayout, 1, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 519, 29));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        loadButton->setText(QApplication::translate("MainWindow", "Cargar tablero", nullptr));
        filenameLabel->setText(QApplication::translate("MainWindow", "Tablero no cargado", nullptr));
        solveButton->setText(QApplication::translate("MainWindow", "Resolver", nullptr));
        tableroLabel->setText(QApplication::translate("MainWindow", "label", nullptr));
        BTradioButton->setText(QApplication::translate("MainWindow", "BackTracking", nullptr));
        AC3radioButton->setText(QApplication::translate("MainWindow", "AC3", nullptr));
        FCradioButton->setText(QApplication::translate("MainWindow", "Forward Checking", nullptr));
        statusLabel->setText(QApplication::translate("MainWindow", "Estado", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

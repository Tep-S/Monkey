/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tbMain;
    QWidget *tab;
    QPushButton *btOpenImage;
    QLabel *lbImage;
    QCheckBox *cbGrayscale;
    QPushButton *btSaveCommand;
    QPushButton *btSaveSequence;
    QPushButton *btRemoveCommand;
    QListWidget *lsMain;
    QLineEdit *lnSequence;
    QPushButton *btLoadSequence;
    QComboBox *comboBox;
    QPushButton *btDraw;
    QLineEdit *lnParam1;
    QLineEdit *lnParam2;
    QLineEdit *lnParam3;
    QPushButton *btTemplate;
    QCustomPlot *customPlot;
    QWidget *tab_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1093, 769);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tbMain = new QTabWidget(centralWidget);
        tbMain->setObjectName(QStringLiteral("tbMain"));
        tbMain->setGeometry(QRect(0, 0, 1091, 711));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        btOpenImage = new QPushButton(tab);
        btOpenImage->setObjectName(QStringLiteral("btOpenImage"));
        btOpenImage->setGeometry(QRect(340, 0, 121, 23));
        lbImage = new QLabel(tab);
        lbImage->setObjectName(QStringLiteral("lbImage"));
        lbImage->setGeometry(QRect(40, 140, 131, 21));
        cbGrayscale = new QCheckBox(tab);
        cbGrayscale->setObjectName(QStringLiteral("cbGrayscale"));
        cbGrayscale->setGeometry(QRect(340, 40, 70, 17));
        btSaveCommand = new QPushButton(tab);
        btSaveCommand->setObjectName(QStringLiteral("btSaveCommand"));
        btSaveCommand->setGeometry(QRect(470, 240, 41, 23));
        btSaveSequence = new QPushButton(tab);
        btSaveSequence->setObjectName(QStringLiteral("btSaveSequence"));
        btSaveSequence->setGeometry(QRect(470, 270, 91, 23));
        btRemoveCommand = new QPushButton(tab);
        btRemoveCommand->setObjectName(QStringLiteral("btRemoveCommand"));
        btRemoveCommand->setGeometry(QRect(510, 240, 51, 23));
        lsMain = new QListWidget(tab);
        lsMain->setObjectName(QStringLiteral("lsMain"));
        lsMain->setGeometry(QRect(30, 270, 431, 151));
        lnSequence = new QLineEdit(tab);
        lnSequence->setObjectName(QStringLiteral("lnSequence"));
        lnSequence->setGeometry(QRect(560, 270, 61, 20));
        btLoadSequence = new QPushButton(tab);
        btLoadSequence->setObjectName(QStringLiteral("btLoadSequence"));
        btLoadSequence->setGeometry(QRect(470, 290, 91, 23));
        comboBox = new QComboBox(tab);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(30, 230, 101, 22));
        btDraw = new QPushButton(tab);
        btDraw->setObjectName(QStringLiteral("btDraw"));
        btDraw->setGeometry(QRect(570, 240, 41, 23));
        lnParam1 = new QLineEdit(tab);
        lnParam1->setObjectName(QStringLiteral("lnParam1"));
        lnParam1->setGeometry(QRect(140, 230, 61, 20));
        lnParam2 = new QLineEdit(tab);
        lnParam2->setObjectName(QStringLiteral("lnParam2"));
        lnParam2->setGeometry(QRect(210, 230, 61, 20));
        lnParam3 = new QLineEdit(tab);
        lnParam3->setObjectName(QStringLiteral("lnParam3"));
        lnParam3->setGeometry(QRect(280, 230, 61, 20));
        btTemplate = new QPushButton(tab);
        btTemplate->setObjectName(QStringLiteral("btTemplate"));
        btTemplate->setGeometry(QRect(470, 310, 91, 23));
        customPlot = new QCustomPlot(tab);
        customPlot->setObjectName(QStringLiteral("customPlot"));
        customPlot->setGeometry(QRect(480, 340, 591, 341));
        tbMain->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tbMain->addTab(tab_2, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1093, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tbMain->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        btOpenImage->setText(QApplication::translate("MainWindow", "Open Image", nullptr));
        lbImage->setText(QApplication::translate("MainWindow", "Image Name", nullptr));
        cbGrayscale->setText(QApplication::translate("MainWindow", "Grayscale", nullptr));
        btSaveCommand->setText(QApplication::translate("MainWindow", "Add", nullptr));
        btSaveSequence->setText(QApplication::translate("MainWindow", "Save Sequence", nullptr));
        btRemoveCommand->setText(QApplication::translate("MainWindow", "Remove", nullptr));
        lnSequence->setText(QApplication::translate("MainWindow", "seq.conf", nullptr));
        btLoadSequence->setText(QApplication::translate("MainWindow", "Load Sequence", nullptr));
        comboBox->setItemText(0, QApplication::translate("MainWindow", "Grayscale", nullptr));
        comboBox->setItemText(1, QApplication::translate("MainWindow", "Threshing", nullptr));
        comboBox->setItemText(2, QApplication::translate("MainWindow", "Canny", nullptr));
        comboBox->setItemText(3, QApplication::translate("MainWindow", "Contour", nullptr));
        comboBox->setItemText(4, QApplication::translate("MainWindow", "Bgr2Hsv", nullptr));
        comboBox->setItemText(5, QApplication::translate("MainWindow", "Blur", nullptr));
        comboBox->setItemText(6, QApplication::translate("MainWindow", "Hsv2Bgr", nullptr));

        btDraw->setText(QApplication::translate("MainWindow", "Draw", nullptr));
        lnParam1->setText(QApplication::translate("MainWindow", "1", nullptr));
        lnParam2->setText(QApplication::translate("MainWindow", "2", nullptr));
        lnParam3->setText(QApplication::translate("MainWindow", "3", nullptr));
        btTemplate->setText(QApplication::translate("MainWindow", "Template", nullptr));
        tbMain->setTabText(tbMain->indexOf(tab), QApplication::translate("MainWindow", "Tab 1", nullptr));
        tbMain->setTabText(tbMain->indexOf(tab_2), QApplication::translate("MainWindow", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

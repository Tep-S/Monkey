/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tbMain;
    QWidget *tab;
    QSlider *hzColorV;
    QSlider *hsBlurV;
    QSlider *hsThreshold;
    QLabel *lbColor;
    QLabel *lbThreshold;
    QLabel *lbBlur;
    QCheckBox *cbColor;
    QCheckBox *cbBlur;
    QCheckBox *cbThresh;
    QPushButton *btOpenImage;
    QLabel *lbImage;
    QCheckBox *cbLines;
    QLabel *lbLines;
    QSlider *hsThreshold_2;
    QSlider *hsThreshold_3;
    QWidget *tab_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(673, 472);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tbMain = new QTabWidget(centralWidget);
        tbMain->setObjectName(QStringLiteral("tbMain"));
        tbMain->setGeometry(QRect(0, 0, 491, 411));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        hzColorV = new QSlider(tab);
        hzColorV->setObjectName(QStringLiteral("hzColorV"));
        hzColorV->setGeometry(QRect(100, 10, 131, 21));
        hzColorV->setOrientation(Qt::Horizontal);
        hsBlurV = new QSlider(tab);
        hsBlurV->setObjectName(QStringLiteral("hsBlurV"));
        hsBlurV->setGeometry(QRect(100, 40, 131, 21));
        hsBlurV->setOrientation(Qt::Horizontal);
        hsThreshold = new QSlider(tab);
        hsThreshold->setObjectName(QStringLiteral("hsThreshold"));
        hsThreshold->setGeometry(QRect(100, 70, 131, 21));
        hsThreshold->setOrientation(Qt::Horizontal);
        lbColor = new QLabel(tab);
        lbColor->setObjectName(QStringLiteral("lbColor"));
        lbColor->setGeometry(QRect(30, 10, 61, 16));
        lbThreshold = new QLabel(tab);
        lbThreshold->setObjectName(QStringLiteral("lbThreshold"));
        lbThreshold->setGeometry(QRect(30, 70, 47, 13));
        lbBlur = new QLabel(tab);
        lbBlur->setObjectName(QStringLiteral("lbBlur"));
        lbBlur->setGeometry(QRect(30, 40, 47, 13));
        cbColor = new QCheckBox(tab);
        cbColor->setObjectName(QStringLiteral("cbColor"));
        cbColor->setGeometry(QRect(240, 10, 21, 17));
        cbBlur = new QCheckBox(tab);
        cbBlur->setObjectName(QStringLiteral("cbBlur"));
        cbBlur->setGeometry(QRect(240, 40, 21, 17));
        cbThresh = new QCheckBox(tab);
        cbThresh->setObjectName(QStringLiteral("cbThresh"));
        cbThresh->setGeometry(QRect(240, 70, 21, 17));
        btOpenImage = new QPushButton(tab);
        btOpenImage->setObjectName(QStringLiteral("btOpenImage"));
        btOpenImage->setGeometry(QRect(340, 0, 75, 23));
        lbImage = new QLabel(tab);
        lbImage->setObjectName(QStringLiteral("lbImage"));
        lbImage->setGeometry(QRect(40, 140, 131, 21));
        cbLines = new QCheckBox(tab);
        cbLines->setObjectName(QStringLiteral("cbLines"));
        cbLines->setGeometry(QRect(240, 100, 21, 17));
        lbLines = new QLabel(tab);
        lbLines->setObjectName(QStringLiteral("lbLines"));
        lbLines->setGeometry(QRect(30, 100, 47, 13));
        hsThreshold_2 = new QSlider(tab);
        hsThreshold_2->setObjectName(QStringLiteral("hsThreshold_2"));
        hsThreshold_2->setGeometry(QRect(100, 100, 61, 21));
        hsThreshold_2->setOrientation(Qt::Horizontal);
        hsThreshold_3 = new QSlider(tab);
        hsThreshold_3->setObjectName(QStringLiteral("hsThreshold_3"));
        hsThreshold_3->setGeometry(QRect(170, 100, 61, 21));
        hsThreshold_3->setOrientation(Qt::Horizontal);
        tbMain->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tbMain->addTab(tab_2, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 673, 21));
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        lbColor->setText(QApplication::translate("MainWindow", "Color", Q_NULLPTR));
        lbThreshold->setText(QApplication::translate("MainWindow", "Threshold", Q_NULLPTR));
        lbBlur->setText(QApplication::translate("MainWindow", "Blur", Q_NULLPTR));
        cbColor->setText(QString());
        cbBlur->setText(QString());
        cbThresh->setText(QString());
        btOpenImage->setText(QApplication::translate("MainWindow", "Open Image", Q_NULLPTR));
        lbImage->setText(QApplication::translate("MainWindow", "Image Name", Q_NULLPTR));
        cbLines->setText(QString());
        lbLines->setText(QApplication::translate("MainWindow", "Lines", Q_NULLPTR));
        tbMain->setTabText(tbMain->indexOf(tab), QApplication::translate("MainWindow", "Tab 1", Q_NULLPTR));
        tbMain->setTabText(tbMain->indexOf(tab_2), QApplication::translate("MainWindow", "Tab 2", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

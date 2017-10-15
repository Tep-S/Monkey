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
        btSaveCommand->setGeometry(QRect(410, 230, 81, 23));
        btSaveSequence = new QPushButton(tab);
        btSaveSequence->setObjectName(QStringLiteral("btSaveSequence"));
        btSaveSequence->setGeometry(QRect(470, 270, 151, 23));
        btRemoveCommand = new QPushButton(tab);
        btRemoveCommand->setObjectName(QStringLiteral("btRemoveCommand"));
        btRemoveCommand->setGeometry(QRect(500, 230, 91, 23));
        lsMain = new QListWidget(tab);
        lsMain->setObjectName(QStringLiteral("lsMain"));
        lsMain->setGeometry(QRect(30, 270, 431, 151));
        lnSequence = new QLineEdit(tab);
        lnSequence->setObjectName(QStringLiteral("lnSequence"));
        lnSequence->setGeometry(QRect(620, 270, 113, 20));
        btLoadSequence = new QPushButton(tab);
        btLoadSequence->setObjectName(QStringLiteral("btLoadSequence"));
        btLoadSequence->setGeometry(QRect(470, 290, 151, 23));
        comboBox = new QComboBox(tab);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(30, 230, 101, 22));
        btDraw = new QPushButton(tab);
        btDraw->setObjectName(QStringLiteral("btDraw"));
        btDraw->setGeometry(QRect(600, 230, 91, 23));
        lnParam1 = new QLineEdit(tab);
        lnParam1->setObjectName(QStringLiteral("lnParam1"));
        lnParam1->setGeometry(QRect(140, 230, 61, 20));
        lnParam2 = new QLineEdit(tab);
        lnParam2->setObjectName(QStringLiteral("lnParam2"));
        lnParam2->setGeometry(QRect(210, 230, 61, 20));
        lnParam3 = new QLineEdit(tab);
        lnParam3->setObjectName(QStringLiteral("lnParam3"));
        lnParam3->setGeometry(QRect(280, 230, 61, 20));
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        btOpenImage->setText(QApplication::translate("MainWindow", "Open Image", Q_NULLPTR));
        lbImage->setText(QApplication::translate("MainWindow", "Image Name", Q_NULLPTR));
        cbGrayscale->setText(QApplication::translate("MainWindow", "Grayscale", Q_NULLPTR));
        btSaveCommand->setText(QApplication::translate("MainWindow", "Add", Q_NULLPTR));
        btSaveSequence->setText(QApplication::translate("MainWindow", "Save Sequence", Q_NULLPTR));
        btRemoveCommand->setText(QApplication::translate("MainWindow", "Remove", Q_NULLPTR));
        lnSequence->setText(QApplication::translate("MainWindow", "seq.conf", Q_NULLPTR));
        btLoadSequence->setText(QApplication::translate("MainWindow", "Load Sequence", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Grayscale", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Threshing", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Canny", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Contour", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Bgr2Hsv", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Blur", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Hsv2Bgr", Q_NULLPTR)
        );
        btDraw->setText(QApplication::translate("MainWindow", "Draw", Q_NULLPTR));
        lnParam1->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        lnParam2->setText(QApplication::translate("MainWindow", "2", Q_NULLPTR));
        lnParam3->setText(QApplication::translate("MainWindow", "3", Q_NULLPTR));
        tbMain->setTabText(tbMain->indexOf(tab), QApplication::translate("MainWindow", "Tab 1", Q_NULLPTR));
        tbMain->setTabText(tbMain->indexOf(tab_2), QApplication::translate("MainWindow", "Tab 2", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

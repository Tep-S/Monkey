#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sequence.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Sequence* seq;
    Ui::MainWindow *ui;
    void Connects();
    void ImgAct(int command);

private slots:
    void OpenImage();
    void SaveCommand();
    void RemoveCommand();
    void SaveSequence();
};

#endif // MAINWINDOW_H

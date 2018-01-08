#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sequence.h"
#include "stream.h"
#include "handler.h"

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
    Stream* stream;
    Handler* handler;
    void Tests();
    void Plots();
private slots:
    void TestTemplate();
    void ShowToolTip();
    void Draw();
    void OpenImage();
    void SaveCommand();
    void RemoveCommand();
    void SaveSequence();
    void LoadSequence();
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    QString imageName;
    Ui::MainWindow *ui;
    void Connects();

private slots:
    void OpenImage();
};

#endif // MAINWINDOW_H

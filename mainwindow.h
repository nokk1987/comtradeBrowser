#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

QVector<double> parseDATfile(QTextStream &in);

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
    Ui::MainWindow *ui;

private slots:
    void on_openButton_clicked();

};

#endif // MAINWINDOW_H

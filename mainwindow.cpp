#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <tuple>
#include <vector>

#define SAMPLE_CNT 16000
#define SAMPLE_ELEMENTS (2+2+9+4)



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->customPlot->setInteraction(QCP::iRangeDrag, true);
    ui->customPlot->setInteraction(QCP::iRangeZoom, true);
    ui->customPlot->xAxis->setRange(0, SAMPLE_CNT);
    ui->customPlot->yAxis->setRange(-10000, 10000);
//    QObject::connect()
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Files"), QString(),
                       tr("Data Files (*.dat);;Configuration Files (*.cfg)"));

//    std::tuple<int, int, std::vector<short>> t1 = std::make_tuple(12, 13, std::vector<short>{14, 15, 16});

    QFileInfo fileInfo(fileName);

    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        QTextStream in(&file);
        QDataStream dataIn(&file);
        QVector< QVector< short > > DATbuffer(SAMPLE_CNT, QVector< short> SAMPLE_ELEMENTS);
        QVector<double> currRes(SAMPLE_CNT);
        QVector<double> time(SAMPLE_CNT);


        if (fileInfo.completeSuffix() == "CFG") ui->textEdit->setText(in.readAll());
        // check for the design pattern to abtract reading


        if (fileInfo.completeSuffix() == "DAT")
        {
            for (int i = 0; i < SAMPLE_CNT; i++) {
                for (int j = 0; j < SAMPLE_ELEMENTS; j++)
                    dataIn >> DATbuffer[i][j];

                 currRes[i] = (double) DATbuffer[i][7];
                 time[i] = i;
                 ui->textEdit->append(QString::number(currRes[i]));

             }

            ui->customPlot->addGraph();
            ui->customPlot->graph(0)->setData(time, currRes);
            ui->customPlot->replot();
        }
        file.close();
    }
}

//QVector<double> parseDATfile(QTextStream &in)
//{
//    for (int i = 0; i < 3097; i++)
//    {

//    }
//    QVector<double> fT;
//    return fT;
//}

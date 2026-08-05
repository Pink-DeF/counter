#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    buttons = {
        ui->pushButton1,
        ui->pushButton2,
        ui->pushButton3,
        ui->pushButton4,
        ui->pushButton5,
        ui->pushButton6,
        ui->pushButton7,
        ui->pushButton8,
        ui->pushButton9
    };

    labels = {
        ui->label1,
        ui->label2,
        ui->label3,
        ui->label4,
        ui->label5,
        ui->label6,
        ui->label7,
        ui->label8,
        ui->label9
    };

    loadCounters();
    updateLabels();

    for (int i = 0; i < 8; ++i)
    {
        connect(buttons[i], &QPushButton::clicked,
                this, [this, i]()
                {
                    counters[i]++;
                    labels[i]->setText(QString::number(counters[i]));
                    saveCounters();
                });
    }

    connect(ui->pushButton9, &QPushButton::clicked,
            this, [this]()
            {
                counters[8] += ui->spinBox->value();

                labels[8]->setText(QString::number(counters[8]));

                saveCounters();
            });

    loadCounters();
    updateLabels();
}

MainWindow::~MainWindow()
{
    saveCounters();
    delete ui;
}

void MainWindow::updateLabels()
{
    for (int i = 0; i < labels.size(); ++i)
        labels[i]->setText(QString::number(counters[i]));
}

void MainWindow::saveCounters()
{
    QFile file("counter.json");

    if (!file.open(QIODevice::WriteOnly))
        return;

    QJsonArray array;

    for (int value : counters)
        array.append(value);

    QJsonObject obj;
    obj["counters"] = array;

    file.write(QJsonDocument(obj).toJson());
}

void MainWindow::loadCounters()
{
    QFile file("counter.json");

    if (!file.exists())
        return;

    if (!file.open(QIODevice::ReadOnly))
        return;

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());

    if (!doc.isObject())
        return;

    QJsonArray array = doc.object()["counters"].toArray();

    for (int i = 0; i < array.size() && i < counters.size(); ++i)
        counters[i] = array[i].toInt();
}

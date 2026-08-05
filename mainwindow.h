#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <array>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void loadCounters();
    void saveCounters();
    void updateLabels();

    Ui::MainWindow *ui;

    std::array<int, 9> counters{};
    std::array<QPushButton*, 9> buttons;
    std::array<QLabel*, 9> labels;
};

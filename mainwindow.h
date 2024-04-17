#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>

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

private slots:
    void on_addItemButton_clicked();

    void on_deleteTaskButton_clicked();

    void on_detailsTaskButton_clicked();

    void on_saveTasksButton_clicked();

    void on_loadTasksButton_clicked();

    void on_tasklistWidget_currentRowChanged(int currentRow);

private:
    Ui::MainWindow *ui;
    int mnSelected;
};
#endif // MAINWINDOW_H

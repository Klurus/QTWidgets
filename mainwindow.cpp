#include <QSettings>
#include <QJsonArray>
#include <QJsonDocument>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QInputDialog>
#include <qmessagebox.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->addTaskButton, SIGNAL(clicked()), this, SLOT(on_addItemButton_clicked()));
    connect(ui->deleteTaskButton, SIGNAL(clicked()), this, SLOT(on_deleteTaskButton_clicked()));
    connect(ui->saveTasksButton, SIGNAL(clicked()), this, SLOT(on_saveTasksButton_clicked()));
    connect(ui->loadTasksButton, SIGNAL(clicked()), this, SLOT(on_loadTasksButton_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addItemButton_clicked()
{
    bool ok;

    QString text = QInputDialog::getText(this, tr("Добавить элемент"), tr("Текст элемента:"), QLineEdit::Normal, "", &ok);
    if (ok && !text.isEmpty() && !text.contains(" "))
    {
        QString id = QInputDialog::getText(this, tr("Добавить элемент"), tr("ID задачи (только цифры):"), QLineEdit::Normal, "", &ok);
        if (ok && !id.isEmpty() && id.toInt(&ok) != 0 && !id.contains(" "))
        {
            QString description = QInputDialog::getText(this, tr("Добавить элемент"), tr("Описание задачи:"), QLineEdit::Normal, "", &ok);
            if (ok && !description.contains(" "))
            {
                QString displayText = " (ID: " + id + ") " + text + " - " + description;
                ui->tasklistWidget->addItem(displayText);
            }
            else
            {
                QMessageBox::warning(this, tr("Предупреждение"), tr("Описание задачи не может быть пустым или содержать пробелы"));
            }
        }
        else
        {
            QMessageBox::warning(this, tr("Предупреждение"), tr("ID задачи должен состоять только из цифр и не содержать пробелов"));
        }
    }
    else
    {
        QMessageBox::warning(this, tr("Предупреждение"), tr("Текст элемента не может быть пустым или содержать пробелы"));
    }
}

void MainWindow::on_deleteTaskButton_clicked()
{
    if(mnSelected != -1) {
        QListWidgetItem *it = ui->tasklistWidget->takeItem(mnSelected);
        delete it;
        ui->tasklistWidget->setCurrentRow(-1);
    }
}




void MainWindow::on_detailsTaskButton_clicked()
{
    QListWidgetItem *selectedItem = ui->tasklistWidget->currentItem();

    if (selectedItem) {
        QString taskInfo = selectedItem->text();

        QMessageBox::information(this, tr("Информация о задаче"), taskInfo);
    }
    else {
        QMessageBox::warning(this, tr("Предупреждение"), tr("Пожалуйста, выберите задачу для просмотра информации"));
    }
}



void MainWindow::on_saveTasksButton_clicked()
{
    QSettings settings("Klurus", "laba1");

    QJsonArray tasksArray;

    for (int i = 0; i < ui->tasklistWidget->count(); ++i) {
        QString taskText = ui->tasklistWidget->item(i)->text();
        tasksArray.append(taskText);
    }

    QJsonDocument doc(tasksArray);
    QString tasksString = doc.toJson();

    settings.setValue("tasks", tasksString);
}

void MainWindow::on_loadTasksButton_clicked()
{
    QSettings settings("Klurus", "Laba1");

    QString tasksString = settings.value("tasks").toString();

    QJsonDocument doc = QJsonDocument::fromJson(tasksString.toUtf8());
    QJsonArray tasksArray = doc.array();

    ui->tasklistWidget->clear();

    foreach (const QJsonValue &taskValue, tasksArray) {
        QString taskText = taskValue.toString();
        ui->tasklistWidget->addItem(taskText);
    }
}

void MainWindow::on_tasklistWidget_currentRowChanged(int currentRow)
{
    mnSelected = currentRow;
}


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QMessageBox"
#include "QMenuBar"
#include "QFontDialog"
#include <string>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("NotePad  ©  ПОНОМАРЕВ ДИМИТРИЙ");

}

// __________________________    ОБЪЯВЛЯЕМ ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ
bool flagSave = 0; // статус сохранения
bool flagChange = 0; // статус изменений
QByteArray ba; // массив
QMessageBox::StandardButton reply; //ответ пользователя да/нет/отмена
QString fileName;
#define TITLE_STRING "*Без Имени - NotePad  ©  ПОНОМАРЕВ ДИМИТРИЙ "

// __________________________    ОПИСЫВАЕМ БЛОК ФУНКЦИОНИРОВАНИЯ

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open(){ //функция открыть
    flagSave = 1; flagChange = 0;

    QString fileName; // путь к документу
    fileName = QFileDialog::getOpenFileName(this, \
    tr("Открыть файл"), "D:\\Work\\Study\\Programming\\Qt_worked\\2_sem\\1_practice\\Doci", tr("Text files(*.txt)"));
    //задаем по умолчанию расположение и фильтруем по расширению

    if (fileName == ""){
        QMessageBox::information(this, "Предупреждение", "Файл не выбран");
    }
    else {
        ui->textEdit->clear(); // очищаем текстовое поле
        QFile file; // класс файлов
        file.setFileName(fileName); // связываем с файлом на диске
        file.open(QIODevice::ReadOnly); // открываем только на чтение
        QByteArray ba; //формируем массив для передачи файлов
        ba.clear(); // очищаем массив
        long long fileSize; //объявлем переменную размера файла
        fileSize = file.size(); //Получаем размер файла
        ba = file.read(fileSize); // записываем в масссив file
        ui->textEdit->append(QString(ba).toUtf8()); // выводим текст на экран пользователю через расшифровку toUtf8
        file.close(); // закрываем файл
    }
}

void MainWindow::New(){ // функция создать
    flagSave = 0; flagChange = 0;
    ba.clear(); ui->textEdit->clear(); return;
}

void MainWindow::save(){ // функция сохраниить
    flagSave = 1; flagChange = 0;

    QString fileName; // путь к документу
    QFile file;
    file.setFileName(fileName); //связываем с файлом на диске
    file.open(QIODevice::WriteOnly); //открываем файл на запись
    file.write(ui->textEdit->toPlainText().toUtf8()); //Запись информации с текстового поля в файд
    file.close(); //закрываем файл

}

void MainWindow::saveAs(){ // функция сохранить как
    flagSave = 1; flagChange = 0;

    QString fileName; // путь к документу
    fileName = QFileDialog::getSaveFileName(this, tr("Сохранить как"), \
    "D:\\Work\\Study\\Programming\\Qt_worked\\2_sem\\1_practice\\Doci", tr("Text files (*.txt)"));
    if (fileName.isEmpty()) //Файл не выбран
    {
        QMessageBox::information(this, "Предупреждение", "Файл не выбран");
    }
    else
    {
        QFile file;
        file.setFileName(fileName); //связываем с файлом на диске
        file.open(QIODevice::WriteOnly); //открываем файл на запись
        file.write(ui->textEdit->toPlainText().toUtf8()); //Запись информации с текстового поля в файд
        file.close(); //закрываем файл

    }
}

void MainWindow::on_textEdit_textChanged() // изменения
{
    flagChange = 1;
    debug();

}

void MainWindow::debug(){// дебаг
    QString TflagSave, TflagChange = "";

    TflagSave = flagSave ? "true" : "false";
    TflagChange = flagChange? "true" : "false";
    ui->lineEdit->setText(TflagSave);
    ui->lineEdit_2->setText(TflagChange);

}

void MainWindow::on_pushButton_clicked()
{
    debug();
}

// __________________________ ОПИСЫВАЕМ БЛОК ИНТЕРФЕЙСА

void MainWindow::on_new_d_triggered(){ //кнопка new
//    QFileDialog dialog(this);
//        dialog.setFileMode(QFileDialog::ExistingFile);
    if (flagSave && flagChange){ // сохранен -> изменен
        reply = QMessageBox::question(this, "Предупреждение",
            "Вы желаете сохраниться?",
            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

        if (reply == QMessageBox::Yes){
            save(); New(); return;
            }
        if (reply == QMessageBox::No){
            New(); return;
            }
        if (reply == QMessageBox::Cancel){
            return;}
    }
    if ((flagSave && !flagChange) || (!flagSave && !flagChange)){ // сохранен -> не изменен || не сохранен -> не изменен
        New();return;
    }
    if (!flagSave && flagChange){ //  не сохранен -> не изменен
        reply = QMessageBox::question(this, "Предупреждение",
            "Вы желаете сохраниться?",
            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (reply == QMessageBox::Yes){
            saveAs(); New(); return;
            }
        if (reply == QMessageBox::No){
            New(); return;
            }
        if (reply == QMessageBox::Cancel){
            return;}
    }
}

void MainWindow::on_open_triggered(){ //кнопка open
    if (flagSave && flagChange){ // сохранен -> изменен
        reply = QMessageBox::question(this, "Предупреждение",
            "Вы желаете сохраниться?",
            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (reply == QMessageBox::Yes){
            save(); open(); flagSave = 1; flagChange = 0;  return;
            }
        if (reply == QMessageBox::No){
            open(); flagSave = 1; flagChange = 0;  return;
            }
        if (reply == QMessageBox::Cancel){
            return;}
    }
    if ((flagSave && !flagChange) || (!flagSave && !flagChange)){ // сохранен -> не изменен сохранен -> не изменен || не сохранен -> не изменен
        open(); return;
    }
    if (!flagSave && flagChange){ // сохранен -> не изменен
        reply = QMessageBox::question(this, "Предупреждение",
            "Вы желаете сохраниться?",
            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (reply == QMessageBox::Yes){
            saveAs(); open(); return;
            }
        if (reply == QMessageBox::No){
            open(); return;
            }
        if (reply == QMessageBox::Cancel){
            return;}
    }
}

void MainWindow::on_save_triggered(){ //кнопка сохранить

    if (flagSave && flagChange){ // сохранен -> изменен
        save(); return;
    }
    if ((flagSave && !flagChange) || (!flagSave && !flagChange)){ // сохранен -> не изменен || не сохранен -> не изменен
        return; //сделать название
    }
    if (!flagSave && flagChange){ // не сохранен -> изменен
        saveAs(); return;
    }
}

void MainWindow::on_saveAs_triggered(){ //кнопка сохранить как
    saveAs(); return;
}

void MainWindow::on_exit_triggered(){ // кнопка выхода

    if (flagSave && flagChange){ // сохранен -> изменен
        reply = QMessageBox::question(this, "Предупреждение",
            "Вы желаете сохраниться?",
            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (reply == QMessageBox::Yes){
            save(); exit(0);
            }
        if (reply == QMessageBox::No){
            exit(0);
            }
        if (reply == QMessageBox::Cancel){
            return;}
    }
    if ((flagSave && !flagChange) || (!flagSave && !flagChange)){ //сохранен -> не изменен сохранен -> не изменен || не сохранен -> не изменен
        exit(0);
    }
    if (!flagSave && flagChange){ // сохранен -> не изменен
        reply = QMessageBox::question(this, "Предупреждение",
            "Вы желаете сохраниться?",
            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (reply == QMessageBox::Yes){
            saveAs(); exit(0);
            }
        if (reply == QMessageBox::No){
            exit(0);
            }
        if (reply == QMessageBox::Cancel){
            return;}
    }
}




#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QMessageBox"
#include "QMenuBar"
#include "QFontDialog"
#include "QSettings"
#include <string>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("NotePad  ©  ПОНОМАРЕВ ДИМИТРИЙ");
    ui->lineEdit->hide();
    ui->lineEdit_2->hide();
    ui->lineEdit_3->hide();
    ui->label->hide();
    ui->label_2->hide();
    ui->pushButton->hide();


}

// __________________________    ОБЪЯВЛЯЕМ ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ
bool flagSave = 0; // статус сохранения
bool flagChange = 0; // статус изменений
QByteArray ba; // массив
QMessageBox::StandardButton reply; //ответ пользователя да/нет/отмена
bool flagCancel = 0; // флаг прерывания в сохранить как

QString Nadpis = "";
QString fileName;
QFont m_lastFont;
QSettings m_settings;
QSettings settings;


// __________________________    ОПИСЫВАЕМ БЛОК ФУНКЦИОНИРОВАНИЯ

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open(){ //функция открыть    
    fileName = QFileDialog::getOpenFileName(this, \
    tr("Открыть файл"), "D:\\Work\\Study\\Programming\\Qt_worked\\2_sem\\1_practice\\Doci", tr("Text files(*.txt)"));

    if (fileName == ""){
        QMessageBox::information(this, "Предупреждение", "Файл не выбран");
    }
    else {
        ui->textEdit->blockSignals(true);
        ui->textEdit->clear(); // очищаем текстовое поле
        ui->textEdit->blockSignals(false);
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
        flagSave = 1; flagChange = 0;
        Rename(fileName);
    }
}

void MainWindow::New(){ // функция создать
    ui->textEdit->blockSignals(true);
    ba.clear(); ui->textEdit->clear();
    this->setWindowTitle("NotePad  ©  ПОНОМАРЕВ ДИМИТРИЙ");
    fileName = "";
    ui->textEdit->blockSignals(false);
    flagSave = 0; flagChange = 0;


}

void MainWindow::save(){ // функция сохраниить
    QFile file;
    file.setFileName(fileName); //связываем с файлом на диске
    file.open(QIODevice::WriteOnly); //открываем файл на запись
    file.write(ui->textEdit->toPlainText().toUtf8()); //Запись информации с текстового поля в файл
    file.close(); //закрываем файл
    Rename(fileName);
    flagSave = 1; flagChange = 0;

}

void MainWindow::saveAs(){ // функция сохранить как
    fileName = QFileDialog::getSaveFileName(this, tr("Сохранить как"), \
    "D:\\Work\\Study\\Programming\\Qt_worked\\2_sem\\1_practice\\Doci", tr("Text files (*.txt)"));

    if (fileName.isEmpty()) //Файл не выбран
    {
        QMessageBox::information(this, "Предупреждение", "Файл не выбран");
        flagCancel = 1;

    }
    else
    {
        QFile file;
        file.setFileName(fileName); //связываем с файлом на диске
        file.open(QIODevice::WriteOnly); //открываем файл на запись
        file.write(ui->textEdit->toPlainText().toUtf8()); //Запись информации с текстового поля в файд
        file.close(); //закрываем файл
        Rename(fileName);
        flagSave = 1; flagChange = 0;

    }
}

void MainWindow::on_textEdit_textChanged() // изменения
{
    debug();
    flagChange = 1;
    if(fileName != ""){
        QFileInfo fileInfo(fileName);
        QString Title= "";
        Title = fileInfo.fileName();
        this->setWindowTitle("*" + Title + "- NotePad  ©  ПОНОМАРЕВ ДИМИТРИЙ");
    }
    else{
        this->setWindowTitle("*Без имени - NotePad  ©  ПОНОМАРЕВ ДИМИТРИЙ");
    }


//    ui->lineEdit_3->setText(fileName);
//    if(!fileName.isEmpty()){
//        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QDir::homePath(), tr("Text Files (*.txt);;All Files (*)"));
//        QFileInfo fileInfo(fileName);
//        QString name = fileInfo.fileName();
//        this->setWindowTitle(name + TITLE_STRING);
//    }
//    else{
//        this->setWindowTitle(TITLE_STRING);
//   }

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

void MainWindow::Rename(QString Strochka){
    QFileInfo fileInfo(Strochka);
    QString Title= "";
    Title = fileInfo.fileName();
    this->setWindowTitle(Title + " - " + "NotePad  ©  ПОНОМАРЕВ ДИМИТРИЙ");


}


// __________________________ ОПИСЫВАЕМ БЛОК ИНТЕРФЕЙСА

void MainWindow::on_new_d_triggered(){ //кнопка new
    if (flagSave && flagChange){ // сохранен -> изменен
        reply = QMessageBox::question(this, "Предупреждение",
            "Вы желаете сохраниться?",
            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (reply == QMessageBox::Yes){
            save(); New();return;
            }
        if (reply == QMessageBox::No){
            New(); return;
            }
        if (reply == QMessageBox::Cancel){
            return;}
    }
    if ((flagSave && !flagChange) || (!flagSave && !flagChange)){ // сохранен -> не изменен или не сохранен -> не изменен
        New(); return; //сделать название
    }
    if (!flagSave && flagChange){ // не сохранен -> изменен
        reply = QMessageBox::question(this, "Предупреждение",
            "Вы желаете сохраниться?",
            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (reply == QMessageBox::Yes){
            saveAs();
            if(!flagCancel){
            New();
            }
            flagCancel = 0;
            return;
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
            save(); open(); return;
            }
        if (reply == QMessageBox::No){
            open(); return;
            }
        if (reply == QMessageBox::Cancel){
            return;}
    }
    if ((flagSave && !flagChange) || (!flagSave && !flagChange)){ // сохранен -> не изменен или не сохранен -> не изменен
        open(); return;
    }
    if (!flagSave && flagChange){ // не сохранен -> изменен
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
    if ((flagSave && !flagChange) || (!flagSave && !flagChange)){ // сохранен -> не изменен или не сохранен -> не изменен
        return;
    }
    if (!flagSave && flagChange){ // не сохранен -> изменен
        saveAs(); return;
    }
}

void MainWindow::on_saveAs_triggered(){ //кнопка сохранить как
    saveAs();
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
    if ((flagSave && !flagChange) || (!flagSave && !flagChange)){ // сохранен -> не изменен или не сохранен -> не изменен
        exit(0);
    }
    if (!flagSave && flagChange){ // не сохранен -> изменен
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

void MainWindow::on_actionfont_triggered() // изменение текста
{

    bool ok;
    QFont font = QFontDialog::getFont(&ok, m_lastFont, this);
    if (ok) {
        ui->textEdit->setFont(font);

        m_lastFont = font;
        settings.setValue("lastFont", font.toString());
    }
}

void MainWindow::on_copy_2_triggered() // копировать
{
    ui->textEdit->copy();
}

void MainWindow::on_paste_2_triggered() // вставить
{
    ui->textEdit->paste();
}

void MainWindow::on_cut_2_triggered() //вырезать
{
  ui->textEdit->cut();
}


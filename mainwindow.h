#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_open_triggered();

    void on_new_d_triggered();

    void on_save_triggered();

    void on_saveAs_triggered();

    void on_exit_triggered();

    void on_textEdit_textChanged();

    void open();

    void New();

    void save();

    void saveAs();

    void debug();

    void on_pushButton_clicked();

    void Rename(QString Strochka);

//    void changeDebug();

    void on_actionfont_triggered();


    void on_copy_2_triggered();

    void on_paste_2_triggered();

    void on_cut_2_triggered();

private:
    Ui::MainWindow *ui;

    QString fileName = "";



};
#endif // MAINWINDOW_H

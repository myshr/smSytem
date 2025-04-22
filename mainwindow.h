#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

    QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class StudentLoginWindow;
class AdminLoginWindow;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onContinueClicked();

private:
    Ui::MainWindow *ui;

    StudentLoginWindow *studentWindow;
    AdminLoginWindow *adminWindow;
};

#endif // MAINWINDOW_H

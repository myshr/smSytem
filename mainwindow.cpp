#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "studentloginwindow.h"
#include "adminloginwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect the continue button
    connect(ui->continue_, &QPushButton::clicked, this, &MainWindow::onContinueClicked);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onContinueClicked() {
    QString userType = ui->adminorstud->currentText();

    if (userType == "Student") {
        studentWindow = new StudentLoginWindow(this);
        studentWindow->show();
    } else if (userType == "Admin") {
        adminWindow = new AdminLoginWindow(this);
        adminWindow->show();
    } else {
        QMessageBox::warning(this, "Invalid", "Please select a user type.");
    }
}

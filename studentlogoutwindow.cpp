#include "studentlogoutwindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

StudentLogoutWindow::StudentLogoutWindow(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Confirm Log Out");

    label = new QLabel("Are you sure you want to log out?", this);
    logoutButton = new QPushButton("Log Out", this);
    cancelButton = new QPushButton("Cancel", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(logoutButton);
    layout->addWidget(cancelButton);

    connect(logoutButton, &QPushButton::clicked, this, &StudentLogoutWindow::onLogoutClicked);
    connect(cancelButton, &QPushButton::clicked, this, &StudentLogoutWindow::onCancelClicked);
}

void StudentLogoutWindow::onLogoutClicked()
{
    emit logoutConfirmed();
    accept(); // Close dialog
}

void StudentLogoutWindow::onCancelClicked()
{
    reject(); // Close dialog without logging out
}

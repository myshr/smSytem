#include "adminloginwindow.h"
#include "admindashboard.h"  // Include the AdminDashboard header
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

AdminLoginWindow::AdminLoginWindow(QWidget *parent)
    : QWidget(parent)
{
    // Set up the labels and inputs for username and password
    usernamePlaceholder = new QLabel("Username:", this);
    passwordPlaceholder = new QLabel("Password:", this);
    statusLabel = new QLabel("", this);

    usernameInput = new QLineEdit(this);
    usernameInput->setPlaceholderText("Username");

    passwordInput = new QLineEdit(this);
    passwordInput->setPlaceholderText("Password");
    passwordInput->setEchoMode(QLineEdit::Password);

    loginButton = new QPushButton("Login", this);

    // Set up layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(usernamePlaceholder);
    layout->addWidget(usernameInput);
    layout->addWidget(passwordPlaceholder);
    layout->addWidget(passwordInput);
    layout->addWidget(loginButton);
    layout->addWidget(statusLabel);

    connect(loginButton, &QPushButton::clicked, this, &AdminLoginWindow::handleLogin);
    setLayout(layout);
    setWindowTitle("Admin Login");
    resize(300, 200);
}

void AdminLoginWindow::handleLogin()
{
    QString enteredUsername = usernameInput->text().trimmed();
    QString enteredPassword = passwordInput->text().trimmed();

    if (validateCredentials(enteredUsername, enteredPassword)) {
        statusLabel->setText("✅ Login successful!");

        // Close the login window
        this->close();

        // Open the admin dashboard window
        AdminDashboard *adminDashboard = new AdminDashboard();
        adminDashboard->show();
    } else {
        statusLabel->setText("❌ Invalid Username or Password.");
    }
}

bool AdminLoginWindow::validateCredentials(const QString &username, const QString &password)
{
    QFile file("C:/Users/ptrih/OneDrive/QtManagementSystem/QtStudentManagementSyetm-main/admin.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Unable to open admin.txt");
        return false;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();

        if (line.startsWith("Username:")) {
            QString fileUsername = line.section(':', 1).trimmed();

            QString passwordLine = in.readLine();
            QString filePassword = passwordLine.section(':', 1).trimmed();

            if (fileUsername == username && filePassword == password) {
                return true;
            }
        }
    }

    return false;
}

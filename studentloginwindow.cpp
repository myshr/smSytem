#include "studentloginwindow.h"
#include "studentdashboard.h"
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>

StudentLoginWindow::StudentLoginWindow(QWidget *parent)
    : QWidget(parent)
{
    // Setting up the UI elements
    IDplaceholder = new QLabel("Student ID:", this);
    PINplaceholder = new QLabel("PIN:", this);
    statusLabel = new QLabel("", this);

    studentIdInput = new QLineEdit(this);
    studentIdInput->setPlaceholderText("Student ID");

    pinInput = new QLineEdit(this);
    pinInput->setPlaceholderText("PIN");
    pinInput->setEchoMode(QLineEdit::Password);

    studentlogin = new QPushButton("Login", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(IDplaceholder);
    layout->addWidget(studentIdInput);
    layout->addWidget(PINplaceholder);
    layout->addWidget(pinInput);
    layout->addWidget(studentlogin);
    layout->addWidget(statusLabel);


    // Connecting the login button to handleLogin slot
    connect(studentlogin, &QPushButton::clicked, this, &StudentLoginWindow::handleLogin);

    // Set the layout and window properties
    setLayout(layout);
    setWindowTitle("Student Login");
    resize(300, 200);
}

void StudentLoginWindow::handleLogin()
{
    qDebug() << "Login button pressed.";  // Debug line
    QString enteredId = studentIdInput->text().trimmed();
    QString enteredPin = pinInput->text().trimmed();

    if (validateCredentials(enteredId, enteredPin)) {
        statusLabel->setText("✅ Login successful!");

        // Show Student Dashboard after successful login
        StudentDashboard *dashboard = new StudentDashboard(enteredId);
        dashboard->show();

        this->close(); // Optional: close login window after successful login
    } else {
        statusLabel->setText("❌ Invalid ID or PIN.");
    }
}

bool StudentLoginWindow::validateCredentials(const QString &id, const QString &pin)
{
    QFile file("D:/Users/HP/Documents/StudentManagementSytemG4/student.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Unable to open student.txt");
        return false;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        qDebug() << "Reading line: " << line;  // Debug line

        if (line.startsWith("Student ID:")) {
            QString fileId = line.section(':', 1).trimmed();
            qDebug() << "File ID: " << fileId;  // Debug line

            QString nameLine = in.readLine(); // Name line
            Q_UNUSED(nameLine);

            QString pinLine = in.readLine();
            QString filePin = pinLine.section(':', 1).trimmed();
            qDebug() << "File Pin: " << filePin;  // Debug line

            if (fileId == id && filePin == pin) {
                return true;
            }
        }
    }

    return false;
}

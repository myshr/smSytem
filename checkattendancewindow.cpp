#include "checkattendancewindow.h"
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QHeaderView>

CheckAttendanceWindow::CheckAttendanceWindow(const QString &studentId, QWidget *parent)
    : QWidget(parent), m_studentId(studentId)
{
    setWindowTitle("Check Attendance");
    resize(320, 220);

    // 🏷️ QLabel Title
    titleLabel = new QLabel("📅 Check Attendance", this);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold;");

    // 📋 Attendance Table
    attendanceTable = new QTableWidget(this);
    attendanceTable->setColumnCount(2);
    attendanceTable->setRowCount(1);
    attendanceTable->setHorizontalHeaderLabels(QStringList() << "Present" << "Absent");
    attendanceTable->horizontalHeader()->setStretchLastSection(true);
    attendanceTable->verticalHeader()->setVisible(false);
    attendanceTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // ❌ Exit Button
    exitButton = new QPushButton("Exit", this);
    connect(exitButton, &QPushButton::clicked, this, &QWidget::close);

    // 📦 Layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(titleLabel);
    layout->addWidget(attendanceTable);
    layout->addWidget(exitButton);
    setLayout(layout);

    loadAttendance();
}

void CheckAttendanceWindow::loadAttendance()
{
    QFile file("D:/Users/HP/Documents/StudentManagementSytemG4/student.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Unable to open student.txt");
        return;
    }

    QTextStream in(&file);
    bool found = false;
    QString present = "0", absent = "0";

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();

        if (line.startsWith("Student ID:")) {
            found = (line.section(':', 1).trimmed() == m_studentId);
        }

        if (found && line.startsWith("Present:")) {
            present = line.section(':', 1).trimmed();
        }

        if (found && line.startsWith("Absent:")) {
            absent = line.section(':', 1).trimmed();
            break;  // Stop reading — we got both values
        }
    }

    attendanceTable->setItem(0, 0, new QTableWidgetItem(present));
    attendanceTable->setItem(0, 1, new QTableWidgetItem(absent));

    file.close();
}

#include "viewgradeswindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QHeaderView>


ViewGradesWindow::ViewGradesWindow(const QString &studentId, QWidget *parent)
    : QWidget(parent), m_studentId(studentId)
{
    setWindowTitle("View Grades");
    resize(420, 320);

    // 🏷️ QLabel Title
    titleLabel = new QLabel("📊 View Grades", this);
    titleLabel->setStyleSheet("font-size: 20px; font-weight: bold;");

    // 📋 Grades Table
    gradesTable = new QTableWidget(this);
    gradesTable->setColumnCount(2);
    gradesTable->setHorizontalHeaderLabels(QStringList() << "Course" << "Grade");
    gradesTable->horizontalHeader()->setStretchLastSection(true);
    gradesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    gradesTable->verticalHeader()->setVisible(false);

    // ❌ Exit Button
    QPushButton *exitBtn = new QPushButton("Exit", this);
    connect(exitBtn, &QPushButton::clicked, this, &QWidget::close);

    // 📦 Layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(titleLabel);
    layout->addWidget(gradesTable);
    layout->addWidget(exitBtn);

    loadGrades(); // Load the grades from file
}

void ViewGradesWindow::loadGrades()
{
    QFile file("D:/Users/HP/Documents/StudentManagementSytemG4/student.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Could not open student.txt.");
        return;
    }

    QTextStream in(&file);
    bool foundStudent = false;
    bool readingGrades = false;
    gradesTable->setRowCount(0);

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();

        // Check if we found the student based on their student ID
        if (line.startsWith("Student ID:")) {
            foundStudent = (line.section(':', 1).trimmed() == m_studentId);
            readingGrades = false;
        }

        // If we found the student and are at the Grades section
        if (foundStudent && line == "Grades:") {
            readingGrades = true;
            continue; // Skip the "Grades:" line itself
        }

        // Process the grades once we are in the Grades section
        if (foundStudent && readingGrades) {
            if (line.startsWith("- ")) {
                // Extract course and grade (assuming format: - COURSE: GRADE)
                QString course = line.section(':', 0).mid(2).trimmed(); // Remove the "- " and get the course name
                QString grade = line.section(':', 1).trimmed(); // Get the grade

                // Remove anything after the colon (like "NSCI:100" should become "NSCI")
                course = course.split(":")[0];

                // Add a new row to the table for each course-grade pair
                int row = gradesTable->rowCount();
                gradesTable->insertRow(row);
                gradesTable->setItem(row, 0, new QTableWidgetItem(course)); // Set course name
                gradesTable->setItem(row, 1, new QTableWidgetItem(grade)); // Set grade
            } else {
                break; // End of Grades section, stop reading further lines
            }
        }
    }

    file.close();
}

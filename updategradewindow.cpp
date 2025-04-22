#include "updategradewindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

UpdateGradeWindow::UpdateGradeWindow(const QString &studentId, QWidget *parent)
    : QWidget(parent), m_studentId(studentId)
{
    titleLabel = new QLabel("UPDATE GRADE", this);
    courseLabel = new QLabel("Course and Grade", this);
    courseInput = new QLineEdit(this);
    courseInput->setPlaceholderText("Course");

    gradeInput = new QLineEdit(this);
    gradeInput->setPlaceholderText("New Grade");

    updateButton = new QPushButton("Update", this);
    connect(updateButton, &QPushButton::clicked, this, &UpdateGradeWindow::onUpdateClicked);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(titleLabel);
    layout->addWidget(courseLabel);
    layout->addWidget(courseInput);
    layout->addWidget(gradeInput);
    layout->addWidget(updateButton);

    setLayout(layout);
    setWindowTitle("Update Grade");
    resize(250, 200);
}

void UpdateGradeWindow::onUpdateClicked()
{
    QString course = courseInput->text().trimmed();
    QString newGrade = gradeInput->text().trimmed();

    if (course.isEmpty() || newGrade.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter both course and grade.");
        return;
    }

    QFile file("D:/Users/HP/Documents/StudentManagementSytemG4/student.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Could not open student.txt for reading.");
        return;
    }

    QTextStream in(&file);
    QStringList lines;
    bool studentFound = false;
    bool inTargetStudent = false;
    bool inGradesSection = false;
    bool courseUpdated = false;

    while (!in.atEnd()) {
        QString line = in.readLine();

        // Identify student
        if (line.startsWith("Student ID:")) {
            inTargetStudent = (line.section(':', 1).trimmed() == m_studentId);
            studentFound = studentFound || inTargetStudent;
            inGradesSection = false;  // Reset grades section flag
        }

        // Check for Grades section
        if (inTargetStudent && line.trimmed() == "Grades:") {
            inGradesSection = true;
            lines << line;
            continue;
        }

        // Inside Grades section of the correct student
        if (inTargetStudent && inGradesSection) {
            if (line.trimmed().startsWith("- ")) {
                QString gradeLine = line.trimmed().mid(2);  // Remove "- "
                QStringList parts = gradeLine.split(':');
                if (parts.size() >= 2) {
                    QString fileCourse = parts[0].trimmed();

                    if (QString::compare(fileCourse, course, Qt::CaseInsensitive) == 0) {
                        lines << "- " + course + ": " + newGrade;
                        courseUpdated = true;
                        continue;  // Skip old line
                    }
                }
                lines << line;
                continue;
            } else {
                inGradesSection = false;  // End of Grades section
            }
        }

        // Default case
        lines << line;
    }

    file.close();

    if (!studentFound) {
        QMessageBox::warning(this, "Error", "Student not found.");
        return;
    }

    if (!courseUpdated) {
        QMessageBox::warning(this, "Error", "Course not found. Please add it first.");
        return;
    }

    QFile outFile("C:/Users/HP/Documents/StudentManagementSytemG4/student.txt");
    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Could not write to student.txt.");
        return;
    }

    QTextStream out(&outFile);
    for (const QString &line : lines) {
        out << line << "\n";
    }

    outFile.close();

    QMessageBox::information(this, "Success", "Grade updated successfully!");
    courseInput->clear();
    gradeInput->clear();
    close();
}

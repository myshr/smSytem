#include "addgradewindow.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QIntValidator>
#include <QFile>
#include <QTextStream>

AddGradeWindow::AddGradeWindow(const QString &studentId, QWidget *parent)
    : QWidget(parent), m_studentId(studentId)  // Store student ID
{
    // Initialize labels
    addgradelabel = new QLabel("<h2>Add Grade</h2>", this);
    courseLabel = new QLabel("Course:", this);
    gradeLabel = new QLabel("Grade:", this);

    // Initialize input fields
    courseInput = new QLineEdit(this);
    courseInput->setPlaceholderText("Course");

    gradeInput = new QLineEdit(this);
    gradeInput->setPlaceholderText("Grade");
    gradeInput->setValidator(new QIntValidator(0, 100, this));  // Validate grade between 0 and 100

    // Initialize button
    addButton = new QPushButton("Add", this);

    // Layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(addgradelabel);
    layout->addWidget(courseLabel);
    layout->addWidget(courseInput);
    layout->addWidget(gradeLabel);
    layout->addWidget(gradeInput);
    layout->addWidget(addButton);

    // Connect button to slot
    connect(addButton, &QPushButton::clicked, this, &AddGradeWindow::onAddGradeClicked);

    setLayout(layout);
    setWindowTitle("Add Grade");
    resize(300, 200);
}

AddGradeWindow::~AddGradeWindow() {}

void AddGradeWindow::onAddGradeClicked() {
    QString course = courseInput->text().trimmed();
    QString gradeText = gradeInput->text().trimmed();

    if (course.isEmpty() || gradeText.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter both Course and Grade.");
        return;
    }

    bool gradeValid;
    int grade = gradeText.toInt(&gradeValid);

    if (!gradeValid || grade < 0 || grade > 100) {
        QMessageBox::warning(this, "Invalid Grade", "Please enter a valid grade between 0 and 100.");
        return;
    }

    // Open and read the existing file
    QFile file("D:/Users/HP/Documents/StudentManagementSytemG4/student.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Could not open student.txt for reading.");
        return;
    }

    QString content;
    QTextStream in(&file);
    bool studentFound = false;

    while (!in.atEnd()) {
        QString line = in.readLine();
        content += line + "\n";

        if (line.startsWith("Student ID:")) {
            QString id = line.section(':', 1).trimmed();
            if (id == m_studentId) {
                studentFound = true;

                // Copy name and pin
                content += in.readLine() + "\n"; // Name
                content += in.readLine() + "\n"; // PIN

                QString gradesLine = in.readLine();
                if (gradesLine.trimmed() == "Grades:") {
                    content += gradesLine + "\n";
                } else {
                    content += "Grades:\n";
                    content += gradesLine + "\n";
                }

                // Add new grade
                content += "- " + course + ": " + gradeText + "\n";
            }
        }
    }

    file.close();

    if (!studentFound) {
        QMessageBox::warning(this, "Error", "Student not found.");
        return;
    }

    // Write the updated content
    QFile outFile("D:/Users/HP/Documents/StudentManagementSytemG4/student.txt");
    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Could not write to student.txt.");
        return;
    }

    QTextStream out(&outFile);
    out << content;
    outFile.close();

    QMessageBox::information(this, "Success", "Grade added successfully!");

    courseInput->clear();
    gradeInput->clear();
    close();  // Optionally close the window
}

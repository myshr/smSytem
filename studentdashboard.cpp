#include "mainwindow.h"
#include "studentdashboard.h"
#include "addgradewindow.h"
#include "updategradewindow.h"  // ✅ Include UpdateGradeWindow
#include "viewgradeswindow.h"
#include "checkattendancewindow.h"
#include "studentlogoutwindow.h"


#include <QVBoxLayout>
#include <QMessageBox>

StudentDashboard::StudentDashboard(const QString &studentId, QWidget *parent)
    : QWidget(parent), m_studentId(studentId)
{

    // ✅ Initialize widgets
    dashboardTitle = new QLabel("<h2>STUDENT DASHBOARD</h2>", this);
    greetingLabel = new QLabel("Hi! Student " + m_studentId, this);

    addGradeButton = new QPushButton("Add Grade", this);
    updateGradeButton = new QPushButton("Update Grade", this);
    viewGradesButton = new QPushButton("View Grades", this);
    checkAttendanceButton = new QPushButton("Check Attendance", this);
    logOutButton = new QPushButton("Log Out", this);

    // ✅ Set layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(addgradelabel);
    layout->addWidget(dashboardTitle);
    layout->addWidget(greetingLabel);
    layout->addWidget(addGradeButton);
    layout->addWidget(updateGradeButton);
    layout->addWidget(viewGradesButton);
    layout->addWidget(checkAttendanceButton);
    layout->addWidget(logOutButton);

    // ✅ Connect buttons to their slots
    connect(addGradeButton, &QPushButton::clicked, this, &StudentDashboard::onAddGradeClicked);
    connect(updateGradeButton, &QPushButton::clicked, this, &StudentDashboard::onUpdateGradeClicked);
    connect(viewGradesButton, &QPushButton::clicked, this, &StudentDashboard::onViewGradesClicked);
    connect(checkAttendanceButton, &QPushButton::clicked, this, &StudentDashboard::onCheckAttendanceClicked);
    connect(logOutButton, &QPushButton::clicked, this, &StudentDashboard::onLogOutClicked);

    setLayout(layout);
    setWindowTitle("Student Dashboard");
    resize(300, 350);
}

StudentDashboard::~StudentDashboard() {}

void StudentDashboard::onAddGradeClicked() {
    AddGradeWindow *addGradeWindow = new AddGradeWindow(m_studentId);  // ✅ Pass student ID
    addGradeWindow->show();
}

void StudentDashboard::onUpdateGradeClicked() {
    UpdateGradeWindow *updateGradeWindow = new UpdateGradeWindow(m_studentId);  // ✅ Pass student ID
    updateGradeWindow->show();
}

void StudentDashboard::onViewGradesClicked() {
    // Create and show the ViewGradesWindow
    ViewGradesWindow *viewGradesWindow = new ViewGradesWindow(m_studentId);  // Pass studentId
    viewGradesWindow->show();
}

void StudentDashboard::onCheckAttendanceClicked() {
    CheckAttendanceWindow *attendanceWindow = new CheckAttendanceWindow(m_studentId);
    attendanceWindow->show();
}

void StudentDashboard::onLogOutClicked()
{
    StudentLogoutWindow *dialog = new StudentLogoutWindow(this);
    connect(dialog, &StudentLogoutWindow::logoutConfirmed, this, [=]() {
        this->close(); // Close dashboard
        MainWindow *login = new MainWindow();
        login->show(); // Show login screen
    });

    dialog->exec(); // Show modal confirmation
}

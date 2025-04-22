#ifndef STUDENTDASHBOARD_H
#define STUDENTDASHBOARD_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class StudentDashboard : public QWidget
{
    Q_OBJECT

public:
    explicit StudentDashboard(const QString &studentId, QWidget *parent = nullptr);
    ~StudentDashboard();

private slots:
    void onAddGradeClicked();
    void onUpdateGradeClicked();
    void onViewGradesClicked();
    void onCheckAttendanceClicked();
    void onLogOutClicked();

private:
    QString m_studentId;

    QLabel *addgradelabel;
    QLabel *dashboardTitle;
    QLabel *greetingLabel;

    QPushButton *addGradeButton;
    QPushButton *updateGradeButton;
    QPushButton *viewGradesButton;
    QPushButton *checkAttendanceButton;
    QPushButton *logOutButton;
};

#endif // STUDENTDASHBOARD_H

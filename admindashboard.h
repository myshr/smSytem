#ifndef ADMINDASHBOARD_H
#define ADMINDASHBOARD_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

class AdminDashboard : public QWidget
{
    Q_OBJECT

public:
    explicit AdminDashboard(QWidget *parent = nullptr);
    ~AdminDashboard();

private slots:
    void onViewAllRecordsClicked();
    void onModifyRecordsClicked();
    void onDeleteRecordsClicked();
    void onViewGradesAttendanceClicked();
    void onLogoutClicked();

private:
    QLabel *titleLabel;
    QPushButton *viewAllRecordsBtn;
    QPushButton *modifyRecordsBtn;
    QPushButton *deleteRecordsBtn;
    QPushButton *viewGradesAttendanceBtn;
    QPushButton *logoutBtn;
};

#endif // ADMINDASHBOARD_H

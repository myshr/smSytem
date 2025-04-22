#ifndef CHECKATTENDANCEWINDOW_H
#define CHECKATTENDANCEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QTableWidget>
#include <QPushButton>

class CheckAttendanceWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CheckAttendanceWindow(const QString &studentId, QWidget *parent = nullptr);

private:
    void loadAttendance();

    QString m_studentId;
    QLabel *titleLabel;
    QTableWidget *attendanceTable;
    QPushButton *exitButton;
};

#endif // CHECKATTENDANCEWINDOW_H

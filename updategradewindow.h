#ifndef UPDATEGRADEWINDOW_H
#define UPDATEGRADEWINDOW_H

#include <QWidget>
#include <QString>

class QLabel;
class QLineEdit;
class QPushButton;

class UpdateGradeWindow : public QWidget
{
    Q_OBJECT

public:
    explicit UpdateGradeWindow(const QString &studentId, QWidget *parent = nullptr);  // ✅ add QString constructor

private slots:
    void onUpdateClicked();

private:
    QString m_studentId;  // ✅ Store student ID
    QLabel *courseLabel;
    QLabel *titleLabel;
    QLineEdit *courseInput;
    QLineEdit *gradeInput;
    QPushButton *updateButton;
};

#endif // UPDATEGRADEWINDOW_H

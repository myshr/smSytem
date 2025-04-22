#ifndef ADDGRADEWINDOW_H
#define ADDGRADEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class AddGradeWindow : public QWidget {
    Q_OBJECT

public:
    explicit AddGradeWindow(const QString &studentId, QWidget *parent = nullptr);
    ~AddGradeWindow();

private slots:
    void onAddGradeClicked();

private:
    QString m_studentId; // store the student ID

    QLabel *addgradelabel;
    QLabel *courseLabel;
    QLabel *gradeLabel;
    QLineEdit *courseInput;
    QLineEdit *gradeInput;
    QPushButton *addButton;
};

#endif // ADDGRADEWINDOW_H

#ifndef VIEWGRADESWINDOW_H
#define VIEWGRADESWINDOW_H

#include <QWidget>
#include <QTableWidget>
#include <QLabel>

class ViewGradesWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ViewGradesWindow(const QString &studentId, QWidget *parent = nullptr);

private:
    QString m_studentId;
    QLabel *titleLabel;
    QTableWidget *gradesTable;

    void loadGrades();
};

#endif // VIEWGRADESWINDOW_H

#ifndef VIEWALLRECORDSWINDOW_H
#define VIEWALLRECORDSWINDOW_H

#include <QWidget>
#include <QTableWidget>

class ViewAllRecordsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ViewAllRecordsWindow(QWidget *parent = nullptr);
    ~ViewAllRecordsWindow();

private:
    QTableWidget *tableWidget;  // This will hold the student records
    void setupTable();  // Function to set up the table for displaying records
};

#endif // VIEWALLRECORDSWINDOW_H

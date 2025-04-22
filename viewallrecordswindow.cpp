#include "viewallrecordswindow.h"
#include <QTableWidget>
#include <QHeaderView>
#include <QMessageBox>

ViewAllRecordsWindow::ViewAllRecordsWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("View All Student Records");
    resize(600, 400);

    // 🗂️ Table Setup
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(5);  // STUDENT ID | NAME | PIN | COURSE: GRADEES | PRESENT | ABSENT
    tableWidget->setHorizontalHeaderLabels({"STUDENT ID", "NAME", "PIN", "COURSE: GRADEES", "PRESENT", "ABSENT"});
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  // Resize columns to fit

    // Load records into the table (you should replace this with actual data loading logic)
    setupTable();
}

ViewAllRecordsWindow::~ViewAllRecordsWindow() {}

void ViewAllRecordsWindow::setupTable() {
    // For demonstration, adding a row manually
    int row = tableWidget->rowCount();
    tableWidget->insertRow(row);
    tableWidget->setItem(row, 0, new QTableWidgetItem("2024M1127"));
    tableWidget->setItem(row, 1, new QTableWidgetItem("LYKALAMPARERO"));
    tableWidget->setItem(row, 2, new QTableWidgetItem("1028"));
    tableWidget->setItem(row, 3, new QTableWidgetItem("NSCI: 98, ESP: 100"));
    tableWidget->setItem(row, 4, new QTableWidgetItem("18"));
    tableWidget->setItem(row, 5, new QTableWidgetItem("22"));
}


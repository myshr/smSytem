#ifndef STUDENTLOGOUTWINDOW_H
#define STUDENTLOGOUTWINDOW_H

#include <QDialog>

class QPushButton;
class QLabel;

class StudentLogoutWindow : public QDialog
{
    Q_OBJECT
public:
    explicit StudentLogoutWindow(QWidget *parent = nullptr);

signals:
    void logoutConfirmed(); // Signal to return to login

private slots:
    void onLogoutClicked();
    void onCancelClicked();

private:
    QLabel *label;
    QPushButton *logoutButton;
    QPushButton *cancelButton;
};

#endif // STUDENTLOGOUTWINDOW_H

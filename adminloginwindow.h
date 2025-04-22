#ifndef ADMINLOGINWINDOW_H
#define ADMINLOGINWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class AdminLoginWindow : public QWidget {
    Q_OBJECT

public:
    explicit AdminLoginWindow(QWidget *parent = nullptr);

private slots:
    void handleLogin();

private:
    QLabel *usernamePlaceholder;
    QLabel *passwordPlaceholder;
    QLabel *statusLabel;
    QLineEdit *usernameInput;
    QLineEdit *passwordInput;
    QPushButton *loginButton;

    bool validateCredentials(const QString &username, const QString &password);
};

#endif // ADMINLOGINWINDOW_H

#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>

namespace Ui
{
class ChatWindow;
}

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = nullptr);
    ~ChatWindow() override;

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void handleSendTextButtonClick();
    void handleLeaveButtonClick();

    void showTextLog();
    void updateUserList();

private:
    Ui::ChatWindow* ui;
};

#endif // CHATWINDOW_H

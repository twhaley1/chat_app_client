#include "chatwindow.h"
#include "ui_chatwindow.h"

#include "viewmodel/viewmodel.h"

ChatWindow::ChatWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChatWindow)
{
    this->ui->setupUi(this);
    this->ui->aliasLabel->setText(QString::fromStdString(vm::ViewModel::get()->getAlias() + ": "));

    this->connect(this->ui->sendTextPushButton, SIGNAL(released()), this, SLOT(handleSendTextButtonClick()));
    this->connect(this->ui->sendingTextEdit, SIGNAL(returnPressed()), this, SLOT(handleSendTextButtonClick()));
    this->connect(this->ui->leaveButton, SIGNAL(released()), this, SLOT(handleLeaveButtonClick()));
    this->connect(vm::ViewModel::get(), SIGNAL(logChanged()), this, SLOT(showTextLog()));
    this->connect(vm::ViewModel::get(), SIGNAL(usersChanged()), this, SLOT(updateUserList()));
}

void ChatWindow::handleSendTextButtonClick()
{
    std::string message = this->ui->sendingTextEdit->text().toUtf8().constData();
    if (!message.empty())
    {
        vm::ViewModel::get()->sendMessage(message);
        this->ui->sendingTextEdit->clear();
    }
}

void ChatWindow::handleLeaveButtonClick()
{
    vm::ViewModel::get()->leave();
    qApp->exit();
}

void ChatWindow::showTextLog()
{
    std::string log = vm::ViewModel::get()->getLog();
    QString logText = QString::fromStdString(log);
    this->ui->messageDisplayTextBrowser->setPlainText(logText);
}

void ChatWindow::updateUserList()
{
    this->ui->userListView->clear();
    std::vector<std::string> users = vm::ViewModel::get()->getUsers();
    int rowNumber = 0;
    for (auto& user : users)
    {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(user));
        this->ui->userListView->insertItem(rowNumber, item);
        rowNumber++;
    }
}

void ChatWindow::closeEvent(QCloseEvent* event)
{
    vm::ViewModel::get()->leave();
    QMainWindow::closeEvent(event);
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

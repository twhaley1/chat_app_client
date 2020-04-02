#include "chatwindow.h"
#include "ui_chatwindow.h"

#include "viewmodel/viewmodel.h"

ChatWindow::ChatWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChatWindow)
{
    this->ui->setupUi(this);
    this->connect(this->ui->sendTextPushButton, SIGNAL(released()), this, SLOT(handleSendTextButtonClick()));
    this->connect(vm::ViewModel::get(), SIGNAL(logChanged()), this, SLOT(showTextLog()));
}

void ChatWindow::handleSendTextButtonClick()
{
    std::string message = this->ui->sendingTextEdit->toPlainText().toUtf8().constData();
    if (!message.empty())
    {
        vm::ViewModel::get()->sendMessage(message);
        this->ui->sendingTextEdit->clear();
    }
}

void ChatWindow::showTextLog()
{
    std::string log = vm::ViewModel::get()->getLog();
    QString logText = QString::fromStdString(log);
    this->ui->messageDisplayTextBrowser->setPlainText(logText);
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

#include "startwindow.h"
#include "ui_startwindow.h"

#ifdef DEBUG
#include <iostream>
#endif

#include "chatwindow.h"
#include "viewmodel/viewmodel.h"

StartWindow::StartWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartWindow)
{
    this->ui->setupUi(this);
    this->connect(this->ui->joinChatPushButton, SIGNAL(released()), this, SLOT(handleJoinButtonClick()));
}

void StartWindow::handleJoinButtonClick()
{
    std::string alias = this->ui->aliasLineEdit->text().toUtf8().constData();
#ifdef DEBUG
    std::cout << "Attempting to join chat with alias: " << alias << std::endl;
#endif

    vm::ViewModel* model = vm::ViewModel::get();
    model->join(alias);
#ifdef DEBUG
    std::cout << "Join successful" << std::endl;
#endif
    ChatWindow* chat = new ChatWindow();
    chat->show();
    this->close();
}

StartWindow::~StartWindow()
{
    delete ui;
}


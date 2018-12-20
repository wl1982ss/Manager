#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);



}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_loginBtn_clicked()
{

    // 验证数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("Manager");
    db.setUserName("root");
    db.setPassword("");
    if(db.open())
    {
        QSqlQuery query(db);
        query.exec("select name, password from user");
        while(query.next())
        {
            QString username = query.value(1).toString().trimmed();
            QString password = query.value(2).toString().trimmed();

            //判断用户名和密码是否正确
            //如果错误则弹出警告对话框
            if((ui->userLineEdit->text() == username) && (ui->pwdLineEdit->text() == password))
            {
                accept();
            }
            else
            {
                QMessageBox::warning(this, tr("Warning"), tr("user name or password error!"),
                                     QMessageBox::Yes);
                // 清空内容并定位光标
                ui->userLineEdit->clear();
                ui->pwdLineEdit->clear();
                ui->userLineEdit->setFocus();
            }
        }
    }
    else
    {
        QMessageBox::warning(this, tr("Cannot open database"), tr("Unable to establish a database connection"),
                              QMessageBox::Cancel);
        //return false;
    }


}

void LoginDialog::on_exitBtn_clicked()
{
    this->close();
}

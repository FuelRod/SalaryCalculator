#include "setting.h"
#include "ui_setting.h"
//读写文件
#include <fstream>
//debug
#include <QDebug>
//主窗口头文件
#include "mainwindow.h"
//string
#include <string>
//全局函数
#include <globalfunc.h>
//ini
#include <windows.h>
#include <tchar.h>
//头像窗口
#include "head.h"




using namespace std;

//单例
Setting* Setting::instance = NULL;
Setting* Setting::GetIns(){
    if(instance == NULL){
        instance = new Setting();
    }
    return instance;
}

//构造函数
Setting::Setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);

    //禁止拖拽
    setFixedSize(this->width(),this->height());
}



//amongst others
void Setting::showEvent(QShowEvent * event)
{
    //初始化
    Init();
}


//uishow时初始化
void Setting::Init()
{
    //读取参数
    ui->month_salary_input->setText(QString::number(MainWindow::GetIns()->monthSalary));
    ui->start_h_input->setText(QString::number(MainWindow::GetIns()->start_h));
    ui->start_m_input->setText(QString::number(MainWindow::GetIns()->start_m));
    ui->end_h_input->setText(QString::number(MainWindow::GetIns()->end_h));
    ui->end_m_input->setText(QString::number(MainWindow::GetIns()->end_m));

}




//确定按钮
void Setting::on_apply_button_clicked()
{
    //再校验一下字符串格式是否为int吧
    //...

    //如果数据没有问题
    if(GlobalFunc::CheckSalary(ui->month_salary_input->text().toUInt())//工资
            &&GlobalFunc::CheckTime( ui->start_h_input->text().toUInt(),//时间
                                     ui->start_m_input->text().toUInt(),
                                     ui->end_h_input->text().toUInt(),
                                     ui->end_m_input->text().toUInt())){

        //赋值main变量
        MainWindow::GetIns()->monthSalary = ui->month_salary_input->text().toUInt();
        MainWindow::GetIns()->start_h = ui->start_h_input->text().toUInt();
        MainWindow::GetIns()->start_m = ui->start_m_input->text().toUInt();
        MainWindow::GetIns()->end_h = ui->end_h_input->text().toUInt();
        MainWindow::GetIns()->end_m = ui->end_m_input->text().toUInt();

        //存入ini
        //配置路径
        LPCWSTR iniPath =  L"./Config.ini";
        //写入
        WritePrivateProfileString(L"lable", L"config_monthSalary",String2LPCWSTR(to_string(MainWindow::GetIns()->monthSalary)), iniPath);
        WritePrivateProfileString(L"lable", L"config_start_h", String2LPCWSTR(to_string(MainWindow::GetIns()->start_h)), iniPath);
        WritePrivateProfileString(L"lable", L"config_start_m", String2LPCWSTR(to_string(MainWindow::GetIns()->start_m)), iniPath);
        WritePrivateProfileString(L"lable", L"config_end_h", String2LPCWSTR(to_string(MainWindow::GetIns()->end_h)), iniPath);
        WritePrivateProfileString(L"lable", L"config_end_m", String2LPCWSTR(to_string(MainWindow::GetIns()->end_m)), iniPath);

        //离开界面
        this->close();
    }
    else{
        //弹出报错窗体，拒绝退出


        qDebug()<<"设置失败";
    }
}
//字符串 转 LPCWSTR
LPCWSTR Setting::String2LPCWSTR(string str){
    const char* charstr = (char*)str.c_str();

    QString args = QString::fromLocal8Bit(charstr);
    std::wstring wlpstrstd = args.toStdWString();
    LPCWSTR lpcwStr = wlpstrstd.c_str();

    return lpcwStr;
}

//取消按钮
void Setting::on_cancel_button_clicked()
{
    //直接关闭
    this->close();
}

//开发者按钮
void Setting::on_developer_button_clicked()
{
    qDebug()<<"显示头像";
    Head* headIns = new Head();
    headIns->show();
}

Setting::~Setting()
{
    delete ui;
}









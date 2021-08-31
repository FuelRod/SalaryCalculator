#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <QTimer>
#include <QDebug>
//全局函数
#include "GlobalFunc.h"

//ini
#include <windows.h>

//设置界面
#include "setting.h"

//时间
#include <ctime>
//毫秒
#include<sys/timeb.h>
//数学
#include <math.h>
//字体
#include <QFontDatabase>

//拖拽
#include <QtWidgets/QWidget>
#include <QMouseEvent>


using namespace std;

//单例
MainWindow* MainWindow::instance = NULL;
MainWindow* MainWindow::GetIns(){
    if(instance == NULL){
        instance = new MainWindow();
        qDebug()<<"new了一次";
    }
    return instance;
}

//构造函数
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //设置单例
    instance = this;

    //隐藏边框
    this->setWindowFlags(Qt::FramelessWindowHint);
    //禁止拖拽
    setFixedSize(this->width(),this->height());
    //加载字体
    QFontDatabase::addApplicationFont(":/Image/Resource/digital-7 (mono).ttf");
    QFontDatabase::addApplicationFont(":/Image/Resource/digital-7 (mono italic).ttf");

    //完成初始化
    Init();
}

//初始化函数
void MainWindow::Init()
{
    //尝试读取并赋值
    bool result = ReadAndSetIni();
    //读取失败
    if(!result){
        //初始化ini文件
        InitIni();
        qDebug("ini文件不存在/读取失败，重新初始化ini文件");
        //再次读取
        bool resultAgain = ReadAndSetIni();
        //再次失败
        if(!resultAgain){
            qDebug("第二次读取失败，初始化失败，退出");
            return;
        }
    }

    //声明
    QTimer *timer = new QTimer();
    //设置函数
    connect(timer,&QTimer::timeout,[=](){Update();});
    //开启刷新
    timer->start(1);
}


bool MainWindow::ReadAndSetIni()
{
    //配置路径
    LPCWSTR iniPath =  L"./Config.ini";

    //读取config 暂时无法处理int以外的类型报错
    int config_monthSalary = GetPrivateProfileInt(L"lable", L"config_monthSalary", -1, iniPath);
    int config_start_h = GetPrivateProfileInt(L"lable", L"config_start_h", -1, iniPath);
    int config_start_m = GetPrivateProfileInt(L"lable", L"config_start_m", -1, iniPath);
    int config_end_h = GetPrivateProfileInt(L"lable", L"config_end_h", -1, iniPath);
    int config_end_m = GetPrivateProfileInt(L"lable", L"config_end_m", -1, iniPath);

    //校验数据
    if(GlobalFunc::CheckSalary(config_monthSalary)&&GlobalFunc::CheckTime(config_start_h,config_start_m,config_end_h,config_end_m))
    {
        //更新参数
        monthSalary = config_monthSalary;
        start_h = config_start_h;
        start_m = config_start_m;
        end_h = config_end_h;
        end_m = config_end_m;

        return true;
    }
    else
    {
        return false;
    }
}

void MainWindow::InitIni()
{
    //配置路径
    LPCWSTR iniPath = L"./Config.ini";
    //写入
    WritePrivateProfileString(L"lable", L"config_monthSalary", L"2100", iniPath);
    WritePrivateProfileString(L"lable", L"config_start_h", L"9", iniPath);
    WritePrivateProfileString(L"lable", L"config_start_m", L"0", iniPath);
    WritePrivateProfileString(L"lable", L"config_end_h", L"17", iniPath);
    WritePrivateProfileString(L"lable", L"config_end_m", L"0", iniPath);
}

//更新函数 持续更新，不停止
void MainWindow::Update(){

    //参数不对时提醒错误
    if(!GlobalFunc::CheckTime(start_h,start_m,end_h,end_m)){
        ui->salary_Label->setText("---.---");
        ui->timeout_Label->hide();
        ui->error_Label->show();

        return;
    }
    ui->error_Label->hide();


    //总时间 = 上班 - 下班时间
    //已过时间 = 上班 - 当前时间
    //当前度过时间比 = 已过时间 / 总时间
    //日薪 = 月薪 / 30
    //当前薪 = 日薪 * 度过时间比

    //今日日期
    time_t tempT = time(0);

    //上班时间
    struct tm startTime;
    localtime_s(&startTime, &tempT);
    startTime.tm_hour = start_h;
    startTime.tm_min = start_m;
    startTime.tm_sec = 0;
    //下班时间
    struct tm endTime;
    localtime_s(&endTime, &tempT);
    endTime.tm_hour = end_h;
    endTime.tm_min = end_m;
    endTime.tm_sec = 0;
    //总时间（秒）
    int allSecond;
    allSecond = difftime(mktime(&endTime),mktime(&startTime));

    //当前时间
    struct timeb curTimeb;
    ftime(&curTimeb);
    struct tm curTime;
    localtime_s(&curTime, &curTimeb.time);
    //当前毫秒
    float curTick = curTimeb.millitm/1000.0f;

    //已工作时间
    float workSecond;
    workSecond = difftime(mktime(&curTime),mktime(&startTime))+curTick;

    //当前度过时间比
    float ratio = workSecond/allSecond;

    //提前
    if(ratio<0){
        ui->salary_Label->setText("---.---");
        ui->timeout_Label->show();
    }
    //超时
    else if(ratio>1){
        //日薪
        float daySalary = monthSalary / 30;
        char daySalary2f[64];
        sprintf(daySalary2f, "%.3f", daySalary);

        ui->salary_Label->setText(daySalary2f);
        ui->timeout_Label->show();
    }
    //正常
    else{
        //日薪
        float daySalary = monthSalary / 30;

        //当前薪资
        float curSalary = daySalary * ratio;

        //3位小数
        char curSalary2f[64];
        sprintf(curSalary2f, "%.3f", curSalary);

        //更新lable
        ui->salary_Label->setText(curSalary2f);
        ui->timeout_Label->hide();
    }
}

//设置按钮点击
void MainWindow::on_setting_Button_clicked()
{
    //弹出ui，完成初始化
    Setting::GetIns()->show();
}

//退出按钮
void MainWindow::on_exit_Button_clicked()
{
    QApplication::exit();
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Escape:
        QApplication::exit();
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}



MainWindow::~MainWindow()
{
    delete ui;
}






void MainWindow::on_Drop_Button_clicked()
{

}


void MainWindow::on_Drop_Button_pressed()
{

}


void MainWindow::on_Drop_Button_released()
{

}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        M_point = e->globalPos() - pos();
        e->accept();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() & Qt::LeftButton) {
        move(e->globalPos() - M_point);
        e->accept();
    }
}









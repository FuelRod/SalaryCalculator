#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//时间
#include <ctime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public:
    //单例
    static MainWindow* GetIns();
    static MainWindow* instance;


    //变量
    //工资（月薪
    int monthSalary;
    //设置时间
    int start_h;
    int start_m;
    int end_h;
    int end_m;

    //函数
    void Init();

    //读取并设置ini
    bool ReadAndSetIni();
    //初始化ini
    void InitIni();

    //每秒更新
    void Update();

    //校验数据
    bool CheckSalary(int salary);
    bool CheckTime(int start_h,int start_m,int end_h,int end_m);
    int a=0;
    QPoint M_point;

private slots:
    void on_setting_Button_clicked();
    void on_exit_Button_clicked();

    //??
    void on_Drop_Button_clicked();
    void on_Drop_Button_pressed();
    void on_Drop_Button_released();

    //面板点击/移动事件
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    //键盘点击事件
    void keyPressEvent(QKeyEvent *event);



private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

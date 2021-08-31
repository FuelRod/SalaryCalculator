#ifndef SETTING_H
#define SETTING_H

#include <QWidget>
//ini&LPCTSTR
#include <windows.h>
//string
#include <string.h>

namespace Ui {
class Setting;
}

class Setting : public QWidget
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = nullptr);
    ~Setting();

public:

public:
    //单例
    static Setting* GetIns();
    static Setting* instance;

    //初始化
    void Init();
    LPCWSTR String2LPCWSTR(std::string x);
    //头像按钮
    void head_button_clicked();
    void openUrl(QString url);
private slots:
    //插槽
    void on_apply_button_clicked();
    void on_cancel_button_clicked();
    void on_developer_button_clicked();

protected :
    //show时间
    void showEvent(QShowEvent * event);




private:
    Ui::Setting *ui;



};





#endif // SETTING_H

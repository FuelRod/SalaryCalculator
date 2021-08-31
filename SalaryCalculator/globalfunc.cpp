#include "globalfunc.h"

GlobalFunc::GlobalFunc()
{

}


//检查工资
bool GlobalFunc::CheckSalary(int salary)
{
    if(0<salary&&salary<=300000)
        return true;
    return false;
}

//检查时间
bool GlobalFunc::CheckTime(int start_h, int start_m, int end_h, int end_m)
{
    if(start_h>=0&&start_h<24&&start_m>=0&&start_m<60
            &&end_h>=0&&end_h<24&&end_m>=0&&end_m<60
            &&!((start_h==end_h)&&(start_m==end_m))//时间不相等
            ){
        return true;
    }
    return false;
}

std::string GlobalFunc::GetConfigPath()
{
    return "123";
}



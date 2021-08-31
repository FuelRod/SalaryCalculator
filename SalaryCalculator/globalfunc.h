#ifndef GLOBALFUNC_H
#define GLOBALFUNC_H
#include <string>

class GlobalFunc
{
public:
    GlobalFunc();

    //检查工资/时间
    static bool CheckSalary(int salary);
    static bool CheckTime(int start_h, int start_m, int end_h, int end_m);
    static std::string GetConfigPath();
};

#endif // GLOBALFUNC_H

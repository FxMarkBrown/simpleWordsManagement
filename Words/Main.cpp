#include <cstdlib>
#include <iostream>
#include "ApplicationEntry.h"

using namespace std;

int main() {
    //重构中
    //目标：分离程序启动与表读取以支持多个单词表
    /*
    char fn[20];
    cout << "请输入文件名:";
    cin >> fn;

    char* fn_pt = fn;

    //实例化一个文件管理对象(如果以后智商上去了，可以整个多对象可切换单词表的)
    TableUtils tu1;
    if (tu1.loadFile(fn_pt) == true) cout << "成功读入文件!" << endl;
    else exit(0);
    //成功读入后,传入链表头部指针,读取文件中的字节存入链表
    if (tu1.getBufferToTable(pt_w)) cout << "成功读入所有单词!" << endl;

    //读取单词展现在屏幕上并不停给你看，让你记住它
    if (tu1.readBufferFromTable(pt_w,pt_wf) == true) cout << "操作完成!" << endl;
    else exit(0);
    */
    
    //启动程序实例
    ApplicationEntry applicationEntry;
    applicationEntry.startApplication();
}
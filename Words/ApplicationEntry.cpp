#include <iostream>
#include "ApplicationEntry.h"
#include "TableUtils.h"

using namespace std;

//##############程序启动入口##############
void ApplicationEntry::startApplication() {
    //*调用成员tu的私有成员函数执行操作
    //载入文件
    loadFile();
    tu.readBufferFromTable();
}

//##############读取文件并创建链表##############
//exception还没学，暂时直接返回个true假装全部读取成功了:)
void ApplicationEntry::loadFile() {
    //****待重构：多个单词表支持（由对象组成的链表)****
    
    //打开文件
    char fn[20];
    cout << "请输入文件名:";
    cin >> fn;
    char* fn_pt = fn;

    tu.file.open(fn_pt);
    if (!tu.file.is_open()) {
        cout << "文件打开错误！" << endl;
        exit(0);
    }

    //读入链表
    tu.getBufferToTable();
}

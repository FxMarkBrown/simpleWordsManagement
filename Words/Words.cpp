#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "TableUtils.h"

using namespace std;

//初始化单词表/遗忘词表指针
struct Words* pt_w = NULL;
struct WordsForgetten* pt_wf = NULL;

int main() {
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
    /*暂时没写*/
    if (tu1.readBufferFromTable(pt_w,pt_wf) == true) cout << "操作完成!" << endl;
    else exit(0);
}
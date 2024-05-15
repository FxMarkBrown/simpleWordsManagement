#include <iostream>
#include "ApplicationEntry.h"
#include "TableUtils.h"

using namespace std;

//##############选择模式##############
void ApplicationEntry::chooseMode() {
    //选择模式
    cout << "选择检查单词的模式 N（普通），D（听写）: ";
    char key;
    cin >> key;
    cin.get();
    switch (key) {
    case 'N': {
        //设置模式
        tu->mode = 'N';
        break;
    }
    case 'D': {
        tu->mode = 'D';
        break;
    }
    }
}

void ApplicationEntry::chooseReference() {
    cout << "选择单词表的对照：答案在@前（f），答案在@后（b）:";
    char ref;
    cin >> ref;
    cin.get();
    switch (ref) {
    case 'f': {
        tu->ref = 'f';
        break;
    }
    case 'b': {
        tu->ref = 'b';
        break;
    }
    }
}


//##############程序启动入口##############
void ApplicationEntry::startApplication() {
    //创建表管理对象
    tu = new TableUtils;
    //*调用成员tu的私有成员函数执行操作
    //检查是否有上次遗留的遗忘单词锁文件wordsWF.lock
    if (tu->hasFileWF()) {
        //选择模式
        chooseMode();
        cout << "检测到有上一次没有复习的遗忘单词" << endl;
        //加载锁文件并读取内容
        loadWFFile();
        //调用读取遗忘单词表并检查的函数
        tu->readBuffefromWFTable();
        //删除锁文件
        tu->deleteFileWF();

        cout << "上次遗忘的单词检查完毕，现在你可以选择是否检查新的单词（N）或退出（Y）: ";
        char choiceContinue;
        cin >> choiceContinue;
        if (choiceContinue == 'Y') {
            exit(0);
        }
        else {
            //析构tu对象一次再创建新的tu，这样可清除遗忘单词表中的单词，放置重新检查时出错
            delete tu;
            tu = new TableUtils;
        }
    }

    chooseMode();
    if (tu->mode == 'D')chooseReference();
    loadFile();
    tu->readBufferfromTable();

    cout << "单词检查完毕，程序退出" << endl;
}

//##############读取文件并创建链表##############
//exception还没学，暂时直接返回个true假装全部读取成功了:)
void ApplicationEntry::loadFile() {
    //****待重构：多个单词表支持（由对象组成的链表)****
    
    //打开文件
    string fn;
    cout << "请输入文件名:";
    cin >> fn;
    cin.get();

    tu->inputfile.open(fn);
    if (!tu->inputfile.is_open()) {
        cout << "文件打开错误！" << endl;
        exit(0);
    }

    //读入链表
    tu->getBuffertoTable();
}

//##############加载遗忘单词表文件并读入遗忘单词链表##############
void ApplicationEntry::loadWFFile() {
    tu->inputfile.open("wordsWF.lock");
    if (!tu->inputfile.is_open()) {
        cout << "文件打开错误！" << endl;
        exit(0);
    }

    //读入遗忘单词链表
    tu->getBuffertoWFTable();
}

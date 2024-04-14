#pragma once
#include <string>
#include <fstream>
using namespace std;

//声明存储单词的链表
struct Words {
    string words = "NONE";
    struct Words* next = NULL;
};

//遗忘单词表
struct WordsForgetten {
    string words = "NONE";
    struct WordsForgetten* next = NULL;
};

//操作类
class TableUtils {
private:
    //文件输入对象
    ifstream file;
    //总读入单词数量
    int wordCout;
    //遗忘单词数量
    int numWordsForgetten;
    //单词表指针成员，供最后析构函数释放链表使用
    Words* head;
    WordsForgetten* headWF;
    //遗忘单词表尾部指针，供创建遗忘链表单元/降低单元优先级时调用
    WordsForgetten* endWF;

    //操作类函数
    //写入链表、读取链表并显示操作
    void getBufferToTable(); //完成
    void readBufferFromTable(); //完成
    //遗忘单词表创建、读取、移动、删除操作
    void createWFTable(string wordsProd); //完成
    void readBuffeFromWFTable(); //完成
    void moveWordsInWFTable(WordsForgetten* wordForgetten); //完成
    void deleteSpecificWordsInWFTable(WordsForgetten* wordRemember); //完成

    //友元程序访问入口
    friend class ApplicationEntry;
public:
    //构造函数以及析构函数
    TableUtils();
    ~TableUtils();
};
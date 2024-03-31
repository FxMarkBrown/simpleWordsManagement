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

    //操作类函数
    //写入链表、读取链表并显示操作
    bool getBufferToTable(Words* head); //完成
    bool readBufferFromTable(Words* read, WordsForgetten* headWF); //完成
    //遗忘单词表创建、读取、移动、删除操作
    bool createWFTable(string wordsProd, WordsForgetten* headWF, WordsForgetten*& end); //完成
    bool readBuffeFromWFTable(WordsForgetten* read); //完成
    bool moveWordsInWFTable(WordsForgetten*& headWF, WordsForgetten* wordForgetten); //完成
    bool deleteSpecificWordsInWFTable(WordsForgetten*& headWF, WordsForgetten* wordRemember); //完成

    //友元程序访问入口
    friend class ApplicationEntry;
public:
    //构造函数以及析构函数
    TableUtils();
    ~TableUtils();
};
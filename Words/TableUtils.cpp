#include <iostream>
#include "TableUtils.h"

using namespace std;

/*-----------------单词表操作-----------------*/
//覆写构造函数初始化私有成员
TableUtils::TableUtils() {
    wordCout = 0;
    numWordsForgetten = 0;
    head = NULL;
    headWF = NULL;
}

//exception还没学，暂时直接返回个true假装全部读取成功了:)
bool TableUtils::loadFile(char* filename) {
    file.open(filename);
    return file.is_open();
}

bool TableUtils::getBufferToTable(Words* head) {
    //创建头链表
    head = new Words;
    //单词写入指针
    Words* write = head;
    //链表创建指针
    Words* create;
    string str;
    //读入每一行，若未碰到文件尾EOF，则一直循环读入
    while (getline(file, str))
    {
        //计数读到了几个单词
        wordCout++;
        //写入单词
        write->words = str;
        //创建下一个链表
        create = new Words;
        //链接
        write->next = create;
        //移动write指针至下一链表
        write = create;
    }
    cout << "很好，共读入 " << wordCout << " 个单词" << endl;
    file.close();

    //创建私有成员指针
    TableUtils::head = head;

    return true;
}

//##单词链表读取
bool TableUtils::readBufferFromTable(Words* read, WordsForgetten* headWF) {
    //针对遗忘单词表添加单词使用的遗忘单词链表尾部指针（引用传递）
    WordsForgetten* endOfWF;
    //检索Words表
    char choice;
    while (read->next != NULL) {
        cout << read->words << "你是否还记得? :";
        cin >> choice;
        switch (choice) {
            case 'y': {
                //下一链表，开始一个新循环
                read = read->next;
                continue;
            }
            case 'n': {
                 //存入,并开始下一个循环
                createWFTable(read->words, headWF, endOfWF);
                continue;
            }
        }
    }

    //开始检查WordsForgetten是否存在
    if (headWF == NULL) {
        cout << "恭喜你！全部过关！";
        //设置私有成员指针，后交由析构函数释放链表
        TableUtils::head = head;
        exit(0);
    }
    else {
        //设置私有单词表指针
        TableUtils::head = head;
        readBuffeFromWFTable(headWF);
    }

    return true;
}

bool TableUtils::createWFTable(string wordsProd, WordsForgetten* headWF, WordsForgetten* &end) {
    //创建指针
    WordsForgetten* create;
    //写入指针
    WordsForgetten* write;
    //如果还未建立链表，则建立头部链表，并填入单词，然后设置尾部指针end
    if (headWF == NULL) {
        headWF = new WordsForgetten;
        write = headWF;
        write->words = wordsProd;
        //建立下一个
        create = new WordsForgetten;
        //链接
        write->next = create;
        //设置尾部
        end = create;
    }
    //如果已经建立，则根据尾部指针end来创建新表
    else {
        write = end;
        //填入单词
        write->words = wordsProd;
        //创建新表
        create = new WordsForgetten;
        //链接
        write->next = create;
        //设置新尾部
        end = create;
    }

    //设置私有成员指针
    TableUtils::headWF = headWF;

    return true;
}

bool TableUtils::readBuffeFromWFTable(WordsForgetten* read) {
    //留存读取位置的头部供再次读取使用
    WordsForgetten* headWF = read;
    //设置私有成员指针
    TableUtils::headWF = headWF;
    //读取遗忘单词表，逻辑与单词表类似
    char choiceWF;
    //归零遗忘单词数，防止函数递归后无限增加
    numWordsForgetten = 0;
    //检索遗忘单词表
    while (read->next != NULL) {
        cout << "还记得 " << read->words << " 吗？" << endl;
        cin >> choiceWF;
        switch (choiceWF) {
            case 'y': {
                //将此单词从表中删除,因为可能涉及到第一个单词，所以引用传递表头部head
                deleteSpecificWordsInWFTable(headWF,read);
                continue;
            }
            case 'n': {
                //将此单词提高优先级，即移动到链表最前方
                moveWordsInWFTable(headWF,read);
                numWordsForgetten++;
                continue;
            }
        }
    }

    //如果全记起来了
    if (headWF == NULL) {
        cout << "恭喜你！全部过关！";
        exit(0);
    }
    //如果没有，继续递归此函数读取，直到全部记起来为止（想结束多半只能Alt F4了）
    else {
        cout << "忘掉了" << numWordsForgetten++ <<" 个单词"<<endl;
        readBuffeFromWFTable(headWF);
    }

    //留着给exception
    return true;
}

bool TableUtils::deleteSpecificWordsInWFTable(WordsForgetten* &headWF, WordsForgetten* wordRemember) {
    //设置私有成员指针
    TableUtils::headWF = headWF;
    //如果涉及到表头部单词的删除操作,则通过引用传递改变表的头部指针
    if (wordRemember == headWF) {
        headWF = headWF->next;
        delete wordRemember;
        return true;
    }

    //如果是链表中的非头部单元，则还要判断是否是尾部
    //因为现在还妹学双向链表，所以为了找到上一个链表，暂时先遍历整个链表
    
    //寻找上一个单元
    WordsForgetten* find = headWF;
    while (find->next != wordRemember) {
        find = find->next;
    }
    //操作完成后find即是WordRemember的上一单元
    //如果是尾部
    if (wordRemember->next == NULL) {
        find->next = NULL;
        delete wordRemember;
        return true;
    }
    //如果是中间单元
    else {
        find->next = wordRemember->next;
        delete wordRemember;
        return true;
    }

    return true;
}

bool TableUtils::moveWordsInWFTable(WordsForgetten* &headWF,WordsForgetten* wordForgetten) {
    //设置私有成员指针
    TableUtils::headWF = headWF;
    //如果第一个就妹记住,则不执行任何操作
    //如果不是，则再分情况
    if (wordForgetten != headWF) {
        //首先找到上一单元
        WordsForgetten* find = headWF;
        while (find->next != wordForgetten) {
            find = find->next;
        }

        //如果是尾部
        if (wordForgetten->next == NULL) {
            find->next = NULL;
            wordForgetten->next = headWF;
            headWF = wordForgetten;
            return true;
        }
        //如果是中间单元
        else {
            find->next = wordForgetten->next;
            wordForgetten->next = headWF;
            headWF = wordForgetten;
            return true;
        }
    }

    return true;
}

/*
所有操作进行完毕后，在对象声明周期结束前调用析构函数释放所有链表单元
因为没学exception，所以上方不停的存储head和headWF，以保证一旦程序错误结束，析构函数可以最大
限度析构所有链表，以减少内存中的垃圾
*/
TableUtils::~TableUtils() {
    //首先析构单词表
    Words* find = head;
    while (head->next != NULL) {
        //找到尾部
        while (find->next != NULL) {
            find = find->next;
        }
        //释放
        delete find;
    }
    //最后删除头部
    delete head;

    //再析构遗忘词表
    if (headWF != NULL) {
        WordsForgetten* findWF = headWF;
        while (headWF != NULL) {
            //找到尾部
            while (findWF->next != NULL) {
                findWF = findWF->next;
            }
            //释放
            delete findWF;
        }
        //删除头部
        delete headWF;
    }
}

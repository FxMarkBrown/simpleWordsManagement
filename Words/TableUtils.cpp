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
    endWF = NULL;
}


void TableUtils::getBufferToTable() {
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


}
//##############读取文件并创建链表##############

//##############单词链表读取##############
void TableUtils::readBufferFromTable() {
    //读取指针
    Words* read = head;
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
                createWFTable(read->words);
                numWordsForgetten++;
                read = read->next;
                continue;
            }
        }
    }

    //开始检查WordsForgetten是否存在
    if (headWF == NULL) {
        cout << "恭喜你！全部过关！";
        exit(0);
    }
    else {
        cout << "忘掉了 " << numWordsForgetten << " 个单词"<<endl;
        readBuffeFromWFTable();
    }

}
//##############单词链表读取##############

//##############遗忘表创建##############
void TableUtils::createWFTable(string wordsProd) {
    //创建指针
    WordsForgetten* create;
    //写入指针
    WordsForgetten* write;
    //如果还未建立链表，则建立头部链表，并填入单词，然后设置尾部指针end
    if (headWF == NULL) {
        headWF = new WordsForgetten;
        write = headWF;
        write->words = wordsProd;
        //设置尾部
        endWF = headWF;
    }
    //如果已经建立，创建新表，并设置新的尾部指针
    else {
        //创建新表
        create = new WordsForgetten;
        //取现有尾部准备写入
        write = endWF;
        //链接
        write->next = create;
        //进入新表并填入单词
        write = write->next;
        write->words = wordsProd;
        //设置新尾部
        endWF = create;
    }


}
//##############遗忘表创建##############

//##############遗忘表读取##############
void TableUtils::readBuffeFromWFTable() {
    //读入头部
    WordsForgetten* read = headWF;
    //读取遗忘单词表，逻辑与单词表类似
    char choiceWF;
    //检索遗忘单词表
    while (read != NULL) {
        cout << "还记得 " << read->words << " 吗？" << endl;
        cin >> choiceWF;
        switch (choiceWF) {
            case 'y': {
                //将此单词从表中删除
                deleteSpecificWordsInWFTable(read);
                //读入新头部
                read = headWF;
                continue;
            }
            case 'n': {
                //将此单词降低优先级，即移动到链表最后方
                moveWordsInWFTable(read);
                read = headWF;
                continue;
            }
        }

        read = read->next;
    }

    //如果全记起来了
    if (headWF == NULL) {
        cout << "恭喜你！全部过关！";
        exit(0);
    }
    //如果没有，继续递归此函数读取，直到全部记起来为止（想结束多半只能Alt F4了）
    else {
        cout << "忘掉了" << numWordsForgetten <<" 个单词"<<endl;
        readBuffeFromWFTable();
    }

}
//##############遗忘表读取##############

//##############遗忘表单词删除##############
void TableUtils::deleteSpecificWordsInWFTable(WordsForgetten* wordRemember) {
    //如果涉及到表头部单词的删除操作,则改变表的头部指针
    if (wordRemember == headWF) {
        headWF = headWF->next;
        delete wordRemember;
        return ;
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
        return ;
    }
    //如果是中间单元
    else {
        find->next = wordRemember->next;
        delete wordRemember;
        return ;
    }

}
//##############遗忘表单词删除##############

void TableUtils::moveWordsInWFTable(WordsForgetten* wordForgetten) {
    //如果第一个就没记住，在这个单词不是该表唯一一个单词的前提下，需要改变遗忘单词表头部指针
    if (wordForgetten == headWF) {
        //如果此单词是该表唯一一个单词，则返回
        if (headWF->next == NULL) return;
        else {
            //改变头部链表单元为原来的第二个单元
            headWF = headWF->next;
            //使原来的头部链表链接到最后，变为尾部链表
            endWF->next = wordForgetten;
            wordForgetten->next = NULL;
            endWF = wordForgetten;
        }

        return;
    }

    //如果不是，则单词可能在尾部或中间，在尾部时不执行任何操作
    else {
        //如果在中间，则变为尾部单元
        //寻找该单词的上一单元
        WordsForgetten* find = headWF;
        while (find->next != wordForgetten) {
            find = find->next;
        }
        //使上一单元链接到该单词的下一单元
        find->next = wordForgetten->next;
        //改变尾部
        endWF->next = wordForgetten;
        wordForgetten->next = NULL;
        endWF = wordForgetten;

        return;
    }

}
//##############遗忘表单词移动##############

//##############析构##############
/*
所有操作进行完毕后，在对象声明周期结束前调用析构函数释放所有链表单元
因为没学exception，所以上方不停的存储head和headWF，以保证一旦程序错误结束，析构函数可以最大
限度析构所有链表，以减少内存中的垃圾
*/
TableUtils::~TableUtils() {
    //首先析构单词表
    Words* find = head;
    if (head != NULL) {
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
    }

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
/*-----------------单词表操作-----------------*/
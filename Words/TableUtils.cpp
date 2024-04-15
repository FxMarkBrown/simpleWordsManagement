#include <iostream>
#include "TableUtils.h"

using namespace std;

/*-----------------���ʱ����-----------------*/
//��д���캯����ʼ��˽�г�Ա
TableUtils::TableUtils() {
    wordCout = 0;
    numWordsForgetten = 0;
    head = NULL;
    headWF = NULL;
    endWF = NULL;
}


void TableUtils::getBufferToTable() {
    //����ͷ����
    head = new Words;
    //����д��ָ��
    Words* write = head;
    //������ָ��
    Words* create;
    string str;
    //����ÿһ�У���δ�����ļ�βEOF����һֱѭ������
    while (getline(file, str))
    {
        //���������˼�������
        wordCout++;
        //д�뵥��
        write->words = str;
        //������һ������
        create = new Words;
        //����
        write->next = create;
        //�ƶ�writeָ������һ����
        write = create;
    }
    cout << "�ܺã������� " << wordCout << " ������" << endl;
    file.close();


}
//##############��ȡ�ļ�����������##############

//##############���������ȡ##############
void TableUtils::readBufferFromTable() {
    //��ȡָ��
    Words* read = head;
    //����Words��
    char choice;
    while (read->next != NULL) {
        cout << read->words << "���Ƿ񻹼ǵ�? :";
        cin >> choice;
        switch (choice) {
            case 'y': {
                //��һ������ʼһ����ѭ��
                read = read->next;
                continue;
            }
            case 'n': {
                 //����,����ʼ��һ��ѭ��
                createWFTable(read->words);
                numWordsForgetten++;
                read = read->next;
                continue;
            }
        }
    }

    //��ʼ���WordsForgetten�Ƿ����
    if (headWF == NULL) {
        cout << "��ϲ�㣡ȫ�����أ�";
        exit(0);
    }
    else {
        cout << "������ " << numWordsForgetten << " ������"<<endl;
        readBuffeFromWFTable();
    }

}
//##############���������ȡ##############

//##############��������##############
void TableUtils::createWFTable(string wordsProd) {
    //����ָ��
    WordsForgetten* create;
    //д��ָ��
    WordsForgetten* write;
    //�����δ������������ͷ�����������뵥�ʣ�Ȼ������β��ָ��end
    if (headWF == NULL) {
        headWF = new WordsForgetten;
        write = headWF;
        write->words = wordsProd;
        //����β��
        endWF = headWF;
    }
    //����Ѿ������������±��������µ�β��ָ��
    else {
        //�����±�
        create = new WordsForgetten;
        //ȡ����β��׼��д��
        write = endWF;
        //����
        write->next = create;
        //�����±����뵥��
        write = write->next;
        write->words = wordsProd;
        //������β��
        endWF = create;
    }


}
//##############��������##############

//##############�������ȡ##############
void TableUtils::readBuffeFromWFTable() {
    //����ͷ��
    WordsForgetten* read = headWF;
    //��ȡ�������ʱ��߼��뵥�ʱ�����
    char choiceWF;
    //�����������ʱ�
    while (read != NULL) {
        cout << "���ǵ� " << read->words << " ��" << endl;
        cin >> choiceWF;
        switch (choiceWF) {
            case 'y': {
                //���˵��ʴӱ���ɾ��
                deleteSpecificWordsInWFTable(read);
                //������ͷ��
                read = headWF;
                continue;
            }
            case 'n': {
                //���˵��ʽ������ȼ������ƶ����������
                moveWordsInWFTable(read);
                read = headWF;
                continue;
            }
        }

        read = read->next;
    }

    //���ȫ��������
    if (headWF == NULL) {
        cout << "��ϲ�㣡ȫ�����أ�";
        exit(0);
    }
    //���û�У������ݹ�˺�����ȡ��ֱ��ȫ��������Ϊֹ����������ֻ��Alt F4�ˣ�
    else {
        cout << "������" << numWordsForgetten <<" ������"<<endl;
        readBuffeFromWFTable();
    }

}
//##############�������ȡ##############

//##############��������ɾ��##############
void TableUtils::deleteSpecificWordsInWFTable(WordsForgetten* wordRemember) {
    //����漰����ͷ�����ʵ�ɾ������,��ı���ͷ��ָ��
    if (wordRemember == headWF) {
        headWF = headWF->next;
        delete wordRemember;
        return ;
    }

    //����������еķ�ͷ����Ԫ����Ҫ�ж��Ƿ���β��
    //��Ϊ���ڻ���ѧ˫����������Ϊ���ҵ���һ��������ʱ�ȱ�����������
    
    //Ѱ����һ����Ԫ
    WordsForgetten* find = headWF;
    while (find->next != wordRemember) {
        find = find->next;
    }
    //������ɺ�find����WordRemember����һ��Ԫ
    //�����β��
    if (wordRemember->next == NULL) {
        find->next = NULL;
        delete wordRemember;
        return ;
    }
    //������м䵥Ԫ
    else {
        find->next = wordRemember->next;
        delete wordRemember;
        return ;
    }

}
//##############��������ɾ��##############

void TableUtils::moveWordsInWFTable(WordsForgetten* wordForgetten) {
    //�����һ����û��ס����������ʲ��Ǹñ�Ψһһ�����ʵ�ǰ���£���Ҫ�ı��������ʱ�ͷ��ָ��
    if (wordForgetten == headWF) {
        //����˵����Ǹñ�Ψһһ�����ʣ��򷵻�
        if (headWF->next == NULL) return;
        else {
            //�ı�ͷ������ԪΪԭ���ĵڶ�����Ԫ
            headWF = headWF->next;
            //ʹԭ����ͷ���������ӵ���󣬱�Ϊβ������
            endWF->next = wordForgetten;
            wordForgetten->next = NULL;
            endWF = wordForgetten;
        }

        return;
    }

    //������ǣ��򵥴ʿ�����β�����м䣬��β��ʱ��ִ���κβ���
    else {
        //������м䣬���Ϊβ����Ԫ
        //Ѱ�Ҹõ��ʵ���һ��Ԫ
        WordsForgetten* find = headWF;
        while (find->next != wordForgetten) {
            find = find->next;
        }
        //ʹ��һ��Ԫ���ӵ��õ��ʵ���һ��Ԫ
        find->next = wordForgetten->next;
        //�ı�β��
        endWF->next = wordForgetten;
        wordForgetten->next = NULL;
        endWF = wordForgetten;

        return;
    }

}
//##############���������ƶ�##############

//##############����##############
/*
���в���������Ϻ��ڶ����������ڽ���ǰ�������������ͷ���������Ԫ
��Ϊûѧexception�������Ϸ���ͣ�Ĵ洢head��headWF���Ա�֤һ�����������������������������
�޶��������������Լ����ڴ��е�����
*/
TableUtils::~TableUtils() {
    //�����������ʱ�
    Words* find = head;
    if (head != NULL) {
        while (head->next != NULL) {
            //�ҵ�β��
            while (find->next != NULL) {
                find = find->next;
            }
            //�ͷ�
            delete find;
        }
        //���ɾ��ͷ��
        delete head;
    }

    //�����������ʱ�
    if (headWF != NULL) {
        WordsForgetten* findWF = headWF;
        while (headWF != NULL) {
            //�ҵ�β��
            while (findWF->next != NULL) {
                findWF = findWF->next;
            }
            //�ͷ�
            delete findWF;
        }
        //ɾ��ͷ��
        delete headWF;
    }
}
/*-----------------���ʱ����-----------------*/
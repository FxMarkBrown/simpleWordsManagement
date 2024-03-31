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
}

//exception��ûѧ����ʱֱ�ӷ��ظ�true��װȫ����ȡ�ɹ���:)
bool TableUtils::loadFile(char* filename) {
    file.open(filename);
    return file.is_open();
}

bool TableUtils::getBufferToTable(Words* head) {
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

    //����˽�г�Աָ��
    TableUtils::head = head;

    return true;
}

//##���������ȡ
bool TableUtils::readBufferFromTable(Words* read, WordsForgetten* headWF) {
    //����������ʱ���ӵ���ʹ�õ�������������β��ָ�루���ô��ݣ�
    WordsForgetten* endOfWF;
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
                createWFTable(read->words, headWF, endOfWF);
                continue;
            }
        }
    }

    //��ʼ���WordsForgetten�Ƿ����
    if (headWF == NULL) {
        cout << "��ϲ�㣡ȫ�����أ�";
        //����˽�г�Աָ�룬�������������ͷ�����
        TableUtils::head = head;
        exit(0);
    }
    else {
        //����˽�е��ʱ�ָ��
        TableUtils::head = head;
        readBuffeFromWFTable(headWF);
    }

    return true;
}

bool TableUtils::createWFTable(string wordsProd, WordsForgetten* headWF, WordsForgetten* &end) {
    //����ָ��
    WordsForgetten* create;
    //д��ָ��
    WordsForgetten* write;
    //�����δ������������ͷ�����������뵥�ʣ�Ȼ������β��ָ��end
    if (headWF == NULL) {
        headWF = new WordsForgetten;
        write = headWF;
        write->words = wordsProd;
        //������һ��
        create = new WordsForgetten;
        //����
        write->next = create;
        //����β��
        end = create;
    }
    //����Ѿ������������β��ָ��end�������±�
    else {
        write = end;
        //���뵥��
        write->words = wordsProd;
        //�����±�
        create = new WordsForgetten;
        //����
        write->next = create;
        //������β��
        end = create;
    }

    //����˽�г�Աָ��
    TableUtils::headWF = headWF;

    return true;
}

bool TableUtils::readBuffeFromWFTable(WordsForgetten* read) {
    //�����ȡλ�õ�ͷ�����ٴζ�ȡʹ��
    WordsForgetten* headWF = read;
    //����˽�г�Աָ��
    TableUtils::headWF = headWF;
    //��ȡ�������ʱ��߼��뵥�ʱ�����
    char choiceWF;
    //������������������ֹ�����ݹ����������
    numWordsForgetten = 0;
    //�����������ʱ�
    while (read->next != NULL) {
        cout << "���ǵ� " << read->words << " ��" << endl;
        cin >> choiceWF;
        switch (choiceWF) {
            case 'y': {
                //���˵��ʴӱ���ɾ��,��Ϊ�����漰����һ�����ʣ��������ô��ݱ�ͷ��head
                deleteSpecificWordsInWFTable(headWF,read);
                continue;
            }
            case 'n': {
                //���˵���������ȼ������ƶ���������ǰ��
                moveWordsInWFTable(headWF,read);
                numWordsForgetten++;
                continue;
            }
        }
    }

    //���ȫ��������
    if (headWF == NULL) {
        cout << "��ϲ�㣡ȫ�����أ�";
        exit(0);
    }
    //���û�У������ݹ�˺�����ȡ��ֱ��ȫ��������Ϊֹ����������ֻ��Alt F4�ˣ�
    else {
        cout << "������" << numWordsForgetten++ <<" ������"<<endl;
        readBuffeFromWFTable(headWF);
    }

    //���Ÿ�exception
    return true;
}

bool TableUtils::deleteSpecificWordsInWFTable(WordsForgetten* &headWF, WordsForgetten* wordRemember) {
    //����˽�г�Աָ��
    TableUtils::headWF = headWF;
    //����漰����ͷ�����ʵ�ɾ������,��ͨ�����ô��ݸı���ͷ��ָ��
    if (wordRemember == headWF) {
        headWF = headWF->next;
        delete wordRemember;
        return true;
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
        return true;
    }
    //������м䵥Ԫ
    else {
        find->next = wordRemember->next;
        delete wordRemember;
        return true;
    }

    return true;
}

bool TableUtils::moveWordsInWFTable(WordsForgetten* &headWF,WordsForgetten* wordForgetten) {
    //����˽�г�Աָ��
    TableUtils::headWF = headWF;
    //�����һ�����ü�ס,��ִ���κβ���
    //������ǣ����ٷ����
    if (wordForgetten != headWF) {
        //�����ҵ���һ��Ԫ
        WordsForgetten* find = headWF;
        while (find->next != wordForgetten) {
            find = find->next;
        }

        //�����β��
        if (wordForgetten->next == NULL) {
            find->next = NULL;
            wordForgetten->next = headWF;
            headWF = wordForgetten;
            return true;
        }
        //������м䵥Ԫ
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
���в���������Ϻ��ڶ����������ڽ���ǰ�������������ͷ���������Ԫ
��Ϊûѧexception�������Ϸ���ͣ�Ĵ洢head��headWF���Ա�֤һ�����������������������������
�޶��������������Լ����ڴ��е�����
*/
TableUtils::~TableUtils() {
    //�����������ʱ�
    Words* find = head;
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

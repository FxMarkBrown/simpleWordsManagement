#include <iostream>
#include "TableUtils.h"

using namespace std;

/*-----------------���ʱ����-----------------*/
//��д���캯����ʼ��˽�г�Ա
TableUtils::TableUtils() {
    wordCout = 0;
    numWordsForgetten = 0;
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
        exit(0);
    }
    else readBuffeFromWFTable(headWF);

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

    return true;
}

bool TableUtils::readBuffeFromWFTable(WordsForgetten* read) {
    //�����ȡλ�õ�ͷ�����ٴζ�ȡʹ��
    WordsForgetten* head = read;
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
                deleteSpecificWordsInWFTable(head,read);
                continue;
            }
            case 'n': {
                //���˵���������ȼ������ƶ���������ǰ��
                moveWordsInWFTable(read);
                numWordsForgetten++;
                continue;
            }
        }
    }

    //���ȫ��������
    if (head == NULL) {
        cout << "��ϲ�㣡ȫ�����أ�";
        exit(0);
    }
    //���û�У������ݹ�˺�����ȡ��ֱ��ȫ��������Ϊֹ����������ֻ��Alt F4�ˣ�
    else {
        cout << "������" << numWordsForgetten++ << endl;
        readBuffeFromWFTable(head);
    }

    //���Ÿ�exception
    return true;
}

bool TableUtils::deleteSpecificWordsInWFTable(WordsForgetten* &headWF, WordsForgetten* wordRemember) {
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
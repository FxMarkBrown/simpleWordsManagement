#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdio>
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


void TableUtils::getBuffertoTable() {
    //����ͷ����
    head = new Words;
    //����д��ָ��
    Words* write = head;
    //������ָ��
    Words* create;
    switch (mode) {
        case 'N': {
            string str;
            //����ÿһ�У���δ�����ļ�βEOF����һֱѭ������
            while (getline(inputfile, str))
            {
                //���������˼�������
                wordCout++;
                //д�뵥��
                write->wordA = str;
                //������һ������
                create = new Words;
                //����
                write->next = create;
                //�ƶ�writeָ������һ����
                write = create;
            }
            cout << "��ǰΪ��ͨģʽ�������� " << wordCout << " ������" << endl;
            break;
        }
        case 'D': {
            string line,strA,strB;
            //����ÿһ�У���δ�����ļ�βEOF����һֱѭ������
            while (getline(inputfile, line))
            {
                //��ʼ���ַ�����ȡ�������ָ���@��ȡÿһ�е���������
                istringstream iss(line);
                if (!(getline(iss, strA, '@') && getline(iss, strB, '|'))) {
                    // �����ʽ����ȷ�����ӡ������������  
                    cerr << "��ʽ�������: " << line << endl;
                    continue;
                }
                //���������˼�������
                wordCout++;
                //д�뵥��
                write->wordA = strA;
                write->wordB = strB;
                //������һ������
                create = new Words;
                //����
                write->next = create;
                //�ƶ�writeָ������һ����
                write = create;
            }
            cout << "��ǰΪ��дģʽ�������� " << wordCout << " ������" << endl;
            break;
        }

    }
    inputfile.close();


}
//##############��ȡ�ļ�����������##############

//##############���������ȡ##############

void TableUtils::readBufferfromTable() {
    //��ȡָ��
    Words* read = head;
    //�ж�ģʽ
    switch (mode) {
    case 'N':
        //����Words��
        char choice;
        while (read->next != NULL) {
            cout << read->wordA << "���Ƿ񻹼ǵ�? :";
            cin >> choice;
            switch (choice) {
            case 'y':
                //��һ������ʼһ����ѭ��
                read = read->next;
                continue;
            case 'n':
                //����,����ʼ��һ��ѭ��
                createWFTable(read->wordA);
                numWordsForgetten++;
                read = read->next;
                continue;
            }
        }
        break;
    case 'D':
        //����Words��
        string answer;
        while (read->next != NULL) {
            cout << read->wordA << "���Ƿ񻹼ǵ�? :";
            getline(cin, answer);
            //�ش���ȷ����һ��ѭ��
            if (answer == read->wordB) {
                read = read->next;
                continue;
            }
            //����
            else {
                //����,����ʼ��һ��ѭ��
                createWFTable(read->wordA, read->wordB);
                numWordsForgetten++;
                read = read->next;
                continue;
            }
        }
        break;
    }
    //��ʼ���WordsForgetten�Ƿ����
    if (headWF == NULL) {
        cout << "��ϲ�㣡ȫ�����أ�"<<endl;
    }
    else {
        cout << "������ " << numWordsForgetten << " ������"<<endl;
        cout << "��ѡ�����ڸ�ϰ��1������һ�θ�ϰ��2) : ";
        int choiceReview;
        cin >> choiceReview;
        switch (choiceReview) {
        case 1:
            readBuffefromWFTable();
            break;
        case 2:
            //�����������ʵ��ļ�
            saveBufferWFtoFile();
            exit(0);
            break;
        }
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
        write->wordforgettenA = wordsProd;
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
        write->wordforgettenA = wordsProd;
        //������β��
        endWF = create;
    }


}

void TableUtils::createWFTable(string wordsProdA, string wordsProdB) {
    //����ָ��
    WordsForgetten* create;
    //д��ָ��
    WordsForgetten* write;
    //�����δ������������ͷ�����������뵥�ʣ�Ȼ������β��ָ��end
    if (headWF == NULL) {
        headWF = new WordsForgetten;
        write = headWF;
        write->wordforgettenA = wordsProdA;
        write->wordforgettenB = wordsProdB;
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
        write->wordforgettenA = wordsProdA;
        write->wordforgettenB = wordsProdB;
        //������β��
        endWF = create;
    }


}
//##############��������##############

//##############�������ȡ##############
void TableUtils::readBuffefromWFTable() {
    //����ͷ��
    WordsForgetten* read = headWF;
    //�ж�ģʽ
    switch (mode) {
        case 'N':
        //��ȡ�������ʱ��߼��뵥�ʱ�����
        char choiceWF;
        //�����������ʱ�
        while (read != NULL) {
                cout << "���ǵ� " << read->wordforgettenA << " ��" << endl;
                cin >> choiceWF;
                switch (choiceWF) {
                case 'y': 
                    //���˵��ʴӱ���ɾ��
                    deleteSpecificWordsinWFTable(read);
                    //������ͷ��
                    read = headWF;
                    continue;
                case 'n': 
                    //���˵��ʽ������ȼ������ƶ����������
                    moveWordsinWFTable(read);
                    read = headWF;
                    continue;
                }
                read = read->next;
            }
        break;
        case 'D': 
            //��ȡ�������ʱ��߼��뵥�ʱ�����
            string answerWF;
            //�����������ʱ�
            while (read != NULL) {
                cout << "���ǵ� " << read->wordforgettenA << " ��" << endl;
                getline(cin,answerWF);
                if (answerWF == read->wordforgettenB) {
                    //���˵��ʴӱ���ɾ��
                    deleteSpecificWordsinWFTable(read);
                    //������ͷ��
                    read = headWF;
                    continue;
                }
                else {
                    //���˵��ʽ������ȼ������ƶ����������
                    moveWordsinWFTable(read);
                    read = headWF;
                    continue;
                }
                read = read->next;
            }
            break;
    }

    //���ȫ��������
    if (headWF == NULL) {
        cout << "��ϲ�㣡ȫ�����أ�"<<endl;
    }
    //���û��
    else {
        cout << "������" << numWordsForgetten <<" ������"<<endl;
        cout << "��ѡ�񣺼�����ϰ��1������һ�θ�ϰ��2) : ";
        int choiceReviewWF;
        cin >> choiceReviewWF;
        switch (choiceReviewWF) {
        case 1:
            //�����ݹ�˺�����ȡ��ֱ��ȫ��������Ϊֹ
            readBuffefromWFTable();
            break;
        case 2:
            //�����������ʵ��ļ�
            //����Ѿ������ļ�������ɾ�����ļ�
            if(hasFileWF()){
                deleteFileWF();
                saveBufferWFtoFile();
                cout << "���μ����ϣ������˳�" << endl;
                exit(0);
            }
            else {
                saveBufferWFtoFile();
                cout << "���μ����ϣ������˳�" << endl;
                exit(0);
            }
            break;
        }
    }

}
//##############�������ȡ##############

//##############��������ɾ��##############
void TableUtils::deleteSpecificWordsinWFTable(WordsForgetten* wordRemember) {
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

void TableUtils::moveWordsinWFTable(WordsForgetten* wordForgetten) {
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

//################�������ʳ־û�����################

//##############�������ʱ���##############
void TableUtils::saveBufferWFtoFile() {
    ofstream outputWFFile("wordsWF.lock");
    if (outputWFFile.is_open()) {
        //��ʼ�����������ʱ�����д���ļ�
        WordsForgetten* read = headWF;
        while (read != NULL) {
            if (mode == 'N') {
                outputWFFile << read->wordforgettenA;
           }
            else if (mode == 'D') {
                outputWFFile << read->wordforgettenA << '@' << read->wordforgettenB << '|' << endl;
            }

            read = read->next;
        }

        outputWFFile.close();
    }
}
//##############�������ʱ���##############

//##############�������ʶ�ȡ##############
void TableUtils::getBuffertoWFTable() {
    switch (mode) {
    case 'N': {
        string str;
        //����ÿһ�У���δ�����ļ�βEOF����һֱѭ������
        while (getline(inputfile, str)){
            createWFTable(str);
            //���������˼�������
            wordCout++;
        }
        cout << "��ǰΪ��ͨģʽ�������� " << wordCout << " ������" << endl;
        break;
    }
    case 'D': {
        string line, strA, strB;
        //����ÿһ�У���δ�����ļ�βEOF����һֱѭ������
        while (getline(inputfile, line))
        {
            //��ʼ���ַ�����ȡ�������ָ���@��ȡÿһ�е���������
            istringstream iss(line);
            if (!(getline(iss, strA, '@') && getline(iss, strB, '|'))) {
                // �����ʽ����ȷ�����ӡ������������  
                cerr << "��ʽ�������: " << line << endl;
                continue;
            }
            createWFTable(strA, strB);
            //���������˼�������
            wordCout++;
        }
        cout << "��ǰΪ��дģʽ�������� " << wordCout << " ������" << endl;
        break;
    }

    }
    inputfile.close();

}
//##############�������ʶ�ȡ##############

//############�����������ļ�ɾ��#############
void TableUtils::deleteFileWF() {
    const char* ptFileWF = "wordsWF.lock";
    if (remove(ptFileWF) != 0) {
        cerr << "�Ƴ������������ļ�ʧ�ܣ��볢���ֶ�ɾ��wordsWF.lock�ļ�";
    }
}
//############�����������ļ�ɾ��#############

//############�����������ļ����#############
bool TableUtils::hasFileWF() {
    ifstream testFileWF("wordsWF.lock");
    return testFileWF.is_open();
}

//################�������ʳ־û�����################

//##############����##############
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
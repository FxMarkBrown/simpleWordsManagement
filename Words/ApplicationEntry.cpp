#include <iostream>
#include "ApplicationEntry.h"
#include "TableUtils.h"

using namespace std;

//##############ѡ��ģʽ##############
void ApplicationEntry::chooseMode() {
    //ѡ��ģʽ
    cout << "ѡ���鵥�ʵ�ģʽ N����ͨ����D����д��: ";
    char key;
    cin >> key;
    cin.get();
    switch (key) {
    case 'N': {
        //����ģʽ
        tu->mode = 'N';
        break;
    }
    case 'D': {
        tu->mode = 'D';
        break;
    }
    }
}

//##############�����������##############
void ApplicationEntry::startApplication() {
    //������������
    tu = new TableUtils;
    //*���ó�Աtu��˽�г�Ա����ִ�в���
    //����Ƿ����ϴ������������������ļ�wordsWF.lock
    if (tu->hasFileWF()) {
        //ѡ��ģʽ
        chooseMode();
        cout << "��⵽����һ��û�и�ϰ����������" << endl;
        //�������ļ�����ȡ����
        loadWFFile();
        //���ö�ȡ�������ʱ����ĺ���
        tu->readBuffefromWFTable();
        //ɾ�����ļ�
        tu->deleteFileWF();

        cout << "�ϴ������ĵ��ʼ����ϣ����������ѡ���Ƿ����µĵ��ʣ�N�����˳���Y��: ";
        char choiceContinue;
        cin >> choiceContinue;
        if (choiceContinue == 'Y') {
            exit(0);
        }
        else {
            //����tu����һ���ٴ����µ�tu������������������ʱ��еĵ��ʣ��������¼��ʱ����
            delete tu;
            tu = new TableUtils;
        }
    }

    chooseMode();
    loadFile();
    tu->readBufferfromTable();

    cout << "���ʼ����ϣ������˳�" << endl;
}

//##############��ȡ�ļ�����������##############
//exception��ûѧ����ʱֱ�ӷ��ظ�true��װȫ����ȡ�ɹ���:)
void ApplicationEntry::loadFile() {
    //****���ع���������ʱ�֧�֣��ɶ�����ɵ�����)****
    
    //���ļ�
    string fn;
    cout << "�������ļ���:";
    cin >> fn;
    cin.get();

    tu->inputfile.open(fn);
    if (!tu->inputfile.is_open()) {
        cout << "�ļ��򿪴���" << endl;
        exit(0);
    }

    //��������
    tu->getBuffertoTable();
}

//##############�����������ʱ��ļ�������������������##############
void ApplicationEntry::loadWFFile() {
    tu->inputfile.open("wordsWF.lock");
    if (!tu->inputfile.is_open()) {
        cout << "�ļ��򿪴���" << endl;
        exit(0);
    }

    //����������������
    tu->getBuffertoWFTable();
}

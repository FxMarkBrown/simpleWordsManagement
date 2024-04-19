#include <iostream>
#include "ApplicationEntry.h"
#include "TableUtils.h"

using namespace std;

//##############�����������##############
void ApplicationEntry::startApplication() {
    //*���ó�Աtu��˽�г�Ա����ִ�в���
    //ѡ��ģʽ
    cout << "ѡ���鵥�ʵ�ģʽ N����ͨ����D����д��: ";
    char key;
    cin >> key;
    switch (key) {
        case 'N': {
            //����ģʽ
            tu.mode = 'N';
            //�����ļ�
            loadFile();
            tu.readBufferFromTable();
            break;
        }
        case 'D': {
            tu.mode = 'D';
            loadFile();
            tu.readBufferFromTable();
            break;
        }
    }
}

//##############��ȡ�ļ�����������##############
//exception��ûѧ����ʱֱ�ӷ��ظ�true��װȫ����ȡ�ɹ���:)
void ApplicationEntry::loadFile() {
    //****���ع���������ʱ�֧�֣��ɶ�����ɵ�����)****
    
    //���ļ�
    char fn[20];
    cout << "�������ļ���:";
    cin >> fn;
    char* fn_pt = fn;

    tu.file.open(fn_pt);
    if (!tu.file.is_open()) {
        cout << "�ļ��򿪴���" << endl;
        exit(0);
    }

    //��������
    tu.getBufferToTable();
}

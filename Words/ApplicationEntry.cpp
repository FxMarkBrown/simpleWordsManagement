#include <iostream>
#include "ApplicationEntry.h"
#include "TableUtils.h"

using namespace std;

//##############�����������##############
void ApplicationEntry::startApplication() {
    //*���ó�Աtu��˽�г�Ա����ִ�в���
    //�����ļ�
    loadFile();
    tu.readBufferFromTable();
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

#pragma once
#include <string>
#include <fstream>
using namespace std;

//�����洢���ʵ�����
struct Words {
    string words = "NONE";
    struct Words* next = NULL;
};

//�������ʱ�
struct WordsForgetten {
    string words = "NONE";
    struct WordsForgetten* next = NULL;
};

//������
class TableUtils {
private:
    //�ļ��������
    ifstream file;
    //�ܶ��뵥������
    int wordCout;
    //������������
    int numWordsForgetten;
    //���ʱ�ָ���Ա����������������ͷ�����ʹ��
    Words* head;
    WordsForgetten* headWF;
    //�������ʱ�β��ָ�룬��������������Ԫ/���͵�Ԫ���ȼ�ʱ����
    WordsForgetten* endWF;

    //�����ຯ��
    //д��������ȡ������ʾ����
    void getBufferToTable(); //���
    void readBufferFromTable(); //���
    //�������ʱ�������ȡ���ƶ���ɾ������
    void createWFTable(string wordsProd); //���
    void readBuffeFromWFTable(); //���
    void moveWordsInWFTable(WordsForgetten* wordForgetten); //���
    void deleteSpecificWordsInWFTable(WordsForgetten* wordRemember); //���

    //��Ԫ����������
    friend class ApplicationEntry;
public:
    //���캯���Լ���������
    TableUtils();
    ~TableUtils();
};
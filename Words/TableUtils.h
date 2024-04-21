#pragma once
#include <string>
#include <fstream>
using namespace std;


//��ͨģʽ��ֻʹ��A����дģʽ��ʹ��A��B������B�����
//�����洢���ʵ�����
struct Words {
    string wordA = "NONE";
    string wordB = "NONE";
    struct Words* next = NULL;
};

//�������ʱ�
struct WordsForgetten {
    string wordforgettenA = "NONE";
    string wordforgettenB = "NONE";
    struct WordsForgetten* next = NULL;
};

//������
class TableUtils {
private:
    //�ļ��������
    ifstream inputfile;
    //�����ģʽ��N����ͨģʽ����D����дģʽ��
    char mode;
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
    

    //д�뵥��������ȡ������ʾ����
    void getBuffertoTable(); //���
    void readBufferfromTable(); //���

    //��ʱ���������ʱ�������ȡ���ƶ���ɾ������
    //������ͨ����дģʽ�µ�������������
    void createWFTable(string wordsProd); //���
    void createWFTable(string wordsProdA, string wordsProdB); //���
    void readBuffefromWFTable(); //���
    void moveWordsinWFTable(WordsForgetten* wordForgetten); //���
    void deleteSpecificWordsinWFTable(WordsForgetten* wordRemember); //���
    void showAllAnswersinWFTable();

    //�������ʵĳ־û�����
    //�����������ʱ�ĵ��ʵ��ļ�����ȡ�������ʵ��ļ�
    void saveBufferWFtoFile(); //���
    void getBuffertoWFTable(); //���
    void deleteFileWF(); //���
    //����������������ļ�
    bool hasFileWF(); //���

    //��Ԫ����������
    friend class ApplicationEntry;
public:
    //���캯���Լ���������
    TableUtils();
    ~TableUtils();
};
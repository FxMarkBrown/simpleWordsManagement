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

    //�����ຯ��
    //д��������ȡ������ʾ����
    bool getBufferToTable(Words* head); //���
    bool readBufferFromTable(Words* read, WordsForgetten* headWF); //���
    //�������ʱ�������ȡ���ƶ���ɾ������
    bool createWFTable(string wordsProd, WordsForgetten* headWF, WordsForgetten*& end); //���
    bool readBuffeFromWFTable(WordsForgetten* read); //���
    bool moveWordsInWFTable(WordsForgetten*& headWF, WordsForgetten* wordForgetten); //���
    bool deleteSpecificWordsInWFTable(WordsForgetten*& headWF, WordsForgetten* wordRemember); //���

    //��Ԫ����������
    friend class ApplicationEntry;
public:
    //���캯���Լ���������
    TableUtils();
    ~TableUtils();
};
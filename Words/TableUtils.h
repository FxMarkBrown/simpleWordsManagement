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
public:
    //���캯��
    TableUtils();

    //���ʱ������ļ���д����������ȡ��������ʾ����
    bool loadFile(char* filename); //���
    bool getBufferToTable(Words* head); //���
    bool readBufferFromTable(Words* read, WordsForgetten* headWF); //���
    //�������ʱ���������ȡ���ƶ���ɾ������
    bool createWFTable(string wordsProd, WordsForgetten* headWF, WordsForgetten* &end); //���
    bool readBuffeFromWFTable(WordsForgetten* read);
    bool moveWordsInWFTable(WordsForgetten* wordsForgetten);
    bool deleteSpecificWordsInWFTable(WordsForgetten* worldRemember);
};
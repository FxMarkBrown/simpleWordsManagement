#include "TableUtils.h"
using namespace std;

class ApplicationEntry {
private:
	//��������
	TableUtils* tu;

	//ѡ��ģʽ
	void chooseMode();

	//���뵥�ʱ�/�������ʱ��ļ�
	void loadFile(); //���
	void loadWFFile(); //���

public:
	//���Ƴ���ʼ
	void startApplication();
};
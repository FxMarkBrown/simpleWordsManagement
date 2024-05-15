#include "TableUtils.h"
using namespace std;

class ApplicationEntry {
private:
	//表管理对象
	TableUtils* tu;

	//选择模式
	void chooseMode();
	//选择单词表答案对照
	void chooseReference();

	//读入单词表/遗忘单词表文件
	void loadFile(); //完成
	void loadWFFile(); //完成

public:
	//控制程序开始
	void startApplication();
};
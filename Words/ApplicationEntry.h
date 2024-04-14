#include "TableUtils.h"
using namespace std;

class ApplicationEntry {
private:
	//表管理对象
	TableUtils tu;
public:
	//控制程序开始
	void startApplication();
	//单词表读入文件
	void loadFile(); //完成
};
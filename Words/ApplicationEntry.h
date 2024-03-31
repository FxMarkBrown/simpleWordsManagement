using namespace std;

class ApplicationEntry {
private:
	//表管理对象
	TableUtils tu;
public:
	//控制程序开始
	void startApplication();
	//单词表读入文件
	bool loadFile(); //完成
};
#pragma once
#include<fstream>
#include<vector>
class SaveData {
public:
	SaveData(const char* _fileName);
	~SaveData();
	int Data(int _key) { return datas[_key]; };
	void SetData(int _key, int _num) { 
		datas[_key] = _num; 
	};
private:
	const char* fileName;
	std::vector<int> datas;
	std::fstream* fp;
};
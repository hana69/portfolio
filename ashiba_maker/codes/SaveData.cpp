#include"SaveData.h"


SaveData::SaveData(const char* _fileName) 
	:fp(new std::fstream(_fileName , std::ios::out)),
	fileName(_fileName)
{
	/*while (!fp->eof()) {
		int n;
		*fp >> n;
		datas.push_back(n);
	}

	fp->close();*/
	datas.push_back(5);
	datas.push_back(6);
	datas.push_back(7);
}

SaveData::~SaveData() {
	
	fp = new std::fstream(fileName, std::ios::in);
	for (int i = 0; i < datas.size();i++) {
		*fp << 199 << std::endl;
	}
	//fp->close();
	delete fp;
}




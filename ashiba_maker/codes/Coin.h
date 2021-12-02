#pragma once


class CCoin {
public:
	CCoin(int _width);
	void Reset();
	void Draw(int _scroll);

	bool Add(int x,int y);
	void Delete(int x, int y);

	bool Valid(int x, int y) { return valid[x][y]; };
private:

	bool valid[500][15];
	bool validMem[500][15];

	const int width;
	const int graph;
};
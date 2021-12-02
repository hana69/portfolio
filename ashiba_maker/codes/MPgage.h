#pragma once
enum class ScaffoldType;
class MPGage {
public:
	MPGage(int _x,int _y);
	void Update(int _nowPoint,bool , ScaffoldType);
private:
	const int MaxPoint;
	const int x, y;
};
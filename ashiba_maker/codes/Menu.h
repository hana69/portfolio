#pragma once
#include<vector>

class ClickObj;

class Menu{
public:
	Menu(int _x,int _y,int _backGraph);
	~Menu();
	virtual void Update();
protected:
	void Draw();
	std::vector<ClickObj*> texts;
	int x, y;
	int backGraph;
};

class Pause :public Menu {
public:
	Pause();
	bool Selected();
	enum class Texts {
		RETURN_TO_START,
		RETURN_TO_TITLE,
		RESUME,
		MAX
	} SelectedText() { return selectedText; };
private:
	Texts selectedText;
};


class GameOverMenu: public Menu{
public:
	GameOverMenu();
	bool Selected();
	enum class Texts {
		RETURN_TO_START,
		RETURN_TO_TITLE,
		MAX
	} SelectedText() { return selectedText; };
private:
	Texts selectedText;
};

class GameClearMenu:public Menu {
public:
	GameClearMenu(int _stageNum);
	void Update(int _finalStageNum);
	bool Selected();
	enum class Texts {
		RETURN_TO_TITLE,
		GO_TO_NEXT_STAGE,
		MAX
	}SelectedText() { return selectedText; };
private:
	Texts selectedText;
	const int stageNum;
};
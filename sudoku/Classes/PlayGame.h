#ifndef __PLAYGAME_H__
#define __PLAYGAME_H__

#include "stdafx.h"
#include "Environment.h"
#include "Level.h"


class PlayGame : public Scene {
private:
	DrawNode* dn;
	string sudoku[9][9];

	int num[9] = {1,2,3,4,5,6,7,8,9};
	int rnum[3][3];
	int random[9][9];

	int yIndex = 0;
	int xIndex = 0;

	Button* target;
	
	bool click = false;
public:
	static Scene* createScene(int level);

	static PlayGame* create(int level);
	virtual bool init(int level);
	
	void createLevel(int level);
	void drawLayout();

	
	bool checkSudoku();
	bool check(int x, int y, const string& value);

	void sudokuButton(const Vec2& pos, int tag, int level);
	void buttonCreate(const string& number, const Vec2& pos);
	void finishButton(const string& text, const Vec2& pos);
	void replayButton(const string& text, const Vec2& pos);
	
	void firstRandomNumber();
	void randomNumberWidth();
	void randomNumberHigth(int x, int y);
	void copyIntToString(int count);

	bool checkInt(int x, int y, int value);

	void sudokuSuccess();
	void sudokuFail();

};
#endif // !__PLAYGAME_H__

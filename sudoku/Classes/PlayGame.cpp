#include "stdafx.h"
#include "PlayGame.h"

Scene* PlayGame::createScene(int level) {
	return PlayGame::create(level);
}
PlayGame* PlayGame::create(int level){
	auto ret = new PlayGame();
	if (ret && ret->init(level)) ret->autorelease();
	else CC_SAFE_DELETE(ret);
	return ret;
}

bool PlayGame::init(int level) {
	if(!Scene::init()) return false;

	firstRandomNumber();
	copyIntToString(level);

	drawLayout();

	finishButton("Finish", Vec2(CENTER.x + 150, CENTER.y + 200));
	replayButton("Replay", Vec2(CENTER.x + 350, CENTER.y + 200));

	for (int i = 1; i <= 3; i++) {
		Vec2 pos = Vec2(CENTER.x + 100 + (100 * i), CENTER.y - 50);
		string num = to_string(i);
		buttonCreate(num, pos);
	}
	for (int i = 4; i <= 6; i++) {
		Vec2 pos = Vec2(CENTER.x + 100 + (100 * (i-3)), CENTER.y - 150);
		string num = to_string(i);
		buttonCreate(num, pos);
	}
	for (int i = 7; i <= 9; i++) {
		Vec2 pos = Vec2(CENTER.x + 100 + (100* (i-6)), CENTER.y - 250);
		string num = to_string(i);
		buttonCreate(num, pos);
	}

	auto keybd = EventListenerKeyboard::create();
	keybd->onKeyPressed = [=](EventKeyboard::KeyCode c, Event* e)->void {
		
	};
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(keybd, this);
	

	return true;
}

void PlayGame::drawLayout(){
	addChild(dn = DrawNode::create());
	//dn->drawRect(Vec2(50, 50), Vec2(700, 700), Color4F::GREEN);
	Color4F color1 = Color4F::MAGENTA;
	Color4F color2 = Color4F::WHITE;
	
	for (int i = 0; i <= 9; i++) {

		if (i % 3 == 0) {
			dn->drawLine(Vec2(70 * (i + 1), 70), Vec2(70 * (i + 1), 700), color1);
			dn->drawLine(Vec2(70, 70 * (i + 1)), Vec2(700, 70 * (i + 1)), color1);
		}
		else {
			dn->drawLine(Vec2(70 * (i + 1), 70), Vec2(70 * (i + 1), 700), color2);
			dn->drawLine(Vec2(70, 70 * (i + 1)), Vec2(700, 70 * (i + 1)), color2);
		}
	}
	dn->setLineWidth(5);

	int tag = 0;
	for (int i = 1; i <= 9; i++) {
		for (int k = 1; k <= 9; k++) {
			sudokuButton(Vec2(70 * k, 70 * i), tag, 0);
			tag++;
		}
	}
}

void PlayGame::createLevel(int level){
	
	switch (level) {
	case 1:

		break;
	case 2:

		break;
	case 3:

		break;
	}
}

void PlayGame::finishButton(const string& text, const Vec2& pos) {
	Button* btn = Button::create(DEFULT_UI);
	btn->setAnchorPoint(Vec2(0, 0));
	btn->setPosition(pos);
	btn->setTitleText(text);
	btn->setTitleFontSize(30.0f);
	btn->setTitleColor(Color3B::BLACK);
	btn->setScale9Enabled(true);
	btn->setScaleX(1.5);
	addChild(btn);

	btn->addClickEventListener([=](Ref*)->void {
		// 완료하면 스도쿠 검사 하고 성공 실패
		if (checkSudoku()) {
			sudokuSuccess();
		}
		else {
			sudokuFail();
		}
	});
}


void PlayGame::replayButton(const string& text, const Vec2& pos) {
	Button* btn = Button::create(DEFULT_UI);
	btn->setAnchorPoint(Vec2(0, 0));
	btn->setPosition(pos);
	btn->setTitleText(text);
	btn->setTitleFontSize(30.0f);
	btn->setTitleColor(Color3B::BLACK);
	btn->setScale9Enabled(true);
	btn->setScaleX(1.5);
	addChild(btn);

	btn->addClickEventListener([=](Ref*)->void {
		//다시 새로운게임을 만들거나 난이도조절로 돌아가면됨
		Director::getInstance()->replaceScene(Level::create());
	});
}

void PlayGame::sudokuSuccess() {
	DrawNode* dn = DrawNode::create();
	addChild(dn);
	dn->drawSolidRect(CENTER - Vec2(200, 200), CENTER + Vec2(200, 200), Color4F::WHITE);
}

void PlayGame::sudokuFail() {
	DrawNode* dn = DrawNode::create();
	addChild(dn);
	dn->drawSolidRect(CENTER - Vec2(200, 200), CENTER + Vec2(200, 200), Color4F::RED);
	
}

void PlayGame::firstRandomNumber() {
	srand(time(0));

	for (int i = 0; i < 9; i++) {
		int r = rand() % 8 + 1;
		int temp = num[i];
		num[i] = num[r];
		num[r] = temp;
	}

	int index = 0;
	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 3; k++) {
			random[i][k] = num[index];
			index++;
		}
	}

	randomNumberWidth();
	randomNumberHigth(0, 0);
	randomNumberHigth(0, 3);
	randomNumberHigth(3, 0);
	randomNumberHigth(3, 3);
	randomNumberHigth(6, 0);
	randomNumberHigth(6, 3);
}

void PlayGame::randomNumberWidth() {
	int target = 0;
	for (int i = 0; i < 3; i++) {
		for (int k = 3; k < 6; k++) {
			if (target == i) target++;
			if (target > 2) target = 0;
			random[i][k] = random[target][k - 3];
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int k = 6; k < 9; k++) {
			if (target == i) target++;
			if (target > 2) target = 0;
			random[i][k] = random[target][k - 3];
		}
	}
}

void PlayGame::randomNumberHigth(int x, int y) {
	int target = 0;
	for (int i = x; i < x + 3; i++) {
		for (int k = y; k < y + 3; k++) {
			if (target + x == i) target++;
			if (target > 2) target = 0;
			random[k + 3][i] = random[k][target+x];
		}
	}
}

void PlayGame::copyIntToString(int count) {
	srand(time(0));
	
	for (int i = 0; i < 9; i++) {
		for (int k = 0; k < 9; k++) {
			sudoku[i][k].append(to_string(random[i][k]));
		}
	}

	for (int i = 0; i < count; i++) {
		int x = rand() % 9;
		int y = rand() % 9;
		sudoku[x][y] = ' ';
	}

}

bool PlayGame::checkInt(int x, int y, int value){
	for (int i = 0; i < 9; i++) {
		if (random[x][i] == value && i != y) {
			return false;
		}
		if (random[i][y] == value && i != x) {
			return false;
		}
	}
	// 3x3 부분 체크
	for (int i = (x / 3) * 3; i < (x / 3) * 3 + 3; i++) {
		for (int k = (y / 3) * 3; k < (y / 3) * 3 + 3; k++) {
			if (i == x && k == y) {
				continue;
			}
			else if (random[i][k] == value) {
				return false;
			}
		}
	}

	return true;
}

// 스도쿠 판
void PlayGame::sudokuButton(const Vec2& pos, int tag, int level) {
	Button* btn = Button::create(DEFULT_UI);
	btn->setAnchorPoint(Vec2(0, 0));
	btn->setPosition(pos);
	btn->setColor(Color3B(153, 204, 153));
	btn->setScale(0.7);
	btn->setTag(tag);

	if (xIndex >= 9) {
		xIndex = 0;
		yIndex++;
	}
	btn->setTitleText(sudoku[yIndex][xIndex]);
	btn->setTitleFontSize(50.0f);
	btn->setTitleColor(Color3B::BLUE);

	addChild(btn);

	xIndex++;

	// 누르면 해당 위치 퍼즐 색 변경
	btn->addClickEventListener([=](Ref*)->void {
		click = true;
		if (target == nullptr) {
			target = btn;
			target->setColor(Color3B(102, 153, 102));
		}
		else {
			target->setColor(Color3B(153, 204, 153));
			target = btn;
			target->setColor(Color3B(102, 153, 102));
		}
	});
}


// 번호 누르는곳
void PlayGame::buttonCreate(const string& number, const Vec2& pos) {
	
	Button* btn = Button::create(DEFULT_UI);
	btn->setScale9Enabled(true);
	btn->setTitleText(number);
	btn->setTitleColor(Color3B::BLACK);
	btn->setTitleFontSize(50.0f);
	btn->setPosition(pos);
	addChild(btn);
	
	// 번호를 누르면 그 번호의 Title을 해당 스도쿠퍼즐에 입력해줌
	btn->addClickEventListener([=](Ref*)->void {
		if (target == nullptr) return;
		auto num = btn->getTitleText();
		target->setTitleText(num);
		target->setTitleFontSize(50.0f);
		target->setTitleColor(Color3B::BLACK);
		int tag = target->getTag(); // tag는 0부터 시작
		sudoku[tag / 9][tag % 9] = num;
	});
}

bool PlayGame::checkSudoku() {
	for (int i = 0; i < 9; i++) {
		for (int k = 0; k < 9; k++) {
			// 체크하여 중복된다면 false
			if (!check(i, k, sudoku[i][k])) {
				return false;
			}
		}
	}
	// 모두 마치고 나오면 성공이니까 true
	return true;
}

bool PlayGame::check(int x, int y, const string& value) {
	// x축 y축 9칸 체크
	for (int i = 0; i < 9; i++) {
		if (sudoku[x][i] == value && i != y) {
			return false;
		}
		if (sudoku[i][y] == value && i != x) {
			return false;
		}
	}
	// 3x3 부분 체크
	for (int i = (x / 3) * 3; i < (x / 3) * 3 + 3; i++) {
		for (int k = (y / 3) * 3; k < (y / 3) * 3 + 3; k++) {
			if (i == x && k == y) {
				continue;
			}
			else if (sudoku[i][k] == value) {
				return false;
			}
		}
	}

	return true;
}
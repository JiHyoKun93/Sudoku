#include "stdafx.h"
#include "MainScene.h"

MainScene* MainScene::create() {
	auto ret = new MainScene();
	if (ret && ret->init())ret->autorelease();
	else CC_SAFE_DELETE(ret);
	return ret;
}

bool MainScene::init() {
	if (!Scene::init()) return false;

	Label* lb = Label::createWithTTF("SUDOKU GAME", DEFULT_FONT, 50.0f);
	lb->setPosition(Vec2(CENTER.x, CENTER.y + 150));
	lb->setColor(Color3B::MAGENTA);
	addChild(lb);
	{
		Button* btn = Button::create(DEFULT_UI);
		btn->setPosition(Vec2(CENTER.x, CENTER.y - 100));
		btn->setTitleText("Game Start");
		btn->setTitleColor(Color3B::BLACK);
		btn->setTitleFontSize(18.0f);
		btn->setScale9Enabled(true);
		btn->setScaleY(0.7);
		btn->setScaleX(3);
		addChild(btn);

		btn->addClickEventListener([=](Ref*)->void {
			Director::getInstance()->replaceScene(Level::create());
		});
	}
	{
		Button* btn = Button::create(DEFULT_UI);
		btn->setPosition(Vec2(CENTER.x, CENTER.y - 200));
		btn->setTitleText("Exit");
		btn->setTitleColor(Color3B::BLACK);
		btn->setTitleFontSize(18.0f);
		btn->setScale9Enabled(true);
		btn->setScaleY(0.7);
		btn->setScaleX(3);
		btn->addClickEventListener([=](Ref*)->void {
			exit(0);
			});
		addChild(btn);
	}
	return true;
}

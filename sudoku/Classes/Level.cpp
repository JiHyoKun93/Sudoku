#include "stdafx.h"
#include "Level.h"

Level* Level::create() {
	auto ret = new Level();
	if (ret && ret->init()) ret->autorelease();
	else CC_SAFE_DELETE(ret);
	return ret;
}

bool Level::init() {
	if(!Scene::init()) return false;
	
	Button* easybtn = createButton("Easy", Vec2(CENTER.x, CENTER.y+100));
	easybtn->addClickEventListener([=](Ref*)->void {
		Director::getInstance()->replaceScene(PlayGame::create(20));
	});

	Button* nomalbtn = createButton("Nomal", Vec2(CENTER.x, CENTER.y));
	nomalbtn->addClickEventListener([=](Ref*)->void {
		Director::getInstance()->replaceScene(PlayGame::create(35));
	});
	
	Button* hardbtn = createButton("Hard", Vec2(CENTER.x, CENTER.y - 100));
	hardbtn->addClickEventListener([=](Ref*)->void {
		Director::getInstance()->replaceScene(PlayGame::create(50));
	});

	return true;
}

Button* Level::createButton(const string& title, const Vec2& position)
{
	Button* btn = Button::create(DEFULT_UI);
	btn->setPosition(position);
	btn->setTitleText(title);
	btn->setTitleColor(Color3B::BLACK);
	btn->setTitleFontSize(24.0f);
	btn->setScaleX(2);
	btn->setScaleY(0.7);
	addChild(btn);
	return btn;
}

#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "stdafx.h"
#include "Environment.h"
#include "PlayGame.h"


class Level : public Scene {
public:
	static Level* create();
	virtual bool init();

	Button* createButton(const string& title ,const Vec2& position);
};

#endif // !__LEVEL_H__

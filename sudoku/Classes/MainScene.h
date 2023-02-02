#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "stdafx.h"
#include "Environment.h"
#include "Level.h"


class MainScene : public Scene {
public:
	static MainScene* create();
	virtual bool init();
};
#endif // !__MAIN_SCENE_H__

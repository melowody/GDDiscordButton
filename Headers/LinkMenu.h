#pragma once
#include <cocos2d.h>

using namespace cocos2d;

class LinkMenu : public CCMenu {
	LinkMenu() = default;
	bool init();

public:
	static LinkMenu* create();
};


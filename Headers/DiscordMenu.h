#pragma once
#include <cocos2d.h>

using namespace cocos2d;

class DiscordMenu : public CCMenu {
	DiscordMenu() = default;
	bool init();

public:
	static DiscordMenu* create();
};


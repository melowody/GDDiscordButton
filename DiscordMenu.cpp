#include "DiscordMenu.h"
#include "FLAlertLayer.hpp"
#include "Utils.h"
#include "base64.h"

class DiscordProtocol : public FLAlertLayerProtocol {
	virtual void FLAlert_Clicked(FLAlertLayer*, bool btn2) {
		if (btn2) {
			char data[256] = { 0 };
			size_t len = Base64Decode(DiscordButton::tag, data, sizeof(data)) + 1;
			HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
			memcpy(GlobalLock(hMem), data, len);
			GlobalUnlock(hMem);
			OpenClipboard(0);
			EmptyClipboard();
			SetClipboardData(CF_UNICODETEXT, hMem);
			CloseClipboard();

			float x = .5f;
			float y = .6f;
			std::string copyText = "Copied to clipboard";

			auto textBoxAddr = reinterpret_cast<void* (__stdcall*)(std::string)>(DiscordButton::base + 0x1450B0);
			__asm {
				movss xmm0, x
				movss xmm1, y
			}
			CCLayer* ret = (CCLayer*)textBoxAddr(copyText);
			__asm add esp, 0x18

			CCDirector * director = CCDirector::sharedDirector();
			CCScene* scene = director->getRunningScene();
			ret->setZOrder(510);
			scene->addChild(ret);
			auto fadeto = CCFadeTo::create(0.14, 100);
			ret->runAction(fadeto);
		}
	}
};

bool DiscordMenu::init() {
	unsigned char data[256] = { 0 };
	size_t len = Base64Decode(DiscordButton::tag, data, sizeof(data));
	std::string tagShow = "";
	for (int i = 1; i < len; i += 2) {
		if (data[i] == 0) {
			tagShow.push_back(data[i-1]);
		}
		else {
			tagShow = "Could not show tag. Please copy.";
			break;
		}
	}
	FLAlertLayer* optionsLayer = FLAlertLayer::create(new DiscordProtocol(), "Copy Discord Tag", "Close", "Copy", tagShow);
	optionsLayer->show();

	return true;
}

DiscordMenu* DiscordMenu::create() {
	DiscordMenu* discordMenu = new DiscordMenu();
	if (discordMenu && discordMenu->init()) {
		discordMenu->autorelease();
		return discordMenu;
	}
	else {
		CC_SAFE_DELETE(discordMenu);
		return NULL;
	}
}
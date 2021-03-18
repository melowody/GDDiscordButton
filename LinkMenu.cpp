#include "AccountSettingsLayer.h"
#include "LinkMenu.h"
#include "FLAlertLayer.hpp"
#include "Utils.h"
#include <curl/curl.h>

class LinkProtocol : public FLAlertLayerProtocol {
	virtual void FLAlert_Clicked(FLAlertLayer*, bool btn2) {
		if (btn2) {
			const char* tag = LinkButton::token.c_str();
			const size_t len = strlen(tag) + 1;
			HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
			memcpy(GlobalLock(hMem), tag, len);
			GlobalUnlock(hMem);
			OpenClipboard(0);
			EmptyClipboard();
			SetClipboardData(CF_TEXT, hMem);
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

bool LinkMenu::init() {
	std::string text = "Please send this <cy>token</c> in the subject of a message to the account <cl>GDDiscordButton</c>, as well as submitting it to <cl>play.gear.is:3000</c>\n\n";
	CURL* curl = curl_easy_init();

	struct curl_slist* chunk = NULL;

	chunk = curl_slist_append(chunk, "Content-Type: application/x-www-form-urlencoded; charset=utf-8");

	curl_easy_setopt(curl, CURLOPT_URL, "http://play.gear.is:3000/get_token");
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Utils::writeFunction);
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &LinkButton::token);
	curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	curl = NULL;

	text.append(LinkButton::token);

	FLAlertLayer* optionsLayer = FLAlertLayer::create(new LinkProtocol(), "Token", "Close", "Copy", 500, text);
	optionsLayer->show();

	return true;
}

LinkMenu* LinkMenu::create() {
	LinkMenu* linkMenu = new LinkMenu();
	if (linkMenu && linkMenu->init()) {
		linkMenu->autorelease();
		return linkMenu;
	}
	else {
		CC_SAFE_DELETE(linkMenu);
		return NULL;
	}
}
#include "ProfileLayer.h"
// #include "DiscordLayer.h"
#include "MinHook.h"
#include <Windows.h>
#include <string>
#include "DiscordMenu.h"
#include <curl/curl.h>
#include "geometryjump.h"
#include "Utils.h"
#include "base64.h"
#include "discordbutton.h"

void DiscordButton::callback(CCObject* pSender) {
	DiscordMenu* discordMenu = DiscordMenu::create();
	CCMenuItemSpriteExtra* btn = (CCMenuItemSpriteExtra*)pSender;
	btn->stopAllActions();
}

void __fastcall ProfileLayer::loadPageFromUserInfoHook(CCLayer* self, void*, GJUserScore* arg2) {

	ProfileLayer::loadPageFromUserInfo(self, arg2);

	int accountID = arg2->AccountID;

	DiscordButton::tag = "";

	CURL* curl = curl_easy_init();

	struct curl_slist* chunk = NULL;

	chunk = curl_slist_append(chunk, "Content-Type: application/x-www-form-urlencoded; charset=utf-8");

	curl_easy_setopt(curl, CURLOPT_URL, "http://play.gear.is:3000/get_tag?accountID=" + std::to_string(accountID));
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Utils::writeFunction);
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &DiscordButton::tag);
	curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	curl = NULL;

	if (DiscordButton::tag.empty()) {
		return;
	}

	CCImage *img = new CCImage();
	FILE* imageFile;
	if (fopen_s(&imageFile, "Resources/discordbutton.png", "r") == 0) {
		img->initWithImageFileThreadSafe("Resources/discordbutton.png");
	}
	else {
		img->initWithImageData(&dbutton, sizeof(dbutton), CCImage::kFmtPng);
	}
	
	CCTexture2D *texture = new CCTexture2D();
	texture->initWithImage(img);

	CCSprite* sprite = CCSprite::createWithTexture(texture);

	CCMenuItemSpriteExtra* btn = DiscordButton::create(sprite, sprite, self, menu_selector(DiscordButton::callback));

	CCLayer* profileLayer = (CCLayer*)self->getChildren()->objectAtIndex(0);

	CCMenu* object = NULL;
	CCObject* obj;
	CCARRAY_FOREACH(profileLayer->getChildren(), obj) {
		if (CCMenu* m = dynamic_cast<CCMenu*>(obj)) {
			object = m;
		}
	}

	std::string youtube_url;
	std::string twitter_name;
	std::string twitch_name;

	typedef void(__thiscall* getUserYoutubePtr)(GJUserScore* self, std::string* arg1);
	auto getUserYoutube = reinterpret_cast<getUserYoutubePtr>(DiscordButton::base + 0x136380);
	getUserYoutube(arg2, &youtube_url);

	typedef void(__thiscall * getUserTwitterPtr)(GJUserScore* self, std::string* arg1);
	auto getUserTwitter = reinterpret_cast<getUserTwitterPtr>(DiscordButton::base + 0x1363c0);
	getUserTwitter(arg2, &twitter_name);

	typedef void(__thiscall* getUserTwitchPtr)(GJUserScore* self, std::string* arg1);
	auto getUserTwitch = reinterpret_cast<getUserTwitchPtr>(DiscordButton::base + 0x136400);
	getUserTwitch(arg2, &twitch_name);

	int total_icons = int(!youtube_url.empty()) + int(!twitter_name.empty()) + int(!twitch_name.empty());

	btn->setPositionX(408.0);
	btn->setPositionY(-12.0 - (35.0 * total_icons));
	btn->setZOrder(550);

	object->addChild(btn);
	
	if (total_icons == 3) {
		CCMenuItemSpriteExtra* commentButton = NULL;
		CCObject* obj;
		CCARRAY_FOREACH(object->getChildren(), obj) {
			CCMenuItemSpriteExtra* button = (CCMenuItemSpriteExtra*)obj;
			if (fabs(button->getPositionX() - 408.0) < .1f && fabs(button->getPositionY() - -135.0) < .1f) {
				commentButton = button;
			}
		}
		if (commentButton != NULL) {
			commentButton->setPositionY(-153.0);
		}
	}

	return;
}

void ProfileLayer::mem_init() {
	MH_CreateHook(
		(PVOID)(DiscordButton::base + 0x210040),
		ProfileLayer::loadPageFromUserInfoHook,
		(LPVOID*)&ProfileLayer::loadPageFromUserInfo);
}
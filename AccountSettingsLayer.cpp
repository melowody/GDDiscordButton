#include "AccountSettingsLayer.h"
#include "ProfileLayer.h"
#include "LinkMenu.h"
#include <curl/curl.h>
#include "Utils.h"

void LinkButton::callback(CCObject* pSender) {
	LinkMenu* linkMenu = LinkMenu::create();
	CCMenuItemSpriteExtra* btn = (CCMenuItemSpriteExtra*)pSender;
	btn->stopAllActions();
}

bool __fastcall AccountSettingsLayer::accountSettingsInitHook(CCLayerColor* self, void*, int accountID) {

	accountSettingsInit(self, accountID);

	CCLayer* menuLayer = (CCLayer*)self->getChildren()->objectAtIndex(0);

	CCMenu* menu = NULL;
	CCObject* obj;
	CCARRAY_FOREACH(menuLayer->getChildren(), obj) {
		if (CCMenu* m = dynamic_cast<CCMenu*>(obj)) {
			menu = m;
		}
	}

	CCMenuItemSpriteExtra* cancelButton = NULL;
	CCMenuItemSpriteExtra* updateButton = NULL;

	CCARRAY_FOREACH(menu->getChildren(), obj) {
		CCMenuItem* menuItem = (CCMenuItem*)obj;
		if (menuItem->getPositionX() == -48.0 && menuItem->getPositionY() == -130.0) {
			cancelButton = (CCMenuItemSpriteExtra*)menuItem;
		}
		if (menuItem->getPositionX() == 48.0 && menuItem->getPositionY() == -130.0) {
			updateButton = (CCMenuItemSpriteExtra*)menuItem;
		}
	}

	cancelButton->setPositionX(-115.0);
	updateButton->setPositionX(-30.0);

	CCLabelBMFont* text = CCLabelBMFont::create("Discord: ", "goldFont.fnt");

	text->setPositionX(340.0);
	text->setPositionY(31.0);
	text->setScale(0.6);

	typedef CCSprite* (__fastcall* createButtonPtr)(const char*, unsigned long, unsigned long, unsigned long, const char*, const char*, float);
	auto createButton = reinterpret_cast<createButtonPtr>(DiscordButton::base + 0x137D0);
	float scale = .6;
	__asm {
		movss xmm3, scale
	}
	
	CCSprite* linkSprite = createButton("Link", 40, 0, 1, "bigFont.fnt", "GJ_button_01.png", 25);
	__asm {
		add esp, 0x14
	}

	CCMenuItemSpriteExtra* linkButton = LinkButton::create(linkSprite, linkSprite, self, menu_selector(LinkButton::callback));

	linkButton->setPositionX(125.0);
	linkButton->setPositionY(-130.0);

	menu->addChild(linkButton);
	
	menuLayer->addChild(text);
	

	return true;
}

void AccountSettingsLayer::mem_init() {
	MH_CreateHook(
		(PVOID)(DiscordButton::base + 0x13AFB0),
		accountSettingsInitHook,
		(LPVOID*)&accountSettingsInit);
}

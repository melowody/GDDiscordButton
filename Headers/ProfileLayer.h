#pragma once
#include <cocos2d.h>
#include "MinHook.h"
#include "geometryjump.h";

using namespace cocos2d;
namespace ProfileLayer {
    inline bool(__thiscall* loadPageFromUserInfo)(CCLayer* self, GJUserScore* arg2);
    void __fastcall loadPageFromUserInfoHook(CCLayer* self, void*, GJUserScore* arg2);

    void mem_init();
}

class DiscordButton : public CCMenuItemSpriteExtra {
public:
    static size_t base;
    inline static std::string tag;

    void callback(CCObject* pSender);
};
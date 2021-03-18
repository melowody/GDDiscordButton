#pragma once
#include <cocos2d.h>
#include "MinHook.h"
#include "FLAlertLayer.hpp"

using namespace cocos2d;
namespace AccountSettingsLayer {
    inline FLAlertLayer*(__thiscall* accountSettingsInit)(CCLayerColor* self, int accountID);
    bool __fastcall accountSettingsInitHook(CCLayerColor* self, void*, int accountID);

    void mem_init();
}

class LinkButton : public CCMenuItemSpriteExtra {
public:
    inline static std::string token;

    void callback(CCObject* pSender);
};
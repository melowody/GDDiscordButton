#pragma once

#include "cocos2d.h"

using namespace cocos2d;
class GJUserScore
{
public:
	char pad_0004[232]; //0x0004
	std::string username; //0x00EC
	char pad_0104[32]; //0x0104
	int AccountID; //0x0124
	int Stars; //0x0128
	int Diamonds; //0x012C
	int Demons; //0x0130
	char pad_0134[4]; //0x0134
	int CreatorPoints; //0x0138
	int Coins; //0x013C
	int UserCoins; //0x0140
	char pad_0144[4]; //0x0144
	int PColor1; //0x0148
	int PColor2; //0x014C
	char pad_0150[20]; //0x0150
	std::string YoutubeURL; //0x0164
	std::string TwitterURL; //0x017C
	std::string TwitchURL; //0x0194
	int CubeID; //0x01AC
	int ShipID; //0x01B0
	int BallID; //0x01B4
	int UFOID; //0x01B8
	int WaveID; //0x01BC
	int RobotID; //0x01C0
	int SpiderID; //0x01C4
	char pad_01C8[16]; //0x01C8
	int Rank; //0x01D8
	char pad_01DC[16]; //0x01DC

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
};
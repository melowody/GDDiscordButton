#include "Utils.h";
#include <tchar.h>;
#include "resource.h";
#include "extract.h";

CCSprite* Utils::getSprite(int resource_id) {
	ExtractResource* resource = new ExtractResource(GetModuleHandle(TEXT("ProfileButton.dll")), IDB_PNG1, TEXT("discordbutton.png"), L"png");

	CCImage img = CCImage();
	img.initWithImageFile("discordbutton.png");

	CCTexture2D texture = CCTexture2D();
	texture.initWithImage(&img);

	CCSprite* sprite = CCSprite::createWithTexture(&texture);
	return sprite;
}

std::string Utils::utf8_from_iso8859_1(std::string str)
{
	std::string res;
	for (std::string::iterator i = str.begin(); i < str.end(); i++) {
		if (0 <= *i && *i < 0x80)
			res += *i;
		else {
			res += 0xC0 | ((*i >> 6) & 0x03);
			res += 0x80 | (*i & 0x3F);
		}
	}
	return res;
}

size_t Utils::writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data) {
	data->append((char*)ptr, size * nmemb);
	return size * nmemb;
}
#include <cocos2d.h>

using namespace cocos2d;
class Utils {
public:
	static CCSprite* getSprite(int resource_id);
	static std::string utf8_from_iso8859_1(std::string string);
	static size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data);
};
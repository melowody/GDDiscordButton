#include "Utils.h";
#include <tchar.h>;

size_t Utils::writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data) {
	data->append((char*)ptr, size * nmemb);
	return size * nmemb;
}
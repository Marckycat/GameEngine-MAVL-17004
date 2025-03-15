#include "WebRequest.h"
#include <curl/curl.h>
#include <iostream>

size_t reqCallbackTest(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t realsize = size * nmemb;
    //std::cout << "Received: " << (char*)contents << std::endl;
    printf("%.*s\n", realsize, (char*)contents);
    return realsize;
}

size_t reqCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t realsize = size * nmemb;
    //std::cout << "Received: " << (char*)contents << std::endl;
    printf("%.*s\n", realsize, (char*)contents);
    return realsize;
}

int webRequest(lua_State* L) {
	const char* url = lua_tostring(L, 1);
	CURL* curl;
	CURLcode res;
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, reqCallback);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	return 0;
}
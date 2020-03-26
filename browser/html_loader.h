#pragma once

#include <curl/curl.h>
#include <gtkmm.h>

class Html_loader
{
    CURL* m_curl;
public:
    Html_loader();
    ~Html_loader();

    std::string load_file(const std::string& url);
private:
    static size_t curlWriteFunction(char* data, size_t size, size_t memb, std::string* writer_data);
};

#include "html_loader.h"
#include <string>

Html_loader::Html_loader()
{
    m_curl = curl_easy_init();
    curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(m_curl, CURLOPT_TCP_KEEPALIVE, 1L);
    curl_easy_setopt(m_curl, CURLOPT_TCP_KEEPIDLE, 120L);
    curl_easy_setopt(m_curl, CURLOPT_TCP_KEEPINTVL, 60L);
    curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION,	Html_loader::curlWriteFunction);
}

Html_loader::~Html_loader()
{
    curl_easy_cleanup(m_curl);
}

size_t Html_loader::curlWriteFunction(char *data, size_t size, size_t memb, std::string *writer_data )
{
    if(writer_data == NULL)
        return 0;

    writer_data->append(data, size*memb);

    return size * memb;
}

std::string Html_loader::load_file(const std::string& url)
{
    std::string content;

    if(m_curl)
    {
        curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &content);
        curl_easy_perform(m_curl);
    }

    return content;
}

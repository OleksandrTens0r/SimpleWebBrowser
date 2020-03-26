#include "gtest/gtest.h"
#include "../browser/html_loader.h"
#include "curl/curl.h"

static const auto gtest_doc_uri = "http://kaizou.org/2014/11/gtest-cmake/";
static const auto nonexistent_uri = "https://nonexist";


class CurlGlobalEnviroment : public ::testing::Environment
{
public:
    CurlGlobalEnviroment() { }

    void SetUp() override
    {
        conn = curl_easy_init();
        curl_easy_setopt(conn, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(conn, CURLOPT_TCP_KEEPALIVE, 1L);
        curl_easy_setopt(conn, CURLOPT_TCP_KEEPIDLE, 120L);
        curl_easy_setopt(conn, CURLOPT_TCP_KEEPINTVL, 60L);
        curl_easy_setopt(conn, CURLOPT_WRITEFUNCTION, CurlGlobalEnviroment::writer);
    }

    void TearDown() override
    {
        curl_easy_cleanup(conn);
    }

    static int writer(char *data, size_t size, size_t nmemb, std::string *writerData)
    {
      if(writerData == nullptr)
        return 0;

      writerData->append(data, size*nmemb);

      return size * nmemb;
    }

    static CURL* get_connection()
    {
        return CurlGlobalEnviroment::conn;
    }

private:
    static CURL* conn;
};

CURL* CurlGlobalEnviroment::conn = nullptr;

TEST(BrowserTests, loadExistingPage)
{
    Html_loader loader;
    auto html_length = loader.load_file(gtest_doc_uri);
    ASSERT_GT(html_length.size(), 0);
}

TEST(BrowserTest, loadNonExistingPage)
{
    Html_loader loader;
    auto page_content = loader.load_file(nonexistent_uri);
    ASSERT_TRUE(page_content.empty());
}

TEST(BrowserTest, html_load)
{
    std::string content;
    Html_loader loader;

    curl_easy_setopt(CurlGlobalEnviroment::get_connection(), CURLOPT_URL, gtest_doc_uri);
    curl_easy_setopt(CurlGlobalEnviroment::get_connection(), CURLOPT_WRITEDATA, &content);
    curl_easy_perform(CurlGlobalEnviroment::get_connection());

    ASSERT_EQ(content, loader.load_file(gtest_doc_uri));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::Environment* const curl_enviroment =
        ::testing::AddGlobalTestEnvironment(new CurlGlobalEnviroment);
    int ret = RUN_ALL_TESTS();
    return ret;
}

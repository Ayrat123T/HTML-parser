#include <string>
#include <algorithm>

#include "curl/curl.h"
#include "gumbo.h"

namespace request {

    typedef size_t( * curl_write)(char * , size_t, size_t, std::string * );

    std::string Request(std::string word);

    std::string FindDefinitions(GumboNode *node);

    std::string Scrape(std::string markup);

    std::string ExtractText(GumboNode *node);

    std::string StrReplace(std::string search, std::string replace, std::string &subject);
    

} //namespace request
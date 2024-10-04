#include "request.h"

std::string request::Request(std::string word) {
    CURLcode res_code = CURLE_FAILED_INIT;
    CURL * curl = curl_easy_init();
    std::string result;
    std::string url = "https://www.merriam-webster.com/dictionary/" + word;
    curl_global_init(CURL_GLOBAL_ALL);
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,
                        static_cast<curl_write>([](char * contents, size_t size,
                        size_t nmemb, std::string * data) -> size_t {
            size_t new_size = size * nmemb;
            if (data == NULL) {
                return 0;
            }
            data -> append(contents, new_size);
            return new_size;
        }));
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, & result);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "simple Scraper");
        res_code = curl_easy_perform(curl);
        if (res_code != CURLE_OK) {
            return curl_easy_strerror(res_code);
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return result;
}

std::string request::Scrape(std::string markup) {
    std::string res = "";
    GumboOutput *output = gumbo_parse_with_options(&kGumboDefaultOptions, markup.data(), markup.length());
    res += FindDefinitions(output->root);
    gumbo_destroy_output(&kGumboDefaultOptions, output);
    return res;
}

std::string request::FindDefinitions(GumboNode *node) {
    std::string res = "";
    GumboAttribute *attr;
    if (node->type != GUMBO_NODE_ELEMENT) {
        return res;
    }
    if ((attr = gumbo_get_attribute(&node->v.element.attributes, "class")) &&
        strstr(attr->value, "dtText") != NULL) {
        res += ExtractText(node);
        res += "\n";
    }
    GumboVector *children = &node->v.element.children;
    for (int i = 0; i < children->length; ++i) {
        res += FindDefinitions(static_cast<GumboNode *>(children->data[i]));
    }
    return res;
}

std::string request::ExtractText(GumboNode *node) {
    if (node->type == GUMBO_NODE_TEXT) {
        return std::string(node->v.text.text);
    }
    else if (node->type == GUMBO_NODE_ELEMENT &&
            node->v.element.tag != GUMBO_TAG_SCRIPT &&
            node->v.element.tag != GUMBO_TAG_STYLE) {
        std::string contents = "";
        GumboVector *children = &node->v.element.children;
        for (unsigned int i = 0; i < children->length; ++i) {
        std::string text = ExtractText((GumboNode *)children->data[i]);
        if (i != 0 && !text.empty()) {
            contents.append("");
        }
        contents.append(StrReplace(":", ">", text));
        }
        return contents;
    }
    else {
        return "";
    }
}

std::string request::StrReplace(std::string search, std::string replace, std::string &subject) {
    size_t count = 0;
    for (std::string::size_type pos{};
        subject.npos != (pos = subject.find(search.data(), pos, search.length()));
        pos += replace.length(), ++count) {
        subject.replace(pos, search.length(), replace.data(), replace.length());
    }
    return subject;
}
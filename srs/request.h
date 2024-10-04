#include <string>
#include <algorithm>

#include "curl/curl.h"
#include "gumbo.h"

namespace request {

    typedef size_t( * curl_write)(char * , size_t, size_t, std::string * );

    // получить разметку с сайта Merriam-Webster.
    std::string Request(std::string word);

    // рекурсивно собирает определения из элементов HTML span с уникальным идентификатором класса "dtText". 
    // Она извлекает текст определения с помощью функции ExtractText на каждой успешной итерации из каждого HTML-узла,
    // в котором находится этот текст.
    std::string FindDefinitions(GumboNode *node);

    // передает разметку из запроса в FindDefinitions для выборочного итеративного обхода DOM
    std::string Scrape(std::string markup);

    // извлекает текст из каждого узла, который не является тегом script или style. Функция направляет текст на процедуру StrReplace, которая заменяет ведущее двоеточие на бинарный символ >.
    std::string ExtractText(GumboNode *node);

    // заменяет каждый экземпляр заданной строки поиска в большей строке на другую строку
    std::string StrReplace(std::string search, std::string replace, std::string &subject);
    

} //namespace request
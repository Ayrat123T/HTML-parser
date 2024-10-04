#include <iostream>
#include <string>

#include "request.h"

int main(int argc, char **argv) {
  std::string url;
  std::string request_world;
  if (argc == 3) {
    url = argv[1];
    request_world = argv[2];
  } else if (argc == 2) {
    url = "https://www.merriam-webster.com/dictionary/";
    request_world = argv[1];
  } else {
    std::cout << "Please provide a valid English word" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::cout << "URL: " + url + "\nRequest world: \"" + request_world +  "\"\n";
  std::string res = request::Request(url, request_world);
  std::cout << request::Scrape(res) << std::endl;
  return 0;
}
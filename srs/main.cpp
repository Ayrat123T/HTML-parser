#include <iostream>
#include <string>

#include "request.h"

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "Please provide a valid English word" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::string arg = argv[1];
  std::string res = request::Request(arg);
  std::cout << request::Scrape(res) << std::endl;
  return EXIT_SUCCESS;
}
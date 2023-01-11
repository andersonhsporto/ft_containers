//
// Created by Anderson Porto on 12/18/22.
//

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <map>
#include "testsMap.hpp"
#include "testsVector.hpp"
#include "testsStack.hpp"

void testSelector(int number, const char *argv[]);

#include "../includes/3-map/map.hpp"

int main(int argc, const char *argv[]) {

  time_t start, end;

  start = time(NULL);

  testSelector(argc, argv);

  end = time(NULL);

  std::cout << "Time: " << end - start << " seconds" << std::endl;
  return 0;
}

void errorAndExit() {
  std::cout << "Wrong Argument" << std::endl;
  std::cout << "Usage: ./main <test>" << std::endl;
  std::cout << "Tests: -m (Map), -v (Vector), -s (Stack)" << std::endl;
  exit(1);
}

void testSelector(int number, const char *argv[]) {
  if (number != 2) {
    errorAndExit();
  }

  if (strcmp(argv[1], "-m") == 0) {
    std::cout << "Map Test" << std::endl;
    testMap();
  } else if (strcmp(argv[1], "-v") == 0) {
    std::cout << "Vector Test" << std::endl;
    testFtVector();
  } else if (strcmp(argv[1], "-s") == 0) {
    std::cout << "Stack Test" << std::endl;
    testsFtStack();
  } else {
    errorAndExit();
  }
}

//
// Created by Anderson Porto on 12/18/22.
//

#include <iostream>
#include <map>
#include "testsMap.hpp"
#include "testsVector.hpp"
#include "testsStack.hpp"

int main() {
  time_t start, end;

  start = time(NULL);

//  testMap();

//  testFtVector();

  testsFtStack();


  end = time(NULL);


  std::cout << "Time: " << end - start << " seconds" << std::endl;
  return 0;
}
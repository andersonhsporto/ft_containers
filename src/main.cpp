//
// Created by Anderson Porto on 12/18/22.
//

#include <iostream>
#include "testsMap.hpp"

int main() {
  time_t start, end;

  start = time(NULL);

  testErase();
  testEraseRange();
  testSwap();
  testCount();
  testFind();
  testEqualRange();
  lowerBound();
  testValueComp();
  testsOperator();
  testSlowOperation();

  std::cout << "Tteste;\n";

  end = time(NULL);


  std::cout << "Time: " << end - start << " seconds" << std::endl;
  return 0;
}
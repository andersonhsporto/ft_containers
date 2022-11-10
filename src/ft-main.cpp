#include "Vector.hpp"
#include "testsVector.hpp"

int main() {

  // time to test the vector
  time_t start;
  time_t end;

  start = time(NULL);
  testFtVector();
  end = time(NULL);

  std::cout << "Time taken by program is : " << end - start << " seconds" << std::endl;
  return 0;
}

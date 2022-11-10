//
// Created by Anderson Porto on 11/9/22.
//

#include "../includes/Vector.hpp"
#include "../includes/Colors.hpp"
#include "../includes/testsVector.hpp"

void testFtVector() {

  //  testVectorOperatorEqual();
//  testAssignIntVector();
//  testVectorElementAccess();
//  testVectorIterators();
//  testRangeContructor();
//  testVectorPushBack();
//  testVectorPushBack10K();
//  testVectorSize();
//  testVectorResize();
//  testVectorCapacity();
//  testVectorFillConstructor();
//  testVectorClear();
//  testVectorInsert();
//  testVectorErase();
//  testSlowOperation();
//  testVectorPopBack();
  testVectorSwap();
  testVectorCompares();
}


void testSlowOperation() {
  std::cout << "Vector Slow Operation" << std::endl;

  ft::vector<int> myvector;

  for (int i = 0; i < 8000000; i++) {
    myvector.push_back(i);
  }

  for (int i = 0; i < 8000000; i++) {
    myvector[i] = i;
  }

  for (int i = 0; i < 8000000; i++) {
    myvector[i] = i;
  }
  myvector.clear();

  ft::vector<std::string> myvector2;

  for (int i = 0; i < 8000000; i++) {
    myvector2.push_back("test");
  }

  for (int i = 0; i < 8000000; i++) {
    myvector2[i] = "test";
  }

  for (int i = 0; i < 8000000; i++) {
    myvector2[i] = "test";
  }
}

void printIntVector(ft::vector<int> &vec) {
  std::cout << BLUE << "Vector content: " << RESET;
  for (size_t i = 0; i < vec.size(); i++) {
    std::cout << BLUE << vec[i] << " " << RESET;
  }
  std::cout << std::endl;
}

void printCharVector(ft::vector<char> &vec) {
  std::cout << BLUE << "Vector content: " << RESET;
  for (size_t i = 0; i < vec.size(); i++) {
    std::cout << BLUE << vec[i] << " " << RESET;
  }
  std::cout << std::endl;
}

void printStringVector(ft::vector<std::string> &vec) {
  std::cout << BLUE << "Vector content: " << RESET;
  for (size_t i = 0; i < vec.size(); i++) {
    std::cout << BLUE << vec[i] << " " << RESET;
  }
  std::cout << std::endl;
}

void testVectorOperatorEqual() {
  std::cout << GREEN << "\nTest operator= using 0 to 9" << RESET << std::endl;

  ft::vector<int> vec1;
  ft::vector<int> vec2;

  for (int i = 0; i < 10; i++) {
    vec1.push_back(i);
  }

  vec2 = vec1;

  printIntVector(vec2);
}

void testAssignIntVector() {
  std::cout << GREEN << "\nTest assign member function " << RESET << std::endl;

  ft::vector<char> characters;

  std::cout << BLUE << "Assigning 5 'a' characters to the vector" << RESET << std::endl;
  characters.assign(5, 'a');
  printCharVector(characters);

  std::cout << BLUE << "Assigning 3 'b' characters to the vector using iterator" << RESET
            << std::endl;
  const std::string extra(6, 'b');
  characters.assign(extra.begin(), extra.end());
  printCharVector(characters);
}

void testVectorElementAccess() {
  std::cout << GREEN << "\nTest element access" << RESET << std::endl;

  ft::vector<int> vec;

  for (int i = 0; i < 10; i++) {
    vec.push_back(i);
  }

  std::cout << BLUE << "operator[]: " << RESET << vec[0] << std::endl;
  std::cout << BLUE << "at(): " << RESET << vec.at(0) << std::endl;
  std::cout << BLUE << "First element: " << RESET << vec.front() << std::endl;
  std::cout << BLUE << "Last element: " << RESET << vec.back() << std::endl;
}

void testVectorIterators() {
  std::cout << GREEN << "\nTest iterators" << RESET << std::endl;

  ft::vector<int> vec;

  for (int i = 0; i < 10; i++) {
    vec.push_back(i);
  }

  ft::vector<int>::iterator it = vec.begin();
  ft::vector<int>::iterator ite = vec.end();

  std::cout << BLUE << "Vector content: " << RESET;
  while (it != ite) {
    std::cout << BLUE << *it << " " << RESET;
    it++;
  }
  std::cout << std::endl;

  std::cout << BLUE << "Reverse Iterator Test: " << RESET << std::endl;

  ft::vector<int>::reverse_iterator rit = vec.rbegin();
  ft::vector<int>::reverse_iterator rite = vec.rend();

  std::cout << BLUE << "Vector content: " << RESET;
  while (rit != rite) {
    std::cout << BLUE << *rit << " " << RESET;
    rit++;
  }
  std::cout << std::endl;

}

void testRangeContructor() {
  std::cout << GREEN << "\nTest range constructor" << RESET << std::endl;

  ft::vector<int> vec;

  for (int i = 0; i < 10; i++) {
    vec.push_back(i);
  }

  ft::vector<int> vec2(vec.begin(), vec.end());
  printIntVector(vec2);
}

void testVectorPushBack() {
  std::cout << GREEN << "\nVector push_back test using 0 to 10" << RESET << std::endl;

  ft::vector<int> ft_vector;

  for (int i = 0; i < 10; i++) {
    ft_vector.push_back(i);
  }

  printIntVector(ft_vector);
}

void testVectorPushBack10K() {
  std::cout << GREEN << "\nVector push_back test using 0 to 10K" << RESET << std::endl;

  ft::vector<int> ft_vector;

  for (int i = 0; i < 10000; i++) {
    ft_vector.push_back(i);
  }

  std::cout << CYAN << "Vector size: " << ft_vector.size() << RESET << std::endl;
}

void testVectorSize() {
  std::cout << GREEN << "\nVector size test using 0 to 42" << RESET << std::endl;

  ft::vector<int> ft_vector;

  for (int i = 0; i < 42; i++) {
    ft_vector.push_back(i);
  }

  std::cout << CYAN << "Vector size: " << ft_vector.size() << RESET << std::endl;
}

void testVectorResize() {
  std::cout << GREEN << "\nVector resize test using 0 to 15" << RESET << std::endl;

  ft::vector<int> ft_vector;

  for (int i = 0; i < 15; i++) {
    ft_vector.push_back(i);
  }

  std::cout << CYAN << "Vector before resize 10" << RESET << std::endl;
  printIntVector(ft_vector);

  ft_vector.resize(10);

  std::cout << CYAN << "Vector after resize 10" << RESET << std::endl;
  printIntVector(ft_vector);
}

void testVectorCapacity() {
  std::cout << GREEN << "\nVector capacity test using 0 to 15" << RESET << std::endl;

  ft::vector<int> ft_vector;

  for (int i = 0; i < 15; i++) {
    ft_vector.push_back(i);
  }

  std::cout << CYAN << "Vector size: " << ft_vector.size() << RESET << std::endl;
  std::cout << CYAN << "Vector max_size: " << ft_vector.max_size() << RESET << std::endl;
  std::cout << CYAN << "Vector capacity: " << ft_vector.capacity() << RESET << std::endl;
  std::cout << CYAN << "Vector is empty: " << ft_vector.empty() << RESET << std::endl;

  ft::vector<int> empty_vector;

  std::cout << CYAN << "\nEmpty vector size: " << empty_vector.size() << RESET << std::endl;
  std::cout << CYAN << "Empty vector max_size: " << empty_vector.max_size() << RESET << std::endl;
  std::cout << CYAN << "Empty vector capacity: " << empty_vector.capacity() << RESET << std::endl;
  std::cout << CYAN << "Empty vector is empty: " << empty_vector.empty() << RESET << std::endl;
}

void testVectorFillConstructor() {
  std::cout << GREEN << "\nVector fill constructor test" << RESET << std::endl;

  ft::vector<int> ft_vector(10, 42);

  printIntVector(ft_vector);
}

void testVectorClear() {
  std::cout << GREEN << "\nVector clear test" << RESET << std::endl;

  ft::vector<int> ft_vector;

  for (int i = 0; i < 10; i++) {
    ft_vector.push_back(i);
  }

  printIntVector(ft_vector);

  ft_vector.clear();

  std::cout << CYAN << "Vector size: " << ft_vector.size() << RESET << std::endl;
  std::cout << CYAN << "Vector capacity: " << ft_vector.capacity() << RESET << std::endl;
  std::cout << CYAN << "Vector is empty: " << ft_vector.empty() << RESET << std::endl;

  std::cout << CYAN << "Content after clear: " << RESET << std::endl;
  printIntVector(ft_vector); // Should be empty
}

void testVectorInsert() {
  std::cout << GREEN << "\nVector insert test" << RESET << std::endl;

  ft::vector<int> ft_vector;

  for (int i = 0; i < 10; i++) {
    ft_vector.push_back(i);
  }

  printIntVector(ft_vector);

  ft_vector.insert(ft_vector.begin(), 42);

  std::cout << CYAN << "Vector after insert 42 at begin" << RESET << std::endl;
  printIntVector(ft_vector);

  ft_vector.insert(ft_vector.end(), 42);

  std::cout << CYAN << "Vector after insert 42 at end" << RESET << std::endl;
  printIntVector(ft_vector);

  ft_vector.insert(ft_vector.begin() + 5, 42);

  std::cout << CYAN << "Vector after insert 42 at begin + 5" << RESET << std::endl;
  printIntVector(ft_vector);

  ft_vector.insert(ft_vector.begin() + 5, 3, 42);

  std::cout << CYAN << "Vector after insert 3 * 42 at begin + 5" << RESET << std::endl;
  printIntVector(ft_vector);
}

void testVectorErase() {
  std::cout << GREEN << "\nVector erase test" << RESET << std::endl;

  ft::vector<int> ft_vector;

  for (int i = 0; i < 10; i++) {
    ft_vector.push_back(i);
  }

  printIntVector(ft_vector);

  ft_vector.erase(ft_vector.begin());

  std::cout << CYAN << "Vector after erase at begin" << RESET << std::endl;
  printIntVector(ft_vector);

  ft_vector.erase(ft_vector.end() - 1);

  std::cout << CYAN << "Vector after erase at end - 1" << RESET << std::endl;
  printIntVector(ft_vector);

  ft_vector.erase(ft_vector.begin() + 5);

  std::cout << CYAN << "Vector after erase at begin + 5" << RESET << std::endl;
  printIntVector(ft_vector);

  ft_vector.erase(ft_vector.begin() + 5, ft_vector.begin() + 8);

  std::cout << CYAN << "Vector after erase at begin + 5 to begin + 8" << RESET << std::endl;
  printIntVector(ft_vector);
}

void testVectorPopBack() {
  std::cout << GREEN << "\nVector pop_back test" << RESET << std::endl;

  ft::vector<int> ft_vector;

  for (int i = 0; i < 10; i++) {
    ft_vector.push_back(i);
  }

  printIntVector(ft_vector);

  ft_vector.pop_back();

  std::cout << CYAN << "Vector after pop_back" << RESET << std::endl;
  printIntVector(ft_vector);
}

void testVectorSwap() {
  std::cout << GREEN << "\nVector swap test" << RESET << std::endl;

  ft::vector<std::string> ft_vector1;
  ft::vector<std::string> ft_vector2;

  ft_vector1.push_back("Hello");
  ft_vector1.push_back("World");
  ft_vector1.push_back("!");

  ft_vector2.push_back("Ola");
  ft_vector2.push_back("Mundo");
  ft_vector2.push_back("!");

  std::cout << CYAN << "Vector 1 before swap:\t" << RESET;
  printStringVector(ft_vector1);

  std::cout << CYAN << "Vector 2 before swap:\t" << RESET;
  printStringVector(ft_vector2);

  ft_vector1.swap(ft_vector2);

  std::cout << CYAN << "\nVector 1 after swap:\t" << RESET;
  printStringVector(ft_vector1);

  std::cout << CYAN << "Vector 2 after swap:\t" << RESET;
  printStringVector(ft_vector2);
}

void testComparesEqual(const ft::vector<int> &vector1, const ft::vector<int> &vector2) {
  std::cout << CYAN << "\noperator== test" << RESET << std::endl;
  std::cout << CYAN
            << "ft_vector1 == ft_vector2: "
            << RESET
            << (vector1 == vector2)
            << std::endl;
}

void testComparesNotEqual(const ft::vector<int> &vector1, const ft::vector<int> &vector2) {
  std::cout << CYAN << "\noperator!= test" << RESET << std::endl;
  std::cout << CYAN
            << "ft_vector1 != ft_vector2: "
            << RESET
            << (vector1 != vector2)
            << std::endl;
}

void testComparesLess(const ft::vector<int> &vector1, const ft::vector<int> &vector2) {
  std::cout << CYAN << "\noperator< test" << RESET << std::endl;
  std::cout << CYAN
            << "ft_vector1 < ft_vector2: "
            << RESET
            << (vector1 < vector2)
            << std::endl;
}

void testComparesLessEqual(const ft::vector<int> &vector1, const ft::vector<int> &vector2) {
  std::cout << CYAN << "\noperator<= test" << RESET << std::endl;
  std::cout << CYAN
            << "ft_vector1 <= ft_vector2: "
            << RESET
            << (vector1 <= vector2)
            << std::endl;
}

void testComparesGreater(const ft::vector<int> &vector1, const ft::vector<int> &vector2) {
  std::cout << CYAN << "\noperator> test" << RESET << std::endl;
  std::cout << CYAN
            << "ft_vector1 > ft_vector2: "
            << RESET
            << (vector1 > vector2)
            << std::endl;
}

void testComparesGreaterEqual(const ft::vector<int> &vector1, const ft::vector<int> &vector2) {
  std::cout << CYAN << "\noperator>= test" << RESET << std::endl;
  std::cout << CYAN
            << "ft_vector1 >= ft_vector2: "
            << RESET
            << (vector1 >= vector2)
            << std::endl;
}

void testVectorCompares() {
  std::cout << "\n" << GREEN << "Vector compares test" << RESET << std::endl;
  ft::vector<int> ft_vector1;
  ft::vector<int> ft_vector2;

  for (int i = 0; i < 10; i++) {
    ft_vector1.push_back(i);
    ft_vector2.push_back(i + 1);
  }

  testComparesEqual(ft_vector1, ft_vector2);
  testComparesNotEqual(ft_vector1, ft_vector2);
  testComparesLess(ft_vector1, ft_vector2);
  testComparesLessEqual(ft_vector1, ft_vector2);
  testComparesGreater(ft_vector1, ft_vector2);
  testComparesGreaterEqual(ft_vector1, ft_vector2);
}

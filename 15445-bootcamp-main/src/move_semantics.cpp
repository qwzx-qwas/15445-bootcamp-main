/**
 * @file move_semantics.cpp
 * @author Abigale Kim (abigalek)
 * @brief 移动语义的教程代码。
 */

// C++ 中的移动语义是一种有用的概念，它允许在对象之间高效且优化地
// 转移数据的所有权。移动语义的主要目标之一是提高性能，因为移动对象
// 比对对象进行深拷贝更快、更高效。

// 要理解移动语义，需要理解左值（lvalue）和右值（rvalue）的概念。
// 简化地说，左值是指向内存位置的对象；右值是任何不是左值的表达式。

// std::move 是将对象从一个左值“移动”到另一个左值的最常用方法。
// std::move 将表达式转换为右值。这使得可以把左值当作右值来处理，
// 从而将所有权从一个左值转移到另一个左值。

// 在下面的代码中，我们给出一些示例，用于识别 C++ 表达式是左值还是右值、
// 如何使用 std::move，以及如何将右值引用传入函数。

// 包含 std::cout（用于演示打印）。
#include <iostream>
// 包含提供 std::move 的 utility 头。
#include <utility>
// 包含 std::vector 的头。我们会在 containers.cpp 中更详细地介绍 vector，
// 目前需要知道的是 vector 本质上是动态数组，std::vector<int> 是 int 的数组。
// vector 通常占用不小的内存，这里用来展示使用 std::move 带来的性能优势。
#include <vector>

// 接受右值引用作为参数的函数。
// 它获取传入的 vector 的所有权，在末尾添加 3，并打印 vector 中的值。
void move_add_three_and_print(std::vector<int> &&vec) {
  std::vector<int> vec1 = std::move(vec);
  vec1.push_back(3);
  for (const int &item : vec1) {
    std::cout << item << " ";
  }
  std::cout << "\n";
}

// 接受右值引用作为参数的函数。
// 它在传入的 vector 末尾添加 3 并打印其中的值。值得注意的是，
// 它并不获取 vector 的所有权，因此传入的对象在调用者上下文中仍然可用。
void add_three_and_print(std::vector<int> &&vec) {
  vec.push_back(3);
  for (const int &item : vec) {
    std::cout << item << " ";
  }
  std::cout << "\n";
}

int main() {
  // 看这个表达式。注意 'a' 是左值，因为它是一个指向内存中特定位置的变量
  //（存放 'a' 的地方）。10 是右值。
  int a = 10;

  // 看一个将数据从一个左值移动到另一个左值的基本示例。
  // 这里定义一个整型 vector。
  std::vector<int> int_array = {1, 2, 3, 4};

  // 现在，我们将该数组的值移动到另一个左值。
  std::vector<int> stealing_ints = std::move(int_array);

  // 右值引用是指向数据本身的引用，而不是指向位置的左值引用。
  // 对左值（例如 stealing_ints）调用 std::move 会将该表达式转换为右值引用。
  std::vector<int> &&rvalue_stealing_ints = std::move(stealing_ints);

  // 然而注意，之后仍然可以访问 stealing_ints 中的数据，因为拥有数据的是
  // stealing_ints 这个左值，而不是 rvalue_stealing_ints。
  std::cout << "Printing from stealing_ints: " << stealing_ints[1] << std::endl;

  // 可以将右值引用传入函数。然而，一旦右值从调用者上下文的左值移动到
  // 被调用者上下文的左值，调用者就无法再有效使用它。也就是说，在调用
  // move_add_three_and_print 之后，我们不能再使用 int_array2 中的数据，因
  // 为这些数据不再属于 int_array2 这个左值。
  std::vector<int> int_array2 = {1, 2, 3, 4};
  std::cout << "Calling move_add_three_and_print...\n";
  move_add_three_and_print(std::move(int_array2));

  // 在这里对 int_array2 做任何操作都不明智。取消注释试试看！（在我的机器上
  // 这会导致段错误...）注意：这在你的机器上可能可行，但这并不意味着这是
  // 明智的做法！
  // std::cout << int_array2[1] << std::endl;

  // 如果我们没有在被调用者中把调用者上下文的左值移动到任何左值，那么函数
  // 实际上会把传入的右值引用当作普通引用来处理，调用者上下文的左值仍然
  // 拥有该 vector 的数据。
  std::vector<int> int_array3 = {1, 2, 3, 4};
  std::cout << "Calling add_three_and_print...\n";
  add_three_and_print(std::move(int_array3));

  // 如这里所示，我们可以从该数组打印数据。
  std::cout << "Printing from int_array3: " << int_array3[1] << std::endl;

  return 0;
}

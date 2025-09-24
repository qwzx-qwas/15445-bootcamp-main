/**
 * @file templated_functions.cpp
 * @author Abigale Kim (abigalek)
 * @brief 模板函数的教程代码。
 */

// 包含 std::cout（用于演示打印）。
#include <iostream>

// 模板是 C++ 的一项语言特性，允许编写可适用于多种数据类型的代码，而无需在编写时
// 指定具体类型。在 C++ 中可以创建模板函数和模板类。本文件讨论模板函数。

// 下面是一个简单的模板函数，用于相加两个数。
// 语法说明：你会看到 template<class T> 和 template<typename T> 两种写法。
// 虽然二者等价，但 class 与 typename 关键字之间有细微差别。相关讨论见下方文章，
// 不过在课堂中你通常不需要深入该差别：
// https://mariusbancila.ro/blog/2021/03/15/typename-or-class/
template <typename T> T add(T a, T b) { return a + b; }

// 模板可以接受多个类型参数并传入函数。
// 该函数将打印两个不同类型的值。
template<typename T, typename U>
void print_two_values(T a, U b) {
  std::cout << a << " and " << b << std::endl;
}

// 也可以为不同类型创建特化的模板函数，对不同类型做不同处理。
// 以下示例是一个人为的例子：如果是 float 类型则打印类型信息，其他类型则打印 hello world。
template <typename T> void print_msg() { std::cout << "Hello world!\n"; }

// 针对 float 类型的模板特化实现。
template <> void print_msg<float>() {
  std::cout << "print_msg called with float type!\n";
}

// 最后，模板参数不必是类型。例如下面这个简单（但不太现实）的函数，
// 使用一个 bool 作为模板参数，根据该布尔值对输入参数做不同处理。
template <bool T> int add3(int a) {
  if (T) {
    return a + 3;
  }

  return a;
}

int main() {
  // 首先，看看 add 函数在 int 和 float 上的调用。
  std::cout << "Printing add<int>(3, 5): " << add<int>(3, 5) << std::endl;
  std::cout << "Printing add<float>(2.8, 3.7): " << add<float>(2.8, 3.7)
            << std::endl;

  // 也可以让模板函数根据参数推导出类型，尽管对于 C++ 初学者通常不推荐这样做，
  // 以免不确定传入函数的具体类型。
  std::cout << "Printing add(3, 5): " << add(3, 5) << std::endl;

  // 接着，展示 print_two_values 用两个不同类型作为模板参数的调用。
  std::cout << "Printing print_two_values<int, float>(3, 3.2): ";
  print_two_values<int, float>(3, 3.2);

  // 看看在传入和不传入 float 类型时 print_msg 的行为。如预期，第一次调用打印通用输出，
  // 第二次传入 float 类型时会调用特化实现。
  std::cout << "Calling print_msg<int>(): ";
  print_msg<int>();
  std::cout << "Calling print_msg<float>(): ";
  print_msg<float>();

  // add3 对不同的布尔模板参数有不同表现，如下所示。
  std::cout << "Printing add3<true>(3): " << add3<true>(3) << std::endl;
  std::cout << "Printing add3<false>(3): " << add3<false>(3) << std::endl;

  // 最后要注意，大部分示例是人为构造的（contrived），有些功能（例如传入布尔值）
  // 也可以通过普通参数实现，而不使用模板。但在课程代码中会看到类似用法，理解模板函数很有帮助。

  return 0;
}

/**
 * @file auto.cpp
 * @author Abigale Kim (abigalek)
 * @brief 关于 C++ 关键字 auto 用法的示例代码。
 */

// 包含 std::cout（用于演示打印）。
#include <iostream>
// 包含 std::set 库。
#include <set>
// 包含 C++ 字符串库。
#include <string>
// 包含 std::vector 库。
#include <vector>
// 包含 std::unordered_map 库。
#include <unordered_map>

// C++ 的 auto 关键字用于告诉编译器通过初始化表达式推断所声明变量的类型。
// 它非常有用，因为可以提高开发效率（开发者不再需要完整书写冗长的类型名）。
// 在 for-each 循环等场景中也很方便。然而滥用 auto 有风险：开发者可能不知道所使用的实际类型，
// 从而导致难以察觉的 bug 或功能异常。因此请谨慎使用！

// 一个带有很长名字的模板类，用来展示 auto 的用处。
template <typename T, typename U> class Abcdefghijklmnopqrstuvwxyz {
public:
  Abcdefghijklmnopqrstuvwxyz(T instance1, U instance2)
      : instance1_(instance1), instance2_(instance2) {}

  void print() const {
    std::cout << "(" << instance1_ << "," << instance2_ << ")\n";
  }

private:
  T instance1_;
  U instance2_;
};

// 一个返回该长名字类对象的模板函数。
template <typename T>
Abcdefghijklmnopqrstuvwxyz<T, T> construct_obj(T instance) {
  return Abcdefghijklmnopqrstuvwxyz<T, T>(instance, instance);
}

int main() {
  // 使用 auto 关键字初始化变量 a。这里类型会被推断为 int。
  auto a = 1;

  // 下面是一些使用 auto 声明基础变量的例子。
  // 根据所用的 IDE，可能会显示 a、b、c 的具体类型。
  auto b = 3.2;
  auto c = std::string("Hello");

  // 对于这些简单例子来说，使用 auto 并不特别必要。像 int a = 1;、float b = 3.2;
  // 和 std::string c = "Hello"; 之类的写法开销并不大。但在类型名很长或模板嵌套复杂时，
  // 使用 auto 会非常有帮助。
  Abcdefghijklmnopqrstuvwxyz<int, int> obj = construct_obj<int>(2);
  auto obj1 = construct_obj<int>(2);

  // 单行示例看起来变化不大，但如果长期在代码中使用很长的类型名，auto 可以大幅减少重复输入。

  // 关于 auto 的一个重要注意点是它默认会拷贝对象，这可能影响性能。下面例子构造了一个 int vector，
  // 并演示如何定义一个对该 vector 的引用变量。
  std::vector<int> int_values = {1, 2, 3, 4};

  // 下面代码会将 int_values 深拷贝到 copy_int_values，
  // 因为 auto 推断出的类型是 std::vector<int>，而不是 std::vector<int>&。
  auto copy_int_values = int_values;

  // 但下面代码定义了 ref_int_values，它是对 int_values 的引用，因此不会发生深拷贝。
  auto& ref_int_values = int_values;

  // auto 在遍历 C++ 容器时也非常有用。例如，构造一个键为 std::string、值为 int 的 unordered_map，
  // 然后讨论几种遍历它的方法。
  std::unordered_map<std::string, int> map;
  map.insert({{"andy", 445}, {"jignesh", 645}});

  // unordered_map.cpp 中提到的一种方法是使用带迭代器的 for 循环遍历 map。
  // 比较下面两个循环的可读性。
  std::cout << "Printing elements in map...\n";
  for (std::unordered_map<std::string, int>::iterator it = map.begin();
       it != map.end(); ++it) {
    std::cout << "(" << it->first << "," << it->second << ")"
              << " ";
  }
  std::cout << std::endl;

  std::cout << "Printing elements in map with auto...\n";
  for (auto it = map.begin(); it != map.end(); ++it) {
    std::cout << "(" << it->first << "," << it->second << ")"
              << " ";
  }
  std::cout << std::endl;

  // 同样，也可以使用 auto 来遍历 vector 和 set。
  std::vector<int> vec = {1, 2, 3, 4};
  std::cout << "Printing elements in vector with auto...\n";
  for (const auto& elem : vec) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;

  std::set<int> set;
  for (int i = 1; i <= 10; ++i) {
    set.insert(i);
  }

  std::cout << "Printing elements in set with auto...\n";
  for (const auto &elem : set) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;

  // 总之，auto 是一个有用的 C++ 关键字，可以提高代码编写效率，使代码更简洁、更易读。
  // 在实践中，用 auto 遍历容器通常会让代码更简洁。但如果不确定实际类型，回到显式写出类型是完全可以接受的。

  return 0;
}

/**
 * @file move_constructors.cpp
 * @author Abigale Kim (abigalek)
 * @brief 移动构造函数和移动赋值操作符的示例代码。
 */

// 移动构造函数和移动赋值操作符是在类中实现的方法，用于将资源从一个对象
// 高效地移动到另一个对象，通常使用 std::move。此类方法接收同类型的另一个
// 对象，并将其资源移动到调用方法的实例中。本文件将演示如何实现和使用
// 移动构造函数与移动赋值操作符。

// 包含用于演示打印的 std::cout。
#include <iostream>
// 包含提供 std::move 的 utility 头。
#include <utility>
// 包含 C++ 字符串库。
#include <string>
// 包含 uint32_t 的头文件。
#include <cstdint>
// 包含 std::vector 的头。我们会在 containers.cpp 中更详细地介绍 vector，
// 目前需要知道的是 vector 本质上是动态数组，std::vector<std::string> 是字符串数组。
// vector 通常占用较多内存，这里用来展示使用 std::move 带来的性能优势。
#include <vector>

// 基本的 Person 类，已实现移动构造函数和移动赋值操作符，并删除了拷贝构造和
// 拷贝赋值操作符。这意味着一旦 Person 对象被实例化，就不能被复制，必须从一
// 个左值移动到另一个左值。当类必须保证只有一个实例持有资源时，删除拷贝操作是有用的。
// 例如，如果类管理动态分配的内存，未经妥善处理地创建多个实例可能导致重复释放或内存泄漏。
class Person {
public:
  Person() : age_(0), nicknames_({}), valid_(true) {}

  // 请注意该构造函数接受 std::vector<std::string> 的右值引用。这使得构造更高效，
  // 因为在构造 Person 时不会对 vector 做深拷贝。
  Person(uint32_t age, std::vector<std::string> &&nicknames)
      : age_(age), nicknames_(std::move(nicknames)), valid_(true) {}

  // Person 的移动构造函数。它接收一个 Person 类型的右值引用，并将该右值的内容
  // 移动到当前 Person 对象实例中。注意 std::move 的用法：为了确保将 person.nicknames_
  // 移动而不是深拷贝，我们对其使用 std::move，将左值转换为右值。age_ 没有使用 std::move，
  // 因为它是整数类型，拷贝成本很小。通常对于数值类型直接拷贝即可，而对于字符串或其他较大类型
  // 应使用移动以避免不必要的开销。
  Person(Person &&person)
      : age_(person.age_), nicknames_(std::move(person.nicknames_)),
        valid_(true) {
    std::cout << "Calling the move constructor for class Person.\n";
    // 被移动对象的有效性标记设为 false。
    person.valid_ = false;
  }

  // Person 的移动赋值操作符。
  Person &operator=(Person &&other) {
    std::cout << "Calling the move assignment operator for class Person.\n";
    age_ = other.age_;
    //调用了 std::vector 的移动赋值函数，直接把 other 的内部指针“偷”过来，而不是复制每个元素。
    //效率很高。
    nicknames_ = std::move(other.nicknames_);
    valid_ = true;

    // 被移动对象的有效性标记设为 false。
    other.valid_ = false;
    return *this;
  }

  // 我们删除拷贝构造函数和拷贝赋值操作符，因此该类不能被拷贝构造。
  Person(const Person &) = delete;
  Person &operator=(const Person &) = delete;

  uint32_t GetAge() { return age_; }

  // 返回类型中的 & 表示返回 nicknames_[i] 的引用。这意味着不会复制该字符串，
  // 返回的地址实际上指向 nicknames_ vector 中的内存。
  std::string &GetNicknameAtI(size_t i) { return nicknames_[i]; }

  void PrintValid() {
    if (valid_) {
      std::cout << "Object is valid." << std::endl;
    } else {
      std::cout << "Object is invalid." << std::endl;
    }
  }

private:
  uint32_t age_;
  std::vector<std::string> nicknames_;
  // 跟踪对象的数据是否有效，即其所有数据是否已被移动到另一个实例。
  bool valid_;
};

int main() {
  // 演示如何在类中实现并使用移动构造函数和移动赋值操作符。首先创建一个 Person 实例。
  // 注意 andy 是一个有效的对象。
  Person andy(15445, {"andy", "pavlo"});
  std::cout << "Printing andy's validity: ";
  andy.PrintValid();

  // 要把 andy 的内容移动到另一个对象，我们可以用 std::move 有几种方式。下面这种方式会调用移动赋值操作符。
  Person andy1;
  andy1 = std::move(andy);

  // 注意 andy1 是有效的，而 andy 则不再是有效对象。
  std::cout << "Printing andy1's validity: ";
  andy1.PrintValid();
  std::cout << "Printing andy's validity: ";
  andy.PrintValid();

  // 这种方式会调用移动构造函数。此操作后，原始 andy 的内容先移动到 andy1，再移动到 andy2。
  // andy 和 andy1 作为左值已失效（除非重新初始化，否则不应使用）。
  Person andy2(std::move(andy1));

  // 注意 andy2 是有效的，而 andy1 则不再有效。
  std::cout << "Printing andy2's validity: ";
  andy2.PrintValid();
  std::cout << "Printing andy1's validity: ";
  andy1.PrintValid();

  // 注意：由于拷贝赋值操作符被删除，下面代码将无法编译。第一行通过默认构造构造新对象，
  // 第二行尝试使用拷贝赋值将 andy2 的深拷贝内容赋给 andy3。取消注释可以查看编译器报错。
  // Person andy3;
  // andy3 = andy2;

  // 由于拷贝构造被删除，下面代码也无法编译。取消注释以查看编译错误。
  // Person andy4(andy2);

  return 0;
}

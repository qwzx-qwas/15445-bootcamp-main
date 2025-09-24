/**
 * @file wrapper_class.cpp
 * @author Abigale Kim (abigalek)
 * @brief 关于包装类（wrapper classes）的教程代码。
 */

// C++ 中的包装类是用于管理某种资源的类。资源可以是内存、文件套接字或网络连接。
// 包装类通常使用 RAII（Resource Acquisition Is Initialization，资源获取即初始化）
// 的编程技巧。使用该技巧意味着资源的生命周期与作用域绑定：当包装类实例被构造时，
// 它管理的底层资源可用；当该实例被析构时，资源也随之不可用。
// 下面是一些关于 RAII 的有用资料：
// https://en.cppreference.com/w/cpp/language/raii (CPP 文档的 RAII 页面)
// 关于 “What is meant by RAII?” 的一些有趣的 Stack Overflow 回答：
// https://stackoverflow.com/questions/2321511/what-is-meant-by-resource-acquisition-is-initialization-raii

// 在本文件中，我们将查看一个基本的包装类实现，该类管理一个 int*，并演示如何使用它。

// 包含 std::cout（用于演示打印）。
#include <iostream>
// 包含提供 std::move 的 utility 头。
#include <utility>

// IntPtrManager 类是一个管理 int* 的包装类。该类管理的资源是通过指针 ptr_ 访问的动态内存。
// 根据 RAII 原则，包装类对象通常不可复制，因为每个对象应当管理自己的唯一资源。
// 因此本类删除了拷贝构造函数和拷贝赋值操作符。但类仍然可移动，提供了移动构造函数和移动赋值操作符。
// 如果两个对象管理相同资源，可能导致重复释放。
class IntPtrManager {
  public:
    // 所有包装类的构造函数都应初始化它要管理的资源。在这里即分配我们管理的内存。
    // 该指针所指向的数据的默认值为 0。
    IntPtrManager() {
      ptr_ = new int;
      *ptr_ = 0;
    }

    // 提供带初始值的构造函数。
    IntPtrManager(int val) {
      ptr_ = new int;
      *ptr_ = val;
    }

    // 包装类的析构函数。析构函数必须销毁它所管理的资源；在这里就是 delete 指针。
    ~IntPtrManager() {
      // 注意：移动构造函数会通过将 ptr_ 设为 nullptr 来标记被移动对象无效，
      // 因此析构函数需要处理这种情况。我们不应对 nullptr 调用 delete。
      if (ptr_) {
        delete ptr_;
      }
    }

    // 移动构造函数。移动构造后，other 的数据被转移到当前被构造的实例中，
    // other 不再是一个有效的 IntPtrManager 实例（因为它不再管理内存）。
    IntPtrManager(IntPtrManager&& other) {
      ptr_ = other.ptr_;
      other.ptr_ = nullptr;
    }

    // 移动赋值操作符。与移动构造函数类似的处理手法。
    IntPtrManager &operator=(IntPtrManager &&other) {
      if (ptr_ == other.ptr_) {
        return *this;
      }
      if (ptr_) {
        delete ptr_;
      }
      ptr_ = other.ptr_;
      other.ptr_ = nullptr;
      return *this;
    }

    // 删除拷贝构造函数和拷贝赋值操作符，因此该类不可被拷贝构造。
    IntPtrManager(const IntPtrManager &) = delete;
    IntPtrManager &operator=(const IntPtrManager &) = delete;

    // 设置值的函数。
    void SetVal(int val) {
      *ptr_ = val;
    }

    // 获取值的函数。
    int GetVal() const {
      return *ptr_;
    }

  private:
    int *ptr_;

};

int main() {
  // 初始化一个 IntPtrManager 实例。初始化后该实例开始管理一个 int 指针。
  IntPtrManager a(445);

  // 读取值按预期工作。
  std::cout << "1. Value of a is " << a.GetVal() << std::endl;

  // 设置值后也可正常读取。
  a.SetVal(645);
  std::cout << "2. Value of a is " << a.GetVal() << std::endl;

  // 通过移动构造函数将 a 的所有权移动到 b。
  IntPtrManager b(std::move(a));

  // 读取 b 的值按预期工作，因为 b 现在管理原本由 a 构造时分配的数据。
  // 注意：对 a 调用 GetVal() 将导致段错误，因为 a 在被移动后应视为不可用（空）。
  std::cout << "Value of b is " << b.GetVal() << std::endl;

  // 当函数结束时，a 和 b 的析构函数都会被调用。
  // a 的析构函数会发现它的 ptr_ 被设为 nullptr 并什么都不做，而 b 的析构函数应释放它管理的内存。

  return 0;
}

/**
 * @file unique_ptr.cpp
 * @author Abigale Kim (abigalek)
 * @brief unique_ptr 使用教程代码。
 */

// 智能指针是一种用于内存管理（有时还包含其他功能）的数据结构，适用于那些没有内建内存管理的语言（例如 C++）。
// 有垃圾回收的语言（例如 Java 或 Python）则自带内存管理。现代 C++ 标准库中常用的智能指针有 std::unique_ptr 和 std::shared_ptr，
// 这两个类型会自动管理内存分配与释放，并在内部封装原始指针。换句话说，它们是对原始指针的封装类。
// 在本文件中，我们将讲解 std::unique_ptr。
// std::unique_ptr 是一种对对象保持独占所有权的智能指针类型，这意味着不会有两个 std::unique_ptr 实例管理相同的对象。

// 包含 std::cout（用于演示打印）。
#include <iostream>
// 包含 std::unique_ptr 功能。
#include <memory>
// 字符串库，用于演示打印。
#include <string>
// 包含 std::move 所需的 utility 头文件。
#include <utility>

// 基本的 Point 类。（稍后会使用）
class Point {
public:
  Point() : x_(0), y_(0) {}
  Point(int x, int y) : x_(x), y_(y) {}
  inline int GetX() { return x_; }
  inline int GetY() { return y_; }
  inline void SetX(int x) { x_ = x; }
  inline void SetY(int y) { y_ = y; }

private:
  int x_;
  int y_;
};

// 接受 unique_ptr 引用并将其 x 值设置为 445 的函数。
void SetXTo445(std::unique_ptr<Point> &ptr) { ptr->SetX(445); }

int main() {
  // 以下展示如何初始化不同状态的 std::unique_ptr<Point>。
  // 这是初始化一个空的 std::unique_ptr<Point> 的方式。
  std::unique_ptr<Point> u1;
  // 这是使用默认构造函数初始化 unique_ptr 的方式。（u2 不是 nullptr，它指向刚刚创建的那个 Point 对象。
  std::unique_ptr<Point> u2 = std::make_unique<Point>();
  // 这是使用自定义构造函数初始化 unique_ptr 的方式。
  std::unique_ptr<Point> u3 = std::make_unique<Point>(2, 3);

  // 对于 std::unique_ptr 实例 u，可以用 (u ? "not empty" : "empty") 来判断该指针是否管理了对象。
  // 关键点是 std::unique_ptr 提供了到布尔类型的转换，当将 std::unique_ptr 当作布尔值使用时会调用该转换。
  if (u1) {
    // 由于 u1 为空，这里不会打印。
    std::cout << "u1's value of x is " << u1->GetX() << std::endl;
  }

  if (u2) {
    // 由于 u2 非空且管理了一个 Point 实例，这里会打印。
    std::cout << "u2's value of x is " << u2->GetX() << std::endl;
  }

  // 注意：u1 为空，而 u2 和 u3 非空，因为它们被初始化为管理一个 Point 实例。
  std::cout << "Pointer u1 is " << (u1 ? "not empty" : "empty") << std::endl;
  std::cout << "Pointer u2 is " << (u2 ? "not empty" : "empty") << std::endl;
  std::cout << "Pointer u3 is " << (u3 ? "not empty" : "empty") << std::endl;

  // 由于 std::unique_ptr 实例只能有一个所有者，它没有拷贝构造函数。因此下面代码不会编译（已注释）。
  // std::unique_ptr<Point> u4 = u3;

  // 但是可以通过 std::move 转移 unique_ptr 的所有权。
  std::unique_ptr<Point> u4 = std::move(u3);

  // 由于 u3 已被移动（是一个左值），它不再管理对象，变为空 unique_ptr。我们再次检测其是否为空。
  std::cout << "Pointer u3 is " << (u3 ? "not empty" : "empty") << std::endl;
  std::cout << "Pointer u4 is " << (u4 ? "not empty" : "empty") << std::endl;

  // 最后，讨论如何将 std::unique_ptr 作为函数参数传递。通常应以引用传递，以避免改变所有权。
  // 下面的 SetXTo445 即为示例（在本文件中定义）。
  SetXTo445(u4);

  // 现在打印 u4 的 x 值以确认已修改，同时对象所有权仍保留在 u4 中。
  std::cout << "Pointer u4's x value is " << u4->GetX() << std::endl;

  return 0;
}

/**
 * @file shared_ptr.cpp
 * @author Abigale Kim (abigalek)
 * @brief shared_ptr 使用教程代码。
 */

// 在此文件中，我们将讨论 C++ 智能指针 std::shared_ptr。
// 有关智能指针的介绍可参见 unique_ptr.cpp 的开头部分。
// std::shared_ptr 是一种保有对象共享所有权的智能指针类型。
// 这意味着多个 shared_ptr 可以拥有同一个对象，并且 shared_ptr 可以被拷贝。

// 包含 std::cout（用于演示打印）。
#include <iostream>
// 包含 std::shared_ptr 功能。
#include <memory>
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

// 通过引用传入 shared_ptr 并修改其内部 Point 对象的函数。
void modify_ptr_via_ref(std::shared_ptr<Point> &point) { point->SetX(15); }

// 通过右值引用传入 shared_ptr 并修改其内部 Point 对象的函数。
void modify_ptr_via_rvalue_ref(std::shared_ptr<Point> &&point) {
  point->SetY(645);
}

void copy_shared_ptr_in_function(std::shared_ptr<Point> point) {
  std::cout << "Use count of shared pointer is " << point.use_count()
            << std::endl;
}

int main() {
  // 下面展示如何初始化不同状态的 std::shared_ptr<Point>。
  // 这是初始化一个空的 std::shared_ptr<Point> 的方式。
  std::shared_ptr<Point> s1;
  // 这是使用默认构造函数初始化 shared_ptr 的方式。
  std::shared_ptr<Point> s2 = std::make_shared<Point>();
  // 这是使用自定义构造函数初始化 shared_ptr 的方式。
  std::shared_ptr<Point> s3 = std::make_shared<Point>(2, 3);

  // unique_ptr.cpp（第 56 行）介绍了检查智能指针是否为空的具体语法。
  // 注意 s1 为空，而 s2 和 s3 非空。
  std::cout << "Pointer s1 is " << (s1 ? "not empty" : "empty") << std::endl;
  std::cout << "Pointer s2 is " << (s2 ? "not empty" : "empty") << std::endl;
  std::cout << "Pointer s3 is " << (s3 ? "not empty" : "empty") << std::endl;

  // shared_ptr 支持通过拷贝赋值和拷贝构造来复制共享指针。使用这些拷贝操作会增加指向同一对象的引用计数。
  // std::shared_ptr 提供了 use_count 方法，用于返回当前有多少个 shared_ptr 实例共同管理同一对象。

  // 首先获取 s3 的引用计数。此时为 1，因为只有 s3 使用它所管理的数据。
  std::cout
      << "Number of shared pointer object instances using the data in s3: "
      << s3.use_count() << std::endl;

  // 然后使用拷贝构造从 s3 创建 s4。
  // 这里是拷贝构造，因为这是 s4 第一次出现。
  std::shared_ptr<Point> s4 = s3;

  // 现在 s3 的引用计数应为 2，因为 s3 和 s4 都访问相同的数据。
  std::cout << "Number of shared pointer object instances using the data in s3 "
               "after one copy: "
            << s3.use_count() << std::endl;

  // 再次拷贝构造，从 s4 创建 s5。
  std::shared_ptr<Point> s5(s4);

  // 现在 s3 的引用计数应为 3，因为 s3、s4 和 s5 都访问相同的数据。
  std::cout << "Number of shared pointer object instances using the data in s3 "
               "after two copies: "
            << s3.use_count() << std::endl;

  // 修改 s3 所指向的数据也会影响 s4 和 s5，因为它们指向同一个对象实例。
  s3->SetX(445);

  std::cout << "Printing x in s3: " << s3->GetX() << std::endl;
  std::cout << "Printing x in s4: " << s4->GetX() << std::endl;
  std::cout << "Printing x in s5: " << s5->GetX() << std::endl;

  // 也可以通过移动语义转移 std::shared_ptr 的所有权。注意移动后被移动的指针会变为空。
  std::shared_ptr<Point> s6 = std::move(s5);

  // 现在 s5 为空，s6 与 s3、s4 共享相同数据，且仍然只有 3 个 shared_ptr 实例访问同一 Point 实例（不是 4 个）。
  std::cout << "Pointer s5 is " << (s5 ? "not empty" : "empty") << std::endl;
  std::cout << "Number of shared pointer object instances using the data in s3 "
               "after two copies and a move: "
            << s3.use_count() << std::endl;

  // 与 unique_ptr 类似，shared_ptr 也可以按引用或按右值引用传递。
  // 有关按引用传递 unique_ptr 的说明参见 unique_ptr.cpp（第 89 行）。
  // 有关引用和右值引用的更多信息参见 references.cpp 和 move_semantics.cpp。
  // 下面演示按引用和按右值引用调用会修改 s2 的函数。
  modify_ptr_via_ref(s2);
  modify_ptr_via_rvalue_ref(std::move(s2));

  // 运行上述代码后，s2 的 x 应为 15，y 应为 645。
  std::cout << "Pointer s2 has x=" << s2->GetX() << " and y=" << s2->GetY()
            << std::endl;

  // 与 unique_ptr 不同，shared_ptr 也可以按值传递。此时函数内部会有一个 shared_ptr 的副本，
  // 在函数结束时该副本会被销毁。下面示例说明：在将 s2 按值传入函数前，它的 use_count 为 1；
  // 在函数体内为 2（函数内部有一个额外的拷贝）；函数返回后该拷贝被销毁，use_count 回到 1。
  std::cout
      << "Number of shared pointer object instances using the data in s2: "
      << s2.use_count() << std::endl;
  copy_shared_ptr_in_function(s2);
  std::cout << "Number of shared pointer object instances using the data in s2 "
               "after calling copy_shared_ptr_in_function: "
            << s2.use_count() << std::endl;

  return 0;
}

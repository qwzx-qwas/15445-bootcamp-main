/**
 * @file vectors.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code for C++ Standard Library (STL) vectors.
 */

// C++ STL 包含一个容器库，它是一组通用的数据结构和算法实现，方便用户操作诸如栈、队列和哈希表等数据结构。
// 每种容器都有对应的头文件和使用方式。在 C++ 标准（到 C++23）中，当前有 20 种容器，内容太多无法在此详尽覆盖。
// 本文件将介绍容器 std::vector。std::vector 本质上是一个通用的动态数组（或无界数组）。我们无法覆盖其所有函数，
// 但会尽量讲解使用该容器的基础知识。

// 有关其他函数和容器的文档，请参见：
// https://en.cppreference.com/w/cpp/container。完成本课程作业时你会经常需要该资源，建议收藏查阅！

// 包含 std::remove_if（用于从 vector 中移除元素）。
#include <algorithm>
// 包含 std::cout（示例打印用）。
#include <iostream>
// 包含 vector 容器头文件。
#include <vector>

// 简单的 Point 类（稍后会使用）。
class Point {
public:
  Point() : x_(0), y_(0) {
    std::cout << "Default constructor for the Point class is called.\n";
  }

  Point(int x, int y) : x_(x), y_(y) {
    std::cout << "Custom constructor for the Point class is called.\n";
  }

  inline int GetX() const { return x_; }
  inline int GetY() const { return y_; }
  inline void SetX(int x) { x_ = x; }
  inline void SetY(int y) { y_ = y; }
  void PrintPoint() const {
    std::cout << "Point value is (" << x_ << ", " << y_ << ")\n";
  }

private:
  int x_;
  int y_;
};

// 一个用于打印 int vector 元素的工具函数。实现应当易于理解，与 main 中遍历向量元素的代码类似。
void print_int_vector(const std::vector<int> &vec) {
  for (const int &elem : vec) {
    std::cout << elem << " ";
  }
  std::cout << "\n";
}

int main() {
  // 我们可以用下面的语法声明一个 Point vector。
  std::vector<Point> point_vector;

  // 也可以通过初始化列表来初始化 vector。
  std::vector<int> int_vector = {0, 1, 2, 3, 4, 5, 6};

  // vector 尾部追加数据有两个函数：push_back 和 emplace_back。通常 emplace_back 略快一些，
  // 因为它将构造参数转发给对象构造函数并就地构造对象；而 push_back 则先构造对象，再移动到向量内存中。
  // 下面示例中我们向向量中添加了两个 Point 对象以演示两者差异。
  std::cout << "Appending to the point_vector via push_back:\n";
  point_vector.push_back(Point(35, 36));
  std::cout << "Appending to the point_vector via emplace_back:\n";
  point_vector.emplace_back(37, 38);

  // 再往 point_vector 尾部添加更多元素。
  point_vector.emplace_back(39, 40);
  point_vector.emplace_back(41, 42);

  // 迭代 vector 有多种方式。例如，可以通过索引如下遍历。注意，使用无符号整数类型作为数组或 vector 索引是个好习惯。
  std::cout << "Printing the items in point_vector:\n";
  for (size_t i = 0; i < point_vector.size(); ++i) {
    point_vector[i].PrintPoint();
  }

  // 也可以使用范围 for（for-each）遍历。这里使用引用来遍历，使得迭代的元素是原 vector 中的元素本身。
  // 若以引用迭代，可以修改 vector 中的数据。
  for (Point &item : point_vector) {
    item.SetY(445);
  }

  // 检查修改是否生效。此处使用 const 引用语法以确保只读访问。
  for (const Point &item : point_vector) {
    item.PrintPoint();
  }

  // 下面展示如何从 vector 中擦除元素。首先可以按位置通过 erase 删除元素。例如，如果想删除 int_vector[2]，
  // 可以调用下面的函数。传入 erase 的参数类型是 std::vector<int>::iterator。C++ STL 容器的迭代器是指向容器中
  // 某个元素的对象。例如 int_vector.begin() 是一个迭代器，指向 vector 的第一个元素。vector 迭代器支持加法操作，
  // 可以将迭代器和整数相加，这会将迭代器指向的索引向后移动相应的数量。因此 int_vector.begin() + 2
  // 指向向量的第三个元素，即 int_vector[2]。
  // 如果你对迭代器感到困惑，建议阅读 iterator.cpp 的头部注释。
  int_vector.erase(int_vector.begin() + 2);
  std::cout << "Printing the elements of int_vector after erasing "
               "int_vector[2] (which is 2)\n";
  print_int_vector(int_vector);

  // 也可以通过范围调用 erase 删除一段元素。如果想删除从索引 1 到 vector 末尾的元素，可以像下面这样做。
  // 注意 int_vector.end() 是指向 vector 末尾的迭代器。它并不指向最后一个有效元素，而是指向容器末端，不能用于读取数据。
  int_vector.erase(int_vector.begin() + 1, int_vector.end());
  std::cout << "Printing the elements of int_vector after erasing all elements "
               "from index 1 through the end\n";
  print_int_vector(int_vector);

  // 也可以通过过滤条件删除值。可以使用算法库中的 std::remove_if，按条件从迭代器区间中移除所有满足条件的元素。
  // 这看起来有点复杂，但可以总结如下：
  // std::remove_if 接受 3 个参数。前两个参数表示要过滤的元素范围，通常使用 point_vector.begin() 和 point_vector.end()
  // 表示整个 vector。第三个参数是一个条件型的 lambda（可参考 C++ 的 std::function 或
  // https://en.cppreference.com/w/cpp/utility/functional/function），该 lambda 接受一个参数（代表 vector 中的每个元素），
  // 返回布尔值：如果返回 true，则该元素应被移除，返回 false 则保留该元素。std::remove_if 返回一个迭代器，
  // 指向容器中第一个应被删除的位置。它会在容器内交换元素，将需删除的元素分区到返回的迭代器之后。
  // 然后结合 erase 调用（传入 remove_if 返回的迭代器 到 end）就可以删除这些分区出的元素。
  point_vector.erase(
      std::remove_if(point_vector.begin(), point_vector.end(),
                     [](const Point &point) { return point.GetX() == 37; }),
      point_vector.end());

  // 调用 remove_if 后，我们应该看到 point_vector 中剩下三个元素。只有值为 (37, 445) 的元素被删除。
  std::cout << "Printing the point_vector after (37, 445) is erased:\n";
  for (const Point &item : point_vector) {
    item.PrintPoint();
  }

  // 关于更风格化、可读性更好的遍历 C++ STL 容器的方法，请参见 auto.cpp！有兴趣的话可以去看看。

  return 0;
}

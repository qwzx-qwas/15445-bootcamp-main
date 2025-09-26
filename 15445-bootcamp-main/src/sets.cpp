/**
 * @file sets.cpp
 * @author Abigale Kim (abigalek)
 * @brief C++ 标准库（STL） set 容器的示例代码。
 */

// 在此文件中，我们将介绍容器 std::set。我们无法覆盖此容器的每个函数，
// 但会尽量讲解使用该容器的基础知识。有关 C++ STL 容器的一般概述，请参见 vectors.cpp 的开头部分。

// std::set 是一个包含已排序且唯一对象的容器，所有元素类型相同。如果有助于理解，可以把它想象成常用的红黑树实现。
// std::set 用于维护一组不重复的元素集合。

// 有关其他函数和容器的文档，请参见 https://en.cppreference.com/w/cpp/container。
// 在完成本课程作业时你会经常需要该资源，建议收藏并查阅！

// 包含 std::cout（用于演示打印）。
#include <iostream>
// 包含 set 容器头文件。
#include <set>

int main() {
  // 我们可以用下面的语法声明一个 int 类型的 set。
  std::set<int> int_set;

  // 使用 insert 函数插入元素。这里我们向集合中插入 1 到 5。
  // 还有一个 emplace 函数，允许在集合中就地构造对象。emplace 在 vectors.cpp（第 73 行）有更多说明。
  for (int i = 1; i <= 5; ++i) {
    int_set.insert(i);
  }

  for (int i = 6; i <= 10; ++i) {
    int_set.emplace(i);
  }

  // 要查找元素，可以使用 find 函数，它返回一个指向集合中与给定 key 等价元素的迭代器。
  // 然后检查返回的迭代器是否等于 end 迭代器即可。如果相等则表示元素不存在。
  std::set<int>::iterator search = int_set.find(2);
  if (search != int_set.end()) {
    std::cout << "Element 2 is in int_set.\n";
  }

  // 也可以使用 count 函数，它返回集合中具有指定 key 的元素个数。
  if (int_set.count(11) == 0) {
    std::cout << "Element 11 is not in the set.\n";
  }

  if (int_set.count(3) == 1) {
    std::cout << "Element 3 is in the set.\n";
  }

  // 要删除元素，可以使用 erase 函数。erase 首先可以接受一个要删除的 key。
  // 例如，如果想从集合中删除 4，可以这样调用：
  int_set.erase(4);

  // 验证 4 不再在集合中。
  if (int_set.count(4) == 0) {
    std::cout << "Element 4 is not in the set.\n";
  }

  // 此外，如果想删除集合中某个位置的元素，可以向 erase 传入一个迭代器。
  // 比如想删除集合中的第一个元素，可以传入指向第一个元素的迭代器。
  int_set.erase(int_set.begin());

  // 验证 1 不再在集合中。
  if (int_set.count(1) == 0) {
    std::cout << "Element 1 is not in the set.\n";
  }

  // 最后，也可以通过传入迭代器区间来删除一段元素。例如，如果想删除大于等于 9 的元素（即 9 和 10），可以这样调用。
  int_set.erase(int_set.find(9), int_set.end());

  // 验证 9 和 10 不再在集合中。
  if (int_set.count(9) == 0 && int_set.count(10) == 0) {
    std::cout << "Elements 9 and 10 are not in the set.\n";
  }

  // 我们可以通过 set 的迭代器来遍历集合元素。不能像数组那样通过索引来迭代 set。
  std::cout << "Printing the elements of the iterator:\n";
  for (std::set<int>::iterator it = int_set.begin(); it != int_set.end();
       ++it) {
    // 通过解引用迭代器访问元素本身。
    std::cout << *it << " ";
  }
  std::cout << "\n";

  // 和 std::vector 一样，也可以使用范围 for（for-each）遍历 set。
  std::cout << "Printing the elements of the iterator with a for-each loop:\n";
  for (const int &elem : int_set) {
    std::cout << elem << " ";
  }
  std::cout << "\n";

  // 关于更风格化、可读性更好的遍历 C++ STL 容器的方法，请参见 auto.cpp！有兴趣的话可以去看看。

  return 0;
}

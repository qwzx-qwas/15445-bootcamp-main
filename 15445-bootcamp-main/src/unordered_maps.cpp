/**
 * @file unordered_maps.cpp
 * @author Abigale Kim (abigalek)
 * @brief C++ 标准库（STL） unordered_map 的示例代码。
 */

// 在此文件中，我们将介绍容器 std::unordered_map。我们无法覆盖此容器的所有函数，
// 但会尽量讲解使用该容器的基础用法。有关 C++ STL 容器的一般介绍，请参阅 vectors.cpp 的开头部分。

// 有关其他函数和容器的文档，请参见 https://en.cppreference.com/w/cpp/container。
// 在完成本课程作业时你肯定会需要这个资源，建议查看并收藏！

// 包含 std::cout（用于演示打印）。
#include <iostream>
// 包含 unordered_map 容器头文件。
#include <unordered_map>
// 包含 C++ 字符串库。
#include <string>
// 包含 std::make_pair。
#include <utility>

int main() {
  // std::unordered_map 是一种包含键值对且键唯一的数据结构。
  // 本质上，你可以在代码中将它用作哈希表。

  // 可以用下面的语法声明一个键为 string、值为 int 的 unordered_map。
  std::unordered_map<std::string, int> map;

  // 使用 insert 函数向 unordered_map 插入元素。
  map.insert({"foo", 2});

  // insert 也可以接受 std::pair 作为参数。std::pair 是一个通用的键值对类型，
  // 可以通过调用 std::make_pair 并传入两个参数来创建。std::make_pair 在头文件
  // <utility> 中定义，用于构造一个通用 pair 实例。
  map.insert(std::make_pair("jignesh", 445));

  // 也可以通过传入成对的初始化列表一次性插入多个元素。
  map.insert({{"spam", 1}, {"eggs", 2}, {"garlic rice", 3}});

  // 也可以使用类似数组的语法插入元素，即使该元素之前不存在。
  map["bacon"] = 5;

  // 同样，也可以用相同语法更新 unordered_map 中的元素。
  map["spam"] = 15;

  // find 函数用于在 unordered_map 中查找元素。
  // 如果元素存在，它返回指向该元素的迭代器；否则返回指向容器末端的迭代器。
  std::unordered_map<std::string, int>::iterator result = map.find("jignesh");
  if (result != map.end()) {
    // 这是从迭代器访问键/值对的一种方式。
    std::cout << "Found key " << result->first << " with value "
              << result->second << std::endl;

    // 解引用迭代器是访问键/值对的另一种方法。
    std::pair<std::string, int> pair = *result;
    std::cout << "DEREF: Found key " << pair.first << " with value "
              << pair.second << std::endl;
  }

  // count 函数返回 unordered_map 中具有指定 key 的元素个数。
  size_t count = map.count("spam");
  if (count == 1) {
    std::cout
        << "A key-value pair with key spam exists in the unordered map.\n";
  }

  // erase 函数用于从 unordered_map 中删除值。它可以接受一个 key 作为参数。
  map.erase("eggs");

  // 确认 eggs/2 这个键值对不再存在于 map 中。
  if (map.count("eggs") == 0) {
    std::cout << "Key-value pair with key eggs does not exist in the unordered "
                 "map.\n";
  }

  // 此外，如果想删除某个位置的元素，可以向 erase 传入一个迭代器。
  // 下面代码会删除键为 "garlic rice" 的键值对。注意 std::next 是一个迭代器工具函数，
  // 它返回传入迭代器的下一个位置（后继迭代器）。
  map.erase(map.find("garlic rice"));

  // 确认 garlic rice/3 键值对不再存在。
  if (map.count("garlic rice") == 0) {
    std::cout << "Key-value pair with key garlic rice does not exist in the "
                 "unordered map.\n";
  }

  // 我们可以通过 unordered_map 的迭代器来遍历其元素。不能通过任何索引方式来迭代 unordered_map。
  std::cout << "Printing the elements of the iterator:\n";
  for (std::unordered_map<std::string, int>::iterator it = map.begin();
       it != map.end(); ++it) {
    // 通过解引用迭代器访问元素本身。
    std::cout << "(" << it->first << ", " << it->second << "), ";
  }
  std::cout << "\n";

  // 和 std::vector 一样，也可以使用范围 for（for-each）遍历 unordered_map。
  std::cout << "Printing the elements of the iterator with a for-each loop:\n";
  for (const std::pair<const std::string, int> &elem : map) {
    std::cout << "(" << elem.first << ", " << elem.second << "), ";
  }
  std::cout << "\n";

  // 关于更风格化、可读性更好的遍历 C++ STL 容器的方法，请参见 auto.cpp！有兴趣的话可以去看看。

  return 0;
}

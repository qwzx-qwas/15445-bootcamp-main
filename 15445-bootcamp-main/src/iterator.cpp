/**
 * @file iterator.cpp
 * @author Abigale Kim (abigalek)
 * @brief 迭代器使用与实现的教程代码。
 */

// C++ 迭代器是指向容器内某个元素的对象。
// 它们可用于遍历该容器的元素。
// 一个你已经熟悉的迭代器例子是指针。指针可以用于遍历 C 风格数组。看下面的
// C 风格代码片段：
// int *array = malloc(sizeof(int) * 10);
// int *iter = array;
// int zero_elem = *iter;
// iter++;
// int first_elem = *iter;
// 如上所示，++ 操作符可用于遍历 C 风格数组，解引用操作符返回迭代器所指向的值。

// C++ 迭代器的主要组成是两个核心操作符。
// 迭代器上的解引用操作符 (*) 应返回迭代器当前位置元素的值。
// ++（递增）操作符应将迭代器的位置加 1。如上所示，指针用来遍历 C 风格数组时满足该行为。

// 关于如何在 C++ STL 容器中使用迭代器访问元素的示例，请参见 vectors.cpp、sets.cpp、
// unordered_maps.cpp 和 auto.cpp。这是因为在 C++ 中使用迭代器访问和修改 STL 容器的元素是良好风格，值得在这些文件中提及。

// 本文件主要关注迭代器的实现。我们通过实现一个简单的双向链表（DLL）迭代器来演示如何实现 C++ 迭代器。

// 包含用于演示打印的 std::cout。
#include <iostream>

// 下面是 Node 结构体的定义，用于我们的双向链表（DLL）。
struct Node {
  Node(int val): next_(nullptr), prev_(nullptr), value_(val) {}

  Node* next_;
  Node* prev_;
  int value_;
};

// 该类为双向链表（DLL）实现了一个 C++ 风格的迭代器类。
// 构造函数接收标记迭代起始位置的节点。它还实现了若干运算符用于递增迭代器
// （即访问 DLL 中的下一个元素）以及通过比较 curr_ 指针判断两个迭代器是否相等。
class DLLIterator {
  public:
    DLLIterator(Node* head) 
      : curr_(head) {}

    // 实现前缀递增操作符 (++iter)。运算符重载
    DLLIterator& operator++() {
      curr_ = curr_->next_;
      return *this;
    }

    // 实现后缀递增操作符 (iter++)。前缀与后缀递增的区别在于返回值。
    // 前缀操作返回递增后的迭代器，而后缀操作返回递增前的迭代器。
    DLLIterator operator++(int) {
      DLLIterator temp = *this;
      ++*this;
      return temp;
    }

    // DLLIterator 的相等比较运算符。
    // 通过比较当前指针是否相同来判断。
    bool operator==(const DLLIterator &itr) const {
      return itr.curr_ == this->curr_;
    }

    // DLLIterator 的不等比较运算符。
    // 通过比较当前指针是否不同来判断。
    bool operator!=(const DLLIterator &itr) const {
      return itr.curr_ != this->curr_;
    }

    // DLLIterator 的解引用操作符。
    // 返回迭代器当前位置元素的值。当前位置由 curr_ 标记，可通过其 value 字段访问值。
    int operator*() {
      return curr_->value_;
    }

  private:
    Node* curr_;
};                                                                                              

// 这是双向链表（DLL）的基本实现。它还包含 Begin 和 End 迭代器函数，
// 用于返回可用于遍历该 DLL 实例的 DLLIterator。
class DLL {
  public:
    // DLL 构造函数。
    DLL(): head_(nullptr), size_(0) {}
  
    // 析构函数应遍历并删除所有节点以释放内存。
    ~DLL() {
      Node *current = head_;
      while(current != nullptr) {
        Node *next = current->next_;
        delete current;
        current = next;
      }
      head_ = nullptr;
    }

    // 在链表头插入值 val 的函数。
    void InsertAtHead(int val) {
      Node *new_node = new Node(val);
      new_node->next_ = head_;

      if (head_ != nullptr) {
        head_->prev_ = new_node;
      }

      head_ = new_node;
      size_ += 1;
    }

    // Begin() 返回指向 DLL 头节点的迭代器，
    // 它是遍历时第一个要访问的元素。
    DLLIterator Begin() {
      return DLLIterator(head_);
    }

    // End() 返回标记“尾后”（one-past-the-last）位置的迭代器。
    // 在本例中，该迭代器的 curr_ 指针为 nullptr。
    DLLIterator End() {
      return DLLIterator(nullptr);
    }

    Node* head_{nullptr};
    size_t size_;
};

// main 函数演示 DLL 迭代器的用法。
int main() {
  // 创建 DLL 并插入元素。
  DLL dll;
  dll.InsertAtHead(6);
  dll.InsertAtHead(5);
  dll.InsertAtHead(4);
  dll.InsertAtHead(3);
  dll.InsertAtHead(2);
  dll.InsertAtHead(1);

  // 我们可以通过前缀和后缀递增运算符来遍历 DLL。
  std::cout << "Printing elements of the DLL dll via prefix increment operator\n";
  for (DLLIterator iter = dll.Begin(); iter != dll.End(); ++iter) {
    std::cout << *iter << " ";
  }
  std::cout << std::endl;

  std::cout << "Printing elements of the DLL dll via postfix increment operator\n";
  for (DLLIterator iter = dll.Begin(); iter != dll.End(); iter++) {
    std::cout << *iter << " ";
  }
  std::cout << std::endl;

  return 0;
}

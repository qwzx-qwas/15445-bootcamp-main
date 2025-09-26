/**
 * @file mutex.cpp
 * @author Abigale Kim (abigalek)
 * @brief C++ STL 中 mutex 的示例代码。
 */

// 本程序展示 std::mutex 的简单使用示例。std::mutex 类提供互斥量同步原语。

// 包含 std::cout（用于演示打印）。
#include <iostream>
// 包含互斥量库头文件。
#include <mutex>
// 包含线程库头文件。
#include <thread>

// 定义一个全局计数变量和一个供两个线程共享使用的互斥量。
int count = 0;

// 这是声明并默认初始化互斥量的语法。
std::mutex m;

// add_count 函数允许线程以原子方式将 count 变量增加 1。
void add_count() {
  // 在访问共享资源 count 之前获取锁。
  m.lock();
  count += 1;
  // 在访问共享资源 count 之后释放锁。
  m.unlock();
}

// main 函数构造两个线程对象并让它们并行运行 add_count 函数。
// 这些线程执行完毕后，我们打印 count 的值，展示两次递增都成功了。
// std::thread 库是用于构造线程的 C++ STL 库，可以视为 C 语言中 pthread 库的 C++ 等价物。
int main() {
  std::thread t1(add_count);
  std::thread t2(add_count);
  t1.join();
  t2.join();

  std::cout << "Printing count: " << count << std::endl;
  return 0;
}

// 注意：上面的代码有个问题。如果 add_count 函数在 m.lock() 和 m.unlock() 之间抛出异常，
// 那么 m.unlock() 就不会被调用，导致互斥量永远被锁定，从而引发死锁。
// 更好的做法是使用 std::lock_guard，它在析构时会自动释放锁，从而避免死锁问题。
// 相关示例请参见 lock_guard.cpp。

/**
 * @file scoped_lock.cpp
 * @author Abigale Kim (abigalek)
 * @brief C++ STL 中 std::scoped_lock 的教学示例。
 */

// 本程序演示了 std::scoped_lock 的一个小例子。
// std::scoped_lock 是对 mutex 的封装类，提供 RAII 风格的获取和释放锁的方式。
// 也就是说对象构造时获取锁，析构时释放锁。

// 包含 std::cout（用于示例输出）。
#include <iostream>
// 包含 mutex 头文件。
#include <mutex>
// 包含 thread 头文件。
#include <thread>

// 定义一个全局计数变量和一个供线程使用的 mutex。
int count = 0;
std::mutex m;

// add_count 函数允许线程以原子方式将 count 变量增加 1。
void add_count() {
  // std::scoped_lock 的构造会获取互斥锁 m。
  std::scoped_lock slk(m);
  count += 1;

  // 当 add_count 函数结束，slk 对象超出作用域，其析构函数会释放 mutex m。
}

// main 函数与 mutex.cpp 中的相同。它构造线程对象，在两个线程上运行 add_count，并在执行后打印 count 的结果。
int main() {
  std::thread t1(add_count);
  std::thread t2(add_count);
  t1.join();
  t2.join();

  std::cout << "Printing count: " << count << std::endl;
  return 0;
}

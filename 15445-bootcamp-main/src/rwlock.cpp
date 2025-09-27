/**
 * @file rwlock.cpp
 * @author Abigale Kim (abigalek)
 * @brief 关于 C++ STL 中 std::shared_lock 和 std::unique_lock 的示例代码
 *        （尤其是作为读写锁（RWLocks）使用的场景）。
 */

// 虽然 C++ 没有专门的读写锁库，但可以通过 std::shared_mutex、std::shared_lock 和 std::unique_lock 来模拟读写锁。
// 本程序给出一个小例子说明如何实现。

// std::shared_mutex 是一种既支持共享（只读）锁又支持独占（写）锁的互斥体。
// std::shared_lock 可用作 RAII 风格的读锁，std::unique_lock 可用作 RAII 风格的写锁。
// 有关 RAII 风格加锁，请参见 scoped_lock.cpp。

// 如果想复习读写锁的概念以及 reader-writers 问题，可参考以下讲义：
// https://www.cs.cmu.edu/afs/cs/academic/class/15213-s23/www/lectures/25-sync-advanced.pdf

// 包含 std::cout（用于示例打印）。
#include <iostream>
// 包含 mutex 头文件。
#include <mutex>
// 包含 shared_mutex 头文件。
#include <shared_mutex>
// 包含 thread 头文件。
#include <thread>
#include <string>

// 定义一个全局 count 变量和一个供所有线程使用的 shared mutex。
// std::shared_mutex 既支持共享锁也支持独占锁。
int count = 0;
std::shared_mutex m;

// 这个函数使用 std::shared_lock（相当于读者锁）来获得对 count 的只读共享访问，并读取该变量。
void read_value() {
  std::shared_lock lk(m);
  std::cout << "Reading value " + std::to_string(count) + "\n" << std::flush;
}

// 这个函数使用 std::unique_lock（相当于写者锁）来获得对 count 的独占访问并写入。
void write_value() {
  std::unique_lock lk(m);
  count += 3;
}

// main 构造了六个线程对象，其中两个运行 write_value，四个运行 read_value，全部并行执行。
// 因此输出并非确定性的，取决于哪个线程先获取锁。多运行几次，观察是否得到不同输出。
int main() {
  std::thread t1(read_value);
  std::thread t2(write_value);
  std::thread t3(read_value);
  std::thread t4(read_value);
  std::thread t5(write_value);
  std::thread t6(read_value);

  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
  t6.join();

  return 0;
}

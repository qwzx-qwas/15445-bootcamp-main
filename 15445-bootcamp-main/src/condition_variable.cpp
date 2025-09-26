/**
 * @file condition_variable.cpp
 * @author Abigale Kim (abigalek)
 * @brief C++ STL 中 condition variable 的教学示例。
 */

// 本程序演示了 std::condition_variable 的一个小示例。
// std::condition_variable 提供条件变量这一同步原语。条件变量允许线程在获取互斥锁前等待某个特定条件成立。
// 其他线程可以通知正在等待的线程，提示该条件可能已满足。

// 有关 C 风格条件变量的更详细介绍，请参见:
// https://pages.cs.wisc.edu/~remzi/OSTEP/threads-cv.pdf

// 程序启动三个线程。其中两个线程运行一个函数，该函数以原子方式将全局 count 变量加 1，
// 并在 count 变为 2 时通知等待线程。等待线程在 count 等于 2 时被唤醒，获取锁并打印 count 值。

// 包含 condition_variable 头文件。
#include <condition_variable>
// 包含 std::cout（用于演示输出）。
#include <iostream>
// 包含 mutex 头文件。
#include <mutex>
// 包含 thread 头文件。
#include <thread>

// 定义一个全局的 count 变量、用于保护的 mutex，以及供线程间通信使用的 condition variable。
int count = 0;
std::mutex m;

// 这是声明并默认初始化 condition_variable 的语法。
std::condition_variable cv;

// 在此函数中，线程将 count 增加 1。如果 count 的值变为 2，将通知一个等待的线程。
// 该函数由 main 中的两个线程并发执行。
void add_count_and_notify() {
  std::scoped_lock slk(m);
  count += 1;
  if (count == 2) {
    cv.notify_one();     //随机通知cv上等待的一个线程
  }
}

// 由等待线程运行的函数，等待条件 count == 2 成立。随后它获取互斥锁 m 并在临界区内执行代码。
// condition_variable 需要一个 std::unique_lock 对象来构造。
// std::unique_lock 是 C++ STL 中的一种同步原语，提供比 std::lock_guard 更灵活的功能，
// 例如可以与 condition_variable 配合使用。它是可移动的，但不可拷贝构造或拷贝赋值。
void waiter_thread() {
  std::unique_lock lk(m);
  cv.wait(lk, []{return count == 2;});    //如果线程被通知但条件count != 2,则继续等待
  

  std::cout << "Printing count: " << count << std::endl;
}

// main 函数构造三个线程对象，其中两个并行运行 add_count_and_notify。
// 在这些线程执行完毕后，等待线程会打印 count 值，证明两个增加操作及等待线程的条件获取都已成功。
int main() {
  std::thread t1(add_count_and_notify);
  std::thread t2(add_count_and_notify);
  std::thread t3(waiter_thread);
  t1.join();
  t2.join();
  t3.join();
  return 0;
}

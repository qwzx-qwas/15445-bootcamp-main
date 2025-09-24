/**
 * @file templated_classes.cpp
 * @author Abigale Kim (abigalek)
 * @brief 模板类的教程代码。
 */

// 包含 std::cout（用于打印）。
#include <iostream>

// 模板也可用于实现类。例如，这里有一个基本的模板类，保存一个模板类型的元素，
// 调用 print 时会打印该元素。
template<typename T>
class Foo {
  public:
    Foo(T var) : var_(var) {}
    void print() {
      std::cout << var_ << std::endl;
    }
  private:
    T var_;
};

// 也可以通过模板向类传入多个类型参数。例如，这是另一个基本的模板类，保存两个
// 模板类型的元素，调用 print 时会打印它们。
template<typename T, typename U> 
class Foo2 {
  public:
    Foo2(T var1, U var2) 
      : var1_(var1)
      , var2_(var2) {}
    void print() {
      std::cout << var1_ << " and " << var2_ << std::endl;
    }
  private:
    T var1_;
    U var2_;
};

// 也可以创建模板类的特化，对不同类型做不同处理。下面是一个人为的例子：当模板类型不是
// float 时，print 输出存储的变量值；当实例化为 float 时，print 输出 "hello float" 和
// 存储在 var_ 字段的变量。
template<typename T>
class FooSpecial {
  public:
    FooSpecial(T var) : var_(var) {}
    void print() {
      std::cout << var_ << std::endl;
    }
  private:
    T var_;
};

// 针对 float 类型的模板类特化。
template<>
class FooSpecial<float> {
  public:
    FooSpecial(float var) : var_(var) {}
    void print() {
      std::cout << "hello float! " << var_ << std::endl;
    }
  private:
    float var_;
};

// 模板参数不必是类型，也可以是值！
template<int T>
class Bar {
  public: 
    Bar() {}
    void print_int() {
      std::cout << "print int: " << T << std::endl;
    }
};

int main() {
  // 首先，从模板类构造对象。Foo 模板用 int 参数实例化，会使 a 的类型为 Foo<int>。
  // a 的 print 函数按预期工作。
  Foo<int> a(3);
  std::cout << "Calling print on Foo<int> a(3): ";
  a.print();

  // 模板类也可以根据构造参数推导类型。如果你是初学者，不确定要实例化的类型，
  // 最好慎用此特性。
  Foo b(3.4f);
  std::cout << "Calling print on Foo b(3.4f): ";
  b.print();

  // 其次，构造一个带有多个类型参数的模板类对象。
  Foo2<int, float> c(3, 3.2f);
  std::cout << "Calling print on Foo2<int, float> c(3, 3.2f): ";
  c.print();

  // 演示对 FooSpecial 使用有无 float 类型参数实例化时的行为。对 d 调用 print 时输出变量而非
  // "hello float"。对 e（FooSpecial<float> 实例）调用时会输出 "hello float!"。
  FooSpecial<int> d(5);
  std::cout << "Calling print on FooSpecial<int> d(5): ";
  d.print();

  FooSpecial<float> e(4.5);
  std::cout << "Calling print on FooSpecial<float> e(4.5): ";
  e.print();

  // 最后，演示用非类型模板参数构造对象时的行为。
  Bar<150> f;
  std::cout << "Calling print_int on Bar<150> f: ";
  f.print_int();

  // 再次提示，这些示例是人为构造的，但理解它们仍然很重要：在 Bustub 代码库中会看到
  // 类似的代码，因此理解模板类在这些场景下的用法很有帮助。

  return 0;
}

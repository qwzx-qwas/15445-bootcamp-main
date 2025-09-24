/**
 * @file namespaces.cpp
 * @author Abigale Kim (abigalek)
 * @brief 演示命名空间用法的示例代码。
 */

// 命名空间为标识符（函数名、类型、变量名）提供作用域。它们用于将代码组织成逻辑组（例如一个库可能就是一个命名空间）。
// 命名空间还能防止不同标识符之间的命名冲突。例如，C++ 标准库使用 std 命名空间。这就是为什么 C++ 中的输出函数是
// std::cout，因为 cout 在 std 命名空间中声明。C++ 使用 :: 操作符进行作用域解析，因此可以区分某个函数、类型或类属于哪个命名空间。

// 在此文件中，我们将介绍命名空间、命名空间语法、using 关键字，以及如何从其他命名空间调用函数。

// 包含 std::cout（用于演示输出）。
#include <iostream>

// 这是声明命名空间的语法。
namespace ABC {
  // 在 ABC 命名空间中定义了函数 spam。第 57 行会使用它。
  void spam(int a) {
    std::cout << "Hello from ABC::spam: " << a << std::endl;
  }

  // namespace DEF 是一个嵌套命名空间，因为它在命名空间 ABC 内部声明。嵌套命名空间的语法与非嵌套命名空间相同。
  namespace DEF {
    // 在 ABC::DEF 命名空间内定义函数 bar。
    void bar(float a) {
      std::cout << "Hello from ABC::DEF::bar: " << a << std::endl;
    }

    // 在 ABC::DEF 命名空间内定义函数 uses_bar。由于 bar 与 uses_bar 在同一命名空间中，
    // 在 uses_bar 中直接通过名称 bar 来引用它即可。
    void uses_bar(float a) {
      std::cout << "Hello from uses_bar: ";
      bar(a);
    }

    // 在 ABC::DEF 命名空间中定义函数 uses_spam。要在 ABC::DEF 命名空间中引用 ABC::spam，
    // 必须使用其完整标识符 ABC::spam。若直接使用 spam，则会编译错误（找不到 spam 或 ABC::DEF::spam）。
    // 注意可以使用完整标识符引用任何函数，但这样写会降低编码效率。
    void uses_spam(int a) {
      std::cout << "Hello from uses_spam: ";
      ABC::spam(a);

      // 尝试取消注释下面这行代码（调用 spam(a)），会导致编译错误。
      // spam(a);
    }
  }

  // 在 ABC 命名空间中（但不是在 DEF 内）定义函数 uses_DEF_bar。由于 bar 位于 DEF 命名空间，
  // 在 uses_DEF_bar 中通过 DEF::bar 来引用它（区别命名空间）。
  void uses_DEF_bar(float a) {
    std::cout << "Hello from uses_DEF_bar: ";
    DEF::bar(a);
  }
}

// 命名空间 A 和 B 都有一个名为 foo 的函数，参数和返回值相同。代码可以编译，因为两者的完整标识符不同：A::foo 与 B::foo。
namespace A {
  void foo(int a) {
    std::cout << "Hello from A::foo: " << a << std::endl;
  }
}

namespace B {
  void foo(int a) {
    std::cout << "Hello from B::foo: " << a << std::endl;
  }

  void peloton(int a) {
    std::cout << "Hello from B::peloton: " << a << std::endl;
  }
}

namespace C {
  void eggs(int a) {
    std::cout << "Hello from C::eggs: " << a << std::endl;
  }
}


// using 关键字的一个用途是将整个命名空间引入当前作用域。下面这条语句会把命名空间 B 引入当前作用域。
// 这意味着在该行以下的代码中可以直接使用 foo 来表示 B::foo。在 main 中我们会看到可以既用 B::foo 也用 foo 调用它。
using namespace B;

// using 关键字的另一个用途是将命名空间的特定成员引入当前作用域。下面这条语句会把 C::eggs 引入当前作用域。
// 这意味着在该行以下的代码中可以直接使用 eggs 来表示 C::eggs。
using C::eggs;

int main() {
  // 下面这行调用函数 spam（第 25 行）。直接调用 spam(2) 不行，因为没有名为 spam 的函数，只有 ABC::spam。
  ABC::spam(2);

  // 下面这行调用函数 bar。
  ABC::DEF::bar(4.45);

  // 下面这行调用 uses_bar。正如预期，uses_bar 会打印 "Hello from uses_bar"，然后调用 ABC::DEF::bar。
  ABC::DEF::uses_bar(6.45);

  // 下面这行调用 uses_spam。正如预期，uses_spam 会打印 "Hello from uses_spam"，然后调用 ABC::spam。
  ABC::DEF::uses_spam(37);

  // 下面这行调用 uses_DEF_bar。正如预期，uses_DEF_bar 会打印 "Hello from uses_DEF_bar"，然后调用 ABC::DEF::bar。
  ABC::uses_DEF_bar(3.12);

  // 现在讨论两个 foo 函数。A::foo 和 B::foo 是不同的函数，但允许共存，因为它们有不同的完整标识符。
  A::foo(122);
  B::foo(150);

  // 但是，由于第 106 行将命名空间 B 引入了当前作用域，可以不加 B:: 前缀直接访问 B 命名空间中的内容。
  // 因此可以直接用 foo(440) 来调用 B::foo。
  foo(440);

  // 同样，因为整个 B 命名空间被引入当前作用域，也可以用 peloton 代替 B::peloton。
  peloton(721);

  // 请记住，将整个命名空间用 using 引入当前作用域有风险，可能导致命名冲突。因此不推荐滥用。
  // 更推荐只引入命名空间的特定成员，例如第 111 行的示例，此处可直接使用 eggs 代替 C::eggs。
  eggs(999);

  return 0;
}

#include <fmt/core.h>

int main() {
    int x = 42;

    // fmt::print 输出到控制台
    fmt::print("Hello, fmt! x = {}\n", x);

    // fmt::format 返回字符串
    auto s = fmt::format("Formatted string: {}\n", x);
    fmt::print(s);

    return 0;
}

#include <algorithm>
#include <format>
#include <iostream>
#include <string>

// (这里需要上面定义的 int128_to_string 函数)
std::string int128_to_string(__int128_t n) {
  // ... (同方法二.B) ...
  if (n == 0) return "0";
  std::string s;
  bool is_negative = false;
  if (n < 0) {
    is_negative = true;
    n = -n;
  }
  __uint128_t val = n;
  while (val > 0) {
    s += (char)('0' + (val % 10));
    val /= 10;
  }
  if (is_negative) s += '-';
  std::reverse(s.begin(), s.end());
  return s;
}

// 为 __int128_t 特化 std::formatter
template <>
struct std::formatter<__int128_t> {
  // parse 函数：用于解析格式说明符（例如 {} 里的 :x, :d, :010）
  // 这个简化版本不支持任何说明符，所以 parse 是空的。
  template <typename ParseContext>
  constexpr auto parse(ParseContext& ctx) {
    return ctx.begin();  // 指向 '}'
  }

  // format 函数：执行实际的格式化
  template <typename FormatContext>
  auto format(__int128_t val, FormatContext& ctx) const {
    // 1. 转换
    std::string s = int128_to_string(val);

    // 2. 写入输出迭代器
    // 这是一个简化的实现。
    // 高性能的实现会直接计算并写入 ctx.out()，而不是创建临时的 std::string。
    return std::ranges::copy(s, ctx.out()).out;
  }
};
__int128_t readInt() {
  std::string s;
  std::cin >> s;
  reverse(s.begin(), s.end());
  __int128_t x = 0;
  for (auto c : s) x = x * 10 + (c - '0');
  return x;
}

int main() {
  __int128_t large_val = 1;
  large_val = (large_val << 100) + 12345;

  // 现在你可以直接格式化 __int128_t 了！
  std::string s = std::format("Direct format: {}", large_val);

  std::cout << s << std::endl;
}
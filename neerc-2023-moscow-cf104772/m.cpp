%:include "utility/nd_array.h"
bool isvowel(char c) {
  // clang-format off
  return
    c == 'a' or
    c == 'e' or
    c == 'i' or
    c == 'o' or
    c == 'u' or
    c == 'y';
  // clang-format on
}
%:include "main.h"
SOLVE() {
  string s, f;
  cin >> s >> f;
  transform(begin(s), end(s), begin(s), [](char c) { return tolower(c); });
  transform(begin(f), end(f), begin(f), [](char c) { return tolower(c); });
  nd_array<char, 2> dp(size(s) + 1, size(f) + 1);
  dp(0, 0) = true;
  for (int i = 0; i <= size(s); i++) {
    for (int j = 0; j <= size(f); j++) {
      if (j < size(f) and isvowel(f[j])) {
        dp(i, j + 1) |= dp(i, j);
      }
      if (i < size(s) and j < size(f) and s[i] == f[j]) {
        dp(i + 1, j + 1) |= dp(i, j);
      }
    }
  }
  cout << (dp(size(s), size(f)) ? "Same" : "Different") << nl;
}

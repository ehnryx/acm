#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';
using ll = long long;

int main(int argc, char** argv) {
  cin.tie(0)->sync_with_stdio(0);

  const vector<int> length {
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
  };
  assert(length.size() == 12);

  int ans = 0;
  int day = 1;
  for (int year = 1900; year <= 2000; year++) {
    for (int month = 0; month < 12; month++) {
      if (year > 1900 && day == 0) {
        ans++;
      }
      day += length[month];
      if (length[month] == 28 && (year % 4 == 0 && (year % 400 == 0 || year % 100 != 0))) {
        day += 1; // leap years >.<
      }
      day %= 7;
    }
  }
  cout << ans << nl;

  return 0;
}

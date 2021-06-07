#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';
using ll = long long;

const vector<pair<int, string>> num_to_word = {
  {1, "one"},
  {2, "two"},
  {3, "three"},
  {4, "four"},
  {5, "five"},
  {6, "six"},
  {7, "seven"},
  {8, "eight"},
  {9, "nine"},
  {10, "ten"},
  {11, "eleven"},
  {12, "twelve"},
  {13, "thirteen"},
  {14, "fourteen"},
  {15, "fifteen"},
  {16, "sixteen"},
  {17, "seventeen"},
  {18, "eighteen"},
  {19, "nineteen"},
  {20, "twenty"},
  {30, "thirty"},
  {40, "forty"},
  {50, "fifty"},
  {60, "sixty"},
  {70, "seventy"},
  {80, "eighty"},
  {90, "ninety"},
  {100, "hundred"},
  {1000, "thousand"},
};
const map<int, string> word(begin(num_to_word), end(num_to_word));

int solve(int n) {
  if (n == 0) return 0;
  if (n < 20) return word.at(n).size();
  if (n < 100) {
    int tens = n / 10 * 10;
    return word.at(tens).size() + solve(n % 10);
  }
  if (n < 1000) {
    int huns = n / 100;
    return word.at(huns).size() + word.at(100).size()
      + /*and*/(n % 100 ? 3 : 0) + solve(n % 100);
  }
  assert(n == 1000);
  return word.at(1).size() + word.at(1000).size();
}

int main(int argc, char** argv) {
  cin.tie(0)->sync_with_stdio(0);

  int ans = 0;
  for (int i = 1; i <= 1000; i++) {
    ans += solve(i);
  }
  cout << ans << nl;

  return 0;
}

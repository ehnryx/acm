#include <bits/stdc++.h>
using namespace std;


const char nl = '\n';
using ll = long long;
using ld = long double;

const int N = 160;

bitset<N> decode(const string& s, int k) {
  bitset<N> res;
  for (int j = 0; j < 4 * k; j++) {
    int digit = isdigit(s[j / 4]) ? s[j / 4] - '0' : s[j / 4] - 'a' + 10;
    res[j] = digit >> (j % 4) & 1;
  }
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m, k;
  cin >> n >> m >> k;

  vector<bitset<N>> a(n);
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    a[i] = decode(s, k);
  }

  vector<bitset<N>> b(m);
  for (int i = 0; i < m; i++) {
    string s;
    cin >> s;
    b[i] = decode(s, k);
  }

  vector<int> ans(m, -1);
  vector<int> order, basis;
  int zero = -1;
  for (int i = 0; i < n; i++) {
    // find bit
    int bit = -1;
    for (int j = 0; j < 4 * k; j++) {
      if (a[i][j]) {
        bit = j;
      }
    }
    if (bit == -1) {
      if (zero == -1) {
        zero = i + 1;
      }
      continue;
    }

    // add to basis and xor the rest
    order.push_back(bit);
    basis.push_back(i);
    for (int j = i + 1; j < n; j++) {
      if (a[j][bit]) {
        a[j] ^= a[i];
      }
    }

    for (int j = 0; j < m; j++) {
      if (ans[j] > 0 || b[j].count() == 0) continue;
      bitset<N> val = b[j];
      for (int t = 0; t < size(basis); t++) {
        if (val[order[t]]) {
          val ^= a[basis[t]];
        }
      }
      if (val.count() == 0) {
        ans[j] = i + 1;
      }
    }
  }

  for (int i = 0; i < m; i++) {
    cout << (b[i].count() == 0 ? zero : ans[i]) << nl;
  }

  return 0;
}

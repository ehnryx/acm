#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

const int M = 26;

int read_int(const string& s, int& o) {
  int res = 0;
  while(isdigit(s[o])) {
    res = res * 10 + s[o] - '0';
    o++;
  }
  --o; // unread
  return res;
}

int solve(const string& s, int o, vector<int>& val) {
  if(s[o] == '}') return o;

  if(s[o] == '[') {
    int a = s[++o] - 'a';
    ++o; // skip =
    if(isdigit(s[++o])) {
      val[a] = read_int(s, o);
    } else {
      int b = s[o] - 'a';
      ++o; // skip +
      int c = s[++o] - 'a';
      val[a] = val[b] + val[c];
    }
    assert(s[++o] == ']');
    return solve(s, o + 1, val);
  }

  if(s[o] == '<') {
    int b = s[++o] - 'a';
    ++o; // skip =
    int c = s[++o] - 'a';
    if(val[b] != val[c]) {
      return -1;
    }
    assert(s[++o] == '>');
    return solve(s, o + 1, val);
  }

  if(s[o] == '(') {
    int b = s[++o] - 'a';
    ++o; // skip <
    int c = s[++o] - 'a';
    assert(s[++o] == '{');
    if(val[b] < val[c]) {
      // always
      o = solve(s, o + 1, val);
      if(o == -1) return -1;
    } else {
      // never
      for(int open = 1; open > 0; ) {
        if(s[++o] == '{') open++;
        else if(s[o] == '}') open--;
      }
    }
    assert(s[o] == '}');
    assert(s[++o] == ')');
    return solve(s, o + 1, val);
  }

  assert(false); // parse error
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int T;
  cin >> T;
  while(T--) {
    string s;
    cin >> s;
    s.push_back('}');
    string t = s;
    bool ok = true;
    for(int bm=0; bm<1<<10; bm++) {
      for(int i=0, vals=bm; i<size(s); i++) {
        if(s[i] == '?') {
          t[i] = (vals & 1) + '0';
          vals >>= 1;
        } else {
          t[i] = s[i];
        }
      }
      vector<int> val(M);
      if(solve(t, 0, val) == -1) {
        ok = false;
        break;
      }
    }
    if(ok) {
      cout << "ASSERTIONS ALWAYS HOLD" << nl;
    } else {
      cout << "ASSERTIONS INVALID" << nl;
    }
  }

  return 0;
}

//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int T;
  cin >> T;
  while(T--) {
    string s;
    cin >> s;
    {
      string t;
      int last = -1;
      int cnt = 0;
      for(int i=0; i<s.size(); i++) {
        if(s[i] <= '2') {
          cnt += s[i] - '0';
        } else {
          for(int j=last+1; j<i; j++) {
            t.push_back(s[j]);
          }
          if(cnt % 4 != 0) {
            t.push_back('2');
          }
          t.push_back(s[i]);
          cnt = 0;
          last = i;
        }
      }
      for(int j=last+1; j<s.size(); j++) {
        t.push_back(s[j]);
      }
      int sum = accumulate(t.begin(), t.end(), 0, [](int c, char v) {
        return c + v-'0';
      });
      if(cnt % 4 != 0 && __builtin_popcount(sum) > 1) {
        t.push_back('2');
      }
      s = move(t);
    }
    {
      string t;
      int last = -1;
      int cnt = 0;
      for(int i=0; i<s.size(); i++) {
        if(s[i] <= '4') {
          cnt += s[i] - '0';
        } else {
          for(int j=last+1; j<i; j++) {
            t.push_back(s[j]);
          }
          if(cnt % 8 != 0) {
            t.push_back('4');
          }
          t.push_back(s[i]);
          cnt = 0;
          last = i;
        }
      }
      for(int j=last+1; j<s.size(); j++) {
        t.push_back(s[j]);
      }
      int sum = accumulate(t.begin(), t.end(), 0, [](int c, char v) {
        return c + v-'0';
      });
      if(cnt % 8 != 0 && __builtin_popcount(sum) > 1) {
        t.push_back('4');
      }
      s = move(t);
    }
    int sum = accumulate(s.begin(), s.end(), 0, [](int c, char v) {
      return c + v-'0';
    });
    if(__builtin_popcount(sum) > 1) {
      assert(sum % 8 == 0);
      while(__builtin_popcount(sum) > 1) {
        sum += 8;
        s.push_back('8');
      }
    }
    assert(__builtin_popcount(sum) == 1);
    cout << s << nl;
  }

  return 0;
}

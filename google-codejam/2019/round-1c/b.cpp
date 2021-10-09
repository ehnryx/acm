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
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

char query(const string& cur, vector<int>& v, int j, int g) {
  vector<int> cnt(5);
  vector<char> res(120);
  for(int i : v) {
    cout << i*5 + j << endl;
    cin >> res[i];
    if(res[i] == 'N') exit(0);
    cnt[res[i]-'A']++;
  }
  for(int i=0; i<5; i++) {
    if(cur.find(i+'A') != -1) continue;
    if(cnt[i] == g) {
      vector<int> out;
      for(int k : v) {
        if(res[k] == i+'A') {
          out.push_back(k);
        }
      }
      assert(out.size() == g);
      v = move(out);
      return i+'A';
    }
  }
  assert(false);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int T, _;
  cin >> T >> _;
  while(T--) {
    string ans;
    vector<int> vec(119);
    iota(vec.begin(), vec.end(), 0);
    ans.push_back(query(ans, vec, 1, 23));
    ans.push_back(query(ans, vec, 2, 5));
    ans.push_back(query(ans, vec, 3, 1));
    ans.push_back(query(ans, vec, 4, 0));
    for(char c='A'; c<='E'; c++) {
      if(ans.find(c) == -1) {
        ans.push_back(c);
      }
    }
    cout << ans << endl;
    char c; cin >> c;
    if(c == 'N') exit(0);
  }

  return 0;
}

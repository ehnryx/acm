#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  string s;
  cin >> s;
  int n = s.size();

  vector<int> index[26];
  for (int i = 0; i < n; i++) {
    index[s[i]-'a'].push_back(i);
  }
  for (int i = 0; i < 26; i++) {
    index[i].push_back(n);
  }

  stack<int> cur;
  cur.push(-1);

  int q;
  cin >> q;
  for (int i = 0; i < q; i++) {
    string t;
    char c;
    cin >> t;

    if (t == "push") {
      cin >> c;
      auto it = upper_bound(index[c-'a'].begin(), index[c-'a'].end(), cur.top());
      if (it == index[c-'a'].end()) cur.push(n);
      else cur.push(*it);
    } else {
      cur.pop();
    }

    cout << (cur.top() == n ? "NO" : "YES") << nl;
  }

  return 0;
}

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
#define nl '\n'

const ll MOD = 1e9+7;
const ll b = 1789;
const ll a = 12409;
const ll c = 22381;

struct Set {
  set<ll> ch;
  Set() {}
  ll get_hash() const {
    ll hsh = 0;
    ll pw = 1;
    for (auto& x : ch) {
      hsh = (hsh+x*pw)%MOD;
      pw = pw*a%MOD;
    }
    hsh = (hsh*b+c)%MOD;
    return hsh;
  }
};

void solve() {
  int n;
  cin >> n;
  stack<Set> sta;
  for (int i=0; i<n; ++i) {
    string s;
    cin >> s;
    if (s[0] == 'P') {
      sta.push(Set());
    } else if (s[0] == 'D') {
      sta.push(sta.top());
    } else if (s[0] == 'U') {
      Set s1 = sta.top(); sta.pop();
      Set s2 = sta.top(); sta.pop();
      for (auto& x : s2.ch) {
        s1.ch.insert(x);
      }
      sta.push(s1);
    } else if (s[0] == 'I') {
      Set s1 = sta.top(); sta.pop();
      Set s2 = sta.top(); sta.pop();
      set<ll> isec;
      for (auto& x : s1.ch) {
        if (s2.ch.count(x)) {
          isec.insert(x);
        }
      }
      s1.ch = isec;
      sta.push(s1);
    } else if (s[0] == 'A') {
      Set s1 = sta.top(); sta.pop();
      Set s2 = sta.top(); sta.pop();
      s2.ch.insert(s1.get_hash());
      sta.push(s2);
    }
    assert(!sta.empty());
    cout << sta.top().ch.size() << "\n";
    //cerr << endl;
  }
  cout << "***\n";
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int TT;
  cin >> TT;
  while (TT--) {
    solve();
  }

  return 0;
}

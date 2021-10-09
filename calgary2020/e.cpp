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
const ld EPS = 1e-11;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

bool T(int n, vector<int> a, vector<int> b) {
  vector<int> c(n);
  for(int i=0; i<12; i++) {
    transform(a.begin(), a.end(), c.begin(), [=] (int x) {
      return (x + i) % 12;
    });
    if(c == b) return true;
  }
  return false;
}

bool R(int n, vector<int> a, vector<int> b) {
  reverse(a.begin(), a.end());
  return a == b;
}

bool I(int n, vector<int> a, vector<int> b) {
  vector<int> c(n);
  transform(a.begin(), a.end(), c.begin(), [=] (int x) {
    return (2 * a[0] + 12 - x) % 12;
  });
  return c == b;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  unordered_map<string,int> mp;
  mp["C"] = 0;
  mp["C#"] = 1;
  mp["D"] = 2;
  mp["D#"] = 3;
  mp["E"] = 4;
  mp["F"] = 5;
  mp["F#"] = 6;
  mp["G"] = 7;
  mp["G#"] = 8;
  mp["A"] = 9;
  mp["A#"] = 10;
  mp["B"] = 11;

  int n;
  cin >> n;
  vector<int> a(n), b(n);
  for(int i=0; i<n; i++) {
    string s;
    cin >> s;
    a[i] = mp[s];
  }
  for(int i=0; i<n; i++) {
    string s;
    cin >> s;
    b[i] = mp[s];
  }
  if(T(n, a, b)) {
    cout << "Transposition" << nl;
  } else if(R(n, a, b)) {
    cout << "Retrograde" << nl;
  } else if(I(n, a, b)) {
    cout << "Inversion" << nl;
  } else {
    cout << "Nonsense" << nl;
  }

  return 0;
}

//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

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
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const ll M1 = 998244353;
const ll Q1 = 1789;

const ll M2 = 1e9+9;
const ll Q2 = 101;

vector<int> get_ha(const string& s, ll P, ll MOD) {
  int n = s.size();
  ll ha = 0;
  ll pa = 1;
  for(int i=0; i<n; i++) {
    ha = (ha + s[i]*pa) % MOD;
    pa = pa * P % MOD;
  }

  vector<int> out;
  out.push_back(ha);
  for(int i=n-1; i>0; i--) {
    ha = ((ha*P - s[i]*pa + s[i]) % MOD + MOD) % MOD;
    out.push_back(ha);
  }
  return out;
}

vector<tuple<int,int>> get_hashes(string s) {
  vector<int> f1 = get_ha(s, Q1, M1);
  vector<int> f2 = get_ha(s, Q2, M2);
  assert(f1.size() == s.size());
  reverse(s.begin(), s.end());
  vector<int> r1 = get_ha(s, Q1, M1);
  vector<int> r2 = get_ha(s, Q2, M2);

  vector<tuple<int,int>> out;
  for(int i=0; i<s.size(); i++) {
    out.emplace_back(f1[i], f2[i]);
  }
  for(int i=0; i<s.size(); i++) {
    out.emplace_back(r1[i], r2[i]);
  }
  return out;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n;
  cin >> n;
  set<tuple<int,int,int>> have;
  for(int i=0; i<n; i++) {
    string s;
    cin >> s;
    vector<tuple<int,int>> hashes = get_hashes(s);
    for(tuple<int,int> ha : hashes) {
      if(have.count(tuple_cat(tuple<int>(s.size()), ha))) {
        cout << "Yes" << nl;
        return 0;
      }
    }
    for(tuple<int,int> ha : hashes) {
      have.insert(tuple_cat(tuple<int>(s.size()), ha));
    }
  }
  cout << "No" << nl;

  return 0;
}

#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "shuffle"

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
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Vector {
  __int128 a, b;
  Vector(): a(0), b(0) {}
  void set(int i, int v) {
    //assert(get(i) == 0);
    if(i < 18) a |= (__int128)v << (i*6);
    else b |= (__int128)v << ((i-18)*6);
  }
  int get(int i) const {
    if(i < 18) return a >> (i*6) & 0b111111;
    else return b >> ((i-18)*6) & 0b111111;
  }
  bool operator < (const Vector& o) const {
    return a < o.a || (a == o.a && b < o.b);
  }
  bool operator == (const Vector& o) const {
    return a == o.a && b == o.b;
  }
};

struct Single {
  __int128 a;
  Single(): a(0) {}
  void set(int i, int v) {
    a |= (__int128)v << (i*6);
  }
  int get(int i) const {
    return a >> (i*6) & 0b111111;
  }
  bool operator < (const Single& o) const {
    return a < o.a;
  }
};

const int P = 5;
int M[P], L[P], S[P];

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n, t, p;
  cin >> n >> t >> p;

  Vector init, goal;
  for(int i=0; i<n; i++) {
    int x;
    cin >> x;
    init.set(i, x);
  }
  for(int i=0; i<n; i++) {
    int x;
    cin >> x;
    goal.set(i, x);
  }

  for(int i=0; i<p; i++) {
    cin >> M[i] >> L[i];
    S[i] = n - L[i] - M[i];
  }

  vector<pair<Vector,Single>> front, fnxt;
  front.emplace_back(init, Single());
  for(int bs=0; bs<t/2; bs++) {
    fnxt.clear();
    for(const auto& [v, path] : front) {
      for(int i=0; i<p; i++) {
        Vector nv; int j=0;
        for(int k=S[i]; k<S[i]+L[i]; k++) nv.set(j++, v.get(k));
        for(int k=0; k<S[i]; k++) nv.set(j++, v.get(k));
        for(int k=S[i]+L[i]; k<n; k++) nv.set(j++, v.get(k));
        fnxt.emplace_back(nv, path);
        fnxt.back().second.set(bs, i+1);
      }
    }
    swap(front, fnxt);
  }

  vector<pair<Vector,Single>> back, bnxt;
  back.emplace_back(goal, Single());
  for(int bs=0; bs<t-t/2; bs++) {
    bnxt.clear();
    for(const auto& [v, path] : back) {
      for(int i=0; i<p; i++) {
        Vector nv; int j=0;
        for(int k=L[i]; k<S[i]+L[i]; k++) nv.set(j++, v.get(k));
        for(int k=0; k<L[i]; k++) nv.set(j++, v.get(k));
        for(int k=S[i]+L[i]; k<n; k++) nv.set(j++, v.get(k));
        bnxt.emplace_back(nv, path);
        bnxt.back().second.set(t-1 - bs, i+1);
      }
    }
    swap(back, bnxt);
  }

  sort(front.begin(), front.end());
  sort(back.begin(), back.end());
  for(int i=0, j=0; i<front.size(); i++) {
    while(j<back.size() && back[j].first < front[i].first) {
      j++;
    }
    if(j < back.size() && back[j].first == front[i].first) {
      for(int k=0; k<t; k++) {
        cout << max(front[i].second.get(k), back[j].second.get(k)) << " ";
      }
      cout << nl;
      return 0;
    }
  }

  cout << "Impossible" << nl;

  return 0;
}

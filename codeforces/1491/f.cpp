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

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ostream& operator << (ostream& os, const vector<int>& v) {
  os << "[ ";
  for(int it : v) os << it << " ";
  return os << "]";
}

pair<vector<int>,vector<int>> generate(unordered_set<int>& all, pair<int,int> p) {
  while(p.first + p.second > all.size()) {
    if(p.first > p.second) p.first--;
    else p.second--;
  }

  vector<int> perm(all.begin(), all.end());
  shuffle(perm.begin(), perm.end(), rng);
  vector<int> a, b;
  for(int i=0; i<perm.size(); i++) {
    if(i < p.first) {
      a.push_back(perm[i]);
      all.erase(perm[i]);
    } else if(i < p.first + p.second) {
      b.push_back(perm[i]);
      all.erase(perm[i]);
    }
  }
  return pair(a, b);
}

int query(vector<int> a, vector<int> b, int n) {
  assert(!a.empty() && !b.empty());
  assert(a.size() + b.size() <= n);
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());
  vector<int> inter;
  set_intersection(a.begin(), a.end(), b.begin(), b.end(), back_inserter(inter));
  assert(inter.empty());
  assert(a.front() >= 1 && a.back() <= n);
  assert(b.front() >= 1 && b.back() <= n);

  cout << "? " << a.size() << " " << b.size() << nl;
  for(int it : a) {
    cout << it << " ";
  }
  cout << nl;
  for(int it : b) {
    cout << it << " ";
  }
  cout << endl;
  int res;
  cin >> res;
  assert(abs(res) <= n);
  return res;
}

void answer(const vector<int>& a) {
  cout << "! " << a.size() << " ";
  for(int it : a) {
    cout << it << " ";
  }
  cout << endl;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    int g = 31 - __builtin_clz(n);
    unordered_set<int> have;
    for(int i=1; i<=n; i++) {
      have.insert(i);
    }

    int s = sqrt(n);
    int o = (s*(s+1) <= n ? s+1 : s);
    auto [a, b] = generate(have, pair(s, o));
    for(int i=0; i<g; i++) {
      if(query(a, b, n)) break;
      shuffle(a.begin(), a.end(), rng);
      shuffle(b.begin(), b.end(), rng);
      vector<int> na(a.begin(), a.begin() + a.size()/2);
      vector<int> nb(a.begin() + a.size()/2, a.end());
      na.insert(na.end(), b.begin() + b.size()/2, b.end());
      nb.insert(nb.end(), b.begin(), b.begin() + b.size()/2);
      s = nb.size();
      o = na.size();
      tie(a, b) = generate(have, pair(s, o));
      na.insert(na.end(), a.begin(), a.end());
      nb.insert(nb.end(), b.begin(), b.end());
      a = move(na);
      b = move(nb);
    }
    set<int> aset(a.begin(), a.end());
    //cerr << "DONE beginning" << nl;

    vector<int> ans;
    for(int i=1; i<=n; i++) {
      vector<int> unit(1, i);
      if(aset.count(i)) {
        if(query(unit, b, n) == 0) {
          ans.push_back(i);
        }
      } else {
        if(query(unit, a, n) == 0) {
          ans.push_back(i);
        }
      }
    }
    answer(ans);
  }

  return 0;
}

// attempt 7

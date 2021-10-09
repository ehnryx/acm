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
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
  return os << '(' << v.first << ',' << v.second << ')';
}
template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  for (const T& it : v) { os << it << " "; } return os;
}
template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
  os << "{ "; for (const T& it : v) { os << it << " "; }
  return os << '}';
}
template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
  os << "{ "; for (const pair<T,U>& it : v) { os << it << " "; }
  return os << '}';
}

void casesolve();

////////////////////////////////////////////////////////////////////////



int main(int argc, char** argv) {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int T;
  cin >> T;
  for (int cc = 1; cc <= T; cc++) {
    cout << "Case #" << cc << ": ";
    casesolve();
  }

  return 0;
}

////////////////////////////////////////////////////////////////////////



void casesolve() {

  int n, m;
  cin >> n >> m;

  vector<int> v;
  for(int j=0; j<m; j++) {
    for(int i=0; i<n; i++) {
      v.push_back(i);
    }
  }

  vector<pair<int,int>> moves;
  for(;;) {
    int last = 0;
    while(last < n*m && v[last] == v[0]) {
      last++;
    }
    if(last == n*m) break;

    int first = last;
    while(last < n*m && v[last] != v[0]) {
      last++;
    }
    if(last == n*m) break;

    while(last < n*m && v[last] == v[0]) {
      last++;
    }

    if(last < n*m) {
      while(first < n*m && v[first] != v[last]) {
        first++;
      }
      while(first < n*m && v[first] == v[last]) {
        first++;
      }
      assert(first < last);
    }

    vector<int> nxt;
    nxt.insert(nxt.end(), v.begin() + first, v.begin() + last);
    nxt.insert(nxt.end(), v.begin(), v.begin() + first);
    nxt.insert(nxt.end(), v.begin() + last, v.end());
    moves.push_back(make_pair(first, last - first));

    v = move(nxt);
  }

  cout << moves.size() << nl;
  for(const auto& it : moves) {
    cout << it.first << " " << it.second << nl;
  }

  //cerr<<"result: "; for(int it : v) { cerr<<it<<" "; }
  //cerr<<nl;

  return;
}


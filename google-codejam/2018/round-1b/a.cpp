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

const int N = 1e5 + 1;
int need[N];

int rounded(int a, int b) {
  int l = 100 * a / b;
  int r = l+1;
  // 100*a/b - l < r - 100*a/b
  if(100*a - l*b < r*b - 100*a) {
    return l;
  } else {
    return r;
  }
}

ld actual(int a, int b) {
  return (ld)(100*a) / b;
}

void casesolve() {

  int n, m;
  cin >> n >> m;
  for(int i=1; i<=n; i++) {
    if(rounded(i, n) >= actual(i, n)) {
      need[i] = 0;
    } else {
      int j = i+1;
      while(rounded(j, n) < actual(j, n)) {
        j++;
      }
      need[i] = j-i;
    }
  }
  for(int j=1; ; j++) {
    if(rounded(j, n) >= actual(j, n)) {
      need[0] = j;
      break;
    }
  }

  int sum = 0;
  vector<pair<int,int>> p;
  for(int i=0; i<m; i++) {
    int v;
    cin >> v;
    sum += v;
    p.push_back(make_pair(need[v], v));
  }
  sort(p.begin(), p.end());

  int ans = 0;
  for(const auto& it : p) {
    int v = it.second;
    int add = min(n-sum, need[v]);
    v += add;
    sum += add;
    ans += rounded(v, n);
  }
  while(sum < n) {
    int v = 0;
    int add = min(n-sum, need[v]);
    v += add;
    sum += add;
    ans += rounded(v, n);
  }
  cout << ans << nl;

  return;
}


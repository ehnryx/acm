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



void init() {
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  init();

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
int a[N], b[N];

ll solve(int l, int r, int k) {
  if(l > r) return 0;
  int m = (l+r) / 2;

  vector<pair<int,int>> left, right;
  int av, bv;

  av = a[m];
  bv = b[m];
  left.push_back(make_pair(av, bv));
  for(int i=m-1; i>=l; i--) {
    av = max(av, a[i]);
    bv = max(bv, b[i]);
    left.push_back(make_pair(av, bv));
  }
  sort(left.begin(), left.end());

  av = a[m];
  bv = b[m];
  right.push_back(make_pair(av, bv));
  for(int i=m+1; i<=r; i++) {
    av = max(av, a[i]);
    bv = max(bv, b[i]);
    right.push_back(make_pair(av, bv));
  }
  sort(right.begin(), right.end());

  int ln = left.size();
  int rn = right.size();
  ll res = solve(l, m-1, k) + solve(m+1, r, k);

  // left is bigger
  ordered_set<pair<int,int>> bs;
  for(int i=0, j=0; i<ln; i++) {
    int A, B;
    tie(A, B) = left[i];
    while(j < rn && right[j].first <= A) {
      bs.insert(make_pair(right[j].second, j));
      j++;
    }
    if(B > A+k) continue;
    if(B < A-k) {
      int upper = bs.order_of_key(make_pair(A+k+1, -1));
      int lower = bs.order_of_key(make_pair(A-k, -1));
      res += upper - lower;
    } else {
      int upper = bs.order_of_key(make_pair(A+k+1, -1));
      res += upper;
    }
  }

  // right is bigger
  bs.clear();
  for(int i=0, j=0; i<rn; i++) {
    int A, B;
    tie(A, B) = right[i];
    while(j < ln && left[j].first < A) {
      bs.insert(make_pair(left[j].second, j));
      j++;
    }
    if(B > A+k) continue;
    if(B < A-k) {
      int upper = bs.order_of_key(make_pair(A+k+1, -1));
      int lower = bs.order_of_key(make_pair(A-k, -1));
      res += upper - lower;
    } else {
      int upper = bs.order_of_key(make_pair(A+k+1, -1));
      res += upper;
    }
  }

  return res;
}

void caseinit() {
}

void casesolve() {
  caseinit();

  int n, k;
  cin >> n >> k;
  for(int i=0; i<n; i++) {
    cin >> a[i];
  }
  for(int i=0; i<n; i++) {
    cin >> b[i];
  }
  cout << solve(0, n-1, k) << nl;

  return;
}


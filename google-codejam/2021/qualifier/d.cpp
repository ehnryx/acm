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
random_device _rd; mt19937 rng(_rd());

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1e9+7;
constexpr ld EPS = 1e-9;

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
  return os << '(' << v.first << ", " << v.second << ')';
}
template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  os << "[ "; for (const T& it : v) { os << it << " , "; }
  return os << ']';
}
template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
  os << "{ "; for (const T& it : v) { os << it << " , "; }
  return os << '}';
}
template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
  os << "{ "; for (const pair<T,U>& it : v) { os << it << " , "; }
  return os << '}';
}

template <class T, class U>
istream& operator >> (istream& is, pair<T,U>& v) {
  return is >> v.first >> v.second;
}
template <int i, class... Ts>
istream& read_tuple_impl(istream& is, tuple<Ts...>& v) {
  if constexpr (i == 0) return is;
  else return read_tuple_impl<i-1>(is, v) >> get<i-1>(v);
}
template <class... Ts>
istream& operator >> (istream& is, tuple<Ts...>& v) {
  return read_tuple_impl<sizeof...(Ts)>(is, v);
}

template <class T = int>
vector<T> read_array(int n, int s=0) {
  vector<T> a(n + 2*s);
  for(int i=0; i<n; i++) {
    cin >> a[s+i];
  }
  return a;
}

template <class T = int>
vector<vector<T>> read_grid(int n, int m, int s=0, int t=0) {
  vector a(n + 2*s, vector<T>(m + 2*t));
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      cin >> a[s+i][t+j];
    }
  }
  return a;
}

void solve_case(int, int);
void initialize();

////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  initialize();

  int T, n, q;
  cin >> T >> n >> q;
  for (int cc = 1; cc <= T; cc++) {
    auto start = chrono::steady_clock::now();
    //cout << "Case #" << cc << ": ";
    solve_case(n, q);
    if(argc > 1 && argv[1][0] == 't') {
      cerr << "Time: " << (chrono::steady_clock::now() - start) / 1.0s << "s" << nl << nl;
    }
  }

  return 0;
}

////////////////////////////////////////////////////////////////////////

int query(int a, int b, int c) {
  //cerr << "query " << a << " " << b << " " << c << nl;
  cout << a << " " << b << " " << c << endl;
  int r;
  cin >> r;
  assert(r != -1);
  return r;
}

void answer(const vector<int>& ans) {
  //cerr << "guess " << ans << nl;
  for(int it : ans) {
    cout << it << " ";
  }
  cout << endl;
  int r;
  cin >> r;
  if(r == -1) exit(0);
}

vector<int> median_sort(vector<int> a) {
  int n = a.size();
  if(n <= 2) return a;
  shuffle(a.begin(), a.end(), rng);
  //cerr << "median_sort " << a << nl;

  int median = query(a[0], a[1], a[2]);
  int left = (median == a[0] ? a[1] : a[0]);
  int right = a[0] ^ a[1] ^ a[2] ^ left ^ median;
  vector<int> lval, rval, mval;
  mval.push_back(median);
  //cerr << "start loop " << a << nl;
  for(int i=3; i<n; i++) {
    int m = query(left, right, a[i]);
    if(m == left) lval.push_back(a[i]);
    else if(m == right) rval.push_back(a[i]);
    else mval.push_back(a[i]);
  }

  lval = median_sort(lval);
  rval = median_sort(rval);
  mval = median_sort(mval);
  //cerr << "reverse check " << a << nl;
  if(lval.size() > 1 && query(lval[0], lval[1], left) == lval[0]) {
    reverse(lval.begin(), lval.end());
  }
  if(mval.size() > 1 && query(mval[0], mval[1], left) == mval[1]) {
    reverse(mval.begin(), mval.end());
  }
  if(rval.size() > 1 && query(rval[0], rval[1], left) == rval[1]) {
    reverse(rval.begin(), rval.end());
  }

  vector<int> res;
  res.insert(res.end(), lval.begin(), lval.end());
  res.push_back(left);
  res.insert(res.end(), mval.begin(), mval.end());
  res.push_back(right);
  res.insert(res.end(), rval.begin(), rval.end());
  return res;
}

void solve_case(int n, int) {

  vector<int> a(n);
  iota(a.begin(), a.end(), 1);
  auto ans = median_sort(a);
  answer(ans);

  return;
}

void initialize() {
}


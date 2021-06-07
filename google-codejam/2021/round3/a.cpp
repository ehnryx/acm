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
constexpr int INF = 0x3f3f3f3f;
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

void solve_case();
void initialize();

////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  initialize();

  int T;
  cin >> T;
  for (int cc = 1; cc <= T; cc++) {
    auto start = chrono::steady_clock::now();
    cout << "Case #" << cc << ": ";
    solve_case();
    if(argc > 1 && argv[1][0] == 't') {
      cerr << "Time: " << (chrono::steady_clock::now() - start) / 1.0s << "s" << nl << nl;
    }
  }

  return 0;
}

////////////////////////////////////////////////////////////////////////

const int M = 10;

ll solve(vector<int> cnt, bool have) {
  int half = accumulate(begin(cnt), end(cnt), 0) / 2 - 1;
  if(half < 0) return 0;
  ll ans = INFLL;
  for(int a=1; a<M; a++) {
    if(cnt[a] == 0) continue;
    int b = a - 1;
    while(b >= 0 && cnt[b] == 0) {
      b--;
    }
    if(b < 0) continue;
    if(b == 0 && !have) continue;
    vector<int> memo = cnt;
    string big, small;
    big.push_back(a + '0');
    small.push_back(b + '0');
    cnt[a]--;
    cnt[b]--;
    for(int i=0, got=0; got<half; i++) {
      while(cnt[i] && got<half) {
        cnt[i]--;
        got++;
        big.push_back(i + '0');
      }
    }
    for(int i=M-1; i>=0; i--) {
      while(cnt[i]) {
        cnt[i]--;
        small.push_back(i + '0');
      }
    }
    ans = min(ans, stoll(big) - stoll(small));
    cnt = move(memo);
  }
  return ans;
}

void solve_case() {

  string s;
  cin >> s;
  vector<int> cnt(M);
  for(char c : s) {
    cnt[c - '0'] += 1;
  }

  if(s.size() % 2) {
    string big, small;
    for(int i=1; i<M; i++) {
      if(cnt[i]) {
        cnt[i]--;
        big.push_back(i + '0');
        break;
      }
    }
    for(int i=0, got=0; i<M && got<s.size()/2; i++) {
      while(cnt[i] && got<s.size()/2) {
        cnt[i]--;
        big.push_back(i + '0');
        got++;
      }
    }
    for(int i=M-1; i>=0; i--) {
      while(cnt[i]) {
        cnt[i]--;
        small.push_back(i + '0');
      }
    }
    cout << stoll(big) - stoll(small) << nl;
    return;
  }

  vector<int> match;
  for(int i=0; i<M; i++) {
    while(cnt[i] >= 2) {
      match.push_back(i);
      cnt[i] -= 2;
    }
  }

  ll ans = INFLL;
  int m = match.size();
  for(int bm=0; bm<1<<m; bm++) {
    vector<int> nums = cnt;
    bool ok = true;
    int nonzero = 0;
    for(int i=0; i<m; i++) {
      if(!(bm >> i & 1)) {
        nums[match[i]] += 2;
      } else {
        nonzero += (match[i] > 0);
        ok &= (i == 0 || (bm >> (i-1) & 1) || match[i] != match[i-1]);
      }
    }
    if(!ok) continue;
    if(nonzero == 0 && bm > 0) continue;
    ans = min(ans, solve(nums, bm > 0));
  }
  cout << ans << nl;

  return;
}

void initialize() {
}


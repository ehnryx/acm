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
random_device _rd; mt19937 rng(_rd());

template <class T> struct min_stack : public stack<T> {
  stack<T> mins; // vals stored in stack inherited from the STL stack
  T mins_top() { return (mins.empty() ? INFLL : mins.top()); }
  void push(T x) { mins.push(min(x, mins_top())); stack<T>::push(x); }
  T pop() { mins.pop(); T x=stack<T>::top(); stack<T>::pop(); return x; }
  T minimum() { return mins_top(); } };
template <class T> struct min_queue { min_stack<T> in, out;
  void refill() { if (out.empty()) while (!in.empty()) out.push(in.pop()); }
  void push(T x) { in.push(x); }
  T pop() { refill(); return out.pop(); }
  T front() { refill(); return out.top(); }
  bool empty() { return in.empty() && out.empty(); }
  T minimum() { return min(in.minimum(), out.minimum()); } };

void solve_case() {
  int n, d;
  cin >> n >> d;
  vector<int> a(n), h;
  for(int i=0; i<n; i++) {
    cin >> a[i];
    for(int j=0; j<=n && j*d < INF; j++) {
      if(a[i] + j*d < INF) h.push_back(a[i] + j*d);
      if(a[i] - j*d >= 0) h.push_back(a[i] - j*d);
    }
  }
  sort(h.begin(), h.end());
  h.resize(unique(h.begin(), h.end()) - h.begin());

  vector dp(n, vector<ll>(h.size(), INFLL));
  dp[0][lower_bound(h.begin(), h.end(), a[0]) - h.begin()] = 0;
  for(int i=1; i<n; i++) {
    min_queue<ll> window;
    for(int j=0, l=0, r=0; j<h.size(); j++) {
      while(r < h.size() && abs(h[r] - h[j]) <= d) {
        window.push(dp[i-1][r++]);
      }
      while(l <= r && abs(h[l] - h[j]) > d) {
        window.pop();
        l++;
      }
      assert(!window.empty());
      dp[i][j] = min(dp[i][j], window.minimum() + abs(a[i] - h[j]));
    }
  }
  ll ans = dp[n-1][lower_bound(h.begin(), h.end(), a[n-1]) - h.begin()];
  if(ans < INFLL) {
    cout << ans << nl;
  } else {
    cout << "impossible" << nl;
  }
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
    solve_case();
  }

  return 0;
}

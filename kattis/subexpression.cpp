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
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ll power(ll n, ll e, ll m) {
  ll r = 1;
  for(;e;e/=2) {
    if(e&1) r = r*n % m;
    n = n*n % m;
  }
  return r;
}

ll inverse(ll n, ll m) {
  return power(n, m-2, m);
}

const int L = 1e6 + 1;
ll p[L], invp[L], pref[L];
ll q[L], invq[L], qref[L];

const ll P = 1789;
const ll M = 1e9+9;
const ll Q = 2017;
const ll O = 1e9+7;

static const int N = 5e4 + 1;
vector<int> adj[N];
int par[N], lb[N], rb[N];
ll ha[N];
string name[N];

ll get_hash(int l, int r) {
  ll a = (pref[r] + M - pref[l]) * invp[l] % M;
  ll b = (qref[r] + O - qref[l]) * invq[l] % O;
  return a << 32 | b;
}

map<pair<int,ll>,int> seen;

void init() {
  seen.clear();
  for(int i=0; i<N; i++) {
    adj[i].clear();
    par[i] = lb[i] = rb[i] = -1;
    ha[i] = -1;
    name[i].clear();
  }
}

void build(int u, int& idx, string& ans) {
  pair<int,ll> csub(rb[u] - lb[u], ha[u]);
  if(seen.count(csub)) {
    ans += to_string(seen[csub]);
    return;
  }

  seen[csub] = ++idx;
  ans += name[u];
  if(!adj[u].empty()) {
    ans.push_back('(');
    build(adj[u][0], idx, ans);
    ans.push_back(',');
    build(adj[u][1], idx, ans);
    ans.push_back(')');
  }
}

void solve(const string& s) {
  init();
  int n = s.size();
  for(int i=0; i<n; i++) {
    pref[i+1] = (pref[i] + s[i] * p[i]) % M;
    qref[i+1] = (qref[i] + s[i] * q[i]) % O;
  }

  int cur = 0;
  int idx = 0;
  lb[cur] = 0;
  rb[cur] = n;
  ha[cur] = get_hash(lb[cur], rb[cur]);

  string token;
  for(int i=0; i<n; i++) {
    if(isalpha(s[i])) {
      if(token.empty()) {
        lb[cur] = i;
      }
      token.push_back(s[i]);
      continue;
    }

    if(!token.empty()) {
      name[cur] = token;
      token.clear();
    }

    if(s[i] == ')' || s[i] == ',') {
      rb[cur] = i;
      ha[cur] = get_hash(lb[cur], rb[cur]);
      assert(lb[cur]<rb[cur] && 0<=lb[cur] && ha[cur]>0);
      cur = par[cur];
    }

    if(s[i] == '(' || s[i] == ',') {
      adj[cur].push_back(++idx);
      par[idx] = cur;
      cur = idx;
    }
  }

  assert(cur == 0);
  if(!token.empty()) {
    name[cur] = token;
  }

  string ans;
  build(0, cur, ans);

  cout << ans << nl;
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

  p[0] = invp[0] = 1;
  q[0] = invq[0] = 1;
  for(int i=1; i<L; i++) {
    p[i] = p[i-1] * P % M;
    invp[i] = inverse(p[i], M);
    q[i] = q[i-1] * Q % O;
    invq[i] = inverse(q[i], O);
  }

  int n;
  cin >> n;
  for(int i=0; i<n; i++) {
    string s;
    cin >> s;
    solve(s);
  }

  return 0;
}

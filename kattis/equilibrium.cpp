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
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1e5;
int par[N], depth[N];
ll val[N];

int get_digit(const string& s, int& i) {
  int res = 0;
  for(;i<s.size() && isdigit(s[i]);i++) {
    res = res*10 + s[i]-'0';
  }
  --i;
  return res;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int T;
  cin>>T;
  while(T--) {
    string s;
    cin>>s;
    int cur = 0;
    int id = 0;
    int leaf = 0;
    val[0] = 0;
    for(int i=0;i<s.size();i++) {
      if(s[i]=='[') {
        par[++id] = cur;
        val[id] = 0;
        cur = id;
      } else if(s[i]==']') {
        cur = par[cur];
      } else if(s[i]==',') {
        par[++id] = par[cur];
        val[id] = 0;
        cur = id;
      } else {
        val[cur] = get_digit(s,i);
        leaf++;
      }
    }

    unordered_map<ll,int> cnt;
    int ans = INF;
    for(int i=0;i<=id;i++) {
      if(i>0) depth[i] = depth[par[i]] + 1;
      if(val[i]) {
        cnt[val[i]<<depth[i]]++;
        ans = min(ans, leaf - cnt[val[i]<<depth[i]]);
      }
    }
    cout<<ans<<nl;
  }

  return 0;
}

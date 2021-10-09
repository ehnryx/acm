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

const int N = 1e5+1;
int a[N];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int T;
  cin>>T;
  while(T--) {
    int s,n;
    cin>>s>>n;
    for(int i=0;i<n;i++) {
      cin>>a[i];
    }

    unordered_map<int,int> cur;
    unordered_set<int> bad;
    for(int i=0;i<n+s;i++) {
      if(i<n) cur[a[i]]++;
      if(i-s>=0 && --cur[a[i-s]] == 0) cur.erase(a[i-s]);
      int len = min(i,n-1) - max(0,i-s+1) + 1;
      if(cur.size() != len) bad.insert(i%s);
    }
    cout<<s-bad.size()<<nl;
  }

  return 0;
}

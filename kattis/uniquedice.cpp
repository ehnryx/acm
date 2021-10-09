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

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  os<<"[ ";
  for(const T& it:v) os<<it<<", ";
  return os<<"]";
}

int convert(vector<int> u) {
  vector<int> canon = u;
  for(int i=0;i<6;i++) {
    vector<int> v = u;
    if(i==1) {
      swap(v[0],v[1]); swap(v[2],v[3]);
    } else if(i==2) {
      swap(v[0],v[2]); swap(v[2],v[1]); swap(v[1],v[3]);
    } else if(i==3) {
      swap(v[0],v[3]); swap(v[3],v[1]); swap(v[1],v[2]);
    } else if(i==4) {
      swap(v[0],v[4]); swap(v[4],v[1]); swap(v[1],v[5]);
    } else if(i==5) {
      swap(v[0],v[5]); swap(v[5],v[1]); swap(v[1],v[4]);
    }
    for(int r=0;r<4;r++) {
      canon = min(canon, v);
      swap(v[2],v[4]); swap(v[4],v[3]); swap(v[3],v[5]);
    }
  }
  int res = 0;
  for(int i:canon) {
    res = res*7 + i;
  }
  return res;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin>>n;
  unordered_map<int,int> cnt;
  int ans = 0;
  for(int i=0;i<n;i++) {
    vector<int> cur(6);
    for(int j=0;j<6;j++) {
      cin>>cur[j];
    }
    ans = max(ans, ++cnt[convert(cur)]);
  }
  cout<<ans<<nl;

  return 0;
}

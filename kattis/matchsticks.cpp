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

vector<int> num = { 6, 2, 5, 5, 4, 5, 6, 3, 7, 6 };

string small(int n) {
  int len = (n+7-1)/7;
  string res;
  for(int i=len-1;i>0;i--) {
    for(int j=0+(i==len-1);j<10;j++) {
      if(n-num[j] <= 7*i && n-num[j] > 1) {
        res.push_back(j+'0');
        n -= num[j];
        break;
      }
    }
  }
  for(int j=0+(len==1);j<10;j++) {
    if(num[j] == n) {
      res.push_back(j+'0');
      break;
    }
  }
  return res;
}

string large(int n) {
  string res = (n%2==1 ? "7" : "1");
  for(;n>3;n-=2) {
    res.push_back('1');
  }
  return res;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int T;
  cin>>T;
  while(T--) {
    int n;
    cin>>n;
    cout<<small(n)<<" "<<large(n)<<nl;
  }

  return 0;
}

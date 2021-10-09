#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/rope>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_cxx;
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
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

bool is_palindrome(int n) {
  vector<int> a;
  for(;n>0;n/=10) {
    a.push_back(n%10);
  }
  vector<int> b = a;
  reverse(b.begin(),b.end());
  return a == b;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin>>n;
  for(int i=0;i<n;i++) {
    int v;
    cin>>v;
    for(int j=0;;j++) {
      if(v-j>99999 && is_palindrome(v-j)) {
        cout<<v-j<<nl;
        break;
      }
      if(v+j<1000000 && is_palindrome(v+j)) {
        cout<<v+j<<nl;
        break;
      }
    }
  }

  return 0;
}

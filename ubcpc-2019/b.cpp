#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// DON'T USE THESE MACROS DURING ICPC PRACTICE
#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Answer {
  string a,b,c;
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin>>n;
  string s[n];
  int h[n],a[n],d[n];
  for(int i=0;i<n;i++) {
    cin>>s[i]>>h[i]>>a[i]>>d[i];
  }

  auto win = [&](int i, int j) {
    int di = max(0,a[j]-d[i]);
    int dj = max(0,a[i]-d[j]);
    if(dj==0) return false;
    if(di==0) return true;
    int ti = (h[i]+di-1)/di;
    int tj = (h[j]+dj-1)/dj;
    return ti>tj;
  };

  auto check = [&](int i, int j, int k) {
    if(win(i,j) && win(j,k) && win(k,i)) return true;
    if(win(j,i) && win(k,j) && win(i,k)) return true;
    return false;
  };

  vector<Answer> ans;
  for(int i=0;i<n;i++) {
    for(int j=0;j<i;j++) {
      for(int k=0;k<j;k++) {
        if(check(i,j,k)) {
          ans.push_back({s[i],s[j],s[k]});
        }
      }
    }
  }
  cout<<ans.size()<<nl;
  for(const auto& it:ans) {
    cout<<it.a<<" "<<it.b<<" "<<it.c<<nl;
  }

  return 0;
}

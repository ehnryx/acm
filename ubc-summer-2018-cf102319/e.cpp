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

int query(const vector<int>& v) {
  cout<<"? ";
  for(int i:v) cout<<i;
  cout<<endl;
  int res;
  cin>>res;
  return res;
}

void answer(const vector<int>& v) {
  cout<<"! ";
  for(int i:v) cout<<i;
  cout<<endl;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n,k;
  cin>>n>>k;

  vector<int> ans(n,-1);
  vector<int> ones;
  vector<int> v(n,1);
  int tot = query(v);
  for(int i=0;i<n;i++) {
    v[i]=!v[i];
    int cur = query(v);
    if(cur!=tot) {
      v[i]=!v[i];
      ans[i]=1;
      ones.push_back(i);
    } else if(i>0 && ans[i-1]!=-1) {
      ans[i]=0;
    }
  }

  assert(ones.size()>=3);
  v = vector<int>(n,0);
  for(int i=0;i<3;i++) {
    v[ones[i]]=1;
  }
  for(int i=0;i<n;i++) {
    if(ans[i]==-1) {
      v[i]=1;
      ans[i]=query(v);
      v[i]=0;
    }
  }
  answer(ans);

  return 0;
}

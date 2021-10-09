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

const int N = 1e3+1;
int A[N], B[N];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n,d;
  cin>>n>>d;
  for(int i=0;i<n;i++) {
    int t,a,b;
    cin>>t>>a>>b;
    A[t] += a;
    B[t] += b;
  }

  int wa = 0;
  int wb = 0;
  int tot = 0;
  for(int i=1;i<=d;i++) {
    tot += A[i] + B[i];
    int cwa, cwb;
    if(A[i]>B[i]) {
      cwa = A[i] - ((A[i]+B[i])/2+1);
      cwb = B[i];
    } else {
      cwa = A[i];
      cwb = B[i] - ((A[i]+B[i])/2+1);
    }
    wa += cwa;
    wb += cwb;
    if(A[i]>B[i]) cout<<"A ";
    else cout<<"B ";
    cout<<cwa<<" "<<cwb<<nl;
  }
  cout<<(ld)abs(wa-wb)/tot<<nl;

  return 0;
}

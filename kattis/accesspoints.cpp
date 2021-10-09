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
int a[N], b[N];

int dsu[N];
int find(int i) {
  if(dsu[i]==-1) return i;
  return dsu[i] = find(dsu[i]);
}
void link(int i, int j) {
  if(find(i)!=find(j)) {
    dsu[find(i)] = find(j);
  }
}

ll A[N], B[N], C[N];
ld x[N];

ld get_x(int i) {
  return (ld)-B[i]/A[i]/2;
}

ld solve(int v[N], int n) {
  memset(dsu,-1,sizeof dsu);
  vector<int> memo;
  for(int i=0;i<n;i++) {
    A[i] = 1;
    B[i] = -2*v[i];
    C[i] = (ll)v[i]*v[i];
    x[i] = v[i];
    for(int j=find(i); !memo.empty() && x[j]<x[memo.back()]; j=find(i)) {
      int k = memo.back();
      memo.pop_back();
      link(j,k);
      A[find(i)] = A[j]+A[k];
      B[find(i)] = B[j]+B[k];
      C[find(i)] = C[j]+C[k];
      x[find(i)] = get_x(find(i));
    }
    memo.push_back(find(i));
  }

  ld res = 0;
  for(int i=0;i<n;i++) {
    res += (v[i]-x[find(i)]) * (v[i]-x[find(i)]);
  }
  return res;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin>>n;
  for(int i=0;i<n;i++) {
    cin>>a[i]>>b[i];
  }
  cout << solve(a,n) + solve(b,n) << nl;

  return 0;
}

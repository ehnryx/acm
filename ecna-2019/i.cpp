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

vector<char> S;

const int N = 100+1;
char g[N][N], orig[N][N];

int n,m;
bool solve(int i, int j, int cid) {
  while(i<=n && g[i][j]!='.' && g[i][j]!='$') {
    if(++j > m) {
      j = 1;
      i++;
    }
  }
  if(i>n) return true;

  int last = -1;
  int cnt = 0;
  for(int s=0;i+s<=n&&j+s<=m;s++) {
    for(int k=0;k<=s;k++) {
      cnt += 2 * (g[i+k][j+s]!='.' && g[i+k][j+s]!='$');
      cnt += (g[i+k][j+s]=='$');
      if(k<s) {
        cnt += 2 * (g[i+s][j+k]!='.' && g[i+s][j+k]!='$');
        cnt += (g[i+s][j+k]=='$');
      }
    }
    if(cnt>1) break;
    last = s;
    for(int k=0;k<=s;k++) {
      g[i+k][j+s] = S[cid];
      g[i+s][j+k] = S[cid];
    }
    if(cnt==1 && solve(i,j,cid+1)) {
      return true;
    }
  }

  for(int s=0;s<=last;s++) {
    for(int k=0;k<=s;k++) {
      g[i+k][j+s] = orig[i+k][j+s];
      g[i+s][j+k] = orig[i+s][j+k];
    }
  }

  return false;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  for(int i=0;i<26;i++) {
    S.push_back('A'+i);
  }
  for(int i=0;i<26;i++) {
    S.push_back('a'+i);
  }

  cin>>n>>m;
  for(int i=1;i<=n;i++) {
    for(int j=1;j<=m;j++) {
      cin>>g[i][j];
      orig[i][j] = g[i][j];
    }
  }

  if(solve(1,1,0)) {
    for(int i=1;i<=n;i++) {
      for(int j=1;j<=m;j++) {
        cout<<g[i][j];
      }
      cout<<nl;
    }
  } else {
    string out = "rectangle";
    reverse(out.begin(),out.end());
    cout<<out<<nl;
  }

  return 0;
}

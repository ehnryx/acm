#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;

ll a, b, c, d;

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  const int N = 999;
  vector<pair<int,int>> rat;
  for(int i=1;i<=N;i++) {
    for(int j=1;j+i<=N;j++) {
      if (__gcd(i,j)!=1) continue;
      rat.emplace_back(i,j);
      //cerr << i << "/" << j <<endl;
    }
  }
  //cerr << rat.size() <<endl;
  cin >> a >> b >> c >> d;
  ll ans = 0;
  for(auto &p: rat) {
    ll num = p.first;
    ll dem = p.second;
    //cerr << num << " " << dem <<endl;
    ll down = max((num+a-1)/num, (dem+c-1)/dem);
    ll up = min(b/num, d/dem);
    ans+=max(0LL,up-down+1);
//    if (up-down+1) cerr << up << " " << down << " "<< num << "/" << dem <<endl;
  }
  cout << ans <<endl;
  

  return 0;
}

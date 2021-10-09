#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <vector>
#include <map>
#include <queue>
using namespace std;

typedef long long ll;
typedef long double ld;

const char nl = '\n';

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  os<<"[ "; for(T it:v) { os<<it<<", "; }
  return os<<"]";
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout<<fixed<<setprecision(13);

  int T;
  for(cin>>T;T--;) {
    ll a, b;
    cin>>a>>b;
    if(b==0) {
      cout<<"Yes"<<nl;
      continue;
    }
    while(b%2==0) b/=2;
    bool ok = false;
    ll msk = (1LL<<(64-__builtin_clzll(b)))-1;
    for(int i=0;i<33;i++) {
      if((msk<<i & a) == (b<<i)) {
        ok = true;
        break;
      }
    }
    if(ok) {
      cout<<"Yes"<<nl;
    } else {
      cout<<"No"<<nl;
    }
  }

  return 0;
}

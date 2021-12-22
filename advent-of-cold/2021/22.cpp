#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  map<int,int>xs,ys,zs;
  vector<tuple<string,int,int,int,int,int,int>>IN;

  {
  string s; int a,b,c,x,y,z;
  while(cin>>s>>a>>x>>b>>y>>c>>z) {
    xs[a];
    xs[x+1];
    ys[b];
    ys[y+1];
    zs[c];
    zs[z+1];
    IN.emplace_back(s,a,b,c,x+1,y+1,z+1);
  }
  }


  vector<int>X,Y,Z;
  int xid=0;
  for(auto&it:xs){
    it.second=xid++;
    X.push_back(it.first);
  }
  int yid=0;
  for(auto&it:ys){
    it.second=yid++;
    Y.push_back(it.first);
  }
  int zid=0;
  for(auto&it:zs){
    it.second=zid++;
    Z.push_back(it.first);
  }


  cout << xid*yid*zid <<nl;




  vector g(xid,vector(yid,vector<bool>(zid)));
  for(auto [s,a,b,c,x,y,z] : IN){
    int add=(s=="on");
    for(int i=xs[a];i<xs[x];i++)
      for(int j=ys[b];j<ys[y];j++)
        for(int k=zs[c];k<zs[z];k++)
          g[i][j][k]=add;
  }

  ll ans=0;
  for(int i=0;i+1<xid;i++){
    for(int j=0;j+1<yid;j++)
    {
      for(int k=0;k+1<zid;k++){
        ans+=g[i][j][k] * (ll)
            (X[i+1]-X[i])*(Y[j+1]-Y[j])*(Z[k+1]-Z[k]);
      }
    }
  }

  cout << ans << nl;

  return 0;
}

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

enum {
  N,
  E,
  S,
  W,
  NW,
  NE,
  SW,
  SE
};

vector<int> da = {
  -1, 0, 1, 0
};
vector<int> db = {
  0, 1, 0, -1
};
vector<int> dt = {
  1, 1, -1, -1
};

const int NN = 1e5+1;
const int D = 4;
vector<pii> idx[2*D][2*NN][D];
vector<vector<int>> dirs = {
  { N, S, NW, NE, SW, SE },
  { E, W, NW, NE, SW, SE },
  { S, N, NW, NE, SW, SE },
  { W, E, NW, NE, SW, SE },
};

vector<function<int(int,int)>> geti = {
  [](int i, int j) { return j; }, // N
  [](int i, int j) { return i; }, // E
  [](int i, int j) { return j; }, // S
  [](int i, int j) { return i; }, // W
  [](int i, int j) { return i+j; }, // NW
  [](int i, int j) { return i-j+NN; }, // NE
  [](int i, int j) { return i+j; }, // SW
  [](int i, int j) { return i-j+NN; }, // SE
};

vector<function<int(int,int)>> getj = {
  [](int i, int j) { return i; }, // N
  [](int i, int j) { return j; }, // E
  [](int i, int j) { return i; }, // S
  [](int i, int j) { return j; }, // W
  [](int i, int j) { return j; }, // NW
  [](int i, int j) { return j; }, // NE
  [](int i, int j) { return j; }, // SW
  [](int i, int j) { return j; }, // SE
};

struct Node {
  int i,j,d;
  bool operator < (const Node& o) const {
    return d>o.d;
  }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  map<char,int> rmpd;
  rmpd['N'] = N;
  rmpd['S'] = S;
  rmpd['L'] = E;
  rmpd['O'] = W;

  int n,m,k;
  cin>>n>>m>>k;
  int a[k],b[k],d[k];
  for(int i=0;i<k;i++) {
    char direction;
    cin>>a[i]>>b[i]>>direction;
    d[i] = rmpd[direction];
    for(int dir:dirs[d[i]]) {
      idx[dir][geti[dir](a[i],b[i])][d[i]].push_back({getj[dir](a[i],b[i]),i});
    }
  }
  for(int i=0;i<2*D;i++) {
    for(int j=0;j<2*NN;j++) {
      for(int t=0;t<D;t++) {
        sort(idx[i][j][t].begin(),idx[i][j][t].end());
        if(idx[i][j][t].empty());else {
          cout<<i<<" "<<j<<" "<<t<<": ";
          for(pii jt:idx[i][j][t]) cout<<jt.first<<nl;
        }
      }
    }
  }

  priority_queue<Node> dijk;
  for(int i=0;i<k;i++) {
    if(d[i]==N) {
      {
        int r = geti[N](a[i],b[i]);
        int x = getj[N](a[i],b[i]);
        const auto& v = idx[N][r][S];
        auto it = upper_bound(v.begin(),v.end(),pii(x,INF));
        if(it!=v.begin()) {
          --it;
          assert(x>it->first);
          dijk.push({i,it->second,x-it->first});
        }
      }
      {
        int r = geti[NE](a[i],b[i]);
        int x = getj[NE](a[i],b[i]);
        const auto& v = idx[NE][r][E];
        auto it = upper_bound(v.begin(),v.end(),pii(x,INF));
        if(it!=v.begin()) {
          --it;
          assert(x>it->first);
          dijk.push({i,it->second,2*(x-it->first)});
        }
      }
    } else if(d[i]==W) {
      {
        int r = geti[W](a[i],b[i]);
        int x = getj[W](a[i],b[i]);
        const auto& v = idx[W][r][E];
        auto it = upper_bound(v.begin(),v.end(),pii(x,INF));
        for(pii jt:v) {
          cout<<jt.first<<" "<<jt.second<<nl;
        }
        if(it!=v.begin()) {
          --it;
          assert(x>it->first);
          dijk.push({i,it->second,x-it->first});
        }
      }
      {
        int r = geti[NW](a[i],b[i]);
        int x = getj[NW](a[i],b[i]);
        const auto& v = idx[NW][r][N];
        auto it = upper_bound(v.begin(),v.end(),pii(x,INF));
        if(it!=v.begin()) {
          --it;
          assert(x>it->first);
          dijk.push({i,it->second,2*(x-it->first)});
        }
      }
    } else if(d[i]==S) {
      {
        int r = geti[SW](a[i],b[i]);
        int x = getj[SW](a[i],b[i]);
        const auto& v = idx[SW][r][W];
        auto it = upper_bound(v.begin(),v.end(),pii(x,INF));
        if(it!=v.begin()) {
          --it;
          assert(x>it->first);
          dijk.push({i,it->second,2*(x-it->first)});
        }
      }
    } else if(d[i]==E) {
      {
        int r = geti[SE](a[i],b[i]);
        int x = getj[SE](a[i],b[i]);
        const auto& v = idx[SE][r][S];
        auto it = upper_bound(v.begin(),v.end(),pii(x,INF));
        if(it!=v.begin()) {
          --it;
          assert(x>it->first);
          dijk.push({i,it->second,2*(x-it->first)});
        }
      }
    } else {
      assert(false);
    }
  }

  auto get_intersect = [&](int i, int j, int t) {
    assert(j!=k);
    if(i!=k && t%2==1) {
      return pii(a[j]+da[d[j]]*(t+dt[d[j]])/2, b[j]+db[d[j]]*(t+dt[d[j]])/2);
    } else {
      return pii(a[j]+da[d[j]]*t/2, b[j]+db[d[j]]*t/2);
    }
  };

  vector<bool> dead(k+1,0);
  while(!dijk.empty()) {
    Node cur = dijk.top();
    dijk.pop();
    if(dead[cur.i]||dead[cur.j]) continue;
    dead[cur.i] = dead[cur.j] = true;
    dead[k] = false;
    int i,j;
    tie(i,j) = get_intersect(cur.i,cur.j,cur.d);
    int t = (cur.d+1)/2;
    {
      int r = geti[N](i,j);
      int x = getj[N](i,j);
      {
        const auto& v = idx[N][r][S]; 
        auto it = upper_bound(v.begin(),v.end(),pii(x-t,0));
        if(it!=v.begin()) {
          --it;
          dijk.push({k,it->second,x-it->first});
          if(it!=v.begin()) {
            --it;
            dijk.push({k,it->second,x-it->first});
          }
        }
      }{
        const auto& v = idx[N][r][N];
        auto it = lower_bound(v.begin(),v.end(),pii(x+t,0));
        if(it!=v.end()) {
          dijk.push({k,it->second,it->first-x});
        }
      }{
        const auto& v = idx[N][r][N];
        auto it = upper_bound(v.begin(),v.end(),pii(x+t,INF));
        if(it!=v.end()) {
          dijk.push({k,it->second,it->first-x});
        }
      }
    }
    {
      int r = geti[E](i,j);
      int x = getj[E](i,j);
      {
        const auto& v = idx[E][r][E]; 
        auto it = upper_bound(v.begin(),v.end(),pii(x-t,0));
        if(it!=v.begin()) {
          --it;
          dijk.push({k,it->second,x-it->first});
          if(it!=v.begin()) {
            --it;
            dijk.push({k,it->second,x-it->first});
          }
        }
      }{
        const auto& v = idx[E][r][W];
        auto it = lower_bound(v.begin(),v.end(),pii(x+t,0));
        if(it!=v.end()) {
          dijk.push({k,it->second,it->first-x});
        }
      }{
        const auto& v = idx[E][r][W];
        auto it = upper_bound(v.begin(),v.end(),pii(x+t,INF));
        if(it!=v.end()) {
          dijk.push({k,it->second,it->first-x});
        }
      }
    }
  }

  int ans = 0;
  for(int i=0;i<k;i++) {
    ans += !dead[i];
  }
  cout<<ans<<nl;

  return 0;
}

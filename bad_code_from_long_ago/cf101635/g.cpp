#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef int ll;
//typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

inline void srand() { srand(clock() + time(nullptr)); }

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
  os << "(" << v.first << "," << v.second << ")"; return os;
}

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  for (const T& it : v) os << it << " "; return os;
}

template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
  os << "{ ";
  for (const T& it : v) os << it << " ";
  os << "}"; return os;
}

template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
  os << "{ ";
  for (const pair<T,U>& it : v) os << "{" << it.first << "," << it.second << "} "; 
  os << "}"; return os;
}

template <class T>
inline T sqr(T x) { return x*x; }

const ll INF = 0x3f3f3f3f;
//const ll INFLL = 0x3f3f3f3f3f3f3f3f;
//const ld PI = M_PIl;
////////////////////////////////////////////////////////////////////////

const ll MOD = 1e9+7;
const ld EPS = 1e-9;

////////////////////////////////////////////////////////////////////////////////
// Max weight bipartite matching/min weight vertex cover (hungarian) - TESTED
////////////////////////////////////////////////////////////////////////////////
//usage: set w to be weights between two sets, n, m - their sizes, run wmatch
namespace FLOW {
//*/
//! w[i][j] = weight of edge from i on left side to j on right side
//! ml[i]   = matching of left vertex i
//! mr[i]   = matching of right vertex j
//! lbl[i]  = score of left vertex i
//! lbr[j]  = score of right vertex j
const int N = 2001;
int w[N][N], ml[N], mr[N], lbl[N], lbr[N], s[N], slack[N], par[N]; // Yury's
//! Run time is O(m * n^2)
void add_edge(int a, int b, int price) {
  w[a][b] = price;
}
int wmatch(int n, int m){ // assume n <= m;
  int i, j, k, done, al, nxt, out = 0;
  for(i=0;i<n;i++)for(j=0,lbl[i]=0,ml[i]=-1;j<m;j++) lbl[i]=max(lbl[i],w[i][j]);
  for(i = 0; i < m; i++) lbr[i] = 0, mr[i] = -1;
  for(i=0;i<n;i++) for(j = 0; j < m; j++) if(w[i][j] == lbl[i] && mr[j] == -1)
    { ml[i] = j, mr[j] = i; break; }
  for(i = 0; i < n; i++) if(ml[i] == -1){
    for(j=0;j<m;j++) s[j]=(j==i), slack[j]=(lbl[i]+lbr[j]-w[i][j]), par[j] = -1;
    for(done = 0; !done;){
      for(j = 0, al = INF; j < m; j++) if(par[j] == -1) al = min(al, slack[j]);
      for(j = 0, lbl[j] -= s[j]*al; j < m; ++j, lbl[j] -= s[j]*al)
        if(par[j] != -1) lbr[j] += al; else slack[j] -= al;
      for(j = 0; j < m; j++) if(!slack[j] && par[j] == -1){
        for(k=0;k<n;k++) if(s[k]&&(lbl[k]+lbr[j]==w[k][j])){ par[j] = k; break;}
        if(mr[j] == -1){ done = 1;
          do{ nxt=ml[par[j]], mr[j]=par[j], ml[par[j]]=j, j=nxt;}while(j != -1);
        }else for(k = 0, s[mr[j]] = 1; k < m; k++)
          slack[k] = min(slack[k], lbl[mr[j]] + lbr[k] - w[mr[j]][k]); break;}}}
  for(i = 0; i < n; i++) {
    out += w[i][ml[i]]; 
    //cerr << i << " --> " << ml[i] << nl;
  } return out; }
}

inline int distance(const pii& a, const pii& b) {
  return abs(a.first - b.first) + abs(a.second - b.second);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int n, m;
  cin >> n >> m;

  pii points[n];
  pii start[m];
  //cerr << "Points: " << nl;
  for (int i = 0; i < n; i++) {
    cin >> points[i].first >> points[i].second;
    //cerr << points[i] << nl;
  }
  //cerr << "Couriers: " << nl;
  for (int j = 0; j < m; j++) {
    cin >> start[j].first >> start[j].second;
    //cerr << start[j] << nl;
  }

  ll sum = 0;
  int mindiff = INF;
  pii dest;
  cin >> dest.first >> dest.second;
  for (int i = 0; i < n; i++) {
    sum += 2*distance(points[i], dest);
    for (int j = 0; j < m; j++) {
      int diff = distance(points[i], dest) - distance(points[i], start[j]);
      mindiff = min(mindiff, -diff);
      if (diff > 0) {
        //cerr << "add edge " << points[i] << " -- " << start[j] << " with cost " << diff << nl;
        FLOW::add_edge(i, j, diff);
      }
    }
    FLOW::add_edge(i, i+m, 0);
  }

  int less = FLOW::wmatch(n,m+n);
  //cerr << "less: " << less << nl;

  if (less > 0) {
    cout << sum - less << nl;
  } else {
    cout << sum + mindiff << nl;
  }

  return 0;
}

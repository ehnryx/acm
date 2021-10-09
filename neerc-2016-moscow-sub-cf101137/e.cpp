#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;


const int MAXN = 2e5+10;
int n, p[MAXN];
set<int> val;

int mem[MAXN][2][2][2];
vector<int> nex[MAXN][2][2][2];
int type[MAXN][2][2][2];

int dp(int, bool, bool, bool);

void update(int ci, bool ce, bool co, bool cb, int ni, bool ne, bool no, bool nb, int t, int bonus, int &ans) {
  int pos = dp(ni, ne, no, nb) + bonus;
  if (pos < ans) {
    nex[ci][ce][co][cb] = {ni, ne, no, nb};
    type[ci][ce][co][cb] = t;
    ans = pos;
  }
}

int cost(int i) {
  return to_string(p[i]).size();
}

int dp(int i, bool e, bool o, bool b) {
  if (mem[i][e][o][b] != -1) return mem[i][e][o][b];
  if (i==n) return ((e|o|b)? INF: 0);
  int d = p[i];
  if (e && d%2==0 && !val.count(d-2)) return INF;
  if (o && d%2==1 && !val.count(d-2)) return INF;
  if (b && !val.count(d-1)) return INF;
  if (b&(e|o)) assert(!(b&(e|o)));

  int ans = INF;

  bool even = (d%2==0);
  bool odd = (d%2==1);
  if (b) {
    update(i,e,o,b,i+1,e,o,0,2,cost(i)+1,ans); // stop b
    update(i,e,o,b,i+1,e,o,b,0,0,ans);// cont
  }
  else if (e && even) {
    update(i,e,o,b,i+1,0,o,b,4,cost(i)+1,ans); // stop e
    update(i,e,o,b,i+1,e,o,b,0,0,ans); // cont
  }
  else if (o && odd) {
    update(i,e,o,b,i+1,e,0,b,6,cost(i)+1,ans); // stop e
    update(i,e,o,b,i+1,e,o,b,0,0,ans); // cont 
  }
  else if (even) {
    update(i,e,o,b,i+1,1,o,b,3,cost(i)+1,ans);// start e
    update(i,e,o,b,i+1,e,o,b,7,cost(i)+1,ans);// put
  }
  else if (odd) {
    update(i,e,o,b,i+1,e,1,b,5,cost(i)+1,ans);// start o
    update(i,e,o,b,i+1,e,o,b,7,cost(i)+1,ans);// put
  }

  if (!b && !e && !o) {
    update(i,e,o,b,i+1,e,o,1,1,cost(i)+1,ans); // start b
  }

  //cerr << p[i] << " " << e << " " << o << " " << b << " is state has ans " << ans << endl;
  return mem[i][e][o][b] = ans;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n;
  for(int i=0;i<n;i++) {
    cin >> p[i];
    val.insert(p[i]);
  }
  sort(p, p+n);
  memset(mem, -1, sizeof mem);
  dp(0,0,0,0);
  bool e = 0;
  bool o = 0;
  bool b = 0;
  bool ne, no, nb;
  int t;
  int pre[3];
  string output;
  for(int i=0;i<n;i++) {
    t = type[i][e][o][b];
    //cerr << p[i] << " " << e << " " << o << " " << b << " recovering with type " << t <<endl;
    if (t==7) {
      output+=to_string(p[i])+",";
    }
    else if (t==0) {
      // do nothing
    }
    else if (t%2) { // open
      pre[(t-1)/2] = p[i];
    }
    else { // close
      string op;
      if (t==2) op = "-";
      if (t==4) op = "%";
      if (t==6) op = "#";
      output+=to_string(pre[(t-1)/2])+op+to_string(p[i])+",";
    }
    ne = nex[i][e][o][b][1];
    no = nex[i][e][o][b][2];
    nb = nex[i][e][o][b][3];
    e = ne;
    o = no;
    b = nb;
  }
  output.pop_back();
  cout << output <<endl;

  return 0;
}

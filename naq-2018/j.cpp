#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef __int128 lll;
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
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Edge {
  int target, jump;
};

vector<vector<Edge>> adj = {
/*0*/   { {3,1}, {5,2} },
/*1*/   { {6,3}, {8,4} },
/*2*/   { {7,4}, {9,5} },
/*3*/   { {0,1}, {10,6}, {5,4}, {12,7} }, // 3
/*4*/   { {11,7}, {13,8} },
/*5*/   { {3,4}, {12,8}, {0,2}, {14,9} },
/*6*/   { {1,3}, {8,7} }, // 6
/*7*/   { {2,4}, {9,8} },
/*8*/   { {6,7}, {1,4} },
/*9*/   { {2,5}, {7,8} }, // 9
/*10*/  { {3,6}, {12,11} },
/*11*/  { {13,12}, {4,7} },
/*12*/  { {5,8}, {14,13}, {10,11}, {3,7} }, // 12
/*13*/  { {11,12}, {4,8} },
/*14*/  { {12,13}, {5,9} }
};

const lll MASK = (1<<7)-1;

map<lll,int> memo;

int value(lll bm, int i) {
  return bm>>(7*i) & MASK;
}

void print(lll cur) {
  int v = 0;
  for (int i=0; i<5; i++) {
    for (int j=0; j<=i; j++) {
      cout << value(cur, v++) << " ";
    }
    cout << nl;
  }
}

int solve(lll cur) {
  if (memo.count(cur)) { return memo[cur]; }
  //cerr << "@: " << nl; print(cur);
  int res = -INF;
  for (int i=0; i<15; i++) {
    int v = value(cur, i);
    if (v) {
      for (const Edge& e : adj[i]) {
        int u = value(cur, e.jump);
        if (u && !value(cur, e.target)) {
          //cerr << "MOVE " << v << " over " << u << " using " << e.target << " " << e.jump << nl;
          lll nxt = cur;
          nxt &= ~(MASK<<(7*i));
          nxt &= ~(MASK<<(7*e.jump));
          nxt |= ((lll)v)<<(7*e.target);
          res = max(res, u*v - solve(nxt));
        }
      }
    }
  }
  if (res == -INF) res = 0;
  //cerr << "VALUE: " << res << nl; print(cur);
  return memo[cur] = res;
}


//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  vector<vector<int>> grid(5);
  int a;
  vector<int> v;
  for (int i=0; i<5; i++) {
    for (int j=0; j<=i; j++) {
      cin >> a;
      v.push_back(a);
    }
  }

  reverse(v.begin(), v.end());
  lll ha = 0;
  for (int it : v) {
    ha = (ha<<7) | it;
  }
  cout << solve(ha) << nl;

  return 0;
}

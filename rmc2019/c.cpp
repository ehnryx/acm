//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
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
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

vector<vector<string>> all = {
  {
    "###...",
    ".#....",
    ".#....",
    ".#....",
    "......",
    "......",
  },

  {
    "##....",
    ".##...",
    ".#....",
    ".#....",
    "......",
    "......",
  },

  {
    "##....",
    ".#....",
    ".##...",
    ".#....",
    "......",
    "......",
  },

  {
    "##....",
    ".#....",
    ".#....",
    ".##...",
    "......",
    "......",
  },

  {
    ".#....",
    "##....",
    ".##...",
    ".#....",
    "......",
    "......",
  },

  {
    ".#....",
    "###...",
    ".#....",
    ".#....",
    "......",
    "......",
  },

  {
    "#.....",
    "###...",
    ".#....",
    ".#....",
    "......",
    "......",
  },

  {
    "#.....",
    "##....",
    ".##...",
    ".#....",
    "......",
    "......",
  },

  {
    "#.....",
    "##....",
    ".#....",
    ".##...",
    "......",
    "......",
  },

  {
    "#.....",
    "#.....",
    "##....",
    ".#....",
    ".#....",
    "......",
  },

  {
    "#.....",
    "##....",
    ".##...",
    "..#...",
    "......",
    "......",
  },

};

string flatten(const vector<string>& g) {
  string s;
  for(const string& r : g) {
    s += r;
  }
  return s;
}

void addtr(unordered_set<string>& yes, vector<string> g, int I, int J) {
  while(I<0) {
    for(int j=0; j<6; j++) {
      if(g[0][j] == '#') return;
    }
    for(int i=0; i<6; i++) {
      for(int j=0; j<6; j++) {
        if(i < 5) g[i][j] = g[i+1][j];
        else g[i][j] = '.';
      }
    }
    I++;
  }
  while(I>0) {
    for(int j=0; j<6; j++) {
      if(g[5][j] == '#') return;
    }
    for(int i=5; i>=0; i--) {
      for(int j=0; j<6; j++) {
        if(i > 0) g[i][j] = g[i-1][j];
        else g[i][j] = '.';
      }
    }
    I--;
  }
  while(J<0) {
    for(int i=0; i<6; i++) {
      if(g[i][0] == '#') return;
    }
    for(int j=0; j<6; j++) {
      for(int i=0; i<6; i++) {
        if(j < 5) g[i][j] = g[i][j+1];
        else g[i][j] = '.';
      }
    }
    J++;
  }
  while(J>0) {
    for(int i=0; i<6; i++) {
      if(g[i][5] == '#') return;
    }
    for(int j=5; j>=0; j--) {
      for(int i=0; i<6; i++) {
        if(j > 0) g[i][j] = g[i][j-1];
        else g[i][j] = '.';
      }
    }
    J--;
  }
  yes.insert(flatten(g));
}

void add(unordered_set<string>& yes, vector<string> g) {
  for(int r=0; r<4; r++) {
    if(r>0) {
      vector<string> nxt(6, "......");
      for(int i=0; i<6; i++) {
        for(int j=0; j<6; j++) {
          nxt[i][j] = g[5-j][i];
        }
      }
      g = nxt;
    }
    for(int i=-4; i<=4; i++) {
      for(int j=-4; j<=4; j++) {
        addtr(yes, g, i, j);
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  unordered_set<string> yes;
  for(const vector<string>& g : all) {
    vector<string> t(6, "......");
    for(int i=0; i<6; i++) {
      for(int j=0; j<6; j++) {
        t[i][j] = g[j][i];
      }
    }
    add(yes, g);
    add(yes, t);
  }

  string s;
  for(int i=0; i<6; i++) {
    string cur;
    cin >> cur;
    s += cur;
  }
  if(yes.count(s)) {
    cout << "can fold" << nl;
  } else {
    cout << "cannot fold" << nl;
  }

  return 0;
}

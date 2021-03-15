#include <bits/stdc++.h>

using namespace std;

#define FILENAME "folding"

#define nl '\n'
typedef long long ll;
typedef long double ld;

char ans[3][3][3];
void output() {
  for(int i=0; i<3; i++) {
    for(int j=0; j<3; j++) {
      if(j>0) cout << " ";
      for(int k=0; k<3; k++) {
        cout << ans[i][j][k];
      }
    }
    cout << nl;
  }
  exit(0);
}

enum {
  UP, DOWN, RIGHT, LEFT, FRONT, BACK,
};

bool turn[28];
const string chars = "AaBbCcDdEeFfGgHhIiJjKkLlMmN";

bool solve(int i, int x, int y, int z, int bm, int dir) {
  if(i == 27) return true;
  //cerr << "put " << chars[i] << " @ " << x << " " << y << " " << z << nl;

  int u = (x*9 + y*3 + z);
  if(x<0 || y<0 || z<0 || x>=3 || y>=3 || z>=3) return false;
  if(bm & 1<<u) return false;
  ans[x][y][z] = chars[i];

  auto [nx, ny, nz] = tie(x, y, z);
  if(dir == UP) {
    nx++;
  } else if(dir == DOWN) {
    nx--;
  } else if(dir == RIGHT) {
    ny++;
  } else if(dir == LEFT) {
    ny--;
  } else if(dir == BACK) {
    nz++;
  } else {
    nz--;
  }

  if(turn[i+1]) {
    bool ok = false;
    for(int ndir=0; ndir<6 && !ok; ndir++) {
      if(ndir == dir || ndir == (dir^1)) continue;
      ok |= solve(i+1, nx, ny, nz, bm | 1<<u, ndir);
    }
    return ok;
  } else {
    return solve(i+1, nx, ny, nz, bm | 1<<u, dir);
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  assert(chars.size() == 27);
  map<char,int> toi;
  for(int i=0; i<27; i++) {
    toi[chars[i]] = i;
  }

  vector<string> g;
  for(string s; getline(cin, s); ) {
    g.push_back(s);
  }

  vector<pair<int,int>> pos(27);
  for(int i=0; i<g.size(); i++) {
    for(int j=0; j<g[i].size(); j++) {
      if(isalpha(g[i][j])) {
        pos[toi[g[i][j]]] = make_pair(i, j);
      }
    }
  }

  for(int i=1; i<26; i++) {
    pair<int,int> first(pos[i].first - pos[i-1].first, pos[i].second - pos[i-1].second);
    pair<int,int> second(pos[i+1].first - pos[i].first, pos[i+1].second - pos[i].second);
    turn[i] = (first != second);
  }

  if(solve(0, 0, 0, 0, 0, UP)) {
    output();
  } else if(solve(0, 0, 1, 1, 0, UP)) {
    output();
  } else if(solve(0, 0, 1, 1, 0, RIGHT)) {
    output();
  }

  assert(false);

  return 0;
}

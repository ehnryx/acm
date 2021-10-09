#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
#define nl '\n'

const int N = 9;
char a[N][N], b[N][N];
int remap[N];
vector<pair<int,int>> idx[N];

const int P = 6;
vector<vector<int>> p = {
  {0,1,2},
  {0,2,1},
  {1,0,2},
  {1,2,0},
  {2,0,1},
  {2,1,0},
};

vector<vector<int>> bigp;

bool solve() {
  for(const vector<int>& u : bigp) {
    for(const vector<int>& v : bigp) {
      memset(remap, -1, sizeof remap);
      bool ok = true;
      for(int k=0; k<9 && ok; k++) {
        for(const auto& [i,j] : idx[k]) {
          if(remap[a[u[i]][v[j]]] == -1) {
            remap[a[u[i]][v[j]]] = k;
          } else if(remap[a[u[i]][v[j]]] != k) {
            ok = false;
            break;
          }
        }
      }
      if(ok) {
        return true;
      }
    }
  }
  return false;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  for(int hi=0; hi<P; hi++) {
    for(int hj=0; hj<P; hj++) {
      for(int hk=0; hk<P; hk++) {
        for(int hh=0; hh<P; hh++) {
          vector<int> cp;
          for(int i=0; i<3; i++) {
            cp.push_back(p[hi][i] + 3*p[hh][0]);
          }
          for(int i=0; i<3; i++) {
            cp.push_back(p[hj][i] + 3*p[hh][1]);
          }
          for(int i=0; i<3; i++) {
            cp.push_back(p[hk][i] + 3*p[hh][2]);
          }
          bigp.push_back(move(cp));
        }
      }
    }
  }

  int T;
  cin >> T;
  while(T--) {
    for(int k=0; k<9; k++) {
      idx[k].clear();
    }
    for(int i=0; i<N; i++) {
      for(int j=0; j<N; j++) {
        cin >> a[i][j];
        a[i][j] -= '0';
        a[i][j]--;
      }
    }
    for(int i=0; i<N; i++) {
      for(int j=0; j<N; j++) {
        cin >> b[i][j];
        b[i][j] -= '0';
        if(b[i][j] > 0) {
          idx[b[i][j]-1].push_back(make_pair(i,j));
        }
      }
    }
    if(solve()) {
      cout << "Yes" << nl;
      continue;
    }
    for(int i=0; i<N; i++) {
      for(int j=0; j<N; j++) {
        swap(a[i][j], a[j][i]);
        swap(b[i][j], b[j][i]);
      }
    }
    for(int k=0; k<9; k++) {
      for(auto& it : idx[k]) {
        swap(it.first, it.second);
      }
    }
    if(solve()) {
      cout << "Yes" << nl;
    } else {
      cout << "No" << nl;
    }
  }

  return 0;
}

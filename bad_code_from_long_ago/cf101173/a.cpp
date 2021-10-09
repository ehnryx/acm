#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG
//#define USE_MAGIC_IO

#define ll long long
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble long double
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

vector<vector<char>> in;
vector<vector<char>> rotate(vector<vector<char>> &a) {
  vector<vector<char>> ret(a[0].size(), vector<char>(a.size()));
  for (int i = 0; i < a[0].size(); i++)
    for (int j = 0; j < a.size(); j++)
      ret[i][j] = a[a.size()-1-j][i];
  return ret;
}
vector<vector<char>> subgrid(int a, int b, int c, int d) {
  vector<vector<char>> ret(b - a + 1, vector<char>(d - c + 1));
  for (int i = a; i <= b; i++)
    for (int j = c; j <= d; j++)
      ret[i-a][j-c] = in[i][j];
  return ret;
}

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  int r, c; cin >> r >> c;
  in.resize(r);
  for (int i = 0; i < r; i++) {
    in[i].resize(c);
    for (int j = 0; j < c; j++)
      cin >> in[i][j];
  }
  int vsize = -1, hsize = -1;
  for (int i = 1; i < r; i++)
    if (in[i][1] == '#') {
      vsize = i;
      break;
    }
  for (int i = 1; i < c; i++)
    if (in[1][i] == '#') {
      hsize = i;
      break;
    }
  set<vector<vector<char>>> windows;
  int ans = 0;
  for (int i = 0; i < r-1; i += vsize) {
    for (int j = 0; j < c-1; j += hsize) {
      vector<vector<char>> cur = subgrid(i+1, i+vsize-1, j+1, j+hsize-1);
      /*
      for (auto &v : cur) {
        for (char c : v)
          cout << c << " ";
        cout << endl;
      }
      cout << endl;*/
      bool good = 1;
      for (int k = 0; k < 4; k++) {
        if (windows.count(cur)) {
          good = 0; break;
        }
        cur = rotate(cur);

      }
      for (int k = 0; k < 4; k++)
        windows.insert(cur), cur = rotate(cur);
      if (good)
        ans++;
    }
  }
  cout << ans << endl;

  return 0;
}

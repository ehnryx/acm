#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1200;
string grid[N];
vector<int> group[N];
int arr[N];

bool cmp(int a, int b) {
  return group[a].size() > group[b].size();
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n;
  while (cin >> n) {
    fill(group, group+n, vector<int>());
    for (int i = 0; i < n; i++) {
      cin >> grid[i];
    }

    vector<int> bad, good;
    for (int j = 1; j < n; j++) {
      if (grid[0][j] == '0') {
        bad.push_back(j);
      } else {
        good.push_back(j);
      }
    }

    for (int i : bad) {
      for (int j : good) {
        if (grid[j][i] == '1') {
          group[j].push_back(i);
          //cerr << "bad " << i << " -> " << j << nl;
          break;
        }
      }
    }
    sort(good.begin(), good.end(), cmp);

    //cerr << "good: "; for (int i : good) //cerr << i << " "; //cerr << nl;
    //cerr << "bad: "; for (int i : bad) //cerr << i << " "; //cerr << nl;

    int cur = n-1;
    for (int ii = 0; ii < good.size(); ii++) {
      int i = good[ii];
      if (group[i].empty()) break;
      //cerr << "group " << i << ": "; for (int j : group[i]) //cerr << j << " "; //cerr << nl;
      int sz = group[i].size(); // exclu
      int subtree = 1 << (32 - __builtin_clz(sz));
      arr[cur] = i;
      //cerr << i << " -> " << cur << nl;
      for (int j = 1; j <= sz; j++) {
        arr[cur-j] = group[i][j-1];
        //cerr << group[i][j-1] << " -> " << cur-j << "()" << nl;
      }
      for (int j = sz+1; j < subtree; j++) {
        //cerr << good.back() << " -> " << cur-j << nl;
        arr[cur-j] = good.back();
        good.pop_back();
      }
      cur -= subtree;
    }
    //cerr << "left over" << nl;
    while (cur > 0) {
      //cerr << good.back() << " -> " << cur << nl;
      arr[cur--] = good.back();
      good.pop_back();
    }
    arr[0] = 0;

    int h = (32 - __builtin_clz(n-1));
    for (int j = 0; j < h; j++) {
      //cerr << "layer "; for (int i = 0; i < n; i++) //cerr << arr[i] << " "; //cerr << nl;
      for (int i = 0; i < n; i += 1<<(j+1)) {
        cout << 1 + arr[i] << " " << 1 + arr[i+(1<<j)] << nl;
        if (grid[arr[i+(1<<j)]][arr[i]] == '1') arr[i] = arr[i+(1<<j)];
      }
    }
  }

  return 0;
}

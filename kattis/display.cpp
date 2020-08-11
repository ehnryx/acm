#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

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

const int N = 7;
const int M = 29;
char grid[N][M];

vector<vector<string>> number = {
  {
    "+---+",
    "|   |",
    "|   |",
    "+   +",
    "|   |",
    "|   |",
    "+---+"
  },
  {
    "    +",
    "    |",
    "    |",
    "    +",
    "    |",
    "    |",
    "    +"
  },
  {
    "+---+",
    "    |",
    "    |",
    "+---+",
    "|    ",
    "|    ",
    "+---+"
  },
  {
    "+---+",
    "    |",
    "    |",
    "+---+",
    "    |",
    "    |",
    "+---+"
  },
  {
    "+   +",
    "|   |",
    "|   |",
    "+---+",
    "    |",
    "    |",
    "    +"
  },
  {
    "+---+",
    "|    ",
    "|    ",
    "+---+",
    "    |",
    "    |",
    "+---+"
  },
  {
    "+---+",
    "|    ",
    "|    ",
    "+---+",
    "|   |",
    "|   |",
    "+---+"
  },
  {
    "+---+",
    "    |",
    "    |",
    "    +",
    "    |",
    "    |",
    "    +"
  },
  {
    "+---+",
    "|   |",
    "|   |",
    "+---+",
    "|   |",
    "|   |",
    "+---+"
  },
  {
    "+---+",
    "|   |",
    "|   |",
    "+---+",
    "    |",
    "    |",
    "+---+"
  },
};

void add(int n, int s) {
  for (int i=0; i<7; i++) {
    for (int j=0; j<5; j++) {
      grid[i][j+s] = number[n][i][j];
    }
  }
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

  string s;
  for (cin >> s; s != "end"; cin >> s) {
    for (int i=0; i<N; i++) {
      for (int j=0; j<M; j++) {
        grid[i][j] = ' ';
      }
    }
    grid[2][14] = 'o';
    grid[4][14] = 'o';
    add(stoi(s.substr(0,1)), 0);
    add(stoi(s.substr(1,1)), 7);
    add(stoi(s.substr(3,1)), 17);
    add(stoi(s.substr(4,1)), 24);
    for (int i=0; i<N; i++) {
      for (int j=0; j<M; j++) {
        cout << grid[i][j];
      }
      cout << nl;
    }
    cout << nl;
    cout << nl;
  }
  cout << "end" << nl;

  return 0;
}

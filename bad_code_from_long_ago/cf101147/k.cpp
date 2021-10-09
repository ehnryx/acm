#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

///* advent of code
typedef istringstream iss;
#define pb push_back
#define ins insert
#define multiset mset
#define getl(A) getline(cin, A)
//*/

const ll INF = 0x3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

const int N = 20;
const int M = 10;
const int K = 15;

ld prob[N+1][N+1][K+1][K+1];
ld card[N+1][M+1];
ld edge[N+1][N+1];
int arr[K+1];

int main() {
  freopen("trip.in", "r", stdin);
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(3);

  int T;
  cin >> T;
  while (T--) {
    int n, m, k, q, z;
    cin >> n >> m >> k >> q >> z;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        cin >> edge[i][j];
      }
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cin >> card[i][j];
      }
    }
    for (int i = 0; i < k; i++) {
      cin >> arr[i];
    }

    // d == 0
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        for (int a = 0; a < k; a++) {
          if (i == j)
            prob[i][j][a][a] = card[i][arr[a]] > 0;
          else
            prob[i][j][a][a] = 0;
        }
      }
    }

    // d == 1
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        for (int a = 1; a < k; a++) {
          prob[i][j][a-1][a] = edge[i][j] * card[j][arr[a]];
        }
      }
    }

    // d > 1
    for (int d = 2; d < k; d++) {
      for (int a = 0; a+d < k; a++) {
        for (int i = 0; i < n; i++) {
          for (int j = 0; j < n; j++) {
            prob[i][j][a][a+d] = 0;
            for (int r = 0; r < n; r++) {
              prob[i][j][a][a+d] += prob[i][r][a][a+d-1] * edge[r][j] * card[j][arr[a+d]];
            }
          }
        }
      }
    }

    ld top, bot;
    top = bot = 0;
    for (int e = 0; e < n; e++) {
      top += prob[z][e][q][k-1];
      bot += prob[0][e][0][k-1];
    }
    if (top == 0) {
      //cerr << "fix top" << nl;
      top = 1;
    }

//#define DEBUG
#ifdef DEBUG
    for (int e = 0; e < n; e++) {
      for (int j = 0; j < k; j++) {
        cout << "end: " << e << ", j: " << j << " --> " << prob[0][e][0][j] << endl;
      }
    }
#endif

    //cerr << "prob: " << prob[0][z][0][q] << nl;
    //cerr << "top: " << top << nl;
    //cerr << "bot: " << bot << nl;
    cout << prob[0][z][0][q] * top / bot << nl;
    //cerr << endl;
  }

  return 0;
}

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
const char nl = '\n';

const int N = 3e5 + 1;
const int M = 1e6 + 1;

int score[N]; // person -> score
int rank[M]; // score -> rank
map<int,ll> slope[M], prefix[M];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int n, m;
  cin >> n >> m;

  for(int i=1; i<=m; i++) {
    int k;
    cin >> k;
    vector<int> p(k);
    for(int j=0; j<k; j++) {
      cin >> p[j];
    }
  }

  return 0;
}

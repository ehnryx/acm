#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const int N = 505;
const int C = 100011;

int mem[N][C], n, c;
int pre[N][C];
int preval[N][C];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cin >> n >> c;
  vector<vector<int>> obj;
  for(int i=0;i<n;i++) {
    int d, s;
    cin >> d >> s;
    obj.push_back({s-max(d,s), s, i});
  }
  sort(obj.begin(), obj.end());
  for(int i=0;i<n;i++) {
    int req = -obj[i][0]+obj[i][1];
    int cost = obj[i][1];
    int id = obj[i][2];
    //cerr << req << " " << cost << " " << id <<endl;
    for(int k=0;k<=c;k++) {
      mem[i+1][k] = mem[i][k];
      pre[i+1][k] = -1;
      preval[i+1][k] = -1;
    }
    for(int k=c-req;k>=0;k--) {
      if (mem[i+1][k+cost] < mem[i][k]+1) {
//        cerr << "UPDATE " << i+1 << " " << k+cost <<" " << k << " " << id <<endl;
        mem[i+1][k+cost] = mem[i][k]+1;
        pre[i+1][k+cost] = id;
        preval[i+1][k+cost] = k;
      }
    }
  }
  int maxans = 0;
  int maxc = 0;
  for(int i=0;i<=c;i++) {
    if (maxans<mem[n][i]) {
      maxans = mem[n][i];
      maxc = i;
    }
  }
  int curc = maxc;
  vector<int> v;
  for(int i=n;i>0;i--) {
//    cerr<< "@ "<< i << " "  << curc << " " << pre[i][curc] << " " << mem[i][curc] << endl;
    if (pre[i][curc]!=-1) {
      v.push_back(pre[i][curc]);
      curc = preval[i][curc];
    }
  }
  reverse(v.begin(),v.end());
  cout << maxans <<endl;
  for(int i: v) cout << i+1 << " "; cout <<endl;
  return 0;
}

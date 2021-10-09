#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main()  {
  ios_base::sync_with_stdio(0), cin.tie(0);
  cout << "1\n";

  vector<vector<bool>> adj(26, vector<bool>(26, true));

  
  adj[0][23] = false;
  adj[0][20] = false;
  adj[20][21] = false;
  adj[21][22] = false;
  adj[22][25] = false;
  adj[22][24] = false;
  adj[24][25] = false;
  adj[23][25] = false;
  adj[25][0] = false;

  cout << 26*26-9 << endl;
  /*
  adj[0][1] = false;
  adj[1][0] = false;
  adj[2][0] = false;
  cout << 26*26-3 << endl;
  */
  for(int i=0;i<26;++i) {
    for(int j=0;j<26;++j) {
      if(adj[i][j]) {
        cout << (char) ('a'+i) << (char) ('a'+j) << "\n";
      }
    }
  }
  return 0;
}

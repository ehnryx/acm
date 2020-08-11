#include<bits/stdc++.h>
typedef long long ll;
using namespace std;

int chosen[1000000], nextv[1000000];
vector<int> adj[1000000];

void connect_ (int x, int y) {
    nextv[y] = x;
    for (int i : adj[y]) {
        if (nextv[i] == -1)
            connect_(y, i);
    }
}
void connect (int x, int y) {
    if (nextv[x] != -1)
        connect_(x, y);
    else if (nextv[y] != -1)
        connect_(y, x);
    else {
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
}
int findAndChose(int x, int n) {
    int y = x;
    int i = 0;
    while (chosen[y] == 0) {
        y = nextv[y];
        ++i;
    }
    if (chosen[y] != -1) {
        if (i <= n) {
            n -= i;
            while (i--) {
                chosen[x] = 1;
                x = nextv[x];
            }
            return n;
        }
        else {
            int k = i - n;
            while (k--){
                chosen[x] = -1;
                x = nextv[x];
            }
        }
    } else {
        while (i--) {
            chosen[x] = -1;
            x = nextv[x];
        }
    }
    return n;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);
    int n, k;
    cin >> n >> k;
    memset(nextv, -1, sizeof(int)*1e6);
    int i = n;
    ++nextv[n - 1];
    while (--i) {
        int x, y;
        cin >> x >> y;
        connect(x - 1, y - 1);
    }
    i = n - 1;
    int nchose = n - k - 1;
    chosen[i] = 1;
    while (nchose > 0)
        if (chosen[--i] != -1)
            if (chosen[i] == 0)
                nchose = findAndChose(i, nchose);
    for (i = 0; i < n; ++i)
        if(chosen[i] <= 0)
            cout << i + 1 << ' ';
    return 0;
}

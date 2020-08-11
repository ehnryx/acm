#include <iostream>
using std::cin;

const int N = 3e5;
int d[N], y[N], c[N], g[18][N], p[N], n, m, i, j, k, u, v, *t = *g;
#define f for(
#define U [u]
#define V [v]

main() {
	cin >> n >> m;
	f ;i<n;) cin >> t[++i];

	f ++i;--i;) if(!c[i]) {
		d[p[k=0] = i] = N;
		f u = t[i]; !d U; u = t U) d[p[++k] = u] = N;
		j = d U == N;
		f v=p[k]; k>=0; v=p[--k])
			f
				c V = c[t V] + 1,
				j ? y V = u, t V = 0 : 0,
				d V = d[t V] + 1,
				j &= v != u,
				n=0; n<17; n++
			) g[n+1] V = g[n][g[n] V];
	}

	f ;cin >> u >> v;) {
		k = d U - d V;
		f n=0; n<18; n++) k & 1<<n ? u = g[n] U : 0;
		printf("%d\n", y V && y U == y V ? k + (c U - c V + c[y V]) % c[y V] : u^v ? -1 : k);
	}
}

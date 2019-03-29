// https://www.acmicpc.net/problem/11378

#include <stdio.h>
#include <vector>
#include <queue>

template <typename T>
class Dinic {
public:
	int n;
	T inf;
	std::vector<int>* vec;
	int* level;
	T** f;

	Dinic(int n, T inf) {
		this->n = n;
		this->inf = inf;
		vec = new std::vector<int>[n + 1];
		level = new int[n + 1];
		f = new T*[n + 1];
		for (int i = 0; i <= n; i++) {
			f[i] = new T[n + 1];
			for (int j = 0; j <= n; j++) f[i][j] = 0;
		}
	}

	~Dinic(void) {
		delete[] vec;
		delete[] level;
		delete[] f;
	}

	void add_edge(int x, int y, T c) {
		vec[x].push_back(y);
		vec[y].push_back(x);
		f[x][y] = c;
	}

	bool bfs(int src, int snk) {
		int i;
		for (i = 0; i <= n; i++) level[i] = 0;
		std::queue<int> q;
		level[src] = 1;
		q.push(src);
		for (; !q.empty();) {
			int now = q.front();
			q.pop();

			for (int chd : vec[now]) {
				if (f[now][chd] > 0 && level[chd] == 0) {
					q.push(chd);
					level[chd] = level[now] + 1;
				}
			}
		}
		return level[snk] != 0;
	}

	T dfs(int now, int snk, T flow) {
		if (now == snk) return flow;
		for (int chd : vec[now]) {
			if (f[now][chd] > 0 && level[now] < level[chd]) {
				T d = dfs(chd, snk, (flow > f[now][chd]) ? f[now][chd] : flow);
				if (d == 0) continue;
				f[now][chd] -= d;
				f[chd][now] += d;
				return d;
			}
		}
		return 0;
	}

	T max_flow(int src, int snk) {
		T ret = 0;
		for (; bfs(src, snk);) {
			T flow;
			for (; flow = dfs(src, snk, inf);) {
				ret += flow;
			}
		}
		return ret;
	}
};

int main(void) {
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);
	Dinic<int> dinic(n + m + 3, 1 << 30);
	dinic.add_edge(0, 1, n);
	dinic.add_edge(0, 2, k);
	for (int i = 1; i <= n; i++) {
		dinic.add_edge(1, i + 2, 1);
		dinic.add_edge(2, i + 2, k);
		int j, x;
		for (scanf("%d", &j); j--;) {
			scanf("%d", &x);
			dinic.add_edge(i + 2, n + 2 + x, 1);
		}
	}
	for (int i = 1; i <= m; i++) dinic.add_edge(n + 2 + i, n + m + 3, 1);
	printf("%d\n", dinic.max_flow(0, n + m + 3));
	return false;
}
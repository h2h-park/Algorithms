#include <stdio.h>
#include <algorithm>
#include <vector>
#include <stack>

class SCC {
public:
	int n;
	std::vector<int>* vec;
	std::vector<int>* inv;
	bool* check;
	int* group;
	std::stack<int> st;
	std::vector<std::vector<int> > scc;

	SCC(int n) {
		this->n = n;
		vec = new std::vector<int>[n + 1];
		inv = new std::vector<int>[n + 1];
		check = new bool[n + 1];
		group = new int[n + 1];
	}

	~SCC(void) {
		delete[] vec;
		delete[] inv;
		delete[] check;
		delete[] group;
	}

	void add_edge(int x, int y) {
		vec[x].push_back(y);
		inv[y].push_back(x);
	}

	void dfs(int x) {
		check[x] = true;
		for (int chd : vec[x]) {
			if (check[chd]) continue;
			dfs(chd);
		}
		st.push(x);
	}

	void dfs2(int x, int k) {
		group[x] = k + 1;
		check[x] = true;
		scc[k].push_back(x);
		for (int chd : inv[x]) {
			if (check[chd]) continue;
			dfs2(chd, k);
		}
	}

	std::vector<std::vector<int> > get_scc(void) {
		for (; !st.empty(); st.pop());
		for (int i = 1; i <= n; i++) check[i] = false;
		scc.clear();

		for (int i = 1; i <= n; i++) {
			if (check[i]) continue;
			dfs(i);
		}

		int sz = 0;
		for (int i = 1; i <= n; i++) check[i] = false;
		for (; !st.empty(); ) {
			int i = st.top();
			st.pop();
			if (check[i]) continue;
			scc.resize(++sz);
			dfs2(i, sz - 1);
		}
		return scc;
	}
};

int main(void) {
	int n, m, i, j;
	scanf("%d %d", &n, &m);
	SCC scc(n);
	std::vector<std::vector<int> > comp;
	for (; m--;) {
		scanf("%d %d", &i, &j);
		scc.add_edge(i, j);
	}
	comp = scc.get_scc();

	printf("%d\n", comp.size());
	for (auto& it : comp) {
		std::sort(it.begin(), it.end());
	}
	std::sort(comp.begin(), comp.end(), [](const std::vector<int> x, const std::vector<int> y) {
		return x[0] < y[0];
	});
	for (auto& it : comp) {
		for (auto k : it) printf("%d ", k);
		printf("-1\n");
	}
	return false;
}
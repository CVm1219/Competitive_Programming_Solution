#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <iomanip>
#include <functional>

using namespace std;
using l = long long;
using ul = unsigned long long;

const int inf =  2147483647;         // 2e9     1 << 30
const l INF = 9223372036854775807;  // 9e18    1LL << 60

#define r(i, n) for (l i = 0; i < n; ++i)
#define r1(i, n) for (l i = 1; i < n; ++i)
#define r0(i) for (l i = -1; i < 2; ++i)
#define pll pair<l, l>


struct UnionFind {
    vector<l> parent, rank, size;
    l tree_count;
    
    UnionFind(l n) : parent(n), rank(n, 0), size(n, 1), tree_count(n) {
        for (l i = 0; i < n; i++) parent[i] = i;
    }
    
    l find(l x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);  // パス圧縮
    }
    bool unite(l x, l y) {
        l rx = find(x);
        l ry = find(y);
        if (rx == ry) return false;
        if (rank[rx] < rank[ry]) swap(rx, ry);
        parent[ry] = rx;
        size[rx] += size[ry];
        if (rank[rx] == rank[ry]) rank[rx]++;

        tree_count--;

        return true;
    }
    
    bool same(l x, l y) {
        return find(x) == find(y);
    }
    
    l getSize(l x) {
        return size[find(x)];
    }
};


int main() {
    l n,m;cin>>n>>m;

    vector<l> ans(m, n*(n-1)/2);

    vector<vector<l>> bridge;

    r(i, m) {
        l a,b;cin>>a>>b;--a;--b;

        bridge.push_back({a,b});
    }

    reverse(bridge.begin(), bridge.end());

    UnionFind uf(n);

    r(i, m-1) {
        ans[i+1]=ans[i];

        if (!uf.same(bridge[i][0], bridge[i][1])) {
            ans[i+1] -= uf.getSize(bridge[i][0]) * uf.getSize(bridge[i][1]);

            uf.unite(bridge[i][0], bridge[i][1]);
        }
    }

    r(i, m) cout<<ans[m-1-i]<<endl;
}
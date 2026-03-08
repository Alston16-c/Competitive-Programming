#include <bits/stdc++.h>
using namespace std;

struct LCA {
    int n, LOG;
    vector<vector<int>> g, up;
    vector<int> depth;

    LCA(int n) : n(n) {
        LOG = ceil(log2(n));
        g.resize(n);
        up.assign(n, vector<int>(LOG + 1));
        depth.resize(n);
    }

    void add_edge(int a,int b){
        g[a].push_back(b);
        g[b].push_back(a);
    }

    void dfs(int v,int p){
        up[v][0] = p;
        for(int i=1;i<=LOG;i++)
            up[v][i] = up[up[v][i-1]][i-1];

        for(int to:g[v]){
            if(to==p) continue;
            depth[to] = depth[v] + 1;
            dfs(to,v);
        }
    }

    int lca(int a,int b){
        if(depth[a] < depth[b]) swap(a,b);

        int k = depth[a] - depth[b];
        for(int i=0;i<=LOG;i++)
            if(k & (1<<i))
                a = up[a][i];

        if(a == b) return a;

        for(int i=LOG;i>=0;i--){
            if(up[a][i] != up[b][i]){
                a = up[a][i];
                b = up[b][i];
            }
        }

        return up[a][0];
    }
};

int main(){
    int n = 7;

    LCA tree(n);

    tree.add_edge(0,1);
    tree.add_edge(0,2);
    tree.add_edge(1,3);
    tree.add_edge(1,4);
    tree.add_edge(2,5);
    tree.add_edge(2,6);

    tree.dfs(0,0);

    cout << tree.lca(3,4) << endl; // 1
}
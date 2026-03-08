#include <bits/stdc++.h>
using namespace std;

struct SCC {
    int n;
    vector<vector<int>> g, rg;
    vector<int> comp, order, used;

    SCC(int n) : n(n) {
        g.resize(n);
        rg.resize(n);
    }

    void add_edge(int a, int b){
        g[a].push_back(b);
        rg[b].push_back(a);
    }

    void dfs1(int v){
        used[v] = 1;
        for(int to : g[v])
            if(!used[to])
                dfs1(to);
        order.push_back(v);
    }

    void dfs2(int v, int c){
        comp[v] = c;
        for(int to : rg[v])
            if(comp[to] == -1)
                dfs2(to, c);
    }

    vector<vector<int>> scc(){
        used.assign(n,0);
        comp.assign(n,-1);
        order.clear();

        for(int i=0;i<n;i++)
            if(!used[i])
                dfs1(i);

        reverse(order.begin(), order.end());

        int j = 0;
        for(int v : order)
            if(comp[v] == -1)
                dfs2(v, j++);

        vector<vector<int>> groups(j);
        for(int i=0;i<n;i++)
            groups[comp[i]].push_back(i);

        return groups;
    }
};

int main(){
    SCC scc(5);

    scc.add_edge(0,1);
    scc.add_edge(1,2);
    scc.add_edge(2,0);
    scc.add_edge(1,3);
    scc.add_edge(3,4);

    auto groups = scc.scc();

    for(auto &g : groups){
        for(int v : g)
            cout << v << " ";
        cout << "\n";
    }
}

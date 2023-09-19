#include <bits/stdc++.h> 
vector<pair<pair<int, int>, int>> calculatePrimsMST(int n, int m, vector<pair<pair<int, int>, int>> &g)
{
    //prepare adjacency list
    unordered_map<int, list<pair<int,int> > > adj;

    for(int i = 0; i < g.size(); i++) {
        int u = g[i].first.first;
        int v = g[i].first.second;
        int w = g[i].second;

        adj[u].push_back(make_pair(v,w));
        adj[v].push_back(make_pair(u,w));
    }

    // 3 data structures
    vector<int> key(n+1, INT_MAX);
    vector<bool> mst(n+1, false);
    vector<int> parent(n+1, -1);

    key[1] = 0;
    parent[1] = -1;

    //process for all nodes
    for(int i = 0; i < n; i++) {
        int mini = INT_MAX;
        int u;

        //step 1 : find the minimum wali node
        for(int j = 1; j <= n; j++) {
            if(mst[j] == false && key[j] < mini) {
                u = j;
                mini = key[j];
            }
        }

        //step 2: update the mst
        mst[u] = true;

        //step 3: check the adjacency nodes
        for(auto it : adj[u]) {
            int v = it.first;
            int w = it.second;

            if(mst[v] == false && w < key[v]) {
                key[v] = w;
                parent[v] = u;
            }
        }
    }
    vector<pair<pair<int, int>, int> > result;
    
    for(int i = 2; i <= n; i++) {
        result.push_back({{parent[i], i}, key[i]});
    }

    return result;
}

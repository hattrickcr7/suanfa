#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
void dfs(int start,vector<vector<int>>& map,vector<bool>& visit,vector<int>& order);
void mydfs(int start,int count,vector<vector<int>>& map,vector<bool>& visit,vector<int>& order);
//Please put this source code in the same directory with SCC.in
//And do NOT change the file name.
/*
This function computes the number of Strongly Connected Components in a graph
Args:
    n: The number of nodes in the graph. The nodes are indexed as 0~n-1
    edge: The edges in the graph. For each element (a,b) in edge, it means
          there is a directed edge from a to b
          Notice that there may exists multiple edge and self-loop
Return:
    The number of strongly connected components in the graph.
*/
int SCC(int n, vector<pair<int,int> >& edge) {
    int count=0;
    vector<vector<int>> map1(n);
    vector<vector<int>> map2(n);
    vector<bool> visit(n);
    vector<int> order;
    for (int i=0;i<edge.size();i++){
        map1[edge[i].second].push_back(edge[i].first);
        map2[edge[i].first].push_back(edge[i].second);
    }
    for (int i = n-1; i >= 0; --i) {
        if (!visit[i]){
            dfs(i,map1,visit,order);
        }
    }
    reverse(order.begin(),order.end());
    fill(visit.begin(),visit.end(),0);
    for (int i = 0; i < n; ++i) {
        if (!visit[order[i]]){
            count++;
//            mydfs(order[i],count,map2,visit,bianhao);
            dfs(order[i],map2,visit,order);
        }
    }
    return count;
}

void mydfs(int start,int count,vector<vector<int>>& map,vector<bool>& visit,vector<int>& order){
    if (visit[start]){
        return;
    }
    visit[start] = true;
    for(int i=0;i<map[start].size();i++){
        mydfs(map[start][i],count,map,visit,order);
    }
    order[start]=count;
    return;
}

void dfs(int start,vector<vector<int>>& map,vector<bool>& visit,vector<int>& order){
    if (visit[start]){
        return;
    }
    visit[start] = true;
    for(int i=0;i<map[start].size();i++){
        dfs(map[start][i],map,visit,order);
    }
    order.push_back(start);
    return;
}
//Please do NOT modify anything in main(). Thanks!
int main()
{
    int m,n;
    vector<pair<int,int>> edge;
    ifstream fin;
    ofstream fout;
    fin.open("../SCC.in");
    fin>>n>>m;
    int tmp1,tmp2;
    for(int i=0;i<m;i++)
    {
        fin>>tmp1>>tmp2;
        edge.push_back(pair<int,int>(tmp1,tmp2));
    }
    fin.close();
    int ans=SCC(n,edge);
    fout.open("SCC.out");
    fout<<ans<<'\n';
    fout.close();
    return 0;

}
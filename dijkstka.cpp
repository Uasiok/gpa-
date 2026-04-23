#include <iostream>
#include <vector>

using namespace std;

vector<long> Dist;
const long INF = 1000000;
vector<bool> used;
vector<vector<vector<int>>> matrix;

void Dijkstra(int start){
    Dist[start] = 0;
    for(int j = 0; j < Dist.size(); j++){
        int v = -1;
        for(int i = 0; i < Dist.size(); i++){
            if( (Dist[i] < Dist[v] || v == -1) && used[i] == false){
                v = i;
            }
        }

        if(v == -1){
            break;
        }
        used[v] = true;
        cout << v << endl;
        for(auto a : matrix[v]){
            int to = a[0];
            int w = a[1];
            if(Dist[v] + w < Dist[to]){
                Dist[to] = Dist[v] + w;
            }
        }
    }
    return;
}

int main()
{
    int n, m;
    cin >> n >> m;
    Dist.resize(n);
    used.resize(n);
    Dist.assign(n, INF);
    used.assign(n, false);
    matrix.resize(m);
    for(int i = 0; i < m; i++){
        int nach, kon, rasst;
        cin >> nach >> kon >> rasst;
        matrix[nach].push_back({kon, rasst});
    }
    Dijkstra(0);
    for(auto i : Dist){
        cout <<i << " ";
    }
    return 0;
}

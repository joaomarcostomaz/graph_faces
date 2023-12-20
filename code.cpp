//--------------------------------------------------------------------------
//Trabalho prático 1                                                        |
//Objetivo: Retornar todas as faces de um grafo planar                      |
//Aluno: João Marcos Tomáz Silva Campos                                     |
//Matrícula: 2022043728                                                     |
//Disciplina: Algoritmos 1                                                  |
//Professor: GG                                                             |
//--------------------------------------------------------------------------|
#include <bits/stdc++.h>

using namespace std;

// Funções auxiliares 
struct Ponto {
    double x, y;
};

struct hash_pair { 
    size_t operator()(const pair<size_t,size_t>& p) const
    { 
       return((hash<size_t>()(p.first) ^ (hash<size_t>()(p.second) << 1)) >> 1);
    } 
};

// Coeficiente da reta orientada de p para q. 
double InclinacaoRelativa(Ponto p, Ponto q) {
  return atan2(q.y - p.y, q.x - p.x);
}

//encontra as faces do grafo
vector<vector<int> > dfs_faces(vector<Ponto> pontos, vector<vector<int> > adj){
    int n = pontos.size();
    vector<vector<int> > faces;
    //Utiliza-se uma hash para verificar se a aresta já foi visitada
    unordered_map<pair<size_t,size_t>,bool,hash_pair> visited_edges(n);
    //dfs adaptado para encontrar as faces
    for(int i = 0; i < n; i++){
        for(int j = 0; j < adj[i].size(); j++){
            //se a aresta já foi visitada, não precisa fazer nada
            if(visited_edges[make_pair(i,adj[i][j])] == true){
                continue;
            }
            vector<int> face;
            int current_v = i;int current_e = j;
            //Faz o caminhamento identificando cada face - DFS
            while(!visited_edges[make_pair(current_v,adj[current_v][current_e])]){
                visited_edges[make_pair(current_v,adj[current_v][current_e])] = true;
                face.push_back(current_v + 1);
                int next_v = adj[current_v][current_e];
                //encontra a proxima aresta 
                //Utiliza-se mod para facilitar caso seja a ultima
                int next_e = (find(adj[next_v].begin(),adj[next_v].end(), current_v) - adj[next_v].begin() + 1) % adj[next_v].size();
                
                //Troca o vertice e a aresta para os proximos
                current_v = next_v;
                current_e = next_e;
            }
            //Adiciona o ultimo vertice
            face.push_back(current_v + 1);
            
            //Adiciona a face encontrada
            faces.push_back(face);
        }
    }
    return faces;
}


int main(){
    int n, m;
    cin >> n >> m;
    vector<Ponto> vertices(n);
    vector<vector<int> > adj(n);
     //Leitura dos pontos e arestas
    for(int i = 0; i < n; i++){
        int grau;
        cin >> vertices[i].x >> vertices[i].y >> grau;
        //Leitura dos pontos adjascentes
        for(int j = 0; j < grau; j++){
            int aux;
            cin >> aux;
            adj[i].push_back(aux - 1);
        }
    }
    //Ordena os pontos por ângulo polar
    for(int i = 0; i < n; i++){
        sort(adj[i].begin(),adj[i].end(),[&](int a, int b){
            return InclinacaoRelativa(vertices[i], vertices[a]) < InclinacaoRelativa(vertices[i], vertices[b]);
        });
    }
    //encontra as faces
    vector<vector<int> > faces = dfs_faces(vertices, adj);
    //imprime quantas faces são e a sequencia dos indices dos vertices que compoem cada face
    cout << faces.size() << endl;
    for(int i = 0; i < faces.size(); i++){
        cout << faces[i].size() << " ";
        for(int j = 0; j < faces[i].size(); j++){
            cout << faces[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
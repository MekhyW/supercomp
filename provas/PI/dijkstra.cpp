#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

// Definindo uma estrutura para representar um nó no grafo ponderado
struct Node {
    int id;
    int distance;
    Node(int _id, int _distance) : id(_id), distance(_distance) {}
    // Sobrecarregando o operador "<" para usar com uma fila de prioridade
    bool operator<(const Node& other) const {
        return distance > other.distance;
    }
};

vector<int> dijkstra(const vector<vector<pair<int, int>>>& graph, int source, int destination) {
    int numNodes = graph.size();
    vector<int> distance(numNodes, numeric_limits<int>::max());
    vector<int> previous(numNodes, -1);
    distance[source] = 0;
    priority_queue<Node> pq;
    pq.push(Node(source, 0));
    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();
        int u = current.id;
        if (u == destination) break;
        for (const auto& neighbor : graph[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;
            if (distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.push(Node(v, distance[v]));
            }
        }
    }
    vector<int> path;
    int current = destination;
    while (current != -1) {
        path.push_back(current);
        current = previous[current];
    }
    reverse(path.begin(), path.end());
    return path;
}



vector<vector<pair<int, int>>> le_grafo() {
  int N;         // Número de cidades
  int E;         // Número de estradas
  int i, f, p;   // Início, fim e peso da estrada
  cin >> N >> E;
  vector<vector<pair<int, int>>> graph(N);
  for (int x=0; x<E; x++) {
    cin >> i >> f >> p;
    graph[i].push_back({f, p});  // ida
    graph[f].push_back({i, p});  // volta
  }
  return graph;
}


vector<vector<pair<int, int>>> le_caminhos() {
  int C;         // Número de caminhos a serem calculados
  int o, d;      // Início e fim
  cin >> C;
  vector<vector<pair<int, int>>> caminhos(C);
  for (int x=0; x<C; x++) {
    cin >> o >> d;
    caminhos[x].push_back({o, d});
  }
  return caminhos;  
}


int main() {
    // Lê os dados
    vector<vector<pair<int, int>>> graph = le_grafo();
    vector<vector<pair<int, int>>> caminhos = le_caminhos();
    // Calculando e exibindo os resultados
    for (auto& p : caminhos){
      int origem = p[0].first;   // origem
      int destino = p[0].second; // destino
      // Encontrando o caminho mais curto entre origem e destino
      vector<int> path = dijkstra(graph, origem, destino);
      // Imprimindo a resposta
      cout << "Caminho mais curto de " << origem << " para " << destino << ": ";
      for (int node : path) {
        cout << node << " ";
      }
      cout << endl;
    }
    return 0;
}
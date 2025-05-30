#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <stack>
#include <string>
#include <climits>

using namespace std;

//khai bao ham
vector <vector <int>> convertMatrixToList(const string& filename);
vector <vector <int>> convertListToMatrix(const string& filename);
bool isDirected(const vector<vector<int>>& adjMatrix);
int countVertices(const vector<vector<int>>& adjMatrix);
int countEdges(const vector<vector<int>>& adjMatrix);
vector<int> getIsolatedVertices(const vector<vector<int>>& adjMatrix);
bool isCompleteGraph(const vector<vector<int>>& adjMatrix);
bool isBipartite(const std::vector<std::vector<int>>& adjMatrix);
bool isCompleteBipartite(const vector<vector<int>>& adjMatrix);
vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix);
vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix);
vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix);
void dfsVisited(const vector<vector<int>>& adjMatrix, int start, vector <bool> &visited, int &n, vector <vector <int>> &result);
vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start);
vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start);
bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix);
vector<int> dijkstra(int start, int end, const vector<vector<int>>& adjMatrix);
vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix);

//viet ham
int max(int a, int b)
{
    return (a > b) ? a : b;
}

vector<vector<int>> convertMatrixToList(const string& filename)
{
    int n_matrix;
    ifstream is(filename);
    if (!is)
    {
        cerr << "cannot open input file!";
        return vector<vector <int>> {};
    }
    is >> n_matrix;
    int temp;
    vector <vector <int>> List(n_matrix, vector <int> (1, 0));
    for (int i = 0; i < n_matrix; ++i)
    {
        for (int j = 0; j < n_matrix; ++j)
        {
            is >> temp;
            if (temp != 0)
            {
                List[i].push_back(j);
                ++List[i][0];
            }
        }
    }
    return List;
}

vector<vector<int>> convertListToMatrix(const string& filename)
{
    int n_matrix;
    ifstream is(filename);
    if (!is)
    {
        cerr << "cannot open input file!";
        return vector<vector <int>> {};
    }
    is >> n_matrix;
    vector <vector <int>> Matrix(n_matrix, vector <int> (n_matrix));
    int temp, temp_num;
    for (int i = 0; i < n_matrix; ++i)
    {
        is >> temp;
        for (int j = 0; j < temp; ++j)
        {
            is >> temp_num;
            Matrix[i][temp_num] = 1;
        }
    }
    return Matrix;
}

bool isDirected(const vector<vector<int>>& adjMatrix)
{
    int MatrixSize = adjMatrix.size();
    for (int i = 0; i < MatrixSize - 1; ++i)
    {
        for (int j = i + 1; j < MatrixSize; ++j)
        {
            if (adjMatrix[i][j] != adjMatrix[j][i]) 
            {
                return true;
            }
        }
    }
    return false;
}

int countVertices(const vector<vector<int>>& adjMatrix)
{
    return adjMatrix.size();
}

int countEdges(const vector<vector<int>>& adjMatrix)
{
    int MatrixSize = adjMatrix.size(), dem = 0, special_edges = 0;
    for (int i = 0; i < MatrixSize - 1; ++i)
    {
        for (int j = i + 1; j < MatrixSize; ++j)
        {
            if (adjMatrix[i][j] != 0) ++dem;
            if (adjMatrix[j][i] != 0) ++dem;
        }
    }
    for (int i = 0; i < MatrixSize; ++i)
    {
        if (adjMatrix[i][i] != 0) ++special_edges;
    }
    if (isDirected(adjMatrix)) return dem + special_edges;
    else return dem / 2 + special_edges;
}

vector <int> getIsolatedVertices(const vector<vector<int>>& adjMatrix)
{
    int MatrixSize = adjMatrix.size();
    vector <bool> temp(MatrixSize, true);
    for (int i = 0; i < MatrixSize - 1; ++i)
    {
        for (int j = i + 1; j < MatrixSize; ++j)
        {
            if (adjMatrix[i][j] != 0 || adjMatrix[j][i] != 0) 
            {
                temp[i] = temp[j] = false;
            }
        }
    }
    for (int i = 0; i < MatrixSize; ++i) 
    {
        if (adjMatrix[i][i] != 0) temp[i] = false;
    }
    vector <int> result;
    for (int i = 0; i < MatrixSize; ++i)
    {
        if (temp[i]) result.push_back(i);
    }
    return result;
}

bool isCompleteGraph(const vector<vector<int>>& adjMatrix)
{
    if (isDirected(adjMatrix)) return false;
    int MatrixSize = adjMatrix.size();
    for (int i = 0; i < MatrixSize - 1; ++i)
    {
        for (int j = i + 1; j < MatrixSize; ++j)
        {
            if (adjMatrix[i][j] == 0 || adjMatrix[j][i] == 0) 
            {
                return false;
            }
        }
    }
    return true;
}

bool isBipartite(const std::vector<std::vector<int>>& adjMatrix)
{
    if (isDirected(adjMatrix)) return false;
    for (int i = 0; i < adjMatrix.size(); ++i) 
    {
        if (adjMatrix[i][i] != 0) return false;
    }
    int MatrixSize = adjMatrix.size();
    vector <int> color(MatrixSize, -1);
    queue <int> q;
    for (int i = 0; i < MatrixSize; ++i)
    {
        if (color[i] == -1)
        {
            color[i] = 0;
            int temp;
            q.push(i);
            while (!q.empty())
            {
                temp = q.front();
                q.pop();
                for (int j = 0; j < MatrixSize; ++j)
                {
                    if (adjMatrix[temp][j] == 1)
                    {
                        if (color[j] == -1)
                        {
                            color[j] = 1 - color[temp];
                            q.push(j);
                        }
                        else if (color[j] == color[temp])
                        {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

bool isCompleteBipartite(const vector<vector<int>>& adjMatrix)
{
    if (isDirected(adjMatrix)) return false;
    for (int i = 0; i < adjMatrix.size(); ++i) 
    {
        if (adjMatrix[i][i] != 0) return false;
    }
    int MatrixSize = adjMatrix.size();
    vector <int> color(MatrixSize, -1);
    queue <int> q;
    for (int i = 0; i < MatrixSize; ++i)
    {
        if (color[i] == -1)
        {
            color[i] = 0;
            int temp;
            q.push(i);
            while (!q.empty())
            {
                temp = q.front();
                q.pop();
                for (int j = 0; j < MatrixSize; ++j)
                {
                    if (adjMatrix[temp][j] != 0)
                    {
                        if (color[j] == -1)
                        {
                            color[j] = 1 - color[temp];
                            q.push(j);
                        }
                        else if (color[j] == color[temp])
                        {
                            return false;
                        }
                    }
                }
            }
        }
    }
    vector <int> zero, one;
    for (int i = 0; i < MatrixSize; ++i)
    {
        if (color[i] == 0) zero.push_back(i);
        else one.push_back(i); 
    }
    for (int i : zero)
    {
        for (int j : one)
        {
            if (adjMatrix[i][j] == 0) return false;
        }
    }
    return true;
}

vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix)
{
    int MatrixSize = adjMatrix.size();
    vector<vector<int>> result = adjMatrix;
    for (int i = 0; i < MatrixSize - 1; ++i)
    {
        for (int j = i + 1; j < MatrixSize; ++j)
        {
            result[i][j] = result[j][i] = max(result[i][j], result[j][i]);
        }
    }
    return result;
}

vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix)
{
    if (isDirected(adjMatrix)) return vector <vector <int>> {};
    int MatrixSize = adjMatrix.size();
    vector<vector<int>> result = adjMatrix;
    for (int i = 0; i < MatrixSize - 1; ++i)
    {
        for (int j = i + 1; j < MatrixSize; ++j)
        {
            if (adjMatrix[i][j] == 0) 
            {
                result[i][j] = result[j][i] = 1;
            }
            else
            {
                result[i][j] = result[j][i] = 0;
            }
        }
    }
    for (int i = 0; i < MatrixSize; ++i)
    {
        result[i][i] = 0;
    }
    return result;
}

vector <int> findEulerCycle(const vector<vector<int>>& adjMatrix) 
{
    int MatrixSize = adjMatrix.size(); 
    if (MatrixSize == 0) return vector <int> {};
    vector <int> dinhColap = getIsolatedVertices(adjMatrix);
    if (dinhColap.size() == MatrixSize) return vector <int> {};
    vector <int> khongColap;
    dinhColap.push_back(-1);
    int k = 0;
    for (int i = 0; i < MatrixSize; ++i)
    {
        if (dinhColap[k] == i)
        {
            ++k;
        }
        else
        {
            khongColap.push_back(i);
        }
    }
    int edgeSum = countEdges(adjMatrix);
    bool directed = isDirected(adjMatrix);
    vector<int> in(MatrixSize, 0), out(MatrixSize, 0);
    for (int u = 0; u < MatrixSize; ++u)
    {
        for (int v = 0; v < MatrixSize; ++v)
        {
            if (adjMatrix[u][v])
            {
                ++out[u];
                ++in[v];
            }
        }
    }
    if (directed)
    {
        for (int i = 0; i < MatrixSize; ++i)
        {
            if (in[i] != out[i]) return vector <int> {};
        }
    }
    else
    {
        for (int i = 0; i < MatrixSize; ++i)
        {
            if ((in[i] + out[i]) / 2 % 2 != 0) return vector <int> {};
        }
    }
    if (directed) 
    {
        for (int st = 0; st < khongColap.size(); ++st) 
        {
            int start = khongColap[st];
            vector <vector <int>> matrix = adjMatrix;
            stack <int> s;
            vector <int> result;
            s.push(start);
            while (!s.empty()) 
            {
                int temp = s.top();
                bool coCanh = false;                
                for (int i = 0; i < MatrixSize; ++i) 
                {
                    if (matrix[temp][i] != 0) 
                    {
                        s.push(i);
                        matrix[temp][i] = 0;
                        coCanh = true;
                        break;
                    }
                }
                if (!coCanh) 
                {
                    result.push_back(temp);
                    s.pop();
                }
            }
            if (result.size() == edgeSum + 1) 
            {
                for (int i = 0; i < result.size() / 2; ++i)
                {
                    int doi = result[i];
                    result[i] = result[result.size() - 1 - i];
                    result[result.size() - 1 - i] = doi;
                }
                return result;
            }
        }
        return vector <int> {};
    }
    else 
    {
        vector <vector <int>> matrix = adjMatrix;
        int start = khongColap[0];
        stack <int> s;
        vector <int> result;
        s.push(start);
        while (!s.empty()) 
        {
            int temp = s.top();
            bool coCanh = false;
            for (int i = 0; i < MatrixSize; ++i) 
            {
                if (matrix[temp][i] != 0) 
                {
                    s.push(i);
                    matrix[temp][i] = matrix[i][temp] = 0;
                    coCanh = true;
                    break;
                }
            }            
            if (!coCanh) 
            {
                result.push_back(temp);
                s.pop();
            }
        }
        if (result.size() == edgeSum + 1) 
        {
            for (int i = 0; i < result.size() / 2; ++i)
            {
                int doi = result[i];
                result[i] = result[result.size() - 1 - i];
                result[result.size() - 1 - i] = doi;
            }
            return result;
        }
        return vector <int> {};
    }
}

void dfsVisited(const vector<vector<int>>& adjMatrix, int start, vector <bool> &visited, int &n, vector <vector <int>> &result)
{
    if (n == adjMatrix.size()) return;
    visited[start] = true;
    ++n;
    for (int i = 0; i < adjMatrix.size(); ++i)
    {
        if (adjMatrix[start][i] == 1 && !visited[i])
        {
            result[start][i] = result[i][start] = 1;
            dfsVisited(adjMatrix, i, visited, n, result);
        }
        if (n == adjMatrix.size()) break;
    }
}

vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start)
{
    if (isDirected(adjMatrix)) return vector <vector <int>> {};
    vector <vector <int>> result(adjMatrix.size(), vector <int> (adjMatrix.size(), 0));
    vector <bool> visited(adjMatrix.size(), false);
    int n = 0;
    dfsVisited(adjMatrix, start, visited, n, result);
    if (n == adjMatrix.size()) return result;
    return vector <vector <int>> {};
}

vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start)
{
    if (isDirected(adjMatrix)) return vector <vector <int>> {};
    vector <vector <int>> result(adjMatrix.size(), vector <int> (adjMatrix.size(), 0));
    vector <bool> visited(adjMatrix.size(), false);
    visited[start] = true;
    int n = 1;
    queue <int> q;
    q.push(start);
    while (!q.empty())
    {
        start = q.front();
        q.pop();
        for (int i = 0; i < adjMatrix.size(); ++i)
        {
            if (i != start && adjMatrix[start][i] == 1 && !visited[i])
            {
                visited[i] = true;
                ++n;
                result[start][i] = result[i][start] = 1;
                q.push(i);
            }
            if (n == adjMatrix.size()) break;
        }
    }
    if (n == adjMatrix.size()) return result;
    else return vector <vector <int>> {};
}

bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix)
{
    if (u == v) return true;
    vector <bool> visited(adjMatrix.size(), false);
    visited[u] = true;
    queue <int> q;
    q.push(u);
    int temp;
    while (!q.empty())
    {
        temp = q.front();
        q.pop();
        for (int i = 0; i < adjMatrix.size(); ++i)
        {
            if (adjMatrix[temp][i] == 1 && !visited[i]) 
            {
                if (i == v) return true;
                else
                {
                    q.push(i);
                    visited[i] = true;
                }
            }
        }
    }
    return false;
}

vector <int> dijkstra(int start, int end, const vector <vector <int>>& adjMatrix)
{
    vector <int> minS(adjMatrix.size(), INT_MAX), parent(adjMatrix.size(), -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    minS[start] = 0;
    pq.push({0, start});
    while (!pq.empty())
    {
        int d = pq.top().first, u = pq.top().second;
        pq.pop();
        if (d > minS[u]) continue;
        if (u == end) break;
        for (int i = 0; i < adjMatrix.size(); ++i) 
        {
            if (adjMatrix[u][i] != 0 && minS[i] > minS[u] + adjMatrix[u][i])
            {
                minS[i] = minS[u] + adjMatrix[u][i];
                parent[i] = u;
                pq.push({minS[i], i});
            }
        }
    }
    if (minS[end] == INT_MAX) return vector <int> {};
    vector<int> result;
    while (end != -1) 
    {
        result.push_back(end);
        end = parent[end];
    }
    for (int i = 0; i < result.size() / 2; ++i)
    {
        int doi = result[i];
        result[i] = result[result.size() - 1 - i];
        result[result.size() - 1 - i] = doi;
    }
    return result;
}

vector <int> bellmanFord(int start, int end, const vector <vector <int>>& adjMatrix) 
{
    vector <int> minS(adjMatrix.size(), INT_MAX), parent(adjMatrix.size(), -1);
    minS[start] = 0;
    for (int i = 0; i < adjMatrix.size() - 1; ++i) 
    {
        for (int u = 0; u < adjMatrix.size(); ++u) 
        {
            for (int v = 0; v < adjMatrix.size(); ++v)
            {
                if (adjMatrix[u][v] != 0 && minS[u] != INT_MAX && minS[u] + adjMatrix[u][v] < minS[v]) 
                {
                    minS[v] = minS[u] + adjMatrix[u][v];
                    parent[v] = u;
                }
            }
        }
    }
    for (int u = 0; u < adjMatrix.size(); ++u)
    {
        for (int v = 0; v < adjMatrix.size(); ++v)
        {
            if (adjMatrix[u][v] != 0 && minS[u] != INT_MAX && minS[u] + adjMatrix[u][v] < minS[v]) 
            {
                return vector <int> {};
            }
        }
    }
    if (minS[end] == INT_MAX) return vector <int> {};
    vector <int> result;
    while (end != -1) 
    {
        result.push_back(end);
        end = parent[end];
    }
    for (int i = 0; i < result.size() / 2; ++i)
    {
        int doi = result[i];
        result[i] = result[result.size() - 1 - i];
        result[result.size() - 1 - i] = doi;
    }
    if (result[0] != start) return {};
    return result;
}
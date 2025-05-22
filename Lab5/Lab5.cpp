#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <locale>

using namespace std;

// Функция для поиска кратчайшего пути с помощью поиска в ширину
vector<int> findShortestPath(const vector<vector<int>>& graph, int start, int end) {
    int n = graph.size();
    vector<bool> visited(n, false);
    vector<int> parent(n, -1);
    queue<int> q;

    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        if (current == end) {
            break; // Нашли конечную вершину
        }

        for (int neighbor = 0; neighbor < n; ++neighbor) {
            if (graph[current][neighbor] != 0 && !visited[neighbor]) {
                visited[neighbor] = true;
                parent[neighbor] = current;
                q.push(neighbor);
            }
        }
    }

    // Восстанавливаем путь от end к start
    vector<int> path;
    if (!visited[end]) {
        return path; // Путь не существует
    }

    for (int at = end; at != -1; at = parent[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());

    return path;
}

// Функция для чтения графа из файла
vector<vector<int>> readGraphFromFile(const string& filename, int& start, int& end) {
    ifstream input(filename);
    if (!input) {
        cerr << "Не удалось открыть файл " << filename << endl;
        exit(1);
    }

    int n;
    input >> n >> start >> end;

    vector<vector<int>> graph(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            input >> graph[i][j];
        }
    }

    return graph;
}

// Функция для записи результата в файл
void writeResultToFile(const string& filename, const vector<int>& path, int start, int end) {
    ofstream output(filename);
    if (!output) {
        cerr << "Не удалось создать файл " << filename << endl;
        return;
    }

    output << "Кратчайший путь между вершинами " << start << " и " << end << ":\n";
    if (path.empty()) {
        output << "Путь не существует\n";
    }
    else {
        for (size_t i = 0; i < path.size(); ++i) {
            if (i != 0) output << " -> ";
            output << path[i];
        }
        output << "\nДлина пути: " << path.size() - 1 << endl;
    }
}

int main() {

    setlocale(LC_ALL, "Russian");
    int start, end;

    // Чтение графа из файла
    vector<vector<int>> graph = readGraphFromFile("resources/input.txt", start, end);

    // Поиск кратчайшего пути
    vector<int> shortestPath = findShortestPath(graph, start, end);

    // Вывод результата на экран
    cout << "Кратчайший путь между вершинами " << start << " и " << end << ":\n";
    if (shortestPath.empty()) {
        cout << "Путь не существует\n";
    }
    else {
        for (size_t i = 0; i < shortestPath.size(); ++i) {
            if (i != 0) cout << " -> ";
            cout << shortestPath[i];
        }
        cout << "\nДлина пути: " << shortestPath.size() - 1 << endl;
    }

    // Запись результата в файл
    writeResultToFile("resources/output.txt", shortestPath, start, end);
}
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#include "vertex.cpp"

using namespace std;

// グラフデータを読み込む -> vector<Vertex>
vector<Vertex> read_graph_data(string path)
{
    fstream file(path);
    string line;

    int N;               // 頂点数
    string sigma;        // 入力期待文字列
    vector<Vertex> vtxs; // 頂点テーブル

    // 頂点数を取得
    getline(file, line);
    N = stoi(line);

    // sigmaを取得
    getline(file, line);
    sigma = line;

    // 頂点テーブルを初期化
    vtxs.resize(N, Vertex(0, sigma.size()));
    for (int i = 0; i < N; i++)
    {
        vtxs[i].id = i;
    }

    // pathを登録
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < sigma.size(); j++)
        {
            //(n文字目の遷移作の頂点番号)を登録
            getline(file, line);
            stringstream ss{line};
            string s;
            while (getline(ss, s, ' '))
            {
                vtxs[i].to[j].push_back(stoi(s));
            }
        }
    }

    return vtxs;
}

int main()
{
    /*
    How to input graph data.
    N(int) 頂点の数
    sigma(str)
    (sigmaの文字の長さだけ繰り返す)
    (1文字目の遷移先の頂点番号)
    (n文字目の遷移作の頂点番号)
    */

    read_graph_data("sample.txt");

    return 0;
}

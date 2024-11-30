#pragma once

#include <iostream>
#include <vector>

using namespace std;

// 頂点
struct Vertex
{
    int id;
    string lambda;
    string sigma;
    vector<vector<int>> to;

    Vertex(int i, int t)
    {
        id = i;
        to.resize(t, vector<int>(0));
    }

    string get_lambda()
    {
        return lambda;
    }

    // dot言語化
    string to_str()
    {
        string out;
        for (int i = 0; i < to.size(); i++)
        {
            for (int j = 0; j < to[i].size(); j++)
            {
                out += "    ";
                out += "q_" + to_string(id) + " -> " + "q_" + to_string(to[i][j]);
                out += " [label=" + to_string(i) + "];";
                // out += " " + lambda;
                out += "\n";
            }
        }
        return out;
    }
};

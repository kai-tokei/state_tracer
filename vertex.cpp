#pragma once

#include <vector>
#include <iostream>

using namespace std;

// 頂点
struct Vertex
{
    int id;
    vector<vector<int>> to;

    Vertex(int i, int t)
    {
        id = i;
        to.resize(t);
    }

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
                out += "\n";
            }
        }
        return out;
    }
};
#pragma once

#include <string>
#include <fstream>
#include <vector>

using namespace std;

class Field {
public:
    Field();
    Field(int n, int m);
    Field(string filename);
    friend ostream& operator<<(ostream& , Field&);
    int width = 0;
    int height = 0;
    vector<vector<int> > field;
};

Field::Field(int n, int m) {
    srand(time(NULL));
    height = n;
    width = m;
    for (int i = 0; i < n; i++) {
        vector<int> current_row(m);
        for (int j = 0; j < m; j++) {
            current_row[j] = rand() % 2;
        }
        field.push_back(current_row);
    }
}

Field::Field() {
    height = 0;
    width = 0;
}

ostream& operator<<(ostream& out, Field& other){
    for (int i = 0; i < other.height; i++) {
        for (int j = 0; j < other.width; j++) {
            out << other.field[i][j] << " ";
        }
        out << "\n";
    }
    return out;
}
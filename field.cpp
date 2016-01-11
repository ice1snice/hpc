//#include "field.h"


/*
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
*/
/*
Field::Field(string filename) {
    ifstream fin(filename);
    int n, m;
    fin >>  n >> m;
    height = n;
    width = m;
    vector<int> current_row(n);
    for (int i = 0; i < n; i++) {
        string curr_row_str;
        fin >> curr_row_str;
        for (int j = 0; j < n; j++) {
            if (curr_row_str[j] == '0') {
                current_row[j] = 0;
            } else {
                current_row[j] = 1;
            }
        }
        field.push_back(current_row);
    }
}
*/
/*
ostream& operator<<(ostream& out, Field& other){
    for (int i = 0; i < other.height; i++) {
        for (int j = 0; j < other.width; j++) {
            out << other.field[i][j] << " ";
        }
        out << "\n";
    }
    return out;
}*/
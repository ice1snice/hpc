#pragma once

vector<int> adj_cells_y;
vector<int> adj_cells_x;

int calculate_one(int** field, int n, int m, int width) {
    adj_cells_y.push_back(0);
    adj_cells_y.push_back(0);
    adj_cells_y.push_back(-1);
    adj_cells_y.push_back(-1);
    adj_cells_y.push_back(-1);
    adj_cells_y.push_back(1);
    adj_cells_y.push_back(1);
    adj_cells_y.push_back(1);
    adj_cells_x.push_back(1);
    adj_cells_x.push_back(-1);
    adj_cells_x.push_back(-1);
    adj_cells_x.push_back(0);
    adj_cells_x.push_back(1);
    adj_cells_x.push_back(-1);
    adj_cells_x.push_back(0);
    adj_cells_x.push_back(1);


    int active_neighbour = 0;
    for (int i = 0; i < 8; i++) {
        
        int i1 = n + adj_cells_y[i];
        int j1 = m + adj_cells_x[i];
        //if (i1 < 0) {i1 = field->height - 1;}
        if (j1 < 0) {j1 = width - 1;}
        //if (i1 >= field->height) {i1 = 0;}
        if (j1 > width) {j1 = 0;}
        
        active_neighbour += field[i1][j1];
    }
    
    if (field[n][m] == 1) {
        if (active_neighbour >= 2 && active_neighbour <= 3) {
            return 1;
        }
    }
    if (field[n][m] == 0) {
        if (active_neighbour == 3) {
            return 1;
        }
    }
    return 0;
}

int calculate_one_vect(Field* field, int n, int m) {
    adj_cells_y.push_back(0);
    adj_cells_y.push_back(0);
    adj_cells_y.push_back(-1);
    adj_cells_y.push_back(-1);
    adj_cells_y.push_back(-1);
    adj_cells_y.push_back(1);
    adj_cells_y.push_back(1);
    adj_cells_y.push_back(1);
    adj_cells_x.push_back(1);
    adj_cells_x.push_back(-1);
    adj_cells_x.push_back(-1);
    adj_cells_x.push_back(0);
    adj_cells_x.push_back(1);
    adj_cells_x.push_back(-1);
    adj_cells_x.push_back(0);
    adj_cells_x.push_back(1);
    int active_neighbour = 0;
    for (int i = 0; i < 8; i++) {
        int i1 = n + adj_cells_y[i];
        int j1 = m + adj_cells_x[i];
        if (i1 < 0) {i1 = field->height - 1;}
        if (j1 < 0) {j1 = field->width - 1;}
        if (i1 >= field->height) {i1 = 0;}
        if (j1 > field->width) {j1 = 0;}
        
        active_neighbour += field->field[i1][j1];
    }
    
    if (field->field[n][m] == 1) {
        if (active_neighbour >= 2 && active_neighbour <= 3) {
            return 1;
        }
    }
    if (field->field[n][m] == 0) {
        if (active_neighbour == 3) {
            return 1;
        }
    }
    return 0;
}
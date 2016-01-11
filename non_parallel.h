void run_non_parallel (Field* field, int num_of_steps) {
    Field new_field;
    vector<int> empty_row(field->width);
    for (int i = 0; i < field->height; i++) {
        new_field.field.push_back(empty_row);
    }
    for (int k = 0; k < num_of_steps; k++) {
        for (int i = 0; i < field->height; i++) {
            for (int j = 0; j < field->width; j++) {
                new_field.field[i][j] = calculate_one_vect(field, i, j);
            }
        }
        
        for (int i = 0; i < field->height; i++) {
            for (int j = 0; j < field->width; j++) {
                field->field[i][j] = new_field.field[i][j];
            }
        }
    }
}
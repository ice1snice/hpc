#pragma once

#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <mpi.h>

#include "field_operations.h"

using namespace std;

void translate_matrix_to_vector(vector<vector<int> > field, int* message, int left, int right, int width) {
    for(int i = left; i <= right; i++) {
        for (int j = 0; j < width; j++) {
            message[(i - left)*width + j] = field[i][j];
            
        }
    }
}

void translate_int_matrix_to_vector(int** field, int* message, int left, int right, int width) {
    for(int i = left; i <= right; i++) {
        for (int j = 0; j < width; j++) {
            message[(i - left)*width + j] = field[i][j];
        }
    }
}

void translate_vector_to_matrix(int* buffer, int** field, int left, int right, int width) {
    for (int i = left; i  <= right; i++) {
        for (int j = 0; j < width; j++) {
            field[i][j] = buffer[(i - left) * width + j];
        }
    }
}

void workers_computations(int rank, int m, int number_of_steps, int number_of_workers) {
    //вычисляем ранги соседей
    int left_rank, right_rank;
    left_rank = rank - 1;
    if (left_rank == 0)
        left_rank = number_of_workers;
    right_rank = rank + 1;
    if (right_rank > number_of_workers)
        right_rank = 1;

    char continuation_bit = 1;
    MPI_Request request;

    //принимаем сообщение о кол-ве строчек
    int n;
    MPI_Recv(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    //принимаем сами строчки
    int* recv_buffer = new int[n * m];
    MPI_Recv(recv_buffer, n * m, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    //делаем 2 копии поля с пустыми 0-ой и последней строчками
    int** field = new int*[n + 2];
    int** new_field= new int*[n + 2];
    for(int i = 0; i < n + 2; i++) {
        field[i] = new int[m];
        new_field[i] = new int[m];
    }
    translate_vector_to_matrix(recv_buffer, field, 1, n, m);
    delete[] recv_buffer;

    if (rank == 1) {
        MPI_Irecv(&continuation_bit, 1, MPI_CHAR, 0, 13, MPI_COMM_WORLD, &request); 
    } else {
        MPI_Irecv(&number_of_steps, 1, MPI_INT, 1, number_of_steps + 1, MPI_COMM_WORLD, &request);
    }

    for (int k = 0; k < number_of_steps; k++) {
        
        if (rank == 1) {
            if (continuation_bit == 0) {
                int process;
                int u = k + number_of_workers / 2;
                for (process = 2; process < number_of_workers + 1; process++) {
                    MPI_Ssend(&u, 1, MPI_INT, process, number_of_steps + 1, MPI_COMM_WORLD);
                }
                number_of_steps = u;
                continuation_bit = 1;
            }
        }
        
        MPI_Sendrecv(field[n], m, MPI_INT, right_rank, k, 
                     field[0], m, MPI_INT, left_rank, k, 
                     MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Sendrecv(field[1], m, MPI_INT, left_rank, k,
                     field[n + 1], m, MPI_INT, right_rank, k, 
                     MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (int i = 1; i < n + 1; i++) {
            for (int j = 0; j < m; j++) {
                new_field[i][j] = calculate_one(field, i, j, m);
            }
        }
        for (int i = 0; i < n + 2; i++) {
            for (int j = 0; j < m; j++) {
                field[i][j] = new_field[i][j];
            }
        }
    }
    int* send_buffer = new int[n * m];
    translate_int_matrix_to_vector(field, send_buffer, 1, n, m);
    MPI_Send(send_buffer, n * m, MPI_INT, 0, 0, MPI_COMM_WORLD);
    delete[] send_buffer;
    for (int i = 0; i < n + 2; i++) {
        delete[] field[i];
        delete[] new_field[i];
    }
    delete[] field;
    delete[] new_field;
}
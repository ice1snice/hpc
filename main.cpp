#include "field.h"
#include "parallel.h"
#include "non_parallel.h"
#include "field_operations.h"

#include <mpi.h>
#include <iostream>
#include <ctime>
#include <sys/time.h>

#define N 2000
#define M 100
#define number_of_steps 100

using namespace std;

int main(int argc, char** argv) {
    int number_of_nodes, rank;

    Field test1(N, M);
    Field test2(test1);
    //cout << test1 << "\n";
    double t;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &number_of_nodes);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);    
    int number_of_workers = number_of_nodes - 1;

    if (rank == 0) {
        t = MPI_Wtime();
        int segment_size = test1.height / number_of_workers;
        vector<pair<int, int> > border(number_of_workers);
        for (int i = 0; i < number_of_workers - 1; i++) {
            border[i].first = i * segment_size;
            border[i].second = ((i + 1) * segment_size) - 1;
        }
        border[number_of_workers - 1].first = (number_of_workers - 1) * segment_size;
        border[number_of_workers - 1].second = test1.height - 1;

        for (int i = 0; i < number_of_workers; i++) {
            int count = border[i].second - border[i].first + 1;
            int* message = new int[count * M];
            translate_matrix_to_vector(test1.field, message, border[i].first, border[i].second, M);
            /*
            for(int i = border[i].first; i <= border[i].second; i++) {
                for(int j = 0; j < M; j++) {
                cout << message[(i - border[i].first)*M + j] << " ";
                }
            }
            cout << "\n";
            */
            MPI_Send(&count, 1, MPI_INT, i + 1, 0, MPI_COMM_WORLD);
            MPI_Send(message, count * M, MPI_INT, i + 1, 1, MPI_COMM_WORLD);
            delete[] message;
        }

        int** answer_matrix = new int*[N];
        for(int i = 0; i < N; i++) {
            answer_matrix[i] = new int[M];
        }

        for (int i = 0; i < number_of_workers; i++) {
            int buffer_size = (border[i].second - border[i].first + 1) * M;
            int* buffer = new int[buffer_size];
            MPI_Recv(buffer, buffer_size, MPI_INT, i + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            translate_vector_to_matrix(buffer, answer_matrix, border[i].first, border[i].second, M);
            delete[] buffer;
        }
        t = MPI_Wtime() - t;
        cout << "Parallel time: " << t << "\n";
        t = MPI_Wtime();
        run_non_parallel(&test2, number_of_steps);
        t = MPI_Wtime() - t;
        cout << "Non-Parallel time: " << t << "\n";
        //освобождаем память
        /*
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
                if (answer_matrix[i][j] != test2.field[i][j]) {
                    cout << "Results are not equal!\n";
                    
                    for(int i = 0; i < N; i++) {
                        delete[] answer_matrix[i];
                    }       
                    delete[] answer_matrix;
                    
                    MPI_Finalize();
                    return 0;
                }
            }
        }
        */

        for(int i = 0; i < N; i++) {
            delete[] answer_matrix[i];
        }
        delete[] answer_matrix;

    } else {
        workers_computations(rank, M, number_of_steps, number_of_workers);
    }    

    
    MPI_Finalize();

    return 0;
}

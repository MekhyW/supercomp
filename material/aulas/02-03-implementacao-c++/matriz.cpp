#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
using namespace std;

void readInput(const char *filename, int &n, vector<vector<double>> &matrix) {
    ifstream input(filename);
    if (!input.is_open()) {
        cerr << "Error opening file " << filename << endl;
        exit(1);
    }
    input >> n;
    for (int i = 0; i < n; i++) {
        matrix.push_back(vector<double>(2));
        input >> matrix[i][0] >> matrix[i][1];
    }
    input.close();
}

void calcDistances(int n, const vector<vector<double>> &matrix, vector<vector<double>> &D) {
    D.resize(n, vector<double>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i > j) continue;
            int DX = matrix[i][0] - matrix[j][0];
            int DY = matrix[i][1] - matrix[j][1];
            D[i][j] = sqrt(DX * DX + DY * DY);
            D[j][i] = D[i][j];
        }
    }
}

void writeOutput(const char *filename, int n, const vector<vector<double>> &D) {
    string output_filename(filename);
    output_filename.replace(output_filename.find("in"), 2, "out");
    ofstream output(output_filename);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            output << D[i][j] << " ";
        }
        output << endl;
    }
    output.close();
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <input file>" << endl;
        return 1;
    }
    int n;
    vector<vector<double>> matrix;
    readInput(argv[1], n, matrix);
    vector<vector<double>> D(n, vector<double>(n));
    calcDistances(n, matrix, D);
    writeOutput(argv[1], n, D);
    return 0;
}
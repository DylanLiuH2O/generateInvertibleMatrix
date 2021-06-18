/*
 * @Author: dylan
 * @Date: 2021-06-14 13:13:09
 * @LastEditTime: 2021-06-14 16:28:15
 * @LastEditors: dylan
 * @Description: generate an invertibale n-order matrix
 * @FilePath: /paraMatInver/tools/genInvertibaleMat.cc
 */
#include <iostream>
#include <fstream>
#include <exception>
#include <algorithm>
#include <random>
#include <vector>

using namespace std;

template<typename T>
void rowSwitch(vector<vector<T>> &mat, int row1, int row2);
template<typename T, typename U>
void rowMultiply(vector<vector<T>> &mat, int row1, U factor);
template<typename T, typename U>
void rowAddition(vector<vector<T>> &mat, int row1, int row2, U times);

int main(int argc, char *argv[])
{
    if (argc != 4 && argc != 5) {
        cerr << "usage: " << argv[0] << " <iterations> <order> <filename> [int/double] \n";
        exit(1);
    }

    int iterations;
    int order;
    string filename   = argv[3];
    string numberType = (argc == 5) ? argv[4] : "";

    try {
        iterations  = stoi(argv[1]);
        order       = stoi(argv[2]);
    } catch (invalid_argument) {
        cerr << "invalid argument\n";
        exit(1);
    } catch (out_of_range) {
        cerr << "out of range\n";
        exit(1);
    }

    if (argc == 5 && numberType != "int" && numberType != "double") {
        cerr << "number type error\n";
        exit(1);
    }

#if true
    cout << "argc: " << argc << "\n";
    cout << "iterations: " << iterations << "\n";
    cout << "order: " << order << "\n";
    cout << "filename: " << filename << "\n";
    if (numberType != "") {
        cout << "numberType: " << numberType << "\n";
        // cout << (numberType == "int") << " " << (numberType == "double") << "\n";
    }
#endif

    /* create an identity matrix */
    vector<vector<double>> mat(order, vector<double>(order, 0));
    for (int i = 0; i < order; i++) {
        mat[i][i] = 1.0;
    }

    enum class rowTransType {
        SWITCH   = 0, 
        MULTIPLY = 1, 
        ADDITION = 2
    };
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int>   randomType(0, 2);
    uniform_int_distribution<int>   randomRow(0, order-1);
    uniform_int_distribution<int>   randomFactorInt(1, 5);
    uniform_int_distribution<int>   randomTimesInt(1, 10);
    uniform_real_distribution<double>  randomFactorDouble(1, 5);
    uniform_real_distribution<double>  randomTimesDouble(1, 10);

    for (int i = 0; i < iterations; i++) {
        rowTransType type = (rowTransType)randomType(gen);
        int row1     = randomRow(gen);
        int row2     = randomRow(gen);
        while ((row2 = randomRow(gen)) == row1) { }

        int timesInt        = randomTimesInt(gen);
        int factorInt       = randomFactorInt(gen);
        double timesDouble  = randomTimesInt(gen);
        double factorDouble = randomFactorDouble(gen);;
        switch (type) {
            case rowTransType::SWITCH:
                rowSwitch(mat, row1, row2);
                break;
            case rowTransType::MULTIPLY:
                if (numberType == "int"){
                    rowMultiply(mat, row1, factorInt);
                } else {
                    rowMultiply(mat, row1, factorDouble);
                }
                break;
            case rowTransType::ADDITION:
                if (numberType == "int"){
                    rowAddition(mat, row1, row2, timesInt);
                } else {
                    rowAddition(mat, row1, row2, timesDouble);
                }
                break;
            default:
                break;
        }
    }

    /* open file */
    ofstream out;
    out.open(filename);
    if (!out) {
        cerr << "file \"" << filename << "\" open error\n";
        exit(1);
    }

    /* output matrix to file */
    // out << order << " " << order << " " << order << "\n";
    out << order << "\n";
    for (int i = 0; i < order; i++) {
        for (int j = 0; j < order; j++) {
            if (mat[i][j] != 0) {
                out << i << " " << j << " " << mat[i][j] << "\n";
            }
        }
    }

    /* close file */
    out.close();

    return 0;
}

template<typename T>
void rowSwitch(vector<vector<T>> &mat, int row1, int row2)
{
    const int order = mat.size();

    for (int j = 0; j < order; j++) {
        swap(mat[row1][j], mat[row2][j]);
    }
}

template<typename T, typename U>
void rowMultiply(vector<vector<T>> &mat, int row, U factor)
{
    if (factor == 0) {
        return;
    }
    const int order = mat.size();

    for (int j = 0; j < order; j++) {
        mat[row][j] *= factor;
    }
}

template<typename T, typename U>
void rowAddition(vector<vector<T>> &mat, int row1, int row2, U times)
{
    const int order = mat.size();

    for (int j = 0; j < order; j++) {
        mat[row1][j] += mat[row2][j] * times;
    }
}
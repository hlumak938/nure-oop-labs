#include <iostream>
#include <vector>
using namespace std;

int main() {
    int row, column;
    cout << "Enter size of matrix:[row; column]" << endl;
    cin >> row >> column;

    vector <vector <int>> matrix(row);

    cout << "Enter matrix: " << endl;
    for (int i = 0; i < row; ++i)
    {
        matrix[i].resize(column);
        for (int j = 0; j < column; ++j)
        {
            cin >> matrix[i][j];
        }
    }

    cout << endl;

    vector <int> NegativeValues;

    int sum;
    for (int i = 0; i < row; ++i) {
        sum = 0;
        for (int j = 0; j < column; ++j) {
            if (matrix[i][j] > 0)
                sum += matrix[i][j];
        }
        NegativeValues.push_back(sum);
    }

    for (int i = 0; i < NegativeValues.size(); ++i) {
        if (NegativeValues[i] == 0) {
            cout << "\nCount of elements after 0 = " << NegativeValues.size() - 1 - i << endl;
            break;
        }
        cout << NegativeValues[i] << "  ";
    }
    return 0;
}

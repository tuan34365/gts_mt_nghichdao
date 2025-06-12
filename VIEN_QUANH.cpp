#include <iostream>
#include <iomanip>
using namespace std;

// Ham in ma tran
void printMatrix(double** matrix, int n, int step) {
    cout << "\nBuoc " << step << ":\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2 * n; j++) {
            cout << fixed << setprecision(4) << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

// Ham tim ma tran nghich dao
bool inverseMatrix(double** matrix, int n) {
    // Tao ma tran mo rong: [A|I]
    double** augmented = new double* [n];
    for (int i = 0; i < n; i++) {
        augmented[i] = new double[2 * n];
        for (int j = 0; j < n; j++) {
            augmented[i][j] = matrix[i][j]; // Sao chep ma tran A
            augmented[i][j + n] = (i == j) ? 1.0 : 0.0; // Ma tran don vi I
        }
    }

    cout << "Ma tran mo rong ban dau [A|I]:\n";
    printMatrix(augmented, n, 0);

    // Phuong phap Gauss-Jordan
    int step = 1;
    for (int i = 0; i < n; i++) {
        // Tim phan tu chinh (pivot)
        if (augmented[i][i] == 0) {
            cout << "Phan tu chinh bang 0 tai vi tri (" << i << "," << i << "). Ma tran khong kha nghich!\n";
            return false;
        }

        // Chuan hoa hang i (pivot = 1)
        double pivot = augmented[i][i];
        for (int j = 0; j < 2 * n; j++) {
            augmented[i][j] /= pivot;
        }
        cout << "\nChuan hoa hang " << i + 1 << " (pivot = 1):";
        printMatrix(augmented, n, step++);

        // Loai bo cot i o cac hang khac
        for (int k = 0; k < n; k++) {
            if (k != i) {
                double factor = augmented[k][i];
                for (int j = 0; j < 2 * n; j++) {
                    augmented[k][j] -= factor * augmented[i][j];
                }
            }
        }
        cout << "\nLoai bo cot " << i + 1 << " o cac hang khac:";
        printMatrix(augmented, n, step++);
    }

    // Kiem tra ma tran don vi
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j && augmented[i][j] != 1 || i != j && augmented[i][j] != 0) {
                cout << "Ma tran khong kha nghich!\n";
                return false;
            }
        }
    }

    // Sao chep ma tran nghich dao vao ma tran ket qua
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = augmented[i][j + n];
        }
    }

    // Giai phong bo nho
    for (int i = 0; i < n; i++) {
        delete[] augmented[i];
    }
    delete[] augmented;
    return true;
}

int main()
{
    freopen("input.txt", "r", stdin);
    int n;
    cout << "Nhap kich thuoc ma tran vuong n: ";
    cin >> n;

    // Kiem tra kich thuoc hop le
    if (n <= 0) {
        cout << "Kich thuoc ma tran khong hop le!\n";
        return 1;
    }

    // Cap phat dong ma tran
    double** matrix = new double* [n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new double[n];
    }

    // Nhap ma tran
    cout << "Nhap cac phan tu cua ma tran:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "A[" << i + 1 << "][" << j + 1 << "] = ";
            cin >> matrix[i][j];
        }
    }

    // In ma tran goc
    cout << "\nMa tran goc:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << fixed << setprecision(4) << matrix[i][j] << "\t";
        }
        cout << endl;
    }

    // Tim ma tran nghich dao
    if (inverseMatrix(matrix, n)) {
        cout << "\nMa tran nghich dao:\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << fixed << setprecision(4) << matrix[i][j] << "\t";
            }
            cout << endl;
        }
    }

    // Giai phong bo nho
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}

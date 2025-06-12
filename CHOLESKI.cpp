#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// Ham in ma tran
void printMatrix(double** A, int n, string name) {
    cout << name << ":\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << fixed << setprecision(4) << A[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

// Ham phan ra Cholesky
bool choleskyDecomposition(double** A, double** L, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            double sum = 0;
            if (j == i) { // Tinh phan tu duong cheo
                for (int k = 0; k < j; k++)
                    sum += pow(L[j][k], 2);
                if (A[j][j] - sum <= 0) {
                    cout << "Ma tran khong duong xac dinh.\n";
                    return false;
                }
                L[j][j] = sqrt(A[j][j] - sum);
                cout << "Buoc " << i + 1 << ": Tinh L[" << j << "][" << j << "] = sqrt(A[" << j << "][" << j << "] - sum) = "
                     << L[j][j] << endl;
            } else { // Tinh phan tu ngoai duong cheo
                for (int k = 0; k < j; k++)
                    sum += L[i][k] * L[j][k];
                if (L[j][j] == 0) {
                    cout << "L[j][j] = 0, khong the tinh L[" << i << "][" << j << "].\n";
                    return false;
                }
                L[i][j] = (A[i][j] - sum) / L[j][j];
                cout << "Buoc " << i + 1 << ": Tinh L[" << i << "][" << j << "] = (A[" << i << "][" << j << "] - sum) / L["
                     << j << "][" << j << "] = " << L[i][j] << endl;
            }
        }
        printMatrix(L, n, "Ma tran L sau buoc " + to_string(i + 1));
    }
    return true;
}

// Ham giai he phuong trinh Ly = b
void forwardSubstitution(double** L, double* b, double* y, int n) {
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < i; j++)
            sum += L[i][j] * y[j];
        y[i] = (b[i] - sum) / L[i][i];
        cout << "The xuoi: y[" << i << "] = (b[" << i << "] - sum) / L[" << i << "][" << i << "] = " << y[i] << endl;
    }
}

// Ham giai he phuong trinh L^T x = y
void backwardSubstitution(double** L, double* y, double* x, int n) {
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0;
        for (int j = i + 1; j < n; j++)
            sum += L[j][i] * x[j];
        x[i] = (y[i] - sum) / L[i][i];
        cout << "The nguoc: x[" << i << "] = (y[" << i << "] - sum) / L[" << i << "][" << i << "] = " << x[i] << endl;
    }
}

// Ham tim ma tran nghich dao
void inverseMatrix(double** L, double** inv, int n) {
    double* b = new double[n];
    double* y = new double[n];
    double* x = new double[n];

    for (int j = 0; j < n; j++) {
        // Tao vector don vi e_j
        for (int i = 0; i < n; i++)
            b[i] = (i == j) ? 1.0 : 0.0;

        cout << "\nGiai he cho cot " << j + 1 << " cua ma tran nghich dao:\n";
        cout << "Vector b: ";
        for (int i = 0; i < n; i++) cout << b[i] << " ";
        cout << endl;

        // Giai Ly = b
        forwardSubstitution(L, b, y, n);
        // Giai L^T x = y
        backwardSubstitution(L, y, x, n);

        // Luu cot x vao ma tran nghich dao
        for (int i = 0; i < n; i++)
            inv[i][j] = x[i];
    }

    delete[] b;
    delete[] y;
    delete[] x;
}

// Ham chinh
int main()
{
    freopen("input.txt", "r", stdin);
    int n;
    cout << "Nhap kich thuoc ma tran (n): ";
    cin >> n;

    // Cap phat ma tran
    double** A = new double*[n];
    double** L = new double*[n];
    double** inv = new double*[n];
    for (int i = 0; i < n; i++) {
        A[i] = new double[n];
        L[i] = new double[n];
        inv[i] = new double[n];
        for (int j = 0; j < n; j++) {
            L[i][j] = 0;
            inv[i][j] = 0;
        }
    }

    // Nhap ma tran
    cout << "Nhap ma tran A (" << n << "x" << n << "):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> A[i][j];

    printMatrix(A, n, "Ma tran A");

    // Phan ra Cholesky
    cout << "\n=== Phan ra Cholesky ===\n";
    if (!choleskyDecomposition(A, L, n)) {
        cout << "Khong the phan ra Cholesky.\n";
        return 1;
    }

    // Tim ma tran nghich dao
    cout << "\n=== Tim ma tran nghich dao ===\n";
    inverseMatrix(L, inv, n);

    // In ma tran nghich dao
    printMatrix(inv, n, "Ma tran nghich dao");

    // Giai phong bo nho
    for (int i = 0; i < n; i++) {
        delete[] A[i];
        delete[] L[i];
        delete[] inv[i];
    }
    delete[] A;
    delete[] L;
    delete[] inv;

    return 0;
}

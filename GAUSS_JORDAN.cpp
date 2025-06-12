#include "bits/stdc++.h"
using namespace std;

// Kích thước tối đa của ma trận
const int MAX = 10;

// Hàm in ma trận (gốc và đơn vị cạnh nhau)
void printStep(double matrix[MAX][MAX], double inverse[MAX][MAX], int n, int step) {
    cout << "\nBuoc " << step << ":\n";
    cout << "Ma tran ket hop:\n";
    for (int i = 0; i < n; i++) {
        // In ma trận gốc
        for (int j = 0; j < n; j++) {
            cout << fixed << setprecision(4) << matrix[i][j] << "\t";
        }
        cout << " | ";
        // In ma trận đơn vị (đang biến đổi thành nghịch đảo)
        for (int j = 0; j < n; j++) {
            cout << fixed << setprecision(4) << inverse[i][j] << "\t";
        }
        cout << endl;
    }
}

// Hàm tìm ma trận nghịch đảo bằng Gauss-Jordan
bool inverseMatrix(double matrix[MAX][MAX], double inverse[MAX][MAX], int n) {
    // Tạo ma trận đơn vị
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inverse[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    int step = 0;
    // In ma trận ban đầu
    printStep(matrix, inverse, n, step++);

    // Phương pháp Gauss-Jordan
    for (int i = 0; i < n; i++) {
        // Kiểm tra phần tử chéo chính
        if (matrix[i][i] == 0) {
            cout << "Ma tran khong kha nghich!" << endl;
            return false;
        }

        // Chuẩn hóa hàng i (đưa phần tử chéo chính về 1)
        double pivot = matrix[i][i];
        for (int j = 0; j < n; j++) {
            matrix[i][j] /= pivot;
            inverse[i][j] /= pivot;
        }
        cout << "\nSau khi chuan hoa hang " << i + 1 << " (pivot = " << pivot << "):";
        printStep(matrix, inverse, n, step++);

        // Biến các cột khác về 0
        for (int k = 0; k < n; k++) {
            if (k != i) {
                double factor = matrix[k][i];
                for (int j = 0; j < n; j++) {
                    matrix[k][j] -= factor * matrix[i][j];
                    inverse[k][j] -= factor * inverse[i][j];
                }
                cout << "\nSau khi bien doi hang " << k + 1 << " (factor = " << factor << "):";
                printStep(matrix, inverse, n, step++);
            }
        }
    }
    return true;
}

int main()
{
    freopen("input.txt", "r", stdin);
    int n;
    double matrix[MAX][MAX], inverse[MAX][MAX];

    // Nhập kích thước ma trận
    cout << "Nhap kich thuoc ma tran vuong (n): ";
    cin >> n;

    // Kiểm tra kích thước hợp lệ
    if (n <= 0 || n > MAX) {
        cout << "Kich thuoc ma tran khong hop le!" << endl;
        return 1;
    }

    // Nhập ma trận
    cout << "Nhap cac phan tu cua ma tran (" << n << "x" << n << "):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "a[" << i << "][" << j << "] = ";
            cin >> matrix[i][j];
        }
    }

    // Tìm ma trận nghịch đảo
    if (inverseMatrix(matrix, inverse, n)) {
        // In ma trận nghịch đảo cuối cùng
        cout << "\nMa tran nghich dao cuoi cung:\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << fixed << setprecision(4) << inverse[i][j] << "\t";
            }
            cout << endl;
        }
    }

    return 0;
}

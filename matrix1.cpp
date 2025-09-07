#include <iostream>
using namespace std;

// Structure to represent a sparse matrix element
struct Element {
    int row;
    int col;
    int value;
};

// Class to represent a sparse matrix
class SparseMatrix {
private:
    int rows, cols, numElements;
    Element* elements;

public:
    // Constructor
    SparseMatrix(int r, int c, int n) {
        rows = r;
        cols = c;
        numElements = n;
        elements = new Element[numElements];
    }

    // Destructor
    ~SparseMatrix() {
        delete[] elements;
    }

    // Input sparse matrix
    void read() {
        cout << "Enter row, column, and value for each non-zero element:\n";
        for (int i = 0; i < numElements; i++) {
            cin >> elements[i].row >> elements[i].col >> elements[i].value;
        }
    }

    // Display sparse matrix in full 2D form
    void display() {
        int k = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (k < numElements && elements[k].row == i && elements[k].col == j) {
                    cout << elements[k++].value << " ";
                } else {
                    cout << "0 ";
                }
            }
            cout << endl;
        }
    }

    // Add two sparse matrices
    SparseMatrix add(SparseMatrix& other) {
        if (rows != other.rows || cols != other.cols) {
            throw invalid_argument("Matrix dimensions do not match for addition.");
        }

        SparseMatrix result(rows, cols, numElements + other.numElements);
        int i = 0, j = 0, k = 0;

        while (i < numElements && j < other.numElements) {
            if (elements[i].row < other.elements[j].row ||
                (elements[i].row == other.elements[j].row && elements[i].col < other.elements[j].col)) {
                result.elements[k++] = elements[i++];
            } else if (elements[i].row > other.elements[j].row ||
                       (elements[i].row == other.elements[j].row && elements[i].col > other.elements[j].col)) {
                result.elements[k++] = other.elements[j++];
            } else {
                // Same row and column
                result.elements[k] = elements[i];
                result.elements[k++].value = elements[i++].value + other.elements[j++].value;
            }
        }

        while (i < numElements) result.elements[k++] = elements[i++];
        while (j < other.numElements) result.elements[k++] = other.elements[j++];

        result.numElements = k; // update number of elements
        return result;
    }
};

// Main function to test
int main() {
    int r, c, n;

    cout << "Enter rows, columns, and number of non-zero elements for Matrix A: ";
    cin >> r >> c >> n;
    SparseMatrix A(r, c, n);
    A.read();

    cout << "Enter rows, columns, and number of non-zero elements for Matrix B: ";
    cin >> r >> c >> n;
    SparseMatrix B(r, c, n);
    B.read();

    cout << "\nMatrix A:" << endl;
    A.display();

    cout << "\nMatrix B:" << endl;
    B.display();

    try {
        SparseMatrix C = A.add(B);
        cout << "\nResult of A + B:" << endl;
        C.display();
    } catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}

#include <iostream>
#include <vector>

using namespace std;

class Matrix {
public:

    Matrix (): col(0), row(0) {}

    Matrix (const int& new_row, const int& new_col) {
        Reset (new_row, new_col);
    }

    void Reset (const int& new_row, const int& new_col) {
        if (new_row < 0 or new_col < 0) {
            throw out_of_range("At least one of parameters is negative");
        }
        row = new_row;
        col = new_col;
        vec = vector<vector<double>>(row, vector<double>(col, 0));
    }

    double At (const int& i, const int& j) const {
        return vec.at(i).at(j);
    }

    double& At (const int& i, const int& j) {
        return vec.at(i).at(j);
    }
    int GetNumRows () const {
        return row;
    }

    int GetNumColumns () const {
        return col;
    }


private:
    vector<vector<double>> vec;
    int col, row;
};

istream& operator>> (istream& istr, Matrix& m) {
    int r, c;
    istr >> r >> c;
    m.Reset(r, c);
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            istr >> m.At(i, j);
        }
    }

    return istr;
}

ostream& operator<< (ostream& ostr, const Matrix& m) {
    ostr << m.GetNumRows() << " " << m.GetNumColumns() << endl;
    for (int i = 0; i < m.GetNumRows(); ++i) {
        for (int j = 0; j < m.GetNumColumns(); ++j) {
            ostr << m.At(i,j) << " ";
        }
        ostr << endl;
    }

    return ostr;
}

bool operator== (const Matrix& m1, const Matrix& m2) {
    if (m1.GetNumRows() == m2.GetNumRows() and m1.GetNumColumns() == m2.GetNumColumns()) {
        for (int i = 0; i < m1.GetNumRows(); ++i) {
            for (int j = 0; j < m1.GetNumColumns(); ++j) {
                if (m1.At(i, j) != m2.At(i, j)) {
                    return false;
                }
            }
        }
    } else {
        return false;
    }
    return true;
}

Matrix operator+ (const Matrix& m1, const Matrix& m2) {
    if (m1.GetNumRows() == m2.GetNumRows() and m1.GetNumColumns() == m2.GetNumColumns()) {
        Matrix ans(m1.GetNumRows(), m1.GetNumColumns());
        for (int i = 0; i < m1.GetNumRows(); ++i) {
            for (int j = 0; j < m1.GetNumColumns(); ++j) {
                ans.At(i, j) = m1.At(i, j) + m2.At(i, j);
            }
        }
        return ans;
    } else {
        throw invalid_argument("Matrices have different size");
    }
}

Matrix operator- (const Matrix& m1, const Matrix& m2) {
    if (m1.GetNumRows() == m2.GetNumRows() and m1.GetNumColumns() == m2.GetNumColumns()) {
        Matrix ans(m1.GetNumRows(), m1.GetNumColumns());
        for (int i = 0; i < m1.GetNumRows(); ++i) {
            for (int j = 0; j < m1.GetNumColumns(); ++j) {
                ans.At(i, j) = m1.At(i, j) - m2.At(i, j);
            }
        }
        return ans;
    } else {
        throw invalid_argument("Matrices have different size");
    }
}

Matrix operator* (const Matrix& m1, const Matrix& m2) {
    if (m1.GetNumRows() == m2.GetNumRows() and m1.GetNumColumns() == m2.GetNumColumns()) {
        Matrix ans(m1.GetNumRows(), m1.GetNumColumns());
        for (int i = 0; i < m1.GetNumRows(); ++i) {
            for (int j = 0; j < m1.GetNumColumns(); ++j) {
                ans.At(i, j) = m1.At(i, j) * m2.At(i, j);
            }
        }
        return ans;
    } else {
        throw invalid_argument("Matrices have different size");
    }
}

Matrix operator/ (const Matrix& m1, const Matrix& m2) {
    if (m1.GetNumRows() == m2.GetNumRows() and m1.GetNumColumns() == m2.GetNumColumns()) {
        Matrix ans(m1.GetNumRows(), m1.GetNumColumns());
        for (int i = 0; i < m1.GetNumRows(); ++i) {
            for (int j = 0; j < m1.GetNumColumns(); ++j) {
                ans.At(i, j) = m1.At(i, j) / m2.At(i, j);
            }
        }
        return ans;
    } else {
        throw invalid_argument("Matrices have different size");
    }
}


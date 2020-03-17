#include <iostream>
#include <stdlib.h>
#include<cstdlib>
#include<new>
using namespace std;

class doubleMatrix
{
private:
    int rows;
    int columns;
    double **matrix;
    void allocArray()
	{
		matrix = new double*[rows];
		for(int i = 0; i < rows; i++)
		{
			matrix[i] = new double[columns];
		}
	}
public:
    void set_rows(int r){this->rows = r;}
    void set_cols(int c){this->columns = c;}
    void set_matrix(double x)
    {
        for(int i = 0; i < rows; i++)
            for(int j = 0; j < columns; j++)
                this->matrix[i][j] = x;
    }
    int get_rows() {return this->rows;}                             ///no. of rows
    int get_cols() {return this->columns;}                          ///no. of columns
    int get_noElements() {return (this->rows)*(this->columns);}     ///no. of elements
    doubleMatrix(int, int, double);                                 ///constructor
    doubleMatrix();                                                 ///default constructor
    ~doubleMatrix();                                                ///destructor
    doubleMatrix(doubleMatrix&);                                    ///constructor de copiere

    void citire(istream &in);
    friend istream& operator>>(istream &in, doubleMatrix& A);
    void afisare(ostream &out);
    friend ostream& operator<<(ostream &out, doubleMatrix& A);

    void operator=(doubleMatrix& A);
    void reshape(int newLinie, int newColoana, double x);
    double det();
    doubleMatrix& invers();

    friend doubleMatrix& operator+(doubleMatrix& A, doubleMatrix& B)
    {
        if (A.rows == B.rows && A.columns == B.columns)
        {
            doubleMatrix &sum = *new doubleMatrix(A.rows, A.columns, 0.0);          ///operator + overload
            for (int i = 0; i < A.rows; i++)
                for (int j = 0; j < A.columns; j++)
                sum.matrix[i][j] = A.matrix[i][j] + B.matrix[i][j];
            return sum;
        }
        else
        {
            doubleMatrix &zero = *new doubleMatrix(0, 0, 0);
            cout<<"Dimensiunile matricilor nu sunt compatibile!"<<endl;
            return zero;

        }

    }
    friend doubleMatrix& operator-(doubleMatrix& A, doubleMatrix& B)
    {
        if (A.rows == B.rows && A.columns == B.columns)
        {
            doubleMatrix &dif = *new doubleMatrix(A.rows, A.columns, 0.0);          ///operator - overload
            for (int i = 0; i < A.rows; i++)
                for (int j = 0; j < A.columns; j++)
                dif.matrix[i][j] = A.matrix[i][j] - B.matrix[i][j];
            return dif;
        }
        else
        {
            doubleMatrix &zero = *new doubleMatrix(0, 0, 0);
            cout<<"Dimensiunile matricilor nu sunt compatibile!"<<endl;
            return zero;
        }

    }
    friend doubleMatrix& operator*(doubleMatrix& A, doubleMatrix& B)
    {
        if( A.columns != B.rows)
        {
            doubleMatrix &zero = *new doubleMatrix(0, 0, 0);
            cout<<"Dimensiunile matricilor nu sunt compatibile!"<<endl;
            return zero;
        }
        else
        {
            doubleMatrix &P = *new doubleMatrix(A.rows, B.columns, 0.0);            ///operator * overload
            for ( int i = 0; i < A.rows; i++)
                for ( int j =0; j < B.columns; j++)
                    for ( int k = 0; k < A.columns; ++k)
                        P.matrix[i][j] += A.matrix[i][k] * B.matrix[k][j];
            return P;
        }
    }
    friend doubleMatrix& operator*(int x, doubleMatrix &A)
    {
        doubleMatrix &N = *new doubleMatrix(A);
        for(int i = 0 ; i < N.rows ; i++)
            for(int j = 0; j < N.columns; j++)
                N.matrix[i][j] = N.matrix[i][j] * x;
        return N;
    }
    friend bool operator==(doubleMatrix& A, doubleMatrix& B)
    {
        if (A.rows != B.rows || A.columns != B.columns)                             ///operator == overload
            return false;
        for (int i = 0; i < A.rows; i++)
            for (int j = 0; j < A.columns; j++)
                if (A.matrix[i][j] != B.matrix[i][j]) return false;
        return true;
    }

};
///constructor pentru initializarea cu un nr dat de linii si coloane si initializarea componentelor cu un nr dat
doubleMatrix::doubleMatrix(int r, int c, double x = 0.0)
{
    this->rows = r;
    this->columns = c;
    allocArray();
    for (int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->columns; j++)
        this->matrix[i][j] = x;
}
///default constructor
doubleMatrix::doubleMatrix()
{
    this->rows = 0;
    this->columns = 0;
    this->matrix = NULL;
}
///destructor
doubleMatrix::~doubleMatrix()
{
     for (int i = 0; i < this->rows; i++)
        delete[] matrix[i];
    delete matrix;
}
///constructor de copiere
doubleMatrix::doubleMatrix(doubleMatrix& A)
{
    this->rows = A.rows;
    this->columns = A.columns;
    allocArray();
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
        matrix[i][j] = A.matrix[i][j];
}

///citire
void doubleMatrix::citire(istream &in)
{
    cout<<"Scrieti numarul de linii:"<<endl;
    cin>>this->rows;
    cout<<"Scrieti numarul de coloane:"<<endl;
    cin>>this->columns;
    allocArray();
    cout<<"Pentru a initializa matricea cu un numar double apasati 1."<<endl;
    cout<<"Pentru a initializa matricea element cu element apasati 2."<<endl;
    int n;
    cin>>n;
    if (n == 1)
    {
        double x;
        cout<<"Scrieti valoarea cu care vreti sa fie initializata matricea:"<<endl;
        cin>>x;
        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < this->columns; j++)
                this->matrix[i][j] = x;
    }
    else if (n == 2)
    {
        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < this->columns; j++)
            {
                cout<<"matrice["<<i<<"]["<<j<<"] = ";
                cin>>this->matrix[i][j];
                cout<<endl;
            }
    }

}
istream& operator>>(istream& in, doubleMatrix& A){
    A.citire(in);
    return in;
}

///afisare
void doubleMatrix::afisare(ostream& out)
{
    out<<"Numarul de linii este: "<<this->rows<<endl;
    out<<"Numrul de coloane este: "<<this->columns<<endl;
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->columns; j++)
            out<<this->matrix[i][j]<<" ";
        out<<endl;
    }
}
ostream& operator<<(ostream& out, doubleMatrix &A)
{
    A.afisare(out);
    return out;
}
void doubleMatrix::operator=(doubleMatrix& A)
{
    this->rows = A.rows;
    this->columns = A.columns;
    allocArray();
    for (int i = 0; i < rows; i++)
        for( int j = 0; j < columns; j++)
            this->matrix[i][j] = A.matrix[i][j];
}
void doubleMatrix::reshape(int newRows, int newColumns, double x)
{
    this->rows = newRows;
    this->columns = newColumns;
    allocArray();
    for ( int i = 0; i < this->rows; i++)
        for ( int j = 0; j < this->columns; j++)
            this->matrix[i][j] = x;
}
double doubleMatrix::det()
{
    allocArray();
    double det;
    switch(this->rows)
    {
    case 2:
        det = this->matrix[0][0] * this->matrix[1][1] - this->matrix[0][1] * this->matrix[1][0];
        break;
    case 3:
        for(int i = 0; i < this->rows; i++)
        det += (this->matrix[0][i] * (this->matrix[1][(i+1)%3] * this->matrix[2][(i+2)%3] - this->matrix[1][(i+2)%3] * this->matrix[2][(i+1)%3]));
        break;
    default:
        cout<<"Matrice 2x2 sau 3x3!!"<<endl;
    }

    return det;
}
doubleMatrix& doubleMatrix::invers()
{
    allocArray();
    doubleMatrix& C = *new doubleMatrix(this->rows, this->columns, 0.0);
    switch(this->rows)
    {
    case 2:
        if (det() != 0)
        {
            C.matrix[0][0] = this->matrix[1][1] / det();
            C.matrix[0][1] = (-1)*this->matrix[0][1] / det();
            C.matrix[1][0] = (-1)*this->matrix[1][0] / det();
            C.matrix[1][1] = this->matrix[0][0] / det();
        }
        else cout<<"Matricea nu este inversabila!"<<endl;
        break;

    case 3:
        if (det() != 0)
        {
            for( int i = 0; i < 3; i++)
                for( int j = 0; j < 3; j++)
                C.matrix[i][j] = ((this->matrix[(j+1)%3][(i+1)%3] * this->matrix[(j+2)%3][(i+2)%3]) - (this->matrix[(j+1)%3][(i+2)%3] * this->matrix[(j+2)%3][(i+1)%3])) / det();
        }
        else cout<<"Matricea nu este inversabila!"<<endl;
        break;
    default:
        cout<<"Matrice 2x2 sau 3x3!!"<<endl;
    }
    return C;
}
doubleMatrix eqSolver()
{
    doubleMatrix A;
    doubleMatrix B;

    cout<<"Se citeste matricea A (2x2 / 3x3)"<<endl;
    cin>>A;
    cout<<"Se citeste matricea B (2x1 / 3x1)"<<endl;
    cin>>B;
    doubleMatrix X;
    X = (-1) * B;
    A = A.invers();
    cout<<"X este"<<endl;
    cout<<X;
    cout<<endl;
    cout<<"A este:"<<endl;
    cout<<A;
    X = A * X;
    cout<<"Solutia ecuatiei Ax + b = 0 este: "<<endl;
    cout<<X;

}
void menu_output()
{
    cout<<"Ruxandra_Maierean 212 - Tema 1_15 - MATRICE DOUBLE"<<endl;
    cout<<"Meniu:"<<endl;
    cout<<"1. Citirea si afisarea a N matrice."<<endl;
    cout<<"2. Suma a doua matrici."<<endl;
    cout<<"3. Diferenta a doua matrici."<<endl;
    cout<<"4. Produsul a doua matrici."<<endl;
    cout<<"5. Produsul unei matrici cu un intreg."<<endl;
    cout<<"6. Solutia ecuatiei Ax + b = 0"<<endl;
    cout<<"0.Iesire"<<endl;

}
void menu()
{
    int option = 0;
    do
    {
        menu_output();
        cout<<endl<<"Introduceti numarul actiunii: ";
        cin>>option;
        doubleMatrix A;
        doubleMatrix B;
        if (option < 0 || option > 6)
            cout<<"Selectie invalida!"<<endl;
        if (option == 0)
            cout<<"EXIT!"<<endl;
        if (option == 1)
        {
            doubleMatrix v[100];
            cout<<"Cate matrice citesc?"<<endl;
            int n = 0;
            cin>>n;
            for (int i = 0; i < n; i++)
            {
                cout<<"Se citeste a "<<i+1<<"-a matrice."<<endl;
                cin>>v[i];
            }
            for (int i = 0; i < n; i++)
            {
                cout<<"Se scrie a "<<i+1<<"-a matrice"<<endl;
                cout<<v[i]<<endl;
            }
        }
        if (option == 2)
        {
            cout<<"Prima matrice: "<<endl;
            cin>>A;
            cout<<"A doua matrice: "<<endl;
            cin>>B;
            doubleMatrix C(A.get_rows(), A.get_cols(), 0.0);
            C = A + B;
            cout<<"Suma matricilor este:"<<endl;
            cout<<C;
        }
        if (option == 3)
        {
            cout<<"Prima matrice: "<<endl;
            cin>>A;
            cout<<"A doua matrice: "<<endl;
            cin>>B;
            doubleMatrix C(A.get_rows(), A.get_cols(), 0.0);
            C = A - B;
            cout<<"Diferenta dintre prima si a doua matrice este: "<<endl;
            cout<<C;
        }
        if (option == 4)
        {
            cout<<"Prima matrice: "<<endl;
            cin>>A;
            cout<<"A doua matrice: "<<endl;
            cin>>B;
            doubleMatrix C(A.get_rows(), B.get_cols(), 0.0);
            C = A * B;
            cout<<"Produsul dintre prima si a doua matrice este: "<<endl;
            cout<<C;
        }
        if (option == 5)
        {
            cin>>A;
            int x;
            cout<<"Scrieti un numar interg: "<<endl;
            cin>>x;
            doubleMatrix C(A.get_rows(), A.get_cols(), 0.0);
            C = x * A;
            cout<<"Produsul dintre matrice si intreg este: "<<endl;
            cout<<C;
        }
        if(option == 6)
        {
            eqSolver();
        }
        system("pause"); ///Pauza - Press any key to continue...
        system("cls");
    }while(option != 0);
}
int main()
{
    menu();
    return 0;
}

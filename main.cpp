#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <wchar.h>
#include <memory>
#include <fstream>
#include <functional>

using namespace std;

using wc = wchar_t;

#pragma region Tricks

#pragma region Stubborn

// Stubborn class contains a method doesn't have the access to change any member in the class
class Stubborn{
    int a;

    // const keyword after func() blocks the function.
    void func() const{
        //a = 2;
    }
};

#pragma endregion

#pragma region Pointers Hell

// just a function returning a pointer to int
int* hello() {
    cout << "hello";
    int* v = new int(2);
    return v;
}

// A function returning an array of pointers
int (*y())[20]{
    static int arr[20][20] = {1,1,1,2};
    return arr;
}

void pointersHell(){

    // A pointer to a function which return a pointer to int
    int* (* z)() = hello;

    // A list of pointers to pointers point to a function which return a pointer to int
    int* (** x [])() = {&z};

    int (* arr1)[20] = y();

    int arr[5] = {1,2,3,4};

    // Slicing array
    int* a = &arr[2];

    for (int i = 0; i < 2; i++){
        cout << a[i] << "\t";
    }
}

#pragma endregion

#pragma region ArrayWithoutSpaces
void arrayNoSpace(string& s){
    auto r = remove(s.begin(), s.end(), ' ');
    cout << s << endl;
    s.erase(r,s.end());
}
#pragma endregion

#pragma region Wide Char

// Wide characters take up twice the space and much larger values (UNICODE)

void wideChar(){

    wc w = L'B';

    // L is a prefix for wide char literals

    cout << sizeof(w);
}
#pragma endregion

#pragma region Garbage Cin
void garbageCin(){

    int cin;

    // Declaring a variable named cin in a local scope make the compiler ignore cin from std namespace

    //cin >> cin;
    //std::cin >> cin;

    cout << cin;
}
#pragma endregion

#pragma region The end
void theEnd(){
    // \0 is an escape character used at the end of string in the memory
    string a = "Hello\0World";
    // a = Hello
    cout << a;
}
#pragma endregion

#pragma region No Touching

void noTouching(){
    int x = 5;
    float b = 1;

    // sizeof makes expressions have no side effects
    int size = sizeof(++x + b);

    cout << x << ' ' << size;
}

#pragma endregion

#pragma region CS gonna make me lose my mind

void csIsBadass(){
    char a;
    char b;

    // Input more characters than required
    cin >> a >> b >> a;

    cout << cin.peek() << endl;

    cin.putback('a');
    cin.putback('b');

    cin.get(a);
    cin.get(b);

    cout << cin.peek() << endl;

    a = cin.peek();
    cout << a;
    cout << b;
}

#pragma endregion

#pragma region Bro didn got his chance
void spectator(){
    int i = 1; int c = 5;

    // This condition will always be true cause of i the rest of the expression will be ignored
    // So c will never change
    if (i || --c > 0){
        cout << "s"<<endl;
    }

    // but not the expression had a chance to show off, expression must be read
    if (--c > 0 || i){
        cout << "s"<<endl;
    }

    cout << c;
}
#pragma endregion

#pragma region Salam yabn el 3abeta
int& iWillVanish(){

    int x = 10;
    return x;

    // return a variable reference that will be deallocated at the end of the function scope

}
#pragma endregion

#pragma region WTF printing

// This is a normal printing
void print(int a, int b){
    cout << a << " " << b << endl;
}

void wtfPrint(){
    int x = 10;
    // Just try them yourself, Uncomment one and comment the rest
//    print(++x, ++x);
//    print(++x, x++);
//    print(x++, ++x);
//    print(x++, x++);

    // This is called order of evaluation

}
#pragma endregion

#pragma region Diffrence between constructor And operators
class C{
private:
    int value;
public:
    // Constructor is called once allocating an object
    C(int v){
        value = v;
        cout << "Value assigned"<<endl;
    }

    // operator when assigning variable to variable
    C & operator=(C& c){
        c.value = this->value;
        cout << "This is assigning" << endl;
        return *this;
    }

};

void SameSameButDifferent(){
    C a(20);
    C b = a; // Constructor called
    C c(10);
    c = a; // Operator overloading
}
#pragma endregion

#pragma region Insane developer
void func(int a, int b = 10){
    cout << a << " " << b << endl;
}

void func(int a){
    cout << a << endl;
}

void KareemAndKaram(){

    // The compiler would get confused, two functions with the same name, both accept 1 argument

    //func(1); // Immediate error
    //func(1,2); // This is fine
}
#pragma endregion

// Just ignore this. I was using it for myself
constexpr int operator""_s(unsigned long long mins){
    return mins*60;
}

#pragma region All eyes on memory

void* operator new (size_t size){
    cout << "Allocated: " << size << "bytes\n";
    return malloc(size);
}

void operator delete(void* memory, size_t size){
    cout << "Free: " << size << "bytes\n";
    free(memory);
}

#pragma endregion

#pragma endregion

#pragma region Exams

#pragma region Martix

void IterateOverAMatrix(int rows, int cols, function<void (int, int)> operation, function<void (int)> breaking){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            operation(i, j);
        }
        breaking(i);
    }
}

void load( const string& filename, int m[10][10], int& rows, int& cols ){
    ifstream fileStream;
    fileStream.open(filename);
    if (fileStream.fail()){
        cout << "Failed to load file"<<endl;
        return;
    }
    fileStream >> cols >> rows;

    IterateOverAMatrix(rows, cols, [&](int i, int j){
        fileStream >> m[i][j];
    }, [](int i){});
}

void printMatrix(int a[10][10], int m, int n){

    IterateOverAMatrix(m,n, [=](int i, int j){
        cout << a[i][j] << " ";
    }, [](int i){
        cout << endl;
    });
}

// Add 2 Matrices
void add(int m1[][10], int m2[][10], int m, int n){
    IterateOverAMatrix(m, n, [&](int i, int j){
        m1[i][j] += m2[i][j];
    }, [](int i){});
}

void AddMtoM(){
    int mat1[10][10];
    int mat2[10][10];

    int rows1, rows2, cols1, cols2;

    load("file1.txt", mat1, rows1, cols1);
    load("file2.txt", mat2, rows2, cols2);

    add(mat1, mat2, 2, 3);

    printMatrix(mat1, 2, 3);

}

#pragma endregion

#pragma region Pointers Conflict

void PointersConflict(){
    int a[3] = {5, 9, 7};

    int* p = a;
    *p = 3;
    p[1] = 8;
    * (p + 2) = 6;
    cout << a[0] << " " << a[1] << " " << a[2] << endl;

    a[0] = 4; a[1] = 6; a[2] = 8;
    p = a;
    *p++ = 7;
    * (p + 1) = *p;
    (*p)--;
    cout << a[0] << " " << a[1] << " " << a[2] << endl;

    a[0] = 2; a[1] = 8; a[2] = 4;
    p = &a[0];
    * (p + 2) += 3;
    * ++p = 6;
    ++ * (p - 1);
    cout << a[0] << " " << a[1] << " " << a[2] << endl;
}

#pragma endregion

#pragma region CellsOfSum

int GetCells(int** mat, int m, int n){

    int sum = 0;

    for (int i = 1; i < m - 1; i++){
        for (int j = 1; j < n-1; j++){
            if (mat[i][j] == mat[i-1][j] + mat[i+1][j])
                sum++;
        }
    }

    return sum;
}

void MatCells(){

    int rows, cols;

    cin >> rows >> cols;

    int** mat = new int*[rows]{};

    for (int i = 0; i < rows; i++){
        mat[i] = new int[cols]{};
        for (int j = 0; j < cols; j++){
            cin >> mat[i][j];
        }
    }

    cout << GetCells(mat, rows, cols);

}

#pragma endregion

#pragma endregion

int main(){
    MatCells();
    return 0;
}

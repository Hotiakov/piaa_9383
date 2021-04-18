#include "lb1.hpp"

void Print_Answer(const int result, List_of_squares result_squares) {
    std::cout << result << "\n";
    for (size_t i = 0; i < result_squares.size(); ++i) {
        std::cout << result_squares[i].x + 1 << " " << result_squares[i].y + 1<< " " << result_squares[i].width <<"\n";
    }
}

void New_Square(Matrix& matrix, Square square) { //добавляет новый квадрат
    for (int i = square.x; i < square.x + square.width; i++)
        for (int j = square.y; j < square.y + square.width; j++)
            matrix[i][j] = 1;
}

bool isCan_Add_Square(int n, Matrix matrix, Square square){   //можно ли вместить квадрат
    int w = square.width;
    return (square.x + w < n)&&(square.y + w < n)&&(matrix[square.x][square.y + w] == 0)&&(matrix[square.x + w][square.y] == 0)&&(matrix[square.x + w][square.y + w] == 0)&&(square.x>=0)&&(square.y>=0);
}

void Backtracking(int n, Matrix matrix, int count_ready_squares, int& result, List_of_squares& result_squares) {
    List_of_squares interim_squares; //для промежуточных значений
    std::stack<For_backtracking> st;
    st.emplace(matrix, count_ready_squares, interim_squares); //добавляем элемент
    while (!st.empty()){
        For_backtracking last = st.top();  //берем верхний элемент

        st.pop();  //удаляем верхний

        bool A = true;
        Point point = {-1, -1};
        for (int x = 0; x < n / 2 + 1; x++) {
            for (int y = 0; y < n / 2 + 1; y++) {
                if (last.matrix[x][y] == 0) {
                    point = {x, y};
                    A = false;
                    break;
                }
            }
            if (point.first > -1) {
                break;
            }
        }

        if (A) {
            result = last.count;
            result_squares = last.list_of_square;
        }

        if (last.count + 1 >= result){
            continue;
        }

        for (int w = 0; w < n - 1; w++) {

            Point start = {point.first, point.second};

            if (isCan_Add_Square(n, last.matrix, Square(point.first,point.second, w))) {
                for (int x = start.first; x <= point.first + w; x++) {
                    last.matrix[x][point.second + w] = last.count + 1;
                }
                for (int y = start.second; y <= point.second + w; y++) {
                    last.matrix[point.first + w][y] = last.count + 1;
                }
                start.first++;
                start.second++;
                last.list_of_square.push_back(Square({point.first, point.second, w + 1}));
                st.emplace(last.matrix, last.count + 1, last.list_of_square);   //добавили элемент
                last.list_of_square.pop_back();
            }
            else {
                break;
            }
        }
    }
}

void Divisible_2(int n, int&result, List_of_squares& result_squares) {   //делящиеся на 2
    result_squares = {	{ 0, 0, n / 2 }, { 0, n / 2, n / 2}, { n / 2, 0, n / 2}, { n / 2, n / 2, n/ 2} };
    result = 4;
}

void Divisible_3(int n, int&result, List_of_squares& result_squares) { //делящиеся на 3
    result_squares = {	{ 0, 0, n/3 }, { 0, n/3, n/3}, { 0, 2*(n/3), n/3 }, { n/3, 0, n/3}, { 2*(n/3), 0, n/3}, { n/3, n/3, 2*(n/3)} };
    result = 6;
}

void Simple_Number(int n, Matrix& matrix, int&result, List_of_squares& resultSquares) { // n - простое число
    List_of_squares ready_squares;   //для начальных квадратов

    New_Square(matrix, Square(n / 2, n / 2, n / 2 + 1));
    ready_squares.emplace_back(n / 2, n / 2, n / 2 + 1);

    New_Square(matrix, Square(n - n / 2, 0, n / 2));
    ready_squares.emplace_back(n - n / 2, 0, n / 2);

    New_Square(matrix, Square(0, n - n / 2, n / 2));
    ready_squares.emplace_back(0, n - n / 2, n / 2);

    Backtracking(n, matrix, ready_squares.size(), result, resultSquares);
    copy(ready_squares.begin(), ready_squares.end(), back_inserter(resultSquares));
}

void Time_Information(clock_t start_time, clock_t end_time) {
    std::cout << (float)(end_time- start_time) / CLOCKS_PER_SEC << "\n";
}


#include <iostream>
#include <vector>
#include <ctime>
using namespace std;



struct Square { //�������, ������� ����� ����������� �� ����������
	int size;
	int x;
	int y;
};

bool Field[50][50];   //����������

//������� ���������:
vector <Square> StepStack;  //��������� ���������� ����������
vector <Square> CurrentStack; //������� ���������� ����������
vector <Square> BestStack; //������ ���������� ���������� (���������� ���������� ���������)


Square DeleteSquare(const int& size) { //������� ��� �������� ���������� ��������
	if (CurrentStack.size() == 0)
		return Square{ -1, -1, -1 };
	Square Last = CurrentStack.back();
	CurrentStack.pop_back();
	//cout << "��� ������ �������: " << Last.x + 1 << ' ' << Last.y + 1 << ' ' << Last.size << '\n';
	for (int i = 0; i < Last.size; ++i) {
		for (int j = 0; j < Last.size; ++j) {
			Field[i + Last.y][j + Last.x] = 0;
			}
	}
	return Last;
}



Square FreeCell(int size) {  //������� ������ ������ ������ �� ����������
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (Field[i][j] == 0)
				return { 0, j, i };
		}
	}
	return { -1, -1, -1 };
}


Square Place(int size, Square Alleged) { //�������, ������� �������� ������� �� ���������� (��������� ��������� ������� ���������� ��������)
	Square Result;
	int SizeOfRes = 1;
	if (Alleged.size > 0) { //���������� ���������� � ��������� ��������� ��������
		Result = Alleged;
		Result.size--;
	}
	else {
		Result = { size - 1, 0, 0 }; //������ ���
	}
	//���������� ������ ��������, ������� ����� ������, ��� ���������� �������. ����� �� ������ ���������� �� ����������.
	while ((SizeOfRes < Result.size) && ((Result.x + SizeOfRes) < size) && ((Result.y + SizeOfRes) < size) && (Field[Result.y][Result.x + SizeOfRes] == 0)) {
		SizeOfRes++;
	}
	Result.size = SizeOfRes;
	for (int i = 0; i < Result.size; ++i) { // ������������ ��������
		for (int j = 0; j < Result.size; ++j) {
			Field[Result.y + i][Result.x + j] = 1;
		}
	}
	return Result;
}


void Backtracking(int size) {  //����������� ����� � ��������
	bool back = false;
	bool full = false;
	int div = 1;
	Square Alleged{ -1, 0, 0 };
	Square ResultPlace{ 0, 0, 0 };
	for (int i = 2; i <= size; i++) { //���������� ������� ���������� �� ����������� �������� ��������
		if (size % i == 0) {
			div = size / i;
			size = i;
		}
	}

	//cout << "������������ ������ ���������:\n";
	//cout << "������ �������: 1 1 " << (size + 1) / 2 << "\n";
	//cout << "������ �������: 1 " << (size + 1) / 2 + 1 << " " << size - (size + 1) / 2 << "\n";
	//cout << "������ �������: " << (size + 1) / 2 + 1 << " 1 " << size - (size + 1) / 2 << "\n";

	ResultPlace = Place(size, { (size + 1) / 2 + 1, 0, 0 }); //���������� � ���� ���������
	CurrentStack.push_back(ResultPlace);
	ResultPlace = Place(size, { size - (size + 1) / 2 + 1, 0, (size + 1) / 2 });
	CurrentStack.push_back(ResultPlace);
	ResultPlace = Place(size, { size - (size + 1) / 2 + 1, (size + 1) / 2, 0 });
	CurrentStack.push_back(ResultPlace);
	Alleged = FreeCell(size); 
	Alleged.size = size - 1;

	//������ �����
	do {
		int last_size = 0;
		full = false;
		back = false;
		while (!full) {  //���� ���������� �� ����� ��������� ���������
			ResultPlace = Place(size, Alleged); //���������� ���� �������
			CurrentStack.push_back(ResultPlace);
			if ((BestStack.size() > 0) && (CurrentStack.size() > 0) && (CurrentStack.size() >= BestStack.size())) {
				back = true;  //���� ������� ������������ ����, �� ������ ��� ����� (������� �������)
				DeleteSquare(size);
				Alleged = DeleteSquare(size); //�������� ���� ����������� ��������� ��������
				break;
			}
			Alleged = FreeCell(size); //���������� � ���������� ���������� ���������
			full = (Alleged.size == -1);
			Alleged.size = size;
		}
		if (!back) { //���� ���������� ���������
			if ((CurrentStack.size() < BestStack.size()) || (BestStack.size() == 0)) { //��������� �������� ������������ � ������ �������������
				BestStack = CurrentStack;
			}
		}

		do {
			Alleged = DeleteSquare(size); //������� ��� �����, ���� ������ �������� ����� 1 ��� 2, ���� ���������� ���������
		} while (Alleged.size == 1 || (full && Alleged.size == 2) && CurrentStack.size() >= 3);


	} while (CurrentStack.size() >= 3);

	for (int i = 0; i < BestStack.size(); i++) {
		BestStack[i].x *= div;
		BestStack[i].y *= div;
		BestStack[i].size *= div;
	}
}



int main() {
	setlocale(LC_ALL, "Russian");
	int N;
	cout << "������� ������ ����������:\n";
	cin >> N;
	double time = clock();

	if (N % 2 == 0) {
		cout << "\n������ ������, ���������� �� ���������.\n";
		cout << 4 << "\n";
		cout << 1 << ' ' << 1 << ' ' << N / 2 << "\n";
		cout << N / 2 + 1 << ' ' << 1 << ' ' << N / 2 << "\n";
		cout << 1 << ' ' << N / 2 + 1 << ' ' << N / 2 << "\n";
		cout << N / 2 + 1 << ' ' << N / 2 + 1 << ' ' << N / 2 << "\n";
	}
	else {
		cout << "\n���������� �����������:\n";
		Backtracking(N);
		cout << BestStack.size() << "\n";
		for (auto& Res : BestStack)
			cout << Res.x + 1 << ' ' << Res.y + 1 << ' ' << Res.size << '\n';
	}

	cout << "\n------------------------------------------------------\n";
	cout << "_������������ ������� ���������� �� ������� ��������_\n";
	cout << "��� ������� �������� " << N << " ���� ��������� �������: " << (clock() - time) / 1000.0 << '\n';
	return 0;
}
#include "lab4_1.h"


void KMP::Read() {
	std::cout << "������� ������ ������ P:\n";
	std::cin >> P;
	std::cout << "������� ������ ������ T:\n";
	std::cin >> T;
}

void KMP::PrintAnswer() {
    std::cout << "\n_�����_:\n";
    if (!answer.size()) {
        std::cout << "P �� ������ � T\n";
        std::cout << -1;
    }
    else {
        std::cout << "������� ����� ��������� P � T:\n";
        for (auto a : answer) {
            if (a == answer.front())
                std::cout << a;
            else
                std::cout << "," << a;
        }
    }
    std::cout << '\n';
}

void KMP::Prefix() {   //�������-�������
	std::cout << "\n_������� �������-�������_:\n\n";
	int pLength = P.length();
    arrPrefix = std::vector<int>(pLength);
    arrPrefix[0] = 0;
    std::cout << "�������� �������-������� ��� ������� "<< P[0] << " ��� ������� " << 0  << " ����� " << 0 << '\n';
    for (int i = 1; i < pLength; i++) {
        int curLength = arrPrefix[i - 1];
        std::cout << "���������� �������� �������-������� ��� ������� " << P[i] << " ��� ������� " << i << "\n\n";

        while (curLength > 0 && (P[curLength] != P[i])) {   // ���� ���������� ������� ������ ���������, �� ������������� ������� �������� �������
            std::cout << "���������� ������� ������� " << curLength << " ������ ���������.\n";
            curLength = arrPrefix[curLength - 1];
            std::cout << "���������� ����� ������� �������� �������: " << curLength << '\n';
        }

        if (P[curLength] == P[i]) {    // �������� �� ����������
            std::cout << "������� ������ " << curLength << " ����� ���������.\n";
            curLength++;
            std::cout << "����� ������ ��������: " << curLength << '\n';
        }

        std::cout << "�������� �������-������� ����� " << curLength << '\n';
        arrPrefix[i] = curLength;
    }

    std::cout << "\n�������� �������-�������:\n";
    for (auto j : P) { 
        std::cout << j << ' ';
    }
    std::cout << '\n';
    for (auto i : arrPrefix) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}


void KMP::AlgorithmKMP(){
    Prefix();
    std::cout << "\n\n_�������� �����-�������-������_:\n\n";
    int tSize = T.size();
    int pSize = P.size();
    int pIndex = 0;
    int tIndex = 0;
    while (tIndex < tSize) {
        if (P[pIndex] == T[tIndex]) {  //���� ������� �����
            std::cout << "������� ���������� " << pIndex << " ������� ������� " << P[pIndex]  << " � " << tIndex << " ������� ������ " << T[tIndex] << '\n';
            pIndex++;
            tIndex++;
            if (pIndex == pSize) {  //���� ��������� �������
                std::cout << "��������� �������, ������ ����� " << tIndex - pIndex << "\n\n";
                answer.push_back(tIndex - pIndex);
                pIndex = arrPrefix[pIndex - 1]; //������� �� ������� ������ �������������� �������� �������-�������
            }
        }
        else if (pIndex == 0) // ���� ��������� � ������ ��������
            tIndex++;
        else  //���� �� �� ������� ������������
            pIndex = arrPrefix[pIndex - 1];
    }
}


int main() {
    setlocale(LC_ALL, "Russian");
    KMP k;
    k = KMP();
    k.Read();
    k.AlgorithmKMP();
    k.PrintAnswer();
    return 0;
}
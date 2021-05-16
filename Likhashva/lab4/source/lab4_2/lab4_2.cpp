#include "lab4_2.h"


void KMP::Read() {
    std::cout << "������� ������ ������ �:\n";
    std::cin >> A;
    std::cout << "������� ������ ������ �:\n";
    std::cin >> B;
}


void KMP::PrintAnswer() {
    std::cout << "\n\n_�����_:\n";
    if (answer == -1) {
        std::cout << "A �� �������� ����������� ������� B.\n";
        std::cout << answer << '\n';
    }
    else {
        std::cout << "A �������� ����������� ������� B.\n";
        std::cout << "������ ������ ������ B � �: " << answer << '\n';
    }
}


void KMP::Prefix() {   //�������-�������
    std::cout << "\n_������� �������-�������_:\n\n";
    int bLength = B.length();
    arrPrefix = std::vector<int>(bLength);
    arrPrefix[0] = 0;
    std::cout << "�������� �������-������� ��� ������� " << B[0] << " ��� ������� " << 0 << " ����� " << 0 << '\n';
    for (int i = 1; i < bLength; i++) {
        int curLength = arrPrefix[i - 1];
        std::cout << "���������� �������� �������-������� ��� ������� " << B[i] << " ��� ������� " << i << "\n\n";

        while (curLength > 0 && (B[curLength] != B[i])) {   // ���� ���������� ������� ������ ���������, �� ������������� ������� �������� �������
            std::cout << "���������� ������� ������� " << curLength << " ������ ���������.\n";
            curLength = arrPrefix[curLength - 1];
            std::cout << "���������� ����� ������� �������� �������: " << curLength << '\n';
        }

        if (B[curLength] == B[i]) {    // �������� �� ����������
            std::cout << "������� ������ " << curLength << " ����� ���������.\n";
            curLength++;
            std::cout << "����� ������ ��������: " << curLength << '\n';
        }

        std::cout << "�������� �������-������� ����� " << curLength << '\n';
        arrPrefix[i] = curLength;
    }

    std::cout << "\n�������� �������-�������:\n";
    for (auto j : B) {
        std::cout << j << ' ';
    }
    std::cout << '\n';
    for (auto i : arrPrefix) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}


void KMP::CyclicShift() {
    if (A.length() != B.length()) {
        std::cout << "������ ����� �� �����, ������ ��� �� ����������� �����.\n";
        answer = -1;
        return;
    }

    Prefix();
    std::cout << "\n\n_�����������, �������� �� � ����������� ������� B_:\n\n";
    int aLength = A.length();
    int curBLength = 0;
    for (int i = 0; i < aLength * 2; i++) { //����� �� ���������� ������ ������
        int j = i % aLength;
        if (B[curBLength] != A[j]) //���� ������� �� �����
            std::cout << "������������ " << j << " ������� ������ � " << '(' << A[j] << ')' << " � " << curBLength << " ������� ������ � "  << '(' << B[curBLength] << ")";
        while (curBLength > 0 && B[curBLength] != A[j]) {
            curBLength =arrPrefix[curBLength - 1];
        }
        std::cout << '\n';
        if (B[curBLength] == A[j]) { //���� ������� �����
            std::cout << "������� ���������� " << j << " ������� ������ � " << '(' << A[j] << ')' << " � " << curBLength << " ������� ������ � " << '(' << B[curBLength] << ")";
            curBLength++;
        }

        if (curBLength == aLength) {  //���� ������� ���������
            answer = i - curBLength + 1;
            std::cout << "\n\n��������� �������. ������ ����� " << answer << '\n';
            return;
        }
    }

    answer = -1;
    return;
}


int main() {
    setlocale(LC_ALL, "Russian");
    KMP k;
    k = KMP();
    k.Read();
    k.CyclicShift();
    k.PrintAnswer();
    return 0;
}
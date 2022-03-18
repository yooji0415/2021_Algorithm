#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <ctime>

#define ABS(X) ((X) < 0 ? -(X) : (X))
#define EPSILON 0.000001

using namespace std;

double insertCost = 1; // ���ۺ� �ڽ�Ʈ�� �������ش�.
double deleteCost = 1;
double changeCost = 1;

void Distance(char* source, int sourceLen, char* target, int targetLen);

int main() {
    char source1[5] = { 'G','U','M','B','O' };
    char target1[6] = { 'G','A','M','B','O','L' };
    Distance(source1, 5, target1, 6);
    insertCost = 0.7; // �� ���ۺ� �ڽ�Ʈ�� �������ش�.
    deleteCost = 0.5;
    changeCost = 0.3;
    Distance(source1, 5, target1, 6);
    char source2[11] = { 'L','e','v','e','n','s','h','t','e','i','n' };
    char target2[11] = { 'M','e','i','l','e','n','s','t','e','i','n' };
    Distance(source2, 11, target2, 11);
    char source3[5] = { 'T','A','C','T','G' };
    char target3[8] = { 'C','A','T','G','A','C','T','G' };
    Distance(source3, 5, target3, 8);
    char source4[6] = { '��','��','Ÿ','��','��','��' };
    char target4[8] = { '��', '��', '��', '��', '��','��', '��', '��' };
    Distance(source4, 6, target4, 8);
    cout << "12171810 ������Ű��а� ������" << endl;
    return 0;
}

void Distance(char* source, int sourceLen, char* target, int targetLen) { // Levenshtein Distance ��� �Լ�
    double left, up, diagonal; // ��� ��ġ������ �� �� �ְ� �����ִ� ����
    double min; // �� ��ġ���� ��� ���� ���� ������ �ľ��ϱ� ���� �Լ�
    double** arr = new double* [targetLen + 1]; // ���� �����ϱ� ���� 2���� ��� ���̺� ����
    for (int j = 0; j < targetLen + 1; j++) {
        arr[j] = new double[sourceLen + 1];
    }
    arr[0][0] = 0;
    for (int i = 0; i < sourceLen + 1; i++) arr[0][i] = arr[0][0] + deleteCost * i; // �켱������ �� �� ��� �ٿ� ���� �־��ش�.
    for (int j = 0; j < targetLen + 1; j++) arr[j][0] = arr[0][0] + insertCost * j;
    for (int j = 1; j < targetLen + 1; j++) { // ���� (1,1)�� ��ġ�������� ���� ������ش�.
        for (int i = 1; i < sourceLen + 1; i++) {
            min = 100; // �켱������ �ּҰ��� 100�� ���� ���� ������ 100���� �ʱ�ȭ�� �Ź� ���ش�.
            left = arr[j][i - 1] + deleteCost; // �ش� ��ġ �������� ����, ��, �밢���� ��쿡 ���� �̸� ����ؼ� ��´�,
            up = arr[j - 1][i] + insertCost;
            if (source[i - 1] == target[j - 1]) diagonal = arr[j - 1][i - 1]; // �밢���� ��쿡�� ������ ���� ����
            else diagonal = arr[j - 1][i - 1] + changeCost; // �ٸ� ��츦 ���� �и��ؼ� ���� �־��ش�.

            if (min > up) min = up; // if���� 3�� �ϸ鼭 ���� ���� ���� ���� ã���ش�.
            if (min > diagonal) min = diagonal;
            if (min > left) min = left;

            arr[j][i] = min; // �ش�Ǵ� ���� ĭ�� �־��ش�.
        }
    }
    for (int j = 0; j < targetLen + 1; j++) { // ���̺��� �°� ����������� Ȯ���ϱ� ���ؼ� ����� �غ���.
        for (int i = 0; i < sourceLen + 1; i++) {
            cout << setw(5) << arr[j][i] << " ";
        }
        cout << endl;
    }
    cout << "Levenshtein Distance : " << arr[targetLen][sourceLen] << endl << endl; // ����� ������ش�.
    // ��θ� �ľ��ϴ� �˰��� 
    int i = sourceLen; // while���� ���� ���� �ε��� i, j�� ���� �־��ش�.
    int j = targetLen;
    int position = 0; // ��� ��η� ������ �ش� ��θ� �޴� ����
    int step[30] = { 0 }; // �� �� ������� ���� ���� �������� ���������� ��θ� �����ϴ� ���
    int stepCount = 0; // ����� �� ��° ĭ���� ������ �Ǿ��ִ��� �˷��ִ� �ε���
    while (i > 0 && j > 0) { // �� �� �ϳ��� 0���ο� �����ϱ� ������ �ݺ��Ѵ�.
        position = 0; // ��� ���� ������ 0�� �ʱ�ȭ ���ش�.

        if (ABS(arr[j][i] - deleteCost - arr[j][i - 1])<EPSILON) position = 1; // �ش� �������� ���� ���� �밢������ ���� 
        if (ABS(arr[j][i] - insertCost - arr[j - 1][i])<EPSILON) position = 2; // �� �ڽ�Ʈ�� ���̸�ŭ ���ְ� �񱳸� �ؼ� 
        if (ABS(arr[j][i] - changeCost - arr[j - 1][i - 1])<EPSILON) position = 3; // ���� ��ġ�ϸ� �ش� ��ġ�� ��Ÿ���� position ���� �ִ´�.
        if (ABS(arr[j][i] - arr[j - 1][i - 1])<EPSILON) position = 4; // ����� ���� �� 4������ ���ߴ�.
        // 1 : ���� / 2 : ���� / 3 : �밢��(source�� target�� ���� �ٸ����) / 4 : �밢��(�� ���� ���Ƽ� ���� ������ ���� ���)

        if (arr[j - 1][i] < arr[j - 1][i - 1]) { // if���� ���� �� �밢���� ���� �������� �־ �밢���� ������� Ŀ���� ������ 
                                         // ���ϴ� ��η� �� ���� ��찡 �־���.
                                         // ���� ���ʰ� ������ �� ���� ��� �ѹ� �� ��ȸ�� �ִ� ������� ���踦 �ߴ�.
            if (ABS(arr[j][i] - insertCost - arr[j - 1][i]) < EPSILON) position = 2;
        }
        if (arr[j][i - 1] < arr[j - 1][i - 1]) {
            if (ABS(arr[j][i] - deleteCost - arr[j][i - 1]) < EPSILON) position = 1;
        }

        // �� �۾��� ���� ����� position ���� ���� step��̿� ���� �־��ְ� stepCount�� ���������ش�.
        // ���� �ش� ��ġ�� i, j �ε��� ��ġ�� �ٲپ��ش�.
        if (position == 1) {
            step[stepCount] = 1;
            stepCount++;
            i--;
        }
        else if (position == 2) {
            step[stepCount] = 2;
            stepCount++;
            j--;
        }
        else if (position == 3) {
            step[stepCount] = 3;
            stepCount++;
            i--;
            j--;
        }
        else if (position == 4) {
            stepCount++;
            i--;
            j--;
        }

    }

    // �� while���� �� ���� �������� [0][0]��ġ�� �� ������ ��쿡 ����ؼ� 
    // �� �ε����� ����, ���� ó���� ������־���. 0�� �� �� ���� for���� ���ؼ� 
    // �����̳� ���� ������ ���� step��̿� ����.
    if (j > 0) {
        for (int k = j; k > 0; k--) {
            step[stepCount] = 2;
            stepCount++;
        }
    }
    else if (i > 0) {
        for (int k = i; k > 0; k--) {
            step[stepCount] = 1;
            stepCount++;
        }
    }
    // ���� step��̿� ���� �о���� �κ��̴�.
    // ������ ��θ� ��ұ� ������ ����� ������ ó�����ָ� ������ ��ΰ� ���´�.
    // stepCount���� ���� 0 �ε������� for���� ���� �ϸ鼭 �Էµ��ִ� ���� ���� 
    // ��ο� cost�� ������ش�. 
    for (int k = stepCount; k >= 0; k--) {
        if (step[k] == 1) cout << "�������� ���� " << deleteCost << endl;
        else if (step[k] == 2) cout << "���Կ��� ����" << insertCost << endl;
        else if (step[k] == 3) cout << "��ȯ���� ����" << changeCost << endl;
    }
    cout << endl;
}
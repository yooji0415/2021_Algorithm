#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <Windows.h> 
using namespace std;

LARGE_INTEGER freq, start, stop;
const int TESTNUM = 16777216;

void swap(int* arr, int a, int b) { // �Է���ġ�� ���� �ٲ��ִ� swap �Լ�
    int temp = 0;
    temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

void QuickSort(int arr[], int l, int r) { //QuickSort �Լ�
    int m, v, i, j; // �ʿ��� ���� ����
    if (r - l > 1) { // �ɰ��� ũ�Ⱑ 1ĭ~2ĭ�� ��츦 üũ
        m = (l + r) / 2;
        if (arr[l] > arr[m]) swap(arr, l, m); // �հ� �߰��� ũ���
        if (arr[l] > arr[r]) swap(arr, l, r); // �հ� ���� ũ���
        if (arr[m] > arr[r]) swap(arr, m, r); // �߰��� ���� ũ���
        swap(arr, m, r - 1); // �߰����� �Ű��ش�
        v = arr[r - 1]; // �Ǻ��� ũ�⸦ �˷��ش�
        i = l; // �պ��� ���۵Ǵ� ����Ʈ
        j = r - 1; // �ں��� ���۵Ǵ� ����Ʈ
        for (;;) {
            while (arr[++i] < v); // �Ǻ����� ū ��� ��ž
            while (arr[--j] > v); // �Ǻ����� ���� ��� ��ž
            if (i >= j) break; // �ΰ��� ���� ��ġ�� ����Ű�� �극��ũ
            swap(arr, i, j); // �� ��ġ�� ���� �ٲ��ش�
        }
        swap(arr, i, r - 1); // �Ǻ��� ��ġ�� ���� ��ġ�� �ٲپ��ش�
        QuickSort(arr, l, i - 1); // �Ǻ����� �� �ڸ� ������ �ݺ��Ѵ�
        QuickSort(arr, i + 1, r);
    }
    else if (arr[l] > arr[r]) swap(arr, l, r); // 2ĭ�� ��� �յڸ� ���ϰ� �ٲ۴�
}

void ShellSort(int arr[], int n) { //ShellSort �Լ�
    int h, i, j, v; // �ʿ��� ���� ����
    for (h = 1; h < n; h = 3 * h + 1) {}; // �켱 Concrete gap�� ���� �ڷ� �̷��
    // ���⼭ ����� ����� Knuth�� �˰������� 1,4,13 .. 3�� + 1 �˰��� �̴�
    for (; h > 0; h /= 3) { // �ѹ� �ݺ��� �� ���� gap�� �ٿ��ش�
        for (i = h + 1; i <= n; i++) { // h ������ ���� �� ���� ������� ã�´�
            v = arr[i]; // �켱 �� ��ġ�� ���� ��Ƶΰ�
            j = i; // �� �ε��� ���� ������ ��Ƶд�
            while (j > h && arr[j - h] > v) { // �������ִ� j ��ġ���� ���ݺ��� ũ��
            // �� ���� �̸� ������ ������ Ŭ�� ��� ��ĭ���� �Ű��ش�.
                arr[j] = arr[j - h]; // �� �ڵ尡 ����ȴٴ� ����
                // �� ������ �۴ٴ� �ǹ̴� ��ġ�� �ٲپ��ش�
                j = j - h; // j ��ġ�� ������ �Ű��ش�
            }
            arr[j] = v; // ���κ��� ���� ���� �տ� �����ϴ� ���̹Ƿ� �� ��ġ�� 
            // ���� �־��ش�
        }
    }
}

int main() {
    int* arr = new int[TESTNUM]; // ������ ��̸� �����ϱ� ���� 
    int* copy1 = new int[TESTNUM]; // ���縦 ���� ��̸� �����Ѵ�
    int* copy2 = new int[TESTNUM];
    QueryPerformanceFrequency(&freq);
    srand(2001); // ���������� ���� srand ������ ���ش�. �� �κ��� 3�� ��� ���α׷��� �����ϰ� �õ�ο��� �ߴ�
    for (int n = 1024; n <= TESTNUM; n *= 2) { // ������ 1024������ TESTNUM���� �� �辿 ���������ݴϴ�.
        for (int i = 0; i < n; i++) { // ������ �´� ���� ��ǲ�� �����.
            arr[i] = rand() % TESTNUM;
        }
        for (int i = 0; i < n; i++) { 
            copy1[i] = arr[i];
            copy2[i] = arr[i];
        }
        cout << n << "���� �Է¿� ���� �ҿ�ð�" << endl;
        QueryPerformanceCounter(&start);
        QuickSort(copy1, 0, n - 1); // �ð��� �����غ���
        QueryPerformanceCounter(&stop);
        cout << "QuickSort �ҿ�ð� : " << double(stop.QuadPart - start.QuadPart) * 1000 / freq.QuadPart << "ms" << endl; // �ҿ�ð��� ������ش�.
        QueryPerformanceCounter(&start);
        ShellSort(copy2, n); // �ð��� �����غ���
        QueryPerformanceCounter(&stop);
        cout << "ShellSort �ҿ�ð� : " << double(stop.QuadPart - start.QuadPart) * 1000 / freq.QuadPart << "ms" << endl; // �ҿ�ð��� ������ش�.
        cout << endl;
    }
    //delete[] arr;
    //delete[] copy1;
    //delete[] copy2;
    cout << "12171810 ������Ű��а� ������" << endl;
    return 0;
}
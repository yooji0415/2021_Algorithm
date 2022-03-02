// CUDA Runtime
#include <cuda_runtime.h>

// Utilities and system includes
#include "helper_cuda.h"
#include "helper_timer.h"

#include "sortingNetworks_common.h"

////////////////////////////////////////////////////////////////////////////////
// Test driver
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    cudaError_t error;
    printf("%s Starting...\n\n", argv[0]);

    printf("Starting up CUDA context...\n");
    int dev = findCudaDevice(argc, (const char**)argv);

    uint* h_InputKey, * h_InputVal, * h_OutputKeyGPU, * h_OutputValGPU;
    uint* d_InputKey, * d_InputVal, * d_OutputKey, * d_OutputVal;
    StopWatchInterface* hTimer = NULL;

    // 입력갯수와 평균시간을 측정하기위한 반복횟수 그리고 랜덤변수 생성을 위한
    // 나누어주는 숫자를 생성한다
    // 여기에서 N의 갯수를 바꾸어가면서 실행을 하였다
    const uint             N = 16777216;
    const uint           DIR = 0;
    const uint     numValues = 65536;
    const uint numIterations = 1;

    // 안정성(stable) 채크에 필요한 키 벨류 쌍 변수묶음을 생성해준다
    printf("Allocating and initializing host arrays...\n\n");
    sdkCreateTimer(&hTimer);
    h_InputKey = (uint*)malloc(N * sizeof(uint));
    h_InputVal = (uint*)malloc(N * sizeof(uint));
    h_OutputKeyGPU = (uint*)malloc(N * sizeof(uint));
    h_OutputValGPU = (uint*)malloc(N * sizeof(uint));
    srand(2001); // 랜드 시드값을 확인하고 1번과 2번 통합코드에도 적용했다
    // 랜덤한 변수를 생성해준다
    for (uint i = 0; i < N; i++)
    {
        h_InputKey[i] = rand() % numValues;
        h_InputVal[i] = i;
    }
    // 쿠다 동적할당을 해준다
    // 아마 GPU상 계산을 위해서 할당해주는 메모리로 보인다
    printf("Allocating and initializing CUDA arrays...\n\n");
    error = cudaMalloc((void**)&d_InputKey, N * sizeof(uint));
    checkCudaErrors(error);
    error = cudaMalloc((void**)&d_InputVal, N * sizeof(uint));
    checkCudaErrors(error);
    error = cudaMalloc((void**)&d_OutputKey, N * sizeof(uint));
    checkCudaErrors(error);
    error = cudaMalloc((void**)&d_OutputVal, N * sizeof(uint));
    checkCudaErrors(error);
    error = cudaMemcpy(d_InputKey, h_InputKey, N * sizeof(uint), cudaMemcpyHostToDevice);
    checkCudaErrors(error);
    error = cudaMemcpy(d_InputVal, h_InputVal, N * sizeof(uint), cudaMemcpyHostToDevice);
    checkCudaErrors(error);

    int flag = 1;
    printf("Running GPU bitonic sort (%u identical iterations)...\n\n", numIterations);

    for (uint arrayLength = 64; arrayLength <= N; arrayLength *= 2) // 어레이 길이를 64개부터 2배씩 증가시켜준다
    {
        printf("Testing array length %u (%u arrays per batch)...\n", arrayLength, N / arrayLength);
        // 테스트 하는 어레이의 길이와 묶음당 어레이 수를 알려준다
        // 테스트 하는 실질적인 개수 N개를 어떻게 분할하는지에 따라서 시간이 달라진다
        // 따라서 이 구조를 분해해서 테스트 어레이를 고정시켜서 하기 보다는 
        // 이 for문을 돌고 나온 결과중 가장 작은 값을 가지는 결과를 자료에 추가시키기로 했다
        error = cudaDeviceSynchronize();
        checkCudaErrors(error);

        sdkResetTimer(&hTimer);
        sdkStartTimer(&hTimer); // 시간측정을 초기화 한 이후 시작을 해준다
        uint threadCount = 0;

        for (uint i = 0; i < numIterations; i++)
            threadCount = bitonicSort(
                d_OutputKey,
                d_OutputVal,
                d_InputKey,
                d_InputVal,
                N / arrayLength,
                arrayLength,
                DIR
            );

        error = cudaDeviceSynchronize();
        checkCudaErrors(error);

        sdkStopTimer(&hTimer); // 시간측정을 멈춰준다
        printf("Average time: %f ms\n\n", sdkGetTimerValue(&hTimer) / numIterations); 
        // 걸린 평균 시간을 말해주는데 numIterations가 1인 관계로 사실상 한번 실행했을 경우의 시간을 알려준다

        if (arrayLength == N) // 만약 어레이의 길이가 끝에 다가왔으면
        {
            // bitonicSort 관련된 정보를 출력해준다
            double dTimeSecs = 1.0e-3 * sdkGetTimerValue(&hTimer) / numIterations;
            printf("sortingNetworks-bitonic, Throughput = %.4f MElements/s, Time = %.5f s, Size = %u elements, NumDevsUsed = %u, Workgroup = %u\n",
                (1.0e-6 * (double)arrayLength / dTimeSecs), dTimeSecs, arrayLength, 1, threadCount);
        }
        // 쿠다 메모리 관련 에러가 생겼는지를 채크한다
        printf("\nValidating the results...\n");
        printf("...reading back GPU results\n");
        error = cudaMemcpy(h_OutputKeyGPU, d_OutputKey, N * sizeof(uint), cudaMemcpyDeviceToHost);
        checkCudaErrors(error);
        error = cudaMemcpy(h_OutputValGPU, d_OutputVal, N * sizeof(uint), cudaMemcpyDeviceToHost);
        checkCudaErrors(error);

        int keysFlag = validateSortedKeys(h_OutputKeyGPU, h_InputKey, N / arrayLength, arrayLength, numValues, DIR);
        int valuesFlag = validateValues(h_OutputKeyGPU, h_OutputValGPU, h_InputKey, N / arrayLength, arrayLength);
        flag = flag && keysFlag && valuesFlag;
        printf("\n");
    }
    printf("12171810 정보통신공학과 유지훈\n");
    // 반복문을 종료하고 할당해주었던 동적할당 메모리를 풀어준다
    printf("Shutting down...\n");
    sdkDeleteTimer(&hTimer);
    cudaFree(d_OutputVal);
    cudaFree(d_OutputKey);
    cudaFree(d_InputVal);
    cudaFree(d_InputKey);
    free(h_OutputValGPU);
    free(h_OutputKeyGPU);
    free(h_InputVal);
    free(h_InputKey);

    exit(flag ? EXIT_SUCCESS : EXIT_FAILURE);
}

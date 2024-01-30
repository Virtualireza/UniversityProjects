#include <windows.h>
#include <iostream>
#include <chrono>
#include <time.h>
#include <stdlib.h>
using namespace std;
inline void Division(double* UnCompDiv, int start, int end)
{
    for (int i = start; i <= end; i++)
        UnCompDiv[i] = rand() % 3 + 1;
}
inline void Calculate_Childs_Sum(double* UnCompDiv, double* ShareMemory, int lands, double& Sum1, double& Sum2, double& Sum3)
{
    for (int i = 0, RelatedArea = 0; i <= lands - 1; i++, RelatedArea++)
    {
        if (UnCompDiv[i] == 1)
            Sum1 += ShareMemory[RelatedArea];
        else if (UnCompDiv[i] == 2)
            Sum2 += ShareMemory[RelatedArea];
        else
            Sum3 += ShareMemory[RelatedArea];
    }
}
inline void Update_Fault(double* UnCompDiv, double* ShareMemory, double exact_boy, double exact_daughter, int start, int end,int lands)
{
    double Boy1_Sum = 0, Boy2_Sum = 0, Daughter_Sum = 0, old_fault = ShareMemory[end + 1], new_fault;
    Calculate_Childs_Sum(UnCompDiv,ShareMemory, lands, Boy1_Sum, Boy2_Sum, Daughter_Sum);
    new_fault = abs(Boy1_Sum - exact_boy) + abs(Boy2_Sum - exact_boy) + abs(Daughter_Sum - exact_daughter);
    if (new_fault < old_fault || old_fault == -1)
    {
        ShareMemory[end + 1] = new_fault;
        for (int i = start, RelatedArea = 0; i <= end; i++, RelatedArea++)
            ShareMemory[i] = UnCompDiv[RelatedArea];
    }
}
int main()
{
    HANDLE SizeOfShareMemories_Handle = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 2 * sizeof(int), TEXT("OS3"));
    int* SizeOf_ShareMemories = (int*)MapViewOfFile(SizeOfShareMemories_Handle, FILE_MAP_ALL_ACCESS, 0, 0, 2 * sizeof(int));
    const int share_memory_size = SizeOf_ShareMemories[0];
    const int temp_share_memory_size = SizeOf_ShareMemories[1];
    HANDLE TempShareMemory_Handle = OpenFileMapping(FILE_MAP_ALL_ACCESS, false, TEXT("OS2"));
    unsigned long long int* TempShareMemory = (unsigned long long int*)MapViewOfFile(TempShareMemory_Handle, FILE_MAP_ALL_ACCESS, 0, 0, temp_share_memory_size * sizeof(unsigned long long int));
    HANDLE h = OpenFileMapping(FILE_MAP_ALL_ACCESS, false, TEXT("OS1"));
    double* ShareMemory = (double*)MapViewOfFile(h, FILE_MAP_ALL_ACCESS, 0, 0, share_memory_size * sizeof(double));
    const int lands = (share_memory_size - 10) / 6;
    const int sec = ShareMemory[6 * lands + 6];
    const int type = ShareMemory[6 * lands + 9] + 1;
    ShareMemory[6 * lands + 9] += 10;
    /*
        k in parent(== ShareMemory[6 * lands + 9]), become k++.
        Then the parent can know about the child is created and ran or no.
        This help parent to crate new child and set for him a different type.
        childs should have different types from each other.
    */
    const double exact_boy = ShareMemory[6 * lands + 7];
    const double exact_daughter = ShareMemory[6 * lands + 8];
    int i = type, j = i - 1 , r = i - 2 , start = i * lands + j, end = (i + 1) * lands + r;
    const int max_lands = 100;
    double UnCompDiv[max_lands];//UnCompared_Division
    unsigned long long int count_divs = 0;
    srand(GetCurrentProcessId() + time(NULL));
    auto startTime = std::chrono::steady_clock::now();
    auto endTime = startTime + std::chrono::seconds(sec);
    while (chrono::steady_clock::now() < endTime)
    {
        Division(UnCompDiv, 0, lands - 1);
        Update_Fault(UnCompDiv, ShareMemory, exact_boy, exact_daughter, start, end, lands);
        count_divs++;
    }
    TempShareMemory[type - 1] = count_divs;
    return 0;
}
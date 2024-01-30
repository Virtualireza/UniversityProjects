#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <string>
#include <chrono>
using namespace std;
const int max_lands = 100;
const int max_cores = 5;
inline int Get_Cores()
{
    int cores;
    cout << "Enter Cores (1,2,3,4,5) : ";
    cin >> cores;
    while (cores < 1 || cores > 5)
    {
        cout << "enter again between 1 to 5 : ";
        cin >> cores;
    }
    return cores;
}
inline int Get_Sec()
{
    int sec;
    cout << "Enter time (Second) : ";
    cin >> sec;
    return abs(sec);
}
inline int Get_Dataset()
{
    short dataset;
    cout << "Enter dataset (1,2,3,4,5,6) : ";
    cin >> dataset;
    while (dataset < 1 || dataset > 6)
    {
        cout << "enter again between 1 to 6 : ";
        cin >> dataset;
    }
    return dataset;
}
inline int CountLands(int dataset)
{
    string line;
    ifstream MyFile;
    switch (dataset)
    {
    case 1:
        MyFile.open("dataset1.txt");
        break;
    case 2:
        MyFile.open("dataset2.txt");
        break;
    case 3:
        MyFile.open("dataset3.txt");
        break;
    case 4:
        MyFile.open("dataset4.txt");
        break;
    case 5:
        MyFile.open("dataset5.txt");
        break;
    case 6:
        MyFile.open("dataset6.txt");
        break;
    }
    int n = 0;
    while (getline(MyFile, line, '\n'))
        n++;
    MyFile.close();
    return n;
}
inline double CalculateSum_InitializeSharememory(int dataset, double*& ShareMemory)
{
    double sum = 0;
    string line;
    ifstream MyFile;
    switch (dataset)
    {
    case 1:
        MyFile.open("dataset1.txt");
        break;
    case 2:
        MyFile.open("dataset2.txt");
        break;
    case 3:
        MyFile.open("dataset3.txt");
        break;
    case 4:
        MyFile.open("dataset4.txt");
        break;
    case 5:
        MyFile.open("dataset5.txt");
        break;
    case 6:
        MyFile.open("dataset6.txt");
        break;
    }
    int i = 0;
    while (getline(MyFile, line, '\n'))
    {
        double area = stod(line);
        ShareMemory[i] = area;
        sum += area;
        i++;
    }
    MyFile.close();
    return sum;
}
inline void Print_Count_Div(unsigned long long int* TempShareMemory,int cores)
{
    cout << "-----CORES SITUATION-----" << endl;
        for (int i = 1,Related = 0; i <= cores; i++,Related++)
            cout << "Core " << i << " executed " << TempShareMemory[Related] << " times" << endl;
    cout << endl;
}
inline void Print_exactShare_and_Lands_number(int lands, double exactshare_for_boy, double exactshare_for_daughter)
{
    cout << "number of lands : " << lands << endl;
    cout << "exact share for boys : " << fixed << setprecision(5) << exactshare_for_boy << endl;
    cout << "exact share for daughter : " << fixed << setprecision(5) << exactshare_for_daughter << endl << endl;
}
void LandsDivision(int dataset, int lands, double& exactshare_for_boy, double& exactshare_for_daughter, double*& ShareMemory)
{
    const double sum_of_all_lands_area = CalculateSum_InitializeSharememory(dataset, ShareMemory);
    cout << "sum of lands area : " << sum_of_all_lands_area << endl;
    exactshare_for_boy = sum_of_all_lands_area * 0.4;
    exactshare_for_daughter = sum_of_all_lands_area * 0.2;
    Print_exactShare_and_Lands_number(lands, exactshare_for_boy, exactshare_for_daughter);
}
inline void Print_ChildsValues(double* array, int last, int first)
{
    for (int i = 1, j = first; j < last; i++, j++)
        cout << i << ". " << array[j] << endl;
}
inline void Print_Lands(double* ShareMemory,int start_index,int last_index)
{
    double array[3 * max_lands];
    //0 to (1 * max_lands) - 1
    //1 * max_lands to (2 * max_lands) - 1
    //2 * max_lands to (3 * max_lands - 1)
    const int first_of_boy1 = 0;
    const int first_of_boy2 = max_lands;
    const int first_of_daughter = 2 * max_lands;
    int last_of_boy1 = first_of_boy1, last_of_boy2 = first_of_boy2, last_of_daughter = first_of_daughter;
    for (int i = start_index, RelatedArea = 0; i <= last_index; i++, RelatedArea++)
    {
        if (ShareMemory[i] == 1)
        {
            array[last_of_boy1] = ShareMemory[RelatedArea];
            last_of_boy1++;
        }
        else if (ShareMemory[i] == 2)
        {
            array[last_of_boy2] = ShareMemory[RelatedArea];
            last_of_boy2++;
        }
        else
        {
            array[last_of_daughter] = ShareMemory[RelatedArea];
            last_of_daughter++;
        }
    }
    cout << "BOY 1 LANDS : " << endl;
    Print_ChildsValues(array, last_of_boy1, first_of_boy1);
    cout << "BOY 2 LANDS : " << endl;
    Print_ChildsValues(array, last_of_boy2, first_of_boy2);
    cout << "DAUGHTER LANDS : " << endl;
    Print_ChildsValues(array, last_of_daughter, first_of_daughter);
}
void Print_Best(double* ShareMemory, int lands)
{
    int first_index[5];
    for (int i = 1, j = 0; i < 6; i++,j++)
        first_index[j] = i * lands + j;
    int last_index[5];
    for (int i = 2, j = -1, k = 0; i < 7; i++, j++, k++)
        last_index[k] = i * lands + j;
    double fault[5];
    cout << "-----FAULTS-----" << endl;
    for (int i = 0; i < 5; i++)
    {
        fault[i] = ShareMemory[last_index[i] + 1];
        cout << "core " << i + 1 << " fault = " << fault[i] << endl;
    }
    double minimum = fault[0];
    for (int i = 0; i < 5; i++)
        if ((fault[i] < minimum) && (fault[i] != -1))
            minimum = fault[i];
    cout << endl << "-----BEST DIVISIONS-----" << endl;
    for (int i = 0, j = 1; i < 5; i++)
        if (fault[i] == minimum)
        {
            cout << "number : " << j << endl;
            Print_Lands(ShareMemory, first_index[i], last_index[i]);
            j++;
            cout << "fault is : " << fault[i] << endl;
            cout << endl;
        }
}
void CreateChilds_PrintResults(int lands, double exactshare_for_boy, double exactshare_for_daughter, double*& ShareMemory, unsigned long long int* &TempShareMemory,int cores)
{
    for (int i = 2, j = 0; i < 7; i++,j++)
        ShareMemory[i * lands + j] = -1; // read child functions
    ShareMemory[6 * lands + 5] = lands;
    ShareMemory[6 * lands + 7] = exactshare_for_boy;
    ShareMemory[6 * lands + 8] = exactshare_for_daughter;
    ShareMemory[6 * lands + 9] = 9; // This cell defines type of each child
    STARTUPINFO s[max_cores];
    PROCESS_INFORMATION p[max_cores];
    int k = 0;
    while (true)
    {
        while ((k < cores) && (ShareMemory[6 * lands + 9] == k + 9))
        {
            /*
               conditions checks these : process created and read his type
               and changed "ShareMemory[6 * lands + 9] to ShareMemory[6 * lands + 9] + 10"
            */
            ZeroMemory(&s[k], sizeof(s[k]));
            s[k].cb = sizeof(s[k]);
            ZeroMemory(&p[k], sizeof(p[k]));
            ShareMemory[6 * lands + 9] = k;
            bool b = CreateProcess(TEXT("Child.exe"), NULL, NULL, NULL, FALSE, 0, NULL, NULL, &s[k], &p[k]);
            if (!b)
            {
                cout << "Create Process failed" << endl;
                exit(-1);
            }
            k++;
        }
        if (k == cores)
            break;
    }
    for (int k = 0; k < cores; k++)
    {
        WaitForSingleObject(p[k].hProcess, INFINITE);
        CloseHandle(p[k].hProcess);
        CloseHandle(p[k].hThread);
    }
    Print_Count_Div(TempShareMemory,cores);
    Print_Best(ShareMemory, lands);
}
void Create_ShareMemory(int dataset, int sec, double& boy, double& daughter, int lands, int share_memory_size,int temp_share_memory_size)
{
    HANDLE SizeOfShareMemories_Handle = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 2 * sizeof(int), TEXT("OS3"));
    int* SizeOf_ShareMemories = (int*)MapViewOfFile(SizeOfShareMemories_Handle, FILE_MAP_ALL_ACCESS, 0, 0, 2 * sizeof(int));
    SizeOf_ShareMemories[0] = share_memory_size;
    SizeOf_ShareMemories[1] = temp_share_memory_size;
    HANDLE TempShareMemory_Handle = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, temp_share_memory_size * sizeof(unsigned long long int), TEXT("OS2"));
    unsigned long long int* TempShareMemory = (unsigned long long int*)MapViewOfFile(TempShareMemory_Handle, FILE_MAP_ALL_ACCESS, 0, 0, temp_share_memory_size * sizeof(unsigned long long int));
    HANDLE h = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, share_memory_size * sizeof(double), TEXT("OS1"));
    double* ShareMemory = (double*)MapViewOfFile(h, FILE_MAP_ALL_ACCESS, 0, 0, share_memory_size * sizeof(double));
    ShareMemory[6 * lands + 6] = sec;
    LandsDivision(dataset, lands, boy, daughter, ShareMemory);
    CreateChilds_PrintResults(lands, boy, daughter, ShareMemory, TempShareMemory,temp_share_memory_size);
}
int main()
{
    cout << "-----INPUTED VALUES-----" << endl;
    int cores = Get_Cores();
    int dataset = Get_Dataset();
    int sec = Get_Sec();
    double exactshare_for_boy, exactshare_for_daughter;
    int lands = CountLands(dataset);
    int share_memory_size = (lands * 6) + 10;
    int temp_share_memory_size = cores;
    Create_ShareMemory(dataset, sec, exactshare_for_boy, exactshare_for_daughter, lands, share_memory_size,temp_share_memory_size);
    return 0;
}
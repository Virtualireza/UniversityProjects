#include <iostream>
#include <windows.h>
#include <chrono>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;
const int max_lands = 100;
const int max_cores = 5;
double exactshare_for_boy, exactshare_for_daughter;
const int max_share_array_size = 6 * max_lands + 5;
int cores, dataset, sec, lands;
double ShareArray[max_share_array_size];
unsigned long long int TempShareArray[max_cores];
bool created = false;
int last_pid = 1;
double Sum_of_All = 0;
inline void CalculateSum_InitializeShareArray()
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
    int i = 0;
    while (getline(MyFile, line, '\n'))
    {
        double area = stod(line);
        ShareArray[i] = area;
        Sum_of_All += area;
        i++;
        lands++;
    }
    MyFile.close();
}
inline void Print_Count_Div()
{
    cout << "-----THREADS SITUATION-----" << endl;
    for (int i = 1, Related = 0; i <= cores; i++, Related++)
        cout << "thread " << i << " executed " << TempShareArray[Related] << " times" << endl;
    cout << endl;
}
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
inline void Division(double* UnCompDiv)
{
    for (int i = 0; i <= lands - 1; i++)
        UnCompDiv[i] = rand() % 3 + 1;
}
inline void Calculate_Childs_Sum(double* UnCompDiv, double& Sum1, double& Sum2, double& Sum3)
{
    for (int i = 0, RelatedArea = 0; i <= lands - 1; i++, RelatedArea++)
    {
        if (UnCompDiv[i] == 1)
            Sum1 += ShareArray[RelatedArea];
        else if (UnCompDiv[i] == 2)
            Sum2 += ShareArray[RelatedArea];
        else
            Sum3 += ShareArray[RelatedArea];
    }
}
inline void Update_Fault(double* UnCompDiv, int start, int end)
{
    double Boy1_Sum = 0, Boy2_Sum = 0, Daughter_Sum = 0, old_fault = ShareArray[end + 1], new_fault;
    Calculate_Childs_Sum(UnCompDiv, Boy1_Sum, Boy2_Sum, Daughter_Sum);
    new_fault = abs(Boy1_Sum - exactshare_for_boy) + abs(Boy2_Sum - exactshare_for_boy) + abs(Daughter_Sum - exactshare_for_daughter);
    if (new_fault < old_fault || old_fault == -1)
    {
        ShareArray[end + 1] = new_fault;
        for (int i = start, RelatedArea = 0; i <= end; i++, RelatedArea++)
            ShareArray[i] = UnCompDiv[RelatedArea];
    }
}
inline void Print_ChildsValues(double* array, int last, int first)
{
    for (int i = 1, j = first; j < last; i++, j++)
        cout << i << ". " << array[j] << endl;
}
inline void Print_Lands(int start_index, int last_index)
{
    double array[3 * max_lands];
    const int first_of_boy1 = 0;
    const int first_of_boy2 = max_lands;
    const int first_of_daughter = 2 * max_lands;
    int last_of_boy1 = first_of_boy1, last_of_boy2 = first_of_boy2, last_of_daughter = first_of_daughter;
    for (int i = start_index, RelatedArea = 0; i <= last_index; i++, RelatedArea++)
    {
        if (ShareArray[i] == 1)
        {
            array[last_of_boy1] = ShareArray[RelatedArea];
            last_of_boy1++;
        }
        else if (ShareArray[i] == 2)
        {
            array[last_of_boy2] = ShareArray[RelatedArea];
            last_of_boy2++;
        }
        else
        {
            array[last_of_daughter] = ShareArray[RelatedArea];
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
void Print_Best()
{
    int first_index[5];
    for (int i = 1, j = 0; i < 6; i++, j++)
        first_index[j] = i * lands + j;
    int last_index[5];
    for (int i = 2, j = -1, k = 0; i < 7; i++, j++, k++)
        last_index[k] = i * lands + j;
    double fault[5];
    cout << "-----FAULTS-----" << endl;
    for (int i = 0; i < 5; i++)
    {
        fault[i] = ShareArray[last_index[i] + 1];
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
            Print_Lands(first_index[i], last_index[i]);
            j++;
            cout << "fault is : " << fault[i] << endl;
            cout << endl;
        }
}
DWORD WINAPI Child(LPVOID Param)
{
    int pid = last_pid;
    srand(time(NULL) + pid);
    created = true;
    int i = pid;
    int j = i - 1;
    int r = i - 2;
    int start = i * lands + j;
    int end = (i + 1) * lands + r;
    double UnCompDiv[max_lands];//UnCompared_Division
    unsigned long long int count_divs = 0;
    auto startTime = std::chrono::steady_clock::now();
    auto endTime = startTime + std::chrono::seconds(sec);
    while (chrono::steady_clock::now() < endTime)
    {
        Division(UnCompDiv);
        Update_Fault(UnCompDiv, start, end);
        count_divs++;
    }
    TempShareArray[pid - 1] = count_divs;
    return 0;
}
inline void Create_Threads()
{
    HANDLE Childhandle[max_cores];
    for (int i = 0; i < cores; i++, last_pid++, created = false)
    {
        Childhandle[i] = CreateThread(NULL, 0, Child, NULL, 0, NULL);
        if (!Childhandle[i])
        {
            cout << "Create Threads failed" << endl;
            exit(-1);
        }
        while (!created);
    }
    for (int i = 0; i < cores; i++)
    {
        WaitForSingleObject(Childhandle[i], INFINITE);
        CloseHandle(Childhandle[i]);
    }
    Print_Count_Div();
    Print_Best();
}
void inline InitializeShareArray()
{
    for (int i = 2, j = 0; i < 7; i++, j++)
        ShareArray[i * lands + j] = -1;
}
void inline Set_Value()
{
    cout << "-----INPUTED VALUES-----" << endl;
    cores = Get_Cores();
    dataset = Get_Dataset();
    sec = Get_Sec();
    CalculateSum_InitializeShareArray();
    cout << "sum of lands area : " << Sum_of_All << endl;
    exactshare_for_boy = Sum_of_All * 0.4;
    exactshare_for_daughter = Sum_of_All * 0.2;
    cout << "number of lands : " << lands << endl;
    cout << "exact share for boys : " << fixed << setprecision(5) << exactshare_for_boy << endl;
    cout << "exact share for daughter : " << fixed << setprecision(5) << exactshare_for_daughter << endl << endl;
    InitializeShareArray();
}
int main()
{
    Set_Value();
    Create_Threads();
    return 0;
}
#include <iostream>
#include <windows.h>
#include <chrono>
#include <time.h>
#include <fstream>
#include <string>
#include <thread>
using namespace std;
double exactshare_for_boy, exactshare_for_daughter, Sum_of_All;
int cores = std::thread::hardware_concurrency() - 1, dataset, sec, lands;
double* ShareArray = nullptr;
bool* is_all_threads_finished = new bool[cores];
int Best_Calculator_ID;
double* LastBest = new double[cores];
HANDLE writersLock, WakeUp, p;
HANDLE* Childhandle = new HANDLE[cores];
unsigned long long int* Count_Tries = new unsigned long long int[cores];
inline void Does_Semaphore_Created(HANDLE h1, HANDLE h2, HANDLE h3)
{
	if (!h1 || !h2 || !h3)
	{
		cout << "Create Semaphores failed" << endl;
		exit(-1);
	}
}
inline void Set_Threads_Activities_Control_Array()
{
	for (int i = 0; i < cores; i++)
	{
		is_all_threads_finished[i] = false;
		Count_Tries[i] = 0;
		LastBest[i] = -1;
	}
}
inline bool Does_Threads_Activities_Finished()
{
	for (int i = 0; i < cores; i++)
		if (!is_all_threads_finished[i])
			return false;
	return true;
}
inline void Count_Lands()
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
	while (getline(MyFile, line, '\n'))
		lands++;
	MyFile.close();
}
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
	for (int i = 0; i < lands; i++)
	{
		getline(MyFile, line, '\n');
		double area = stod(line);
		Sum_of_All += area;
		ShareArray[i] = area;
	}
	MyFile.close();
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
inline void Division(double*& UnCompDiv, int my_id)
{
	for (int i = 0; i < lands; i++)
		UnCompDiv[i] = rand() % 3 + 1;
	++Count_Tries[my_id];
}
inline void Calculate_Childs_Sum(double*& UnCompDiv, double& Sum1, double& Sum2, double& Sum3)
{
	for (int i = 0, RelatedArea = 0; i < lands; i++, RelatedArea++)
	{
		if (UnCompDiv[i] == 1)
			Sum1 += ShareArray[RelatedArea];
		else if (UnCompDiv[i] == 2)
			Sum2 += ShareArray[RelatedArea];
		else
			Sum3 += ShareArray[RelatedArea];
	}
}
inline void Update_Diff(double*& UnCompDiv, int my_id)
{
	double Boy1_Sum = 0, Boy2_Sum = 0, Daughter_Sum = 0, diff = 0;
	Calculate_Childs_Sum(UnCompDiv, Boy1_Sum, Boy2_Sum, Daughter_Sum);
	diff = abs(Boy1_Sum - exactshare_for_boy) + abs(Boy2_Sum - exactshare_for_boy) + abs(Daughter_Sum - exactshare_for_daughter);

	// READ SECTION
	//LastBest[my_id] = ShareArray[2 * lands];

	//if (diff < LastBest[my_id] || LastBest[my_id] == -1)
	{
		LastBest[my_id] = diff;

		// BEFORE WRITE SECTION
		WaitForSingleObject(writersLock, INFINITE);
		
		// WRITE SECTION
		if ((diff < ShareArray[2 * lands] || ShareArray[2 * lands] == -1)) // Am I Better than front of me (last) writer ?
		{
			ShareArray[2 * lands] = diff;
			Best_Calculator_ID = my_id;
			for (int i = lands, RelatedArea = 0; RelatedArea < lands; i++, RelatedArea++)
				ShareArray[i] = UnCompDiv[RelatedArea];
			ReleaseSemaphore(WakeUp, 1, NULL);
			WaitForSingleObject(p, INFINITE);
		}
		LastBest[my_id] = ShareArray[2 * lands];
		// AFTER WRITE SECTION
		ReleaseSemaphore(writersLock, 1, NULL);
	}
}
inline void Print_ChildsValues(double* array, int last)
{
	for (int i = 1, j = 0; j <= last; i++, j++)
		cout << i << ". " << array[j] << endl;
}
inline void Print_Lands()
{
	cout << "\n-----BEST DIVISIONS-----" << endl;
	double* Boy1 = new double[lands];
	double* Boy2 = new double[lands];
	double* Daughter = new double[lands];
	int last_of_boy1 = -1, last_of_boy2 = -1, last_of_daughter = -1;
	const int last = 2 * lands - 1;
	for (int i = lands, RelatedArea = 0; i <= last; i++, RelatedArea++)
	{
		if (ShareArray[i] == 1)
		{
			last_of_boy1++;
			Boy1[last_of_boy1] = ShareArray[RelatedArea];
		}
		else if (ShareArray[i] == 2)
		{
			last_of_boy2++;
			Boy2[last_of_boy2] = ShareArray[RelatedArea];
		}
		else
		{
			last_of_daughter++;
			Daughter[last_of_daughter] = ShareArray[RelatedArea];
		}
	}
	cout << "\nBOY 1 LANDS : " << endl;
	Print_ChildsValues(Boy1, last_of_boy1);
	cout << "\nBOY 2 LANDS : " << endl;
	Print_ChildsValues(Boy2, last_of_boy2);
	cout << "\nDAUGHTER LANDS : " << endl;
	Print_ChildsValues(Daughter, last_of_daughter);
	cout << "\n-----DIFFERENTION-----\n";
	cout << ShareArray[2 * lands] << endl;
}
DWORD WINAPI Child(LPVOID lpParam)
{
	int* pValue = static_cast<int*>(lpParam);
	int my_id = *pValue;
	srand(time(NULL) + my_id);
	double* UnCompDiv = new double[lands];//UnCompared_Division
	auto startTime = std::chrono::steady_clock::now();
	auto endTime = startTime + std::chrono::seconds(sec);
	while (chrono::steady_clock::now() < endTime)
	{
		Division(UnCompDiv, my_id);
		Update_Diff(UnCompDiv, my_id);
	}
	is_all_threads_finished[my_id] = true;
	delete pValue;
	if (my_id == 0)
	{
		for (int i = 1; i < cores; i++)
			WaitForSingleObject(Childhandle[i], INFINITE);
		ReleaseSemaphore(WakeUp, 1, NULL);
	}
	return 0;
}
inline void Create_Threads()
{
	writersLock = CreateSemaphore(NULL, 1, 1, NULL);
	WakeUp = CreateSemaphore(NULL, 0, 1, NULL);
	p = CreateSemaphore(NULL, 0, 1, NULL);
	Does_Semaphore_Created(WakeUp, writersLock, p);
	for (int i = 0; i < cores; i++)
	{
		int* pValue = new int(i);
		Childhandle[i] = CreateThread(NULL, 0, Child, pValue, 0, NULL);
		if (!Childhandle[i])
		{
			cout << "Create Threads failed" << endl;
			exit(-1);
		}
	}
	unsigned long long int Count_Best_Division = 0;
	while (true)
	{
		WaitForSingleObject(WakeUp, INFINITE);
		if (Does_Threads_Activities_Finished())
			break;
		Count_Best_Division++;
		cout << Count_Best_Division << ". " << ShareArray[2 * lands] << endl;
		cout << "by THREAD = " << Best_Calculator_ID << '\t';
		cout << "TRY number = " << Count_Tries[Best_Calculator_ID] << endl;
		ReleaseSemaphore(p, 1, NULL);
	}
	for (int i = 0; i < cores; i++)
		CloseHandle(Childhandle[i]);
	CloseHandle(WakeUp);
	CloseHandle(writersLock);
	CloseHandle(p);
	Print_Lands();
}
void inline Set_Value()
{
	if (cores == 0)
	{
		cout << "Count Cores failed" << endl;
		exit(-1);
	}
	cout << "-----INPUTED VALUES-----" << endl;
	dataset = Get_Dataset();
	sec = Get_Sec();
	Set_Threads_Activities_Control_Array();
	Count_Lands();
	ShareArray = new double[2 * lands + 1];
	ShareArray[2 * lands] = -1;
	CalculateSum_InitializeShareArray();
	cout << "sum of lands area : " << Sum_of_All << endl;
	exactshare_for_boy = Sum_of_All * 0.4;
	exactshare_for_daughter = Sum_of_All * 0.2;
	cout << "number of lands : " << lands << endl;
	cout << "exact share for boys : " << exactshare_for_boy << endl;
	cout << "exact share for daughter : " << exactshare_for_daughter << endl << endl;
}
int main()
{
	Set_Value();
	Create_Threads();
	return 0;
}
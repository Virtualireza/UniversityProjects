#include <iostream>
#include <fstream>
using namespace std;
int PacketsNumber,BoxProducersNumber;
int* PacketsSize;
int** BoxesSize;
int ProducersID = -1;
int* BoxesNumber_of_a_Producer;
int BestProducer = -1;
bool Continue = true;
bool boxFound = false;
int emptySpace = 0;
int lastFitBox = -1;
bool is_this_char_an_ineger (char ch)
{
    if (ch > 57 || ch < 48)
        return false;
    return true;
}
bool is_there_same_size_boxes (int * array,int arraysize)
{
    bool check = false;
    for (int i = 0 ; i < arraysize ; i++)
        for (int j = i+1 ; j < arraysize ; j++)
            if (array[i] == array[j])
            {
                check = true;
                cout << "ERROR : file has problem in line 2" << '\n';
                cout << "DESCRIPTION : there are same size boxes" << '\n';
                exit(-1);
            }
    return check;
}
int find_Producer_BoxNumbers(string data,int lenght)
{
    int k = 0;
    for (int j = 1 ; j <= lenght - 2 ; j++)
        if (data[j] == ' ')
            k++;
    return k+1;
}
inline void modify_BoxesSize (string data)
{
    int lenght = data.length();
    string num;
    int i = -1;
    if(data[0] == ' ')
    {
        cout << "ERROR : file has problems" << '\n';
        cout << "DESCRIPTION : BoxesSize of a producer starts with space" << '\n';
        exit(-1);
    }
    if(data[lenght - 1] == ' ')
    {
        cout << "ERROR : file has problems" << '\n';
        cout << "DESCRIPTION : BoxesSize of a producer ends with space" << '\n';
        exit(-1);
    }
    int CurrentProducer_BoxNumbers = find_Producer_BoxNumbers(data,lenght);
    ProducersID++;
    BoxesSize[ProducersID] = new int[CurrentProducer_BoxNumbers];
    BoxesNumber_of_a_Producer[ProducersID] = CurrentProducer_BoxNumbers;
    for (int j = 0 ; j < lenght ; j++)
    {
        if (data[j] == ' ')
        {
            if (data[j - 1] == ' ')
            {
                cout << "ERROR : file has problems" << '\n';
                cout << "DESCRIPTION : BoxesSize has a sequence (more than one) of spaces" << '\n';
                exit(-1);
            }
            else
            {
                i++;
                BoxesSize[ProducersID][i] = stoi(num);
                num = "";
            }
        }
        else if(!is_this_char_an_ineger(data[j]))
        {
            cout << "ERROR : file has problems" << '\n';
            cout << "DESCRIPTION : there are non-integer characters for size boxes in file" << '\n';
            exit(-1);
        }
        else //data[j] is integer
            num += data[j];
    }
    if (num != "") // num has some characters
        BoxesSize[ProducersID][CurrentProducer_BoxNumbers - 1] = stoi(num);
}
inline void modify_PacketsSizes (string data)
{
    int lenght = data.length();
    if (lenght < 2*PacketsNumber-1)
    {
        cout << "ERROR : file has problems in line 2" << '\n';
        cout << "DESCRIPTION : there are not enough size boxes in file" << '\n';
        exit(-1);
    }
    PacketsSize = new int[PacketsNumber];
    string num;
    int i = -1;
    if(data[0] == ' ')
    {
        cout << "ERROR : file has problems in line 2" << '\n';
        cout << "DESCRIPTION : line 2 starts with space" << '\n';
        exit(-1);
    }
    if(data[lenght - 1] == ' ')
    {
        cout << "ERROR : file has problems in line 2" << '\n';
        cout << "DESCRIPTION : line 2 ends with space" << '\n';
        exit(-1);
    }
    for (int j = 0 ; j < lenght ; j++)
    {
        if (data[j] == ' ')
        {
            if (data[j - 1] == ' ')
            {
                cout << "ERROR : file has problems in line 2" << '\n';
                cout << "DESCRIPTION : line 2 has a sequence (more than one) of spaces" << '\n';
                exit(-1);
            }
            else
            {
                i++;
                PacketsSize[i] = stoi(num);
                if (PacketsSize[i] < 1)
                {
                    cout << "ERROR : file has problems in line 2" << '\n';
                    cout << "DESCRIPTION : Packets size should greater than 1" << '\n';
                    exit(-1);
                }
                num = "";
            }
        }
        else if(!is_this_char_an_ineger(data[j]))
        {
            cout << "ERROR : file has problems in line 2" << '\n';
            cout << "DESCRIPTION : there are non-integer characters for size packets in file" << '\n';
            exit(-1);
        }
        else //data[j] is integer
            num += data[j];
    }
    if (num != "") // num has some characters
    {
        if (stoi(num) < 1)
        {
            cout << "ERROR : file has problems in line 2" << '\n';
            cout << "DESCRIPTION : Packets size should greater than 1" << '\n';
            exit(-1);
        }
        else
            PacketsSize[PacketsNumber - 1] = stoi(num);
    }
}
void readfile ()
{
    string data;
    fstream file;
    bool BADFILE = false;
    file.open("in1.txt");
    for (int i = 1 ; i < 4 ; i++) 
    {
        getline(file,data,'\n');
        if (data == "" || data == " ")
        {
            BADFILE = true;
            break;
        }
        if (i == 1)
            PacketsNumber = stoi(data);
        else if (i == 2)
            modify_PacketsSizes(data);
        else if (i == 3)
            BoxProducersNumber = stoi(data);
    }
    if (BADFILE)
    {
        cout << "ERROR : file has problems" << '\n';
        cout << "DESCRIPTION : there are not enough lines in file ( 3< )" << '\n';
        exit(-1);
    }
    is_there_same_size_boxes(PacketsSize, PacketsNumber);
    int exepted_producers_nums = BoxProducersNumber;
    BoxesSize = new int* [BoxProducersNumber];
    BoxesNumber_of_a_Producer = new int [BoxProducersNumber];
    while (getline(file,data,'\n'))
    {
        modify_BoxesSize(data);
        exepted_producers_nums--;
    }
    if (exepted_producers_nums != 0)
    {
        cout << "ERROR : file has problems" << '\n';
        cout << "DESCRIPTION : the lines that define sizes of boxes for each producer is lower than number of BoxProducers" << '\n';
        exit(-1);
    }
    file.close();
}
void print_PacketsSize ()
{
    for (int i = 0; i < PacketsNumber; i++)
        cout << PacketsSize[i] << '\t';
    cout << endl;
}
void print_BoxesSize_of_a_producer (int id)
{
    int k = BoxesNumber_of_a_Producer[id];
    for (int i = 1; i <= k ; i++)
        cout << BoxesSize[id][i] << '\t';
}
int partition(int* arr, int low, int high)
{
    int pivot = arr[low];
    int left = low + 1;
    int right = high;
    while (true) 
    {
        while (left <= right && arr[left] <= pivot)
            left++;
        while (left <= right && arr[right] >= pivot)
            right--;
        if (left < right)
            std::swap(arr[left], arr[right]);
        else
            break;
    }
    std::swap(arr[low], arr[right]);
    return right;
}
void quickSort(int* arr, int low, int high)
{
    if (low < high) 
    {
        int j = partition(arr, low, high);
        quickSort(arr, low, j - 1);
        quickSort(arr, j + 1, high);
    }
}
void sort_all_arrays ()
{
    quickSort(PacketsSize,0, PacketsNumber - 1);
    for (int i = 0; i < BoxProducersNumber; i++)
        quickSort(BoxesSize[i], 0, BoxesNumber_of_a_Producer[i]);
}
void division (int ID,int n,int m)
{
    if (Continue && n >= 0)
    {
        if (!boxFound)
            division(ID,n-1,m);
        if (Continue)
        {
            if (BoxesSize[ID][m] < PacketsSize[n])
            {
                if (!boxFound)
                {
                    cout << "ERROR : Division faild.";
                    cout << "can not put all Packets in Boxes of this Producer (";
                    cout << PacketsSize[n] << " > " << BoxesSize[ID][m] << ")" << '\n';
                    Continue = false;
                }
                else
                {
                    cout << PacketsSize[n] << " into " << lastFitBox;
                    cout << '\t' << " +" << lastFitBox - PacketsSize[n] << endl;
                    emptySpace += lastFitBox - PacketsSize[n];
                }
                boxFound = false;
                lastFitBox = -1;
            }
            else if (lastFitBox == -1 || lastFitBox > BoxesSize[ID][m])//BoxesSize[ID][m]>=PacketsSize[n]
            {
                if (BoxesSize[ID][m] - PacketsSize[n] == 0)
                {
                    lastFitBox = BoxesSize[ID][m];
                    cout << PacketsSize[n] << " into " << lastFitBox;
                    cout << '\t' << " +" << 0 << endl;
                    boxFound = false;
                    lastFitBox = -1;
                }
                else //BoxesSize[ID][m]>PacketsSize[n]
                {
                    lastFitBox = BoxesSize[ID][m];
                    boxFound = true;
                    if (m >= 2)
                        division(ID,n,m-1);
                    else // m = 1
                    {
                        cout << PacketsSize[n] << " into " << lastFitBox;
                        cout << '\t' << " +" << lastFitBox - PacketsSize[n] << endl;
                        emptySpace += lastFitBox - PacketsSize[n];
                        boxFound = false;
                        lastFitBox = -1;
                    }
                }
            }
        }
    }
}
void print_finalanswer_of_producer ()
{
    sort_all_arrays();
    cout << "PacketsSize : ";
    print_PacketsSize();
    cout << endl;
    int MinimunemptySpace = -1;
    for (int ID = 1;ID<=BoxProducersNumber;ID++,cout<<endl,Continue=true,boxFound=false,emptySpace=0,lastFitBox=-1)
    {
        cout << "ProducerID : " << ID << endl;
        cout << "BoxesSize : ";
        print_BoxesSize_of_a_producer(ID-1);
        cout << endl;
        division(ID-1,PacketsNumber - 1,BoxesNumber_of_a_Producer[ID-1]);
        if (Continue)
        {
            cout << "Total emptySpace : " << emptySpace << endl;
            if (MinimunemptySpace > emptySpace || MinimunemptySpace == -1)
            {
                BestProducer = ID;
                MinimunemptySpace = emptySpace;
            }
        }
    }
    cout << "-----------The Best answer------------" << endl;
    if (BestProducer == -1)
        cout << "NOT found..." << endl;
    else
        cout << "BestProducer : " << BestProducer << endl;
}
void report ()
{
    readfile();
    print_finalanswer_of_producer();
}
int main()
{
    report();
    return 0;
}
/*
bool is_this_string_an_ineger (string str)
{
    int lenght = str.length();
    for (int i = 0; i < lenght; i++)
        if (str[i] > 57 || str[i] < 48)
            return false;
    return true;
}
 
 struct node
 {
     int BoxSize = NULL;
     node * next = NULL;
 };
 
 void print_nodes (node* FirstNode)
 {
     node* CurrentNode = FirstNode;
     while (CurrentNode) {
         cout << CurrentNode -> BoxSize << '\t';
         CurrentNode = CurrentNode -> next;
     }
     cout << '\n';
 }
 
 -------------------------------------------------------
 TEST readfile() function
 
 for (int i = 0; i < PacketsNumber; i++)
     cout << PacketsSize[i] << '\t';
 
 cout << endl;
 
 for (int i = 0; i < BoxProducersNumber; i++)
     for (int j = 0; j < 3; j++)
         cout << BoxesSize[i][j] << '\t';
 
 cout << endl;
 
 for (int i = 0; i < BoxProducersNumber; i++)
     cout << BoxesNumber_of_a_Producer[i] << '\t';
 
 cout << endl;
 
 for (int i = 0; i < BoxProducersNumber; i++,cout << endl)
     for (int j = 1; j <= BoxesNumber_of_a_Producer[i]; j++)
         cout << BoxesSize[i][j] << '\t';
 -------------------------------------------------------
*/

#include <iostream>
#include <fstream>
using namespace std;
int*** TravelDistance;//TravelCost[a][b][c] => you can knows from this matrix that which one of hotels has ways between thems
// => a:beginning Station    b:hotel number b(b omin) of station a    c:hotel number c(c omin) of station a+1
int** StationHotelsInfo; // cell number 0 of each matrix, defines number of hotels in station
int* HotelCost;// cost of stay one night in each hotel
int* CheapestCostUntilStation; // Cheapest cost to reach this station (= ANSWER of the problem)
int* BestHotelUntilStation; // saves reached hotel on mentioned station (=cell number of matrix)
int* CheapestCostUntilHotel; // Cheapest cost to reach this hotel (= ANSWER of the problem)
//int* CheapestCostUntilHotel; // Cheapest cost to reach this station (= ANSWER of the problem)
int Stations,Hotels = 1;//number of them. assume beginning Station By default has a hotel
const int feeCost = 50000;
bool* there_is_a_way_to_station;
int* pervious_hotel;
//WARNING :
//This code working only when number of hotels start from 0 and Hotel 0 is the only hotel of the beginning Station
//Next hotels of other Stations should be IN ORDER (in file and in numbers) from 1 to number of last hotels
void find_BestWays ()
{
    for (int step = 1 , l = step - 1 , minimum_cost = -1 , current_cost = -1,perv_costs ; step < Stations ; step++,l = step - 1,minimum_cost = -1)
        {
            for(int j = 0 ; j < StationHotelsInfo[l][0] ; j++) // hotels of beginning Station
            {
                perv_costs = CheapestCostUntilHotel[StationHotelsInfo[l][1 + j]];
                for(int k = 0 ; k < StationHotelsInfo[l + 1][0] ; k++) // hotels of next Station
                {
                    if (TravelDistance[l][j][k] == -1)
                        continue;
                    there_is_a_way_to_station[l + 1] = true;
                    current_cost = perv_costs + HotelCost[StationHotelsInfo[l + 1][1 + k]] + TravelDistance[l][j][k] * feeCost;
                    if (minimum_cost > current_cost || minimum_cost == -1)
                    {
                        minimum_cost = current_cost;
                        BestHotelUntilStation[l + 1] = StationHotelsInfo[l + 1][1 + k];
                    }
                    if (CheapestCostUntilHotel[StationHotelsInfo[l + 1][1 + k]] == 0 || CheapestCostUntilHotel[StationHotelsInfo[l + 1][1 + k]] > current_cost)
                    {
                        CheapestCostUntilHotel[StationHotelsInfo[l + 1][1 + k]] = current_cost;
                        pervious_hotel[StationHotelsInfo[l + 1][1 + k]] = StationHotelsInfo[l][1+j];
                    }
                }
                if (!there_is_a_way_to_station[l + 1] && j + 1 == StationHotelsInfo[l][0])
                {
                    cout << "ERROR : there is not a way from Station " << l << " to Station " << l+1 << '\n';
                    exit(-1);
                }
            }
            if (minimum_cost != -1)
                CheapestCostUntilStation[l + 1] = minimum_cost;
        }
}
void print_BestWays ()
{
    find_BestWays();
    cout << "Total Cost : " << CheapestCostUntilStation[Stations - 1] << endl;
    cout << "--------------------------" << endl;
    cout << "Station " << Stations - 1 << " : " << "Hotel " << BestHotelUntilStation[Stations - 1] << endl;
    cout << "--------------------------" << endl;
    for (int p = pervious_hotel[BestHotelUntilStation[Stations - 1]],i = 0,s=Stations-2 ;i <= Stations - 2; p = pervious_hotel[p],i++,s--)
        if (p != -1)
        {
            cout << "Station " << s << " : " << "Hotel " << p << endl;
            cout << "--------------------------" << endl;
        }
}
int find_hotelOeder_in_itsStation (int hotelNumber)
{
    int result = -1;
    int y;
    for (int s = 0 ; s < Stations ; s++)
    {
        y = StationHotelsInfo[s][0];
        for (int k = 1 ; k <= y ; k++)
            if(StationHotelsInfo[s][k] == hotelNumber)
            {
                result = k - 1;
                break;
            }
    }
    return result;
}
int find_Station_from_hotelNumber (int n)
{
    int result = -1;
    int y;
    for (int s = 0 ; s < Stations ; s++)
    {
        y = StationHotelsInfo[s][0];
        for (int k = 1 ; k <= y ; k++)
            if(StationHotelsInfo[s][k] == n)
            {
                result = s;
                break;
            }
    }
    return result;
}
void test ()
{
    for (int i = 0 ; i < Stations ; cout << endl, i++)
    {
        cout << "Hotels of Station " << i << " : ";
        for (int j = 1 ; j <= StationHotelsInfo[i][0]; j++)
            cout << StationHotelsInfo[i][j] << "  ";
    }
    for (int i = 1 ; i < Hotels ; i++)
        cout << HotelCost[i] << endl;
    for (int s = 0 ; s < Stations - 1 ; s++)
        for (int i = 0 ; i < StationHotelsInfo[s][0] ; i++)
            for (int j = 0; j < StationHotelsInfo[s+1][0] ; j++)
                cout << TravelDistance [s][i][j] << endl;
}
bool is_this_char_an_ineger (char ch)
{
    if (ch > 57 || ch < 48)
        return false;
    return true;
}
void modify_Distance_array ()
{
    int beginningStation = 0,currentStationHotels,nextStationHotels;
    while (beginningStation < Stations - 1)
    {
        currentStationHotels = StationHotelsInfo[beginningStation][0];
        TravelDistance[beginningStation] = new int*[currentStationHotels];
        nextStationHotels = StationHotelsInfo[beginningStation + 1][0];
        for (int j = 0 ; j < currentStationHotels ;j++)
        {
            TravelDistance[beginningStation][j] = new int[nextStationHotels];
            for (int d = 0 ; d < nextStationHotels ; d++)
                TravelDistance[beginningStation][j][d] = -1; // each way from any hotel to another one, has -1 as Default cost that means there is not any way from j to d
        }
        beginningStation++;
    }
}
void modify_Distances (string data)
{
    unsigned long int lenght = data.length();
    if (lenght < 5)
    {
        cout << "ERROR : file has problems in part two (Distances)" << '\n';
        cout << "DESCRIPTION : there are not enough information" << '\n';
        exit(-1);
    }
    string num;
    if(data[0] == ' ')
    {
        cout << "ERROR : file has problems in part two (Distances)" << '\n';
        cout << "DESCRIPTION : Distances starts with space" << '\n';
        exit(-1);
    }
    if(data[lenght - 1] == ' ')
    {
        cout << "ERROR : file has problems in part two (Distances)" << '\n';
        cout << "DESCRIPTION : Distances ends with space" << '\n';
        exit(-1);
    }
    int start_Hotel = -1,end_Hotel = -1,steps = 1,start_Station = -1;
    for (int j = 0 ; j < lenght ; j++)
    {
        if (data[j] == ' ')
        {
            if (data[j - 1] == ' ')
            {
                cout << "ERROR : file has problems in part two (Distances)" << '\n';
                cout << "DESCRIPTION : Distances has a sequence (more than one) of spaces" << '\n';
                exit(-1);
            }
            else
            {
                if (stoi(num) < 0)
                {
                    cout << "ERROR : file has problems in part two (Distances)" << '\n';
                    cout << "DESCRIPTION : Hotels number and Distances should be positive" << '\n';
                    exit(-1);
                }
                if (steps == 1) // start_Hotel should initialized
                {
                    start_Hotel = stoi(num);
                    start_Station = find_Station_from_hotelNumber(start_Hotel);
                }
                else // end_Hotel should initialized
                    end_Hotel = stoi(num);
                num = "";
                steps++;
            }
        }
        else if(!is_this_char_an_ineger(data[j]))
        {
            cout << "ERROR : file has problems in part two (Distances)" << '\n';
            cout << "DESCRIPTION : there are non-integer characters in a line of this part" << '\n';
            exit(-1);
        }
        else
            num += data[j];
    }
    if (num != "") // distance initialized here
    {
        if (stoi(num) < 0)
        {
            cout << "ERROR : file has problems in part two (Distances)" << '\n';
            cout << "DESCRIPTION : Hotels number and Distances should be positive" << '\n';
            exit(-1);
        }
        else
            TravelDistance[start_Station][find_hotelOeder_in_itsStation(start_Hotel)][find_hotelOeder_in_itsStation(end_Hotel)] = stoi(num);
    }
    
}
void modify_Costs (string data)
{
    unsigned long int lenght = data.length();
    string num;
    int hotelNumber = Hotels + 1;
    if(data[0] == ' ')
    {
        cout << "ERROR : file has problems in last part" << '\n';
        cout << "DESCRIPTION : Cost of Hotels starts with space" << '\n';
        exit(-1);
    }
    if(data[lenght - 1] == ' ')
    {
        cout << "ERROR : file has problems in last part" << '\n';
        cout << "DESCRIPTION : Cost of Hotels ends with space" << '\n';
        exit(-1);
    }
    for (int j = 0 ; j < lenght ; j++)
    {
        if (data[j] == ' ')
        {
            if (data[j - 1] == ' ')
            {
                cout << "ERROR : file has problems in last part" << '\n';
                cout << "DESCRIPTION : Cost of Hotels has a sequence (more than one) of spaces" << '\n';
                exit(-1);
            }
            else
            {
                hotelNumber = stoi(num);
                if (hotelNumber < 1)
                {
                    cout << "ERROR : file has problems in last part" << '\n';
                    cout << "DESCRIPTION : Cost of Hotels should greater than 1" << '\n';
                    exit(-1);
                }
                num = "";
            }
        }
        else if(!is_this_char_an_ineger(data[j]))
        {
            cout << "ERROR : file has problems in last part" << '\n';
            cout << "DESCRIPTION : there are non-integer characters in file" << '\n';
            exit(-1);
        }
        else //data[j] is integer
            num += data[j];
    }
    if (hotelNumber > Hotels) // means : hotelNumber did not assignd in above for
    {
        cout << "ERROR : file has problems in last part" << '\n';
        cout << "DESCRIPTION : HotelNumber should mention" << '\n';
        exit(-1);
    }
    if (num != "") // num has some characters
    {
        if (stoi(num) < 1)
        {
            cout << "ERROR : file has problems in last part" << '\n';
            cout << "DESCRIPTION : Cost of Hotels should greater than 0" << '\n';
            exit(-1);
        }
        else
            HotelCost[hotelNumber] = stoi(num);
    }
    else
    {
        cout << "ERROR : file has problems in last part" << '\n';
        cout << "DESCRIPTION : Cost of Hotels should mention" << '\n';
        exit(-1);
    }
}
inline void modify_Hotels (string data)
{
    unsigned long int lenght = data.length();
    if (lenght < (2*(Stations - 1)-1))
    {
        cout << "ERROR : file has problems in line 2" << '\n';
        cout << "DESCRIPTION : there are not enough hotels in file" << '\n';
        exit(-1);
    }
    string num;
    int i = 0;
    int h = 1;
    int integer_num;
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
                integer_num = stoi(num);
                StationHotelsInfo[i] = new int[integer_num + 1];
                StationHotelsInfo[i][0] = integer_num;
                for (int k = 1 ; k <= integer_num ; k++,h++)
                    StationHotelsInfo[i][k] = h;
                Hotels+=integer_num;
                if (integer_num < 1)
                {
                    cout << "ERROR : file has problems in line 2" << '\n';
                    cout << "DESCRIPTION : Hotels number should greater than 0" << '\n';
                    exit(-1);
                }
                num = "";
            }
        }
        else if(!is_this_char_an_ineger(data[j]))
        {
            cout << "ERROR : file has problems in line 2" << '\n';
            cout << "DESCRIPTION : there are non-integer characters in file" << '\n';
            exit(-1);
        }
        else
            num += data[j];
    }
    if (num != "")
    {
        if (stoi(num) < 1)
        {
            cout << "ERROR : file has problems in line 2" << '\n';
            cout << "DESCRIPTION : Hotels number should greater than 0" << '\n';
            exit(-1);
        }
        else
        {
            integer_num = stoi(num);
            StationHotelsInfo[Stations - 1] = new int[integer_num + 1];
            StationHotelsInfo[Stations - 1][0] = integer_num;
            for (int k = 1 ; k <= integer_num ; k++,h++)
                StationHotelsInfo[Stations - 1][k] = h;
            Hotels+=integer_num;
        }
    }
}
void readfile()
{
    string data;
    fstream file;
    bool BADFILE = false;
    file.open("in2.txt");
    for (int i = 1 ; i < 3 ; i++)
    {
        getline(file,data,'\n');
        if (data == "" || data == " ")
        {
            BADFILE = true;
            break;
        }
        if (i == 1)
        {
            Stations = stoi(data) + 1;
            TravelDistance = new int**[Stations];
            BestHotelUntilStation = new int[Stations];
            BestHotelUntilStation[0] = 0; // we reached on station 0 and hotel 0
            CheapestCostUntilStation = new int[Stations];
            CheapestCostUntilStation[0] = 0; // CheapestCost until reached on station 0 is 0
            there_is_a_way_to_station = new bool[Stations]; // Default value = 0 (false)
            there_is_a_way_to_station[0] = true;
            pervious_hotel = new int[Hotels];
            pervious_hotel[0] = 0;
            for (int i = 1 ; i < Hotels ; i++)
                pervious_hotel[i] = -1;
            StationHotelsInfo = new int*[Stations];
            StationHotelsInfo[0] = new int[2];
            StationHotelsInfo[0][0] = 1;
            StationHotelsInfo[0][1] = 0;
        }
        else if (i == 2)
            modify_Hotels(data);
    }
    if (BADFILE)
    {
        cout << "ERROR : file has problems" << '\n';
        cout << "DESCRIPTION : there are BadLines in file" << '\n';
        exit(-1);
    }
    modify_Distance_array();
    CheapestCostUntilHotel = new int[Hotels];
    CheapestCostUntilHotel[0] = 0;
    bool emptyLine = false;
    while (getline(file,data,'\n'))
    {
        if (data == "")
        {
            emptyLine = true;
            break;
        }
        modify_Distances(data);
    }
    if (!emptyLine)
    {
        cout << "ERROR : file has problems between part two and last part" << '\n';
        cout << "DESCRIPTION : emptyLine as division between these parts did not mention" << '\n';
        exit(-1);
    }
    int exepted_hotels = Hotels - 1;
    HotelCost = new int [Hotels];
    while (getline(file,data,'\n'))
    {
        modify_Costs(data);
        exepted_hotels--;
    }
    if (exepted_hotels != 0)
    {
        cout << "ERROR : file has problems in last part" << '\n';
        cout << "DESCRIPTION : HotelsNumber in line 2 is not equal to HotelsNumber in last part" << '\n';
        exit(-1);
    }
    file.close();
}
int main()
{
    readfile();
    print_BestWays();
    return 0;
}

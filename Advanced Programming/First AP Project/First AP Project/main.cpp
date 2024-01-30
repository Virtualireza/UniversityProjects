#include <iostream>
#include <fstream>
#define size 15
#define PersonalCosts 30
using namespace std;
int Count_Admin()
{
    fstream users;
    users.open("users.txt");
    string firstname, lastname, studentnumber, password, type;
    int counter = 0;
    while (getline(users, firstname, '\t'))
    {
        getline(users, lastname, '\t');
        getline(users, studentnumber, '\t');
        getline(users, password, '\t');
        getline(users, type, '\n');
        if (type == "1")
            counter++;
    }
    users.close();
    return counter;
}
//control Firstname & Lastname to just include letters
bool Check_Correct_letter(string name)
{
    for (int i = 0; name[i] != '\0'; i++)
    {
        if (name[0]==' ')
            return false;
        if (((name[i] < 'A' || name[i] > 'z') || (name[i] < 'a' && name[i] >'Z')) && (name[i] != ' '))
            return false;
    }
    return true;
}
bool check_correct_char_for_studentnumber(string studentnumber)
{
    int n = studentnumber.length();
    for (int i = 0; i < n; i++)
        if (studentnumber[i] < '0' || studentnumber[i] > '9')
            return false;
    return true;
}
bool Check_similiar_Studentnumber(string studentnumber)
{
    fstream users;
    users.open("users.txt");
    string firstname, lastname, stunum, password, type;
    bool a = false;
    while (getline(users, firstname, '\t'))
    {
        getline(users, lastname, '\t');
        getline(users, stunum, '\t');
        getline(users, password, '\t');
        getline(users, type, '\n');
        if (stunum == studentnumber)
        {
            a = true;
            break;
        }
    }
    users.close();
    if (a == true)
        return true; // they are similiar
    return false; // they are unsimiliar
}
int number_of_users()
{
    fstream users;
    users.open("users.txt");
    int counter = 0;
    string a, b, c, d, e;
    while (getline(users, a, '\t'))
    {
        getline(users, b, '\t');
        getline(users, c, '\t');
        getline(users, d, '\t');
        getline(users, e, '\n');
        counter++;
    }
    users.close();
    return counter;
}
bool IsHeThat(string studentnumber)
{
    fstream users;
    users.open("users.txt");
    string f, l, s, p, t;
    while (getline(users, f, '\t'))
    {
        getline(users, l, '\t');
        getline(users, s, '\t');
        getline(users, p, '\t');
        getline(users, t, '\n');
        if (s == studentnumber)
            break;
    }
    int choice;
    cout << "Did You Mean " << f << " " << l << " ? " << endl;
    cout << "1.Yes\t2.No\n";
    cin >> choice;
    while (choice < 1 || choice > 2)
    {
        cout << "Incorrect input ." << endl;
        cout << "1.Yes\t2.No\n";
        cin >> choice;
    }
    users.close();
    if (choice == 1)
        return true;
    return false;
}
string SignUp_FirstName()
{
    cin.ignore();
    string Firstname;
    cout << "Enter First Name : ";
    getline(cin, Firstname, '\n');
    while (Check_Correct_letter(Firstname) == false)
    {
        cout << "Please just enter letter " << endl;
        cout << "Enter First Name : ";
        getline(cin, Firstname, '\n');
    }
    return Firstname;
}
string SignUp_LastName()
{
    string Lastname;
    cout << "Enter Last Name : ";
    getline(cin, Lastname, '\n');
    while (Check_Correct_letter(Lastname) == false)
    {
        cout << "Please just enter letter " << endl;
        cout << "Enter Last Name : ";
        getline(cin, Lastname, '\n');
    }
    return Lastname;
}
string SignUp_StudentNumber()
{
    string studentnumber;
    cout << "Enter StudentNumber : ";
    getline(cin, studentnumber, '\n');
    //khat zir tamam shart haye lazem yek studentnumber baraye sabtname ra darad .
    while (true)
    {
        bool a = check_correct_char_for_studentnumber(studentnumber);
        bool c = Check_similiar_Studentnumber(studentnumber);
        if (a && c == false)
            break;
        else
        {
            cout << "StudentNumber Should Be  Unsimiliar and digit .\n Try Again : ";
            getline(cin, studentnumber, '\n');
        }
    }
    return studentnumber;
}
bool use_space(string password)
{
    int n = password.length();
    for (int i = 0; i < n; i++)
        if (password[i] == ' ')
            return false;
    return true;
}
string SignUp_Password()
{
    string password;
    cout << "Enter Your Password : ";
    getline(cin, password, '\n');
    while (use_space(password) == false)
    {
        cout << "You Should Not Use SPACE CHARACTER" << endl;
        cout << "Enter Another password : ";
        getline(cin, password, '\n');
    }
    return password;
}
bool SignUp_Admin()
{
    cout << "There Is NO Admin . We need an admin to run programme ." << endl;
    cout << "1.Signup As an Admin" << endl;
    cout << "2.CloseProgramme" << endl;
    int choice;
    cin >> choice;
    while (choice < 1 || choice>2)
    {
        cout << "Incorrect Input ." << endl;
        cout << "1.Signup As an Admin" << endl;
        cout << "2.CloseProgramme" << endl;
        cin >> choice;
    }
    if (choice == 2)
        return false;
    if (choice)
    {
        fstream users;
        users.open("users.txt");
        users << SignUp_FirstName() << "\t";
        users << SignUp_LastName() << "\t";
        users << SignUp_StudentNumber() << "\t";
        users << SignUp_Password() << "\t";
        users << "1" << endl;
        cout << "Sign up was succesful ." << endl;
        users.close();
    }
    return true;
}
struct Pub
{
    string stunum[size];
    string date[size];
    string detail[size];
    string price[size];
};
struct Per
{
    string paid[size];
    string paid_for[size];
    string date[size];
    string detail[size];
    string price[size];
};
void Update_Files_With_New_Info_stunum(string Oldstunum, string Newstunum)
{
    Pub Public;
    fstream Personal_File, Public_File;
    int i = 0;
    int n = number_of_users();
    Public_File.open("PublicCosts.txt");
    while (getline(Public_File, Public.stunum[i], '\t'))
    {
        getline(Public_File, Public.date[i], '\t');
        getline(Public_File, Public.detail[i], '\t');
        getline(Public_File, Public.price[i], '\n');
        if (Public.stunum[i] == Oldstunum)
            Public.stunum[i] = Newstunum;
        i++;
    }
    Public_File.close();
    Public_File.open("PublicCosts.txt");
    for (int a = 0; a < n; a++)
    {
        Public_File << Public.stunum[a] << "\t";
        Public_File << Public.date[a] << "\t";
        Public_File << Public.detail[a] << "\t";
        Public_File << Public.price[a] << "\n";
    }
    Public_File.close();
    Per Personal;
    int j = 0;
    Personal_File.open("PersonalCosts.txt");
    while (getline(Personal_File, Personal.paid[j], '\t'))
    {
        getline(Personal_File, Personal.paid_for[j], '\t');
        getline(Personal_File, Personal.date[j], '\t');
        getline(Personal_File, Personal.detail[j], '\t');
        getline(Personal_File, Personal.price[j], '\n');
        if (Personal.paid[j] == Oldstunum)
            Personal.paid[j] = Newstunum;
        if (Personal.paid_for[j] == Oldstunum)
            Personal.paid_for[j] = Newstunum;
        j++;
    }
    Personal_File.close();
    Personal_File.open("PersonalCosts.txt");
    for (int a = 0; a < n; a++)
    {
        Personal_File << Personal.paid[a] << "\t";
        Personal_File << Personal.paid_for[a] << "\t";
        Personal_File << Personal.date[a] << "\t";
        Personal_File << Personal.detail[a] << "\t";
        Personal_File << Personal.price[a] << "\n";
    }
    Personal_File.close();
}
void Edit_Info(string Inputstunum)
{
    string firstname[size],lastname[size],stunum[size],password[size],type[size];
    fstream users;
    string Oldstunum;
    users.open("users.txt");
    for (int i = 0; getline(users, firstname[i], '\t'); i++)
    {
        getline(users,lastname[i], '\t');
        getline(users,stunum[i], '\t');
        getline(users,password[i], '\t');
        getline(users,type[i], '\n');
        while (Inputstunum == stunum[i])
        {
            cout << "Which one do you want to change ? " << endl;
            cout << "1.Firstname" << "\tCurrent FirstName :" << firstname[i] << endl;
            cout << "2.Lastname" << "\tCurrent LastName :" << lastname[i] << endl;
            cout << "3.StudentNumber" << "\tCurrent StudentNumber :" << stunum[i] << endl;
            cout << "4.Password" << "\tCurrent Password :" << password[i] << endl;
            cout << "5.Exit & Save Changes" << endl;
            int choice;
            cin >> choice;
            if (choice == 5)
                break;
            Oldstunum = stunum[i];
            cin.ignore();
            switch (choice)
            {
            case 1: firstname[i] = SignUp_FirstName(); break;
            case 2: lastname[i] = SignUp_LastName(); break;
            case 3: stunum[i] = SignUp_StudentNumber(); Update_Files_With_New_Info_stunum(Oldstunum, stunum[i]); break;
            case 4: password[i] = SignUp_Password(); break;
            default: cout << "Try again with correct input ." << endl; break;
            }
        }
    }
    users.close();
    fstream user;
    user.open("users.txt");
    int n = number_of_users();
    for (int i = 0; i < n; i++)
    {
        user << firstname[i] << "\t";
        user << lastname[i] << "\t";
        user << stunum[i] << "\t";
        user << password[i] << "\t";
        user << type[i] << endl;
    }
    user.close();
}
long int MajmooMakharejOmoomiMan(string StudentNumber)
{
    fstream Public;
    Public.open("PublicCosts.txt");
    string stu_num, date, detail, string_price;
    long long int Your_Public_Cost = 0;
    while (getline(Public, stu_num, '\t'))
    {
        getline(Public, date, '\t');
        getline(Public, detail, '\t');
        getline(Public, string_price, '\n');
        int int_price = stoi(string_price);
        if (StudentNumber == stu_num)
            Your_Public_Cost = int_price + Your_Public_Cost;
    }
    Public.close();
    return Your_Public_Cost;
}
string Add_Detail()
{
    cout << "Add Detail : ";
    string detail;
    cin.ignore();
    getline(cin, detail, '\n');
    return detail;
}
int check_day(int month)
{
    cout << "Add Day : ";
    int day;
    cin >> day;
    while (true)
    {
        if ((day > 0 && day < 32 && month < 7) || (day > 0 && day < 31 && month>7))
            break;
        else
        {
            cout << "Enter Right Number" << endl;
            cin >> day;
        }
    }
    return day;
}
string Add_Date()
{
    string date;
    int year, month;
    cout << "Add Year : ";
    cin >> year;
    while (year < 1300 || year > 1410)
    {
        cout << "Enter Right Number :";
        cin >> year;
    }
    cout << "Add Month : ";
    cin >> month;
    while (month < 1 || month > 12)
    {
        cout << "Enter Right Number :";
        cin >> month;
    }
    int day = check_day(month);
    date = to_string(year) + '.' + to_string(month) + '.' + to_string(day);
    return date;
}
long int Add_Price()
{
    cout << "Add Price : ";
    long int price;
    cin >> price;
    while (price < 0)
    {
        cout << "Incorrect input . ";
        cout << "Add Price : ";
        cin >> price;
    }
    return price;
}
bool is_admin(string studentnumber)
{
    fstream users;
    users.open("users.txt");
    string firstname, lastname, stunum, password, type;
    while (getline(users, firstname, '\t'))
    {
        getline(users, lastname, '\t');
        getline(users, stunum, '\t');
        getline(users, password, '\t');
        getline(users, type, '\n');
        if (studentnumber == stunum && type == "1")
        {
            users.close();
            return true;
        }
    }
    users.close();
    return false;
}
void Add_Admin(string studentnumber)
{
    fstream users;
    users.open("users.txt");
    int i = 0;
    int n = number_of_users();
    string f,l;
    string firstname[size], lastname[size], stunum[size], password[size], type[size];
    while (getline(users, firstname[i], '\t'))
    {
        getline(users, lastname[i], '\t');
        getline(users, stunum[i], '\t');
        getline(users, password[i], '\t');
        getline(users, type[i], '\n');
        if (studentnumber == stunum[i])
        {
            type[i] = "1";
            f = firstname[i];
            l = lastname [i];
        }
        i++;
    }
    users.close();
    ofstream user;
    user.open("users.txt");
    user.close();
    users.open("users.txt", ios::app);
    for (int i = 0; i < n; i++)
    {
        users << firstname[i] << "\t";
        users << lastname[i] << "\t";
        users << stunum[i] << "\t";
        users << password[i] << "\t";
        users << type[i] << "\n";
    }
    users.close();
    cout << f << " " << l << " " << "Becamed Admin ." << endl;
}
void RemoveAdmin(string studentnumber)
{
    fstream users;
    users.open("users.txt");
    int i = 0;
    int n = number_of_users();
    string f,l;
    string firstname[size], lastname[size], temp_studentsumber[size], password[size], type[size];
    while (getline(users, firstname[i], '\t'))
    {
        getline(users, lastname[i], '\t');
        getline(users, temp_studentsumber[i], '\t');
        getline(users, password[i], '\t');
        getline(users, type[i], '\n');
        if (studentnumber == temp_studentsumber[i])
        {
            type[i] = "0";
            f = firstname[i];
            l = lastname[i];
        }
        i++;
    }
    users.close();
    ofstream user;
    user.open("users.txt");
    user.close();
    users.open("users.txt", ios::app);
    for (int i = 0; i < n; i++)
    {
        users << firstname[i] << "\t";
        users << lastname[i] << "\t";
        users << temp_studentsumber[i] << "\t";
        users << password[i] << "\t";
        users << type[i] << "\n";
    }
    users.close();
    cout << f << " " << l << " " << "Removed From Admin ." << endl;
}
long long int MajmooMakharejOmoomi()
{
    fstream Public;
    Public.open("PublicCosts.txt");
    string stu_num, date, detail, string_price;
    long int int_Price = 0;
    long long int price = 0;
    while (getline(Public, stu_num, '\t'))
    {
        getline(Public, date, '\t');
        getline(Public, detail, '\t');
        getline(Public, string_price, '\n');
        int_Price = stoi(string_price);
        price = int_Price + price;
    }
    Public.close();
    return price;
}
long long int MajmooMakharejVaBedehkariOmoomiMan(string Studentnumber)
{
    return -1 * (MajmooMakharejOmoomi() / number_of_users() - MajmooMakharejOmoomiMan(Studentnumber));
}
//MajmooSahmKhosoosi ba ehtesab barayand talabkariha va bedehkariha
//tasviye hesabha ra ham shamel mishavad
long long int MajmooMakharejKhosoosiMan(string Studentnumber)
{
    fstream Personal;
    Personal.open("PersonalCosts.txt");
    long int int_Price;
    long long int price = 0;
    string paid, paid_for, date, detail, string_price;
    while (getline(Personal, paid, '\t'))
    {
        getline(Personal, paid_for, '\t');
        getline(Personal, date, '\t');
        getline(Personal, detail, '\t');
        getline(Personal, string_price, '\n');
        int_Price = stoi(string_price);
        if (Studentnumber == paid)
            price += int_Price;
        if (Studentnumber == paid_for)
            price -= int_Price ;
    }
    //      قیمت خرج کننده (طلبکار) + است و قیمت بدهکار - است   .
    Personal.close();
    return price;
}
// نمایش دهنده وضعیت کلی کاربر است که بفهمد در مجموع چقدر طلبکار و چقدر بدهکار است
void Vaziat_Koli_Hesab(string Studentnumber)
{
    long long int a = 0, b = 0;
    a = MajmooMakharejVaBedehkariOmoomiMan(Studentnumber);
    b = MajmooMakharejKhosoosiMan(Studentnumber);
    if (a + b < 0)
    {
        cout << "Shoma Dar Majmoo , Bedehkar Hastid . " << endl;
        cout << "Bedehi Shoma Barabar Ast Ba : " << -1 * (a + b) << endl;
    }
    if (a + b == 0)
        cout << "Majmoo Bedehi & Talab Hesab Shoma Barabar Ast ... " << endl;
    if (a + b > 0)
    {
        cout << "Shoma Dar Majmoo , Talabkar Hastid . " << endl;
        cout << "Talab Shoma Barabar Ast Ba : " << a + b << endl;
    }
}
void List_of_My_Personal_Costs(string Studentnumber)
{
    fstream Personal;
    Personal.open("PersonalCosts.txt");
    long long int int_price = 0;
    int counter = 0;
    string paid, paid_for, date, detail, string_price;
    while (getline(Personal, paid, '\t'))
    {
        getline(Personal, paid_for, '\t');
        getline(Personal, date, '\t');
        getline(Personal, detail, '\t');
        getline(Personal, string_price, '\n');
        int_price = stoi(string_price);
        if (Studentnumber == paid || Studentnumber == paid_for)
        {
            counter++;
            cout << counter << " : " << paid << "\t" << paid_for << "\t" << date << "\t" << detail << "\t" << int_price << endl;
        }
    }
    Personal.close();
}
int tedad_Makharej_Personal(string Studentnumber)
{
    fstream Personal;
    Personal.open("PersonalCosts.txt");
    int counter = 0;
    string paid, paid_for, date, detail, string_price;
    while (getline(Personal, paid, '\t'))
    {
        getline(Personal, paid_for, '\t');
        getline(Personal, date, '\t');
        getline(Personal, detail, '\t');
        getline(Personal, string_price, '\n');
        if (Studentnumber == paid || Studentnumber == paid_for)
            counter++;
    }
    Personal.close();
    return counter;
}
/*void Edit_Public_Date(string studentnumber)
{

}
void Edit_Public_Price(string studentnumber)
{

}
void Edit_Public_Detail(string studentnumber)
{

}*/
void Edit_Personal_Date(string studentnumber)
{
    List_of_My_Personal_Costs(studentnumber);
    cout << "\n\n To Edit Date Of Each  one , Enter defined Number ." << endl;
    cout << "Your Number : " << endl;
    int choice, n;
    n = tedad_Makharej_Personal(studentnumber);
    cin >> choice;
    while (choice > n || choice < 0)
    {
        cout << "Incorrect input . Your Number : " << endl;
        cin >> choice;
    }
    fstream Personal;
    Personal.open("PersonalCosts.txt");
    string paid[PersonalCosts], paid_for[PersonalCosts], date[PersonalCosts], detail[PersonalCosts], string_price[PersonalCosts];
    int j = 0;
    while (getline(Personal, paid[j], '\t'))
    {
        getline(Personal, paid_for[j], '\t');
        getline(Personal, date[j], '\t');
        getline(Personal, detail[j], '\t');
        getline(Personal, string_price[j], '\n');
        for (int i = 0; i <= n; i++)
        {
            if (studentnumber == paid[j] || studentnumber == paid_for[j])
                i++;
            if (i == choice)
            {
                date[j] = Add_Date();
                cout << "That ocuarred succesfully . New date :  " << date[j] << endl;
                break;
            }
        }
        j++;
    }
    Personal.close();
    Personal.open("PersonalCosts.txt");
    for (int a = 0; a < n; a++)
    {
        Personal << paid[a] << "\t";
        Personal << paid_for[a] << "\t";
        Personal << date[a] << "\t";
        Personal << detail[a] << "\t";
        Personal << string_price[a] << "\n";
    }
    Personal.close();
}
void Edit_Personal_Price(string studentnumber)
{
    List_of_My_Personal_Costs(studentnumber);
    cout << "\n\n To Edit Date Of Each  one , Enter defined Number ." << endl;
    cout << "Your Number : " << endl;
    int choice, n;
    n = tedad_Makharej_Personal(studentnumber);
    cin >> choice;
    while (choice > n || choice < 0)
    {
        cout << "Incorrect input . Your Number : " << endl;
        cin >> choice;
    }
    fstream Personal;
    Personal.open("PersonalCosts.txt");
    string paid[PersonalCosts], paid_for[PersonalCosts], date[PersonalCosts], detail[PersonalCosts], string_price[PersonalCosts];
    int j = 0;
    while (getline(Personal, paid[j], '\t'))
    {
        getline(Personal, paid_for[j], '\t');
        getline(Personal, date[j], '\t');
        getline(Personal, detail[j], '\t');
        getline(Personal, string_price[j], '\n');
        for (int i = 0; i <= n; i++)
        {
            if (studentnumber == paid[j] || studentnumber == paid_for[j])
                i++;
            if (i == choice)
            {
                string_price[j] = Add_Price();
                cout << "That ocuarred succesfully . New Price :  " << string_price[j] << endl;
                break;
            }
        }
        j++;
    }
    Personal.close();
    Personal.open("PersonalCosts.txt");
    for (int a = 0; a < n; a++)
    {
        Personal << paid[a] << "\t";
        Personal << paid_for[a] << "\t";
        Personal << date[a] << "\t";
        Personal << detail[a] << "\t";
        Personal << string_price[a] << "\n";
    }
    Personal.close();
}
void Edit_Personal_Detail(string studentnumber)
{
    List_of_My_Personal_Costs(studentnumber);
    cout << "\n\n To Edit Date Of Each  one , Enter defined Number ." << endl;
    cout << "Your Number : " << endl;
    int choice, n;
    n = tedad_Makharej_Personal(studentnumber);
    cin >> choice;
    while (choice > n || choice < 0)
    {
        cout << "Incorrect input . Your Number : " << endl;
        cin >> choice;
    }
    fstream Personal;
    Personal.open("PersonalCosts.txt");
    string paid[PersonalCosts], paid_for[PersonalCosts], date[PersonalCosts], detail[PersonalCosts], string_price[PersonalCosts];
    int j = 0;
    while (getline(Personal, paid[j], '\t'))
    {
        getline(Personal, paid_for[j], '\t');
        getline(Personal, date[j], '\t');
        getline(Personal, detail[j], '\t');
        getline(Personal, string_price[j], '\n');
        for (int i = 0; i <= n; i++)
        {
            if (studentnumber == paid[j] || studentnumber == paid_for[j])
                i++;
            if (i == choice)
            {
                detail[j] = Add_Detail();
                cout << "That ocuarred succesfully . New Detail :  " << detail[j] << endl;
                break;
            }
        }
        j++;
    }
    Personal.close();
    Personal.open("PersonalCosts.txt");
    for (int a = 0; a < n; a++)
    {
        Personal << paid[a] << "\t";
        Personal << paid_for[a] << "\t";
        Personal << date[a] << "\t";
        Personal << detail[a] << "\t";
        Personal << string_price[a] << "\n";
    }
    Personal.close();

}
void List_Of_Public_Cost()
{
    cout << "The List of Public Costs is : " << endl;
    string stu_num, date, detail, string_price;
    long long int int_price;
    fstream Public;
    Public.open("PublicCosts.txt");
    while (getline(Public, stu_num, '\t'))
    {
        getline(Public, date, '\t');
        getline(Public, detail, '\t');
        getline(Public, string_price, '\n');
        int_price = stoi(string_price);
        cout << stu_num << "\t" << date << "\t" << detail << "\t" << int_price << endl;
    }
    cout << "Overall Public Cost : " << MajmooMakharejOmoomi() << endl;
    Public.close();
}
void TasviyeHesab(string MyStudentNumber)
{
    string firstname, lastname, password, type, HisStudentNumber;
    string paid, paid_for, date, detail, string_price;
    fstream users, Personal;
    long long int MyBedehi, MyTalab, int_price;
    // حالا شماره دانشجویی شخصی که میخواهد بدهی خود را پرداخت کند در MyStudentNumber ذخیره شده است .
    users.open("users.txt");
    while (getline(users, firstname, '\t'))
    {
        getline(users, lastname, '\t');
        getline(users, HisStudentNumber, '\t');
        getline(users, password, '\t');
        getline(users, type, '\n');
        Personal.open("PersonalCosts.txt");
        MyTalab = MajmooMakharejOmoomiMan(MyStudentNumber) / number_of_users();
        MyBedehi = MajmooMakharejOmoomiMan(HisStudentNumber) / number_of_users();
        while (getline(Personal, paid, '\t'))
        {
            getline(Personal, paid_for, '\t');
            getline(Personal, date, '\t');
            getline(Personal, detail, '\t');
            getline(Personal, string_price, '\n');
            int_price = stoi(string_price);
            if (paid == MyStudentNumber && paid_for == HisStudentNumber)
                MyTalab = int_price + MyTalab;
            if (paid == HisStudentNumber && paid_for == MyStudentNumber)
                MyBedehi = int_price + MyBedehi;
        }
        //  اگر طرف طلبکار بود آن وقت :
        if (MyBedehi > MyTalab)
            cout << "StudentNumber : " << HisStudentNumber << "\t" << "Bedehi Shoma Be Ishan  : " << MyBedehi - MyTalab << endl;
        // اگر با طرف حسابی تسویه داشت  :
        if (MyBedehi == MyTalab)
            cout << "Hesab Shoma Ba " << HisStudentNumber << "Saf Ast " << endl;
        // اگر طرف بدهکار بود ، اسمش وارد بدهکاران شود :
        if (MyBedehi < MyTalab)
            cout << "StudentNumber : " << HisStudentNumber << "\t" << "Talab Shoma Be Ishan : " << MyTalab - MyBedehi << endl;
        Personal.close();
    }
    users.close();
    cout << "ATTENTION !!! Baraye Pardakht Bedehi , Be Menuye Add Personal Costs Beravid" << endl;
}
bool CheckHesabMaliUserToRemove(string MyStudentNumber)
{
    string firstname, lastname, password, type, HisStudentNumber;
    string paid, paid_for, date, detail, string_price;
    fstream users, Personal;
    long long int MyBedehi, MyTalab, int_price;
    users.open("users.txt");
    while (getline(users, firstname, '\t'))
    {
        getline(users, lastname, '\t');
        getline(users, HisStudentNumber, '\t');
        getline(users, password, '\t');
        getline(users, type, '\n');
        Personal.open("PersonalCosts.txt");
        MyTalab = MajmooMakharejOmoomiMan(MyStudentNumber) / number_of_users();
        MyBedehi = MajmooMakharejOmoomiMan(HisStudentNumber) / number_of_users();
        while (getline(Personal, paid, '\t'))
        {
            getline(Personal, paid_for, '\t');
            getline(Personal, date, '\t');
            getline(Personal, detail, '\t');
            getline(Personal, string_price, '\n');
            int_price = stoi(string_price);
            if (paid == MyStudentNumber && paid_for == HisStudentNumber)
                MyTalab = int_price + MyTalab;
            if (paid == HisStudentNumber && paid_for == MyStudentNumber)
                MyBedehi = int_price + MyBedehi;
        }
        if (MyBedehi > MyTalab || MyBedehi < MyTalab)
        {
            Personal.close();
            users.close();
            return false;
        }
    }
    return true;
}
void RemoveUser(string studentnumber)
{
    while (true)
    {
        bool a = check_correct_char_for_studentnumber(studentnumber);
        bool c = Check_similiar_Studentnumber(studentnumber);
        if (a && c)
        {
            if (IsHeThat(studentnumber))
                break;
        }
        else
        {
            cout << "StudentNumber Should Be similiar and digit .\n Try Again : ";
            cout << "Try Again : ";
            getline(cin, studentnumber, '\n');
        }
    }
    if (CheckHesabMaliUserToRemove(studentnumber))
    {
        fstream users;
        users.open("users.txt");
        string firstname[size], lastname[size], stunum[size], password[size], type[size];
        string f, l, s, p, t;
        int n = number_of_users();
        int i = 0;
        while (getline(users, f, '\t'))
        {
            getline(users, l, '\t');
            getline(users, s, '\t');
            getline(users, p, '\t');
            getline(users, t, '\n');
            if (studentnumber != s)
            {
                firstname[i] = f;
                lastname[i] = l;
                stunum[i] = s;
                password[i] = p;
                type[i] = t;
                i++;
            }
        }
        users.close();
        users.open("users.txt");
        //n - 1 : because one user deleted
        for (int j = 0; j < n - 1; j++)
        {
            users << firstname[j] << "\t";
            users << lastname[j] << "\t";
            users << stunum[j] << "\t";
            users << password[j] << "\t";
            users << type[j] << endl;
        }
        users.close();
        cout << "User Removed ." << endl;
    }
    else
    {
        cout << "Dar Hal Hazer Emkan Remove Vojood Nadarad" << endl;
        cout << "Hesab User , Tasviye nist ." << endl;
    }
}
void Calculate_My_Public_Costs(string studentnumber)
{
    long int Mypubliccost = MajmooMakharejOmoomiMan(studentnumber);
    cout << "Overall Public Cost : " << MajmooMakharejOmoomi() << endl;
    cout << "Your Piece : " << MajmooMakharejOmoomi() / number_of_users() << endl;
    cout << "You Cost : " << Mypubliccost << endl;
    cout << "You Should  Pay : " << (MajmooMakharejOmoomi() / number_of_users()) - Mypubliccost << endl;
    cout << "If You Want to Pay : Go To Add Personal Cost OR Add Public Costs " << endl;
    cout << "If You Want to Earn : Tell Another to Go To Add Personal Cost " << endl;
}
void Add_Public_Cost(string studentnumber)
{
    cout << "Number of Users is : " << number_of_users() << endl;
    fstream Public;
    Public.open("PublicCosts.txt", ios::app);
    Public << studentnumber << "\t" << Add_Date() << "\t" << Add_Detail() << "\t" << Add_Price() << endl;
    Public.close();
}
void Public_Menu(string studentnumber)
{
    cout << "1.Add Public Cost" << endl;
    cout << "2.Calculate My Public Costs" << endl;
    cout << "3.List of Public Costs" << endl;
    int Choice;
    cin >> Choice;
    switch (Choice)
    {
    case 1: Add_Public_Cost(studentnumber); break;
    case 2: Calculate_My_Public_Costs(studentnumber); break;
    case 3: List_Of_Public_Cost(); break;
    default: cout << "Bad Input" << endl ; break;
    }
}
void Add_Personal_Cost_You_Paid(string studentnumber)
{
    string paid_for;
    fstream Personal;
    Personal.open("PersonalCosts.txt", ios::app);
    cout << "Enter StudentNumber (Who You Paid For Him) : ";
    cin.ignore();
    getline(cin, paid_for, '\n');
    //khat zir tamam shart haye lazem yek studentnumber baraye sabtname ra darad .
    while (true)
    {
        bool a = check_correct_char_for_studentnumber(paid_for);
        bool c = Check_similiar_Studentnumber(paid_for);
        if (a && c)
        {
            if (IsHeThat(paid_for))
                break;
        }
        else
        {
            cout << "StudentNumber Should Be similiar and digit .\n Try Again : ";
            getline(cin, paid_for, '\n');
        }
    }
    Personal << studentnumber << "\t";
    Personal << paid_for << "\t";
    Personal << Add_Date() << "\t";
    Personal << Add_Detail() << "\t";
    Personal << Add_Price() << "\n";
    Personal.close();
}
void Add_Personal_Cost_Paid_For_You(string studentnumber)
{
    string paid;
    fstream Personal;
    Personal.open("PersonalCosts.txt", ios::app);
    cout << "Enter StudentNumber (Who Paid) : ";
    cin.ignore();
    getline(cin, paid, '\n');
    //khat zir tamam shart haye lazem yek studentnumber baraye sabtname ra darad .
    while (true)
    {
        bool a = check_correct_char_for_studentnumber(paid);
        bool c = Check_similiar_Studentnumber(paid);
        if (a && c)
        {
            if (IsHeThat(paid))
                break;
        }
        else
        {
            cout << "StudentNumber Should Be similiar and digit .\n Try Again : ";
            getline(cin, paid, '\n');
        }
    }
    Personal << paid << "\t";
    Personal << studentnumber << "\t";
    Personal << Add_Date() << "\t";
    Personal << Add_Detail() << "\t";
    Personal << Add_Price() << "\n";
    Personal.close();
}
void Add_Personal_Cost_menu(string studentnumber)
{
    cout << "1.Add Personal Cost (You Paid)" << endl;
    cout << "2.Add Personal Cost (Paid For You)" << endl;
    int Choice;
    cin >> Choice;
    switch (Choice)
    {
    case 1: Add_Personal_Cost_You_Paid(studentnumber); break;
    case 2: Add_Personal_Cost_Paid_For_You(studentnumber); break;
    default: cout << "Bad Input" << endl ; break;
    }
}
void Calculate_My_Personal_Costs_menu(string studentnumber)
{
    cout << "Your Personal Costs Are : ";
    cout << MajmooMakharejKhosoosiMan(studentnumber) << endl;
}
/*void edit_Mypersonal (string studentnumber)
{
    cout << "1.Edit Personal Date" << endl;
    cout << "2.Edit Personal Detail" << endl;
    cout << "3.Edit Personal Price" << endl;
    int Choice;
    cin >> Choice;
    switch (Choice)
    {
    case 1: Edit_Personal_Date(studentnumber); break;
    case 2: Edit_Personal_Detail(studentnumber); break;
    case 3: Edit_Personal_Price(studentnumber);  break;
    default: cout << "Enter Right Number : "; cin >> Choice; break;
    }
}*/
void Personal_Menu(string studentnumber)
{
    cout << "Tedad Makharej Khosoosi Shoma Ta Be Inja : ";
    cout << tedad_Makharej_Personal(studentnumber) << endl;
    cout << "1.Add Personal Cost" << endl;
    cout << "2.Calculate My Personal Costs" << endl;
    cout << "3.List of My Personal Costs" << endl;
    //cout << "4.Edit Personal Files" << endl;
    int Choice;
    cin >> Choice;
    switch (Choice)
    {
    case 1: Add_Personal_Cost_menu(studentnumber); break;
    case 2: Calculate_My_Personal_Costs_menu(studentnumber); break;
    case 3: List_of_My_Personal_Costs(studentnumber);  break;
    // case 4: edit_Mypersonal(studentnumber); break;
    default: cout << "Bad Input" << endl ; break;
    }
}
void Edit_Personal_Info_Menu(string Studentnumber)
{
    Edit_Info(Studentnumber);
}
void Vaziat_Koli_Hesab_VA_Tasviye_Hesab_Menu(string Studentnumber)
{
    Vaziat_Koli_Hesab(Studentnumber);
    cout << "\n\n";
    TasviyeHesab(Studentnumber);
    //majmoo bedehkari be har karbar = مقادیر دستی که به کاربری داده شده + خرج های عمومی که او انجام داده تقسیم بر تعداد کاربران
    //majmoo talabkari az har karbar = مقادیر دستی که از کاربری گرفته شده + خرج های عمومی که من انجام دادم تقسیم بر تعداد کاربران
}
bool Login (string &ID)
{
    fstream users;
    string f, l, s, p, t;
    string StudentNumber;
    string password;
    bool check = false ;
    while (true)
    {
        cout << "Enter Your StudentNumber : ";
        getline(cin, StudentNumber, '\n');
        cout << "Enter Your Password : ";
        getline(cin,password, '\n');
        users.open("users.txt");
        while (getline(users, f, '\t'))
        {
            getline(users, l, '\t');
            getline(users, s, '\t');
            getline(users, p, '\t');
            getline(users, t, '\n');
            if (password == p && StudentNumber == s && t == "0")
            {
                cout << "Welcome !" << endl << "You Loged In As : " << f << "\t" << l << endl;
                check = true;
                break;
                }
            if (password == p && StudentNumber == s && t == "1")
            {
                cout << "Welcome !" << endl << "You Loged In As : " << f << "\t" << l << endl;
                check = true;
                break;
            }
        }
        users.close();
        if (check)
            break;
        else
            cout << "There Is No user With this Info" << "\tTry Again" << endl ;
    }
    ID = StudentNumber ;
    if (t=="1")
        return true;
    return false;
}
//USER MENU **
void User_Login_Menu(string Studentnumber)
{
    while (true)
    {
        cout << "1.Public Costs" << endl;
        cout << "2.Personal Costs" << endl;
        cout << "3.Edit Personal Info" << endl;
        cout << "4.Vaziat Koli Hesab & Tasviye Hesab" << endl;
        cout << "5.Log Out & Exit" << endl;
        int Choice;
        cin >> Choice;
        if (Choice==5)
            break;
        switch (Choice)
        {
            case 1: Public_Menu(Studentnumber); break;
            case 2: Personal_Menu(Studentnumber); break;
            case 3: Edit_Personal_Info_Menu(Studentnumber);  break;
            case 4: Vaziat_Koli_Hesab_VA_Tasviye_Hesab_Menu(Studentnumber);  break;
            default: cout << "Try again ... "; break;
        }
    }
}
void Add_Admin_Menu()
{
    string studentnumber;
    cout << "Enter StudentNumber That You Want To Become Admin : ";
    cin.ignore();
    getline(cin, studentnumber, '\n');
    while (true)
    {
        bool a = check_correct_char_for_studentnumber(studentnumber);
        bool c = Check_similiar_Studentnumber(studentnumber);
        bool d = is_admin(studentnumber);
        if (a && c && d == false)
        {
            Add_Admin(studentnumber);
            break;
        }
        else
        {
            cout << "StudentNumber Should Not Be Admin , similiar and digit .\n";
            cout << "Try Again : ";
            getline(cin, studentnumber, '\n');
        }
    }
}
void Remove_Admin_Menu()
{
    string studentnumber;
    cout << "Enter StudentNumber That You Want To Remove From Admining : ";
    cin.ignore();
    getline(cin, studentnumber, '\n');
    while (true)
    {
        cin.ignore();
        bool a = check_correct_char_for_studentnumber(studentnumber);
        bool c = Check_similiar_Studentnumber(studentnumber);
        bool d = is_admin(studentnumber);
        int  e = Count_Admin();
        if (a && c && d && e > 1)
        {
            RemoveAdmin(studentnumber);
            break;
        }
        else
        {
            if (e == 1)
            {
                cout << "Shoma Tanha Admin Hastid." << endl;
                cout << "Ghabl Az darkhast remove admin , admin digari ezafe konid ";
                cout << "Ta barname bedoon admin nabashad" << endl;
            }
            cout << "StudentNumber Should Be Admin , similiar and digit .\n";
            cout << "Try Again . ";
            getline(cin, studentnumber, '\n');
        }
    }
}
void Add_User_Menu()
{
    fstream users;
    int type = 0;
    users.open("users.txt", ios::app);
    users << SignUp_FirstName() << "\t";
    users << SignUp_LastName() << "\t";
    users << SignUp_StudentNumber() << "\t";
    users << SignUp_Password() << "\t";
    users << type << endl;
    users.close();
    cout << "Sign Up was Sucsesful ." << endl;
}
void Remove_User_Menu()
{
    string studentnumber;
    cout << "Enter StudentNumber That You Want To Remove From Users : ";
    cin.ignore();
    getline(cin, studentnumber, '\n');
    RemoveUser(studentnumber);
}
void Users_Info_Menu()
{
    fstream users;
    users.open("users.txt");
    cout << "Number Of Users  : " << number_of_users() << endl;
    string firstname, lastname, studentsumber, password, type;
    while (getline(users, firstname, '\t'))
    {
        getline(users, lastname, '\t');
        getline(users, studentsumber, '\t');
        getline(users, password, '\t');
        getline(users, type, '\n');
        cout << "Firstname : " << firstname << "\t";
        cout << "Lastname : " << lastname << "\t";
        cout << "Studentnumber : " << studentsumber << "\t";
        cout << "Password : " << password << "\t";
        cout << "Type : " << type << endl;
    }
    users.close();
  //cout << "ATTENTION : For Change Sth , Enter 1 At this Level To View User's Info That You Want , ";
  //cout << "Then Go to Login Menu And Enter User's Password to Login & Change " << endl;
}
void Ediit_Personal_Info_Menu(string studentnumber)
{
    Edit_Info(studentnumber);
}
//ADMIN MENU**
void Admin_Login_Menu(string Studentnumber)
{
    while (true)
    {
        cout << "1.Add Admin" << endl;
        cout << "2.Remove Admin" << endl;
        cout << "3.Add User" << endl;
        cout << "4.Remove User" << endl;
        cout << "5.User's Info" << endl;
        cout << "6.Edit Personal Info" << endl;
        cout << "7.Public Costs" << endl;
        cout << "8.Personal Costs" << endl;
        cout << "9.Vaziat Koli Hesab & Tasviye Hesab" << endl;
        cout << "10.Log Out & Exit" << endl;
        int Choice;
        cin >> Choice;
        if (Choice==10)
            break;
        switch (Choice)
        {
            case 1: Add_Admin_Menu();  break;
            case 2: Remove_Admin_Menu();  break;
            case 3: Add_User_Menu();  break;
            case 4: Remove_User_Menu();  break;
            case 5: Users_Info_Menu();  break;
            case 6: Ediit_Personal_Info_Menu(Studentnumber);  break;
            case 7: Public_Menu(Studentnumber); break;
            case 8: Personal_Menu(Studentnumber); break;
            case 9: Vaziat_Koli_Hesab_VA_Tasviye_Hesab_Menu(Studentnumber);  break;
            default: cout << "Enter Right Number : "; break;
        }
    }
}
int main()
{
    string ID ;
    if (Count_Admin() == 0)
        if (SignUp_Admin() == false)
                return 0;
    bool choice = Login(ID);
    if (choice)
        Admin_Login_Menu(ID);
    else
        User_Login_Menu(ID);
}

#include <iostream>
using namespace std;
class complex
{
private:
    double real , imaginity;
public:
    void set_value()
    {
        cout << "Enter real part : " ;
        cin >> real;
        cout << "Enter imaginity part : " ;
        cin >> imaginity;
    };
    complex () //sazande
    {
        real = 0;
        imaginity = 0;
    };
    static string sum (complex first , complex second)
    {
        double real_result , imaginity_result;
        string result;
        real_result = first.real + second.real ;
        imaginity_result = first.imaginity + second.imaginity;
        result = to_string(real_result) + " " + "+" + " " + to_string(imaginity_result) + " i";
        return result;
    };
    static string Mines (complex first , complex second)
    {
        double real_result , imaginity_result;
        string result;
        real_result = first.real - second.real ;
        imaginity_result = first.imaginity - second.imaginity;
        result = to_string(real_result) + " " + "+" + " " + to_string(imaginity_result) + " i";
        return result;
    };
    static string Multiplication (complex first , complex second)
    {
        double real_result , imaginity_result;
        string result;
        real_result = (first.real * second.real) - (first.imaginity * second.imaginity);
        imaginity_result = (first.real * second.imaginity) + (second.real * first.imaginity);
        result = to_string(real_result) + " " + "+" + " " + to_string(imaginity_result) + " i";
        return result;
    };
    static string Division (complex first , complex second)
    {
        double real_result , imaginity_result;
        string result;
        result = "division is not calculatable ( = division by zero )";
        short choice = 0;
        while (second.real == 0 || second.imaginity == 0)
        {
            cout << "ATTENTION !!! real and imaginity part of second number should NOT be ZERO" << endl;
            cout << "Do you want to change ?\n anynumber.Yes 2.No" << endl;
            cin >> choice;
            if (choice == 2)
                break;
            cout << "Enter real part of second complex number : " ;
            cin >> second.real;
            cout << endl;
            cout << "Enter imaginity part of second complex number : " ;
            cin >> second.imaginity;
            cout << endl;
        }
        if (choice == 2)
            return result;
        real_result = ((first.real * second.real) + (first.imaginity * second.imaginity)) / ((second.real * second.real) + (second.imaginity * second.imaginity));
        imaginity_result = ((second.real * first.imaginity) - (first.real * second.imaginity)) / ((second.real * second.real) + (second.imaginity * second.imaginity));
        result = to_string(real_result) + " " + "+" + " " + to_string(imaginity_result) + " i";
        return result;
    };
    static void chap (complex first , complex second)
    {
        cout << "First numnber \n--------------\n";
        first.set_value();
        cout << endl;
        cout << "Second numnber \n--------------\n";
        second.set_value();
        cout << endl << endl;
        cout << "Summation : " << complex::sum(first,second) << endl;
        cout << "Mines : " << Mines(first,second) << endl;
        cout << "Multiplication : " << Multiplication(first,second) << endl;
        cout << "Division : " << Division(first,second) << endl;
    };
};
int main()
{
    complex f , s;
    cout << complex::sum(f,s);
}


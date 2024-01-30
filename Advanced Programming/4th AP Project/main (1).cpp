#include <iostream>
using namespace std;
class complex
{
private:
    double real, img;

public:
    void set_value()
    {
        cout << "Enter real part : ";
        cin >> real;
        cout << "Enter imaginity part : ";
        cin >> img;
    };
    complex() // sazande
    {
        real = 0;
        img = 0;
    };
    static string sum(complex first, complex second)
    {
        double real_result, imaginity_result;
        string result;
        real_result = first.real + second.real;
        imaginity_result = first.img + second.img;
        result = to_string(real_result) + " " + "+" + " " + to_string(imaginity_result) + " i";
        return result;
    };
    static string Mines(complex first, complex second)
    {
        double real_result, imaginity_result;
        string result;
        real_result = first.real - second.real;
        imaginity_result = first.img - second.img;
        result = to_string(real_result) + " " + "+" + " " + to_string(imaginity_result) + " i";
        return result;
    };
    static string Multiplication(complex first, complex second)
    {
        double real_result, imaginity_result;
        string result;
        real_result = (first.real * second.real) - (first.img * second.img);
        imaginity_result = (first.real * second.img) + (second.real * first.img);
        result = to_string(real_result) + " " + "+" + " " + to_string(imaginity_result) + " i";
        return result;
    };
    static string Division(complex first, complex second)
    {
        double real_result, imaginity_result;
        string result;
        result = "division is not calculatable ( = division by zero )";
        short choice = 0;
        while (second.real == 0 || second.img == 0)
        {
            cout << "ATTENTION !!! real and imaginity part of second number should NOT be ZERO" << endl;
            cout << "Do you want to change ?\n anynumber.Yes 2.No" << endl;
            cin >> choice;
            if (choice == 2)
                break;
            cout << "Enter real part of second complex number : ";
            cin >> second.real;
            cout << endl;
            cout << "Enter imaginity part of second complex number : ";
            cin >> second.img;
            cout << endl;
        }
        if (choice == 2)
            return result;
        real_result = ((first.real * second.real) + (first.img * second.img)) / ((second.real * second.real) + (second.img * second.img));
        imaginity_result = ((second.real * first.img) - (first.real * second.img)) / ((second.real * second.real) + (second.img * second.img));
        result = to_string(real_result) + " " + "+" + " " + to_string(imaginity_result) + " i";
        return result;
    };
    static void chap(complex first, complex second)
    {
        cout << "First numnber \n--------------\n";
        first.set_value();
        cout << endl;
        cout << "Second numnber \n--------------\n";
        second.set_value();
        cout << endl
             << endl;
        cout << "Summation : " << complex::sum(first, second) << endl;
        cout << "Mines : " << Mines(first, second) << endl;
        cout << "Multiplication : " << Multiplication(first, second) << endl;
        cout << "Division : " << Division(first, second) << endl;
    };
};
int main()
{
    complex f, s;
    cout << complex::sum(f, s);
}

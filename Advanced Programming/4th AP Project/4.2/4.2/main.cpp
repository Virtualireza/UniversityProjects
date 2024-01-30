#include <iostream>
using namespace std;
class rational
{
    friend class complex;
private:
    int numerator , denominator;
public :
    rational ()
    {
        numerator = 0;
        denominator = 1;
    }
    void set_value()
    {
        cout << "Enter numerator : " ;
        cin >> numerator;
        cout << "Enter denominator : " ;
        cin >> denominator;
        while (denominator == 0)
        {
            cout << "Denominator should NOT be zero " << endl;
            cout << "Try again : " << endl;
            cin >> denominator;
        }
        rational number;
        number.numerator = numerator;
        number.denominator = denominator;
        number = simplify(number);
        numerator = number.numerator;
        denominator = number.denominator;
    };
    static rational simplify (rational n)
    {
        int maximum = max(n.numerator,n.denominator);
        int minimum = min(n.numerator,n.denominator);
        short help = 1; // max == numerator
        if (maximum == n.denominator)
            help = 2; // max == denominator
        if ((maximum % minimum == 0))
        {
            maximum = maximum / minimum;
            minimum = 1;
        }
        for (int i = (minimum / 2) ; i > 1 ; i--)
        if (maximum % i == 0 && minimum % i == 0)
            {
                maximum = maximum / i;
                minimum = minimum / i;
                break;
            }
        if (help == 2)
        {
            n.denominator = maximum;
            n.numerator = minimum;
        }
        else
        {
            n.numerator = maximum;
            n.denominator = minimum;
        }
        return n;
    };
    static bool is_equal (rational first , rational second)
    {
        if ((first.numerator == second.numerator) && (first.denominator == second.denominator) && (first.numerator == second.numerator) && (first.denominator == second.denominator))
            return true;
        return false;
    };
};
class complex
{
private:
    rational real , imaginity;
public:
    void set_value()
    {
        cout << "Real part" << endl;
        real.set_value();
        cout << "Imaginity part" << endl;
        imaginity.set_value();
    };
    static string sum (complex first , complex second)
    {
        rational real_result , imaginity_result;
        string result;
        rational real_max , real_min;
        real_max.denominator = max(first.real.denominator,second.real.denominator);
        real_min.denominator = min(first.real.denominator,second.real.denominator);
        real_max.numerator = max(first.real.numerator,second.real.numerator);
        real_min.numerator = min(first.real.numerator,second.real.numerator);
        if (real_max.denominator % real_min.denominator == 0)
        {
            int dif = real_max.denominator / real_max.denominator;
            real_result.numerator = real_min.numerator * dif + real_max.numerator;
            real_result.denominator = real_max.denominator;
        }
        else
        {
            real_result.numerator = (first.real.numerator * second.real.denominator) + (second.real.numerator * first.real.denominator);
            real_result.denominator = first.real.denominator * second.real.denominator;
        }
        rational imaginity_max , imaginity_min;
        imaginity_max.denominator = max(first.imaginity.denominator,second.imaginity.denominator);
        imaginity_min.denominator = min(first.imaginity.denominator,second.imaginity.denominator);
        imaginity_max.numerator = max(first.imaginity.numerator,first.imaginity.numerator);
        imaginity_min.numerator = min(first.imaginity.numerator,first.imaginity.numerator);
        if (imaginity_max.denominator % imaginity_min.denominator == 0)
        {
            int dif = imaginity_max.denominator / imaginity_min.denominator;
            imaginity_result.numerator = imaginity_min.numerator * dif + imaginity_max.numerator;
            imaginity_result.denominator = imaginity_max.denominator;
        }
        else
        {
            imaginity_result.numerator = (first.imaginity.numerator * second.imaginity.denominator) + (second.imaginity.numerator * first.imaginity.denominator);
            imaginity_result.denominator = first.imaginity.denominator * second.imaginity.denominator;
        }
        rational::simplify(real_result);
        rational::simplify(imaginity_result);
        result = to_string(real_result.numerator) + " / " + to_string(real_result.denominator) + " + " + to_string(imaginity_result.numerator) + " / " + to_string(imaginity_result.denominator) + " i";
        return result;
    };
    static string Mines (complex first , complex second)
    {
        rational real_result , imaginity_result;
        string result;
        rational real_max , real_min;
        real_max.denominator = max(first.real.denominator,second.real.denominator);
        real_min.denominator = min(first.real.denominator,second.real.denominator);
        real_max.numerator = max(first.real.numerator,second.real.numerator);
        real_min.numerator = min(first.real.numerator,second.real.numerator);
        if (real_max.denominator % real_min.denominator == 0)
        {
            int dif = real_max.denominator / real_max.denominator;
            real_result.numerator = real_min.numerator * dif - real_max.numerator;
            real_result.denominator = real_max.denominator;
        }
        else
        {
            real_result.numerator = (first.real.numerator * second.real.denominator) - (second.real.numerator * first.real.denominator);
            real_result.denominator = first.real.denominator * second.real.denominator;
        }
        rational imaginity_max , imaginity_min;
        imaginity_max.denominator = max(first.imaginity.denominator,second.imaginity.denominator);
        imaginity_min.denominator = min(first.imaginity.denominator,second.imaginity.denominator);
        imaginity_max.numerator = max(first.imaginity.numerator,first.imaginity.numerator);
        imaginity_min.numerator = min(first.imaginity.numerator,first.imaginity.numerator);
        if (imaginity_max.denominator % imaginity_min.denominator == 0)
        {
            int dif = imaginity_max.denominator / imaginity_min.denominator;
            imaginity_result.numerator = imaginity_min.numerator * dif - imaginity_max.numerator;
            imaginity_result.denominator = imaginity_max.denominator;
        }
        else
        {
            imaginity_result.numerator = (first.imaginity.numerator * second.imaginity.denominator) - (second.imaginity.numerator * first.imaginity.denominator);
            imaginity_result.denominator = first.imaginity.denominator * second.imaginity.denominator;
        }
        rational::simplify(real_result);
        rational::simplify(imaginity_result);
        result = to_string(real_result.numerator) + " / " + to_string(real_result.denominator) + " + " + to_string(imaginity_result.numerator) + " / " + to_string(imaginity_result.denominator) + " i";
        return result;
    };
    static string Multiplication (complex first , complex second)
    {
        rational real_result , imaginity_result;
        string result;
        real_result.numerator = first.real.numerator * second.real.numerator;
        real_result.denominator = first.real.denominator * second.real.denominator;
        imaginity_result.numerator = first.imaginity.numerator * second.imaginity.numerator;
        imaginity_result.denominator = first.imaginity.denominator * second.imaginity.denominator;
        rational::simplify(real_result);
        rational::simplify(imaginity_result);
        result = to_string(real_result.numerator) + " / " + to_string(real_result.denominator) + " + " + to_string(imaginity_result.numerator) + " / " + to_string(imaginity_result.denominator) + " i";
        return result;
    };
    static string Division (complex first , complex second)
    {
        rational real_result , imaginity_result;
        string result;
        real_result.numerator = first.real.numerator * second.real.denominator;
        real_result.denominator = first.real.denominator * second.real.numerator;
        imaginity_result.numerator = first.imaginity.numerator * second.imaginity.denominator;
        imaginity_result.denominator = first.imaginity.denominator * second.imaginity.numerator;
        rational::simplify(real_result);
        rational::simplify(imaginity_result);
        result = to_string(real_result.numerator) + " / " + to_string(real_result.denominator) + " + " + to_string(imaginity_result.numerator) + " / " + to_string(imaginity_result.denominator) + " i";
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
    static bool is_equal (complex first , complex second)
    {
        if (rational::is_equal(first.real,second.real) && rational::is_equal(first.imaginity,second.imaginity))
            return true;
        return false;
    };
};
int main ()
{
    complex f , s ;
    complex::chap(f,s);
    cout << endl << complex::is_equal(f,s) << endl;
}

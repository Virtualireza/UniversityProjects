#include <iostream>
using namespace std;
class Rational
{
    friend class complex;
    friend class myset;
private:
    int a, b;
public :
    void set_a(int a=0)
    {
        this -> a = a;
    };
    void set_b (int b=1)
    {
        if (b != 0)
            this -> b = b;
    };
    Rational simplify (Rational n)
    {
        int maximum = max(n.a,n.b);
        int minimum = min(n.a,n.b);
        short help = 1; // max == a
        if (maximum == n.b)
            help = 2; // max == b
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
            n.b = maximum;
            n.a = minimum;
        }
        else
        {
            n.a = maximum;
            n.b = minimum;
        }
        return n;
    };
    static bool is_equal (Rational r1, Rational r2)
    {
        if ((r1.a == r2.a) && (r1.b == r2.b))
            return true;
        return false;
    };
};
class Complex
{
    friend class myset;
private:
    Rational real, img;
public:
    void set_real (Rational r)
    {
        real.set_a(r.a);
        real.set_b(r.b);
    };
    void set_img (Rational i)
    {
        img.set_a(i.a);
        img.set_b(i.b);
    };
    void set_complex (complex c)
    {
        real.set_real(c.real);
        img.set_img(c.img);
    };
    string print_complex_number (complex number)
    {
        string result;
        result = to_string(number.real.a) + " / " + to_string(number.real.b) + " + " + to_string(number.img.a) + " / " + to_string(number.img.b) + " i";
        return result;
    };
    static complex sum (complex first, complex second)
    {
        complex result;
        Rational real_max, real_min;
        real_max.b = max(first.real.b,second.real.b);
        real_min.b = min(first.real.b,second.real.b);
        real_max.a = max(first.real.a,second.real.a);
        real_min.a = min(first.real.a,second.real.a);
        if (real_max.b % real_min.b == 0)
        {
            int dif = real_max.b / real_max.b;
            result.real.a = real_min.a * dif + real_max.a;
            result.real.b = real_max.b;
        }
        else
        {
            result.real.a = (first.real.a * second.real.b) + (second.real.a * first.real.b);
            result.real.b = first.real.b * second.real.b;
        }
        Rational img_max, img_min;
        img_max.b = max(first.img.b,second.img.b);
        img_min.b = min(first.img.b,second.img.b);
        img_max.a = max(first.img.a,first.img.a);
        img_min.a = min(first.img.a,first.img.a);
        if (img_max.b % img_min.b == 0)
        {
            int dif = img_max.b / img_min.b;
            result.img.a = img_min.a * dif + img_max.a;
            result.img.b = img_max.b;
        }
        else
        {
            result.img.a = (first.img.a * second.img.b) + (second.img.a * first.img.b);
            result.img.b = first.img.b * second.img.b;
        }
        Rational::simplify(result.real);
        Rational::simplify(result.img);
        return result;
    };
    static complex Mines (complex first, complex second)
    {
        complex result;
        Rational real_max, real_min;
        real_max.b = max(first.real.b,second.real.b);
        real_min.b = min(first.real.b,second.real.b);
        real_max.a = max(first.real.a,second.real.a);
        real_min.a = min(first.real.a,second.real.a);
        if (real_max.b % real_min.b == 0)
        {
            int dif = real_max.b / real_max.b;
            result.real.a = real_min.a * dif - real_max.a;
            result.real.b = real_max.b;
        }
        else
        {
            result.real.a = (first.real.a * second.real.b) - (second.real.a * first.real.b);
            result.real.b = first.real.b * second.real.b;
        }
        Rational img_max, img_min;
        img_max.b = max(first.img.b,second.img.b);
        img_min.b = min(first.img.b,second.img.b);
        img_max.a = max(first.img.a,first.img.a);
        img_min.a = min(first.img.a,first.img.a);
        if (img_max.b % img_min.b == 0)
        {
            int dif = img_max.b / img_min.b;
            result.img.a = img_min.a * dif - img_max.a;
            result.img.b = img_max.b;
        }
        else
        {
            result.img.a = (first.img.a * second.img.b) - (second.img.a * first.img.b);
            result.img.b = first.img.b * second.img.b;
        }
        Rational::simplify(result.real);
        Rational::simplify(result.img);
        return result;
    };
    static complex Multiplication (complex first, complex second)
    {
        complex result;
        result.real.a = first.real.a * second.real.a;
        result.real.b = first.real.b * second.real.b;
        result.img.a = first.img.a * second.img.a;
        result.img.b = first.img.b * second.img.b;
        Rational::simplify(result.real);
        Rational::simplify(result.img);
        return complex;
    };
    static complex Division (complex first, complex second)
    {
        complex result;
        result.real.a = first.real.a * second.real.b;
        result.real.b = first.real.b * second.real.a;
        result.img.a = first.img.a * second.img.b;
        result.img.b = first.img.b * second.img.a;
        Rational::simplify(result.real);
        Rational::simplify(result.img);
        return complex;
    };
    static void print (complex first, complex second)
    {
        complex result;
        //cout << "First numnber \n--------------\n";
        // cout << endl;
        // cout << "Second numnber \n--------------\n";
        cout << "Summation : " ;
        result = sum(first,second);
        print_complex_number(result);
        cout << endl << "Mines : " ;
        result = Mines(first,second);
        print_complex_number(result);
        cout << endl << "Multiplication : " ;
        result = Multiplication(first,second);
        print_complex_number(result);
        cout << endl << "Division : " ;
        result = Division(first,second);
        print_complex_number(result);
        cout << endl;
    };
    static bool is_equal (complex first, complex second)
    {
        if (Rational::is_equal(first.real,second.real) && Rational::is_equal(first.img,second.img))
            return true;
        return false;
    };
};
struct node
{
    complex data;
    node * next;
};
class Myset
{
private :
    node * first;
public :
    myset()
    {
        first = NULL;
    };
    bool is_empety ()
    {
        if (first == NULL)
            return true;
        return false;
    };
    void print () //DONED
    {
        node * current = first;
        cout << " { ";
        while (current)
        {
            cout << complex::print_complex_number(current -> data) ;
            current = current -> next;
            if (current)
                cout << " , ";
        }
        cout << "} " << endl;
    };
    bool have_the_set_this_data (complex data)  //DONED
    {
        if (how_many_repeat_a_data(data) == 1)
            return true;
        return false;
    };
    int how_many_repeat_a_data (complex data)  //DONED
    {
        int n = 0;
        node * current = first;
        while (current)
        {
            if (complex::is_equal(current -> data,data))
                n++;
            current = current -> next;
        }
        return n;
    };
    void add (complex value) //DONED
    {
        if (!have_the_set_this_data(value))
        {
            while (current -> next != NULL)
            {
                current = current -> next;
            }
            current -> next = new node;
            current = current -> next;
            current -> data = value;
            current -> next = NULL;
        }
    };
    node * delete (complex value) //DONED
    {
        node * current = first;
        if (!have_the_set_this_data(value))
        {
            cout << "There is no equal value " << endl;
            return first;
        }
        if (complex::is_equal(current -> data,value) && (current == first))
        {
            //avali
            first = first -> next;
            delete current;
            return first;
        }
        while (true)
        {
            if (complex::is_equal(current -> next -> data,value) && (current->next == NULL))
            {
                //akahri
                node * p = current -> next;
                current -> next = NULL;
                delete p;
                return first;
            }
            if (complex::is_equal(current -> next -> data,value))
            {
                //vasati
                node * p = current -> next;
                current -> next = current -> next -> next;
                delete p;
                return first;
            }
            current = current -> next;
        }
    }
};
complex Sum_of_set () //DONED
{
    node * current = first;
    complex sum;//check to be zero
    while (current)
    {
        sum = complex::sum(current -> data,sum);
        current = current -> next;
    }
    return sum;
};
void Emptize_set () //DONED
{
    if (is_empety(set))
        cout << "Set is empty" << endl;
    else
    {
        node * current = set.first;
        node * next_node_addre;
        while (current)
        {
            next_node_addre = current -> next;
            delete current;
            current = next_node_addre;
        }
    }
};
static Myset Union (myset set_1, myset set_2)  //DONED
{
    Myset result;
    node * current = set_1.first;
    while (current)
    {
        cout << complex::print_complex_number(current -> data) << " , ";
        if (!have_the_set_this_data(set_2,current -> data))
            cout << complex::print_complex_number(current -> data) << " , ";
        current = current -> next;
    }
};
static Myset Intersection (myset set_1, myset set_2)  //DONED
{
    node * current = set_1.first;
    while (current)
    {
        if (have_the_set_this_data(set_2,current -> data))
            cout << complex::print_complex_number(current -> data) << " , ";
        current = current -> next;
    }
};
static Myset Difference (myset set_1, myset set_2)  //DONED
{
    node * current = set_1.first;
    while (current)
    {
        if (!have_the_set_this_data(set_2,current -> data))
            cout << complex::print_complex_number(current -> data) << " , ";
        current = current -> next;
    }
};
bool is_equal (myset set_1, myset set_2)  //DONED
{
    node * current = set_2.first;
    while (current)
    {
        if (!have_the_set_this_data(set_1,current -> data))
            return false;
        current = current -> next;
    }
    return true;
};
};
void options ()
{
    cout << "1.View second set\n";
    cout << "2.Add member to first set\n";
    cout << "3.Add member to second set\n";
    cout << "4.Delete member from first set\n";
    cout << "5.Delete member from second set\n";
    cout << "6.Sum of first set's numbers\n";
    cout << "7.Sum of second set's numbers\n";
    cout << "8.Emptize first set\n";
    cout << "9.Emptize second set\n";
    cout << "10.Union of sets\n";
    cout << "11.Intersection of sets\n";
    cout << "12.Difference of sets\n";
    cout << "13.Close programme\n";
    cout << "14.View first set\n\n";
    cout << "Your choose : ";
};
void ui(myset set_1, myset set_2)
{
    while (true)
    {
        Myset result;
        short choice;
        options();
        cin >> choice;
        cout << endl;
        while (choice < 0 || choice > 14)
        {
            cout << "\nWrong input ... Try again : ";
            cin >> choice;
        }
        if (choice == 13)
            break;
        system ("cls");
        switch (choice)
        {
        case 14 :
            set_1.print( );
            break;
        case 1 :
            set_2.print( );
            break;
        case 2 :
            set_1.add( );
            break;
        case 3 :
            set_2.add( );
            break;
        case 4 :
            set_1.delete( );
            break;
        case 5 :
            set_2.delete( );
            break;
        case 6 :
            Complex::print_complex_number(set_1.Sum_of_set( ));
            break;
        case 7 :
            Complex::print_complex_number(set_2.Sum_of_set( ))
            break;
        case 8 :
            set_1.Emptize_set( );
            break;
        case 9 :
            set_2.Emptize_set( );
            break;
        case 10 :
            result = Myset::Union(set_1,set_2);
            Myset::print(result);
            break;
        case 11 :
            result = Myset::Intersection(set_1,set_2);
            Myset::print(result);
            break;
        case 12 :
            result = Myset::Difference(set_1,set_2);
            Myset::print(result);
            break;
        }
        cout << endl;
    }
};
int main()
{
    Myset s1,s2;
    ui(s1,s2);
}

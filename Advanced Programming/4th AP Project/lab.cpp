#include <iostream>
using namespace std;
class rational
{
    friend class complex;
private:
    int a, b;
public:
    rational(int a=0,int b=1)
    {
       set_a(a);
       set_b(b);
    };
    void set(int a, int b)
    {
       set_a(a);
       set_b(b);
    };
    static rational simplify(rational n)
    {
        int maximum = max(n.a, n.b);
        int minimum = min(n.a, n.b);
        short help = 1; // max == a
        if (maximum == n.b)
            help = 2; // max == b
        if ((maximum % minimum == 0))
        {
            maximum = maximum / minimum;
            minimum = 1;
        }
        for (int i = (minimum / 2); i > 1; i--)
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
    static bool is_equal(rational first, rational second)
    {
        if ((first.a == second.a) && (first.b == second.b) && (first.a == second.a) && (first.b == second.b))
            return true;
        return false;
    };
};
class complex
{
    friend class myset;
private:
    rational real, imaginity;
public:
    complex()
    {
        real.a = 0;
        real.b = 1;
        imaginity.a = 0;
        imaginity.b = 1;
    };
    void set_value()
    {
        cout << "Real part" << endl;
        real.set_value();
        cout << "Imaginity part" << endl;
        imaginity.set_value();
    };
    static string print_complex_number(complex number)
    {
        string result;
        result = to_string(number.real.a) + " / " + to_string(number.real.b) + " + " + to_string(number.imaginity.a) + " / " + to_string(number.imaginity.b) + " i";
        return result;
    };
    static complex return_sum(complex first, complex second)
    {
        complex result;
        rational real_max, real_min;
        real_max.b = max(first.real.b, second.real.b);
        real_min.b = min(first.real.b, second.real.b);
        real_max.a = max(first.real.a, second.real.a);
        real_min.a = min(first.real.a, second.real.a);
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
        rational imaginity_max, imaginity_min;
        imaginity_max.b = max(first.imaginity.b, second.imaginity.b);
        imaginity_min.b = min(first.imaginity.b, second.imaginity.b);
        imaginity_max.a = max(first.imaginity.a, first.imaginity.a);
        imaginity_min.a = min(first.imaginity.a, first.imaginity.a);
        if (imaginity_max.b % imaginity_min.b == 0)
        {
            int dif = imaginity_max.b / imaginity_min.b;
            result.imaginity.a = imaginity_min.a * dif + imaginity_max.a;
            result.imaginity.b = imaginity_max.b;
        }
        else
        {
            result.imaginity.a = (first.imaginity.a * second.imaginity.b) + (second.imaginity.a * first.imaginity.b);
            result.imaginity.b = first.imaginity.b * second.imaginity.b;
        }
        rational::simplify(result.real);
        rational::simplify(result.imaginity);
        return result;
    };
    static void sum(complex first, complex second)
    {
        complex result;
        rational real_max, real_min;
        real_max.b = max(first.real.b, second.real.b);
        real_min.b = min(first.real.b, second.real.b);
        real_max.a = max(first.real.a, second.real.a);
        real_min.a = min(first.real.a, second.real.a);
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
        rational imaginity_max, imaginity_min;
        imaginity_max.b = max(first.imaginity.b, second.imaginity.b);
        imaginity_min.b = min(first.imaginity.b, second.imaginity.b);
        imaginity_max.a = max(first.imaginity.a, first.imaginity.a);
        imaginity_min.a = min(first.imaginity.a, first.imaginity.a);
        if (imaginity_max.b % imaginity_min.b == 0)
        {
            int dif = imaginity_max.b / imaginity_min.b;
            result.imaginity.a = imaginity_min.a * dif + imaginity_max.a;
            result.imaginity.b = imaginity_max.b;
        }
        else
        {
            result.imaginity.a = (first.imaginity.a * second.imaginity.b) + (second.imaginity.a * first.imaginity.b);
            result.imaginity.b = first.imaginity.b * second.imaginity.b;
        }
        rational::simplify(result.real);
        rational::simplify(result.imaginity);
        print_complex_number(result);
    };
    static void Mines(complex first, complex second)
    {
        complex result;
        rational real_max, real_min;
        real_max.b = max(first.real.b, second.real.b);
        real_min.b = min(first.real.b, second.real.b);
        real_max.a = max(first.real.a, second.real.a);
        real_min.a = min(first.real.a, second.real.a);
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
        rational imaginity_max, imaginity_min;
        imaginity_max.b = max(first.imaginity.b, second.imaginity.b);
        imaginity_min.b = min(first.imaginity.b, second.imaginity.b);
        imaginity_max.a = max(first.imaginity.a, first.imaginity.a);
        imaginity_min.a = min(first.imaginity.a, first.imaginity.a);
        if (imaginity_max.b % imaginity_min.b == 0)
        {
            int dif = imaginity_max.b / imaginity_min.b;
            result.imaginity.a = imaginity_min.a * dif - imaginity_max.a;
            result.imaginity.b = imaginity_max.b;
        }
        else
        {
            result.imaginity.a = (first.imaginity.a * second.imaginity.b) - (second.imaginity.a * first.imaginity.b);
            result.imaginity.b = first.imaginity.b * second.imaginity.b;
        }
        rational::simplify(result.real);
        rational::simplify(result.imaginity);
        print_complex_number(result);
    };
    static void Multiplication(complex first, complex second)
    {
        complex result;
        result.real.a = first.real.a * second.real.a;
        result.real.b = first.real.b * second.real.b;
        result.imaginity.a = first.imaginity.a * second.imaginity.a;
        result.imaginity.b = first.imaginity.b * second.imaginity.b;
        rational::simplify(result.real);
        rational::simplify(result.imaginity);
        print_complex_number(result);
    };
    static void Division(complex first, complex second)
    {
        complex result;
        result.real.a = first.real.a * second.real.b;
        result.real.b = first.real.b * second.real.a;
        result.imaginity.a = first.imaginity.a * second.imaginity.b;
        result.imaginity.b = first.imaginity.b * second.imaginity.a;
        rational::simplify(result.real);
        rational::simplify(result.imaginity);
        print_complex_number(result);
    };
    static void print(complex first, complex second)
    {
        cout << "First numnber \n--------------\n";
        first.set_value();
        cout << endl;
        cout << "Second numnber \n--------------\n";
        second.set_value();
        cout << endl << endl;
        cout << "Summation : ";
        complex::sum(first, second);
        cout << endl;
        cout << "Mines : ";
        Mines(first, second);
        cout << endl;
        cout << "Multiplication : ";
        Multiplication(first, second);
        cout << endl;
        cout << "Division : ";
        Division(first, second);
        cout << endl;
    };
    static bool is_equal(complex first, complex second)
    {
        if (rational::is_equal(first.real, second.real) && rational::is_equal(first.imaginity, second.imaginity))
            return true;
        return false;
    };
};
struct node
{
    complex data;
    node * next;
};
class myset
{
private:
    node * first;
public:
    myset() //sazande
    {
        first = NULL;
    };
    bool is_empety(myset set)
    {
        if (set.first == NULL)
            return true;
        return false;
    };
    void print(myset set) //DONED
    {
        cout << " { ";
        node * current = set.first;
        while (current)
        {
            cout << complex::print_complex_number(current->data) << " , ";
            current = current->next;
        }
        cout << "} " << endl;

    };
    bool have_the_set_this_data(myset set, complex data) //DONED
    {
        if (how_many_repeat_a_data(set, data) == 1)
            return true;
        return false;
    };
    int how_many_repeat_a_data(myset set, complex data) //DONED
    {
        int n = 0;
        node * current = set.first;
        while (current)
        {
            if (complex::is_equal(current->data, data))
                n++;
            current = current->next;
        }
        return n;
    };
    complex get_value()
    {
        complex value;
        cout << "Enter value ";
        cout << endl;
        value.set_value();
        return value;
    };
    void Add_member_to_set() //DONED
    {
        complex value = get_value();
        node * current = set.first;
        if (have_the_set_this_data(set, value))
            cout << "Value is invalid ... because of similarity" << endl;
        else
        {
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = new node;
            current = current->next;
            current->data = value; //IS THAT WORKING ???????????????????????????????????????????
            current->next = NULL;
        }
    };
    void Delete_member_from_set(myset &set) //DONED
    {
        if (is_empety(set))
            cout << "Set is empty" << endl;
        else
        {
            complex value = get_value();
            node * current = set.first;
            while (true)
            {
                if (!have_the_set_this_data(set, value))
                {
                    cout << "There is no equal value " << endl;
                    break;
                }
                if (complex::is_equal(current->data, value) && (current == set.first))
                {
                    //avali
                    set.first = set.first->next;
                    delete current;
                    break;
                }
                if (complex::is_equal(current->next->data, value) && (current->next == NULL))
                {
                    //akahri
                    node * p = current->next;
                    current->next = NULL;
                    delete p;
                    break;
                }
                if (complex::is_equal(current->next->data, value))
                {
                    //vasati
                    node * p = current->next;
                    current->next = current->next->next;
                    delete p;
                    break;
                }
                current = current->next;
            }
        }
    };
    void Sum_of_set(myset set) //DONED
    {
        node * current = set.first;
        complex sum;
        if (is_empety(set))
            cout << "Set is empty" << endl;
        else
        {
            while (current)
            {
                sum = complex::return_sum(current->data, sum);
                current = current->next;
            }
            cout << "Sum : " << complex::print_complex_number(sum) << endl;
        }
    };
    void Emptize_set(myset set) //DONED
    {
        if (is_empety(set))
            cout << "Set is empty" << endl;
        else
        {
            node * current = set.first;
            node * next_node_addre;
            while (current)
            {
                next_node_addre = current->next;
                delete current;
                current = next_node_addre;
            }
        }
    };
    myset Union(myset set_1, myset set_2) //DONED
    {

        node * current = set_1.first;
        while (current)
        {
            cout << complex::print_complex_number(current->data) << " , ";
            if (!have_the_set_this_data(set_2, current->data))
                cout << complex::print_complex_number(current->data) << " , ";
            current = current->next;
        }
        cout << "} " << endl;
    }
};
void Intersection(myset set_1, myset set_2) //DONED
{
    bool check = true;
    if (is_empety(set_1))
    {
        cout << "first Set is empty" << endl;
        check = false;
    }
    if (is_empety(set_2))
    {
        cout << "Second Set is empty" << endl;
        check = false;
    }
    if (check)
    {
        cout << "Interaction : ";
        cout << " { ";
        node * current = set_1.first;
        while (current)
        {
            if (have_the_set_this_data(set_2, current->data))
                cout << complex::print_complex_number(current->data) << " , ";
            current = current->next;
        }
        cout << "} " << endl;
    }
};
void Difference(myset set_1, myset set_2) //DONED
{
    bool check = true;
    if (is_empety(set_1))
    {
        cout << "first Set is empty" << endl;
        check = false;
    }
    if (is_empety(set_2))
    {
        cout << "Second Set is empty" << endl;
        check = false;
    }
    if (check)
    {
        node * current = set_1.first;
        cout << "Difference : ";
        cout << " { ";
        while (current)
        {
            if (!have_the_set_this_data(set_2, current->data))
                cout << complex::print_complex_number(current->data) << " , ";
            current = current->next;
        }
        cout << "} ";
        cout << endl;
    }
};
bool is_equal(myset set_1, myset set_2) //DONED
{
    node * current = set_2.first;
    while (current)
    {
        if (!have_the_set_this_data(set_1, current->data))
            return false;
        current = current->next;
    }
    return true;
};
void options()
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
void UserInterface(myset set_1, myset set_2)
{
    while (true)
    {
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
        system("cls");
        switch (choice)
        {
        case 14:
            print(set_1);
            break;
        case 1:
            print(set_2);
            break;
        case 2:
            Add_member_to_set(set_1);
            break;
        case 3:
            Add_member_to_set(set_2);
            break;
        case 4:
            Delete_member_from_set(set_1);
            break;
        case 5:
            Delete_member_from_set(set_2);
            break;
        case 6:
            Sum_of_set(set_1);
            break;
        case 7:
            Sum_of_set(set_2);
            break;
        case 8:
            Emptize_set(set_1);
            break;
        case 9:
            Emptize_set(set_2);
            break;
        case 10:
            Union(set_1, set_2);
            break;
        case 11:
            Intersection(set_1, set_2);
            break;
        case 12:
            Difference(set_1, set_2);
            break;
        }
        cout << endl;
    }
};
};
int main()
{
    myset first, second;
    myset::UserInterface(first, second);
}


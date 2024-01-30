#include <iostream>
using namespace std;
class rational
{
    friend class complex;
    friend class myset;
private:
    int numerator , denominator;
public :
    rational ()
    {
        numerator = 0;
        denominator = 1;
    };
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
    friend class myset;
private:
    rational real , imaginity;
public:
    complex ()
    {
        real.numerator = 0;
        real.denominator = 1;
        imaginity.numerator = 0;
        imaginity.denominator = 1;
    }
    void set_value ()
    {
        cout << "Real part" << endl;
        real.set_value();
        cout << "Imaginity part" << endl;
        imaginity.set_value();
    };
    static string print_complex_number (complex number)
    {
        string result;
        result = to_string(number.real.numerator) + " / " + to_string(number.real.denominator) + " + " + to_string(number.imaginity.numerator) + " / " + to_string(number.imaginity.denominator) + " i";
        return result;
    };
    static complex return_sum (complex first , complex second)
    {
        complex result;
        rational real_max , real_min;
        real_max.denominator = max(first.real.denominator,second.real.denominator);
        real_min.denominator = min(first.real.denominator,second.real.denominator);
        real_max.numerator = max(first.real.numerator,second.real.numerator);
        real_min.numerator = min(first.real.numerator,second.real.numerator);
        if (real_max.denominator % real_min.denominator == 0)
        {
            int dif = real_max.denominator / real_max.denominator;
            result.real.numerator = real_min.numerator * dif + real_max.numerator;
            result.real.denominator = real_max.denominator;
        }
        else
        {
            result.real.numerator = (first.real.numerator * second.real.denominator) + (second.real.numerator * first.real.denominator);
            result.real.denominator = first.real.denominator * second.real.denominator;
        }
        rational imaginity_max , imaginity_min;
        imaginity_max.denominator = max(first.imaginity.denominator,second.imaginity.denominator);
        imaginity_min.denominator = min(first.imaginity.denominator,second.imaginity.denominator);
        imaginity_max.numerator = max(first.imaginity.numerator,first.imaginity.numerator);
        imaginity_min.numerator = min(first.imaginity.numerator,first.imaginity.numerator);
        if (imaginity_max.denominator % imaginity_min.denominator == 0)
        {
            int dif = imaginity_max.denominator / imaginity_min.denominator;
            result.imaginity.numerator = imaginity_min.numerator * dif + imaginity_max.numerator;
            result.imaginity.denominator = imaginity_max.denominator;
        }
        else
        {
            result.imaginity.numerator = (first.imaginity.numerator * second.imaginity.denominator) + (second.imaginity.numerator * first.imaginity.denominator);
            result.imaginity.denominator = first.imaginity.denominator * second.imaginity.denominator;
        }
        rational::simplify(result.real);
        rational::simplify(result.imaginity);
        return result;
    };
    static void sum (complex first , complex second)
    {
        complex result;
        rational real_max , real_min;
        real_max.denominator = max(first.real.denominator,second.real.denominator);
        real_min.denominator = min(first.real.denominator,second.real.denominator);
        real_max.numerator = max(first.real.numerator,second.real.numerator);
        real_min.numerator = min(first.real.numerator,second.real.numerator);
        if (real_max.denominator % real_min.denominator == 0)
        {
            int dif = real_max.denominator / real_max.denominator;
            result.real.numerator = real_min.numerator * dif + real_max.numerator;
            result.real.denominator = real_max.denominator;
        }
        else
        {
            result.real.numerator = (first.real.numerator * second.real.denominator) + (second.real.numerator * first.real.denominator);
            result.real.denominator = first.real.denominator * second.real.denominator;
        }
        rational imaginity_max , imaginity_min;
        imaginity_max.denominator = max(first.imaginity.denominator,second.imaginity.denominator);
        imaginity_min.denominator = min(first.imaginity.denominator,second.imaginity.denominator);
        imaginity_max.numerator = max(first.imaginity.numerator,first.imaginity.numerator);
        imaginity_min.numerator = min(first.imaginity.numerator,first.imaginity.numerator);
        if (imaginity_max.denominator % imaginity_min.denominator == 0)
        {
            int dif = imaginity_max.denominator / imaginity_min.denominator;
            result.imaginity.numerator = imaginity_min.numerator * dif + imaginity_max.numerator;
            result.imaginity.denominator = imaginity_max.denominator;
        }
        else
        {
            result.imaginity.numerator = (first.imaginity.numerator * second.imaginity.denominator) + (second.imaginity.numerator * first.imaginity.denominator);
            result.imaginity.denominator = first.imaginity.denominator * second.imaginity.denominator;
        }
        rational::simplify(result.real);
        rational::simplify(result.imaginity);
        print_complex_number(result);
    };
    static void Mines (complex first , complex second)
    {
        complex result;
        rational real_max , real_min;
        real_max.denominator = max(first.real.denominator,second.real.denominator);
        real_min.denominator = min(first.real.denominator,second.real.denominator);
        real_max.numerator = max(first.real.numerator,second.real.numerator);
        real_min.numerator = min(first.real.numerator,second.real.numerator);
        if (real_max.denominator % real_min.denominator == 0)
        {
            int dif = real_max.denominator / real_max.denominator;
            result.real.numerator = real_min.numerator * dif - real_max.numerator;
            result.real.denominator = real_max.denominator;
        }
        else
        {
            result.real.numerator = (first.real.numerator * second.real.denominator) - (second.real.numerator * first.real.denominator);
            result.real.denominator = first.real.denominator * second.real.denominator;
        }
        rational imaginity_max , imaginity_min;
        imaginity_max.denominator = max(first.imaginity.denominator,second.imaginity.denominator);
        imaginity_min.denominator = min(first.imaginity.denominator,second.imaginity.denominator);
        imaginity_max.numerator = max(first.imaginity.numerator,first.imaginity.numerator);
        imaginity_min.numerator = min(first.imaginity.numerator,first.imaginity.numerator);
        if (imaginity_max.denominator % imaginity_min.denominator == 0)
        {
            int dif = imaginity_max.denominator / imaginity_min.denominator;
            result.imaginity.numerator = imaginity_min.numerator * dif - imaginity_max.numerator;
            result.imaginity.denominator = imaginity_max.denominator;
        }
        else
        {
            result.imaginity.numerator = (first.imaginity.numerator * second.imaginity.denominator) - (second.imaginity.numerator * first.imaginity.denominator);
            result.imaginity.denominator = first.imaginity.denominator * second.imaginity.denominator;
        }
        rational::simplify(result.real);
        rational::simplify(result.imaginity);
        print_complex_number(result);
    };
    static void Multiplication (complex first , complex second)
    {
        complex result;
        result.real.numerator = first.real.numerator * second.real.numerator;
        result.real.denominator = first.real.denominator * second.real.denominator;
        result.imaginity.numerator = first.imaginity.numerator * second.imaginity.numerator;
        result.imaginity.denominator = first.imaginity.denominator * second.imaginity.denominator;
        rational::simplify(result.real);
        rational::simplify(result.imaginity);
        print_complex_number(result);
    };
    static void Division (complex first , complex second)
    {
        complex result;
        result.real.numerator = first.real.numerator * second.real.denominator;
        result.real.denominator = first.real.denominator * second.real.numerator;
        result.imaginity.numerator = first.imaginity.numerator * second.imaginity.denominator;
        result.imaginity.denominator = first.imaginity.denominator * second.imaginity.numerator;
        rational::simplify(result.real);
        rational::simplify(result.imaginity);
        print_complex_number(result);
    };
    static void print (complex first , complex second)
    {
        cout << "First numnber \n--------------\n";
        first.set_value();
        cout << endl;
        cout << "Second numnber \n--------------\n";
        second.set_value();
        cout << endl << endl;
        cout << "Summation : " ; complex::sum(first,second) ; cout << endl;
        cout << "Mines : " ; Mines(first,second) ; cout << endl;
        cout << "Multiplication : " ; Multiplication(first,second) ; cout << endl;
        cout << "Division : " ; Division(first,second) ; cout << endl;
    };
    static bool is_equal (complex first , complex second)
    {
        if (rational::is_equal(first.real,second.real) && rational::is_equal(first.imaginity,second.imaginity))
            return true;
        return false;
    };
};
class myset
{
private :
    struct node
    {
        complex data;
        node * next;
    };
    node * First_addre;
public :
    myset () //sazande
    {
        First_addre -> next = NULL;
        First_addre -> data.real.numerator = NULL;
        First_addre -> data.real.denominator = NULL;
        First_addre -> data.imaginity.numerator = NULL;
        First_addre -> data.imaginity.denominator = NULL;
    };
    static void View_set (myset set) //DONED
    {
        if (set.First_addre == NULL)
            cout << "Set is empty" << endl;
        else
        {
            cout << " { ";
            node * current = set.First_addre;
            while (current)
            {
                cout << complex::print_complex_number(current -> data) << " , ";
                current = current -> next;
            }
            cout << "} " << endl;
        }
    };
    static bool have_the_set_this_data (myset set , complex data) //DONED
    {
        if (set.First_addre == NULL)
            cout << "Set is empty" << endl;
        else
        {
            if (how_many_repeat_a_data(set,data) == 1)
                return true;
        }
        return false;
    };
    static int how_many_repeat_a_data (myset set , complex data) //DONED
    {
        int n = 0;
        node * current = set.First_addre;
        while (current)
        {
            if (complex::is_equal(current -> data,data))
                n++;
            current = current -> next;
        }
        return n;
    };
    static void Add_member_to_set (myset set) //DONED
    {
        complex value;
        node * current = set.First_addre;
        cout << "Enter value : ";
        value.set_value();
        if (set.First_addre == NULL)
            cout << "Set is empty" << endl;
        else if (have_the_set_this_data(set,value))
            cout << "Value is invalid ... because of similarity" << endl;
        else
        {
            while (current -> next != NULL)
            {
                current = current -> next;
            }
            current -> next = new node;
            current = current -> next;
            current -> data = value; //IS THAT WORKING ???????????????????????????????????????????
            current -> next = NULL;
        }
    };
    static void Delete_member_from_set (myset &set) //DONED
    {
        complex value;
        node * current = set.First_addre;
        if (set.First_addre == NULL)
            cout << "Set is empty" << endl;
        else
        {
            cout << "Enter value : ";
            value.set_value();
            while (true)
            {
                if (!have_the_set_this_data(set,value))
                {
                    cout << "There is no equal value " << endl;
                    break;
                }
                if (complex::is_equal(current -> data,value) && (current == set.First_addre))
                {//avali
                    set.First_addre = set.First_addre -> next;
                    delete current;
                    break;
                }
                if (complex::is_equal(current -> next -> data,value) && (current->next == NULL))
                    {//akahri
                    node * p = current -> next;
                    current -> next = NULL;
                    delete p;
                    break;
                    }
                if (complex::is_equal(current -> next -> data,value))
                {//vasati
                    node * p = current -> next;
                    current -> next = current -> next -> next;
                    delete p;
                    break;
                }
                current = current -> next;
            }
        }
    };
    static void Sum_of_set (myset set) //DONED
    {
        node * current = set.First_addre;
        complex sum;
        if (set.First_addre == NULL)
            cout << "Set is empty" << endl;
        else
        {
            while (current)
            {
                sum = complex::return_sum(current -> data,sum);
                current = current -> next;
            }
            cout << "Sum : ";
            complex::print_complex_number(sum);
            cout << endl;
        }
    };
    static void Emptize_set (myset set) //DONED
    {
        if (set.First_addre == NULL)
            cout << "Set is empty" << endl;
        else
        {
            node * current = set.First_addre;
            node * next_node_addre;
            while (current)
            {
                next_node_addre = current -> next;
                delete current;
                current = next_node_addre;
            }
        }
    };
    static void Union (myset set_1 , myset set_2) //DONED
    {
        if (set_1.First_addre == NULL)
            cout << "First set is empty" << endl;
        else if (set_2.First_addre == NULL)
            cout << "Second set is empty" << endl;
        cout << "Union : ";
        cout << " { ";
        node * current = set_1.First_addre;
        while (current)
        {
            cout << complex::print_complex_number(current -> data) << " , ";
            current = current -> next;
        }
        current = set_2.First_addre;
        
        cout << "} " << endl;
    };
    static void Intersection (myset set_1 , myset set_2) //DONED
    {
        if (set_1.First_addre == NULL)
            cout << "First set is empty" << endl;
        else if (set_2.First_addre == NULL)
            cout << "Second set is empty" << endl;
        cout << "Interaction : ";
        cout << " { ";
        node * current = set_1.First_addre;
        while (current)
        {
            if (have_the_set_this_data(set_2,current -> data))
                cout << complex::print_complex_number(current -> data) << " , ";
            current = current -> next;
        }
        cout << "} ";
        cout << endl;
    };
    static void Difference (myset set_1 , myset set_2) //DONED
    {
        if (set_1.First_addre == NULL)
            cout << "First set is empty" << endl;
        else if (set_2.First_addre == NULL)
            cout << "Second set is empty" << endl;
        else
        {
            node * current = set_1.First_addre;
            cout << "Interaction : ";
            cout << " { ";
            while (current)
            {
                if (!have_the_set_this_data(set_2,current -> data))
                    cout << complex::print_complex_number(current -> data) << " , ";
                current = current -> next;
            }
            cout << "} ";
            cout << endl;
        }
    };
    static bool is_equal (myset set_1 , myset set_2) //DONED
    {
        node * current = set_2.First_addre;
        while (current)
        {
            if (!have_the_set_this_data(set_1,current -> data))
                return false;
            current = current -> next;
        }
        return true;
    };
    static void options ()
    {
        cout << "0.View first set\n";
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
        cout << "13.Close programme\n\n";
        cout << "Your choose : ";
    };
    static void UserInterface (myset set_1 , myset set_2)
    {
        while (true)
        {
            short choice;
            options();
            cin >> choice;
            cout << endl;
            while (choice < 0 || choice > 13)
            {
                cout << "\nWrong input ... Try again : ";
                cin >> choice;
            }
            if (choice == 13)
                break;
            switch (choice)
            {
                case 0 : View_set(set_1);
                    break;
                case 1 : View_set(set_2);
                    break;
                case 2 : Add_member_to_set(set_1);
                    break;
                case 3 : Add_member_to_set(set_2);
                    break;
                case 4 : Delete_member_from_set(set_1);
                    break;
                case 5 : Delete_member_from_set(set_2);
                    break;
                case 6 : Sum_of_set(set_1);
                    break;
                case 7 : Sum_of_set(set_2);
                    break;
                case 8 : Emptize_set(set_1);
                    break;
                case 9 : Emptize_set(set_2);
                    break;
                case 10 : Union(set_1,set_2);
                    break;
                case 11 : Intersection(set_1,set_2);
                    break;
                case 12 : Difference(set_1,set_2);
                    break;
            }
            cout << endl;
        }
    };
};
int main()
{
    myset first , second;
    myset::UserInterface(first,second);
}


#include <iostream>
#include <fstream>
#define max_units 12
#define min_units 4
#define max_rate 20
#define min_rate 0
int number_of_registered_students = 0;
int number_of_courses = 0;
using namespace std;
//-----Structers-----
struct StudenNode
{
      unsigned id;
      string fname;
      string lname;
      int average;
      StudenNode *next;
};
struct CourseNode
{
      unsigned code;
      string title;
      int units;
      int capacity;
      CourseNode *next;
};
struct RegisterNode
{
      StudenNode *student;
      CourseNode *course;
      RegisterNode *next;
};
//-----necessary but not enough-----
bool str1_find_str2 (string str1,string str2)
{
    int str1_lenght = str1.length();
    int str2_lenght = str2.length();
    int j = 0;
    for (short i = 0 ; i < str1_lenght ;)
    {
        if (str1[i] == str2[j])
        {
            i++;j++;
        }
        else
            i++;
    }
    if (j == str2_lenght)
        return true;
    return false;
}
void suugestions_for_student_number (StudenNode * address_of_first_student_node,string inputed_id)
{
    StudenNode * current = address_of_first_student_node;
    string node_id = to_string(current -> id);
    short i = 1;
    while (true)
    {
        if (node_id == inputed_id)
            break;
        if (current -> next == NULL)
        {
            if (str1_find_str2(node_id,inputed_id))
            {
                cout << i << "." << current -> id << '\t' << current -> fname << " " << current -> lname << endl;
                i++;
            }
            break;
        }
        if (str1_find_str2(node_id,inputed_id))
        {
            cout << i << "." << current -> id << '\t' << current -> fname << " " << current -> lname << endl;
            i++;
        }
        current = current -> next;
        node_id = to_string(current -> id);
    }
}
void suugestions_for_course_code (CourseNode * address_of_first_course_node,string inputed_code)
{
    CourseNode * current = address_of_first_course_node;
    string node_code = to_string(current -> code);
    short i = 1;
    while (true)
    {
        if (node_code == inputed_code)
            break;
        if (current -> next == NULL)
        {
            if (str1_find_str2(node_code,inputed_code))
            {
                cout << i << "." << current -> code << '\t' << current -> title << endl;
                i++;
            }
            break;
        }
        if (str1_find_str2(node_code,inputed_code))
        {
            cout << i << "." << current -> code << '\t' << current -> title << endl;
            i++;
        }
        current = current -> next;
        node_code = to_string(current -> code);
    }
}
string compare_two_string_according_to_alphabetics_and_return_less(string s1,string s2)
{
    string little , big;
    if (s1>s2)
    {
        little=s2;
        big=s1;
    }
    else
    {
        little=s1;
        big=s2;
    }
    int lenght = little.length();
    for (int i = 0 ; i < lenght ; i++)
    {
        if (little[i]>big[i])
            return big;
        if (little[i]<big[i])
            return little;
    }
    return little;
}
bool have_he_this_course (int code,int id,RegisterNode * address_of_first_register_node)
{
    RegisterNode * current = address_of_first_register_node;
    while (true)
    {
        if (current -> next == NULL)
        {
            if (current -> course -> code == code && current -> student -> id == id)
                return true;
            break;
        }
        if (current -> course -> code == code && current -> student -> id == id)
            return true;
        current = current -> next;
    }
    return false;
}
bool are_there_this_id_in_student_list (StudenNode * address_of_first_student_node,string id)
{
    StudenNode * current = address_of_first_student_node;
    int identifier = stoi(id);
    while (true)
    {
        if (current -> next == NULL)
        {
            if (current -> id == identifier)
                return true;
            break;
        }
        if (current -> id == identifier)
            return true;
        current = current -> next;
    }
    return false;
}
void update_file_after_add_course (int input_code,int input_id)
{
    fstream f;
    f.open("register.txt",ios::app);
    f << input_id << '\t' << input_code << endl;
    f.close();
}
bool just_number(string studentnumber)
{
    int n = studentnumber.length();
    for (int i = 0; i < n; i++)
        if (studentnumber[i] < '0' || studentnumber[i] > '9')
            return false;
    return true;
}
string to_lower_alphabetics (string input)
{
    int lenght = input.length();
    string output;
    char ch;
    for (int i = 0 ; i < lenght ; i++)
    {
        if (input[i] >= 'A' && input[i] <= 'Z')
        {
            ch = input[i] + 32;
            output += ch;
        }
        else
        {
            ch = input[i];
            output += ch;
        }
    }
    return output;
}
void print_all_students_for_one_course (StudenNode * address_of_first_student_node,RegisterNode * address_of_first_register_node,int code)
{
    StudenNode * current = address_of_first_student_node;
    int id = current -> id;
    short i = 1;
    while (true)
    {
        if (current -> next == NULL)
        {
            if (have_he_this_course(code,id,address_of_first_register_node))
            {
                cout << i << "." ;
                cout << current -> id << '\t';
                cout << current -> fname << '\t';
                cout << current -> lname << '\t';
                cout << current -> average << endl;
            }
            break;
        }
        if (have_he_this_course(code,id,address_of_first_register_node))
        {
            cout << i << "." ;
            cout << current -> id << '\t';
            cout << current -> fname << '\t';
            cout << current -> lname << '\t';
            cout << current -> average << endl;
            i++;
        }
        current = current -> next;
        id = current -> id;
    }
}
void print_all_students(StudenNode * first)
{
    StudenNode * current = first;
    short i = 1;
    while (true)
    {
        if (current -> next == NULL)
        {
            cout << i << "." ;
            cout << current -> id << '\t';
            cout << current -> fname << '\t';
            cout << current -> lname << '\t';
            cout << current -> average << endl;
            break;
        }
        cout << i << "." ;
        cout << current -> id << '\t';
        cout << current -> fname << '\t';
        cout << current -> lname << '\t';
        cout << current -> average << endl;
        current = current -> next;
        i++;
    }
}
int how_many_registered_for_course (RegisterNode * address_of_first_register_node,int code)
{
    int number = 0;
    RegisterNode * current = address_of_first_register_node;
    while (true)
    {
        if (current -> next == NULL)
        {
            if (current -> course -> code == code)
                number++;
            break;
        }
        if (current -> course -> code == code)
            number++;
        current = current -> next;
    }
    return number;
}
StudenNode * return_address_of_id (StudenNode * address_of_first_student_node,unsigned id)
{
    fstream f;
    f.open("students.txt");
    StudenNode * pointer = address_of_first_student_node;
    while (true)
    {
        if (pointer -> id == id)
            break;
        if (pointer -> next == NULL)
            break;
        pointer = pointer -> next;
    }
    f.close();
    return pointer;
}
CourseNode * return_address_of_course (CourseNode * address_of_first_course_node,unsigned code)
{
    fstream f;
    f.open("courses.txt");
    CourseNode * pointer = address_of_first_course_node;
    while (true)
    {
        if (pointer -> code == code)
            break;
        if (pointer -> next == NULL)
            break;
        pointer = pointer -> next;
    }
    f.close();
    return pointer;
}
int total_units_of_this_student (RegisterNode * address_of_first_register_node,int input_id)
{
    int total_units = 0;
    RegisterNode * current = address_of_first_register_node;
    int node_id;
    node_id = current -> student -> id;
    while (true)
    {
        if (node_id == input_id)
            total_units += current -> course -> units;
        current = current -> next;
        node_id = current -> student -> id;
        if (current -> next == NULL)
        {
            if (node_id == input_id)
                total_units += current -> course -> units;
            break;
        }
    }
    return total_units;
}
bool kaf_vahed_roayat_mishavad (CourseNode * address_of_first_course_node,RegisterNode * address_of_first_register_node,int input_code,int input_id)
{
    CourseNode * course_address = return_address_of_course(address_of_first_course_node,input_code);
    int deleted_units = course_address -> units;
    int old_units = total_units_of_this_student(address_of_first_register_node,input_id);
        if (old_units - deleted_units < min_units)
            return false;
    return true;
}
bool saghf_vahed_roayat_mishavad (StudenNode * address_of_first_student_node,CourseNode * address_of_first_course_node,RegisterNode * address_of_first_register_node,int input_code,int input_id)
{
    StudenNode * student_address = return_address_of_id(address_of_first_student_node,input_id);
    int avg = student_address -> average;
    CourseNode * course_address = return_address_of_course(address_of_first_course_node,input_code);
    int new_units = course_address -> units;
    int old_units = total_units_of_this_student(address_of_first_register_node,input_id);
    if (avg >= 17)
        if (new_units + old_units <= max_units)
            return true;
    if (avg <= 17)
        if (new_units + old_units <= 10)
            return true;
    return false;
}
bool zarfiat_dars_roayat_mishavad (CourseNode * address_of_first_course_node,RegisterNode * address_of_first_register_node,int input_code)
{
    int capacity = 0;
    int number_of_registered = 0;
    CourseNode * current_course_node = address_of_first_course_node;
    RegisterNode * current_register_node = address_of_first_register_node;
    while (true)
    {
        if (current_course_node -> code == input_code)
        {
            capacity = current_course_node -> capacity;
            break;
        }
        current_course_node = current_course_node -> next;
        if (current_course_node -> next == NULL)
        {
            if (current_course_node -> code == input_code)
            {
                capacity = current_course_node -> capacity;
                break;
            }
            break;
        }
    }
    number_of_registered = how_many_registered_for_course(address_of_first_register_node,input_code);
    if (number_of_registered < capacity)
        return true;
    return false;
}
void add_course_to_end_of_register_node (StudenNode * address_of_first_student_node,CourseNode * address_of_first_course_node,RegisterNode * address_of_first_register_node,int input_id,int input_code)
{
    StudenNode * student_address = return_address_of_id(address_of_first_student_node,input_id);
    CourseNode * course_address = return_address_of_course(address_of_first_course_node,input_code);
    RegisterNode * current = address_of_first_register_node;
    while (true)
    {
        if (current -> next == NULL)
        {
            current -> next = new RegisterNode;
            current = current -> next;
            current -> student = student_address;
            current -> course = course_address;
            current -> next = NULL;
            break;
        }
        current = current -> next;
    }
}
void delete_course_from_register_node (RegisterNode * &address_of_first_register_node,int input_id,int input_code)
{
    RegisterNode * current_register = address_of_first_register_node;
    RegisterNode * next_register = current_register -> next;
    int current_node_id = current_register -> student -> id;
    int current_node_code = current_register -> course -> code;
    int next_node_id = next_register -> student -> id;
    int next_node_code = next_register -> course -> code;
    while (true)
    {
        if ((current_node_id == input_id) && (current_node_code == input_code) && (current_register == address_of_first_register_node))
        {//avali
            address_of_first_register_node = current_register -> next;
            delete current_register;
            break;
        }
        if ((next_node_id == input_id) && (next_node_code == input_code))
        {//vasati
            current_register -> next = next_register -> next;
            delete next_register;
            break;
        }
        if ((next_node_id == input_id) && (next_node_code == input_code) && (next_register -> next == NULL))
        { //akahri
            RegisterNode * p = current_register -> next;
            current_register -> next = NULL;
            delete p;
            break;
        }
        current_register = current_register -> next;
        next_register = current_register -> next;
        current_node_id = current_register -> student -> id;
        current_node_code = current_register -> course -> code;
        next_node_id = next_register -> student -> id;
        next_node_code = next_register -> course -> code;
    }
}
bool are_there_this_code_in_courses_list (CourseNode * address_of_first_course_node,int code)
{
    CourseNode * current = address_of_first_course_node;
    while (true)
    {
        if (current -> next == NULL)
        {
            if (current -> code == code)
            {
                cout << "Title of course is : " << current -> title << endl;
                cout << "List of registered students , according to alphabetics" << endl;
                return true;
            }
            else
                break;
        }
        if (current -> code == code)
        {
            cout << "Title of course is : " << current -> title << endl;
            cout << "List of registered students , according to alphabetics" << endl;
            return true;
        }
        current = current -> next;
    }
    return false;
}
bool are_there_this_code_in_courses_list (CourseNode * address_of_first_course_node,string code)
{
    CourseNode * current = address_of_first_course_node;
    int course_code = stoi(code);
    while (true)
    {
        if (current -> next == NULL)
        {
            if (current -> code == course_code)
                return true;
            break;
        }
        if (current -> code == course_code)
            return true;
        current = current -> next;
    }
    return false;
}
void update_file_after_delete_course (RegisterNode * address_of_first_register_node)
{
    fstream f;
    f.open("register.txt");
    RegisterNode * current = address_of_first_register_node;
    while (current)
    {
        f << current -> student -> id << '\t' << current -> course -> code << endl;
        current = current -> next;
    }
    f.close();
}
//-----Read & Save data from files-----
StudenNode * read_and_save_data_from_students_file ()
{
    fstream f;
    StudenNode * first = NULL;
    StudenNode * current = new StudenNode;
    string identefier,firstname,lastname,avg;
    f.open("students.txt");
    if (getline(f,identefier,'\t') && getline(f,firstname,'\t') && getline(f,lastname,'\t') && getline(f,avg,'\n'))
    {
        StudenNode * current = new StudenNode;
        number_of_registered_students++;
        current -> id = stoi(identefier);
        current -> fname = to_lower_alphabetics(firstname);
        current -> lname = to_lower_alphabetics(lastname);
        current -> average = stoi(avg);
        first = current;
    }
    while (getline(f,identefier,'\t') && getline(f,firstname,'\t') && getline(f,lastname,'\t') && getline(f,avg,'\n'))
    {
        number_of_registered_students++;
        current -> next = new StudenNode;
        current = current -> next;
        current -> id = stoi(identefier);
        current -> fname = to_lower_alphabetics(firstname);
        current -> lname = to_lower_alphabetics(lastname);
        current -> average = stoi(avg);
    }
    current -> next = NULL;
    f.close();
    return first;
}
CourseNode * read_and_save_data_from_courses_file ()
{
    fstream f;
    CourseNode * first = NULL;
    CourseNode * current = new CourseNode;
    string code,title,units,capacity;
    f.open("courses.txt");
    if (getline(f,code,'\t') && getline(f,title,'\t') && getline(f,units,'\t') && getline(f,capacity,'\n'))
    {
        number_of_courses++;
        current -> code = stoi(code);
        current -> title = title;
        current -> units = stoi(units);
        current -> capacity = stoi(capacity);
        first = current;
    }
    while (getline(f,code,'\t') && getline(f,title,'\t') && getline(f,units,'\t') && getline(f,capacity,'\n'))
    {
        number_of_courses++;
        current -> next = new CourseNode;;
        current = current -> next;
        current -> code = stoi(code);
        current -> title = title;
        current -> units = stoi(units);
        current -> capacity = stoi(capacity);
    }
    current -> next = NULL;
    f.close();
    return first;
}
RegisterNode * read_and_save_data_from_register_file (StudenNode * address_of_first_student_node,CourseNode * address_of_first_course_node)
{
    fstream f;
    RegisterNode * first = NULL;
    RegisterNode * current = new RegisterNode;
    string identefier,code;
    StudenNode * student_address;
    CourseNode * course_address;
    unsigned id,cod;
    f.open("register.txt");
    if (getline(f,identefier,'\t') && getline(f,code,'\n'))
    {
        id = stoi(identefier);
        cod = stoi(code);
        student_address = return_address_of_id(address_of_first_student_node,id);
        course_address = return_address_of_course(address_of_first_course_node,cod);
        if (student_address && course_address)
        {
            current -> student = student_address;
            current -> course = course_address;
        }
        first = current;
    }
    while (getline(f,identefier,'\t') && getline(f,code,'\n'))
    {
        id = stoi(identefier);
        cod = stoi(code);
        current -> next = new RegisterNode;
        current = current -> next;
        student_address = return_address_of_id(address_of_first_student_node,id);
        course_address = return_address_of_course(address_of_first_course_node,cod);
        if (student_address && course_address)
        {
            current -> student = student_address;
            current -> course = course_address;
        }
    }
    current -> next = NULL;
    f.close();
    return first;
}
//-----Add/Del courses-----
void register_course (StudenNode * address_of_first_student_node,CourseNode * address_of_first_course_node,RegisterNode * address_of_first_register_node)
{
    string input_id_str , input_code_str;
    cout << "Enter studentnumber : ";
    cin >> input_id_str;
    suugestions_for_student_number(address_of_first_student_node,input_id_str);
    while(!just_number(input_id_str) || !are_there_this_id_in_student_list(address_of_first_student_node,input_id_str))
    {
        cout << "Invalid values ... Help from suggestions" << endl << "Try again : " ;
        cin >> input_id_str;
        suugestions_for_student_number(address_of_first_student_node,input_id_str);
    }
    cout << "Enter course's code : ";
    cin >> input_code_str;
    suugestions_for_course_code(address_of_first_course_node,input_code_str);
    while (!just_number(input_code_str) || !are_there_this_code_in_courses_list(address_of_first_course_node,input_code_str))
    {
        cout << "Invalid values ..." << endl << "Try again : " ;
        cin >> input_code_str;
        suugestions_for_course_code(address_of_first_course_node,input_code_str);
    }
    int input_code = stoi(input_code_str) , input_id = stoi(input_id_str);
    while (true)
        {
            if (have_he_this_course(input_code,input_id,address_of_first_register_node))
            {
                cout << "You have this course , now " << endl;
                break;
            }
            if (!zarfiat_dars_roayat_mishavad(address_of_first_course_node,address_of_first_register_node,input_code))
            {
                cout << "Capacity of this course is fulled " << endl;
                break;
            }
            if  (!saghf_vahed_roayat_mishavad(address_of_first_student_node,address_of_first_course_node,address_of_first_register_node,input_code,input_id))
            {   cout << "You achived , maximum of your valid units " << endl;
                break;
            }
            add_course_to_end_of_register_node(address_of_first_student_node,address_of_first_course_node,address_of_first_register_node,input_id,input_code);
            update_file_after_add_course(input_code,input_id);
            CourseNode * course = return_address_of_course(address_of_first_course_node,input_code);
            StudenNode * student = return_address_of_id(address_of_first_student_node,input_id);
            cout << course -> title << " added successful for " << student -> fname << " " << student -> lname << endl;
            break;
        }
}
void print_reg (RegisterNode * address_of_first_register_node)
{
    RegisterNode * current = address_of_first_register_node;
    short i = 1;
    while (true)
    {
        if (current -> next == NULL)
        {
            cout << i << "." << current -> student -> fname << '\t' << current -> student -> lname << '\t' << current -> course -> title << endl;
            break;
        }
        cout << i << "." << current -> student -> fname << '\t' << current -> student -> lname << '\t' << current -> course -> title << endl;
        i++;
        current = current -> next;
    }
}
void remove_registered_course (StudenNode * address_of_first_student_node,CourseNode * address_of_first_course_node,RegisterNode * address_of_first_register_node)
{
    if (number_of_courses > 1)
    {
        print_reg(address_of_first_register_node);
        string input_id_str , input_code_str;
        cout << "Enter studentnumber : ";
        cin >> input_id_str;
        suugestions_for_student_number(address_of_first_student_node,input_id_str);
        while(!just_number(input_id_str) || !are_there_this_id_in_student_list(address_of_first_student_node,input_id_str))
        {
            cout << "Invalid values ... Help from suggestions" << endl << "Try again : " ;
            cin >> input_id_str;
            suugestions_for_student_number(address_of_first_student_node,input_id_str);
        }
        cout << "Enter course's code : ";
        cin >> input_code_str;
        suugestions_for_course_code(address_of_first_course_node,input_code_str);
        while (!just_number(input_code_str) || !are_there_this_code_in_courses_list(address_of_first_course_node,input_code_str))
        {
            cout << "Invalid values ..." << endl << "Try again : " ;
            cin >> input_code_str;
            suugestions_for_course_code(address_of_first_course_node,input_code_str);
        }
        int input_code = stoi(input_code_str) , input_id = stoi(input_id_str);
        while (true)
        {
            if (!kaf_vahed_roayat_mishavad(address_of_first_course_node,address_of_first_register_node,input_code,input_id))
            {
                cout << "Your units will be under valid units " << endl;
                break;
            }
            if (!have_he_this_course(input_code,input_id,address_of_first_register_node))
            {
                cout << "You have not this course ..." << endl;
                break;
            }
            delete_course_from_register_node(address_of_first_register_node,input_id,input_code);
            update_file_after_delete_course(address_of_first_register_node);
            CourseNode * course = return_address_of_course(address_of_first_course_node,input_code);
            StudenNode * student = return_address_of_id(address_of_first_student_node,input_id);
            cout << course -> title << " removed successful for " << student -> fname << " " << student -> lname << endl;
            print_reg(address_of_first_register_node);
            break;
        }
    }
    else
        cout << "Remove course is disable ... There is just one course" << endl;
}
//-----course's lists-----
void list_of_each_course_and_number_of_their_registered_students (CourseNode * address_of_first_course_node,RegisterNode * address_of_first_register_node)
{
    CourseNode * current_course = address_of_first_course_node;
    RegisterNode * current_register = address_of_first_register_node;
    float code;
    int i = 1;
    while (true)
    {
        float n = 0;
        code = current_course -> code;
        float capacity = current_course -> capacity;
        if (current_course -> next == NULL)
        {
            while (true)
            {
                if (current_register -> next == NULL)
                {
                    if (current_register -> course -> code == code)
                        n++;
                    cout << i << "." << current_course -> title << "\t\t" << n << " Students registered" << "\t\t" << n*100 / capacity << " Percent of capacity" << endl;
                    i++;
                    break;
                }
                if (current_register -> course -> code == code)
                    n++;
                current_register = current_register -> next;
            }
        }
        if (current_course -> next == NULL)
            break;
        while (true)
        {
            if (current_register -> next == NULL)
            {
                if (current_register -> course -> code == code)
                    n++;
                cout << i << "." << current_course -> title << "\t\t" << n << " Students registered" << "\t\t" << n*100 / capacity << " Percent of capacity" << endl;
                i++;
                break;
            }
            if (current_register -> course -> code == code)
                n++;
            current_register = current_register -> next;
        }
        current_register = address_of_first_register_node;
        current_course = current_course -> next;
    }
}
void list_of_registered_courses_for_each_students (StudenNode * address_of_first_student_node,CourseNode * address_of_first_course_node,RegisterNode * address_of_first_register_node)
{
    string input_id_str;
    cout << "Enter studentnumber : ";
    cin >> input_id_str;
    suugestions_for_student_number(address_of_first_student_node,input_id_str);
    while(!just_number(input_id_str) || !are_there_this_id_in_student_list(address_of_first_student_node,input_id_str))
    {
        cout << "Invalid values ..." << endl << "Try again : " ;
        cin >> input_id_str;
        suugestions_for_student_number(address_of_first_student_node,input_id_str);
    }
    int input_id = stoi(input_id_str);
    StudenNode * student = return_address_of_id(address_of_first_student_node,input_id);
    cout << student -> fname << " " << student -> lname << endl;
    cout << "List of your registered courses are : " << endl;
    int i = 1 , total_units = 0 , node_id;
    RegisterNode * current = address_of_first_register_node;
    node_id = current -> student -> id;
    while (true)
    {
        if (current -> next == NULL)
        {
            if (node_id == input_id)
            {
                cout << i << "." << current -> course -> title << '\t' << current -> course -> units << " UNITS" << endl;
                total_units += current -> course -> units;
                i++;
            }
            break;
        }
        if (node_id == input_id)
        {
            cout << i << "." << current -> course -> title << '\t' << current -> course -> units << " UNITS" << endl;
            total_units += current -> course -> units;
            i++;
        }
        current = current -> next;
        node_id = current -> student -> id;
    }
    cout << "Total units are : " << total_units << endl;
}
//-----students's lists-----
void list_of_each_student_and_number_of_their_registered_units (RegisterNode * address_of_first_register_node,StudenNode * address_of_first_student_node)
{
    RegisterNode * current_register = address_of_first_register_node;
    StudenNode * current_student = address_of_first_student_node;
    int i = 1;
    while (true)
    {
        int id = current_student -> id;
        int units = total_units_of_this_student(address_of_first_register_node,id);
        if (current_student -> next == NULL)
        {
            int id = current_student -> id;
            int units = total_units_of_this_student(address_of_first_register_node,id);
            cout << i << "." << id << '\t' << current_student -> fname << '\t' << current_student -> lname << '\t' << units << " units" << endl;
            break;
        }
        cout << i << "." << id << '\t' << current_student -> fname << '\t' << current_student -> lname << '\t' << units << " units" << endl;
        i++;
        current_student = current_student -> next;
    }
}
void insert_bad_place_node_in_right_place (StudenNode * &head,StudenNode * end,StudenNode * &bad_place)
{
    StudenNode * first_sorted = head;
    StudenNode * second_sorted = head -> next;
    string bad_place_str = bad_place -> lname + bad_place -> fname;
    string first_sorted_str = first_sorted -> lname + first_sorted -> fname;
    string second_sorted_str = second_sorted -> lname + second_sorted -> fname;
    while (true)
    {
        if (second_sorted == end)
            {
                if (bad_place_str == compare_two_string_according_to_alphabetics_and_return_less(first_sorted_str,bad_place_str))
                {
                    bad_place -> next = first_sorted;
                    head = bad_place;
                    break;
                }
                if ((first_sorted_str == compare_two_string_according_to_alphabetics_and_return_less(first_sorted_str,bad_place_str)) && (bad_place_str == compare_two_string_according_to_alphabetics_and_return_less(second_sorted_str,bad_place_str)))
                {
                    first_sorted -> next = bad_place;
                    bad_place -> next = second_sorted;
                    break;
                }
            }
        if (bad_place_str == compare_two_string_according_to_alphabetics_and_return_less(first_sorted_str,bad_place_str))
        {
            bad_place -> next = first_sorted;
            head = bad_place;
            break;
        }
        if ((first_sorted_str == compare_two_string_according_to_alphabetics_and_return_less(first_sorted_str,bad_place_str)) && (bad_place_str == compare_two_string_according_to_alphabetics_and_return_less(second_sorted_str,bad_place_str)))
        {
            first_sorted -> next = bad_place;
            bad_place -> next = second_sorted;
            break;
        }
        first_sorted = second_sorted;
        second_sorted = second_sorted -> next;
        first_sorted_str = first_sorted -> lname + first_sorted -> fname;
        second_sorted_str = second_sorted -> lname + second_sorted -> fname;
    }
    end -> next = NULL;
}
void list_of_ordered_all_students_according_to_alphabetics (StudenNode * &address_of_first_student_node)
{
    int n = number_of_registered_students;
    if (n > 1)
    {
        StudenNode * first_unsorted = address_of_first_student_node;
        StudenNode * second_unsorted = first_unsorted -> next;
        StudenNode * head_of_sorted_list = first_unsorted;
        StudenNode * end_of_sorted_list = second_unsorted;
        StudenNode * temp = NULL;
        string first_unsorted_str = first_unsorted -> lname + first_unsorted -> fname;
        string second_unsorted_str = second_unsorted -> lname + second_unsorted -> fname;
        string less = compare_two_string_according_to_alphabetics_and_return_less(first_unsorted_str,second_unsorted_str);
        while (true)
        {
            if (less == first_unsorted_str)
            {
                if (end_of_sorted_list != second_unsorted)
                    end_of_sorted_list -> next = second_unsorted;
                end_of_sorted_list = second_unsorted;
                first_unsorted = second_unsorted;
                if (n != 2)
                    {
                        second_unsorted = second_unsorted -> next;
                        first_unsorted_str = first_unsorted -> lname + first_unsorted -> fname;
                        second_unsorted_str = second_unsorted -> lname + second_unsorted -> fname;
                        less = compare_two_string_according_to_alphabetics_and_return_less(first_unsorted_str,second_unsorted_str);
                    }
                n--;
            }
            else
            {
                if (n != 2)
                    temp = second_unsorted -> next;
                insert_bad_place_node_in_right_place(head_of_sorted_list,end_of_sorted_list,second_unsorted);
                first_unsorted = end_of_sorted_list;
                second_unsorted = temp;
                first_unsorted_str = first_unsorted -> lname + first_unsorted -> fname;
                second_unsorted_str = second_unsorted -> lname + second_unsorted -> fname;
                less = compare_two_string_according_to_alphabetics_and_return_less(first_unsorted_str,second_unsorted_str);
                n--;
            }
            if (n == 1)
                break;
        }
        address_of_first_student_node = head_of_sorted_list;
    }
}
void list_of_ordered_students_for_each_course_according_to_alphabetics (StudenNode * address_of_first_student_node,CourseNode * address_of_first_course_node,RegisterNode * address_of_first_register_node)
{
    cout << "Enter code of course : " ;
    int code;
    cin >> code;
    string inputed_code = to_string(code);
    suugestions_for_course_code(address_of_first_course_node,inputed_code);
    while (!are_there_this_code_in_courses_list(address_of_first_course_node,code))
    {
        cout << "There is not this code in courses list ..." << endl << "Try again : ";
        cin >> code;
        inputed_code = to_string(code);
        suugestions_for_course_code(address_of_first_course_node,inputed_code);
    }
    int registered = how_many_registered_for_course(address_of_first_register_node,code);
    if (registered >= 1)
    {
        list_of_ordered_all_students_according_to_alphabetics(address_of_first_student_node);
        print_all_students_for_one_course(address_of_first_student_node,address_of_first_register_node,code);
    }
    else
        cout << "There is no one for this course ... " << endl;
}
void list_of_ordered_all_students_according_to_rates (StudenNode * address_of_first_student_node)
{
    StudenNode * current = address_of_first_student_node;
    int rate = max_rate , i = 1;
    while (true)
    {
        while (true)
        {
            if (current -> next == NULL)
            {
                if (current -> average == rate)
                {
                    cout << i << "." << current -> id << "\t\t" << current -> fname << "\t\t" << current -> lname << "\t\t" << rate << endl;
                    i++;
                }
                break;
            }
            if (current -> average == rate)
            {
                cout << i << "." << current -> id << "\t\t" << current -> fname << "\t\t" << current -> lname << "\t\t" << rate << endl;
                i++;
            }
            current = current -> next;
        }
        current = address_of_first_student_node;
        rate--;
        if (rate == min_rate - 1)
            break;
    }
}
void list_of_ordered_all_students_according_to_registered_units (StudenNode * address_of_first_student_node,RegisterNode * address_of_first_register_node)
{
    StudenNode * current_student = address_of_first_student_node;
    int id = current_student -> id , units = max_units , i = 1;
    while (true)
    {
        while (true)
        {
            if (current_student -> next == NULL)
            {
                if (total_units_of_this_student(address_of_first_register_node,id) == units)
                {
                    cout << i << "." << id << "\t\t" << current_student -> fname << "\t\t" << current_student -> lname << "\t\t" << units << " units" << endl;
                    i++;
                }
                break;
            }
            if (total_units_of_this_student(address_of_first_register_node,id) == units)
            {
                cout << i << "." << id << "\t\t" << current_student -> fname << "\t\t" << current_student -> lname << "\t\t" <<units << " units" << endl;
                i++;
            }
            current_student = current_student -> next;
            id = current_student -> id;
        }
        current_student = address_of_first_student_node;
        id = current_student -> id;
        units--;
        if (units == min_units - 1)
            break;
    }
}
//-----Options-----
void options ()
{
    cout << "\n-----Add/Del courses-----\n";
    cout << "1.Register course\n2.Remove registered course\n\n";
    cout << "-----Course's lists-----\n";
    cout << "3.List of courses and number of their registered students\n";
    cout << "4.List of registered courses for each student\n\n";
    cout << "-----Students's lists-----\n";
    cout << "5.List of students and number of their registered units\n";
    cout << "6.List of ordered students for each course , according to alphabetics\n";
    cout << "7.List of ordered students , according to alphabetics\n";
    cout << "8.List of ordered students , according to rates\n";
    cout << "9.List of ordered students , according to registered units\n\n";
    cout << "-----Another options-----\n";
    cout << "10.Close programme\n\n";
    cout << "Your choose : ";
}
//-----Menu-----
void menu ()
{
    StudenNode * address_of_first_student_node = read_and_save_data_from_students_file();
    CourseNode * address_of_first_course_node = read_and_save_data_from_courses_file();
    RegisterNode * address_of_first_register_node = read_and_save_data_from_register_file(address_of_first_student_node,address_of_first_course_node);
    while (true)
    {
        short choice;
        options();
        cin >> choice;
        cout << endl;
        while (choice < 1 || choice > 10)
        {
            cout << "\nWrong input ... Try again : ";
            cin >> choice;
        }
        if (choice == 10)
            break;
        switch (choice)
        {
            case 1 :
                if (address_of_first_student_node == NULL)
                {
                    cout << "Student file is empty" << endl;
                    break;
                }
                register_course(address_of_first_student_node,address_of_first_course_node,address_of_first_register_node);
                break;
            case 2 :
                if (address_of_first_student_node == NULL)
                {
                    cout << "Student file is empty" << endl;
                    break;
                }
                remove_registered_course(address_of_first_student_node,address_of_first_course_node,address_of_first_register_node);
                break;
            case 3 :
                if (address_of_first_course_node == NULL)
                {
                    cout << "Course file is empty" << endl;
                    break;
                }
                list_of_each_course_and_number_of_their_registered_students(address_of_first_course_node, address_of_first_register_node);
                break;
            case 4 :
                if (address_of_first_student_node == NULL)
                {
                    cout << "Student file is empty" << endl;
                    break;
                }
                if (address_of_first_course_node == NULL)
                {
                    cout << "Course file is empty" << endl;
                    break;
                }
                list_of_registered_courses_for_each_students(address_of_first_student_node, address_of_first_course_node, address_of_first_register_node);
                break;
            case 5 :
                if (address_of_first_student_node == NULL)
                {
                    cout << "Student file is empty" << endl;
                    break;
                }
                if (address_of_first_course_node == NULL)
                {
                    cout << "Course file is empty" << endl;
                    break;
                }
                list_of_each_student_and_number_of_their_registered_units(address_of_first_register_node, address_of_first_student_node);
                break;
            case 6 :
                if (address_of_first_student_node == NULL)
                {
                    cout << "Student file is empty" << endl;
                    break;
                }
                if (address_of_first_course_node == NULL)
                {
                    cout << "Course file is empty" << endl;
                    break;
                }
                list_of_ordered_students_for_each_course_according_to_alphabetics(address_of_first_student_node,address_of_first_course_node,address_of_first_register_node);
                break;
            case 7 :
                if (address_of_first_student_node == NULL)
                {
                    cout << "Student file is empty" << endl;
                    break;
                }
                list_of_ordered_all_students_according_to_alphabetics(address_of_first_student_node);
                print_all_students(address_of_first_student_node);
                break;
            case 8 :
                if (address_of_first_student_node == NULL)
                {
                    cout << "Student file is empty" << endl;
                    break;
                }
                list_of_ordered_all_students_according_to_rates(address_of_first_student_node);
                break;
            case 9 :
                if (address_of_first_student_node == NULL)
                {
                    cout << "Student file is empty" << endl;
                    break;
                }
                list_of_ordered_all_students_according_to_registered_units(address_of_first_student_node, address_of_first_register_node);
                break;
        }
        cout << endl;
    }
}
int main()
{
    menu();
}




/*
 RegisterNode * find_next_registernode_who_has_this_course (RegisterNode * arrived,int code)
 {
     if (arrived -> next == NULL)
         return NULL;
     RegisterNode * current = arrived -> next;
     while (true)
     {
         if (current -> next == NULL)
         {
             if (current -> course -> code == code)
                 return current;
             break;
         }
         if (current -> course -> code == code)
             return current;
         current = current -> next;
     }
     return NULL;
 }
 void list_of_ordered_students_for_each_course_according_to_alphabetics (StudenNode * address_of_first_student_node,CourseNode * address_of_first_course_node,RegisterNode * address_of_first_register_node)
 {
     //روش دوم : یکبار مرتب سازی برای همه و سپس هر کدام که کدی برابر با کد وارده داشت ، آنرا چاپ کن
     cout << "Enter code of course : " ;
     int code;
     cin >> code;
     while (!are_there_this_code_in_courses_list(address_of_first_course_node,code))
     {
         cout << "There is not this code in courses list ..." << endl << "Try again : ";
         cin >> code;
     }
     int n = how_many_registered_for_course(address_of_first_register_node,code);
     RegisterNode * current = address_of_first_register_node;
     if (n > 1)
     {
         RegisterNode * first_unsorted;
         if (address_of_first_register_node -> course -> code == code)
             RegisterNode * first_unsorted = address_of_first_register_node;
         else
             RegisterNode * first_unsorted = find_next_registernode_who_has_this_course(address_of_first_register_node,code);
         RegisterNode * second_unsorted = find_next_registernode_who_has_this_course(first_unsorted,code);
         RegisterNode * head_of_sorted_list = first_unsorted;
         RegisterNode * end_of_sorted_list = second_unsorted;
         RegisterNode * temp = NULL;
         string first_unsorted_str = first_unsorted -> student -> lname + first_unsorted -> student -> fname;
         string second_unsorted_str = second_unsorted -> student -> lname + second_unsorted -> student -> fname;
         string less = compare_two_string_according_to_alphabetics_and_return_less(first_unsorted_str,second_unsorted_str);
         while (true)
         {
             if (less == first_unsorted_str)
             {
                 if (end_of_sorted_list != second_unsorted)
                     end_of_sorted_list -> next = second_unsorted;
                 end_of_sorted_list = second_unsorted;
                 first_unsorted = end_of_sorted_list;
                 if (n != 2)
                     {
                         second_unsorted = find_next_registernode_who_has_this_course(second_unsorted,code);
                         if (second_unsorted == NULL)
                             break;
                         first_unsorted_str = first_unsorted -> student -> lname + first_unsorted -> student -> fname;
                         second_unsorted_str = second_unsorted -> student -> lname + second_unsorted -> student -> fname;
                         less = compare_two_string_according_to_alphabetics_and_return_less(first_unsorted_str,second_unsorted_str);
                     }
                 n--;
             }
             else
             {
                 if (n != 2)
                     temp = find_next_registernode_who_has_this_course(second_unsorted,code);
                 insert_bad_place_node_in_right_place_for_one_course(head_of_sorted_list,end_of_sorted_list,second_unsorted);
                 first_unsorted = end_of_sorted_list;
                 second_unsorted = temp;
                 if (temp == NULL)
                     break;
                 first_unsorted_str = first_unsorted -> student -> lname + first_unsorted -> student -> fname;
                 second_unsorted_str = second_unsorted -> student -> lname + second_unsorted -> student -> fname;
                 less = compare_two_string_according_to_alphabetics_and_return_less(first_unsorted_str,second_unsorted_str);
                 n--;
             }
             if (n == 1)
                 break;
         }
         address_of_first_register_node = head_of_sorted_list;
     }
 }
 */

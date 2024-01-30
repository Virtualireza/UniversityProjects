#include <iostream>
#include <fstream>
using namespace std ;
#define perspolis "perspolis"
#define esteghlal "esteghlal"
#define mosavi "mosavi"
#define mibare "mibare"
#define bazandast "bazandast"
string delete_space (string str)
{
    int lenght = str.length();
    string finished_str;
    for (int i = 0 ; i < lenght ; i++)
        if (str[i] != ' ')
            finished_str += str[i];
    return finished_str;
}
bool is_number (char ch)
{
    if (ch < '0' || ch > '9')
        return false;
    return true;
}
bool number_dash_number (string data,int starting_cell)
{
    if (is_number(data[starting_cell]) && data[starting_cell+1] == '-' && is_number(data[starting_cell+2]))
        return true;
    return false;
}
void delete_point_and_attention_symbol (string &s)
{
    int lenght = s.length();
    string str;
    char end_char = s[lenght - 1];
    if (end_char == '.' || end_char == '!')
    {
        for (int i = 0 ; i < lenght - 1 ; i++)
            str += s[i];
        s = str;
    }
}
bool equal_lenght_but_just_one_diference (string a,string b)
{
    int lenght = a.length();
    if (b.length() != lenght)
        return false;
    int faults = 0 ;
    char capital[lenght];
    char small[lenght];
    for (int i = 0 ; i < lenght ; i++)
    {
        if (a[i] >= 'A' && a[i] <= 'Z')
            capital[i] = a[i];
        if (a[i] >= 'a' && a[i] <= 'z')
            capital[i] = a[i] - 32 ;
    }
    for (int i = 0 ; i < lenght ; i++)
        small[i] = capital[i] + 32 ;
    for (int i = 0 ; i < lenght ; i++)
    {
        if (b[i] == capital[i] || b[i] == small[i]);
        else
            faults++;
    }
    if (faults > 1)
        return false;
    return true;
}
bool the_diference_is_just_one_add_character (string a,string b)
{
    int lenght_a = a.length();
    int lenght_b = b.length();
    string max,min ; // min & max append on width of strings a and b
    if (lenght_a > lenght_b)
    {
        max = a;
        min = b;
    }
    else
    {
        max = b;
        min = a;
    }
    int max_lenght = max.length();
    int min_lenght = min.length();
    if (min_lenght + 1 != max_lenght)
        return false;
    char capital[min_lenght];
    char small[min_lenght];
    for (int i = 0 ; i < min_lenght ; i++)
    {
        if (min[i] >= 'A' && min[i] <= 'Z')
            capital[i] = min[i];
        if (min[i] >= 'a' && min[i] <= 'z')
            capital[i] = min[i] - 32 ;
    }
    for (int i = 0 ; i < min_lenght ; i++)
        small[i] = capital[i] + 32 ;
    int faults = 0;
    for (int i = 0 , j = 0 ; i < min_lenght ; i++ , j++)
    {
        if (max[j] == capital[i] || max[j] == small[i]);
        else
        {
            faults++;
            j++;
            for (;i < min_lenght;i++,j++)
                if (!(max[j] == capital[i] || max[j] == small[i]))
                    faults++;
            break;
        }
    }
    if (faults > 1)
        return false;
    return true;
}
bool the_diference_is_just_one_less_character (string a,string b)
{
    int lenght_a = a.length();
    int lenght_b = b.length();
    string max,min ;
    if (lenght_a > lenght_b)
    {
        max = a;
        min = b;
    }
    else
    {
        max = b;
        min = a;
    }
    int max_lenght = max.length();
    int min_lenght = min.length();
    char capital[max_lenght];
    char small[max_lenght];
    for (int i = 0 ; i < max_lenght ; i++)
    {
        if (max[i] >= 'A' && max[i] <= 'Z')
            capital[i] = max[i];
        if (max[i] >= 'a' && max[i] <= 'z')
            capital[i] = max[i] - 32 ;
    }
    for (int i = 0 ; i < max_lenght ; i++)
        small[i] = capital[i] + 32 ;
    if (min_lenght + 1 != max_lenght)
        return false;
    int faults = 0;
    for (int i = 0 , j = 0 ; i < min_lenght ; i++ , j++)
    {
        if (min[i] == capital[j] || min[i] == small[j]);
        else
        {
            faults++;
            j++;
            for (;i < min_lenght;i++,j++)
                if (!(min[i] == capital[j] || min[i] == small[j]))
                    faults++;
            break;
        }
    }
    if (faults > 1)
        return false;
    return true;
}
bool the_diference_is_just_capital_and_lower_alphabetics (string a,string b)
{
    int lenght_a = a.length();
    int lenght_b = b.length();
    if (lenght_a != lenght_b)
        return false;
    for (int i = 0 ; i < lenght_a ; i++)
    {
        if (a[i] != b[i])
        {
            if (a[i] > b[i])
            {
                a[i] = a[i] - 32;
                if (a[i] != b[i])
                    return false;
            }
            if (b[i] > a[i])
            {
                b[i] = b[i] - 32;
                if (a[i] != b[i])
                    return false;
            }
        }
    }
    return true;
}
bool just_include_number (string s)
{
    int lenght = s.length();
    for (int i = 0 ; i < lenght ; i++)
        if (s[i] < '0' || s[i] > '9')
            return false;
    return true;
}
string setayeaval (string data)
{
    string s;
    for (int i = 0 ; i <= 2 ; i++)
        s += data[i];
    return s;
}
string edame_setayeaval (string data,int lenght)
{
    string s;
    for (int i = 3 ; i < lenght ; i++)
        s += data[i];
    return s;
}
string hashtayeaval (string data)
{
    string s;
    for (int i = 0 ; i <= 7 ; i++)
        s += data[i];
    return s;
}
string edame_hashtayeaval (string data,int lenght)
{
    string s;
    for (int i = 8 ; i < lenght ; i++)
        s += data[i];
    return s;
}
string edame_hashtayeaval_bejoz_natije (string data,int lenght)
{
    string s;
    for (int i = 11; i < lenght ; i++)
        s += data[i];
    return s;
}
string nohtayeaval (string data)
{
    string s;
    for (int i = 0 ; i <= 8 ; i++)
        s += data[i];
    return s;
}
string edame_nohtayeaval (string data,int lenght)
{
    string s;
    for (int i = 9 ; i < lenght ; i++)
        s += data[i];
    return s;
}
string edame_nohtayeaval_bejoz_natije (string data,int lenght)
{
    string s;
    for (int i = 12; i < lenght ; i++)
        s += data[i];
    return s;
}
string dahtayeaval (string data)
{
    string s;
    for (int i = 0 ; i <= 9 ; i++)
        s += data[i];
    return s;
}
string edame_dahtayeaval (string data,int lenght)
{
    string s;
    for (int i = 10 ; i < lenght ; i++)
        s += data[i];
    return s;
}
string edame_dahtayeaval_bejoz_natije (string data,int lenght)
{
    string s;
    for (int i = 13; i < lenght ; i++)
        s += data[i];
    return s;
}
bool acceptable_bazandast (string str)
{
    int lenght = str.length();
    if (lenght == 8 && the_diference_is_just_one_less_character(str,bazandast))
        return true;
    if (lenght == 9 && the_diference_is_just_capital_and_lower_alphabetics(str, bazandast))
        return true;
    if (lenght == 9 && equal_lenght_but_just_one_diference(str, bazandast))
        return true;
    if (lenght == 10 && the_diference_is_just_one_add_character(str, bazandast))
        return true;
    return false;
}
bool acceptable_mibare (string str)
{
    int lenght = str.length();
    if (lenght == 5 && the_diference_is_just_one_less_character(str,mibare))
        return true;
    if (lenght == 6 && the_diference_is_just_capital_and_lower_alphabetics(str, mibare))
        return true;
    if (lenght == 6 && equal_lenght_but_just_one_diference(str, mibare))
        return true;
    if (lenght == 7 && the_diference_is_just_one_add_character(str, mibare))
        return true;
    return false;
}
bool acceptable_mosavi (string str)
{
    int lenght = str.length();
    if (lenght == 5 && the_diference_is_just_one_less_character(str,mosavi))
        return true;
    if (lenght == 6 && the_diference_is_just_capital_and_lower_alphabetics(str,mosavi))
        return true;
    if (lenght == 6 && equal_lenght_but_just_one_diference(str,mosavi))
        return true;
    if (lenght == 7 && the_diference_is_just_one_add_character(str,mosavi))
        return true;
    return false;
}
bool nameteam_bazandast_form (string team,string first8ta,string first9ta,string first10ta,string edame8ta,string edame9ta,string edame10ta)
{
    if (the_diference_is_just_one_less_character(first8ta,team) && acceptable_bazandast(edame8ta))
        return true;
    if (the_diference_is_just_capital_and_lower_alphabetics(first9ta,team) && acceptable_bazandast(edame9ta))
        return true;
    if (equal_lenght_but_just_one_diference(first9ta,team) && acceptable_bazandast(edame9ta))
        return true;
    if (the_diference_is_just_one_add_character(first10ta,team) && acceptable_bazandast(edame10ta))
        return true;
    return false;
}
void plusplus (int &a,int &b,int &c)
{
    a++;
    b++;
    c++;
}
void PlusEqual (float &a,int b,float &c,int d)
{
    a += b;
    c += d;
}
bool is_that_mean_perspolis_wins (string data,int lenght,int &p_w,int &e_w,int &m_p_s,int &m_e_s,float &p_g,float &e_g)
{
    string first8ta = hashtayeaval(data);
    string first9ta = nohtayeaval(data);
    string first10ta = dahtayeaval(data);
    string edame3ta = edame_setayeaval(data,lenght);
    string edame8ta = edame_hashtayeaval(data,lenght);
    string edame9ta = edame_nohtayeaval(data,lenght);
    string edame10ta = edame_dahtayeaval(data,lenght);
    string edame8ta_bejoz_natije = edame_hashtayeaval_bejoz_natije(data,lenght);
    string edame9ta_bejoz_natije = edame_nohtayeaval_bejoz_natije(data,lenght);
    string edame10ta_bejoz_natije = edame_dahtayeaval_bejoz_natije(data,lenght);
    int x_3taee = static_cast<int>(data[0]) - 48;
    int y_3taee = static_cast<int>(data[2]) - 48;
    int x_8taee = static_cast<int>(data[8]) - 48;
    int y_8taee = static_cast<int>(data[10]) - 48;
    int x_9taee = static_cast<int>(data[9]) - 48;
    int y_9taee = static_cast<int>(data[11]) - 48;
    int x_10taee = static_cast<int>(data[10]) - 48;
    int y_10taee = static_cast<int>(data[12]) - 48;
    int maximum_3 = max(x_3taee,y_3taee);
    int maximum_8 = max(x_8taee,y_8taee);
    int maximum_9 = max(x_9taee,y_9taee);
    int maximum_10 = max(x_10taee,y_10taee);
    int minimum_3 = min(x_3taee,y_3taee);
    int minimum_8 = min(x_8taee,y_8taee);
    int minimum_9 = min(x_9taee,y_9taee);
    int minimum_10 = min(x_10taee,y_10taee);
    if (number_dash_number(data,0) && data[0] != data[2])
    {
        if (the_diference_is_just_one_less_character(edame3ta,perspolis))
        {
            PlusEqual(p_g, maximum_3, e_g, minimum_3);
            plusplus(p_w,m_e_s,m_p_s);
            return true;
        }
        if (the_diference_is_just_capital_and_lower_alphabetics(edame3ta,perspolis))
        {
            PlusEqual(p_g, maximum_3, e_g, minimum_3);
            plusplus(p_w,m_e_s,m_p_s);
            return true;
        }
        if (equal_lenght_but_just_one_diference(edame3ta,perspolis))
        {
            PlusEqual(p_g, maximum_3, e_g, minimum_3);
            plusplus(p_w,m_e_s,m_p_s);
            return true;
        }
        if (the_diference_is_just_one_add_character(edame3ta,perspolis))
        {
            PlusEqual(p_g, maximum_3, e_g, minimum_3);
            plusplus(p_w,m_e_s,m_p_s);
            return true;
        }
    }
    else
    {
        if (the_diference_is_just_one_less_character(first8ta,perspolis) && number_dash_number(data,8) && data[8] != data[10] && acceptable_mibare(edame8ta_bejoz_natije))
        {
            PlusEqual(p_g, maximum_8, e_g, minimum_8);
            plusplus(p_w,m_e_s,m_p_s);
            return true;
        }
        if (the_diference_is_just_capital_and_lower_alphabetics(first9ta,perspolis) && number_dash_number(data,9) && data[9] != data[11] && acceptable_mibare(edame9ta_bejoz_natije))
        {
            PlusEqual(p_g, maximum_9, e_g, minimum_9);
            plusplus(p_w,m_e_s,m_p_s);
            return true;
        }
        if (equal_lenght_but_just_one_diference(first9ta,perspolis) && number_dash_number(data,9) && data[9] != data[11] && acceptable_mibare(edame9ta_bejoz_natije))
        {
            PlusEqual(p_g, maximum_9, e_g, minimum_9);
            plusplus(p_w,m_e_s,m_p_s);
            return true;
        }
        if (the_diference_is_just_one_add_character(first10ta,perspolis) && number_dash_number(data,10) && data[10] != data[12] && acceptable_mibare(edame10ta_bejoz_natije))
        {
            PlusEqual(p_g, maximum_10, e_g, minimum_10);
            plusplus(p_w,m_e_s,m_p_s);
            return true;
        }
        if (nameteam_bazandast_form(perspolis, first8ta, first9ta, first10ta, edame8ta, edame9ta, edame10ta))
        {
            e_w++;
            return true;
        }
    }
    return false;
}
bool is_that_mean_esteghlal_wins (string data,int lenght,int &e_w,int &p_w,int &m_e_s,int &m_p_s,float &e_g,float &p_g)
{
    string first8ta = hashtayeaval(data);
    string first9ta = nohtayeaval(data);
    string first10ta = dahtayeaval(data);
    string edame3ta = edame_setayeaval(data,lenght);
    string edame8ta = edame_hashtayeaval(data,lenght);
    string edame9ta = edame_nohtayeaval(data,lenght);
    string edame10ta = edame_dahtayeaval(data,lenght);
    string edame8ta_bejoz_natije = edame_hashtayeaval_bejoz_natije(data,lenght);
    string edame9ta_bejoz_natije = edame_nohtayeaval_bejoz_natije(data,lenght);
    string edame10ta_bejoz_natije = edame_dahtayeaval_bejoz_natije(data,lenght);
    int x_3taee = static_cast<int>(data[0]) - 48;
    int y_3taee = static_cast<int>(data[2]) - 48;
    int x_8taee = static_cast<int>(data[8]) - 48;
    int y_8taee = static_cast<int>(data[10]) - 48;
    int x_9taee = static_cast<int>(data[9]) - 48;
    int y_9taee = static_cast<int>(data[11]) - 48;
    int x_10taee = static_cast<int>(data[10]) - 48;
    int y_10taee = static_cast<int>(data[12]) - 48;
    int maximum_3 = max(x_3taee,y_3taee);
    int maximum_8 = max(x_8taee,y_8taee);
    int maximum_9 = max(x_9taee,y_9taee);
    int maximum_10 = max(x_10taee,y_10taee);
    int minimum_3 = min(x_3taee,y_3taee);
    int minimum_8 = min(x_8taee,y_8taee);
    int minimum_9 = min(x_9taee,y_9taee);
    int minimum_10 = min(x_10taee,y_10taee);
    if (number_dash_number(data,0) && data[0] != data[2])
    {
        if (the_diference_is_just_one_less_character(edame3ta,esteghlal))
        {
            PlusEqual(e_g, maximum_3, p_g, minimum_3);
            plusplus(e_w,m_e_s,m_p_s);
            return true;
        }
        if (the_diference_is_just_capital_and_lower_alphabetics(edame3ta,esteghlal))
        {
            PlusEqual(e_g, maximum_3, p_g, minimum_3);
            plusplus(e_w,m_e_s,m_p_s);
            return true;
        }
        if (equal_lenght_but_just_one_diference(edame3ta,esteghlal))
        {
            PlusEqual(e_g, maximum_3, p_g, minimum_3);
            plusplus(e_w,m_e_s,m_p_s);
            return true;
        }
        if (the_diference_is_just_one_add_character(edame3ta,esteghlal))
        {
            PlusEqual(e_g, maximum_3, p_g, minimum_3);
            plusplus(e_w,m_e_s,m_p_s);
            return true;
        }
    }
    else
    {
        if (the_diference_is_just_one_less_character(first8ta,esteghlal) && number_dash_number(data,8) && data[8] != data[10] && acceptable_mibare(edame8ta_bejoz_natije))
        {
            PlusEqual(e_g, maximum_8, p_g, minimum_8);
            plusplus(e_w,m_e_s,m_p_s);
            return true;
        }
        if (the_diference_is_just_capital_and_lower_alphabetics(first9ta,esteghlal) && number_dash_number(data,9) && data[9] != data[11] && acceptable_mibare(edame9ta_bejoz_natije))
        {
            PlusEqual(e_g, maximum_9, p_g, minimum_9);
            plusplus(e_w,m_e_s,m_p_s);
            return true;
        }
        if (equal_lenght_but_just_one_diference(first9ta,esteghlal) && number_dash_number(data,9) && data[9] != data[11] && acceptable_mibare(edame9ta_bejoz_natije))
        {
            PlusEqual(e_g, maximum_9, p_g, minimum_9);
            plusplus(e_w,m_e_s,m_p_s);
            return true;
        }
        if (the_diference_is_just_one_add_character(first10ta,esteghlal) && number_dash_number(data,10) && data[10] != data[12] && acceptable_mibare(edame10ta_bejoz_natije))
        {
            PlusEqual(e_g, maximum_10, p_g, minimum_10);
            plusplus(e_w,m_e_s,m_p_s);
            return true;
        }
        if (nameteam_bazandast_form(esteghlal, first8ta, first9ta, first10ta, edame8ta, edame9ta, edame10ta))
        {
            p_w++;
            return true;
        }
    }
    return false;
}
bool is_that_mean_draw (string data,int lenght,int &draws,int &m_p_s,int &m_e_s,float &p_g,float &e_g)
{
    string equal = "=";
    if (lenght == 1 && data == equal)
    {
        draws++;
        return true;
    }
    if (lenght == 2 && (data[0] == '=' || data[1] == '='))
    {
        draws++;
        return true;
    }
    if (acceptable_mosavi(data))
    {
        draws++;
        return true;
    }
    if (number_dash_number(data,0) && data[0] == data[2])
    {
        int x = static_cast<int>(data[0]) - 48;
        if (lenght == 3)
        {
            PlusEqual(e_g, x, p_g, x);
            plusplus(draws,m_e_s,m_p_s);
            return true;
        }
        string str = edame_setayeaval(data, lenght);
        if (acceptable_mosavi(str))
        {
            PlusEqual(e_g, x, p_g, x);
            plusplus(draws,m_e_s,m_p_s);
            return true;
        }
    }
    return false;
}
void read_and_procses_messages(int &p_w,int &d,int &e_w,float &p_g,float &e_g,int &m_p_s,int &m_e_s,float &t_m,float &u_m)
{
    string data;
    fstream results;
    results.open("results.txt");
    while (getline(results,data,'\n'))
    {
        t_m++;
        data = delete_space(data);
        delete_point_and_attention_symbol(data);
        int lenght = data.length();
        is_that_mean_perspolis_wins(data,lenght,p_w,e_w,m_p_s,m_e_s,p_g,e_g);
        is_that_mean_esteghlal_wins(data,lenght,e_w,p_w,m_e_s,m_p_s,e_g,p_g);
        is_that_mean_draw(data,lenght,d,m_p_s,m_e_s,p_g,e_g);
    }
    u_m = t_m - p_w - e_w - d;
    results.close();
}
void View_results ()
{
    int p_w = 0,d = 0,e_w = 0;
    float p_g = 0,e_g = 0;
    int m_p_s = 0,m_e_s = 0;
    float t_m = 0,u_m = 0;
    /* p_w = perspolis wins , d = draws , e_w = esteghlal wins , p_g = perspolis goals ,e_g = esteghlal goals */
    /* m_p_s = matches_perspolis_scored , m_e_s = matches_esteghlal_scored , t_m = total messages , u_m = unknown messages */
    read_and_procses_messages(p_w,d,e_w,p_g,e_g,m_p_s,m_e_s,t_m,u_m);
    float average_perspolis_goals = p_g / m_p_s;
    float average_esteghlal_goals = e_g / m_e_s;
    cout << "Total messages : " << t_m << endl ;
    cout << perspolis << " win messages : " << p_w << "\t" << p_w * 100 / t_m << " %" << endl ;
    cout << "Draw messages : " << d << "\t" << d * 100 / t_m << " %"  << endl ;
    cout << esteghlal << " win messages : " << e_w << "\t" << e_w * 100 / t_m << " %" << endl ;
    cout << "Unknown messages : " << u_m << "\t" << u_m * 100 / t_m << " %" << endl ;
    cout << perspolis << " goals : " << p_g << endl;
    cout << "The matches that " << perspolis << " scored : " << m_p_s << endl;
    cout << "Average of " << perspolis << " goals ( per match ) : " << average_perspolis_goals << endl;
    cout << esteghlal << " goals : " << e_g << endl;
    cout << "The matches that " << esteghlal << " scored : " << m_e_s << endl;
    cout << "Average of " << esteghlal << " goals ( per match ) : " << average_esteghlal_goals << endl;
}
int main()
{
   View_results();
}

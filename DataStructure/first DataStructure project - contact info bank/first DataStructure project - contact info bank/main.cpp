#include <iostream>
#include <fstream>
#include<stdlib.h>
using namespace std;
class Bank_of_contacts
{
private:
    fstream file;
    struct data_node
    {
        string value;
        short type = 3;
        data_node *next;
    };
    struct property_node
    {
        string title;
        short type = 2;
        property_node *next;
        data_node *down_data;
        property_node *down_property;
    };
    struct contact_node
    {
        string name;
        short type = 1;
        contact_node *next;
        property_node *down;
    };
    struct handmade_node
    {
        int depth_of_property;
        property_node *address_of_property;
        handmade_node *pervious;
        handmade_node *next;
    };
    class linklist_for_property
    {
    public:
        int size;
        handmade_node *first;
        handmade_node *last;
        handmade_node *new_handmade;
        linklist_for_property()
        {
            size = 0;
        }
        ~linklist_for_property()
        {
            size = 0;
            while (size > 0)
                pop();
        }
        void manual_destructor()
        {
            while (size > 0)
                pop();
        }
        void situation()
        {
            handmade_node *p = first;
            int n = size;
            cout << "size of stack is " << size << endl;
            if (n == 0)
                cout << "stack is empty" << endl;
            while (n > 0)
            {
                if (p->address_of_property)
                    cout << p->address_of_property->title << endl;
                if (p->next)
                    p = p->next;
                n--;
            }
        }
        void push(property_node *input, int depth)
        {
            if (size > 0)
            {
                new_handmade = new handmade_node;
                new_handmade->pervious = last;
                new_handmade->address_of_property = input;
                new_handmade->depth_of_property = depth;
                new_handmade->next = NULL;
                last->next = new_handmade;
                last = new_handmade;
                new_handmade = NULL;
            }
            else
            {
                first = new handmade_node;
                first->address_of_property = input;
                first->depth_of_property = depth;
                first->next = NULL;
                last = first;
            }
            ++size;
        }
        void pop()
        {
            if (size > 0)
            {
                if (size == 1)
                {
                    first = NULL;
                    last = NULL;
                }
                if (size == 2)
                {
                    first->next = NULL;
                    last = first;
                }
                else if (size > 2)
                    last = last->pervious;
            }
            --size;
        }
        property_node *get_last_cell()
        {
            if (size == 1)
                return first->address_of_property;
            else if (last->address_of_property)
                return last->address_of_property;
            return NULL;
        }
        int get_last_cell_depth()
        {
            if (size > 0)
            {
                if (size == 1)
                    return first->depth_of_property;
                else
                    return last->depth_of_property;
            }
            return -1;
        }
    };

public:
    short control_mojaz_value_of_baze(int min, int number, int max)
    {
        while ((number < min) || (number > max))
        {
            cout << "value is incorrect . that should be between";
            cout << " " << min << " and " << max << endl;
            cout << "Try again : ";
            cin >> number;
        }
        return number;
    }
    void find_contact_address_by_name(string inputed_name,contact_node *firstcontact)
    {
        if (inputed_name == firstcontact->name)
            contact_address = firstcontact;
        else if ((firstcontact->next) && (!contact_address))
        {
            perv_address_of_defined_contact = firstcontact;
            find_contact_address_by_name(inputed_name, firstcontact->next);
        }
    }
    float find_dash_place_in_line(string str) // == find depth of each line on file
    {
        unsigned long int lenght = str.length();
        for (int i = 0; i <= lenght; i++)
            if (str[i] == '-')
                return i;
        return 1.01;
    }
    void add_property_to_down_of_a_contact(property_node *new_property, contact_node *contact_address) // added to depth = 1
    {
        if (contact_address->down)
            new_property->next = contact_address->down;
        contact_address->down = new_property;
    }
    void add_property_to_a_down_of_a_upper_property(property_node *&upper_property, property_node *&new_property)
    {
        if (upper_property->down_property)
            new_property->next = upper_property->down_property;
        upper_property->down_property = new_property;
    }
    short find_type_of_file_line(string file_line, int start_of_word)
    {
        bool is_contact = true;
        bool is_property = true;
        bool is_value = true;
        for (int i = 1, j = 0; i < 9; i++, j++)
            if (file_line[i] != contact_word[j])
            {
                is_contact = false;
                break;
            }
        if (is_contact)
            return 1;
        for (int i = start_of_word + 1, j = 0; i < start_of_word + 11; i++, j++)
            if (file_line[i] != property_word[j])
            {
                is_property = false;
                break;
            }
        if (is_property)
            return 2;
        for (int i = start_of_word + 1, j = 0; i < start_of_word + 8; i++, j++)
            if (file_line[i] != value_word[j])
            {
                is_value = false;
                break;
            }
        if (is_value)
            return 3;
        return 0; // always , will not run
    }
    // READ FROM FILE
    void read_from_file()
    {
        string fileline;
        int current_depth;
        short current_type = 0;
        if (getline(file, fileline, '\n'))
        {
            current_depth = find_dash_place_in_line(fileline);
            current_type = find_type_of_file_line(fileline, current_depth);
            read_from_file();
        }
        if (current_type == 1)
        {
            current_contact_node = new contact_node;
            unsigned long int lenght = fileline.length();
            for (int i = current_depth + 10; i < lenght; i++)
                current_contact_node->name = current_contact_node->name + fileline[i];
            current_contact_node->type = 1;
            if (type_of_last_processed_node == 2)
            {
                current_contact_node->down = stack.get_last_cell();
                stack.pop();
            }
            current_contact_node->next = last_contact;
            last_contact = current_contact_node;
            stack.manual_destructor();
        }
        else if (current_type == 2)
        {
            current_property_node = new property_node;
            unsigned long int lenght = fileline.length();
            for (int i = current_depth + 11; i < lenght; i++)
                current_property_node->title = current_property_node->title + fileline[i];
            current_property_node->type = 2;
            if (type_of_last_processed_node == 3)
            {
                current_property_node->down_data = last_data;
                if (stack.get_last_cell_depth() == current_depth)
                {
                    current_property_node->next = stack.get_last_cell();
                    stack.pop();
                }
                stack.push(current_property_node, current_depth);
            }
            else
            {
                if (stack.get_last_cell_depth() == current_depth + 1)
                {
                    current_property_node->down_property = stack.get_last_cell();
                    stack.pop();
                    if (stack.get_last_cell_depth() == current_depth)
                    {
                        current_property_node->next = stack.get_last_cell();
                        stack.pop();
                        stack.push(current_property_node, current_depth);
                    }
                    else
                        stack.push(current_property_node, current_depth);
                }
                else if (stack.get_last_cell_depth() == current_depth)
                {
                    current_property_node->next = stack.get_last_cell();
                    stack.pop();
                    stack.push(current_property_node, current_depth);
                }
                else if (stack.get_last_cell_depth() < current_depth)
                    stack.push(current_property_node, current_depth);
            }
            last_data = NULL;
        }
        else if (current_type == 3)
        {
            current_data_node = new data_node;
            unsigned long int lenght = fileline.length();
            for (int i = current_depth + 8; i < lenght; i++)
                current_data_node->value = current_data_node->value + fileline[i];
            current_data_node->type = 3;
            if ((last_data != NULL))
                if (last_data_node_depth == current_depth)
                    current_data_node->next = last_data;
            last_data = current_data_node;
            last_data_node_depth = current_depth;
        }
        type_of_last_processed_node = current_type;
        address_of_firstcontact = last_contact;
    }
    // WRITE ON FILE
    void write_on_file(data_node *a, short uppernode_depth)
    {
        if (a)
        {
            short depth = uppernode_depth + 1;
            for (int i = 1; i <= depth; i++)
                file << " ";
            file << "-";
            file << "Value: " << a->value << endl;
            if (a->next)
                write_on_file(a->next, depth - 1);
        }
    }
    void write_on_file(property_node *a, short uppernode_depth)
    {
        if (a)
        {
            short depth = uppernode_depth + 1;
            for (int i = 1; i <= depth; i++)
                file << " ";
            file << "-";
            file << "Property: " << a->title << endl;
            if (a->down_property)
                write_on_file(a->down_property, depth);
            if (a->down_data)
                write_on_file(a->down_data, depth);
            if (a->next)
                write_on_file(a->next, depth - 1);
        }
    }
    void write_on_file(contact_node *a)
    {
        if (a)
        {
            file << "-";
            file << "Contact: " << a->name << endl;
            if (a->down)
                write_on_file(a->down,0);
            if (a->next)
                write_on_file(a->next);
        }
    }
    // DELETE VALUE/PROPERTY
    void delete_value()
    {
        string firstname, lastname, value_of_data;
        cout << "enter contact firstname : ";
        cin >> firstname;
        cout << "enter contact lastname : ";
        cin >> lastname;
        firstname = firstname + " " + lastname;
        contact_address = NULL;
        find_contact_address_by_name(firstname,address_of_firstcontact);
        if (contact_address == NULL)
            cout << "there is not a contact with this info" << endl;
        else
        {
            cout << "enter name of value that you want to delete : ";
            cin >> value_of_data;
            found_value = false;
            perv_address_of_defined_property = NULL;
            number_of_same_values = 0;
            is_this_value_exist_for_a_defined_contact(contact_address -> down,value_of_data,0);
            if (found_value == false)
                cout << "there is not this info" << endl;
            else
                choose_between_same_values();
        }
    }
    void delete_property()
    {
        string firstname, lastname, property_title;
        contact_address = NULL;
        cout << "enter contact firstname : ";
        cin >> firstname;
        cout << "enter contact lastname : ";
        cin >> lastname;
        firstname = firstname + " " + lastname;
        find_contact_address_by_name(firstname, address_of_firstcontact);
        if (contact_address == NULL)
            cout << "there is not a contact with this info" << endl;
        else
        {
            cout << "enter name of property that you want to delete : ";
            cin >> property_title;
            found_property = false;
            is_this_property_exist_for_a_defined_contact(contact_address->down, property_title);
            if (found_property == false)
                cout << "there is not this info" << endl;
            else
            {
                choose_between_same_property_titles_and_find_property_features();
                delete_list(address_of_defined_property->down_data);     // correct ? if null ?
                delete_list(address_of_defined_property->down_property); // correct ? if null ?
                if (perv_address_of_defined_property)
                    perv_address_of_defined_property->next = address_of_defined_property->next;
                else if (perv_address_of_defined_property == NULL)
                    upper_address_of_defined_property->down_property = address_of_defined_property->next;
                delete address_of_defined_property;
            }
        }
    }
    // ADD VALUE/PROPERTY
    void add_value()
    {
        string firstname, lastname, value_of_data, upper_property_title;
        data_node *new_data_node = new data_node;
        contact_address = NULL;
        cout << "enter contact firstname : ";
        cin >> firstname;
        cout << "enter contact lastname : ";
        cin >> lastname;
        firstname = firstname + " " + lastname;
        find_contact_address_by_name(firstname, address_of_firstcontact);
        if (contact_address == NULL)
            cout << "there is not a contact with this info" << endl;
        else
        {
            cout << "enter name of value that you want to add : ";
            cin >> value_of_data;
            found_value = false;
            is_this_value_exist_for_a_defined_contact(contact_address -> down,value_of_data,0);
            if (found_value == true)
                cout << "there is same value for this info" << endl;
            else
            {
                cout << "enter name of upper property :";
                cin >> upper_property_title;
                found_property = false;
                is_this_property_exist_for_a_defined_contact(contact_address->down, upper_property_title);
                if (found_property == false)
                    cout << "there is not a property with this info for the contact" << endl;
                else
                {
                    new_data_node->value = value_of_data;
                    new_data_node->type = 3;
                    if (upper_address_of_defined_property->down_data == NULL)
                        upper_address_of_defined_property->down_data = new_data_node;
                    else
                    {
                        // that will attend to the first data node of list in defined upper property
                        new_data_node->next = upper_address_of_defined_property->down_data->next;
                        upper_address_of_defined_property->down_data->next = new_data_node;
                    }
                }
            }
        }
    }
    void add_property()
    {
        short choice;
        bool control = true;
        string firstname, lastname, property_title, upper_property_title;
        contact_address = NULL;
        property_node *new_property = new property_node;
        property_node *upper_property = NULL;
        cout << "enter contact firstname : ";
        cin >> firstname;
        cout << "enter contact lastname : ";
        cin >> lastname;
        firstname = firstname + " " + lastname;
        find_contact_address_by_name(firstname,address_of_firstcontact);
        if (contact_address == NULL)
            cout << "there is not a contact with this info" << endl;
        else
        {
            cout << "enter name of property that you want to add : ";
            cin >> property_title;
            found_property = false;
            is_this_property_exist_for_a_defined_contact(contact_address->down, property_title);
            if (found_property == true)
            {
                if (same_property_title_same_upper_property(upper_property_title))
                {
                    control = false;
                    properties.manual_destructor();
                    address_of_perv_properties.manual_destructor();
                    address_of_upper_properties.manual_destructor();
                }
            }
            if (control)
            {
                cout << "is it a property for a property ? \n1.yes\t2.no\nyour choose : ";
                cin >> choice;
                choice = control_mojaz_value_of_baze(1, choice, 2);
                while (choice == 1)
                {
                    cout << "enter name of upper property :";
                    cin >> upper_property_title;
                    if (upper_property_title == property_title)
                        break;
                    found_property = false;
                    is_this_property_exist_for_a_defined_contact(contact_address->down, upper_property_title);
                    if (found_property == false)
                        cout << "there is not a property with this info for the contact" << endl;
                    else
                    {
                        upper_property = address_of_defined_property;
                        break;
                    }
                }
                if (choice == 1)
                    add_property_to_a_down_of_a_upper_property(upper_property, new_property);
                else if (choice == 2)
                    add_property_to_down_of_a_contact(new_property, contact_address);
                new_property->title = property_title;
                new_property->type = 2;
            }
        }
    }
    void add_contact()
    {
        string firstname, lastname;
        contact_address = NULL;
        cout << "enter contact firstname : ";
        cin >> firstname;
        cout << "enter contact lastname : ";
        cin >> lastname;
        firstname = firstname + " " + lastname;
        find_contact_address_by_name(firstname, address_of_firstcontact);
        if (contact_address != NULL)
            cout << "there is a contact with same info" << endl;
        else
        {
            contact_address = new contact_node;
            contact_address->name = firstname;
            contact_address->type = 1;
            contact_address->down = NULL;
         // if (address_of_firstcontact)
                contact_address -> next = address_of_firstcontact;
            address_of_firstcontact = contact_address;
        }
    }
    void delete_contact()
    {
        string firstname, lastname;
        contact_address = NULL;
        cout << "enter contact firstname : ";
        cin >> firstname;
        cout << "enter contact lastname : ";
        cin >> lastname;
        firstname = firstname + " " + lastname;
        perv_address_of_defined_contact = NULL;
        find_contact_address_by_name(firstname, address_of_firstcontact);
        if (contact_address == NULL)
            cout << "there is not a contact with this info" << endl;
        else
        {
            if (perv_address_of_defined_contact)
                perv_address_of_defined_contact->next = contact_address->next;
            if (contact_address->down)
                delete_list(contact_address->down);
            if (address_of_firstcontact == contact_address)
                address_of_firstcontact = address_of_firstcontact -> next;
            delete contact_address;
            contact_address = NULL;
        }
    }
    // PRINT
    void print_info_for_a_contact()
    {
        string firstname, lastname;
        cout << "enter contact firstname : ";
        cin >> firstname;
        cout << "enter contact lastname : ";
        cin >> lastname;
        firstname = firstname + " " + lastname;
        contact_address = NULL;
        find_contact_address_by_name(firstname, address_of_firstcontact);
        if (contact_address)
        {
            cout << "-";
            cout << "Contact : " << contact_address -> name << endl;
            if (contact_address -> down)
                print(contact_address -> down,0);
        }
        else
            cout << "there is not a contact with this info" << endl;
    }
    void print(data_node *a, short uppernode_depth) // uppernode_depth : because of print spaces before data_node (see file)
    {
        short depth = uppernode_depth + 1;
        if (a != NULL)
        {
            for (int i = 1; i <= depth; i++)
                cout << " ";
            cout << "-";
            cout << "Value : " << a->value << endl;
            if (a->next)
                print(a->next, depth - 1);
        }
    }
    void print(property_node *a, short uppernode_depth)
    {
        short depth = uppernode_depth + 1;
        if (a != NULL)
        {
            for (int i = 1; i <= depth; i++)
                cout << " ";
            cout << "-";
            cout << "Property : " << a->title << endl;
            if (a->down_property)
                print(a->down_property, depth);
            if (a->down_data)
                print(a->down_data, depth);
            if (a->next)
                print(a->next, depth - 1);
        }
    }
    void print(contact_node *a)
    {
        if (a != NULL)
        {
            cout << "-";
            cout << "Contact : " << a->name << endl;
            if (a->down)
                print(a->down, 0);
            if (a->next)
                print(a->next);
        }
    }
    bool same_property_title_same_upper_property(string upper_property_title)
    {
        property_node *a = address_of_upper_properties.first->address_of_property;
        while (a != NULL)
        {
            if (a->title == upper_property_title)
                return true;
            a = a->next;
        }
        return false;
    }
    void choose_between_same_property_titles_and_find_property_features()
    {
        if (properties.size > 0)
        {
            property_node *a = properties.first->address_of_property;
            property_node *b = address_of_upper_properties.first->address_of_property;
            property_node *c = address_of_perv_properties.first->address_of_property;
            short choice;
            int n = properties.size;
            for (int i = 1; i <= n; i++)
            {
                cout << i << ".";
                cout << "title of property :" << a->title << endl;
                cout << "upper property : ";
                if (b)
                    cout << b->title << endl;
                else
                    cout << "null" << endl;
                cout << "pervious property : ";
                if (c)
                    cout << c->title << endl;
                else
                    cout << "null" << endl;
                a = a->next;
                b = b->next;
                c = c->next;
            }
            cin >> choice;
            choice = control_mojaz_value_of_baze(1, choice, n);
            handmade_node *prop = properties.first;
            handmade_node *up = address_of_upper_properties.first;
            handmade_node *perv = address_of_perv_properties.first;
            short t = 1;
            while (t <= n)
            {
                if (choice == prop->depth_of_property)
                {
                    address_of_defined_property = prop->address_of_property;
                    perv_address_of_defined_property = perv->address_of_property;
                    upper_address_of_defined_property = up->address_of_property;
                    properties.manual_destructor();
                    address_of_upper_properties.manual_destructor();
                    address_of_perv_properties.manual_destructor();
                    break;
                }
                prop = prop->next;
                perv = perv->next;
                up = up->next;
                t++;
            }
        }
    }
    // IS THE PROPERTY EXIST
    void is_this_property_exist_for_a_defined_contact(property_node *first_property_of_contact, string input_title,short uppernode_depth)
    {
        short depth = uppernode_depth + 1;
        if (first_property_of_contact->title == input_title)
        {
            found_property = true;
            properties.push(first_property_of_contact,depth);
            address_of_perv_properties.push(perv_address_of_defined_property,depth);
            address_of_upper_properties.push(upper_address_of_defined_property,depth);
        }
        if (first_property_of_contact->down_property)
        {
            address_of_perv_properties.push(NULL,depth);
            address_of_upper_properties.push(upper_address_of_defined_property,depth);
            properties.push(first_property_of_contact,depth);
            is_this_value_exist_print_it(first_property_of_contact->down_property, depth);
        }
        if (first_property_of_contact->next)
        {
            while ((properties.last) && (properties.last -> depth_of_property >= depth))
                properties.pop();
            is_this_value_exist_print_it(first_property_of_contact->next, depth - 1);
        }
        
        
        
        
        
        
        
        
        
        
        
        
        if ((first_property_of_contact->down_property) && (found_property == false))
        {
            perv_address_of_defined_property = NULL;
            upper_address_of_defined_property = first_property_of_contact;
            is_this_property_exist_for_a_defined_contact(first_property_of_contact->next, input_title);
        }
        if (first_property_of_contact->next)
            if (found_property == false)
            {
                perv_address_of_defined_property = first_property_of_contact;
                is_this_property_exist_for_a_defined_contact(first_property_of_contact->down_property, input_title);
            }
    }
    // IS THE VALUE EXIST ? IF YES , PRINT IT
    void is_this_value_exist_print_it(data_node *a, short uppernode_depth)
    {
        short depth = uppernode_depth + 1;
        if (a->value == temp)
        {
            cout << number_of_same_values + 1 << "." << endl << "-Contact : " << contact_address -> name << endl;
            handmade_node * p = properties.first;
            while (p)
            {
                int n = p -> depth_of_property;
                for (int i = 1; i <= n; i++)
                    cout << " ";
                cout << "-Property : " << p -> address_of_property -> title << endl;
                p = p -> next;
            }
            for (int i = 1; i <= depth; i++)
                cout << " ";
            cout << "-Value : " << a->value << endl;
            number_of_same_values++;
        }
        else if (a->next)
            is_this_value_exist_print_it(a->next, depth - 1);
    }
    void is_this_value_exist_print_it(property_node *a, short uppernode_depth)
    {
        short depth = uppernode_depth + 1;
        if (a->down_property)
        {
            properties.push(a,depth);
            is_this_value_exist_print_it(a->down_property, depth);
        }
        if (a->down_data)
        {
            properties.push(a,depth);
            is_this_value_exist_print_it(a->down_data, depth);
        }
        if (a->next)
        {
            //depth = size of stack = depth of a and depth of a -> next
            while ((properties.last) && (properties.last -> depth_of_property >= depth))
                properties.pop();
            is_this_value_exist_print_it(a->next, depth - 1);
        }
    }
    void is_this_value_exist_print_it(contact_node *a) // input = address of first contact
    {
        contact_address = a;
        if (a->down)
            is_this_value_exist_print_it(a->down, 0);
        if (a->next)
        {
            properties.manual_destructor();
            is_this_value_exist_print_it(a->next);
        }
    }
    // IS THE VALUE EXIST
    void is_this_value_exist_for_a_defined_contact(data_node *a,string input_value,short uppernode_depth)
    {
        if (a)
        {
            short depth = uppernode_depth + 1;
            if (a -> value == input_value)
            {
                found_value = true;
                current_property_node = new property_node;
                current_property_node -> down_data = a;
                if (!perv_address_of_defined_property)
                    perv_address_of_defined_property = new property_node;
                address_of_perv_properties.push(perv_address_of_defined_property,depth);
                stack.push(current_property_node,depth);
                address_of_upper_properties.push(properties.last->address_of_property,depth);
                cout << number_of_same_values + 1 << "." << endl;
                handmade_node * p = properties.first;
                while (p)
                {
                    int n = p -> depth_of_property;
                    for (int i = 1; i <= n; i++)
                        cout << " ";
                    cout << "-Property : " << p -> address_of_property -> title << endl;
                    p = p -> next;
                }
                for (int i = 1; i <= depth; i++)
                    cout << " ";
                cout << "-Value : " << a->value << endl;
                ++number_of_same_values;
            }
            else if (a->next)
            {
                perv_address_of_defined_property = new property_node;
                perv_address_of_defined_property -> down_data = a;
                is_this_value_exist_for_a_defined_contact(a->next,input_value,depth - 1);
            }
        }
    }
    void is_this_value_exist_for_a_defined_contact(property_node *first_property_for_this_contact,string input_value,short uppernode_depth)
    {
        if (first_property_for_this_contact)
        {
            short depth = uppernode_depth + 1;
            if (first_property_for_this_contact->down_property)
            {
                properties.push(first_property_for_this_contact,depth);
                is_this_value_exist_for_a_defined_contact(first_property_for_this_contact->down_property,input_value,depth);
            }
            if (first_property_for_this_contact->down_data)
            {
                properties.push(first_property_for_this_contact,depth);
                is_this_value_exist_for_a_defined_contact(first_property_for_this_contact->down_data,input_value,depth);
            }
            if (first_property_for_this_contact->next)
            {
                while ((properties.last) && (properties.last -> depth_of_property >= depth))
                    properties.pop();
                is_this_value_exist_for_a_defined_contact(first_property_for_this_contact->next,input_value,depth - 1);
            }
        }
    }
    void choose_between_same_values ()
    {
        if (stack.size > 1)
        {
            short choice;
            cout << "Enter your choose " << endl;
            cin >> choice;
            choice = control_mojaz_value_of_baze(1, choice, number_of_same_values);
            while (stack.size != choice)
            {
                stack.pop();
                address_of_perv_properties.pop();
                address_of_upper_properties.pop();
            }
        }
        if (address_of_perv_properties.last -> address_of_property -> down_data)
        {
            address_of_perv_properties.last -> address_of_property -> down_data -> next = stack.last -> address_of_property -> down_data -> next;
            address_of_upper_properties.last -> address_of_property -> down_data = address_of_perv_properties.last -> address_of_property -> down_data;
        }
        else
            address_of_upper_properties.last -> address_of_property -> down_data = stack.last -> address_of_property -> down_data -> next;
        perv_address_of_defined_data = NULL;
        upper_address_of_defined_data = NULL;
        address_of_defined_data = NULL;
        stack.manual_destructor();
        address_of_perv_properties.manual_destructor();
        address_of_upper_properties.manual_destructor();
    }
    // DELETE LIST
    void delete_list(data_node *a)
    {
        if (a)
        {
            if (a->next)
                delete_list(a->next);
            a = NULL;
        }
    }
    void delete_list(property_node *a)
    {
        if (a)
        {
            if (a->down_property)
                delete_list(a->down_property);
           else if (a->down_data)
                delete_list(a->down_data);
            if (a->next)
                delete_list(a->next);
            a = NULL;
        }
    }
    void delete_list(contact_node *a)
    {
        if (a)
        {
            if (a->down)
                delete_list(a->down);
            if (a->next)
                delete_list(a->next);
            if (a == address_of_firstcontact)
            {
                delete address_of_firstcontact;
                address_of_firstcontact = NULL;
            }
            a = NULL;
        }
    }
    // CLIENT SIDE
    short options()
    {
        cout << "-----Add-----" << endl;
        cout << "1.Add contact" << endl;
        cout << "2.Add property" << endl;
        cout << "3.Add value" << endl;
        cout << "----Delete-----" << endl;
        cout << "4.Delete all" << endl;
        cout << "5.Delete contact" << endl;
        cout << "6.Delete property" << endl;
        cout << "7.Delete value" << endl;
        cout << "-----View-----" << endl;
        cout << "8.View all" << endl;
        cout << "9.View contact's info" << endl;
        cout << "10.View value" << endl;
        cout << "-----Exit-----" << endl;
        cout << "11.Close programme" << endl;
        cout << endl;
        cout << "Your choose : ";
        short choice;
        cin >> choice;
        return choice;
    }
    void menu()
    {
        file.open("bank.txt");
        read_from_file();
        file.close();
        while (true)
        {
            short request = options();
            if (request == 11)
                break;
            switch (request)
            {
            case 1:
                add_contact();
                file.open("bank.txt");
                write_on_file(address_of_firstcontact);
                file.close();
                break;
            case 2:
                add_property();
                remove("bank.txt");
                file.open("bank.txt");
                write_on_file(address_of_firstcontact);
                file.close();
                break;
            case 3:
                add_value();
                file.open("bank.txt");
                write_on_file(address_of_firstcontact);
                file.close();
                break;
            case 4:
                delete_list(address_of_firstcontact);
                cout << "list deleted sucessfully" << endl;
                //remove("bank.txt");
                file.open("bank.txt");
                write_on_file(address_of_firstcontact);
                file.close();
                break;
            case 5:
                delete_contact();
                file.open("bank.txt");
                write_on_file(address_of_firstcontact);
                file.close();
                break;
            case 6:
                delete_property();
                file.open("bank.txt");
                write_on_file(address_of_firstcontact);
                file.close();
            case 7:
                delete_value();
                file.open("bank.txt");
                write_on_file(address_of_firstcontact);
                file.close();
                break;
            case 8:
                print(address_of_firstcontact);
                cout << "list printed sucessfully" << endl;
                break;
            case 9:
                print_info_for_a_contact();
                break;
            case 10:
                cout << "enter value : ";
                cin >> temp;
                number_of_same_values = 0;
                is_this_value_exist_print_it(address_of_firstcontact);
                break;
            default:
                cout << "inputed value is not correct ... ";
                cout << "have attention to options and try again " << endl
                     << endl;
                break;
            }
            if ((request > 0) && (request < 11))
            {
                string str;
                cout << "Press a character key to back main menu" << endl;
                cin >> str;
            }
            system("clear");
            system("cls");
        }
    }

protected:
    data_node *current_data_node;
    contact_node *current_contact_node;
    property_node *current_property_node;
    data_node *last_data;
    contact_node *last_contact;
    int last_data_node_depth;
    int type_of_last_processed_node;
    linklist_for_property stack;
    int number_of_same_values = 0;
    contact_node *address_of_firstcontact = NULL;
    contact_node * contact_address;
    contact_node *perv_address_of_defined_contact = NULL;
    bool found_value = false;
    bool found_property = false;
    string temp;
    const string contact_word = "Contact: ";
    const string property_word = "Property: ";
    const string value_word = "Value: ";
    property_node *upper_address_of_defined_property = NULL;
    property_node *perv_address_of_defined_property = NULL;
    property_node *address_of_defined_property = NULL;
    property_node *upper_address_of_defined_data = NULL;
    data_node *perv_address_of_defined_data = NULL;
    data_node *address_of_defined_data = NULL;
    linklist_for_property properties;
    linklist_for_property address_of_upper_properties;
    linklist_for_property address_of_perv_properties;
};
int main()
{
    Bank_of_contacts a;
    a.menu();
}

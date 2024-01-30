#include <iostream>
#include <fstream>
using namespace std;
// STRUCTERS
struct point
{
    double x = NULL;
    double y = NULL;
};
struct region
{
    point topLeft, botRight;
};
struct node
{
    region reg;
    point pos;
    string name;
    node * father = NULL;
    node * nw = NULL;
    node * ne = NULL;
    node * sw = NULL;
    node * se = NULL;
};
struct Tree
{
    node* root;
};
// CLASS POINTS_TREE
class points_tree
{
private:
    Tree big_tree;
public:
    fstream file;
    unsigned int number_of_points;
    void set_big_tree_root_info ()
    {
        file.open("point.txt");
        big_tree.root = new node;
        if (getline(file,big_tree.root->name,' '))
            big_tree.root -> reg.topLeft.x = stod(big_tree.root->name);
        if (getline(file,big_tree.root->name,' '))
            big_tree.root -> reg.topLeft.y = stod(big_tree.root->name);
        if (getline(file,big_tree.root->name,' '))
            big_tree.root -> reg.botRight.x = stod(big_tree.root->name);
        if (getline(file,big_tree.root->name,'\n'))
            big_tree.root -> reg.botRight.y = stod(big_tree.root->name);
        getline(file,big_tree.root->name,'\n');
        number_of_points = stoi(big_tree.root->name);
        big_tree.root -> name = "";
    }
    bool can_region_dived (region r)
    {
        if (r.topLeft.y - r.botRight.y < 2.0)
            return false;
        return true;
    }
    bool find_posibility_nw_direction_in_father_node (point * point,node * &possible_node)
    {
        if (can_point_be_in_nw_of_this_node(*point,possible_node))
        {
            node * current = new node;
            update_region_for_nw_child(current,possible_node);
            if (can_region_dived(possible_node -> reg))
            {
                if (possible_node -> nw == NULL)
                {
                    possible_node -> nw = new node;
                    possible_node -> nw -> father = possible_node;
                    possible_node -> nw -> reg.topLeft.x = current -> reg.topLeft.x;
                    possible_node -> nw -> reg.topLeft.y = current -> reg.topLeft.y;
                    possible_node -> nw -> reg.botRight.x = current -> reg.botRight.x;
                    possible_node -> nw -> reg.botRight.y = current -> reg.botRight.y;
                }
                possible_node = possible_node -> nw;
                return true;
            }
        }
    return false;
    }
    bool find_posibility_ne_direction_in_father_node (point * point,node * &possible_node)
    {
        if (can_point_be_in_ne_of_this_node(*point,possible_node))
        {
            node * current = new node;
            update_region_for_ne_child(current,possible_node);
            if (can_region_dived(possible_node -> reg))
            {
                if (possible_node -> ne == NULL)
                {
                    possible_node -> ne = new node;
                    possible_node -> ne -> father = possible_node;
                    possible_node -> ne -> reg.topLeft.x = current -> reg.topLeft.x;
                    possible_node -> ne -> reg.topLeft.y = current -> reg.topLeft.y;
                    possible_node -> ne -> reg.botRight.x = current -> reg.botRight.x;
                    possible_node -> ne -> reg.botRight.y = current -> reg.botRight.y;
                }
                possible_node = possible_node -> ne;
                return true;
            }
        }
    return false;
    }
    bool find_posibility_sw_direction_in_father_node (point * point,node * &possible_node)
    {
        if (can_point_be_in_sw_of_this_node(*point,possible_node))
        {
            node * current = new node;
            update_region_for_sw_child(current,possible_node);
            if (can_region_dived(possible_node -> reg))
            {
                if (possible_node -> sw == NULL)
                {
                    possible_node -> sw = new node;
                    possible_node -> sw -> father = possible_node;
                    possible_node -> sw -> reg.topLeft.x = current -> reg.topLeft.x;
                    possible_node -> sw -> reg.topLeft.y = current -> reg.topLeft.y;
                    possible_node -> sw -> reg.botRight.x = current -> reg.botRight.x;
                    possible_node -> sw -> reg.botRight.y = current -> reg.botRight.y;
                }
                possible_node = possible_node -> sw;
                return true;
            }
        }
    return false;
    }
    bool find_posibility_se_direction_in_father_node (point * point,node * &possible_node)
    {
            if (can_point_be_in_se_of_this_node(*point,possible_node))
            {
                node * current = new node;
                update_region_for_se_child(current,possible_node);
                if (can_region_dived(possible_node -> reg))
                {
                    if (possible_node -> se == NULL)
                    {
                        possible_node -> se = new node;
                        possible_node -> se -> father = possible_node;
                        possible_node -> se -> reg.topLeft.x = current -> reg.topLeft.x;
                        possible_node -> se -> reg.topLeft.y = current -> reg.topLeft.y;
                        possible_node -> se -> reg.botRight.x = current -> reg.botRight.x;
                        possible_node -> se -> reg.botRight.y = current -> reg.botRight.y;
                    }
                    possible_node = possible_node -> se;
                    return true;
                }
            }
        return false;
    }
    void find_empty_possible_node (bool &does_point_insert,point * p,string name,node * &possible_node,bool &all_regions_checked)
    {
        does_point_insert = false;
        if (find_posibility_nw_direction_in_father_node(p,possible_node))
            insertation(p,name,possible_node,does_point_insert,all_regions_checked);
        if (does_point_insert == false)
            if (find_posibility_ne_direction_in_father_node(p,possible_node))
                insertation(p,name,possible_node,does_point_insert,all_regions_checked);
        if (does_point_insert == false)
            if (find_posibility_sw_direction_in_father_node(p,possible_node))
                insertation(p,name,possible_node,does_point_insert,all_regions_checked);
        if (does_point_insert == false)
            if (find_posibility_se_direction_in_father_node(p,possible_node))
                insertation(p,name,possible_node,does_point_insert,all_regions_checked);
        all_regions_checked = true;
    }
    void insertation (point * new_point,string name,node * possible_node,bool &does_point_insert,bool &all_regions_checked)
    {
        static point * old_point = new point;
        static string old_name;
        switch (kind_of_node(possible_node))
        {
            case 1:
                if (is_node_fulled(possible_node) == false)
                {
                    possible_node -> name = name;
                    possible_node -> pos.x = new_point -> x;
                    possible_node -> pos.y = new_point -> y;
                    does_point_insert = true;
                }
                else if (all_regions_checked == true)
                {
                    cout << "all possible regions are fulled ." << endl;
                    cout << "can not insert this point" << endl;
                    cout << "Name of point : " << name << "\t";
                    cout << "X : " << new_point -> x << "\t" << "Y : " << new_point -> y << endl;
                }
                break;
            case 2:
                if (can_region_dived(possible_node->reg))
                {
                    old_point -> x = possible_node -> pos.x;
                    old_point -> y = possible_node -> pos.y;
                    old_name = possible_node -> name;
                    possible_node -> pos.x = NULL;
                    possible_node -> pos.y = NULL;
                    possible_node -> name = "";
                    find_empty_possible_node(does_point_insert,old_point,old_name,possible_node,all_regions_checked);
                    possible_node = possible_node -> father;
                    find_empty_possible_node(does_point_insert,new_point,name,possible_node,all_regions_checked);
                }
                else
                {
                    cout << "all possible regions are fulled ." << endl;
                    cout << "can not insert this point" << endl;
                    cout << "Name of point : " << name << "\t";
                    cout << "X : " << new_point -> x << "\t" << "Y : " << new_point -> y << endl;
                }
                break;
            case 3:
                find_empty_possible_node(does_point_insert,new_point,name,possible_node,all_regions_checked);
            }
    }
    void read_from_file()
    {
        bool does_point_insert = false;
        bool all_regions_checked = false;
        node * possible_node = big_tree.root;
        point * new_point = NULL;
        int unprocessed_points = number_of_points;
        string name,x,y;
        while (unprocessed_points > 0)
        {
            getline(file,name,' ');
            getline(file,x,' ');
            getline(file,y,'\n');
            if ((is_x_acceptable_in_this_region(stod(x),big_tree.root->reg) == false)|| (is_y_acceptable_in_this_region(stod(y),big_tree.root->reg) == false))
                cout << "point is out of defined region" << endl;
            else
            {
                new_point = new point;
                new_point -> x = stod(x);
                new_point -> y = stod(y);
                insertation(new_point,name,possible_node,does_point_insert,all_regions_checked);
            }
            unprocessed_points--;
            does_point_insert = false;
            all_regions_checked = false;
            possible_node = big_tree.root;
        }
        file.close();
    }
    short kind_of_node (node * node)
    {
        if (node -> nw == NULL)
            if (node -> ne == NULL)
                if (node -> sw == NULL)
                    if (node -> se == NULL)
                    {
                        if (node -> name == "")
                            return 1; // completley null
                        else if (node -> name != "")
                            return 2; // without children but has just a point
                        else
                            cout << "mored nashenakhte !!!!!!!!!!!!!!!!" << endl;
                    }
        return 3; // atleast has a child in one of his directions
    }
    void d ()
    {
        file.open("point.txt");
        string s;
        while (getline(file,s, '\n'))
            cout << s << endl;
        file.close();
    }
    void pre_write_on_file ()
    {
        if (big_tree.root)
        {
            file.open("point.txt");
            
            file.close();
        }
    }
    void write_on_file (node * current)
    {
        d();
        if (current)
        {
            if (current == big_tree.root)
            {
                file << big_tree.root->reg.topLeft.x << " " << big_tree.root->reg.topLeft.y << " ";
                file << big_tree.root->reg.botRight.x << " " << big_tree.root->reg.botRight.y << endl;
                file << number_of_points << endl;
            }
            else
            {
                if (kind_of_node(current) == 2)
                    file << current -> name << " " << current -> pos.x << " " << current -> pos.y << endl;
                if (current -> nw)
                    write_on_file(current -> nw);
                if (current -> ne)
                    write_on_file(current -> ne);
                if (current -> sw)
                    write_on_file(current -> sw);
                if (current -> se)
                    write_on_file(current -> se);
            }
        }
    }
    void update_region_for_nw_child (node * child,node * father)
    {
        child -> reg.topLeft = father -> reg.topLeft;
        child -> reg.botRight.x = ((father -> reg.botRight.x - father -> reg.topLeft.x) / 2) + father -> reg.topLeft.x;
        child -> reg.botRight.y = ((father -> reg.topLeft.y - father -> reg.botRight.y) / 2) + father -> reg.botRight.y;
    }
    void update_region_for_ne_child (node * child,node * father)
    {
        child -> reg.topLeft.x = ((father -> reg.botRight.x - father -> reg.topLeft.x) / 2) + father -> reg.topLeft.x;
        child -> reg.topLeft.y = (father -> reg.topLeft.y - father -> reg.botRight.y) + father -> reg.botRight.y;
        child -> reg.botRight.x = (father -> reg.botRight.x - father -> reg.topLeft.x) + father -> reg.topLeft.x;
        child -> reg.botRight.y = ((father -> reg.topLeft.y - father -> reg.botRight.y) / 2) + father -> reg.botRight.y;
    }
    void update_region_for_sw_child (node * child,node * father)
    {
        child -> reg.topLeft.x = father -> reg.topLeft.x;
        child -> reg.topLeft.y = ((father -> reg.topLeft.y - father -> reg.botRight.y) / 2) + father -> reg.botRight.y;
        child -> reg.botRight.x = ((father -> reg.botRight.x - father -> reg.topLeft.x) / 2) + father -> reg.topLeft.x;
        child -> reg.botRight.y = father -> reg.botRight.y;
    }
    void update_region_for_se_child (node * child,node * father)
    {
        child -> reg.topLeft.x = ((father -> reg.botRight.x - father -> reg.topLeft.x) / 2) + father -> reg.topLeft.x;
        child -> reg.topLeft.y = ((father -> reg.topLeft.y - father -> reg.botRight.y) / 2) + father -> reg.botRight.y;
        child -> reg.botRight = father -> reg.botRight;
    }
    bool is_y_acceptable_in_this_region (double y,region r)
    {
        if (r.botRight.x == 0)
            if (r.botRight.y == 0)
                if (r.topLeft.x == 0)
                    if (r.topLeft.y == 0)
                        return true;
        if (y > r.topLeft.y)
            return false;
        return true;
    }
    bool is_x_acceptable_in_this_region (double x,region r)
    {
        if (r.botRight.x == 0)
            if (r.botRight.y == 0)
                if (r.topLeft.x == 0)
                    if (r.topLeft.y == 0)
                        return true;
        if (x > r.botRight.x)
            return false;
        return true;
    }
    bool are_points_equal (point a,point b)
    {
        if (a.x == b.x)
            if (a.y == b.y)
                return true;
        return false;
    }
    bool is_node_fulled (node* current)
    {
        if (current->reg.topLeft.y - current->reg.botRight.y < 1.0)
            return true;
        return false;
    }
    bool can_point_be_in_nw_of_this_node (point p,node* node)
    {
        if (node->reg.topLeft.x <= p.x)
            if ((((node -> reg.botRight.x - node -> reg.topLeft.x) / 2) + node -> reg.topLeft.x) >= p.x)
                if ((((node -> reg.topLeft.y - node -> reg.botRight.y) / 2) + node -> reg.botRight.y) <= p.y)
                    if (node->reg.topLeft.y >= p.y)
                        return true;
        return false;
    }
    bool can_point_be_in_ne_of_this_node (point p,node* node)
    {
        if ((((node -> reg.botRight.x - node -> reg.topLeft.x) / 2) + node -> reg.topLeft.x) <= p.x)
            if (node->reg.botRight.x >= p.x)
                if ((((node -> reg.topLeft.y - node -> reg.botRight.y) / 2) + node -> reg.botRight.y) <= p.y)
                    if (node->reg.topLeft.y >= p.y)
                        return true;
        return false;
    }
    bool can_point_be_in_sw_of_this_node (point p,node* node)
    {
        if (node->reg.topLeft.x <= p.x)
            if ((((node -> reg.botRight.x - node -> reg.topLeft.x) / 2) + node -> reg.topLeft.x) >= p.x)
                if (node->reg.botRight.y <= p.y)
                    if ((((node -> reg.topLeft.y - node -> reg.botRight.y) / 2) + node -> reg.botRight.y) >= p.y)
                        return true;
        return false;
    }
    bool can_point_be_in_se_of_this_node (point p,node* node)
    {
        if ((((node -> reg.botRight.x - node -> reg.topLeft.x) / 2) + node -> reg.topLeft.x) <= p.x)
            if (node->reg.botRight.x >= p.x)
                if (node->reg.botRight.y <= p.y)
                    if ((((node -> reg.topLeft.y - node -> reg.botRight.y) / 2) + node -> reg.botRight.y) >= p.y)
                        return true;
        return false;
    }
    bool find_possible_node_nw (point * point,node * &possible_node)
    {
        if (can_point_be_in_nw_of_this_node(*point,possible_node))
        {
            if (possible_node -> nw)
            {
                update_region_for_nw_child(possible_node -> nw,possible_node);
                possible_node = possible_node -> nw;
                return true;
            }
        }
        return false;
    }
    bool find_possible_node_ne (point * point,node * &possible_node)
    {
        if (can_point_be_in_ne_of_this_node(*point,possible_node))
        {
            if (possible_node -> ne)
            {
                update_region_for_ne_child(possible_node -> ne,possible_node);
                possible_node = possible_node -> ne;
                return true;
            }
        }
        return false;
    }
    bool find_possible_node_sw (point * point,node * &possible_node)
    {
        if (can_point_be_in_sw_of_this_node(*point,possible_node))
        {
            if (possible_node -> sw)
            {
                update_region_for_sw_child(possible_node -> sw,possible_node);
                possible_node = possible_node -> sw;
                return true;
            }
        }
        return false;
    }
    bool find_possible_node_se (point * point,node * &possible_node)
    {
        if (can_point_be_in_se_of_this_node(*point,possible_node))
        {
            if (possible_node -> se)
            {
                update_region_for_se_child(possible_node -> se,possible_node);
                possible_node = possible_node -> se;
                return true;
            }
        }
        return false;
    }
    void find_possible_node (point * p,node * &possible_node,node * &address)
    {
        if (find_possible_node_nw(p,possible_node))
            find_node_address_of_point(*p,possible_node,address);
        else if (find_possible_node_ne(p,possible_node))
            find_node_address_of_point(*p,possible_node,address);
        else if (find_possible_node_sw(p,possible_node))
            find_node_address_of_point(*p,possible_node,address);
        else if (find_possible_node_se(p,possible_node))
            find_node_address_of_point(*p,possible_node,address);
    }
    void find_node_address_of_point (point input_point,node * possible_node,node * &address)
    {
        if (possible_node)
        {
            switch (kind_of_node(possible_node))
            {
                case 2:
                    if (possible_node -> pos.x == input_point.x)
                        if (possible_node -> pos.y == input_point.y)
                            address = possible_node;
                    break;
                case 3:
                    find_possible_node(&input_point,possible_node,address);
            }
        }
    }
    double get_good_x (point p)
    {
        if (big_tree.root)
            cout << "valid X is from " << big_tree.root->reg.topLeft.x << " to " << big_tree.root->reg.botRight.x << endl;
        cout << "Enter x : ";
        cin >> p.x;
        while (!is_x_acceptable_in_this_region(p.x,big_tree.root->reg))
        {
            cout << "X value is out of defined region" << endl;
            cout << "try again for x : ";
            cin >> p.x;
        }
        return p.x;
    }
    double get_good_y (point p)
    {
        if (big_tree.root)
            cout << "valid Y is from " << big_tree.root->reg.botRight.y << " to " << big_tree.root->reg.topLeft.y << endl;
        cout << "Enter y : ";
        cin >> p.y;
        while (!is_y_acceptable_in_this_region(p.y,big_tree.root->reg))
        {
            cout << "Y value is out of defined region" << endl;
            cout << "try again for y : ";
            cin >> p.y;
        }
        return p.y;
    }
    void add_point ()
    {
        point p;
        p.x = get_good_x(p);
        p.y = get_good_y(p);
        node * address = NULL;
        find_node_address_of_point(p,big_tree.root,address);
        if (address != NULL)
            cout << "there is SAME point with this info" << endl;
        else
        {
            cout << "Enter name of point : ";
            string name;
            cin >> name;
            bool does_point_insert = false;
            bool all_regions_checked = false;
            node * possible_node = big_tree.root;
            insertation(&p,name,possible_node,does_point_insert,all_regions_checked);
            cout << "The point was added sucessfully" << endl;
            number_of_points++;
        }
    }
    void delete_all_points (node* &root)
    {
        if (root)
        {
            if (root -> nw)
                delete_all_points(root->nw);
            if (root -> ne)
                delete_all_points(root->ne);
            if (root -> sw)
                delete_all_points(root->sw);
            if (root -> se)
                delete_all_points(root->se);
            delete root;
            root = NULL;
        }
    }
    void update_father_after_delete_point (node * &address)
    {
        node * father = address -> father;
        if (father -> nw == address)
            father -> nw = NULL;
        else if (father -> ne == address)
            father -> ne = NULL;
        else if (father -> sw == address)
            father -> sw = NULL;
        else if (father -> se == address)
            father -> se = NULL;
        delete address;
        address = NULL;
    }
    void delete_point ()
    {
        if (kind_of_node(big_tree.root) != 1) // root is not null or empty
        {
            point p;
            p.x = get_good_x(p);
            p.y = get_good_y(p);
            node * address = NULL;
            find_node_address_of_point(p,big_tree.root,address);
            if (address == NULL)
                cout << "there is NOT a point with this info" << endl;
            else
            {
                update_father_after_delete_point(address);
                number_of_points--;
            }
        }
        else
            cout << "list is empty" << endl;
    }
    int print_point (node * current,short depth,unsigned int chaped_points)
    {
        depth++;
        for (int i = 1; i <= depth; i++)
            cout << " ";
        cout << chaped_points << ".1 point number " << endl;
        depth++;
        for (int i = 1; i <= depth; i++)
            cout << " ";
        cout << chaped_points << endl;
        depth--;
        for (int i = 1; i <= depth; i++)
            cout << " ";
        cout << chaped_points << ".2 point position " << endl;
        depth++;
        for (int i = 1; i <= depth; i++)
            cout << " ";
        cout << "X : " << current -> pos.x << endl;
        for (int i = 1; i <= depth; i++)
            cout << " ";
        cout << "Y : " << current -> pos.y << endl;
        return chaped_points;
    }
    int print_name (node * current,short depth,unsigned int chaped_points)
    {
        depth++;
        for (int i = 1; i <= depth; i++)
            cout << " ";
        cout << chaped_points << ".3 point name " << endl;
        depth++;
        for (int i = 1; i <= depth; i++)
            cout << " ";
        cout << current -> name << endl;
        return chaped_points;
    }
    void print_region (node * current,short depth)
    {
        for (int i = 1; i <= depth; i++)
            cout << " ";
        cout << "-node region" << endl;
        depth++;
        for (int i = 1; i <= depth; i++)
            cout << " ";
        cout << "X of topleft  : " << current -> reg.topLeft.x << endl;
        for (int i = 1; i <= depth; i++)
            cout << " ";
        cout << "Y of topleft  : " << current -> reg.topLeft.y << endl;
        for (int i = 1; i <= depth; i++)
            cout << " ";
        cout << "X of botright : " << current -> reg.botRight.x << endl;
        for (int i = 1; i <= depth; i++)
            cout << " ";
        cout << "Y of botright : " << current -> reg.botRight.y << endl;
        depth--;
        for (int i = 1; i <= depth; i++)
            cout << " ";
        cout << "-node type" << endl;
        depth++;
        for (int i = 1; i <= depth; i++)
            cout << " ";
        if (current -> father == NULL)
            cout << "root" << endl;
        else if (kind_of_node(current) == 2)
            cout << "leaf" << endl;
        else if (kind_of_node(current) == 3)
            cout << "interior" << endl;
        depth--;
        if (current -> father)
        {
            node * father = current -> father;
            for (int i = 1; i <= depth; i++)
                cout << " ";
            cout << "-node direction" << endl;
            depth++;
            for (int i = 1; i <= depth; i++)
                cout << " ";
            if (father -> nw == current)
                cout << "nw" << endl;
            else if (father -> ne == current)
                cout << "ne" << endl;
            else if (father -> sw == current)
                cout << "sw" << endl;
            else if (father -> se == current)
                cout << "se" << endl;
        }
    }
    void view_all_points (node * current,unsigned int &chaped_points)
    {
        if (current)
        {
            if (kind_of_node(current) == 2)
            {
                chaped_points++;
                chaped_points = print_point(current,0,chaped_points);
                chaped_points = print_name(current,0,chaped_points);
            }
            else if (kind_of_node(current) == 3)
            {
                if (current -> nw)
                    view_all_points(current -> nw,chaped_points);
                if (current -> ne)
                    view_all_points(current -> ne,chaped_points);
                if (current -> sw)
                    view_all_points(current -> sw,chaped_points);
                if (current -> se)
                    view_all_points(current -> se,chaped_points);
            }
        }
    }
    void view_all_nodes (node * current,short depth,unsigned int &chaped_points)
    {
        if (current)
        {
            print_region(current,depth);
            if (kind_of_node(current) == 2)
            {
                chaped_points++;
                chaped_points = print_point(current,depth,chaped_points);
                chaped_points = print_name(current,depth,chaped_points);
            }
            else if (kind_of_node(current) == 3)
            {
                if (current -> nw)
                {
                    depth++;
                    view_all_nodes(current -> nw,depth,chaped_points);
                }
                if (current -> ne)
                {
                    depth++;
                    view_all_nodes(current -> ne,depth+1,chaped_points);
                }
                if (current -> sw)
                {
                    depth++;
                    view_all_nodes(current -> sw,depth+1,chaped_points);
                }
                if (current -> se)
                {
                    depth++;
                    view_all_nodes(current -> se,depth+1,chaped_points);
                }
            }
        }
    }
    void view_point_info ()
    {
        point p;
        p.x = get_good_x(p);
        p.y = get_good_y(p);
        node * address = NULL;
        find_node_address_of_point(p,big_tree.root,address);
        if (address == NULL)
            cout << "there is not a point with this info" << endl;
        else
        {
            print_point(address,0,1);
            print_name(address,0,1);
        }
    }
    void update_file ()
    {
        //pre_write_on_file();
        cout << "before" << endl;
        d();
        file.open("point.txt");
        write_on_file(big_tree.root);
        file.close();
        cout << "last" << endl;
        d();
    }
    short options()
    {
        cout << "-----Add-----" << endl;
        cout << "1.Add point" << endl;
        cout << "----Delete-----" << endl;
        cout << "2.Delete all points" << endl;
        cout << "3.Delete point" << endl;
        cout << "-----View-----" << endl;
        cout << "4.View all points" << endl;
        cout << "5.View all nodes" << endl;
        cout << "6.View a point's info" << endl;
        cout << "-----Exit-----" << endl;
        cout << "7.Close programme" << endl;
        cout << endl;
        cout << "Your choose : ";
        short choice;
        cin >> choice;
        cout << endl;
        return choice;
    }
    void menu()
    {
        region * r = new region;
        set_big_tree_root_info();
        read_from_file();
        unsigned int chaped_points;
        while (true)
        {
            short request = options();
            if (request == 7)
                break;
            switch (request)
            {
            case 1:
                    add_point();
                    update_file();
                break;
            case 2:
                    if (big_tree.root)
                    {
                        r -> topLeft.x = big_tree.root->reg.topLeft.x;
                        r -> topLeft.y = big_tree.root->reg.topLeft.y;
                        r -> botRight.x = big_tree.root->reg.botRight.x;
                        r -> botRight.y = big_tree.root->reg.botRight.y;
                    }
                    delete_all_points(big_tree.root);
                    number_of_points = 0;
                    big_tree.root = new node;
                    big_tree.root -> reg.topLeft.x = r -> topLeft.x;
                    big_tree.root -> reg.botRight.x = r -> botRight.x;
                    big_tree.root -> reg.topLeft.y = r -> topLeft.y;
                    big_tree.root -> reg.botRight.y = r -> botRight.y;
                    update_file();
                break;
            case 3:
                    delete_point();
                    update_file();
                break;
            case 4:
                    chaped_points = 0;
                    view_all_points(big_tree.root,chaped_points);
                break;
            case 5:
                    chaped_points = 0;
                    view_all_nodes(big_tree.root,0,chaped_points);
                break;
            case 6:
                    view_point_info();
                break;
            default:
                cout << "inputed value is not correct ... ";
                cout << "have attention to options and try again " << endl
                     << endl;
                break;
            }
            if ((request > 0) && (request < 7))
            {
                string str;
                cout << "Press a character key to back main menu" << endl;
                cin >> str;
            }
        }
    }
};
int main()
{
    points_tree t;
    t.menu();
}

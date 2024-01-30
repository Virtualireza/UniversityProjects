#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
int main()
{
    cout << "KHOSH AMADID" << endl;
    char shomaremobile[11];
    int mojoodi[15];
    int gheimat[15];
    fstream mojoodi_f;
    fstream gheimat_f;
    mojoodi_f.open("/Users/alirezamoghadaspour/desktop/mojoodi.txt");
    for (int i=0;i<15;i++)
        mojoodi_f >> mojoodi[i];
    mojoodi_f.close();
    gheimat_f.open("/Users/alirezamoghadaspour/desktop/gheimat.txt");
    for (int i=0;i<15;i++)
        gheimat_f >> gheimat[i];
    gheimat_f.close();
    while (true)
    {
        cout << "1)HESAB KARBARI\n2)KALAHAYE MOJOOD\n3)MODIR SITE\n4)BASTAN BARNAME\n";
        int y;
        cin >> y;
        while (y != 1 && y != 2 && y != 3 && y != 4)
        {
            cout << " LOTFAN 1 YA 2 YA 3 YA 4 RA VARED KONID ";
            cin >> y;
        }
        if (y == 4)
            return 0;
        while (y == 1)
        {
            cout << "1)SABT NAME\n2)VIRAYESH ETELA'AT KARBARI\n3)VAZIAT HESAB KARBARI\n4)BAZGASHT BE MENU GHABL\n5)BASTAN BARNAME" << endl;
            fstream sabtname;
            fstream shomare;
            int a;
            cin >> a;
            while (a != 1 && a != 2 && a != 3 && a != 4 && a != 5)
            {
                cout << "LOTFAN 1 YA 2 YA 3 YA 4 YA 5 RA VARED KONID\n";
                cin >> a;
            }
            while (a == 1)
            {
                cout << "NAME KHOD RA VARED KONID :";
                char firstname[30] ;
                cin.ignore();
                cin.getline(firstname, 30);
                cout << "NAME KHANEVADEGI KHOD RA VARED KONID :";
                char lastname[40];
                cin.getline(lastname, 40);
                cout << "ADDRESS RA VARED KONID :";
                char address[100];
                cin.getline(address, 100);
                sabtname.open("/Users/alirezamoghadaspour/desktop/customer.txt", ios::app);
                sabtname << firstname <<'\t'<< lastname <<'\t'<< address<<'\t' ;
                while (true)
                {
                    cout << "SHOMARE MOBILE KHOD RA DOBARE BEDOON \"0\" VARED KONID :" << endl;
                    cout << "+98";
                    int a;
                    a=0;
                cin >> shomaremobile;
                shomare.open("/Users/alirezamoghadaspour/desktop/shomare.txt",ios::app);
                char shomare_mobile_ghabli[11];
                while (!shomare.eof())
                {
                    shomare >> shomare_mobile_ghabli;
                    shomare << endl;
                    //choon shomare_mobile_ghbli 10 char bishtar nemgire , pas faghat 10 char aval file miran tooye shomare_mobile_ghabli va baadesh ham ke endl mishe
                    if (strcmp(shomaremobile, shomare_mobile_ghabli) == 0)
                    {
                        cout << "IN SHOMARE GHABLAN DAR SYSTEM SABT SHODE AST...SHOMARE MOBILE DIGARI VARED KONID\n";
                        a=1;
                        break;
                    }
                }
                if (strlen(shomaremobile) != 10)
                {
                    cout << "TEDAD ARGHAM VARED SHODE SAHIH NIST\n";
                    a=1;
                }
                for (int t = 0; t < 10; t++)
                {
                    if (shomaremobile[t] < '0' || shomaremobile[t]>'9')
                    {
                        cout << "SHOMARE MOBILE KHOD RA DOBARE BEIN \"0\" TA \"9\" VARED KONID :" << endl;
                        a=1;
                        break;
                    }
                    if (shomaremobile[0] == '0')
                    {
                        cout << "SHOMARE MOBILE KHOD RA DOBARE BEDOON \"0\" DAR EBTEDAYE AN VARED KONID :" << endl;
                        a=1;
                        break;
                    }
                }
                    if (a==0)
                    {
                        //???????????????????????????????????????chrra khat zir kar nemikone ????????????????????????????
                        shomare.open("/Users/alirezamoghadaspour/desktop/shomare.txt", ios::app);
                        shomare << shomaremobile << endl;
                        shomare.close();
                        sabtname << shomaremobile << endl;
                        sabtname.close();
                        break;
                    }
                    if (a==1)
                        continue;
                    shomare.close();
            }
                cout << "SABT NAM SHOMA BA MOVAFAGHIAT ANJAM SHOD !!!\n1)BAZGASHT BE MENU GHABL\n2)BASTAN BARNAME\n";
                fstream tedad;
                int count;
                tedad.open("/Users/alirezamoghadaspour/desktop/tedad.txt");
                //???????????????????????????????????????chrra khat zir kar nemikone ????????????????????????????
                tedad >> count;
                ++count;
                tedad << count;
                tedad.close();
                int aa;
                cin >> aa;
                while (aa != 1 && aa != 2)
                {
                    cout << " LOTFAN 1 YA 2 RA VARED KONID ";
                    cin >> aa;
                }
                if (aa == 1)
                    break;
                else
                    return 0;
            }
            while (a == 2)
            {
                cout << "1)EDAME\n2)BAZGASHT BE MENU GHABL\n3)BASTAN BARNAME\n";
                int ab;
                cin >> ab;
                while (ab != 1 && ab != 2 && ab != 3)
                {
                    cout << " LOTFAN 1 YA 2 YA 3 RA VARED KONID "; cin >> ab;
                }
                if (ab == 3)
                    return 0;
                if (ab == 2)
                    break;
                while (ab == 1)
                {
                    while (true)
                    {
                    cout << "SHOMARE MOBILE GHABLI KHOD RA BEDOON \"0\" VARED KONID :" << endl;
                    cout << "+98";
                        int a;
                        a=0;
                    cin >> shomaremobile;
                    if (strlen(shomaremobile) != 10)
                    {
                        cout << "TEDAD ARGHAM VARED SHODE SAHIH NIST\n";
                        a=1;
                    }
                    for (int t = 0; t < 10; t++)
                    {
                        if (shomaremobile[t] < '0' || shomaremobile[t]>'9')
                        {
                            cout << "SHOMARE MOBILE GHABLI KHOD RA DOBARE BEIN \"0\" TA \"9\" VARED KONID :" << endl;
                            a=1;
                            break;
                        }
                        if (shomaremobile[0] == '0')
                        {
                            cout << "SHOMARE MOBILE GHABLI KHOD RA DOBARE BEDOON \"0\" DAR EBTEDAYE AN VARED KONID :" << endl;
                            a=1;
                            break;
                        }
                    }
                    shomare.open("/Users/alirezamoghadaspour/desktop/shomare.txt", ios::app);
                    char shomare_mobile_ghabli[11];
                    char address[100];
                    char firstname[30];
                    char lastname[40];
                        if (a==0)
                    while (!shomare.eof())
                    {
                        shomare >> shomare_mobile_ghabli;
                        shomare << endl;
                        if (strcmp(shomare_mobile_ghabli, shomaremobile) == 0)
                        {
                            shomare << shomare_mobile_ghabli << endl;
                            cout << "NAME KHOD RA VARED KONID :";
                            cin.ignore();
                            cin.getline(firstname, 30);
                            cout << firstname << endl;
                            cout << "NAME KHANEVADEGI KHOD RA VARED KONID :";
                            cin.getline(lastname, 40);
                            cout << lastname << endl;
                            cout << "ADDRESS RA VARED KONID :";
                            cin.getline(address, 100);
                            cout << address << endl;
                            sabtname.open("/Users/alirezamoghadaspour/desktop/customer.txt", ios::app);
                            sabtname << firstname << lastname << address << shomaremobile << endl;
                            sabtname.close();
                            shomare.open("/Users/alirezamoghadaspour/desktop/shomare.txt", ios::app);
                            shomare << shomaremobile;
                            shomare.close();
                            cout << "ETELA'AT JADID BA MOVAFAGHIAT SABT SHOD\n";
                            return 0;
                        }
                        else continue;
                    }
                        shomare.close();
                        if (a==0)
                            cout << "BA IN SHOMARE MOBILE SABT NAME ANJAM NASHODE\nBE MENU GHABLI ENTEGHAL DADE SHODID\n";
                    }
                    }
                    //IN RO BAYAD EZAFE KONAM KE ETELAAT GHABLI RO BETOONE PAK KONE
                }
            while (a == 3)
            {
                cout << "1)EDAME\n2)BAZGASHT BE MENU GHABL\n3)BASTAN BARNAME\n";
                int ac;
                cin >> ac;
                while (ac != 1 && ac != 2 && ac != 3)
                {
                    cout << " LOTFAN 1 YA 2 YA 3 RA VARED KONID ";
                    cin >> ac;
                }
                if (ac == 3)
                    return 0;
                if (ac == 2)
                    break;
                while (ac == 1)
                {
                    int i;
                    while (true)
                    {
                        i = 0;
                    cout << "SHOMARE MOBILE KHOD RA BEDOON \"0\" VARED KONID :" << endl;
                    cout << "+98";
                    char shomare_mobile_ghabli[11];
                    cin >> shomare_mobile_ghabli;
                    if (strlen(shomare_mobile_ghabli) != 10)
                        cout << "TEDAD ARGHAM VARED SHODE SAHIH NIST\n";
                    for (int t = 0; t < 10; t++)
                    {
                        if (shomare_mobile_ghabli[t] < '0' || shomare_mobile_ghabli[t]>'9')
                        {
                            cout << "SHOMARE MOBILE KHOD RA DOBARE BEIN \"0\" TA \"9\" VARED KONID :" << endl;
                            break;
                        }
                        if (shomare_mobile_ghabli[0] == '0')
                        {
                            cout << "SHOMARE MOBILE KHOD RA DOBARE BEDOON \"0\" DAR EBTEDAYE AN VARED KONID :" << endl;
                            break;
                        }
                    }
                        shomare.open("/Users/alirezamoghadaspour/desktop/shomare.txt");
                        while (!shomare.eof())
                        {
                        shomare >> shomaremobile;
                            ++i;
                    if (strcmp(shomare_mobile_ghabli, shomaremobile) != 0)
                    {
                        cout << "IN SHOMARE MOBILE SABT NAM NASHODE\n";
                        break;
                    }
                        }
                        if (strcmp(shomare_mobile_ghabli, shomaremobile) == 0)
                            break;
                }
                   /* sabtname.open("/Users/alirezamoghadaspour/desktop/customer.txt");
                    fstream bedehkari;
                    bedehkari.open("/Users/alirezamoghadaspour/desktop/bedehkar.txt");
                    cout <<"VAZIAT HESAB SHOMA : \n" ;
                    cout <<"FIRST NAME : ";
                    firstname [i];
                    cout <<"LAST NAME : ";
                    lastname [i];
                    cout <<"ADDRESS : ";
                    address [i];
                    cout <<"SHOMARE MOBILE : ";
                    cout << shomaremobile;
                    cout <<"BEDEHI : ";
                    bedehi [i];
                    sabtname.close();
                    bedehkari.close();
                    break;*/
            }
            }
            if (a == 4)
                break;
            if (a == 5)
                return 0;
        }
        while (y == 2)
        {
            //1)LAPTOPS
            cout << "\n\n  1)LAPTOPS\n";
            cout << "MACBOOK 13.3 INCH (code 1 - " << gheimat[0] << "$ - " << mojoodi[0] << "TA MOJOOD)\n";
            cout << "MACBOOK 15 INCH (code 2 - " << gheimat[1] << "$ - " << mojoodi[1] << "TA MOJOOD)\n";
            cout << "LEGION 5 (code 3 - " << gheimat[2] << "$ - " << mojoodi[2] << "TA MOJOOD)\n";
            cout << "LEGION 7 (code 4 - " << gheimat[3] << "$ - " << mojoodi[3] << "TA MOJOOD)\n";
            cout << "ZENBOOK (code 5 - " << gheimat[4] << "$ - " << mojoodi[5] << "TA MOJOOD)\n";
            //2)CONSOLE GAME
            cout << "  2)CONSOLE GAMES\n";
            cout << "PLAYSTATION 4 (code 6 - " << gheimat[5] << "$ - " << mojoodi[5] << "TA MOJOOD)\n";
            cout << "PLAYSTATION 5 (code 7 - " << gheimat[6] << "$ - " << mojoodi[6] << "TA MOJOOD)\n";
            cout << "X - BOX SERIE S (code 8 - " << gheimat[7] << "$ - " << mojoodi[7] << "TA MOJOOD)\n";
            cout << "X - BOX 360 (code 9 - " << gheimat[8] << "$ - " << mojoodi[8] << "TA MOJOOD)\n";
            cout << "NINENDO SWITCH (code 10 - " << gheimat[9] << "$ - " << mojoodi[9] << "TA MOJOOD)\n";
            //3)MOBILE PHONE
            cout << "  3)MOBILE PHONE\n";
            cout << "IPHONE 13 (code 11 - " << gheimat[10] << "$ - " << mojoodi[10] << "TA MOJOOD)\n";
            cout << "IPHONE 13 MINI (code 12 - " << gheimat[11] << "$ - " << mojoodi[11] << "TA MOJOOD)\n";
            cout << "S20 (code 13 - " << gheimat[12] << "$ - " << mojoodi[12] << "TA MOJOOD)\n";
            cout << "S20 ULTRA (code 14 - " << gheimat[13] << "$ - " << mojoodi[13] << "TA MOJOOD)\n";
            cout << "REDMI (code 15 - " << gheimat[14] << "$ - " << mojoodi[14] << "TA MOJOOD)" << "\n\n";
            cout << "1)KHARID\n3)BAZGASHT BE MENU GHABL\n4)BASTAN BARNAME\n";
            int b;
            int code_mahsool_pardakht[15];
            cin >> b;
            while (b != 1 && b != 3 && b != 4)
            {
                cout << " LOTFAN 1 YA 3 YA 4 RA VARED KONID ";
                cin >> b;
            }
            if (b == 4)
                return 0;
            if (b == 3)
                break;
            while (b == 1)
            {
                int w;
                for (w = 0; w < 15; w++)
                {
                    cout << "CODE MAHSOOL RA VARED KONID : \n";
                    cout << "20)MOSHAHEDE SOORAT HESAB VA PARDAKHT\n";
                    cin >> code_mahsool_pardakht[w];
                    if (code_mahsool_pardakht[w] == 20)
                        break;
                    while (code_mahsool_pardakht[w] <= 0 || code_mahsool_pardakht[w] > 15)
                    {
                        cout << "CODE MAHSOOL RA DOBARE VARED KONID";
                        cin >> code_mahsool_pardakht[w];
                    }
                }
                long int majmoo=0;
                int k;
                for (k = 0; k <= w; k++)
                {
                    if (code_mahsool_pardakht[k] == 1)
                    {
                        cout << "MACBOOK 13.3 INCH (code 1)";
                        majmoo += gheimat[0];
                    }
                    if (code_mahsool_pardakht[k] == 2)
                    {
                        cout << "MACBOOK 15 INCH (code 2)";
                        majmoo += gheimat[1];
                    }
                    if (code_mahsool_pardakht[k] == 3)
                    {
                        cout << "LEGION 5 (code 3)";
                        majmoo += gheimat[2];
                    }
                    if (code_mahsool_pardakht[k] == 4)
                    {
                        cout << "LEGION 7 (code 4)";
                        majmoo += gheimat[3];
                    }
                    if (code_mahsool_pardakht[k] == 5)
                    {
                        cout << "ZENBOOK (code 5)";
                        majmoo += gheimat[4];
                    }
                    if (code_mahsool_pardakht[k] == 6)
                    {
                        cout << "PLAYSTATION 4 (code 6)";
                        majmoo += gheimat[5];
                    }
                    if (code_mahsool_pardakht[k] == 7)
                    {
                        cout << "PLAYSTATION 5 (code 7)";
                        majmoo += gheimat[6];
                    }
                    if (code_mahsool_pardakht[k] == 8)
                    {
                        cout << "X - BOX SERIE S (code 8)";
                        majmoo += gheimat[7];
                    }
                    if (code_mahsool_pardakht[k] == 9)
                    {
                        cout << "X - BOX 360 (code 9)";
                        majmoo += gheimat[8];
                    }
                    if (code_mahsool_pardakht[k] == 10)
                    {
                        cout << "NINENDO SWITCH (code 10)";
                        majmoo += gheimat[9];
                    }
                    if (code_mahsool_pardakht[k] == 11)
                    {
                        cout << "IPHONE 13 (code 11)";
                        majmoo += gheimat[10];
                    }
                    if (code_mahsool_pardakht[k] == 12)
                    {
                        cout << "IPHONE 13 MINI (code 12)";
                        majmoo += gheimat[11];
                    }
                    if (code_mahsool_pardakht[k] == 13)
                    {
                        cout << "S20 (code 13)";
                        majmoo += gheimat[12];
                    }
                    if (code_mahsool_pardakht[k] == 14)
                    {
                        cout << "S20 ULTRA (code 14)";
                        majmoo += gheimat[13];
                    }
                    if (code_mahsool_pardakht[k] == 15)
                    {
                        cout << "REDMI (code 15)";
                        majmoo += gheimat[14];
                    }
                }
                cout << "\n1)TAEED SABAD KHARID\n2)EZAFE KARDAN MAHSOOL\n3)HAZF MAHSOOL\n";
                int taeed;
                cin >> taeed;
                while (taeed != 1 && taeed != 2 && taeed != 3)
                {
                    cout << "LOTFAN 1 YA 2 YA 3 RA VARED KONID\n";
                    cin >> taeed;
                }
                //if taeed==1 ke hich etefaghi nemiofte va edame midim va niazibe neveshtanesh nist
                while (taeed == 2)
                {
                    cout << "CODE MAHSOOLI KE MIKHAHEED EZAFE KONID RA VARED KONID : \n";
                    cout << "20)MOSHAHEDE SOORAT HESAB VA PARDAKHT\n";
                    int code_mahsool_ezafe;
                    cin >> code_mahsool_ezafe;
                    if (code_mahsool_ezafe == 20)
                        break;
                    while (code_mahsool_ezafe <= 0 || code_mahsool_ezafe > 15)
                    {
                        cout << "CODE MAHSOOL RA DOBARE VARED KONID";
                        cin >> code_mahsool_ezafe;
                    }
                    switch (code_mahsool_ezafe)
                    {
                    case 1:
                            cout << "MACBOOK 13.3 INCH (code 1) EZAFE SHOD";
                            majmoo += gheimat[0];
                            cout << endl;
                            break;
                    case 2:
                            cout << "MACBOOK 15 INCH (code 2) EZAFE SHOD";
                            majmoo += gheimat[1];
                            cout << endl;
                            break;
                    case 3:
                            cout << "LEGION 5 (code 3) EZAFE SHOD";
                            majmoo += gheimat[2];
                            cout << endl;
                            break;
                    case 4:
                            cout << "LEGION 7 (code 4) EZAFE SHOD";
                            majmoo += gheimat[3];
                            cout << endl;
                            break;
                    case 5:
                            cout << "ZENBOOK (code 5) EZAFE SHOD";
                            majmoo += gheimat[4];
                            cout << endl;
                            break;
                    case 6:
                            cout << "PLAYSTATION 4 (code 6) EZAFE SHOD";
                            majmoo += gheimat[5];
                            cout << endl;
                            break;
                    case 7:
                            cout << "PLAYSTATION 5 (code 7) EZAFE SHOD";
                            majmoo += gheimat[6];
                            cout << endl;
                            break;
                    case 8:
                            cout << "X - BOX SERIE S (code 8) EZAFE SHOD";
                            majmoo += gheimat[7];
                            cout << endl;
                            break;
                    case 9:
                            cout << "X - BOX 360 (code 9) EZAFE SHOD";
                            majmoo += gheimat[8];
                            cout << endl;
                            break;
                    case 10:
                            cout << "NINENDO SWITCH (code 10) EZAFE SHOD";
                            majmoo += gheimat[9];
                            cout << endl;
                            break;
                    case 11:
                            cout << "IPHONE 13 (code 11) EZAFE SHOD";
                            majmoo += gheimat[10];
                            cout << endl;
                            break;
                    case 12:
                            cout << "IPHONE 13 MINI (code 12) EZAFE SHOD";
                            majmoo += gheimat[11];
                            cout << endl;
                            break;
                    case 13:
                            cout << "S20 (code 13) EZAFE SHOD";
                            majmoo += gheimat[12];
                            cout << endl;
                            break;
                    case 14:
                            cout << "S20 ULTRA (code 14) EZAFE SHOD";
                            majmoo += gheimat[13];
                            cout << endl;
                            break;
                    case 15:
                            cout << "REDMI (code 15) EZAFE SHOD";
                            majmoo += gheimat[14];
                            cout << endl;
                            break;
                    }
                }
                //w=tedad mahsoolat dar sabd khaid
                while (taeed == 3)
                {
                    cout << "CODE MAHSOOLI KE MIKHAHEED HAZF KONID RA VARED KONID : \n";
                    cout << "20)MOSHAHEDE SOORAT HESAB VA PARDAKHT\n";
                    int q;
                    int code_mahsool_hazfi;
                    cin >> code_mahsool_hazfi;
                    if (code_mahsool_hazfi == 20)
                        break;
                    while (code_mahsool_hazfi <= 0 || code_mahsool_hazfi > 15)
                    {
                        cout << "CODE MAHSOOL RA DOBARE VARED KONID";
                        cin >> code_mahsool_hazfi;
                    }
                        for (q = 0; q <= w; q++)
                        {
                            if (code_mahsool_hazfi == code_mahsool_pardakht[q])
                            {
                                switch (code_mahsool_hazfi)
                                {
                                case 1:
                                        cout << "MACBOOK 13.3 INCH (code 1) HAZF SHOD";
                                        majmoo -= gheimat[0];
                                        cout << endl;
                                        break;
                                case 2:
                                        cout << "MACBOOK 15 INCH (code 2) HAZF SHOD";
                                        majmoo -= gheimat[1];
                                        cout << endl;
                                        break;
                                case 3:
                                        cout << "LEGION 5 (code 3) HAZF SHOD";
                                        majmoo -= gheimat[2];
                                        cout << endl;
                                        break;
                                case 4:
                                        cout << "LEGION 7 (code 4) HAZF SHOD";
                                        majmoo -= gheimat[3];
                                        cout << endl;
                                        break;
                                case 5:
                                        cout << "ZENBOOK (code 5) HAZF SHOD";
                                        majmoo -= gheimat[4];
                                        cout << endl;
                                        break;
                                case 6:
                                        cout << "PLAYSTATION 4 (code 6) HAZF SHOD";
                                        majmoo -= gheimat[5];
                                        cout << endl;
                                        break;
                                case 7:
                                        cout << "PLAYSTATION 5 (code 7) HAZF SHOD";
                                        majmoo -= gheimat[6];
                                        cout << endl;
                                        break;
                                case 8:
                                        cout << "X - BOX SERIE S (code 8) HAZF SHOD";
                                        majmoo -= gheimat[7];
                                        cout << endl;
                                        break;
                                case 9:
                                        cout << "X - BOX 360 (code 9) HAZF SHOD";
                                        majmoo -= gheimat[8];
                                        cout << endl;
                                        break;
                                case 10:
                                        cout << "NINENDO SWITCH (code 10) HAZF SHOD";
                                        majmoo -= gheimat[9];
                                        cout << endl;
                                        break;
                                case 11:
                                        cout << "IPHONE 13 (code 11) HAZF SHOD";
                                        majmoo -= gheimat[10];
                                        cout << endl;
                                        break;
                                case 12:
                                        cout << "IPHONE 13 MINI (code 12) HAZF SHOD";
                                        majmoo -= gheimat[11];
                                        cout << endl;
                                        break;
                                case 13:
                                        cout << "S20 (code 13) HAZF SHOD";
                                        majmoo -= gheimat[12];
                                        cout << endl;
                                        break;
                                case 14:
                                        cout << "S20 ULTRA (code 14) HAZF SHOD";
                                        majmoo -= gheimat[13];
                                        cout << endl;
                                        break;
                                case 15:
                                        cout << "REDMI (code 15) HAZF SHOD";
                                        majmoo -= gheimat[14];
                                        cout << endl;
                                        break;
                                }
                            }
                        }
                    if (q > w)
                        cout << "IN CODE DAR SABAD KHARID SHOMA GHARAR NADARAD\n";
                    if (majmoo == 0)
                    {
                        cout << "\nHICH MAHSOOLI DAR SABAD KHARID SHOMA NIST ...\nKHARID SHOMA BATEL SHOD\n DOBARE BARNAME RA EJRA KONID";
                        return 0;
                    }
                }
                cout << "MAJMOO SOORAT HESAB SHOMA " << majmoo << "$ AST\n80)PARDAKHT \n";
                int pardakht_80;
                cin >> pardakht_80;
                while (pardakht_80 != 80)
                {
                    cout << "JAHAT PARDAKHT 80 RA VARED KONID \n";
                    cin >> pardakht_80;
                }
                if (pardakht_80 == 80)
                {
                    cout << "SHOMARE MOBILE KHOD RA BEDOON \"0\" VARED KONID :" << endl;
                    cout << "+98";
                    cin >> shomaremobile;
                    while (strlen(shomaremobile) != 10)
                    {
                        cout << "TEDAD ARGHAM VARED SHODE SAHIH NIST\n";
                        cout << "+98";
                        cin >> shomaremobile;
                    }
                    for (int t = 0; t < 10; t++)
                    {
                        while (shomaremobile[t] < '0' || shomaremobile[t]>'9')
                        {
                            cout << "SHOMARE MOBILE KHOD RA DOBARE BEIN \"0\" TA \"9\" VARED KONID :" << endl;
                            cout << "+98";
                            cin >> shomaremobile;
                        }
                        while (shomaremobile[0] == '0')
                        {
                            cout << "SHOMARE MOBILE KHOD RA DOBARE BEDOON \"0\" DAR EBTEDAYE AN VARED KONID :" << endl;
                            cout << "+98";
                            cin >> shomaremobile;
                        }
                    }
                    cout << "CHAND $ RA NAGHDAN PARDAKHT MIKONID : \nAGAR MIKHHID BA'ADAN PARDAKHT KONID 0 RA HALA PARDAKHT KONID\n";
                    float naghd;
                    cin >> naghd;
                    while (naghd > majmoo || naghd < 0)
                    {
                        cout << "MEGHDAR $ NAGHD RA ESHTEBAH VARED KARDID\nDOBARE VARED KONID : ";
                        cin >> naghd;
                    }
                    cout << "1)CODE TAKHFI\n2)EDAME\n";
                    int m;
                    cin >> m;
                    while (m != 1 && m != 2)
                    {
                        cout << "1)E'AMAL CODE TAKHFI\n2)EDAME\n";
                        cin >> m;
                    }
                    if (m == 1)
                    {
                        cout << "DAR HAL HAZER CODE TAKHFIFI VOJOOD NADARAD "<<endl;
                        cout << "EDAME PARDAKHT ... " << endl;
                    }
                    float bedehi;
                    bedehi = majmoo - naghd;
                    fstream kharid;
                    kharid.open("/Users/alirezamoghadaspour/desktop/purchase.txt", ios::app);
                    for (k = 0; k <= w; k++)
                    {
                        if (code_mahsool_pardakht[k] == 1)
                            kharid << "MACBOOK 13.3 INCH (code 1)";
                        if (code_mahsool_pardakht[k] == 2)
                            kharid << "MACBOOK 15 INCH (code 2)";
                        if (code_mahsool_pardakht[k] == 3)
                            kharid << "LEGION 5 (code 3)";
                        if (code_mahsool_pardakht[k] == 4)
                            kharid << "LEGION 7 (code 4)";
                        if (code_mahsool_pardakht[k] == 5)
                            kharid << "ZENBOOK (code 5)";
                        if (code_mahsool_pardakht[k] == 6)
                            kharid << "PLAYSTATION 4 (code 6)";
                        if (code_mahsool_pardakht[k] == 7)
                            kharid << "PLAYSTATION 5 (code 7)";
                        if (code_mahsool_pardakht[k] == 8)
                            kharid << "X - BOX SERIE S (code 8)";
                        if (code_mahsool_pardakht[k] == 9)
                            kharid << "X - BOX 360 (code 9)";
                        if (code_mahsool_pardakht[k] == 10)
                            kharid << "NINENDO SWITCH (code 10)";
                        if (code_mahsool_pardakht[k] == 11)
                            kharid << "IPHONE 13 (code 11)";
                        if (code_mahsool_pardakht[k] == 12)
                            kharid << "IPHONE 13 MINI (code 12)";
                        if (code_mahsool_pardakht[k] == 13)
                            kharid << "S20 (code 13)";
                        if (code_mahsool_pardakht[k] == 14)
                            kharid << "S20 ULTRA (code 14)";
                        if (code_mahsool_pardakht[k] == 15)
                            kharid << "REDMI (code 15)";
                    }
                    if (majmoo > 0)
                    {
                        kharid.open("/Users/alirezamoghadaspour/desktop/purchase.txt", ios::app);
                        kharid << shomaremobile << '\t' <<"majmoo soorat hesab = " << majmoo <<" $" << '\t' << "pardakhti = " << naghd << " $" ;
                    }
                    int month;
                    int day;
                    cout << "TARIKH KHARID : 1401 / ";
                    cin >> month;
                    while (month > 12 || month < 0)
                    {
                        cout<<"MAH RA DOBARE BEIN \"1\" TA \"12\" VARED KONID "<<endl;
                        cin>>month;
                    }
                    cout << "\nTARIKH KHARID : 1401 / " << month << " /";
                    cin >> day;
                    while (day > 31 || day < 0)
                    {
                        cout<<"ROOZ RA DOBARE BEIN \"1\" TA \"30\" VARED KONID "<<endl;
                        cin>>day;
                    }
                    while ( (month == 7 || month == 8 || month == 9 || month == 10 || month == 11 || month == 12 ) && day == 31 )
                    {
                        cout<<"ROOZ RA DOBARE VARED KONID"<<endl;
                        cin>>day;
                    }
                    kharid << "tarikh kharid = " <<"1401 / " << month << " / " << day<< endl;
                    cout << "\nKHARID SHOMA BA MOVAFAGHIAT ANJAM SHOD\nBEDEHI SHOMA " << bedehi << "$ AST";
                    cout << "\nTARIKH KHARID : 1401 / " << month << " / "<< day << endl;
                    if (bedehi > 0)
                    {
                        fstream bedehkari;
                        bedehkari.open("/Users/alirezamoghadaspour/desktop/bedehkar.txt",ios::app);
                        bedehkari << shomaremobile << '\t'<< "bedehi = " << bedehi << " $" <<endl;
                        bedehkari.close();
                    }
                    for (k = 0; k <= w; k++)
                    {
                        if (code_mahsool_pardakht[k] == 1)
                            --mojoodi[0];
                        if (code_mahsool_pardakht[k] == 2)
                            --mojoodi[1];
                        if (code_mahsool_pardakht[k] == 3)
                            --mojoodi[2];
                        if (code_mahsool_pardakht[k] == 4)
                            --mojoodi[3];
                        if (code_mahsool_pardakht[k] == 5)
                            --mojoodi[4];
                        if (code_mahsool_pardakht[k] == 6)
                            --mojoodi[5];
                        if (code_mahsool_pardakht[k] == 7)
                            --mojoodi[6];
                        if (code_mahsool_pardakht[k] == 8)
                            --mojoodi[7];
                        if (code_mahsool_pardakht[k] == 9)
                            --mojoodi[8];
                        if (code_mahsool_pardakht[k] == 10)
                            --mojoodi[9];
                        if (code_mahsool_pardakht[k] == 11)
                            --mojoodi[10];
                        if (code_mahsool_pardakht[k] == 12)
                            --mojoodi[11];
                        if (code_mahsool_pardakht[k] == 13)
                            --mojoodi[12];
                        if (code_mahsool_pardakht[k] == 14)
                            --mojoodi[13];
                        if (code_mahsool_pardakht[k] == 15)
                            --mojoodi[14];
                    }
                    mojoodi_f.open("/Users/alirezamoghadaspour/desktop/mojoodi.txt");
                    for (int i=0;i<15;i++)
                        mojoodi_f << mojoodi[i] << endl;
                    mojoodi_f.close();
                    cout << "1)BAZGASHT BE MENU GHABL\n2)BASTAN BARNAME\n";
                    int bb;
                    cin >> bb;
                    while (bb != 1 && bb != 2)
                    {
                        cout << "LOTFAN 1 YA 2 RA VARED KONID";
                        cin >> bb;
                    }
                    if (bb == 1)
                        break;
                    if (bb == 2)
                        return 0;
                }
            }
        }
        while (y == 3)
        {
            cout << "1)VOROOD\n2)BAZGASHT BE MENU GHABL\n";
            int c;
            cin >> c;
            while (c == 1)
            {
                cout << "1)PASSWORD\n2)BAZGASHT BE MENU GHABL\n";
                int ccc;
                cin >> ccc;
                while (ccc == 1)
                {
                    cout << "PASSWORD RA VARED KONID : ";
                    char v_password[120];
                    cin >> v_password;
                    char d_password[12];
                    ifstream password_khandan;
                    password_khandan.open("/Users/alirezamoghadaspour/desktop/password.txt");
                    password_khandan >> d_password;
                    password_khandan.close();
                        if (strcmp(d_password , v_password)!=0)
                        {
                            cout << "PASSWORD RA ESHTEBAH VARED KARDID !!!";
                            return 0;
                        }
                    cout << " VARED SHODID ...\n" << "1)TAGHEER PASSWORD\n2)BEROOZ RESANI MOJOODI KALAHA\n3)TAGHEER GHEIMAT KALAHA\n";
                    int ca;
                    cin >> ca;
                    while (ca == 1)
                    {
                        cout << "PASSWORD JADID RA VARED KONID ( MAX = 11 CHARACTER ) : ";
                        char n_password[12];
                        cin >> n_password;
                        while (strlen(n_password) == 0 || strlen(n_password) > 11)
                        {
                            cout << "\nPASSWORD RA BEIN \"1\" TA \"11\" CHARACTER VARED KONID : ";
                        }
                        cout << "PASWORD BA MOVAFAGHIAT TAGHEER PEYDA KARD : \n PASWORD JADID : " << n_password;
                        strcpy(d_password,n_password);
                        ofstream password_berooz;
                        password_berooz.open("/Users/alirezamoghadaspour/desktop/password.txt");
                        password_berooz << n_password;
                        password_berooz.close();
                        break;
                    }
                    while (ca == 2)
                    {
                        cout << "100)TAGHEER MOJOODI KALAHA\n102)BASTAN BARNAME\n";
                        int code_mahsool;
                        cin >> code_mahsool;
                        while (code_mahsool != 100 && code_mahsool != 102)
                        {
                            cout << "LOTFAN 100 YA 102 RA VARED KONID \n";
                            cin >> code_mahsool;
                        }

                        while (code_mahsool == 100)
                        {
                            cout << "CODE MAHSOOL RA VARED KONID :\n200)BAZGASHT BE MENU GHABL\n";
                            cin >> code_mahsool;
                            if (code_mahsool == 200)
                                break;
                            while (code_mahsool < 0 || code_mahsool > 15)
                            {
                                cout << "LOTFAN CODE RA BEIN \"1 TA 15 YA 200 \" RA VARED KONID\n";
                                cin >> code_mahsool;
                            }
                            if (code_mahsool == 200)
                                break;
                            if (code_mahsool == 1)
                            {
                                cout << "MOJOODI JADID RA VARED KONID : ";
                                cin >> mojoodi[0];
                                cout << "\nMOJOODI MACBOOK 13.3 INCH (code 1) BEROOZ SHOD";
                                cout << endl;
                            }
                            if (code_mahsool == 2)
                            {
                                cout << "MOJOODI JADID RA VARED KONID : ";
                                cin >> mojoodi[1];
                                cout << "\nMOJOODI MACBOOK 15 INCH (code 2) BEROOZ SHOD";
                                cout << endl;
                            }
                            if (code_mahsool == 3)
                            {
                                cout << "MOJOODI JADID RA VARED KONID : ";
                                cin >> mojoodi[2];
                                cout << "\nMOJOODI LEGION 5 (code 3) BEROOZ SHOD";
                                cout << endl;
                            }
                            if (code_mahsool == 4)
                            {
                                cout << "MOJOODI JADID RA VARED KONID : ";
                                cin >> mojoodi[3];
                                cout << "\nMOJOODI LEGION 7 (code 4) BEROOZ SHOD";
                                cout << endl;
                            }
                            if (code_mahsool == 5)
                            {
                                cout << "MOJOODI JADID RA VARED KONID : ";
                                cin >> mojoodi[4];
                                cout << "\nMOJOODI ZENBOOK (code 5) BEROOZ SHOD";
                                cout << endl;
                            }
                            if (code_mahsool == 6)
                            {
                                cout << "MOJOODI JADID RA VARED KONID : ";
                                cin >> mojoodi[5];
                                cout << "\nMOJOODI PLAYSTATION 4 (code 6) BEROOZ SHOD";
                                cout << endl;
                            }
                            if (code_mahsool == 7)
                            {
                                cout << "MOJOODI JADID RA VARED KONID : ";
                                cin >> mojoodi[6];
                                cout << "\nMOJOODI PLAYSTATION 5 (code 7) BEROOZ SHOD";
                                cout << endl;
                            }
                            if (code_mahsool == 8)
                            {
                                cout << "MOJOODI JADID RA VARED KONID : ";
                                cin >> mojoodi[7];
                                cout << "\nMOJOODI X - BOX SERIE S (code 8) BEROOZ SHOD";
                                cout << endl;
                            }
                            if (code_mahsool == 9)
                            {
                                cout << "MOJOODI JADID RA VARED KONID : ";
                                cin >> mojoodi[8];
                                cout << "\nMOJOODI X - BOX 360 (code 9) BEROOZ SHOD";
                                cout << endl;
                            }
                            if (code_mahsool == 10)
                            {
                                cout << "MOJOODI JADID RA VARED KONID : ";
                                cin >> mojoodi[9];
                                cout << "\nMOJOODI NINENDO SWITCH (code 10) BEROOZ SHOD";
                                cout << endl;
                            }
                            if (code_mahsool == 11)
                            {
                                cout << "MOJOODI JADID RA VARED KONID : ";
                                cin >> mojoodi[10];
                                cout << "\nMOJOODI IPHONE 13 (code 11) BEROOZ SHOD";
                                cout << endl;
                            }
                            if (code_mahsool == 12)
                            {
                                cout << "MOJOODI JADID RA VARED KONID : ";
                                cin >> mojoodi[11];
                                cout << "\nMOJOODI IPHONE 13 MINI (code 12) BEROOZ SHOD";
                                cout << endl;
                            }
                            if (code_mahsool == 13)
                            {
                                cout << "MOJOODI JADID RA VARED KONID : ";
                                cin >> mojoodi[12];
                                cout << "\nMOJOODI S20 (code 13) BEROOZ SHOD";
                                cout << endl;
                            }
                            if (code_mahsool == 14)
                            {
                                cout << "MOJOODI JADID RA VARED KONID : ";
                                cin >> mojoodi[13];
                                cout << "\nMOJOODI S20 ULTRA (code 14) BEROOZ SHOD";
                                cout << endl;
                            }
                            if (code_mahsool == 15)
                            {
                                cout << "MOJOODI JADID RA VARED KONID : ";
                                cin >> mojoodi[14];
                                cout << "\nMOJOODI REDMI (code 15) BEROOZ SHOD";
                                cout << endl;
                            }
                            mojoodi_f.open("/Users/alirezamoghadaspour/desktop/mojoodi.txt");
                            for (int i=0;i<15;i++)
                            {
                                mojoodi_f << mojoodi[i];
                                mojoodi_f << endl;
                            }
                            mojoodi_f.close();
                        }
                        if (code_mahsool == 102)
                            return 0;
                    }
                    while (ca == 3)
                    {
                        cout << "100)TAGHEER GHEIMAT KALAHA\n102)BASTAN BARNAME\n";
                        int code_mahsool;
                        cin >> code_mahsool;
                        while (code_mahsool != 100 && code_mahsool != 102)
                        {
                            cout << "LOTFAN 101 YA 102 RA VARED KONID \n";
                            cin >> code_mahsool;
                        }
                        while (code_mahsool == 100)
                        {
                            cout << "1)CODE MAHSOOL RA VARED KONID :\n200)BAZGASHT BE MENU GHABL\n";
                            cin >> code_mahsool;
                            if (code_mahsool == 200)
                                break;
                             if (code_mahsool == 1)
                            {
                                cout << "GHEIMAT JADID RA VARED KONID : ";
                                cin >> gheimat[0];
                                cout << "\nGHEIMAT MACBOOK 13.3 INCH (code 1) BEROOZ SHOD";
                                cout << endl;
                            }
                             if (code_mahsool == 2)
                            {
                                cout << "GHEIMAT JADID RA VARED KONID : ";
                                cin >> gheimat[1];
                                cout << "\nGHEIMAT MACBOOK 15 INCH (code 2) BEROOZ SHOD";
                                cout << endl;
                            }
                             if (code_mahsool == 3)
                             {
                                 cout << "GHEIMAT JADID RA VARED KONID : ";
                                 cin >> gheimat[2];
                                 cout << "\nGHEIMAT LEGION 5 (code 3) BEROOZ SHOD";
                                 cout << endl;
                             }
                             if (code_mahsool == 4)
                            {
                                cout << "GHEIMAT JADID RA VARED KONID : ";
                                cin >> gheimat[3];
                                cout << "\nGHEIMAT LEGION 7 (code 4) BEROOZ SHOD";
                                cout << endl;
                            }
                             if (code_mahsool == 5)
                            {
                                cout << "GHEIMAT JADID RA VARED KONID : ";
                                cin >> gheimat[4];
                                cout << "\nGHEIMAT ZENBOOK (code 5) BEROOZ SHOD";
                                cout << endl;
                            }
                             if (code_mahsool == 6)
                            {
                                cout << "GHEIMAT JADID RA VARED KONID : ";
                                cin >> gheimat[5];
                                cout << "\nGHEIMAT PLAYSTATION 4 (code 6 - 600$) BEROOZ SHOD";
                                cout << endl; }
                             if (code_mahsool == 7)
                            {
                                cout << "GHEIMAT JADID RA VARED KONID : ";
                                cin >> gheimat[6];
                                cout << "\nGHEIMAT PLAYSTATION 5 (code 7) BEROOZ SHOD";
                                cout << endl;
                            }
                             if (code_mahsool == 8)
                            {
                                cout << "GHEIMAT JADID RA VARED KONID : ";
                                cin >> gheimat[7];
                                cout << "\nGHEIMAT X - BOX SERIE S (code 8) BEROOZ SHOD";
                                cout << endl;
                            }
                             if (code_mahsool == 9)
                            {
                                cout << "GHEIMAT JADID RA VARED KONID : ";
                                cin >> gheimat[8];
                                cout << "\nGHEIMAT X - BOX 360 (code 9) BEROOZ SHOD";
                                cout << endl;
                            }
                             if (code_mahsool == 10)
                            {
                                cout << "GHEIMAT JADID RA VARED KONID : ";
                                cin >> gheimat[9];
                                cout << "\nGHEIMAT NINENDO SWITCH (code 10) BEROOZ SHOD";
                                cout << endl;
                            }
                             if (code_mahsool == 11)
                            {
                                cout << "GHEIMAT JADID RA VARED KONID : ";
                                cin >> gheimat[10];
                                cout << "\nGHEIMAT IPHONE 13 (code 11) BEROOZ SHOD";
                                cout << endl;
                            }
                             if (code_mahsool == 12)
                             {
                                 cout << "GHEIMAT JADID RA VARED KONID : ";
                                 cin >> gheimat[11];
                                 cout << "\nGHEIMAT IPHONE 13 MINI (code 12) BEROOZ SHOD";
                                 cout << endl;
                             }
                             if (code_mahsool == 13)
                             {
                                 cout << "GHEIMAT JADID RA VARED KONID : ";
                                 cin >> gheimat[12];
                                 cout << "\nGHEIMAT S20 (code 13) BEROOZ SHOD";
                                 cout << endl;
                             }
                             if (code_mahsool == 14)
                             {
                                 cout << "GHEIMAT JADID RA VARED KONID : ";
                                 cin >> gheimat[13];
                                 cout << "\nGHEIMAT S20 ULTRA (code 14) BEROOZ SHOD";
                                 cout << endl;
                             }
                             if (code_mahsool == 15)
                             {
                                 cout << "GHEIMAT JADID RA VARED KONID : ";
                                 cin >> gheimat[14];
                                 cout << "\nGHEIMAT REDMI (code 15) BEROOZ SHOD";
                                 cout << endl;
                             }
                            gheimat_f.open("/Users/alirezamoghadaspour/desktop/gheimat.txt");
                            for (int i=0;i<15;i++)
                                gheimat_f << gheimat[i] << endl;
                            gheimat_f.close();
                        }
                        if (code_mahsool == 102)
                            return 0;
                    }
                }
                if (ccc == 2)
                    break;
            }
            if (c == 2)
                break;
        }
    }
}


#include<iostream>
#include<iomanip>
#include<string>
#include<conio.h>
#include<mysql.h>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <windows.h>
#include<cstdio>
#include<stdio.h>
using namespace std;

int qstate;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;

int qstate1;
MYSQL_ROW row1;
MYSQL_RES* res1;

int qstate2;
MYSQL_ROW row2;
MYSQL_RES* res2;
string BorrowID, AdminID, BookID, TransactionID;


class db_response
{
public:
    static void ConnectionFunction()
    {
        conn = mysql_init(0);
        if (conn)
            cout << "Database Connected" << endl;
        else
            cout << "Failed To Connect!" << endl;

        conn = mysql_real_connect(conn, "localhost", "root", "", "wss", 3306, NULL, 0);
        if (conn)
            cout << "Database Connected To MySql" << endl;
        else
            cout << "Failed To Connect!" << endl;
    }
};

void Register();
void LoginBorrower();
void LoginAdmin();
void BorrowerMenu();
void AdminMenu();
void ViewBook();
void SearchBook();

void AddBorrower();
void AddBook();
void DeleteBorrower();
void UpdateBook();
void UpdateBorrowerStatus();
void ListBook();
void ReturnBook();
void ListBorrowedBook();
void DateCount();
void Sambungan();
void Info();
void Delete();
void Report();
int main()
{
    system("cls");
    system("title :Book Record System");
    db_response::ConnectionFunction();
    int choice;
    cout << "\n\n\t\t\t\t\t\t\t\t\t\t\t   Created by Hanis Zahira\n "
        <<"\n\n\t\t\t\t\t\t\t\t\t\t\t          2BITM S1G1\n\n"
        << "\n\n\t\t\t\t\t\t\t\t\tThis system will be used on the front desk by staff and user of library\n\n";
    cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tWELCOME TO BOOK RECORD SYSTEM\n\n";
  
    cout << "******************************************************************************************************************************************************************************************************************";
    cout << "\n\t\t\t\t\t\t\t\t\t\t\t\tMAIN MENU\n";
    cout << "******************************************************************************************************************************************************************************************************************\n\n";
    cout << "\n\n\t\t\t\t\t\t\t\t\t\t     Choose one from the option below: \n\n";
    cout << "\t\t\t\t\t\t\t\t\t\t\t1. New Registration as Borrower\n\n";
    cout << "\t\t\t\t\t\t\t\t\t\t\t2. Login Borrower\n\n";
    cout << "\t\t\t\t\t\t\t\t\t\t\t3. Login as Admin\n\n";
    cout << "\t\t\t\t\t\t\t\t\t\t\t4. Exit \n\n";
    cout << "\t\t\t\t\t\t\t\t\t\t\tYour choice: ";
    cin >> choice;
    cout << "\n";
    switch (choice) {
    case 1: Register();
        break;
    case 2: LoginBorrower();
        break;
    case 3: LoginAdmin();
        break;
    case 4: cout << "Exiting";
        exit(0);
    default:
        cout << "\n\n\t\t\t\t\t\t\t\t\tYour choice is invalid. Choose between 1-4.Please try again. Press any key";
        _getch();
        main();
    }
    return 0;
}

void Register() {
    system("cls");
    string x;
    string name, phone, email, password;
    cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout << "                                                                                              REGISTRATION PAGE  \n";
    cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------";
    cout << "\n\n\t\t\t\tDo you wish to continue?Press(Y/N)\n";
    cout << "\n\t\t\t\tInput: ";
    cin >> x;
  
    if (x == "Y" || x == "y") {
        cout << "\t\t\t\t-------------------------------------------------------" << endl;
        
        cout << "\n\n\t\t\t\tPlease fill your information below "<<endl;
        cout << "\t\t\t\t-------------------------------------------------------" << endl;
        cout << "\n\n\t\t\t\tA. Enter Name: ";
        cin.ignore(1, '\n');
        getline(cin, name);
        cout << "\n\n\t\t\t\tB. Enter Phone Number: ";
        getline(cin, phone);
        cout << "\n\n\t\t\t\tC. Enter Your email: ";
        getline(cin, email);
        cout << "\n\n\t\t\t\tD. Enter Password: ";
        getline(cin, password);

        string checkUser_query = "select * from borrower where BorrowEmail = '" + email + "'";
        const char* cu = checkUser_query.c_str();
        qstate = mysql_query(conn, cu);

        if (!qstate)
        {
            res = mysql_store_result(conn);
            if (res->row_count == 1)
            {
                cout << "\n\n\t\t\t\temail is already exist. Press Enter to Try Again...";
                (void)getchar();
                Register();
            }
            else
            {
                string insertUser_query = "insert into Borrower (BorrowName, BorrowPhone, BorrowEmail, BorrowPassword) values ('" + name + "', '" + phone + "', '" + email + "', '" + password + "')";
                const char* q = insertUser_query.c_str();
                qstate = mysql_query(conn, q);

                if (!qstate)
                {
                    cout << endl << "\n\n\t\t\t\tYou have been registered. Welcome to Book Record System. Press Enter to Continue...";
                    (void)getchar();
                    main();
                }
                else
                {
                    cout << "\t\t\t\tQuery Execution Problem!" << mysql_errno(conn) << endl;
                }
            }
        }
        else
        {
            cout << "\t\t\t\tQuery Execution Problem!" << mysql_errno(conn) << endl;
        }
    }
    else if (x == "N" || x == "n") {
        main();
    }
    else {
        cout << "\n\n\t\t\t\tWrong choice. Please enter y or n.Press any key to continue";
        _getch();
        Register();
    }
}
void LoginBorrower()
{
    system("cls");
    string password;
    string email;
    cout << "******************************************************************************************************************************************************************************************************************";
    cout << " \n\n\t\t\t\t\t\t\t\t\t\t\t        WELCOME BACK!";
    cout<< endl;
    cout << "\n\n\t\t\t\t\t\t\t\t\t\t\t      BORROWER LOGIN PAGE";
    cout << "\n\n******************************************************************************************************************************************************************************************************************";
    cout << endl << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t ENTER YOUR EMAIL AND PASSWORD";
    cout << "\n\n\t\t\t\t\t\t\t\t\t\t\t EMAIL : ";
    cin >> email;
    cout << "\n\n\t\t\t\t\t\t\t\t\t\t\t PASSWORD : ";
    char ch;
    while ((ch = _getch()) != 13)
    {
        password += ch;
        cout << '*';
    }


    string checkBorrower_query = "select BorrowID from Borrower where BorrowEmail = '" + email + "' and BorrowPassword = '" + password + "'";
    const char* cu = checkBorrower_query.c_str();
    qstate = mysql_query(conn, cu);

    if (!qstate)
    {
        res = mysql_store_result(conn);
        if (res->row_count == 1)
        {
            while (row = mysql_fetch_row(res))
                BorrowID = row[0];
            BorrowerMenu();
        }
        else
        {
            char c;
            cout << "\n\n\n\t\t\t\t\t\t\t\t\t\t\t  Wrong email or password.";
            cout << "\n\n\n\t\t\t\t\t\t\t\t\t\t\tREMINDER: If you forget your email or password,kindly ask admin for help.";

            cout<<"\n\n\t\t\t\t\t\t\t\t\t\t\tPress(Y) to try again.Press any key to go back to menu ";
            cin >> c;
            if (c == 'y' || c == 'Y')
                LoginBorrower();
            else
                main();
        }
    }
    else
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;

}
void LoginAdmin()
{
    system("cls");
    string password, email;
    cout << "******************************************************************************************************************************************************************************************************************";
    cout << "\n\n\t\t\t\t\t\t\t\t\t\t\t WELCOME BACK ADMIN!";
    cout << " \n\n\t\t\t\t\t\t\t\t\t\t\t  ADMIN LOGIN PAGE" << endl;

    cout << "\n\n******************************************************************************************************************************************************************************************************************";
    cout << endl << endl;
    
    cout << "\t\t\t\t\t\t\t\t\t\t\t   EMAIL : ";
    cin >> email;
    cout << "\n\n\t\t\t\t\t\t\t\t\t\t\t  PASSWORD : ";
    char ch;
    while ((ch = _getch()) != 13)
    {
        password += ch;
        cout << '*';
    }
    string checkAdmin_query = "select AdminID from Admin where AdminEmail = '" + email + "' and AdminPassword = '" + password + "'";
    const char* cu = checkAdmin_query.c_str();
    qstate = mysql_query(conn, cu);

    if (!qstate)
    {
        res = mysql_store_result(conn);
        if (res->row_count == 1)
        {
            while (row = mysql_fetch_row(res))
                AdminID = row[0];
            AdminMenu();
        }
        else
        {
            char c;
            cout << "\n\n\n\t\t\t\t\t\t\t\t\t\t\t   Wrong email or password.";
            cout<<"\n\n\n\t\t\t\t\t\t\t\t\t\t\t  Press(Y) to try again. Press any key to go back ";
            cin >> c;
            if (c == 'y' || c == 'Y')
                LoginAdmin();
            else
                main();
        }
    }
    else
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;

}
void BorrowerMenu() {
    int choice;
    string email, password;
    system("cls");
    cout << "\n\n******************************************************************************************************************************************************************************************************************";
    cout << "\n\t\t\t\t\t\t\t\t\t\t\t        BORROWER MENU PAGE\n";
    cout << "******************************************************************************************************************************************************************************************************************\n\n";
    string search_query = "SELECT BorrowID,BorrowName FROM Borrower WHERE BorrowID ='" + BorrowID + "'";
    const char* q = search_query.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate)
    {res = mysql_store_result(conn);

        while (row = mysql_fetch_row(res))
        {

            cout << endl << endl << "\t\t\t\t\t\t\t\t\t\t\tWELCOME BACK " << row[1] << endl;
            cout << "\t\t\t\t\t\t\t\t\t\t\tThis is your ID:" << row[0];
        }
    }
    cout << "\n\n\t\t\t\t\t\t\t\t\t\t\t----------------------------------";

    cout << "\n\t\t\t\t\t\t\t\t\t\t\t|Choose one among the below option|";
    cout << "\n\t\t\t\t\t\t\t\t\t\t\t----------------------------------";
    cout << "\n\t\t\t\t\t\t\t\t\t\t\t|1.Update your detail             |"; 
    cout << "\n\t\t\t\t\t\t\t\t\t\t\t----------------------------------";
    cout << "\n\t\t\t\t\t\t\t\t\t\t\t|2.View Book List                 |"; 
    cout << "\n\t\t\t\t\t\t\t\t\t\t\t----------------------------------";
    cout << "\n\t\t\t\t\t\t\t\t\t\t\t|3.Search Book                    |";
    cout << "\n\t\t\t\t\t\t\t\t\t\t\t----------------------------------";
    cout << "\n\t\t\t\t\t\t\t\t\t\t\t|4.Borrowing Book                 |";
    cout << "\n\t\t\t\t\t\t\t\t\t\t\t----------------------------------";
    cout << "\n\t\t\t\t\t\t\t\t\t\t\t|5.List of book borrowed          |";
    cout << "\n\t\t\t\t\t\t\t\t\t\t\t----------------------------------";
    cout << "\n\t\t\t\t\t\t\t\t\t\t\t|6.Logout                         |" ;
    cout << "\n\t\t\t\t\t\t\t\t\t\t\t----------------------------------"<<endl;

    
    cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n";

    cout << " \n\n\t\t\t\t\t\t\t\t\t\t\tEnter your choice: ";
    cin >> choice;
  

    switch (choice) {
    case 1:Info();
        break;
    case 2:ViewBook();
        break;
    case 3:SearchBook();
        break;
    case 4:AddBorrower();
        break;
    case 5:ListBorrowedBook();
        break;
    case 6:main();
        break;
   
    default:
        cout << "\n\n\t\t\t\t\t\t\t\t\t\tYou enter wrong input.Choose between 1-6";
        _getch();
        system("cls");
        BorrowerMenu();
    }
}
void AdminMenu() {
    int choice;
    system("cls");
    cout << "\n\n******************************************************************************************************************************************************************************************************************";
    cout << "\n\t\t\t\t\t\t\t\t\t\t\t     ADMIN MENU PAGE\n";
    cout << "******************************************************************************************************************************************************************************************************************\n\n";
       cout << "\n\n\t\t\t\t\t\t\t\t\t\t\t---------------------------------";

        cout<< "\n\t\t\t\t\t\t\t\t\t\t\t|1. System Users's Info         |"
            << "\n\t\t\t\t\t\t\t\t\t\t\t---------------------------------"

            << "\n\t\t\t\t\t\t\t\t\t\t\t|2. View list book              |"
            << "\n\t\t\t\t\t\t\t\t\t\t\t---------------------------------"
            << "\n\t\t\t\t\t\t\t\t\t\t\t|3. Add Book                    |"
            << "\n\t\t\t\t\t\t\t\t\t\t\t---------------------------------"
            << "\n\t\t\t\t\t\t\t\t\t\t\t|4. Update Book Info            |"
            << "\n\t\t\t\t\t\t\t\t\t\t\t---------------------------------"
            << "\n\t\t\t\t\t\t\t\t\t\t\t|5. Return Book                 |"
            << "\n\t\t\t\t\t\t\t\t\t\t\t---------------------------------"
            << "\n\t\t\t\t\t\t\t\t\t\t\t|6. Update Borrowing Status     |"
            << "\n\t\t\t\t\t\t\t\t\t\t\t---------------------------------"
            << "\n\t\t\t\t\t\t\t\t\t\t\t|7. Penalty Calculation         |"
            << "\n\t\t\t\t\t\t\t\t\t\t\t---------------------------------"
            << "\n\t\t\t\t\t\t\t\t\t\t\t|8. Report Generate             |" 
            << "\n\t\t\t\t\t\t\t\t\t\t\t---------------------------------"
            << "\n\t\t\t\t\t\t\t\t\t\t\t|9. Logout                      |" << endl;
      
        cout << "\t\t\t\t\t\t\t\t\t\t\t---------------------------------";

        cout <<endl<< "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n";

       cout << "\n\n\t\t\t\t\t\t\t\t\t\t\t Enter your choice: ";
 
    cin >> choice;

    switch (choice) {
    
    case 1:DeleteBorrower();
        break;
    case 2:ListBook();
        break;
    case 3:AddBook();
        break;
    case 4:UpdateBook();
          break;
    case 5:ReturnBook();
        break;
    case 6:UpdateBorrowerStatus();
        break;
    case 7:DateCount();
        break;
    case 8:Report();
        break;
    case 9:main();
        break;
  
  default:
        cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tYou enter wrong input.Choose between 1-8";
        _getch();
        system("cls");
        AdminMenu();
    }
}
void ViewBook() {
    system("cls");
    char choose;
    cout << "******************************************************************************************************************************************************************************************************************\n\n";

    cout << "                                                                                                List of All Book " << endl;
    cout << "******************************************************************************************************************************************************************************************************************\n\n";


    qstate = mysql_query(conn, "select BookID, Title, Genre, AuthorName,Availability from Book");

    if (!qstate)
    {
        cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
        printf("          |%-6s|%-30s|%-30s|%-25s|%-15s|", "BOOKID", "TITLE", "GENRE", "AUTHOR", "AVAILABILITY");
        
        cout << endl;
        cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
       
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            printf("          |%-6s|%-30s|%-30s|%-25s|%-15s|", row[0],row[1],row[2],row[3],row[4]);
            cout << endl;
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }
    qstate2 = mysql_query(conn, "select count(BookID), count(DISTINCT Genre), COUNT(DISTINCT AuthorName) from Book");
    res = mysql_store_result(conn);
    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

    while (row = mysql_fetch_row(res))
    {
        cout << "\t\t\t\t\t\t\t\t\tTotal book in system :" << row[0]
            << "\n\t\t\t\t\t\t\t\t\tTotal number Genre    :" << row[1]
            << "\n\t\t\t\t\t\t\t\t\tTotal number of Author:" << row[2] << endl;
    }
    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

    do
    {
        cout << "\n\n\t\tPress Y to continue or any key to logout: ";
        cin >> choose;
        if (choose == 'y' || choose == 'Y')
        {
            BorrowerMenu();
        }
        else
        {
            main();
        }
    } while (choose != 'y' && choose != 'Y' && choose != 'n' && choose != 'N');
}

void SearchBook() {
    system("cls");
    int choose;
    string choice;
    string Title, Author, Genre;
    cout << "******************************************************************************************************************************************************************************************************************\n\n";

    cout << "                                                                                                SEARCH PAGE " << endl;
    cout << "******************************************************************************************************************************************************************************************************************\n\n";
    cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tChoose through\n"
        << "\n\n\t\t\t\t\t\t\t\t\t\t\t1.Title"
        << "\n\n\t\t\t\t\t\t\t\t\t\t\t2.Genre"
        << "\n\n\t\t\t\t\t\t\t\t\t\t\t3.Author"
        <<"\n\n\t\t\t\t\t\t\t\t\t\t\t4.Menu"
        << "\n\n\t\t\t\t\t\t\t\t\t\t\tEnter your option: ";
    cin >> choose;
    system("cls");

    if (choose == 1) {
        cin.ignore(1, '\n');
      
        cout << "\n\n\t\t\t\t\t\t\t\t\t\t  Search book by Title: ";
        getline(cin, Title);

        cout << "\n\n******************************************************************************************************************************************************************************************************************\n";

        cout << "                                                                                        List of All Book " << endl;
     
        string search_query = "select BookID, Title, Genre, AuthorName from Book where Title like '%" + Title + "%'";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);

        if (!qstate)
        {
            cout << endl;
            cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
             cout << "  ";
                    printf("                  |%-6s |%-30s|%-30s|%-25s", "BOOKID", "TITLE", "GENRE", "AUTHOR");
                    cout << endl;
              cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;


            res = mysql_store_result(conn);
            if (res->row_count > 0) {

                while (row = mysql_fetch_row(res))
                {

                    printf("                    |%-6s |%-30s|%-30s|%-25s", row[0], row[1], row[2], row[3]);
                    cout << endl;
                }
            }
            else {
                cout << "\n\n\t\t\t\t\t\t\t\t\t\t The book you are looking is not exist" << endl;
            }
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        }
        cout << "\n\n\t\t\t\t\t\t\t\t\t\tDo you want continue to search? (Y/N)\n ";
        cin >> choice;
        if (choice == "y" || choice == "Y") {
            SearchBook();
        }
        else if (choice == "n" || choice == "N") {
            BorrowerMenu();
        }
    }
    else if (choose == 2) {
        cin.ignore(1, '\n');
      
        cout << "\n\n\t\t\t\t\t\t\t\t\t\t  Search book by Genre: ";
        getline(cin, Genre);

        cout << "\n\n******************************************************************************************************************************************************************************************************************\n";

        cout << "                                                                                        List of All Book " << endl;

        string search_query = "select BookID, Title, Genre, AuthorName from Book where Genre like '%" + Genre + "%'";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);

        if (!qstate)
        {
            cout << endl;
            cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
            cout << "  ";
            printf("             |%-6s |%-30s|%-30s|%-25s", "BOOKID", "TITLE", "GENRE", "AUTHOR");
            cout << endl;
           cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;


            res = mysql_store_result(conn);
            if (res->row_count > 0) {
                while (row = mysql_fetch_row(res))
                {

                    printf("               |%-6s |%-30s|%-30s|%-25s", row[0],row[1],row[2],row[3]);
                    cout << endl;
                }
            }
            else {
                cout << "\n\n\t\t\t\t\t\t\t\t\t\tThe book you are looking is not exist" << endl;
            }
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        }

        cout << "\n\n\t\t\t\t\t\t\t\t\t\tDo you want continue to search? (Y/N)\n ";
        cin >> choice;
        if (choice == "y" || choice == "Y") {
            SearchBook();
        }
        else if (choice == "n" || choice == "N") {
            BorrowerMenu();
        }

    }
    else if (choose == 3) {
        cin.ignore(1, '\n');
        cout << "\n\n\t\t\t\t\t\t\t\t\t\t  Search book by Author: ";

        getline(cin, Author);
        cout << "\n\n******************************************************************************************************************************************************************************************************************\n";

        cout << "                                                                                        List of All Book " << endl;

        string search_query = "select BookID, Title, Genre, AuthorName from Book where AuthorName like '%" + Author + "%'";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);

        if (!qstate)
        {

            cout << endl;
            cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
            cout << "  ";
            printf("             |%-6s |%-30s|%-30s|%-25s", "BOOKID", "TITLE", "GENRE", "AUTHOR");
            cout << endl;

               cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;


            res = mysql_store_result(conn);
            if (res->row_count > 0) {
                while (row = mysql_fetch_row(res))
                {
                    cout << "  ";
                    printf("             |%-6s |%-30s|%-30s|%-25s",row[0],row[1],row[2],row[3]);
                    cout << endl;
                }
            }
            else {
                cout << "\n\n\t\t\t\t\t\t\t\t\t\tThe book you are looking is not found" << endl;
            }
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        }
        cout << "\n\n\t\t\t\t\t\t\t\t\t\tDo you want continue to search book? (Y/N)\n ";
        cin >> choice;
        if (choice == "y" || choice == "Y") {
            SearchBook();
        }
        else if (choice == "n" || choice == "N") {
            BorrowerMenu();
        }
    }
    else if (choose == 4) {
    BorrowerMenu();
}
    else { cout << "\n\t\t\t\tWrong input.Try again";
    _getch();
    SearchBook();
 }
}

void AddBorrower(){
    system("cls");
    string choose,option;

    cout << "******************************************************************************************************************************************************************************************************************\n\n";

    cout << "                                                                                                List of All Book " << endl;
    cout << "******************************************************************************************************************************************************************************************************************\n\n";

    qstate = mysql_query(conn, "select BookID, Title, Genre, AuthorName,Availability from Book");

    if (!qstate)
    {
        cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
      
        printf("              |%-6s |%-30s|%-30s|%-25s|%-15s|", "BOOKID", "TITLE", "GENRE", "AUTHOR","AVAILABILITY");
        cout << endl;

         cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
          
            printf("              |%-6s |%-30s|%-30s|%-25s|%-15s|", row[0],row[1],row[2],row[3],row[4]);
            cout << endl;

        }
        cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "\t\t\tBorrowing Book Record " << endl;
            cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

            cout << "\n\n\t\t\tEnter Book ID you want to borrow:";
            cin >> BookID;
            string check_query = "SELECT BookID from Book WHERE BookID ='" + BookID + "'";
            const char* q1 = check_query.c_str();
            qstate1 = mysql_query(conn, q1);
            if (!qstate1) {
                res = mysql_store_result(conn);
                if (res->row_count > 0) {
                    while (row = mysql_fetch_row(res))
                    {
                        string availability_query = "SELECT Availability from Book WHERE BookID ='" + BookID + "'";
                        const char* q2 = availability_query.c_str();
                        qstate2 = mysql_query(conn, q2);
                        if (!qstate2)
                        {
                            //cout << setw(11) << "Borrow ID" << setw(25) << "Transaction ID" << setw(25) << "BookID" << setw(15) << " " << setw(10) << "Book Title" << setw(25) << "Status Payment" << setw(30) << "Status Return" << setw(15) << endl;

                            res = mysql_store_result(conn);
                            if (res->row_count > 0) {
                                while (row = mysql_fetch_row(res))
                                {
                                    if (strcmp(row[0], "No") == 0) {
                                        cout << "\n\n\t\t\tBook Availability Status:";
                                        cout << setw(6) << row[1] << endl;
                                        cout << "\n\n\t\t\tBook currently is not available." << endl;
                                        cout << "\n\t\t\tYou're not allowed to borrow this book.Press Enter to continue" << endl;
                                        _getch();
                                        BorrowerMenu();
                                    }


                                }

                            }
                        }
                    }
                }
                else {
                    cout << "\n\t\tWhops! ID is not found.Press Enter to try again";
                    _getch();
                    AddBorrower();
                }
            }
            
            
           
            string inputBorrowDate,StatusAvailability="No";
          
            cin.ignore(1, '\n');
            cout << "\n\n\t\t\tEnter date below in format(dd/mm/yyyy)\n";
            cout << "\n\t\t\tBorrow date :";
            getline(cin, inputBorrowDate);
        

            string insertBorrowing_query = "insert into Borrow (BookID,BorrowID,Borrow_Date,Return_Date)values ('" + BookID + "','" + BorrowID + "', STR_TO_DATE('" + inputBorrowDate + "','%d/%m/%Y'),DATE_ADD(Borrow_Date,INTERVAL 5 day))";
            const char* q = insertBorrowing_query.c_str();
            qstate = mysql_query(conn, q);
            if (!qstate)
            {
                system("cls");
                cout << endl << "\n\t\t\tSuccessfully borrowing book. Don't forget to return book before the due date\n";

                string update_query = "update Book set Availability = '" + StatusAvailability + "' where BookID = '" + BookID + "'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);
                cout << "\n\n\t\t\tThis is your transaction id and return date" << endl << endl;
                qstate = mysql_query(conn, "select max(TransactionID),max(Return_Date) from Borrow");

                if (!qstate)
                {
                    cout <<"\t\t\t"<< setw(11) << "TransactionID" << setw(25) << "Return Date" << endl << endl;

                    res = mysql_store_result(conn);
                    while (row = mysql_fetch_row(res))
                    {
                        cout <<"\t\t\t"<< setw(6) << row[0] << setw(30) << row[1]<<endl;
              
                    }
               
                }
                else
                {
                    cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
                }

            }
        }
        
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        }

        do
        {
            cout << "\n\n\t\t\tDo you want borrow another book? (y/n): ";
            cin >> choose;
            if (choose == "y" || choose == "Y")
            {
                AddBorrower();
            }
            else if (choose == "n" || choose == "N")
            {
                BorrowerMenu();
            }
        } while (choose != "y" && choose != "Y" && choose != "n" && choose != "N");
    }
void AddBook() {
    system("cls");
    string Title, Genre, Author;
    char choose;
    int option;
     cout << "******************************************************************************************************************************************************************************************************************\n";

    cout << "                                                                                                        ADD BOOK PAGE " << endl;
    cout << "******************************************************************************************************************************************************************************************************************\n\n";

    cout << "\t\t\t\t\t\t\t\t\tChoose:"
        << "\n\n\t\t\t\t\t\t\t\t\t1. Add Book"
        << "\n\n\t\t\t\t\t\t\t\t\t2.Back to Menu";
    cout << "\n\n\t\t\t\t\t\t\t\t\tEnter option:";
    cin >> option;
    if (option == 1) {
        system("cls");
         cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "                                                                                                        BOOK DETAIL " << endl;
        cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";

        cin.ignore(1, '\n');
        cout << "\n\n\t\t\t\t\t\t\t\t\t1. Book Title: ";
        getline(cin, Title);
        cout << "\n\n\t\t\t\t\t\t\t\t\t2. Genre of Book: ";
        getline(cin, Genre);
        cout << "\n\n\t\t\t\t\t\t\t\t\t3. Author's name: ";
        getline(cin, Author);

        string insertBook_query = "insert into Book (Title,Genre,AuthorName,AdminID) values ('" + Title + "','" + Genre + "','" + Author + "','" + AdminID + "')";
        const char* q = insertBook_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            cout << endl << "\n\n\t\t\t\t\t\t\t\t\tBook is successfully added into the system." << endl;
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        }
        do
        {
            cout << "\n\t\t\t\t\t\t\t\t\tDo you want add another book? (y/n): ";
            cin >> choose;
            if (choose == 'y' || choose == 'Y')
            {
                AddBook();
            }
            else if (choose == 'n' || choose == 'N')
            {
                AdminMenu();
            }
        } while (choose != 'y' && choose != 'Y' && choose != 'n' && choose != 'N');
    }
    else if (option == 2) {
        AdminMenu();
    }
    else {
        cout << "\n\t\t\t\t\t\t\t\t\tWrong input.Press any key to continue.";
        _getch();
        AdminMenu();
    }
}
void UpdateBook() {
    system("cls");
    cout << "******************************************************************************************************************************************************************************************************************\n";
    cout << "                                                                                                         UPDATE BOOK PAGE " << endl;
    cout << "******************************************************************************************************************************************************************************************************************\n\n";
    cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "                                                                                                        BOOK DETAIL " << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";

    qstate = mysql_query(conn, "select BookID, Title, Genre, AuthorName from Book");

    if (!qstate)
    {
        printf("             |%-6s |%-30s|%-30s|%-25s", "BOOKID", "TITLE", "GENRE", "AUTHOR");
        cout << endl;
        cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";

        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            printf("             |%-6s |%-30s|%-30s|%-25s", row[0],row[1],row[2],row[3]);
            cout << endl;


        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }
     cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";

     cout << "\t\t\tEnter Book ID: ";
     cin >> BookID;
     string check_query = "select BookID from Book where  BookID= '" + BookID + "'";
     const char* cu = check_query.c_str();
     qstate = mysql_query(conn, cu);
     if (!qstate) {
         res = mysql_store_result(conn);
         if (res->row_count > 0) {
             while (row = mysql_fetch_row(res))
             {


                 string title, genre, author;

                 int chooseUpdate = 0;

                 do
                 {
                     system("cls");
                     string search_query = "select BookID, Title, Genre,AuthorName from Book where BookID = '" + BookID + "'";
                     const char* q = search_query.c_str();
                     qstate = mysql_query(conn, q);
                     res = mysql_store_result(conn);
                     while (row = mysql_fetch_row(res))
                     {
                         cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
                         cout<<"                                                                                       Current detail of Book ID "<<row[0]
                         <<endl<<  "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";

                         cout << "\t\t\t\tBook ID: " << row[0] << " (Uneditable)"
                             << "\n\n\t\t\t\t1. Title: " << row[1]
                             << "\n\n\t\t\t\t2. Genre: " << row[2]
                             << "\n\n\t\t\t\t3. Author:  " << row[3]
                             << "\n\n\t\t\t\t4. Menu";

                     }
                     cout << "\n\t\t\t\tChoose one: ";
                     cin >> chooseUpdate;
                     cin.ignore(1, '\n');
                     if (chooseUpdate == 1)
                     {
                         cout << "\n\t\t\t\tInsert New Title: ";
                         getline(cin, title);
                         string update_query = "update Book set Title = '" + title + "' where BookID = '" + BookID + "'";
                         const char* q = update_query.c_str();
                         qstate = mysql_query(conn, q);
                     }
                     else if (chooseUpdate == 2)
                     {
                         cout << "\n\t\t\t\tInsert New Genre: ";
                         getline(cin, genre);

                         string update_query = "update Book set Genre = '" + genre + "' where BookID = '" + BookID + "'";
                         const char* q = update_query.c_str();
                         qstate = mysql_query(conn, q);
                     }
                     else if (chooseUpdate == 3)
                     {
                         cout << "\n\t\t\t\tInsert New Author: ";
                         getline(cin, author);
                         string update_query = "update Book set AuthorName = '" + author + "' where BookID = '" + BookID + "'";
                         const char* q = update_query.c_str();
                         qstate = mysql_query(conn, q);

                     }

                     else if (chooseUpdate == 4)
                     {
                         AdminMenu();
                     }
                 } while (true);
             }
         }
         else {
             cout << "\n\n\t\t\t\tWrong ID!!Press Enter to try again\n";
                 _getch();
             UpdateBook();
         }
     }

}

void UpdateBorrowerStatus(){
     string Status = "Paid",StatusPayment= "Overdue",StatusFine="No charge";
     
    system("cls");

    cout << "******************************************************************************************************************************************************************************************************************\n";
    cout << "                                                                                                         UPDATE BORROWER'S STATUS PAGE " << endl;
    cout << "******************************************************************************************************************************************************************************************************************\n\n";

    qstate = mysql_query(conn, "select t.TransactionID, bk.Title, br.BorrowName, t.StatusPayment,t.StatusReturn,t.ReturnBookDate,t.Return_Date from BORROWER br inner join Borrow t on br.BorrowID = t.BorrowID inner join BOOK bk on t.BookID = bk.BookID WHERE t.StatusPayment='No fine'");

    if (!qstate)
    {
        printf("             |%-15s |%-30s|%-30s|%-15s |%-15s |%-20s |%-25s|", "TRANSACTION ID", "TITLE", "BORROWER'S NAME", "STATUS PAYMENT","STATUS BOOK","DATE BOOK RETURNED","SUPPOSED RETURN DATE");
        cout << endl;
        cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
       
        res = mysql_store_result(conn);
        
        if (res->row_count > 0) {

            while (row = mysql_fetch_row(res))
            {
                printf("             |%-15s |%-30s|%-30s|%-15s |%-15s |%-20s |%-25s|", row[0], row[1], row[2], row[3], row[4], row[5], row[6]);
                cout << endl;

            }
        }
        else {
            cout << "\n\t\tCurrently all borrower status have changed either overdue,paid or no charge.\n\t\tPress enter to continue.";
            _getch();
            AdminMenu();
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }
    cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

    cout << "\n\t\t\t\t\t\t\t\tEnter Transaction ID: ";
    cin >> TransactionID; // Global Variable
    string check_query = "select TransactionID from Borrow where  TransactionID= '" + TransactionID + "' AND StatusPayment='No Fine'";
    const char* cu = check_query.c_str();
    qstate = mysql_query(conn, cu);
    if (!qstate) {
        res = mysql_store_result(conn);
        if (res->row_count > 0) {
            while (row = mysql_fetch_row(res))
            {
                int choose = 0;

                do {
                    system("cls");
                    string search_query = "select TransactionID, StatusPayment, Borrow_Date, Return_Date,StatusReturn from Borrow where TransactionID = '" + TransactionID + "'";
                    const char* q = search_query.c_str();
                    qstate = mysql_query(conn, q);
                    res = mysql_store_result(conn);
                    while (row = mysql_fetch_row(res))
                    {
                        cout << "\n\t\t\t\t\t\t\t\t------ Status Payment for Transaction ID "<<row[0]<<" that you have enter------\n" << endl;
                        cout << "\t\t\t\t\t\t\t\tTransaction ID: " << row[0]
                            << "\n\n\t\t\t\t\t\t\t\tStatus Payment : " << row[1]
                            << "\n\n\t\t\t\t\t\t\t\tChoose below to change status payment to :"
                            << "\n\n\t\t\t\t\t\t\t\t1.Overdue if book was return late"
                            << "\n\n\t\t\t\t\t\t\t\t2.No charge if borrower return book on return date"
                            << "\n\n\t\t\t\t\t\t\t\t3.Return to menu";

                    }
                    cout << "\n\n\t\t\t\t\t\t\t\tChoose one: ";
                    cin >> choose;
                    cin.ignore(1, '\n');
                    if (choose == 1) {

                        string update_query = "update Borrow set StatusPayment = '" + StatusPayment + "' where TransactionID = '" + TransactionID + "'";
                        const char* q = update_query.c_str();
                        qstate = mysql_query(conn, q);
                    }
                    if (choose == 2) {

                        string update_query = "update Borrow set StatusPayment = '" + StatusFine + "' where TransactionID = '" + TransactionID + "'";
                        const char* q = update_query.c_str();
                        qstate = mysql_query(conn, q);
                    }
                    else if (choose == 3) {
                        AdminMenu();
                    }
                } while (true);
            }
        }
        else {
            cout << "\n\t\t\t\t\t\t\t\tWrong Transaction ID.Press any key to continue.";
            _getch();
            UpdateBorrowerStatus();
        }
    }
    else {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }
}
void ListBook(){
    system("cls");
    string choose;

    cout << "                                                                                                List of All Book " << endl;

    qstate = mysql_query(conn, "select BookID, Title, Genre, AuthorName,Availability from Book");

    if (!qstate)
    {
        cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
        printf("          |%-6s|%-30s|%-30s|%-25s|%-15s|", "BOOKID", "TITLE", "GENRE", "AUTHOR", "AVAILABILITY");

        cout << endl;
        cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            printf("          |%-6s|%-30s|%-30s|%-25s|%-15s|", row[0], row[1], row[2], row[3], row[4]);
            cout << endl;
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }
    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

    qstate2 = mysql_query(conn, "select count(BookID), count(DISTINCT Genre), COUNT(DISTINCT AuthorName) from Book");
    res = mysql_store_result(conn);
    while (row = mysql_fetch_row(res))
    {
        cout << "\n\t\tTotal book in system:" << row[0]
            << "\n\t\tTotal number Genre:" << row[1]
            << "\n\t\tTotal number of Author:" << row[2]<<endl;
    }
    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

    cout << "\n\t\t\t\t\t\tAdmin Menu(Y) ";
    cout << "or Any key to logout";
    cout << "\n\n\t\t\t\t\t\tChoice:";
    cin >> choose;
 
    if (choose == "y" || choose == "Y") {
        AdminMenu();
    }
    else {
        main();
    }
    

}

void ReturnBook() {
    system("cls");
 
    string option, StatusReturn = "Return",StatusAvailability="Yes";
    cout << "_________________________________________________________________________________________________________________________________________________________________________________________________________________" << endl;
    cout << "                                                                              \t             THIS IS RETURN BOOK PAGE" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl;

    cout << "\t\t\t\t                                                             List of Borrowing Info" << endl<<endl;
    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl;

    qstate = mysql_query(conn, "select t.TransactionID, bk.Title,bk.BookID, br.BorrowName, t.StatusPayment,t.StatusReturn,t.ReturnBookDate,t.Return_Date from BORROWER br inner join Borrow t on br.BorrowID = t.BorrowID inner join BOOK bk on t.BookID = bk.BookID where StatusReturn='Not Return'");

    if (!qstate)
    {
        printf("          |%-15s|%-6s |%-30s|%-25s|%-15s|%-15s|%-20s|%-22s|", "TRANSACTION ID","BOOKID", "TITLE", "BORROWER'S NAME", "STATUS PAYMENT", "STATUS RETURN","DATE BOOK RETURN","SUPPOSED RETURN DATE");
        cout << endl;
         cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
        res = mysql_store_result(conn);
        if (res->row_count > 0) {

            while (row = mysql_fetch_row(res))
            {
                printf("          |%-15s|%-6s |%-30s|%-25s|%-15s|%-15s|%-20s|%-22s|", row[0], row[2], row[1], row[3], row[4], row[5], row[6], row[7]);
                cout << endl;

            }
        }
        else {
            cout << "\n\t\tCurrently all book has been return.So the list is empty.Press enter to continue.\n";
            _getch();
            AdminMenu();
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    cout << "\n\n-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl;
    cout << "\n\t\tDo you want to continue?Press(Y/N)";
    string choose;
    cin >> choose;
    if (choose == "Y" || choose == "y") {
        cout << "\n\t\t 1. Enter Transaction ID: ";
        cin >> TransactionID; // Global Variable
        cout << "\n\t\t 2. Enter BookID: ";
        cin >> BookID;

        string check_query = "select b.TransactionID,k.BookID from Borrow b inner join Book k on b.BookID=k.BookID where  b.TransactionID= '" + TransactionID + "' and b.BookID = '" + BookID + "' AND StatusReturn='Not Return'";
        const char* cu = check_query.c_str();
        qstate = mysql_query(conn, cu);

        if (!qstate)
        {
            res = mysql_store_result(conn);
            if (res->row_count == 1)
            {
                while (row = mysql_fetch_row(res)) {
                    string ReturnBookDate;

                    cin.ignore(1, '\n');
                    cout << "\n\n\t\t 3. Enter date book was return(dd/mm/yyyy):";
                    getline(cin, ReturnBookDate);
                    string UpdateBorrowing_query = "UPDATE `borrow` SET `ReturnBookDate` = STR_TO_DATE('" + ReturnBookDate + "','%d/%m/%Y') WHERE TransactionID = '" + TransactionID + "'";
                    const char* q = UpdateBorrowing_query.c_str();
                    qstate = mysql_query(conn, q);
                    string UpdateStatus_query = "UPDATE `borrow` SET `StatusReturn` = '" + StatusReturn + "' WHERE TransactionID = '" + TransactionID + "'";
                    const char* q2 = UpdateStatus_query.c_str();
                    qstate2 = mysql_query(conn, q2);
                    string updateAvailable_query = "update Book set Availability = '" + StatusAvailability + "' where BookID = '" + BookID + "'";
                    const char* q1 = updateAvailable_query.c_str();
                    qstate1 = mysql_query(conn, q1);
                }
                cout << "\n\n-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl;

                cout << "\t\t\t\t                                                              List of Borrowing Info " << endl;
                cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl;

                string display = "select t.TransactionID, bk.Title, br.BorrowName, t.StatusPayment,t.StatusReturn,t.ReturnBookDate,t.Return_Date from BORROWER br inner join Borrow t on br.BorrowID = t.BorrowID inner join BOOK bk on t.BookID = bk.BookID where t.TransactionID='" + TransactionID + "'";
                const char* q = display.c_str();
                qstate = mysql_query(conn, q);
                if (!qstate)
                {
                    printf("          |%-15s|%-30s|%-25s|%-15s|%-15s|%-20s|%-22s|", "TRANSACTION ID", "TITLE", "BORROWER'S NAME", "STATUS PAYMENT", "STATUS RETURN", "DATE BOOK RETURN", "SUPPOSED RETURN DATE");
                    cout << endl;
                    cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
                    res = mysql_store_result(conn);
                    while (row = mysql_fetch_row(res))
                    {
                        printf("          |%-15s|%-30s|%-25s|%-15s|%-15s|%-20s|%-22s|", row[0], row[1], row[2], row[3], row[4], row[5], row[6]);
                        cout << endl;

                    }
                    string check_query = "UPDATE borrow SET Duration=(SELECT DATEDIFF(ReturnBookDate,Return_Date) WHERE TransactionID='" + TransactionID + "')";
                    const char* q2 = check_query.c_str();
                    qstate2 = mysql_query(conn, q2);
                }
                else
                {
                    cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
                }

            }
            else
            {

                cout << "\n\tYou have enter mismatch ID between TransactionID and BookID!Press Enter to try again ";
                _getch();
                ReturnBook();

            }
        }
        else {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        }

        cout << "\n\t\tDo you want to continue? Press(Y/N)";
        cin >> option;
        if (option == "Y" || option == "y") {
            AdminMenu();
        }
        else if (option == "N" || option == "n") {
            main();
        }
    }
    else if (choose == "N" || choose == "n") {
        AdminMenu();
    }
}
void ListBorrowedBook(){
     system("cls");
    string choose;
    cout << "******************************************************************************************************************************************************************************************************************\n";
    cout << "                                                                                           YOUR HISTORY OF BORROWING DETAIL  " << endl;
    cout << "******************************************************************************************************************************************************************************************************************\n";

    string search_query = "SELECT borrower.BorrowID,borrow.TransactionID,book.BookID,book.Title,borrow.StatusPayment,borrow.StatusReturn FROM Borrow INNER JOIN Borrower ON borrower.BorrowID=borrow.BorrowID INNER JOIN Book book ON borrow.BookID=book.BookID WHERE borrower.BorrowID ='"+BorrowID+"'";
    const char* q = search_query.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate)
    {
        cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

        printf("\t\t\t\t\t|%-6s|%-15s |%-6s |%-30s |%-15s |%-15s|", "BORROW ID", "TRANSACTION ID" ,"BOOKID", "TITLE", "STATUS PAYMENT", "STATUS RETURN");
        cout << endl;
        cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl;

        res = mysql_store_result(conn);
        if (res->row_count > 0) {
            while (row = mysql_fetch_row(res))
            {
                printf("\t\t\t\t\t|%-6s   |%-15s |%-6s |%-30s |%-15s |%-15s|", row[0], row[1], row[2], row[3], row[4], row[5]);
                cout << endl;

            }
        }
        else {
            cout << "\n\n\t\t\t\tYou have not borrow any book yet";
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    string choice;
    cout << "\n\n\n\t\t\t\tDo you want continue?Press Y to go back.Any key to main menu\n\n ";
    cin >> choice;
    if (choice == "y" || choice == "Y") {
        BorrowerMenu();
    }
    else {
        main();
    }
   
    
}

void DateCount() {
    system("cls");
    cout << "\t\t\t\t                                            List of Borrowing Info of Book That have been Returned " << endl<<endl;

    qstate = mysql_query(conn, "select t.TransactionID, bk.Title, br.BorrowName, t.StatusPayment,t.ReturnBookDate from BORROWER br inner join Borrow t on br.BorrowID = t.BorrowID inner join BOOK bk on t.BookID = bk.BookID where t.StatusReturn='Return' AND t.StatusPayment='Overdue'");

    if (!qstate)
    {
        cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
        printf("          |%-15s|%-30s|%-25s|%-15s|%-20s|", "TRANSACTION ID", "TITLE", "BORROWER'S NAME", "STATUS PAYMENT","DATE BOOK RETURN");
        cout << endl;
        cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
        res = mysql_store_result(conn);
        if (res->row_count > 0) {
            while (row = mysql_fetch_row(res))
            {
                printf("          |%-15s|%-30s|%-25s|%-15s|%-20s|", row[0], row[1], row[2], row[3], row[4]);
                cout << endl;

            }
            cout << "\n\n\t\tPress (Y) to continue or any key to go back :";
            string option;
            cin >> option;
            if (option == "Y" || option == "y") {
                cout << "\n\t\tEnter Transaction ID:";
                cin >> TransactionID;
                system("cls");
                string check_query = "select TransactionID from Borrow where TransactionID = '" + TransactionID + "' AND StatusReturn='Return' AND StatusPayment='Overdue'";
                const char* q2 = check_query.c_str();
                qstate2 = mysql_query(conn, q2);

                if (!qstate2)
                {
                    res = mysql_store_result(conn);
                    if (res->row_count == 1)
                    {
                        while (row = mysql_fetch_row(res)) {

                            string show_query = "select TransactionID, StatusPayment, Borrow_Date, Return_Date,ReturnBookDate from Borrow where TransactionID = '" + TransactionID + "'";
                            const char* q = show_query.c_str();
                            qstate = mysql_query(conn, q);
                            if (!qstate) {
                                res = mysql_store_result(conn);
                                while (row = mysql_fetch_row(res))
                                {
                                    cout << "\n\n\t\t--- Status Payment for current Transaction ID that you have enter--" << endl;
                                    cout << "\n\t\tTransaction ID: " << row[0]
                                        << "\n\n\t\t Borrow Date : " << row[2]
                                        << "\n\n\t\tDate Book Supposed to return:" << row[3]
                                        << "\n\n\t\tDate Book is return:" << row[4];
                                    _getch();
                                    Sambungan();

                                }
                            }
                        }
                    }
                    else
                    {
                        cout << "\n\n\t\tWrong Transaction ID.Press enter to continue ";
                        _getch();
                        DateCount();
                    }
                }
                else
                    cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            }
            else {
                AdminMenu();
            }
        }
        else {
            cout << "\n         List is empty because all borrower either have paid or return book on due";
            cout << "\n\n\t\t\t Press enter to continue";
            _getch();
            AdminMenu();
            
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }
   
}
void Sambungan(){
    string Status = "Paid";
    
    string show_query = "Update Borrow set Duration =DATEDIFF(ReturnBookDate,Return_Date) where TransactionID='"+TransactionID+"'"; 
    const char* q = show_query.c_str();
    qstate = mysql_query(conn, q);
    string showduration_query = "Select Duration from borrow where TransactionID='" + TransactionID + "'";
    const char* q2 = showduration_query.c_str();
    qstate2 = mysql_query(conn, q2);

    if (!qstate2) {
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout<< "\n\n\t\tTotal days book was return late:" << row[0];

            string choice;
            double days;

            double fine = 0;
            cout << "\n\n\t\tEnter total days book was return late: ";
            cin >> days;

            if (days <= 0)
            {
                fine = 0;
            }
            else 
            {
                fine = days  * 0.5;
            }
           

            cout << "\n\n\t\tYour fine:RM " << fine;
            cout << "\n\n\t\t Update user payment status?";
            cout << "\n\t\t Y--> Update Payment Status / Any key--> Menu" << endl;
                cin >> choice;
            if (choice == "Y" || choice == "y") {
                system("cls");
                string search_query = "select TransactionID, StatusPayment, Borrow_Date, Return_Date,StatusReturn from Borrow where TransactionID = '" + TransactionID + "'";
                const char* q = search_query.c_str();
                qstate = mysql_query(conn, q);
                res = mysql_store_result(conn);
                while (row = mysql_fetch_row(res))
                {   cout << "\n\t\t--- Status Payment for current Transaction ID that you have enter--\n" << endl;
                    cout << "\t\tTransaction ID: " << row[0]
                        << "\n\n\t\t1.Status Payment : " << row[1];}
                int choice;
                cout << "\n\t\tPress 1 to pay. Press any keys to go back: ";
                cin >> choice;
                cin.ignore(1, '\n');

                if (choice == 1)
                {
                    string update_query = "update Borrow set StatusPayment = '" + Status + "' where TransactionID = '" + TransactionID + "'";
                    const char* q = update_query.c_str();
                    qstate = mysql_query(conn, q); string search_query = "select TransactionID, StatusPayment, Borrow_Date, Return_Date,StatusReturn from Borrow where TransactionID = '" + TransactionID + "'";
                    const char* q2 = search_query.c_str();
                    qstate2 = mysql_query(conn, q2);
                    res = mysql_store_result(conn);
                    while (row = mysql_fetch_row(res)) {
                        system("cls");
                        cout << "\n\t\t--- Status Payment for current Transaction ID that you have enter--\n" << endl;
                        cout << "\t\tTransaction ID: " << row[0]
                            << "\n\n\t\t1.Status Payment : " << row[1];
                    }
                    cout << "\n\n\t\tY-->continue"
                        << "\n\n\t\tM-->Main Menu"
                        << "\n\n\t\tInput:";
                    string input;
                    cin >> input;
                    if (input == "Y" || input == "y") {
                        AdminMenu();
                   }
                    else if (input == "M" || input == "m") {
                        main();
                    }
                    else {
                        cout << "\n\t\tYou enter wrong input. You will be brought to menu";
                        _getch();
                        AdminMenu();
                       
                    }
                }
                else {
                    _getch();
                    AdminMenu();}}
      else {
                _getch();
                AdminMenu();}} }}

void DeleteBorrower() {
    system("cls");
    cout << "******************************************************************************************************************************************************************************************************************\n";
    cout << "                                                                                                        BORROWER INFO PAGE " << endl;
    cout << "******************************************************************************************************************************************************************************************************************\n\n";
    
    cout << "\t\t\t\t                                                                   List of All User " << endl;
    cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

    qstate = mysql_query(conn, "select BorrowID, BorrowName, BorrowEmail, BorrowPhone from Borrower");

    if (!qstate)
    {
        printf("          |%-10s|%-30s|%-30s|%-15s|", "BORROW ID", "BORROWER'S NAME", "BORROWER'S EMAIL", "PHONE NUMBER");
        cout << endl;
 cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            printf("          |%-10s|%-30s|%-30s|%-15s|", row[0], row[1], row[2], row[3]);
            cout << endl;
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }
    cout << "\n\t\tDelete User(D) OR Update User(U) OR Any key to Menu"<<endl;
    string option;
    cout << "\t\tChoice:";
    cin >> option;
    if (option == "D" || option == "d") {
        Delete();
    }
    else if (option == "U" || option == "u") {
        cout << "\n\t\tEnter BorrowID:";
        cin >> BorrowID;
        string check_query = "select BorrowID from Borrower where  BorrowID= '" + BorrowID + "'";
        const char* cu = check_query.c_str();
        qstate = mysql_query(conn, cu);
        if (!qstate) {
            res = mysql_store_result(conn);
            if (res->row_count > 0) {
                while (row = mysql_fetch_row(res))
                {
                    system("cls");

                    cout << "******************************************************************************************************************************************************************************************************************\n";
                    cout << "                                                                                                         UPDATE INFO PAGE " << endl;
                    cout << "******************************************************************************************************************************************************************************************************************\n\n";
                    string name, email, password, phone;
                    string choose;

                    int chooseUpdate = 0;

                    do
                    {

                        string search_query = "select BorrowID, BorrowName, BorrowEmail, BorrowPassword,BorrowPhone from Borrower where BorrowID = '" + BorrowID + "'";
                        const char* q = search_query.c_str();
                        qstate = mysql_query(conn, q);
                        res = mysql_store_result(conn);
                        while (row = mysql_fetch_row(res))
                        {
                            cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
                            cout << "                                                                                                        YOUR DETAIL " << endl;
                            cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
                            cout << "\n\t\t\t\t\t\t\t\tYour ID: " << row[0] << " (Uneditable)"
                                << "\n\n\t\t\t\t\t\t\t\t1. Name: " << row[1]
                                << "\n\n\t\t\t\t\t\t\t\t2. Email: " << row[2]
                                << "\n\n\t\t\t\t\t\t\t\t3. Password:  " << row[3]
                                << "\n\n\t\t\t\t\t\t\t\t4. Phone Number: " << row[4]
                                << "\n\n\t\t\t\t\t\t\t\t 5. Menu";
                        }
                        cout << "\n\t\t\t\t\t\t\t\tChoose one: ";
                        cin >> chooseUpdate;
                        cin.ignore(1, '\n');
                        if (chooseUpdate == 1)
                        {
                            cout << "\n\n\t\t\t\t\t\t\t\tInsert New Title: ";
                            getline(cin, name);
                            string update_query = "update Borrower set BorrowName = '" + name + "' where BorrowID = '" + BorrowID + "'";
                            const char* q = update_query.c_str();
                            qstate = mysql_query(conn, q);
                            string search_query = "select BorrowID, BorrowName, BorrowEmail, BorrowPassword,BorrowPhone from Borrower where BorrowID = '" + BorrowID + "'";
                            const char* q2 = search_query.c_str();
                            qstate2 = mysql_query(conn, q2);
                            res = mysql_store_result(conn);
                            while (row = mysql_fetch_row(res))
                            {

                                cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
                                cout << "                                                                                                        YOUR DETAIL " << endl;
                                cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
                                cout << "\n\t\t\t\t\t\t\t\tYour ID: " << row[0] << " (Uneditable)"
                                    << "\n\n\t\t\t\t\t\t\t\t1. Name: " << row[1]
                                    << "\n\n\t\t\t\t\t\t\t\t2. Email: " << row[2]
                                    << "\n\n\t\t\t\t\t\t\t\t3. Password:  " << row[3]
                                    << "\n\n\t\t\t\t\t\t\t\t4. Phone Number: " << row[4]
                                    << "\n\n\t\t\t\t\t\t\t\t 5. Menu";
                            }

                            cout << "\n\n\t\t\t\t\t\t\t\tDo you want to go back? (Y/N) ";
                            cin >> choose;
                            if (choose == "y" || choose == "Y") {
                                AdminMenu();
                            }
                            else if (choose == "n" || choose == "N") {
                                main();
                            }
                            else {
                                cout << "\t\tWrong input. You will be direct to menu";
                                _getch();
                                AdminMenu();
                            }
                        }
                        else if (chooseUpdate == 2)
                        {
                            cout << "\n\n\t\t\t\t\t\t\t\tInsert New Email: ";
                            cin >> email;
                            string update_query = "update Borrower set BorrowEmail = '" + email + "' where BorrowID = '" + BorrowID + "'";
                            const char* q = update_query.c_str();
                            qstate = mysql_query(conn, q);
                            string search_query = "select BorrowID, BorrowName, BorrowEmail, BorrowPassword,BorrowPhone from Borrower where BorrowID = '" + BorrowID + "'";
                            const char* q2 = search_query.c_str();
                            qstate2 = mysql_query(conn, q2);
                            res = mysql_store_result(conn);
                            while (row = mysql_fetch_row(res))
                            {

                                cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
                                cout << "                                                                                                        YOUR DETAIL " << endl;
                                cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
                                cout << "\n\t\t\t\t\t\t\t\tYour ID: " << row[0] << " (Uneditable)"
                                    << "\n\n\t\t\t\t\t\t\t\t1. Name: " << row[1]
                                    << "\n\n\t\t\t\t\t\t\t\t2. Email: " << row[2]
                                    << "\n\n\t\t\t\t\t\t\t\t3. Password:  " << row[3]
                                    << "\n\n\t\t\t\t\t\t\t\t4. Phone Number: " << row[4]
                                    << "\n\n\t\t\t\t\t\t\t\t 5. Menu";
                            }
                            cout << "\n\n\t\t\t\t\t\t\t\tDo you want to go back? (Y/N) ";
                            cin >> choose;
                            if (choose == "y" || choose == "Y") {
                                AdminMenu();
                            }
                            else if (choose == "n" || choose == "N") {
                                main();
                            }
                            else {
                                cout << "\t\tWrong input. You will be direct to menu";
                                _getch();
                                AdminMenu();
                            }
                        }
                        else if (chooseUpdate == 3)
                        {
                            cout << "\n\n\t\t\t\t\t\t\t\tInsert New Password:  ";
                            getline(cin, password);
                            string update_query = "update Borrower set BorrowPassword = '" + password + "' where BorrowID = '" + BorrowID + "'";
                            const char* q = update_query.c_str();
                            qstate = mysql_query(conn, q);
                            string search_query = "select BorrowID, BorrowName, BorrowEmail, BorrowPassword,BorrowPhone from Borrower where BorrowID = '" + BorrowID + "'";
                            const char* q2 = search_query.c_str();
                            qstate2 = mysql_query(conn, q2);
                            res = mysql_store_result(conn);
                            while (row = mysql_fetch_row(res))
                            {

                                cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
                                cout << "                                                                                                        YOUR DETAIL " << endl;
                                cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
                                cout << "\n\t\t\t\t\t\t\t\tYour ID: " << row[0] << " (Uneditable)"
                                    << "\n\n\t\t\t\t\t\t\t\t1. Name: " << row[1]
                                    << "\n\n\t\t\t\t\t\t\t\t2. Email: " << row[2]
                                    << "\n\n\t\t\t\t\t\t\t\t3. Password:  " << row[3]
                                    << "\n\n\t\t\t\t\t\t\t\t4. Phone Number: " << row[4]
                                    << "\n\n\t\t\t\t\t\t\t\t 5. Menu";
                            }
                            cout << "\n\n\t\t\t\t\t\t\t\tDo you want to go back?(Y/N) ";
                            cin >> choose;
                            if (choose == "y" || choose == "Y") {
                                AdminMenu();
                            }
                            else if (choose == "n" || choose == "N") {
                                main();
                            }
                            else {
                                cout << "\t\tWrong input. You will be direct to menu";
                                _getch();
                                AdminMenu();
                            }
                        }

                        else if (chooseUpdate == 4)
                        {
                            cout << "\n\n\t\t\t\t\t\t\t\tInsert New Phone Number:  ";
                            getline(cin, phone);
                            string update_query = "update Borrower set BorrowPhone = '" + phone + "' where BorrowID = '" + BorrowID + "'";
                            const char* q = update_query.c_str();
                            qstate = mysql_query(conn, q);
                            string search_query = "select BorrowID, BorrowName, BorrowEmail, BorrowPassword,BorrowPhone from Borrower where BorrowID = '" + BorrowID + "'";
                            const char* q2 = search_query.c_str();
                            qstate2 = mysql_query(conn, q2);
                            res = mysql_store_result(conn);
                            while (row = mysql_fetch_row(res))
                            {

                                cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
                                cout << "                                                                                                        YOUR DETAIL " << endl;
                                cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
                                cout << "\n\t\t\t\t\t\t\t\tYour ID: " << row[0] << " (Uneditable)"
                                    << "\n\n\t\t\t\t\t\t\t\t1. Name: " << row[1]
                                    << "\n\n\t\t\t\t\t\t\t\t2. Email: " << row[2]
                                    << "\n\n\t\t\t\t\t\t\t\t3. Password:  " << row[3]
                                    << "\n\n\t\t\t\t\t\t\t\t4. Phone Number: " << row[4]
                                    << "\n\n\t\t\t\t\t\t\t\t 5. Menu";
                            }
                            cout << "\n\n\t\t\t\t\t\t\t\tDo you want to go back? (Y/N) ";
                            cin >> choose;
                            if (choose == "y" || choose == "Y") {
                                AdminMenu();
                            }
                            else if (choose == "n" || choose == "N") {
                                main();
                            }
                            else {
                                cout << "\t\tWrong input. You will be direct to menu";
                                _getch();
                                AdminMenu();
                            }
                        }
                        else if (chooseUpdate == 5)
                        {
                            AdminMenu();
                        }
                    } while (true);
                }
            }
            else { cout << "\n\t\tThe ID you enter is not exist.Try again.Press enter";
            _getch();
            DeleteBorrower();
 }
        }
    }
    else {
      AdminMenu();
    }
}
void Delete() {
    char choose;
    cout << "\n\n\t\tEnter Borrow ID: ";
    cin >> BorrowID;
    string check_query = "select BorrowID from Borrower where BorrowID= '" + BorrowID + "'";
    const char* cu = check_query.c_str();
    qstate = mysql_query(conn, cu);

    if (!qstate)
    {
        res = mysql_store_result(conn);
        if (res->row_count == 1)
        {
            while (row = mysql_fetch_row(res)) {

                cout << "\n\n\t\tAre you sure want to remove this User? (y/n): ";
                cin >> choose;
                if (choose == 'y' || choose == 'Y')
                {
                    string delete_query = "delete from Borrower where BorrowID = '" + BorrowID + "'";
                    const char* q = delete_query.c_str();
                    qstate = mysql_query(conn, q);
                    if (!qstate)
                    {
                        cout << "\n\t\tThis user has been removed. Press Enter to Continue...";
                        _getch();
                        AdminMenu();

                    }
                    else
                    {

                        cout << "\t\tCannot delete because this user is an active user\n\t\tPress enter to continue" << endl;
                        _getch();
                        AdminMenu();
                    }
                }
                else if (choose == 'n' || choose == 'N')
                {
                    AdminMenu();
                }
            }
        }
        else {
            cout << "\n\t\tWhops! ID you enter is not exist.Press enter to try again\n";
            _getch();
            DeleteBorrower();
        }
    }
}
void Info() {
    system("cls");
    
    cout << "******************************************************************************************************************************************************************************************************************\n";
    cout << "                                                                                                         UPDATE INFO PAGE " << endl;
    cout << "******************************************************************************************************************************************************************************************************************\n\n";
    string name, email, password,phone;
    string choose;

    int chooseUpdate = 0;

    do
    {
       
        string search_query = "select BorrowID, BorrowName, BorrowEmail, BorrowPassword,BorrowPhone from Borrower where BorrowID = '" + BorrowID + "'";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
            cout << "                                                                                                        YOUR DETAIL " << endl;
            cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
            cout << "\n\t\t\t\t\t\t\t\t\t\t\tYour ID: " << row[0] << " (Uneditable)"
                << "\n\n\t\t\t\t\t\t\t\t\t\t\t1. Name: " << row[1]
                << "\n\n\t\t\t\t\t\t\t\t\t\t\t2. Email: " << row[2]
                << "\n\n\t\t\t\t\t\t\t\t\t\t\t3. Password:  " << row[3]
                << "\n\n\t\t\t\t\t\t\t\t\t\t\t4. Phone Number: "<<row[4]
                << "\n\n\t\t\t\t\t\t\t\t\t\t\t5. Menu";
        }
        cout << "\n\n\t\t\t\t\t\t\t\t\t\t   Choose one: ";
        cin >> chooseUpdate;
        cin.ignore(1, '\n');
        if (chooseUpdate == 1)
        {
            cout << "\n\n\t\t\t\t\t\t\t\t\t\tInsert New Title: ";
            getline(cin, name);
            string update_query = "update Borrower set BorrowName = '" + name + "' where BorrowID = '" + BorrowID + "'";
            const char* q = update_query.c_str();
            qstate = mysql_query(conn, q);
            string search_query = "select BorrowID, BorrowName, BorrowEmail, BorrowPassword,BorrowPhone from Borrower where BorrowID = '" + BorrowID + "'";
            const char* q2 = search_query.c_str();
            qstate2 = mysql_query(conn, q2);
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {

                cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
                cout << "                                                                                                        YOUR DETAIL " << endl;
                cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
                cout << "\n\t\t\t\t\t\t\t\t\t\t\tYour ID: " << row[0] << " (Uneditable)"
                    << "\n\n\t\t\t\t\t\t\t\t\t\t\t1. Name: " << row[1]
                    << "\n\n\t\t\t\t\t\t\t\t\t\t\t2. Email: " << row[2]
                    << "\n\n\t\t\t\t\t\t\t\t\t\t\t3. Password:  " << row[3]
                    << "\n\n\t\t\t\t\t\t\t\t\t\t\t4. Phone Number: " << row[4];
                   
            }

            cout << "\n\n\t\t\t\t\t\t\t\tDo you want to continue update? (Y/N) ";
            cin >> choose;
            if (choose == "y" || choose == "Y") {
                Info();
            }
            else if (choose == "n" || choose == "N") {
                BorrowerMenu();
            }
        }
        else if (chooseUpdate == 2)
        {
            cout << "\n\n\t\t\t\t\t\t\t\t\t\tInsert New Email: ";
            cin >> email;
            string update_query = "update Borrower set BorrowEmail = '" + email + "' where BorrowID = '" + BorrowID + "'";
            const char* q = update_query.c_str();
            qstate = mysql_query(conn, q);
            string search_query = "select BorrowID, BorrowName, BorrowEmail, BorrowPassword,BorrowPhone from Borrower where BorrowID = '" + BorrowID + "'";
            const char* q2 = search_query.c_str();
            qstate2 = mysql_query(conn, q2);
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {

                cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
                cout << "                                                                                                        YOUR DETAIL " << endl;
                cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
                cout << "\n\t\t\t\t\t\t\t\t\t\t\tYour ID: " << row[0] << " (Uneditable)"
                    << "\n\n\t\t\t\t\t\t\t\t\t\t\t1. Name: " << row[1]
                    << "\n\n\t\t\t\t\t\t\t\t\t\t\t2. Email: " << row[2]
                    << "\n\n\t\t\t\t\t\t\t\t\t\t\t3. Password:  " << row[3]
                    << "\n\n\t\t\t\t\t\t\t\t\t\t\t4. Phone Number: " << row[4];
                   
            }
            cout << "\n\n\t\t\t\t\t\t\t\t\t\tDo you want to continue update? (Y/N) ";
            cin >> choose;
            if (choose == "y" || choose == "Y") {
                Info();
            }
            else if (choose == "n" || choose == "N") {
                BorrowerMenu();
            }
        }
        else if (chooseUpdate == 3)
        {
            cout << "\n\n\t\t\t\t\t\t\t\t\t\tInsert New Password:  ";
            getline(cin, password);
            string update_query = "update Borrower set BorrowPassword = '" + password + "' where BorrowID = '" + BorrowID + "'";
            const char* q = update_query.c_str();
            qstate = mysql_query(conn, q);
            string search_query = "select BorrowID, BorrowName, BorrowEmail, BorrowPassword,BorrowPhone from Borrower where BorrowID = '" + BorrowID + "'";
            const char* q2 = search_query.c_str();
            qstate2 = mysql_query(conn, q2);
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {

                cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
                cout << "                                                                                                        YOUR DETAIL " << endl;
                cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
                cout << "\n\t\t\t\t\t\t\t\t\t\t\tYour ID: " << row[0] << " (Uneditable)"
                    << "\n\n\t\t\t\t\t\t\t\t\t\t\t1. Name: " << row[1]
                    << "\n\n\t\t\t\t\t\t\t\t\t\t\t2. Email: " << row[2]
                    << "\n\n\t\t\t\t\t\t\t\t\t\t\t3. Password:  " << row[3]
                    << "\n\n\t\t\t\t\t\t\t\t\t\t\t4. Phone Number: " << row[4];
                    
            }
            cout << "\n\n\t\t\t\t\t\t\t\t\t\tDo you want to continue update?(Y/N) ";
            cin >> choose;
            if (choose == "y" || choose == "Y") {
                Info();
            }
            else if (choose == "n" || choose == "N") {
                BorrowerMenu();
            }

        }

        else if (chooseUpdate == 4)
        {
            cout << "\n\n\t\t\t\t\t\t\t\t\t\tInsert New Phone Number:  ";
            getline(cin, phone);
            string update_query = "update Borrower set BorrowPhone = '" + phone + "' where BorrowID = '" + BorrowID + "'";
            const char* q = update_query.c_str();
            qstate = mysql_query(conn, q);
            string search_query = "select BorrowID, BorrowName, BorrowEmail, BorrowPassword,BorrowPhone from Borrower where BorrowID = '" + BorrowID + "'";
            const char* q2 = search_query.c_str();
            qstate2 = mysql_query(conn, q2);
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {

                cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
                cout << "                                                                                                        YOUR DETAIL " << endl;
                cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
                cout << "\n\t\t\t\t\t\t\t\t\t\t\tYour ID: " << row[0] << " (Uneditable)"
                    << "\n\n\t\t\t\t\t\t\t\t\t\t\t1. Name: " << row[1]
                    << "\n\n\t\t\t\t\t\t\t\t\t\t\t2. Email: " << row[2]
                    << "\n\n\t\t\t\t\t\t\t\t\t\t\t3. Password:  " << row[3]
                    << "\n\n\t\t\t\t\t\t\t\t\t\t\t4. Phone Number: " << row[4];
                   
            }
            cout << "\n\n\t\t\t\t\t\t\t\t\tDo you want to continue update? (Y/N) ";
            cin >> choose;
            if (choose == "y" || choose == "Y") {
                Info();
            }
            else if (choose == "n" || choose == "N") {
                BorrowerMenu();
            }
        }
        else if (chooseUpdate == 5)
        {
           BorrowerMenu();
        }
        else { cout << "\n\t\t\t\t\t\t\t\t\t\tWrong input.Press enter to try again.";
        _getch();
        Info();
 }
    } while (true);
}
void Report() {
    system("cls");
    int choose;
    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "                                                                                                      REPORT GENERATE" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\n\t\t\t\t\t\tReport through:"
        << "\n\t\t\t\t\t\t1. Borrower"
        << "\n\t\t\t\t\t\t2. Book"
        << "\n\t\t\t\t\t\t3. Menu";

    cout << "\n\t\t\t\t\t\tInput:";
    cin >> choose;
    if (choose == 1) {
        system("cls");
        string search_query = "Select DISTINCT Borrower.BorrowID,Borrower.BorrowName,count(TransactionID) from Borrower inner join Borrow on Borrower.BorrowID=Borrow.BorrowID group by borrowID ";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        cout << "___________________________________________________________________________________________________________________________________________________________________________________________________________________" << endl ;
        cout << "                                                                                                      LAMAN HIKMAH UTEM'S LIBRARY REPORT" << endl;
        cout << "                                                                                              This report will display report of library's borrower" << endl;
        cout << "                                                                                                      REPORT PREPARED BY HANIS ZAHIRA" << endl;

        cout << "___________________________________________________________________________________________________________________________________________________________________________________________________________________" << endl << endl;

        if (!qstate) {
            cout << endl;
            cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

            printf("                        |%-10s|%-30s|%-50s|", "BORROWID", "NAME", "TOTAL BOOK BORROW");

            cout << endl;
            cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
            printf("                        |%-10s|%-30s|%-50s|", row[0], row[1], row[2]);
                cout << endl;
            }
            cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl;
            string select_query = "Select count(BorrowID) from Borrower ";
            const char* q = select_query.c_str();
            qstate = mysql_query(conn, q);
            if (!qstate) {
                cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl;

                res = mysql_store_result(conn);
                while (row = mysql_fetch_row(res))
                {
                    cout << "\t\t\tTotal User of This System:" << row[0] << endl;
                }
                string select_query = "Select count(DISTINCT BorrowID) from Borrow ";
                const char* q = select_query.c_str();
                qstate = mysql_query(conn, q);
                if (!qstate) {
                    res = mysql_store_result(conn);
                    while (row = mysql_fetch_row(res))
                    {
                        cout << "\t\t\tTotal Active Borrower:" << row[0] << endl;
                    }
                    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

                    cout << "\n\t\t\t\t\t\tDo you want to continue? (Y/N)";
                    string choice;
                    cin >> choice;
                    if (choice == "Y" || choice == "y") {
                        Report();
                    }
                    else if (choice == "N" || choice == "n") { AdminMenu(); }
                    else { main(); }
                }
            }


        }
       

    }
   
    else if (choose == 2) {
        system("cls");
        cout << "___________________________________________________________________________________________________________________________________________________________________________________________________________________" << endl ;

        cout << "                                                                                           LAMAN HIKMAH UTEM'S LIBRARY REPORT" << endl;
        cout << "                                                                                    This report will display report of library's book" << endl;
        cout << "                                                                                             REPORT PREPARED BY HANIS ZAHIRA" << endl;

        cout << "___________________________________________________________________________________________________________________________________________________________________________________________________________________" << endl << endl;
        string book_query = "Select count(BookID),count(DISTINCT Genre),Count(DISTINCT AuthorName) from Book";
        const char* q1 = book_query.c_str();
        qstate1 = mysql_query(conn, q1);
        if (!qstate1) {
            cout << "                                                                                              OVERALL BOOK REPORT" << endl << endl;
            cout << "******************************************************************************************************************************************************************************************************************\n\n";

            cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

            printf("                                                                       |%-15s|%-20s|%-20s|", "TOTAL BOOK", "TOTAL GENRE", "TOTAL AUTHOR");

            cout << endl;
            cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                printf("                                                                       |%-15s|%-20s|%-20s|", row[0], row[1], row[2]);
                cout << endl;

            }
            cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl;
            cout << "                                                                                              OVERALL AUTHOR REPORT" << endl << endl;
            cout << "******************************************************************************************************************************************************************************************************************\n\n";

            string author_query = "SELECT AuthorName,count(BookID),count(genre) from Book group by AuthorName";
            const char* q = author_query.c_str();
            qstate = mysql_query(conn, q);
            if (!qstate) {
                cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

                printf("                                                                   |%-30s|%-20s|%-20s|", "AUTHOR", "TOTAL BOOK WRITTEN", "TOTAL GENRE");

                cout << endl;
                cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

                res = mysql_store_result(conn);
                while (row = mysql_fetch_row(res))
                {
                    printf("                                                                   |%-30s|%-20s|%-20s|", row[0], row[1], row[2]);

                    cout << endl;

                }
                cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl;
                cout << "                                                                                              OVERALL GENRE REPORT" << endl << endl;
                cout << "******************************************************************************************************************************************************************************************************************\n\n";

                string info_query = "SELECT DISTINCT Genre,count(Genre),count(AuthorName) from Book group by Genre";
                const char* q = info_query.c_str();
                qstate = mysql_query(conn, q);
                if (!qstate) {
                    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

                    printf("                                                                       |%-25s|%-5s|%-15s|", "GENRE", "TOTAL", "NUM OF AUTHOR");

                    cout << endl;
                    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

                    res = mysql_store_result(conn);
                    while (row = mysql_fetch_row(res))
                    {
                        printf("                                                                       |%-25s|%-5s|%-15s|", row[0], row[1], row[2]);

                        cout << endl;
                    }
                    cout << "___________________________________________________________________________________________________________________________________________________________________________________________________________________" << endl << endl;
                    cout << "\t\t\t\tDo you want to continue? (Y/N)";
                    string choice;
                    cin >> choice;
                    if (choice == "Y" || choice == "y") {
                        Report();
                    }
                    else if (choice == "N" || choice == "n") { AdminMenu(); }
                    else { main(); }
                }

            }
        }
      
    }
    else if (choose == 3) { AdminMenu(); }
}

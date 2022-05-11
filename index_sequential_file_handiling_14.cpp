#include<bits/stdc++.h>

using namespace std;

class Emp_Cls
{
    typedef struct Employee
    {
        char name[20];
        int emp_id;
        int salary;
        char desig[50];
    }Record;
    typedef struct Index
    {
        int emp_id;
        int position;
    }Index_Record;

    Record rec;
    Index_Record ind_rec;

    public:
    Emp_Cls();
    void create();
    void display();
    void update();
    void deletion();
    void append();
    void search();
};

Emp_Cls::Emp_Cls()
{
    strcpy(rec.name, "");
}

void Emp_Cls::create()
{
    int i;
    char ch = 'Y';
    fstream seqfile;
    fstream indexfile;
    i = 0;
    indexfile.open("ind.txt", ios::in | ios::out);
    seqfile.open("emp.txt", ios::in | ios::out);
    do
    {
        cout << "\n Enter name: ";
        cin >> rec.name;
        cout << "\n Enter Employee ID: ";
        cin >> rec.emp_id;
        cout << "\n Enter salary: ";
        cin >> rec.salary;
        cout << "\n Enter designation: ";
        cin >> rec.desig;

        seqfile.write((char*)&rec, sizeof(rec)) << flush;
        ind_rec.emp_id = rec.emp_id;
        ind_rec.position = i;
        indexfile.write((char*)&ind_rec, sizeof(ind_rec)) << flush;
        i++;
        cout << "\nDo You want to add more records?: ";
        cin >> ch;

    }while(ch == 'Y' || ch == 'y');
    seqfile.close();
    indexfile.close();
}

void Emp_Cls::display()
{
    fstream seqfile;
    fstream indexfile;
    int i;
    indexfile.open("ind.txt", ios::in | ios::out);
    seqfile.open("emp.txt", ios::in | ios::out);
    indexfile.seekg(0, ios::beg);
    seqfile.seekg(0, ios::beg);
    cout << "\n The contents of file are. " << endl;
    i = 0;
    while(indexfile.read((char*)&ind_rec, sizeof(ind_rec)))
    {
        i = ind_rec.position * sizeof(rec);
        seqfile.seekg(i, ios::beg);
        seqfile.read((char*)&rec, sizeof(rec));
        if(rec.emp_id != -1)
        {
            cout << "\nName: " << rec.name;
            cout << "\nEmployee ID: " << rec.emp_id;
            cout << "\nSalary: " << rec.salary;
            cout << "\nDesignation: " << rec.desig;
            cout << "\n";

            
        }
    }
    seqfile.close();
    indexfile.close();

}


void Emp_Cls::update()
{
    int pos, id;
    char new_name[20];
    char new_desig[50];
    int new_salary;
    cout << "\n For Updation: ";
    cout << "\n Enter the Employee ID for for searching: ";
    cin >> id;
    fstream seqfile;
    fstream indexfile;

    seqfile.open("emp.txt", ios::in | ios::out);
    indexfile.open("ind.txt", ios::in | ios::out);
    indexfile.seekg(0, ios::beg);

    pos = -1;
    // reading index file for getting the index
    while (indexfile.read((char*)&ind_rec, sizeof(ind_rec)))
    {
        /* code */
        if (id == ind_rec.position)
        {
            pos = ind_rec.position;
            break;
        }
    }
    if(pos == -1)
    {
        cout << "\n The record is not present in the file";
        return;
    }
    else
    {
        cout << "\n Enter the values for updation.: ";
        cout << "\n Name: ";
        cin >> new_name;
        cout << "\n Salary: ";
        cin >> new_salary;
        cout << "\n Designation: ";
        cin >> new_desig;

        // calculate position of record in seq file using pos of ind file
        int offset = pos * sizeof(rec);
        seqfile.seekp(offset); //shift pointer to desired position where we want to change/update record 
        strcpy(rec.name, new_name); //update name
        rec.emp_id = id;
        rec.salary = new_salary;
        seqfile.write((char*)&rec, sizeof(rec)) << flush;
        cout << "\n The record is updated!!!";
    }
    seqfile.close();
    indexfile.close();
    
}

void Emp_Cls::deletion()
{
    int id, pos;
    cout << "\n For deletion.";
    cout << "\n Enter the employee id for searching: ";
    cin >> id;
    fstream seqfile;
    fstream indexfile;
    seqfile.open("emp.txt", ios::in | ios::out);
    indexfile.open("ind.txt", ios::in | ios::out);
    seqfile.seekg(0, ios::beg);
    indexfile.seekg(0, ios::beg);
    pos = -1;

    // reading ind file for geeting the index 
    while(indexfile.read((char*)&ind_rec, sizeof(ind_rec)))
    {
        if (id == ind_rec.emp_id)
        {
            pos = ind_rec.position;
            ind_rec.emp_id = -1;
            break;
        }
    }
    if (pos == -1)
    {
        cout << "\n The record is not present in the file";
        return;
    }

    // calculate postition of record in seq file using pos of index file 
    int offset = pos * sizeof(rec);
    seqfile.seekp(offset);
    strcpy(rec.name, "");
    rec.emp_id = -1;//logically making deletion using redefining as -1
    rec.salary = -1;
    strcpy(rec.desig, "");
    seqfile.write((char*)&rec, sizeof(rec)) << flush;
    // writing deleted status from index file also the dired record gerts deletd as follows
    offset = pos * sizeof(ind_rec);
    indexfile.seekp(offset);
    ind_rec.emp_id = -1;
    ind_rec.position = pos;
    indexfile.write((char*)&ind_rec, sizeof(ind_rec)) << flush;
    seqfile.seekg(0);
    indexfile.close();
    seqfile.close();
    cout<<"\n The record is Deleted!!!";

}

void Emp_Cls::append()
{
    fstream seqfile;
    fstream indexfile;
    int pos;
    indexfile.open("ind.txt", ios::in | ios::out);
    indexfile.seekg(0, ios::end);
    pos = indexfile.tellg() / sizeof(ind_rec);
    indexfile.close();

    indexfile.open("ind.txt", ios::in | ios::out);
    seqfile.open("emp.txt", ios::in | ios::out);

    cout << "\n Enter the record for appending. ";
    cout << "\n Name: ";
    cin >> rec.name;
    cout << "Employee ID: ";
    cin >> rec.emp_id;
    cout << "\n Salary: ";
    cin >> rec.salary;
    cout << "\nDesignation: ";
    cin >> rec.desig;

    seqfile.write((char*)&rec, sizeof(rec));
    ind_rec.emp_id = pos;
    indexfile.write((char*)&ind_rec, sizeof(ind_rec)) << flush;
    seqfile.close();
    indexfile.close();
    cout << "\n The record is appended!!!";

}

void Emp_Cls::search()
{
    fstream seqfile;
    fstream indexfile;
    int id, pos, offset;
    cout << "\n Enter the employee ID for searching the record: ";
    cin >> id;
    while(indexfile.read((char*)&ind_rec, sizeof(ind_rec)))
    {
        if (id == ind_rec.emp_id)
        {
            pos = ind_rec.position;
            break;
        }
    }
    if (pos == -1)
    {
        cout << "\n Record is not present in the file.";
        return;
    }
    offset = pos * sizeof(rec);
    seqfile.open("emp.txt", ios::in);
    seqfile.seekg(offset, ios::beg);
    seqfile.read((char*)&rec, sizeof(rec));
    if(rec.emp_id == -1)
    {
        cout << "\n Record is not present in the file.";
        return;
    }
    else{
        cout << "\n The record is present in the file and it is...";
        cout << "\n Name: " << rec.name;
        cout << "\n Employee ID: " << rec.emp_id;
        cout << "\n Salary: " << rec.salary;
        cout << "\n Designation: " << rec.desig;
    }
    seqfile.close();
    indexfile.close();
}


int main()
{
    Emp_Cls list;
    char ans = 'Y';
    int choice;

    do
    {
        /* code */
        cout << "\n***************************** Menu *********************************" << endl;
        cout << "\n 1.Create";
        cout << "\n 2.Diaplay";
        cout << "\n 3.Update";
        cout << "\n 4.Delete";
        cout <<"\n 5.Append";
        cout <<"\n 6.Search";
        cout <<"\n 7.Exit";
        cout << "\n Enter Your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            /* code */
            list.create();
            break;
        case 2:
            /* code */
            list.display();
            break;
        case 3:
            /* code */
            list.update();
            break;
        case 4:
            /* code */
            list.deletion();
            break;
        case 5:
            /* code */
            list.append();
            break;
        case 6:
            /* code */
            list.search();
            break;
        case 7:
            /* code */
            exit(0);
            break;
       
        default:
            cout << "\n You have provided wrong information or option!";
            break;
        }

        cout << "\n\t Do you want to go back to main menu?";
        cin >> ans;

        
    } while (ans == 'Y' || ans == 'y');

    return 0;   
}
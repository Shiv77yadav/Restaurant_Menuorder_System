
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
using namespace std;

class Restaurant
{
    string CustomerName;

public:
    void showMenu()
    {
        ifstream menufile("menu.txt");
        if (!menufile)
        {
            cout << "menu file not found." << endl;
            return;
        }

        cout << "*******MENU********" << endl;
        char ch;
        while (menufile.get(ch))
        {
            cout << ch; // ek ek word likhta  h file ka
        }
        menufile.close();
    }

    void addItemToMenu()
    {

        ifstream original("menu.txt");
        ofstream temp("temp_menu.txt"); // backup k liye bnya h taki kabhi file crash ho tab data lose na ho
                                        // menu.txt ki copy bn jata h then usme itmes add krte h safe option h
        char c;
        while (original.get(c))
        {
            temp.put(c); // file ka ek ek word read krta h
        }

        int id;
        string name;
        float price;
        cout << "Enter item ID: " << endl;
        cin >> id;
        cin.ignore(); // space ko ignore krta h then next char pr chala jata h
        cout << "Enter item name: " << endl;
        getline(cin, name);
        cout << "Enter item price: " << endl;
        cin >> price;

        temp << id << " " << name << " " << price << endl;

        original.close();
        temp.close();

        remove("menu.txt");
        rename("temp_menu.txt", "menu.txt"); // temp_menu.txt ko badl kr menu.txt bna diya name change krke

        cout << "Item added" << endl;
    }

    void takeOrder()
    {
        ofstream orderFile("order.txt");
        if (!orderFile)
        {
            cout << "Error creating order file." << endl;
            return;
        }

        cout << "Enter your name: " << endl;
        
        cin.ignore(); // space ko ignore krke next char pr chala jata h

        getline(cin, CustomerName);

        char choice = 'y';
        while (choice == 'y' || choice == 'Y')
        {
            showMenu();
            int id, qty;

            cout << "Enter item ID to order: ";
            cin >> id;

            ifstream menuRead("menu.txt");
            int mid;
            string mname;
            float mprice;
            bool find = false;

            while (menuRead >> mid >> mname >> mprice)
            {
                if (mid == id) // agr enter id and file ki id match hui too if condition  m chale jayenge
                {
                    cout << "Enter quantity: ";
                    cin >> qty;

                    orderFile << mname << " " << qty << " " << mprice << endl;
                    find = true;
                    break;
                }
            }

            menuRead.close();

            if (!find)
            {
                cout << "Item not found..." << endl;
            }

            cout << "Do you want to order more? (y/n): ";

            cin >> choice;
        }

        orderFile.close();
    }
    void generatebill(string customer_name)
    {
        ifstream order("order.txt");

        if (!order)
        {
            cout << "No current order place in history." << endl;
            return;
        }

        string test;
        if (!(order >> test))
        {
            cout << "Order file is empty. no items order." << endl;

            order.close();

            return;
        }

        order.close();
        order.open("order.txt"); // taki hum dubara starting se padh sake

        string existingContent = "";

        ifstream oldHistory("orders.txt");

        if (oldHistory)
        {
            string line;

            while (getline(oldHistory, line))
            {
                existingContent += line + "\n"; // purana data overwrite na ho isliye
            }
            oldHistory.close();
        }

        string name;
        int qty;
        int price;
        float total = 0;
        string newContent;

        cout << endl
             << "--------- BILL ---------" << endl;

        cout << "Customer Name: " << customer_name << endl;

        time_t now = time(0); // real time print ho order m isliye ctime ki header file include kri
        string dt = ctime(&now);
        dt.erase(dt.find('\n'));

        cout << "Time: " << dt << endl;

        newContent += "Customer: " + customer_name + "\n";
        newContent += "Time: " + dt + "\n";

        while (order >> name >> qty >> price)
        {
            int amount = qty * price;

            total = total + amount;

            string line = name + " x " + to_string(qty) + " = Rs " + to_string(amount);

            newContent += line + "\n"; // ek string bnakr order.txt file m save kr dega
            cout << line << endl;
        }

        int tax = total * 0.05;
        int discount = 0;
        int finaltotal = total + tax;

        if (finaltotal > 1000)
        {
            discount = finaltotal * 0.10;

            finaltotal = finaltotal - discount;
        }

        cout << "Tax (5%): Rs " << tax << endl;
        if (discount > 0)
            cout << "Discount (10%): Rs " << discount << endl;

        cout << "Total Amount: Rs " << finaltotal << endl;

        newContent += "Tax: Rs " + to_string(tax) + "\n";
        if (discount > 0)

            newContent += "Discount: Rs " + to_string(discount) + "\n";

        newContent += "Total Paid: Rs " + to_string(finaltotal) + "\n"; // paise ko bhi string m badl kr file m save krenge

        newContent += "--------------------------\n";

        ofstream history("orders.txt");
        if (!history)
        {
            cout << "Unable to write to orders.txt." << endl;
            return;
        }

        history << existingContent;
        history << newContent;

        order.close();
        history.close();
        remove("order.txt");
    }

    void viewHistory()
    {
        ifstream file("orders.txt");
        if (!file)
        {
            cout << "No previous orders in file." << endl;
            return;
        }

        cout << "\n***********ORDER HISTORY ***********" << endl;
        char ch;
        while (file.get(ch))
        {
            cout << ch;
        }
        file.close();
    }

    void searchItem()
    {
        ifstream menu("menu.txt");
        if (!menu)
        {
            cout << "Menu file missing." << endl;
            return;

        }

        string input;
        cout << "Enter part of item name to search: " << endl;
        cin >> input;

        int id;
        string name;
        float price;
        bool check = false;

        while (menu >> id >> name >> price)
        {
            bool match = false;

            for (int i = 0; i <= name.size() - input.size(); i++)
            { // ye file m item name and mne jo naam search kiya h usme koi bhi
                // char agar match ho gya too ye loop kaam krega and jis naam m bhi wo char aayega
                // usko terminal pr print kr dega
                int j;
                for (j = 0; j < input.size(); j++)
                {
                    if (name[i + j] != input[j])
                    {
                        break;
                    }
                }
                if (j == input.size()) // agr naam match kr gya too true return krega
                {
                    match = true;
                    break;
                }
            }

            if (match)
            {
                cout << id << " " << name << " ₹" << price << endl;
                check = true;
            }
        }

        if (!check)
            cout << "Item not found.\n";

        menu.close();
    }

    void sortmenubyprice()
{
    ifstream menu("menu.txt");
    if (!menu)
    {
        cout << "Menu file not found." << endl;
        return;
    }

    // Structure for storing item
    struct Item
    {
        int id;
        string name;
        float price;
    };

    Item items[1000]; //memory ko bachayega
    int count = 0;

    // File se item read karke array mein daalna
    while (menu >> items[count].id >> items[count].name >> items[count].price)
    {
        count++; // total items ka count badhate jao
    }
    menu.close();

//  low to high by price
    for (int i = 0; i < count - 1; i++)

    {
        for (int j = 0; j < count - i - 1; j++)

        {

            if (items[j].price > items[j + 1].price)

            {
                // swap hoga
                Item temp = items[j];
                items[j] = items[j + 1];
                items[j + 1] = temp;
            }
        }
    }

    // Sorted menu print hoga
    cout << "\n--- Sorted Menu by Price (Low to High) ---"<<endl;

    for (int i = 0; i < count; i++)
    {
        cout << items[i].id << " " << items[i].name << " ₹" << items[i].price << endl;

    }

}

    void run()
    {
        int choice;
        do
        {
            cout << endl
                 << "--- Restaurant Menu System ---" << endl;
            cout << "1. Show Menu" << endl
                 << "2.Add Item" << endl
                 << "3. Take Order" << endl
                 << "4. Generate Bill" << endl;
            cout << "5. View Order History" << endl
                 << "6. Search Item" << endl
                 << "7. sort menu by price"<<endl
                 << "8. Exit"<<endl;
            cout << "Enter your choice: "<<endl;
            cin >> choice;

            if (choice == 1)
                showMenu();
            else if (choice == 2)
                addItemToMenu();
            else if (choice == 3)
                takeOrder();
            else if (choice == 4)
                generatebill(CustomerName);
            else if (choice == 5)
                viewHistory();
            else if (choice == 6)
                searchItem();
            else if (choice == 7)
                 sortmenubyprice();
            else if (choice == 8)
                cout << "Thank you for using the system"<<endl;
            else
                cout << "Invalid choice."<<endl;

        } while (choice != 8);

    }

};

int main()
{
    Restaurant r;
    r.run();
    return 0;
}

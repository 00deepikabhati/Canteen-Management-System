#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// STRUCTURE
struct Customer {
    int id;
    string department;
};

// FUNCTION TEMPLATE
template <class T>
void display(T value) {
    cout << value << endl;
}

// CLASS TEMPLATE
template <class T>
class Storage {
public:
    T data;

    void setData(T value) {
        data = value;
    }

    T getData() {
        return data;
    }
};

// FOOD CLASS
class Food {
public:
    int id;
    string name;
    float price;

    // DEFAULT CONSTRUCTOR
    Food() {
        id = 0;
        name = "";
        price = 0;
    }

    // PARAMETERIZED CONSTRUCTOR
    Food(int i, string n, float p) {
        id = i;
        name = n;
        price = p;
    }

    void showFood() {
        cout << id << "  "
             << name << "  Rs."
             << price << endl;
    }
};

// BASE CLASS
class Person {
protected:
    string name;

public:
    Person(string n) {
        name = n;
    }

    virtual void showDetails() {
        cout << "Name: " << name << endl;
    }

    virtual ~Person() {}
};

// DERIVED CLASS - INHERITANCE
class Student : public Person {
public:
    int rollNo;

    Student(string n, int r) : Person(n) {
        rollNo = r;
    }

    // FUNCTION OVERRIDING
    void showDetails() override {
        cout << "Student Name: " << name << endl;
        cout << "Roll Number: " << rollNo << endl;
    }
};

// BILL CLASS
class Bill {
private:
    float total;

public:
    Bill(float amount = 0) {
        total = amount;
    }

    // OPERATOR OVERLOADING
    Bill operator+(Bill b) {
        return Bill(total + b.total);
    }

    // FRIEND FUNCTION
    friend void showBill(Bill b);

    float getTotal() {
        return total;
    }
};

// FRIEND FUNCTION
void showBill(Bill b) {
    cout << "\nTotal Bill: Rs."
         << b.total << endl;
}

// CANTEEN CLASS
class Canteen {
private:
    Food* menu;
    int count;
    int capacity;

    // CONSTANT DATA MEMBER
    const string canteenName;

    // STATIC DATA MEMBER
    static int totalOrders;

    // CLASS TEMPLATE OBJECT
    Storage<int> order;

public:

    // CONSTRUCTOR
    Canteen() : canteenName("College Canteen") {

        capacity = 20;
        count = 0;

        // DYNAMIC MEMORY ALLOCATION
        menu = new Food[capacity];

        // ARRAY OF OBJECTS
        addFood(1, "Burger", 50);
        addFood(2, "Pizza", 100);
        addFood(3, "Sandwich", 40);
        addFood(4, "Tea", 15);
        addFood(5, "Coffee", 25);

        cout << "\nWelcome to "
             << canteenName << endl;
    }

    // FUNCTION OVERLOADING
    void addFood(string n, float p) {
        if (count < capacity) {
            menu[count] = Food(count + 1, n, p);
            count++;
        }
        else {
            cout << "Menu is full!\n";
        }
    }

    void addFood(int i, string n, float p) {
        if (count < capacity) {
            menu[count] = Food(i, n, p);
            count++;
        }
        else {
            cout << "Menu is full!\n";
        }
    }

    // DISPLAY MENU
    void showMenu() {
        cout << "\n------ FOOD MENU ------\n";

        for (int i = 0; i < count; i++) {
            menu[i].showFood();
        }
    }

    // STATIC MEMBER FUNCTION
    static void showOrders() {
        cout << "\nTotal Orders: "
             << totalOrders << endl;
    }

    // ORDER FUNCTION
    void placeOrder(Student s) {

        int id, quantity;
        char choice;

        Bill finalBill;

        // VIRTUAL FUNCTION
        Person* p = &s;
        p->showDetails();

        do {
            showMenu();

            cout << "\nEnter Food ID: ";
            cin >> id;

            cout << "Enter Quantity: ";
            cin >> quantity;

            // EXCEPTION HANDLING
            try {
                if (cin.fail()) {
                    throw "Invalid input!";
                }

                if (id < 1 || id > count) {
                    throw "Invalid Food ID!";
                }

                if (quantity <= 0) {
                    throw "Invalid Quantity!";
                }

                float amount =
                    menu[id - 1].price * quantity;

                cout << "Food: "
                     << menu[id - 1].name << endl;

                cout << "Amount: Rs."
                     << amount << endl;

                // OPERATOR OVERLOADING
                finalBill =
                    finalBill + Bill(amount);
            }

            catch (const char* error) {
                cout << "Error: "
                     << error << endl;
                return;
            }

            cout << "\nAdd more items? (y/n): ";
            cin >> choice;

        } while (choice == 'y' || choice == 'Y');

        // FRIEND FUNCTION
        showBill(finalBill);

        // STATIC MEMBER
        totalOrders++;

        order.setData(totalOrders);

        // FILE HANDLING
        ofstream file("orders.txt", ios::app);

        if (file.is_open()) {
            file << "Order Number: "
                 << order.getData() << endl;

            file << "Customer: Student" << endl;

            file << "Total Amount: Rs."
                 << finalBill.getTotal() << endl;

            file << "-------------------" << endl;

            file.close();

            cout << "Order saved successfully!\n";
        }
        else {
            cout << "File could not be opened!\n";
        }
    }

    // DESTRUCTOR
    ~Canteen() {
        delete[] menu;

        cout << "\nMemory Released Successfully!\n";
    }
};

// STATIC DATA MEMBER INITIALIZATION
int Canteen::totalOrders = 0;

// MAIN FUNCTION
int main() {

    Canteen c;

    Customer customer;
    customer.id = 101;
    customer.department = "CSE AI";

    Student s("Rahul", 25);

    int choice;

    do {
        cout << "\n===== CANTEEN MANAGEMENT SYSTEM =====\n";

        cout << "1. Display Food Menu\n";
        cout << "2. Place Order\n";
        cout << "3. Add Food Item\n";
        cout << "4. Show Total Orders\n";
        cout << "5. Exit\n";

        cout << "\nEnter Your Choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            c.showMenu();
            break;

        case 2:
            c.placeOrder(s);
            break;

        case 3: {
            string name;
            float price;

            cout << "Enter Food Name: ";
            cin >> name;

            cout << "Enter Food Price: ";
            cin >> price;

            if (cin.fail() || price <= 0) {
                cout << "Invalid food price!\n";
                cin.clear();
                cin.ignore(1000, '\n');
                break;
            }

            c.addFood(name, price);

            cout << "Food Added Successfully!\n";
            break;
        }

        case 4:
            Canteen::showOrders();
            break;

        case 5:
            cout << "\nThank You For Visiting!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 5);

    return 0;
}

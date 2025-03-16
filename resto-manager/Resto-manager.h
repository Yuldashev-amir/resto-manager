#ifndef RESTO_MANAGER_H
#define RESTO_MANAGER_H
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <cstdlib>
#include <errno.h>
#include <memory>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::ofstream;
using std::ifstream;
using std::unique_ptr;
using std::make_unique;
using std::ios_base;


const static int BUF_SIZE = 1024;
static const char filename[FILENAME_MAX] = "Menu.csv";
typedef struct dish_menu
{
    string nameDish;
    string compoundDish;
    double priceDish;
    double costDish;
} menu_item;

static int tables = 0;
static int seating = 0;
static int Orders = 0;

class Restaurant
{
protected:
    vector<menu_item> menu;
    string nameRest;
public:
    Restaurant(std::vector<menu_item> & dish, const string & nmR) : nameRest(nmR) { }
    void addDish(const menu_item & dish)
    {
        menu.push_back(dish);

        ofstream fout(filename, ios_base::app);
        if(!fout.is_open())
        {
            std::cerr << "File not opened for append dish.. Exit!";
            exit(EXIT_SUCCESS);
        }
        cout << "Openin file " << filename << endl;
        fout << nameRest << endl;
        fout << dish.nameDish << ", ";
        fout << dish.compoundDish << ", ";
        fout << dish.priceDish << ", ";
        fout << dish.costDish << std::endl;

        fout.close();
        cout << "Data correctly input in file! \n";
    }
    void removeDish()
    {
        if(menu.empty())
            return;
        menu.pop_back();
    }
    void showRest() const {cout << "Menu: " << endl;
                                    for (const auto & item : menu)
                                        cout << "Name dish: " << item.nameDish << endl << "Compound: " << item.compoundDish <<
                                        endl << "Price dish " << item.priceDish << endl << "Cost: " << item.costDish;
                           }
    ~Restaurant() {}
    void loadMenuFromFile()
    {
        ifstream fin(filename);
        if (fin.is_open())
        {
            std::cerr << "File not found. Creating new menu!\n";
            return;
        }

        menu.clear();

        menu_item temp;
        string line;
        while (getline(fin, temp.nameDish) &&
               getline(fin, temp.compoundDish) &&
               fin >> temp.priceDish && fin.ignore(1, ',') &&
               fin >> temp.costDish && fin.ignore())
        {
            menu.push_back(temp);
        }

        fin.close();
        cout << "Menu succesfully loaded from file!\n";
    }
    int GetTables(int tb) { return tables += tb; }
    int GetSeating(int seat) { return seating += seat; }
    string & getName() { return nameRest; }
    vector<menu_item> getMenu() const {return menu;}
    void newMenu(string fileInput)
    {
        char buffer[BUF_SIZE];
        cout << "Enter name file from will be output menu\n";
        getline(cin, fileInput);

        ifstream fin(fileInput);
        if(!(fin.is_open()))
        {
            std::cerr << "File not opened! Error open file for input!... Exit\n";
            exit(EXIT_FAILURE);
        }

        ofstream fout(filename, ios_base::binary);
        if(!(fout.is_open()))
        {
            std::cerr << "File not opened! Error open file!... Exit\n";
            exit(EXIT_FAILURE);
        }

        fout << fin.rdbuf();
        fout.close();
        fin.close();
    }
};

class Order
{
protected:
    vector<menu_item> ordersItem;
    string nameRest;
    int Orders;
public:
    void addOrder(const menu_item & menu) { ordersItem.push_back(menu); Orders += 1; }
    double totalPrice() const
    {
        if(ordersItem.empty())
            return 0.0;
        double sum = 0.0;
        for (const auto & item : ordersItem)
            sum += item.priceDish;
        return sum;
    }
    int getOrders() { return Orders; }
    void printOrder() const
    {
        cout << "Order: \n";
        for (const auto & item : ordersItem)
        {
            cout << "Name dish: " << item.nameDish << endl;
            cout << "Price: " << item.priceDish << endl;
        }
        cout << "Summa = " << totalPrice() << " KZT " << endl;
    }
    vector<menu_item> getOrders() const { return ordersItem; }
    ~Order() {}
};

class Analytics : public Order
{
private:
    double totalRevenue = 0.0;
public:
    Analytics(const Order & order, const string & nameRest) : Order(order) { }
    double averageCheckGuest(const Order & order, int guests) const
    {
        return (guests > 0) ? (order.totalPrice() / guests) : 0;
    }

    double averageCheckTable(const Order & order, int tables) const
    {
        return (tables > 0) ? (order.totalPrice() / tables) : 0;
    }
    void showAnalytics(const Order & order, int guests, int tables) const
    {
        cout << "Average check on guest: " << averageCheckGuest(order, guests) << " KZT " << endl;
//        cout << "Orders in : " << order.getOrders() << endl;
        cout << "Average check on table: " << averageCheckTable(order, tables) << " KZT " << endl;
    }
    void addOrder(double price)
    {
        totalRevenue += price;
        Orders += 1;
    }
    ~Analytics() {}

};
#endif // RESTO_MANAGER_H

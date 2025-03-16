// »спользование классов и методов заголовочного файла Resto-manager.h
// ѕриложение сохран€ет меню заведени€, стоимость, себестоимость, название и состав в текстовом формате каждой из позиций
// —читает средний чек на стол, на гост€, общее количество заказов, и общую выручку за период
// ћеню можно обновл€ть как удал€€ и добавл€€ позиции по одной так и загрузить новый файл формата CSV на чтение программой
#include "Resto-manager.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <memory>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

int main()
{
    std::vector<std::unique_ptr<Restaurant>> restaurants;
    std::vector<std::unique_ptr<Order>> orders;
    std::unique_ptr<Analytics> analytics = nullptr;
    menu_item dish;
    char ch;

    do {
        cout << "Menu select: " << endl;
        cout << "Q - Exit: \n" << endl;
        cout << "S - Create new restaurant: \n" << endl;
        cout << "N - New menu: \n" << endl;
        cout << "D - Show menu restaurant: \n" << endl;
        cout << "F - New order: \n" << endl;
        cin >> ch;
        toupper(ch);
        switch(toupper(ch))
        {
            case 'Q':
                exit(EXIT_SUCCESS);
            case 'S':
            {
                string nm;
                int dishCount;
                cout << "Enter please name your new restaurant: \n";
                cin.ignore();
                getline(cin, nm);
                cout << "Enter count dish in menu: \n";
                cin >> dishCount;
                vector<menu_item> dishList;
                auto newRestaurant = make_unique<Restaurant>(dishList, nm);
                for (int index = 0; index < dishCount; ++index)
                {
                    menu_item dish;
                    cout << "Enter name dish: \n" << index + 1 << ": ";
                    cin.ignore();
                    getline(cin, dish.nameDish);
                    cout << "Enter compound dish: \n";
                    cin.ignore();
                    getline(cin, dish.compoundDish);
                    cout << "Price dish: \n";
                    cin >> dish.priceDish;
                    cout << "Enter cost dish: \n";
                    cin >> dish.costDish;
                    dishList.push_back(dish);
                    newRestaurant->addDish(dish);
                }
                restaurants.push_back(make_unique<Restaurant>(dishList, nm));
                cout << "Restaurant \"" << nm << " added! \n";
            }
            break;
            case 'D':
            {
                if (restaurants.empty())
                {
                    cout << "Restaurants no!  add first you restaurant\n";
                    break;
                }
                else
                {
                    cout << "Select restaurant: \n";
                    for (size_t index = 0; index < restaurants.size(); ++index)
                        cout << index + 1 << ". " << restaurants[index]->getName() << '\n';
                }
                int restChoice = 0;
                cout << "Enter number restaurant: ";
                cin >> restChoice;

                if (restChoice > 0 && restChoice <= restaurants.size())
                    restaurants[restChoice - 1]->showRest();
                else
                    cout << "Incorrect choice! \n";
            }
            break;
            case 'F':
            {
                menu_item orderedDish;
                int restChoice = 0;
                if (restaurants.empty())
                {
                    cout << "No restaurants, add new restaurant \n";
                    break;
                }
                else
                {
                    cout << "Select restaurant for order: \n";
                    for (size_t index = 0; index < restaurants.size(); ++index)
                        cout << index + 1 << ", " << restaurants[index]->getName() << '\n';
                }

                cout << "Enter number restaurant: \n";
                cin >> restChoice;

                if (restChoice > 0 && restChoice <= restaurants.size())
                {
                    auto & selectedRestaurant = restaurants[restChoice - 1];

                    selectedRestaurant->showRest();
                    cout << "Choice number dish: \n";
                    int dishChoice;
                    cin >> dishChoice;

                    if (dishChoice > 0 && dishChoice <= selectedRestaurant->getMenu().size())
                    {
                        selectedRestaurant->showRest();
                        orders[dishChoice]->addOrder(orderedDish);
                        cout << "You orders: " << orderedDish.nameDish << "price " << orderedDish.priceDish << "KZT\n";

                        if (!analytics)
                        {
                            analytics = make_unique<Analytics>(*orders.back(), selectedRestaurant->getName());
                            analytics->addOrder(orderedDish.priceDish);
                        }
                        else
                            cout << "Incorrect select!\n";
                    }
                }
            }
            break;
            case 'N':
            {
                    string nmFile;
                    cin.ignore();
                    cout << "Enter please name file for import new menu" << endl;
                    getline(cin, nmFile);
                    if (restaurants.empty())
                    {
                        cout << "Actually restaurants no";
                        break;
                    }
                    for(int index = 0; index < restaurants.size(); index++)
                        restaurants[index]->showRest();
                    cout << "How restaurant you select? For refresh menu\n";
                    int numberRest = 0;
                    cin >> numberRest;

                    if (numberRest < 1 || numberRest > restaurants.size())
                    {
                        cout << "Invalid selection! \n";
                        break;
                    }

                    restaurants[numberRest - 1]->newMenu("newMenu.csv");
            }
            break;
        default:
            break;
    }
}
    while (toupper(ch) != 'Q');

    return 0;
}


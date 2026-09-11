#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Cargo
{
    int id;
    double mass;
    double value;
    int isDivisible;
    double valuePerMass;
};

bool compareCargo(Cargo a, Cargo b)
{
    return a.valuePerMass > b.valuePerMass;
}

int main()
{
    int numItems;
    double maxMass;

    cout << "Cargo Loading for Spaceship\n";
    cout << "Enter number of cargo items: ";
    cin >> numItems;

    Cargo cargoList[1000];

    cout << "Enter spaceship capacity (kg): ";
    cin >> maxMass;

    for (int i = 0; i < numItems; i++)
    {
        cargoList[i].id = i + 1;

        cout << "\nCargo Item " << i + 1 << endl;
        cout << "Enter mass (kg): ";
        cin >> cargoList[i].mass;

        cout << "Enter value: ";
        cin >> cargoList[i].value;

        cout << "Enter type (1 = Divisible, 0 = Indivisible): ";
        cin >> cargoList[i].isDivisible;

        cargoList[i].valuePerMass = cargoList[i].value / cargoList[i].mass;
    }

    sort(cargoList, cargoList + numItems, compareCargo);

    double leftoverMass = maxMass;
    double loadedMass = 0;
    double totalValue = 0;

    cout << fixed << setprecision(2);

    cout << "\nSelected Cargo Items\n";
    cout << "ID\tMass\tValue\n";

    for (int i = 0; i < numItems && leftoverMass > 0; i++)
    {
        if (cargoList[i].mass <= leftoverMass)
        {
            leftoverMass -= cargoList[i].mass;
            loadedMass += cargoList[i].mass;
            totalValue += cargoList[i].value;

            cout << cargoList[i].id << "\t"
                 << cargoList[i].mass << "\t"
                 << cargoList[i].value << endl;
        }
        else
        {
            if (cargoList[i].isDivisible == 1)
            {
                double fraction = leftoverMass / cargoList[i].mass;
                double partialValue = cargoList[i].value * fraction;

                loadedMass += leftoverMass;
                totalValue += partialValue;

                cout << cargoList[i].id << "\t"
                     << leftoverMass << "\t"
                     << partialValue
                     << " (Partial)" << endl;

                leftoverMass = 0;
            }
            else
            {
                continue;
            }
        }
    }

    cout << "\nTotal Mass Loaded: " << loadedMass << " kg" << endl;
    cout << "Remaining Spaceship Capacity: " << leftoverMass << " kg" << endl;
    cout << "Maximum Total Value: " << totalValue << endl;

    return 0;
}

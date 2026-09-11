#include <iostream>
#include <climits>
using namespace std;

const int MAX_NODES = 1000;
const int INFINITY_VAL = INT_MAX;

int cityGraph[MAX_NODES][MAX_NODES];
int timeArr[MAX_NODES];
int previousNode[MAX_NODES];
bool isProcessed[MAX_NODES];
int numNodes;

int getMinTimeNode()
{
    int minTime = INFINITY_VAL;
    int minNodeIndex = -1;

    for (int i = 0; i < numNodes; i++)
    {
        if (!isProcessed[i] && timeArr[i] < minTime)
        {
            minTime = timeArr[i];
            minNodeIndex = i;
        }
    }

    return minNodeIndex;
}

void printRoutePath(int node)
{
    if (node == -1)
        return;

    printRoutePath(previousNode[node]);
    cout << node << " ";
}

void findOptimalRoute(int startNode, int endNode)
{
    for (int i = 0; i < numNodes; i++)
    {
        timeArr[i] = INFINITY_VAL;
        previousNode[i] = -1;
        isProcessed[i] = false;
    }

    timeArr[startNode] = 0;

    for (int count = 0; count < numNodes - 1; count++)
    {
        int u = getMinTimeNode();

        if (u == -1)
            break;

        isProcessed[u] = true;

        if (u == endNode)
            break;

        for (int v = 0; v < numNodes; v++)
        {
            if (!isProcessed[v] &&
                cityGraph[u][v] != INFINITY_VAL &&
                timeArr[u] != INFINITY_VAL &&
                timeArr[u] + cityGraph[u][v] < timeArr[v])
            {
                timeArr[v] = timeArr[u] + cityGraph[u][v];
                previousNode[v] = u;
            }
        }
    }

    cout << "\nQuickest Delivery Truck Route\n";
    cout << "-----------------------------\n";

    if (timeArr[endNode] == INFINITY_VAL)
    {
        cout << "No route available.\n";
    }
    else
    {
        cout << "Warehouse Source: " << startNode << endl;
        cout << "Store Destination: " << endNode << endl;
        cout << "Minimum Travel Time: " << timeArr[endNode] << " minutes" << endl;
        cout << "Optimal Route: ";
        printRoutePath(endNode);
        cout << endl;
    }
}

int main()
{
    int connections;
    int startNode, endNode;

    cout << "Smart Delivery Route Management\n";
    cout << "Enter number of locations: ";
    cin >> numNodes;

    if (numNodes > MAX_NODES)
    {
        cout << "Maximum " << MAX_NODES << " locations allowed!\n";
        return 0;
    }

    for (int i = 0; i < numNodes; i++)
    {
        for (int j = 0; j < numNodes; j++)
        {
            if (i == j)
                cityGraph[i][j] = 0;
            else
                cityGraph[i][j] = INFINITY_VAL;
        }
    }

    cout << "Enter number of road connections: ";
    cin >> connections;

    cout << "Enter Location1 Location2 TravelTime:\n";

    for (int i = 0; i < connections; i++)
    {
        int u, v, travelTime;

        cin >> u >> v >> travelTime;

        if (u < 0 || u >= numNodes ||
            v < 0 || v >= numNodes ||
            travelTime < 0)
        {
            cout << "Invalid input!\n";
            i--;
            continue;
        }

        cityGraph[u][v] = travelTime;
        cityGraph[v][u] = travelTime;
    }

    cout << "Enter warehouse source location: ";
    cin >> startNode;

    cout << "Enter store destination location: ";
    cin >> endNode;

    findOptimalRoute(startNode, endNode);

    char updateFlag;

    cout << "\nDo you want to update traffic conditions? (Y/N): ";
    cin >> updateFlag;

    while (updateFlag == 'Y' || updateFlag == 'y')
    {
        int u, v, newTime;

        cout << "Enter road connection to update (Location1 Location2): ";
        cin >> u >> v;

        cout << "Enter new travel time: ";
        cin >> newTime;

        cityGraph[u][v] = newTime;
        cityGraph[v][u] = newTime;

        cout << "Traffic condition updated successfully!\n";

        findOptimalRoute(startNode, endNode);

        cout << "\nDo you want to update another road? (Y/N): ";
        cin >> updateFlag;
    }

    cout << "\nDelivery Route Optimization Completed Successfully!\n";

    return 0;
}

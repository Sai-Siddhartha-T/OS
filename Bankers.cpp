#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter number of resources: ";
    cin >> m;

    vector<vector<int>> alloc(n, vector<int>(m));
    vector<vector<int>> max(n, vector<int>(m));
    vector<vector<int>> need(n, vector<int>(m));
    vector<int> avail(m);
    vector<int> finish(n, 0), safeSeq(n);

    cout << "\nEnter Allocation Matrix (" << n << " x " << m << "):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> alloc[i][j];

    cout << "\nEnter Maximum Matrix (" << n << " x " << m << "):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> max[i][j];

    cout << "\nEnter Available Resources (" << m << "):\n";
    for (int j = 0; j < m; j++)
        cin >> avail[j];

    // Calculate Need matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    int count = 0;
    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canRun = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        canRun = false;
                        break;
                    }
                }
                if (canRun) {
                    // Process can execute
                    for (int k = 0; k < m; k++)
                        avail[k] += alloc[i][k];
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = true;
                }
            }
        }
        if (!found) {
            cout << "\nSystem is NOT in a safe state (Deadlock Possible).\n";
            return 0;
        }
    }

    cout << "\nSystem is in a SAFE state.\nSafe Sequence: ";
    for (int i = 0; i < n; i++)
        cout << "P" << safeSeq[i] << " ";
    cout << endl;

    return 0;
}

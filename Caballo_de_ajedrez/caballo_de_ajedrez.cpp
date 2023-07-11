/*
* Solucion aportada por el profesor de la FdI (UCM):
* Solution given by FdI's (UCM) professor:
*   ANTONIO ALEJANDRO SANCHEZ RUIZ-GRANADOS
*/
#include <iostream>
#include <vector>

using namespace std;

struct Square {
    int x, y;
};

// Returns the new square if we move in direction dir ([0-7]) from current
Square move(const Square& current, int dir) {
    vector<Square> delta{ {-1, 2}, {1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, 1}, {2, -1} };
    return { current.x + delta[dir].x, current.y + delta[dir].y };
}

// current inside the chess board and not visited
bool isValid(const Square& current, const vector<vector<bool>>& visited) {
    return 0 <= current.x && current.x < visited.size() &&
        0 <= current.y && current.y < visited.size() &&
        !visited[current.x][current.y];
}

// Printing the path followed by the knight
// void print(const vector<Square> &sol) {
//     cout << "sol" << endl;
//     for (int i=0; i<sol.size(); ++i)
//         cout << sol[i].x << " " << sol[i].y << endl;
//     cout << endl;    
// }

// Returns the number of ways to go from sol[k-1] to the top right corner of the board
// without going through visited squares. We could also show each found solution
int knight(vector<Square>& sol, int k, vector<vector<bool>>& visited) {
    int r = 0;
    //if we finished building this solution
    if (sol[k - 1].x == visited.size() - 1 && sol[k - 1].y == visited.size() - 1) {
        r = 1;
        //print(sol);
    }
    else {
        for (int dir = 0; dir < 8; ++dir) {
            sol[k] = move(sol[k - 1], dir);
            if (isValid(sol[k], visited)) {
                visited[sol[k].x][sol[k].y] = true;
                r += knight(sol, k + 1, visited);
                visited[sol[k].x][sol[k].y] = false;
            }
        }
    }
    return r;
}

// Same but using an in/out parameter "res" to return the result.
// In this case, we just count the number of posibles solution, without specifying which are they.
void knight2(vector<Square>& sol, int k, vector<vector<bool>>& visited, int& res) {
    if (sol[k - 1].x == visited.size() - 1 && sol[k - 1].y == visited.size() - 1) {
        ++res;
    }
    else {
        for (int dir = 0; dir < 8; ++dir) {
            sol[k] = move(sol[k - 1], dir);
            if (isValid(sol[k], visited)) {
                visited[sol[k].x][sol[k].y] = true;
                knight2(sol, k + 1, visited, res);
                visited[sol[k].x][sol[k].y] = false;
            }
        }
    }
}


bool solve() {
    int n, x, y;
    cin >> n >> x >> y;
    if (!n)
        return false;

    vector<Square> sol(n * n);
    sol[0].x = x;
    sol[0].y = y;
    vector<vector<bool>> visited(n, vector<bool>(n));
    visited[x][y] = true;
    cout << knight(sol, 1, visited) << endl;
    // int res = 0;
    // knight2(sol, 1, visited, res);
    // cout << res << endl;
    return true;
}

int main() {
    while (solve());
    return 0;
}
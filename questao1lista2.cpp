#include <iostream>
#include <string>

using namespace std;

typedef struct {
    int timestamp;
    unsigned ip;
} Connection;

int queryConnection(int value, int begin, int end, Connection *arr){

    int middle = (begin + end)/2;

    if(begin > end)
        return -1;

    if(arr[middle].timestamp == value)
        return middle;

    if(arr[middle].timestamp > value)
        return queryConnection(value, begin, middle-1, arr);

    else
        return queryConnection(value, middle+1, end, arr);
};

int main() {
    ios::sync_with_stdio(0);
    
    int control = 1;
    string command;
    int timestamp;
    unsigned ip;

    Connection *vector = NULL;

    while (true) {
        cin >> command;
        if (command == "END") {
            break;
        };
        if (command == "NEW") {
            cin >> timestamp >> ip;
            vector = (Connection *) realloc(vector, sizeof(Connection) * control);
            if(vector == NULL){
                exit(1);
            }
            
            vector[control-1].ip = ip;
            vector[control-1].timestamp = timestamp;

            control++;
        };
        if (command == "QRY") {
            cin >> timestamp;

            int x = queryConnection(timestamp, 0, control-2, vector);

            if(x == -1)
                cout << "-1 -1" << endl;
        
            else
                cout << vector[x].ip << " " << x << endl;
        };
    }

    return 0;
}
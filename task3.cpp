#include <iostream>
#include <string>
using namespace std;

struct Coach {
    int number;
    string type;
    int capacity;
    int passengers;
    Coach* next;
    Coach* prev;

    Coach(int number, string type, int capacity, int passengers) {
        this->number = number;
        this->type = type;
        this->capacity = capacity;
        this->passengers = passengers;
        this->next = nullptr;
        this->prev = nullptr;
    }
};

class Train {
    Coach* head;      // first coach
    Coach* current;   // selected coach

public:
    Train() {
        head = nullptr;
        current = nullptr;
    }

    void printCoach(Coach* c) {
        cout << "Coach No: " << c->number << " | Type: " << c->type
             << " | Capacity: " << c->capacity << " | Passengers: " << c->passengers
             << " | Empty seats: " << c->capacity - c->passengers << endl;
    }

    // Finds a coach by number, returns nullptr if not found
    Coach* findCoach(int number) {
        if (head == nullptr) return nullptr;
        Coach* p = head;
        do {
            if (p->number == number) return p;
            p = p->next;
        } while (p != head);
        return nullptr;
    }

    // 1. Add Coach at the end
    void addCoach(int number, string type, int capacity, int passengers) {
        Coach* n = new Coach(number, type, capacity, passengers);

        if (head == nullptr) {
            n->next = n;
            n->prev = n;
            head = n;
            current = n;
        }
        else {
            Coach* tail = head->prev;    // last coach
            n->next = head;
            n->prev = tail;
            tail->next = n;
            head->prev = n;
        }
    }

    // 2. Insert Coach after a given coach number
    void insertCoach(int afterNumber, int number, string type, int capacity, int passengers) {
        Coach* pos = findCoach(afterNumber);
        if (pos == nullptr) {
            cout << "Coach " << afterNumber << " not found." << endl;
            return;
        }
        Coach* n = new Coach(number, type, capacity, passengers);
        n->next = pos->next;
        n->prev = pos;
        pos->next->prev = n;
        pos->next = n;
        cout << "Coach inserted." << endl;
    }

    // 3. Remove Coach by number
    void removeCoach(int number) {
        Coach* c = findCoach(number);
        if (c == nullptr) {
            cout << "Coach not found." << endl;
            return;
        }
        removeNode(c);
        cout << "Coach removed." << endl;
    }

    // Unlinks and deletes one coach
    void removeNode(Coach* n) {
        if (n->next == n) {              // only one coach
            head = nullptr;
            current = nullptr;
        }
        else {
            n->prev->next = n->next;
            n->next->prev = n->prev;
            if (head == n) head = n->next;
            if (current == n) current = n->next;   // next coach becomes current
        }
        delete n;
    }

    // 4. Move Forward
    void moveForward() {
        if (current == nullptr) {
            cout << "Train is empty." << endl;
            return;
        }
        current = current->next;
    }

    // 5. Move Backward
    void moveBackward() {
        if (current == nullptr) {
            cout << "Train is empty." << endl;
            return;
        }
        current = current->prev;
    }

    // 6. Display Train Clockwise
    void showClockwise() {
        if (current == nullptr) {
            cout << "Train is empty." << endl;
            return;
        }
        Coach* p = current;
        do {
            printCoach(p);
            p = p->next;
        } while (p != current);
    }

    // 7. Display Train Anti-clockwise
    void showAnticlockwise() {
        if (current == nullptr) {
            cout << "Train is empty." << endl;
            return;
        }
        Coach* p = current;
        do {
            printCoach(p);
            p = p->prev;
        } while (p != current);
    }

    // 8. Search Coach
    void searchCoach(int number) {
        Coach* c = findCoach(number);
        if (c == nullptr) cout << "Coach not found." << endl;
        else printCoach(c);
    }

    // 9. Find coach with the most empty seats
    void maxAvailable() {
        if (head == nullptr) {
            cout << "Train is empty." << endl;
            return;
        }
        Coach* best = head;
        Coach* p = head->next;
        while (p != head) {
            if (p->capacity - p->passengers > best->capacity - best->passengers) {
                best = p;
            }
            p = p->next;
        }
        cout << "Coach with most empty seats:" << endl;
        printCoach(best);
    }

    // 10. Display Current Coach
    void showCurrent() {
        if (current == nullptr) {
            cout << "Train is empty." << endl;
            return;
        }
        printCoach(current);
    }

    // 11. Reverse Train Direction (swap next and prev in every node)
    void reverseTrain() {
        if (head == nullptr) {
            cout << "Train is empty." << endl;
            return;
        }
        Coach* oldTail = head->prev;
        Coach* p = head;
        do {
            Coach* temp = p->next;     // remember the original next
            p->next = p->prev;
            p->prev = temp;
            p = temp;                  // move to the original next
        } while (p != head);
        head = oldTail;                // old last coach is now the first
        cout << "Train direction reversed." << endl;
    }

    // Free all coaches when program ends
    ~Train() {
        while (head != nullptr) {
            removeNode(head);
        }
    }
};

int main() {
    Train train;
    int n;

    cout << "Number of coaches: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        int number, capacity, passengers;
        string type;
        cout << "\nCoach " << i + 1 << endl;
        cout << "Coach Number: ";
        cin >> number;
        cin.ignore();
        cout << "Coach Type: ";
        getline(cin, type);
        cout << "Passenger Capacity: ";
        cin >> capacity;
        cout << "Current Passengers: ";
        cin >> passengers;
        train.addCoach(number, type, capacity, passengers);
    }

    int choice;
    do {
        cout << "\n1. Add Coach (at end)" << endl;
        cout << "2. Insert Coach After a Coach" << endl;
        cout << "3. Remove Coach" << endl;
        cout << "4. Move Forward" << endl;
        cout << "5. Move Backward" << endl;
        cout << "6. Display Train Clockwise" << endl;
        cout << "7. Display Train Anti-clockwise" << endl;
        cout << "8. Search Coach" << endl;
        cout << "9. Find Maximum Available Capacity" << endl;
        cout << "10. Display Current Coach" << endl;
        cout << "11. Reverse Train Direction" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1 || choice == 2) {
            int after = 0, number, capacity, passengers;
            string type;
            if (choice == 2) {
                cout << "Insert after coach number: ";
                cin >> after;
            }
            cout << "Coach Number: ";
            cin >> number;
            cin.ignore();
            cout << "Coach Type: ";
            getline(cin, type);
            cout << "Passenger Capacity: ";
            cin >> capacity;
            cout << "Current Passengers: ";
            cin >> passengers;
            if (choice == 1) {
                train.addCoach(number, type, capacity, passengers);
                cout << "Coach added." << endl;
            }
            else {
                train.insertCoach(after, number, type, capacity, passengers);
            }
        }
        else if (choice == 3) {
            int number;
            cout << "Coach number: ";
            cin >> number;
            train.removeCoach(number);
        }
        else if (choice == 4) train.moveForward();
        else if (choice == 5) train.moveBackward();
        else if (choice == 6) train.showClockwise();
        else if (choice == 7) train.showAnticlockwise();
        else if (choice == 8) {
            int number;
            cout << "Coach number: ";
            cin >> number;
            train.searchCoach(number);
        }
        else if (choice == 9) train.maxAvailable();
        else if (choice == 10) train.showCurrent();
        else if (choice == 11) train.reverseTrain();
    } while (choice != 0);

    return 0;
}
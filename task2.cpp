#include <iostream>
#include <string>
using namespace std;

struct Photo {
    int id;
    string name;
    string date;
    string location;
    Photo* next;
    Photo* prev;

    Photo(int id, string name, string date, string location) {
        this->id = id;
        this->name = name;
        this->date = date;
        this->location = location;
        this->next = nullptr;
        this->prev = nullptr;
    }
};

class Album {
    Photo* head;      // first photo
    Photo* current;   // selected photo
    int count;

public:
    Album() {
        head = nullptr;
        current = nullptr;
        count = 0;
    }

    void printPhoto(Photo* p) {
        cout << "ID: " << p->id << " | Name: " << p->name
             << " | Date: " << p->date << " | Location: " << p->location << endl;
    }

    // Finds a photo by ID, returns nullptr if not found
    Photo* findPhoto(int id) {
        if (head == nullptr) return nullptr;
        Photo* p = head;
        do {
            if (p->id == id) return p;
            p = p->next;
        } while (p != head);
        return nullptr;
    }

    // Unlinks and deletes one photo (used by both remove functions)
    void removeNode(Photo* n) {
        if (n->next == n) {              // only one photo
            head = nullptr;
            current = nullptr;
        }
        else {
            n->prev->next = n->next;
            n->next->prev = n->prev;
            if (head == n) head = n->next;
            if (current == n) current = n->next;   // next photo becomes current
        }
        delete n;
        count--;
    }

    // 1. Adding Photo at the end
    void addPhoto(int id, string name, string date, string location) {
        Photo* n = new Photo(id, name, date, location);

        if (head == nullptr) {
            n->next = n;
            n->prev = n;
            head = n;
            current = n;
        }
        else {
            Photo* tail = head->prev;    // last photo
            n->next = head;
            n->prev = tail;
            tail->next = n;
            head->prev = n;
        }
        count++;
    }

    // 2. Inserting Photo After Current
    void insertAfterCurrent(int id, string name, string date, string location) {
        if (current == nullptr) {        // empty album: same as adding first photo
            addPhoto(id, name, date, location);
            cout << "Photo inserted." << endl;
            return;
        }
        Photo* n = new Photo(id, name, date, location);
        n->next = current->next;
        n->prev = current;
        current->next->prev = n;
        current->next = n;
        count++;
        cout << "Photo inserted." << endl;
    }

    // 3. Removing Photo by ID
    void removeById(int id) {
        Photo* p = findPhoto(id);
        if (p == nullptr) {
            cout << "Photo not found." << endl;
            return;
        }
        removeNode(p);
        cout << "Photo removed." << endl;
    }

    // 4. Removing Current Photo
    void removeCurrent() {
        if (current == nullptr) {
            cout << "Album is empty." << endl;
            return;
        }
        removeNode(current);
        cout << "Current photo removed." << endl;
    }

    // 5. Moving Next
    void moveNext() {
        if (current == nullptr) {
            cout << "Album is empty." << endl;
            return;
        }
        current = current->next;
    }

    // 6. Moving Previous
    void movePrev() {
        if (current == nullptr) {
            cout << "Album is empty." << endl;
            return;
        }
        current = current->prev;
    }

    // 7. Displaying Album Forward
    void showForward() {
        if (current == nullptr) {
            cout << "Album is empty." << endl;
            return;
        }
        Photo* p = current;
        do {
            printPhoto(p);
            p = p->next;
        } while (p != current);
    }

    // 8. Displaying Album Backward
    void showBackward() {
        if (current == nullptr) {
            cout << "Album is empty." << endl;
            return;
        }
        Photo* p = current;
        do {
            printPhoto(p);
            p = p->prev;
        } while (p != current);
    }

    // 9. Searching Photo
    void searchPhoto(int id) {
        Photo* p = findPhoto(id);
        if (p == nullptr) cout << "Photo not found." << endl;
        else printPhoto(p);
    }

    // 10. Counting Photos
    void countPhotos() {
        cout << "Total photos: " << count << endl;
    }

    // Show the selected photo
    void showCurrent() {
        if (current == nullptr) {
            cout << "Album is empty." << endl;
            return;
        }
        printPhoto(current);
    }

    // Free all photos when program ends
    ~Album() {
        while (head != nullptr) {
            removeNode(head);
        }
    }
};

int main() {
    Album album;
    int n;

    cout << "Number of photos: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        int id;
        string name, date, location;
        cout << "\nPhoto " << i + 1 << endl;
        cout << "Photo ID: ";
        cin >> id;
        cin.ignore();
        cout << "Name: ";
        getline(cin, name);
        cout << "Date Taken: ";
        getline(cin, date);
        cout << "Location: ";
        getline(cin, location);
        album.addPhoto(id, name, date, location);
    }

    int choice;
    do {
        cout << "\n1. Add Photo (at end)" << endl;
        cout << "2. Insert Photo After Current" << endl;
        cout << "3. Remove Photo by ID" << endl;
        cout << "4. Remove Current Photo" << endl;
        cout << "5. Move Next" << endl;
        cout << "6. Move Previous" << endl;
        cout << "7. Display Album Forward" << endl;
        cout << "8. Display Album Backward" << endl;
        cout << "9. Search Photo" << endl;
        cout << "10. Count Photos" << endl;
        cout << "11. Display Current Photo" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1 || choice == 2) {
            int id;
            string name, date, location;
            cout << "Photo ID: ";
            cin >> id;
            cin.ignore();
            cout << "Name: ";
            getline(cin, name);
            cout << "Date Taken: ";
            getline(cin, date);
            cout << "Location: ";
            getline(cin, location);
            if (choice == 1) {
                album.addPhoto(id, name, date, location);
                cout << "Photo added." << endl;
            }
            else {
                album.insertAfterCurrent(id, name, date, location);
            }
        }
        else if (choice == 3) {
            int id;
            cout << "Photo ID: ";
            cin >> id;
            album.removeById(id);
        }
        else if (choice == 4) album.removeCurrent();
        else if (choice == 5) album.moveNext();
        else if (choice == 6) album.movePrev();
        else if (choice == 7) album.showForward();
        else if (choice == 8) album.showBackward();
        else if (choice == 9) {
            int id;
            cout << "Photo ID: ";
            cin >> id;
            album.searchPhoto(id);
        }
        else if (choice == 10) album.countPhotos();
        else if (choice == 11) album.showCurrent();
    } while (choice != 0);

    return 0;
}
#include <iostream>
#include <string>
using namespace std;


struct Tab{
    int id;
    string title;
    string url;
    Tab* next;
    Tab* prev;

    Tab(int id,string title, string url){
        this->id  = id;
        this->title = title;
        this->url = url;
        this->next  = nullptr;
        this->prev = nullptr;
    }
};

class TabManager{
    private:
        Tab* current;
    
    public:
        TabManager(){
            current = nullptr;
        }

        void printTab(Tab* t){
            cout << "ID: " << t->id << " | Title: " << t->title << " | URL: " << t->url << endl;
        }


        //Operation 1: Inserting a new tab after the current tab.
        void openTab(int id, string title, string url){
            Tab* n = new Tab(id,title,url);

            if (current == nullptr){
                n->next = n;
                n->prev = n;
                current = n;
            }
            else{
                n->next = current-> next;
                n->prev = current;
                current->next->prev = n;
                current->next = n;
            }
        }

        //Operation 2: Removing current tab.
        void closeTab() {
            if (current == nullptr) {
                cout << "No tabs opened" << endl;
                return;
            }

            Tab* temp = current;

            if (current->next == current) {      // when only one tab is opened
                current = nullptr;
            }
            else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
                current = current->next;         
            }

            delete temp;
            cout << "Tab closed." << endl;
        }

        //Operation 3: Moving next
        void moveNext() {
            if (current == nullptr) {
                cout << "No tabs open." << endl;
                return;
            }
            current = current->next;
        }

        //Operation 4. Moving Previous
        void movePrev() {
            if (current == nullptr) {
                cout << "No tabs open." << endl;
                return;
            }
            current = current->prev;
        }

        //Operation 5. Displaying Current Tab
        void showCurrent() {
            if (current == nullptr) {
                cout << "No tabs open." << endl;
                return;
            }
            printTab(current);
        }

        //Operation 6. Displaying All Forward
        void showForward() {
            if (current == nullptr) {
                cout << "No tabs open." << endl;
                return;
            }
            Tab* p = current;
            do {
                printTab(p);
                p = p->next;
            } while (p != current);
        }

        // 7. Display All Backward
        void showBackward() {
            if (current == nullptr) {
                cout << "No tabs open." << endl;
                return;
            }
            Tab* p = current;
            do {
                printTab(p);
                p = p->prev;
            } while (p != current);
        }

        // 8. Search by ID
        void searchTab(int id) {
            if (current == nullptr) {
                cout << "No tabs open." << endl;
                return;
            }
            Tab* p = current;
            do {
                if (p->id == id) {
                    printTab(p);
                    return;
                }
                p = p->next;
            } while (p != current);
            cout << "Tab not found." << endl;
        }


        // Frees all tabs when program ends
        ~TabManager() {
            while (current != nullptr) {
                closeTab();
            }
        }
};

int main() {
    TabManager tm;
    int choice;

    do {
        cout << "\n1. Open New Tab" << endl;
        cout << "2. Close Current Tab" << endl;
        cout << "3. Move Next" << endl;
        cout << "4. Move Previous" << endl;
        cout << "5. Display Current Tab" << endl;
        cout << "6. Display All Tabs Forward" << endl;
        cout << "7. Display All Tabs Backward" << endl;
        cout << "8. Search Tab" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) {
            int id;
            string title, url;
            cout << "Tab ID: ";
            cin >> id;
            cin.ignore();
            cout << "Title: ";
            getline(cin, title);
            cout << "URL: ";
            getline(cin, url);
            tm.openTab(id, title, url);
        }
        else if (choice == 2) tm.closeTab();
        else if (choice == 3) tm.moveNext();
        else if (choice == 4) tm.movePrev();
        else if (choice == 5) tm.showCurrent();
        else if (choice == 6) tm.showForward();
        else if (choice == 7) tm.showBackward();
        else if (choice == 8) {
            int id;
            cout << "Tab ID: ";
            cin >> id;
            tm.searchTab(id);
        }
    } while (choice != 0);

    return 0;
}

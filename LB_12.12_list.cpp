#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Структура службовця
struct Employee {
    string surname;
    string initials;
    string position;
    int year;
    double salary;
    Employee* next;
};

// Оголошення функцій
void addEmployee(Employee*& head);
void deleteEmployee(Employee*& head);
void editEmployee(Employee* head);
void sortEmployees(Employee* head, int criterion);
Employee* findEmployee(Employee* head, const string& surname);
void printEmployees(const Employee* head);
void saveToFile(const Employee* head, const string& filename);
void loadFromFile(Employee*& head, const string& filename);
void displayMenu();

int main() {
    Employee* head = nullptr;
    int choice;
    string filename;

    while (true) {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Для очищення буферу вводу

        switch (choice) {
        case 1:
            addEmployee(head);
            break;
        case 2:
            deleteEmployee(head);
            break;
        case 3:
            editEmployee(head);
            break;
        case 4: {
            int criterion;
            cout << "Sort by: 1 - Surname, 2 - Salary, 3 - Year: ";
            cin >> criterion;
            sortEmployees(head, criterion);
            break;
        }
        case 5: {
            string searchSurname;
            cout << "Enter surname to search: ";
            cin.ignore();
            getline(cin, searchSurname);
            Employee* found = findEmployee(head, searchSurname);
            if (found) {
                cout << "Found: " << found->surname << " " << found->initials << ", " << found->position
                    << ", Year: " << found->year << ", Salary: " << found->salary << endl;
            }
            else {
                cout << "Employee not found." << endl;
            }
            break;
        }
        case 6:
            printEmployees(head);
            break;
        case 7:
            cout << "Enter filename to save: ";
            cin >> filename;
            saveToFile(head, filename);
            break;
        case 8:
            cout << "Enter filename to load: ";
            cin >> filename;
            loadFromFile(head, filename);
            break;
        case 9:
            cout << "Exiting program." << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}

void addEmployee(Employee*& head) {
    Employee* newEmployee = new Employee();
    cout << "Enter surname: ";
    cin.ignore();
    getline(cin, newEmployee->surname);
    cout << "Enter initials: ";
    getline(cin, newEmployee->initials);
    cout << "Enter position: ";
    getline(cin, newEmployee->position);
    cout << "Enter year of employment: ";
    cin >> newEmployee->year;
    cout << "Enter salary: ";
    cin >> newEmployee->salary;
    cin.ignore(); // Очищення буферу

    newEmployee->next = head;
    head = newEmployee;
    cout << "Employee added successfully." << endl;
}

void deleteEmployee(Employee*& head) {
    string surname;
    cout << "Enter surname of employee to delete: ";
    cin.ignore();
    getline(cin, surname);

    Employee* current = head;
    Employee* previous = nullptr;

    while (current != nullptr && current->surname != surname) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Employee not found." << endl;
        return;
    }

    if (previous == nullptr) {
        head = current->next;
    }
    else {
        previous->next = current->next;
    }

    delete current;
    cout << "Employee deleted successfully." << endl;
}

void editEmployee(Employee* head) {
    string surname;
    cout << "Enter surname of employee to edit: ";
    cin.ignore();
    getline(cin, surname);

    Employee* current = head;
    while (current != nullptr && current->surname != surname) {
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Employee not found." << endl;
        return;
    }

    cout << "Enter new initials: ";
    getline(cin, current->initials);
    cout << "Enter new position: ";
    getline(cin, current->position);
    cout << "Enter new year of employment: ";
    cin >> current->year;
    cout << "Enter new salary: ";
    cin >> current->salary;
    cin.ignore(); // Очищення буферу

    cout << "Employee information updated successfully." << endl;
}

void sortEmployees(Employee* head, int criterion) {
    if (!head) return;

    bool swapped;
    Employee* ptr1;
    Employee* lptr = nullptr;

    do {
        swapped = false;
        ptr1 = head;

        while (ptr1->next != lptr) {
            bool shouldSwap = false;
            switch (criterion) {
            case 1:
                shouldSwap = ptr1->surname > ptr1->next->surname;
                break;
            case 2:
                shouldSwap = ptr1->salary > ptr1->next->salary;
                break;
            case 3:
                shouldSwap = ptr1->year > ptr1->next->year;
                break;
            default:
                cout << "Invalid criterion." << endl;
                return;
            }
            if (shouldSwap) {
                swap(ptr1->surname, ptr1->next->surname);
                swap(ptr1->initials, ptr1->next->initials);
                swap(ptr1->position, ptr1->next->position);
                swap(ptr1->year, ptr1->next->year);
                swap(ptr1->salary, ptr1->next->salary);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
    cout << "Employees sorted successfully." << endl;
}

Employee* findEmployee(Employee* head, const string& surname) {
    while (head != nullptr) {
        if (head->surname == surname) {
            return head;
        }
        head = head->next;
    }
    return nullptr;
}

void printEmployees(const Employee* head) {
    const Employee* current = head;
    while (current != nullptr) {
        cout << current->surname << " " << current->initials << ", " << current->position
            << ", Year: " << current->year << ", Salary: " << current->salary << endl;
        current = current->next;
    }
}

void saveToFile(const Employee* head, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file for writing." << endl;
        return;
    }
    const Employee* current = head;
    while (current != nullptr) {
        file << current->surname << " " << current->initials << " " << current->position << " "
            << current->year << " " << current->salary << endl;
        current = current->next;
    }
    file.close();
    cout << "Data saved to file successfully." << endl;
}

void loadFromFile(Employee*& head, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file for reading." << endl;
        return;
    }
    // Очистка списку перед завантаженням нових даних
    while (head != nullptr) {
        Employee* temp = head;
        head = head->next;
        delete temp;
    }

    string surname, initials, position;
    int year;
    double salary;
    while (file >> surname >> initials >> position >> year >> salary) {
        Employee* newEmployee = new Employee();
        newEmployee->surname = surname;
        newEmployee->initials = initials;
        newEmployee->position = position;
        newEmployee->year = year;
        newEmployee->salary = salary;
        newEmployee->next = head;
        head = newEmployee;
    }
    file.close();
    cout << "Data loaded from file successfully." << endl;
}

void displayMenu() {
    cout << "1. Add Employee" << endl;
    cout << "2. Delete Employee" << endl;
    cout << "3. Edit Employee" << endl;
    cout << "4. Sort Employees" << endl;
    cout << "5. Find Employee" << endl;
    cout << "6. Print All Employees" << endl;
    cout << "7. Save to File" << endl;
    cout << "8. Load from File" << endl;
    cout << "9. Exit" << endl;
}

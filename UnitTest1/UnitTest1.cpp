#include "pch.h"
#include "CppUnitTest.h"
#include "../LB_12.12_list.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
        TEST_METHOD(TestAddEmployee)
        {
            Employee* head = nullptr;
            Employee* newEmployee = new Employee{ "Doe", "J.D.", "Manager", 2010, 50000.0, nullptr };
            newEmployee->next = head;
            head = newEmployee;

            Assert::IsNotNull(head);
            Assert::AreEqual(string("Doe"), head->surname);
            Assert::AreEqual(string("J.D."), head->initials);
            Assert::AreEqual(string("Manager"), head->position);
            Assert::AreEqual(2010, head->year);
            Assert::AreEqual(50000.0, head->salary);

            delete head;
        }

        TEST_METHOD(TestDeleteEmployee)
        {
            Employee* head = new Employee{ "Doe", "J.D.", "Manager", 2010, 50000.0, nullptr };
            Employee* previous = nullptr;

            Employee* current = head;
            while (current != nullptr && current->surname != "Doe") {
                previous = current;
                current = current->next;
            }

            if (current != nullptr) {
                if (previous == nullptr) {
                    head = current->next;
                }
                else {
                    previous->next = current->next;
                }
                delete current;
            }

            Assert::IsNull(head);
        }

        TEST_METHOD(TestEditEmployee)
        {
            Employee* head = new Employee{ "Doe", "J.D.", "Manager", 2010, 50000.0, nullptr };
            Employee* current = head;
            if (current->surname == "Doe") {
                current->surname = "Jane";
                current->initials = "J.D.";
                current->position = "Director";
                current->year = 2011;
                current->salary = 60000.0;
            }

            Assert::IsNotNull(head);
            Assert::AreEqual(string("Jane"), head->surname);
            Assert::AreEqual(string("J.D."), head->initials);
            Assert::AreEqual(string("Director"), head->position);
            Assert::AreEqual(2011, head->year);
            Assert::AreEqual(60000.0, head->salary);

            delete head;
        }

        TEST_METHOD(TestFindEmployee)
        {
            Employee* head = new Employee{ "Doe", "J.D.", "Manager", 2010, 50000.0, nullptr };
            Employee* found = nullptr;
            Employee* current = head;
            while (current != nullptr) {
                if (current->surname == "Doe") {
                    found = current;
                    break;
                }
                current = current->next;
            }

            Assert::IsNotNull(found);
            Assert::AreEqual(string("Doe"), found->surname);

            delete head;
        }

        TEST_METHOD(TestSortEmployees)
        {
            Employee* head = nullptr;
            Employee* e1 = new Employee{ "Smith", "A.B.", "Developer", 2012, 45000.0, nullptr };
            Employee* e2 = new Employee{ "Doe", "J.D.", "Manager", 2010, 50000.0, e1 };
            head = e2;

            bool swapped;
            Employee* ptr1;
            Employee* lptr = nullptr;

            do {
                swapped = false;
                ptr1 = head;

                while (ptr1->next != lptr) {
                    if (ptr1->surname > ptr1->next->surname) {
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

            Assert::IsNotNull(head);
            Assert::AreEqual(string("Doe"), head->surname);
            Assert::AreEqual(string("Smith"), head->next->surname);

            delete e2;
            delete e1;
        }
	};
}

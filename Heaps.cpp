#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <thread>
#include <chrono>

using namespace std;

// ANSI color codes for text color
const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN = "\033[36m";

vector<string> history;
vector<int> maxHeap;
vector<int> minHeap;
vector<int> userInputAges; // New vector to store user input from case 1

// Function to display the heap
void displayHeap(const vector<int>& heap) {
    cout << CYAN << "Current heap: ";
    for (int age : heap) {
        cout << age << " ";
    }
    cout << RESET << endl;
}

// Function to insert an element into a Max-Heap
void insertMaxHeap(vector<int>& heap, int age) {
    cout << GREEN << "Inserting age " << age << " into Max-Heap." << RESET << endl;
    heap.push_back(age);
    push_heap(heap.begin(), heap.end());
    displayHeap(heap);
    history.push_back("Inserted age " + to_string(age) + " into Max-Heap.");
}

// Function to convert Max-Heap to Min-Heap
void convertToMinHeap(vector<int>& heap) {
    cout << YELLOW << "Converting Max-Heap to Min-Heap." << RESET << endl;
    make_heap(heap.begin(), heap.end(), greater<int>());
    minHeap = heap; // Store the min heap state
    displayHeap(heap);
    history.push_back("Converted Max-Heap to Min-Heap.");
}

// Function to heapify a random list into a Max-Heap
void heapifyMaxHeap(vector<int>& heap) {
    cout << BLUE << "Heapifying the list into Max-Heap. Let's get those cats in order!" << RESET << endl;
    make_heap(heap.begin(), heap.end());
    maxHeap = heap; // Store the max heap state
    displayHeap(heap);
    history.push_back("Heapified the list into Max-Heap.");
}

// Function to delete an element from the heap
void deleteFromHeap(vector<int>& heap, int age) {
    auto it = find(heap.begin(), heap.end(), age);
    if (it != heap.end()) {
        cout << RED << "Deleting age " << age << " from the heap." << RESET << endl;
        heap.erase(it);
        make_heap(heap.begin(), heap.end());
        displayHeap(heap);
        history.push_back("Deleted age " + to_string(age) + " from the heap.");
        if (!minHeap.empty()) {
            convertToMinHeap(maxHeap); // Update the min heap after deletion
        }
    } else {
        cout << RED << "Age " << age << " not found in the heap." << RESET << endl;
    }
}

int main() {
    int choice, age;
    string welcomeMessage = "Hello! Welcome, it's your first day as a vet \n" "Your task is to manage the ages of the pets in the shelter.\n" "Let's get started!\n";
    for (char c : welcomeMessage) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(25));
    }

    while (true) {
        cout << MAGENTA << "\nHome for the aged Cats at the shelter (CATS):\n" << RESET;
        cout << "1. Insert age of a cat\n";
        cout << "2. Convert Max-Heap to Min-Heap\n";
        cout << "3. Heapify random ages into a Max-Heap\n";
        cout << "4. Remove a naughty cat\n";
        cout << "5. Finish your duty and recap\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cout << " \n";
        cin >> choice;

        switch (choice) {
            case 1:
                while (true) {
                    cout << "Enter age to insert (or -1 to stop): ";
                    cin >> age;
                    if (age == -1) break;
                    insertMaxHeap(maxHeap, age);
                    userInputAges.push_back(age); // Store the user input
                }
                break;
            case 2:
                convertToMinHeap(maxHeap);
                break;
            case 3:
                heapifyMaxHeap(userInputAges); // Use the user input to heapify
                break;
            case 4:
                while (true) {
                    cout << "Enter age to delete (or -1 to stop): ";
                    cin >> age;
                    if (age == -1) break;
                    deleteFromHeap(maxHeap, age);
                }
                break;
            case 5:
                cout << BLUE << "Recap of the heap and changes made:\n" << RESET;
                cout << "Max-Heap: ";
                displayHeap(maxHeap);
                cout << "Min-Heap: ";
                displayHeap(minHeap);
                cout << GREEN << "History of changes:\n" << RESET;
                for (const string& record : history) {
                    cout << record << endl;
                }
                for (char c : "Thank you for your duty!") {
                    cout << c << flush;
                    this_thread::sleep_for(chrono::milliseconds(60));
                    cout << " \n";
                }
                break;
            case 6:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << RED << "Invalid choice. Please try again.\n" << RESET;
        }
    }

    return 0;
}
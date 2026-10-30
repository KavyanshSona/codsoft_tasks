#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <sstream>
using namespace std;

struct Task {
    int id;
    string title;
    string description;
    string priority; // High, Medium, Low
    string dueDate;
    bool completed;
    string createdAt;
};

class TodoManager {
private:
    vector<Task> tasks;
    int nextId;
    const string dataFile = "tasks_data.csv";

    string getCurrentTime(){
        time_t now = time(0);
        tm *ltm = localtime(&now);
        stringstream ss;
        ss << 1900+ltm->tm_year << "-" << 1+ltm->tm_mon << "-" << ltm->tm_mday;
        return ss.str();
    }

    void saveToFile(){
        ofstream file(dataFile);
        for(auto &t: tasks){
            file << t.id << "," << t.title << "," << t.description << "," 
                 << t.priority << "," << t.dueDate << "," << t.completed << "," << t.createdAt << "\n";
        }
        file.close();
    }

    void loadFromFile(){
        ifstream file(dataFile);
        if(!file.is_open()) return;
        string line;
        tasks.clear();
        int maxId=0;
        while(getline(file, line)){
            stringstream ss(line);
            Task t; string compStr;
            getline(ss, line, ','); t.id = stoi(line);
            getline(ss, t.title, ',');
            getline(ss, t.description, ',');
            getline(ss, t.priority, ',');
            getline(ss, t.dueDate, ',');
            getline(ss, compStr, ','); t.completed = (compStr=="1");
            getline(ss, t.createdAt, ',');
            tasks.push_back(t);
            if(t.id>maxId) maxId=t.id;
        }
        nextId = maxId+1;
        file.close();
    }

public:
    TodoManager(): nextId(1){
        cout << "========================================\n";
        cout << "  PROFESSIONAL TO-DO LIST MANAGER v3.0\n";
        cout << "  CODSOFT C++ INTERNSHIP PROJECT\n";
        cout << "========================================\n";
        loadFromFile();
    }

    void addTask(){
        Task t;
        t.id = nextId++;
        cout << "Enter Task Title: ";
        cin.ignore(); getline(cin, t.title);
        cout << "Enter Description: ";
        getline(cin, t.description);
        cout << "Enter Priority (High/Medium/Low): ";
        getline(cin, t.priority);
        cout << "Enter Due Date (YYYY-MM-DD): ";
        getline(cin, t.dueDate);
        t.completed = false;
        t.createdAt = getCurrentTime();
        tasks.push_back(t);
        saveToFile();
        cout << "Task Added Successfully with ID: " << t.id << endl;
    }

    void viewAllTasks(){
        if(tasks.empty()){ cout << "No tasks available.\n"; return; }
        cout << "\n" << string(100,'-') << "\n";
        cout << left << setw(5) << "ID" << setw(15) << "Title" << setw(12) << "Priority" 
             << setw(12) << "Due Date" << setw(10) << "Status" << "Description\n";
        cout << string(100,'-') << "\n";
        for(auto &t: tasks){
            cout << left << setw(5) << t.id << setw(15) << t.title.substr(0,14) 
                 << setw(12) << t.priority << setw(12) << t.dueDate 
                 << setw(10) << (t.completed ? "DONE" : "PENDING") << t.description << endl;
        }
        cout << string(100,'-') << "\n";
    }

    void markComplete(){
        viewAllTasks();
        cout << "Enter ID to mark complete: ";
        int id; cin >> id;
        for(auto &t: tasks){
            if(t.id==id){ t.completed=true; saveToFile(); cout << "Task " << id << " marked as DONE!\n"; return; }
        }
        cout << "Task ID not found!\n";
    }

    void deleteTask(){
        viewAllTasks();
        cout << "Enter ID to delete: ";
        int id; cin >> id;
        auto it = remove_if(tasks.begin(), tasks.end(), [id](Task &t){ return t.id==id; });
        if(it!=tasks.end()){
            tasks.erase(it, tasks.end());
            saveToFile();
            cout << "Task deleted!\n";
        } else cout << "ID not found!\n";
    }

    void searchTask(){
        cout << "Enter keyword to search: ";
        string key; cin.ignore(); getline(cin, key);
        bool found=false;
        for(auto &t: tasks){
            if(t.title.find(key)!=string::npos || t.description.find(key)!=string::npos){
                cout << "Found -> ID:" << t.id << " Title:" << t.title << " Status:" << (t.completed?"Done":"Pending") << endl;
                found=true;
            }
        }
        if(!found) cout << "No matching task found.\n";
    }

    void filterByPriority(){
        cout << "Enter priority to filter (High/Medium/Low): ";
        string p; cin >> p;
        for(auto &t: tasks) if(t.priority==p) 
            cout << t.id << ". " << t.title << " - Due: " << t.dueDate << endl;
    }

    void showStats(){
        int done=0, pending=0, high=0;
        for(auto &t: tasks){
            if(t.completed) done++; else pending++;
            if(t.priority=="High") high++;
        }
        cout << "\n--- TASK STATISTICS ---\n";
        cout << "Total Tasks: " << tasks.size() << endl;
        cout << "Completed: " << done << endl;
        cout << "Pending: " << pending << endl;
        cout << "High Priority Tasks: " << high << endl;
    }

    void run(){
        int ch;
        do{
            cout << "\n--- TO-DO MENU ---\n";
            cout << "1. Add New Task\n2. View All Tasks\n3. Mark Task as Complete\n4. Delete Task\n";
            cout << "5. Search Task\n6. Filter by Priority\n7. View Statistics\n8. Exit\nChoice: ";
            cin >> ch;
            switch(ch){
                case 1: addTask(); break;
                case 2: viewAllTasks(); break;
                case 3: markComplete(); break;
                case 4: deleteTask(); break;
                case 5: searchTask(); break;
                case 6: filterByPriority(); break;
                case 7: showStats(); break;
                case 8: cout << "Saving and exiting...\n"; break;
                default: cout << "Invalid!\n";
            }
        }while(ch!=8);
    }
};

int main(){
    TodoManager manager;
    manager.run();
    return 0;
}

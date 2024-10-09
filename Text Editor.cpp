#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <dirent.h>

using namespace std;

int main() {
    while (true) {
        system("clear"); 
        cout << "Welcome to Text Editor" << endl << endl;
        cout << "Main Menu" << endl;
        cout << "-------------" << endl;
        cout << "1. Create File" << endl;
        cout << "2. Add to File" << endl;
        cout << "3. Read from File" << endl;
        cout << "4. Empty File" << endl;
        cout << "5. Delete File" << endl;
        cout << "6. Copy File" << endl;
        cout << "7. Edit File in Nano" << endl;
        cout << "8. List Files (with serial number)" << endl;
        cout << "9. Exit" << endl << endl;      
        cout << "Enter Choice: ";

        int choice = 0;
        string filename;
        string text;

        cin >> choice;
        if (choice == 1) {
            cout << endl << "Enter name of file: ";
            cin.ignore();
            getline(cin, filename);
            ofstream myfile((filename + ".txt").c_str());
            myfile.close();
            cout << "File Created Successfully" << endl << endl;
        } else if (choice == 2) {
            text = "";
            cout << endl << "Enter name of file: ";
            cin >> filename;
            cout << endl << "Enter text to write to file: (Enter END to complete)" << endl;
            ofstream myfile;
            myfile.open((filename + ".txt").c_str(), ios::app);
            string line;
            cin.ignore();
            while (getline(cin, line)) {
                if (line.size() >= 3) {
                    if (line.substr(line.size() - 3) == "END") {
                        text += line.substr(0, line.size() - 3);
                        break;
                    } else {
                        text += line + "\n";
                    }
                } else {
                    text += line + "\n";
                }
            }
            myfile << text;
            myfile.close();
            cout << "File Updated Successfully" << endl << endl;
        } else if (choice == 3) {
            text = "";
            cout << endl << "Enter name of file: ";
            cin >> filename;
            fstream myfile;
            myfile.open((filename + ".txt").c_str());
            while (getline(myfile, text)) {
                cout << text << "\n";
            }
            myfile.close();
            char now;
            cout << endl << "End of File. Press any key for main menu: ";
            cin >> now;
        } else if (choice == 4) {
            cout << endl << "Enter name of file: ";
            cin >> filename;
            ofstream myfile;
            myfile.open((filename + ".txt").c_str());
            myfile << "";
            myfile.close();
            cout << "File Emptied Successfully" << endl << endl;
        } else if (choice == 5) {
            cout << endl << "Enter name of file: ";
            cin >> filename;
            if (remove((filename + ".txt").c_str()) == 0) {
                cout << "File Deleted Successfully" << endl << endl;
            } else {
                cout << "File Not Found" << endl << endl;
            }
        } else if (choice == 6) {
            text = "";
            cout << endl << "Enter name of file to copy from: ";
            cin.ignore();
            getline(cin, filename);
            fstream myfile((filename + ".txt").c_str());
            string line;
            while (getline(myfile, line)) {
                text += line + "\n";
            }
            myfile.close();
            cout << endl << "Enter name of file to copy to: ";
            string second;
            getline(cin, second);
            ofstream myfile2;
            myfile2.open((second + ".txt").c_str(), ios::app);
            myfile2 << text;
            myfile2.close();
            cout << "File Copied Successfully" << endl << endl;
        } else if (choice == 7) {
            cout << endl << "Enter the name of the file to edit: ";
            cin >> filename;
            string command = "nano " + filename + ".txt";
            system(command.c_str());
        } else if (choice == 9) {
            exit(EXIT_SUCCESS);
        } else if (choice == 8) {
           
            vector<string> files;
            DIR *dir;
            struct dirent *ent;
            if ((dir = opendir(".")) != NULL) {
                int sr_no = 1;
                while ((ent = readdir(dir)) != NULL) {
                    string file_name = ent->d_name;
             
                    if (file_name[0] != '.') {
                        files.push_back(file_name);
                        cout << sr_no++ << ". " << file_name << endl;
                    }
                }
                closedir(dir);
            } else {
                cout << "Unable to open directory" << endl;
            }
            int file_choice;
            cout << endl << "Enter the serial number of the file to open: ";
            cin >> file_choice;
            if (file_choice > 0 && file_choice <= files.size()) {
                string selected_file = files[file_choice - 1];
                string command = "nano " + selected_file;
                system(command.c_str());
            } else {
                cout << "Invalid choice" << endl;
            }
            char now;
            cout << endl << "Press any key for main menu: ";
            cin >> now;
        }
    }

    return 0;
}

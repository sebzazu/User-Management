#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void createUser(fstream& file);
void deleteUser(fstream&file);
void readUsernames(fstream&file);
void updateUser(fstream&file);
void crud();

int main(){
    crud();
   

    return 0;
}

void crud(){
    fstream file;
    char repeat;
    char use;
    bool valid = false;


    while (valid == false){
        cout << "What would you like to do? Create, Read, Update, or Delete? (c/r/u/d)";
        cin >> use;

        if (use == 'c'){
            valid = true;
            createUser(file);
        }
        if (use == 'r'){
            valid = true;
            readUsernames(file);
        }   
        if (use == 'u'){
            valid = true;
            updateUser(file);
        }
        if (use == 'd'){
            valid = true;
            deleteUser(file);
        }

    }

    cout << "Would you like to do anything else? ";
    cin >> repeat;

    if (repeat == 'y')
        crud();
    
}

void createUser(fstream &file){

    string username, password, line;

    file.open("users.txt", ios::app);
  
    
    cout << "Enter Username and Password separated by space";
    cin >> username >> password;

  
    file << username << "/" << password << "\n";
       
    file.close();
}

void readUsernames(fstream &file){
    string line;
    int passpos;

    file.open("users.txt", ios::in);

    while (getline(file, line)){
         passpos = line.find("/");

         for (int i = 0; i < passpos; ++i){
            cout << line[i];
         }
         cout << endl;
    }
}


void deleteUser(fstream &file){
    int linecount = 0;
    string username;
    string line;
    cout << "Enter the username of the user you want to delete: ";
    cin >> username;

    
    fstream temp;
    temp.open("temp.txt", ios::out);
    file.open("users.txt", ios::in);

    while (getline(file,line)){
        if (line.find(username)==string::npos) {
            temp << line << "\n";
        }
    }

    temp.close();
    file.close();
    
    const char * p = "users.txt";
    
    remove(p);
    
    rename("temp.txt", "users.txt");
}



void updateUser(fstream &file){
    string line;
    string username;
    string oldpass;
    string newpass;
    string userPass;
    int passpos;
    ofstream temp;
    bool correct_pass = false;

   
    do{
        cout << "What User would you like to update? ";
        cin >> username;

        cout << "Please enter current password: ";
        cin >> oldpass;

        userPass = username + "/" + oldpass;
        file.open("users.txt", ios::in);

        while (getline(file, line)){
          if(line == userPass)
            correct_pass = true;
          
       
        }
        file.close();
        
        if (correct_pass == false){
            cout << "Invalid username or password, please try again" << endl;
        }

    }
    while(correct_pass == false);
    
    cout << "Please enter new password" << endl;
    cin >> newpass;

    file.open("users.txt", ios::in);
    temp.open("temp.txt", ios::out);

    while(getline(file, line)){
         if (line != userPass) 
            temp << line << "\n";
        
        else {

             passpos = line.find("/");

            for (int i = 0; i < passpos; ++i){
                temp << line[i];
            }

            temp << "/" << newpass << "\n";
        }
    }
   
    temp.close();
    file.close();
    
    const char * p = "users.txt";
    
    remove(p);
    
    rename("temp.txt", "users.txt");
}

     
  
  

    





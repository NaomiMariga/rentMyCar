#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;


//global variables for successfull login
string name;
string sName;

/**
 * basic storage container // implemented in login 
 */
class User {
public:
    string password;
    string fName;
    string lName;
    string email;
};

/*

Registration function for adminstrator and customer

*/

void registration(){
    string firstName;
    string surName;
    string password;
    string email;
    int selector;
    cout << "Are you an adminstrator \n";
    cout << "1. For admintsrtor account enter 1 \n";
    cout << "2. For rental account enter 2 \n";
    cin >> selector; // option 1 or 2

    if (selector == 2){
        cout << "Enter your first name \n";
        cin >> firstName;
        cout << "Enter yours surname \n";
        cin >> surName;
        cout << "Enter your password \n";
        cin >> password;
        cout << "Welcome " << firstName << " " << surName << " Your account has been created Please proceed to login \n";

        ofstream dataFile;
        dataFile.open("usersDB.txt", ios::app);//ios:app is for writing to existing data file to avoid overwriting 

        //checking for file errors

        if(dataFile.fail()){
            cerr << "Error opening the file";
            exit(1);
        }

        dataFile << firstName<< "," << surName << ","<< password << endl;
        dataFile.close();

    } else if(selector == 1){
        ofstream dataFile;
        dataFile.open("adminDB.txt",ios::app); //ios::app is for adding data to an existing data

        //checking for error while opening
        if(dataFile.fail()){
            cerr << "Error opening the file";
            exit(1);
        }

        cout << "Enter your first name \n";
        cin >> firstName;
        cout << "Enter yours surname \n";
        cin >> surName;
        cout << "Enter yours admin email \n";
        cin >> email;
        cout << "Enter your password \n";
        cin >> password;
        cout << "Welcome Adminstrator " << firstName << " " << surName << " Your account has been created Please proceed to login \n"; 
        dataFile << firstName << ","<<surName<< ","<<email<< "," <<password << endl; //Write to file adminDB.txt
        
        dataFile.close(); //close the file

    } else{
        cout << "Your " << selector <<" seletion was not recognized. Please try again!";
    }
}

/*
Login Function for both admin and customer

*/
void login(){
    int selector;
    string username; // implemented in the car renter login and expects it to be the surname
    string inputPassword; // implemented for admin login
    string inputEmail; // inmplemented in both admin and car renter login
    cout << "1. Login as Adminstrator \n";
    cout << "2. Login as car renter \n";
    cin >> selector;

    //Implementing Admin Login 
    if (selector == 1){
        cout << "Enter your email: \n";
        cin >> inputEmail;
        cout << "Enter your Password: \n";
        cin >> inputPassword;

        ifstream dataFile;
        vector<User>vector;//use a vector to store the unknown number of users that you will read from the file
        dataFile.open("adminDB.txt");
        
        
        //checking errors while opening the file
        if (dataFile.fail()){
            cerr << "File could not open \n";
            exit(1);
        }

        //retrieving stored information from the adminDB text files
        string line;
        while (getline(dataFile, line)){ // this will loop through all the data in the text file
            
            //split the line
            int position = line.find(",");
            string fName = line.substr(0, position);
            //erase the first name and get the next substring
            line.erase(0, position + 1);
            position = line.find(",");
            string lName = line.substr(0, position);
            //erase the surname and get the next substring
            line.erase(0, position + 1);
            position = line.find(",");
            string email = line.substr(0, position);
            //erase the email and get the next substring
            line.erase(0, position + 1);
            position = line.find(",");
            string password = line.substr(0, position);

            //create a user object
            User user;
            user.fName = fName;
            user.lName = lName;
            user.email = email;
            user.password = password;

            //store the user in a vector. If using an array then make sure the array is large enough
            vector.push_back(user);

            
        }
        // doing the checks on user input data
        //go through your vector or array and check if the user is there
        bool userFound=false;
        for(int i=0;i<vector.size();i++){
            if(vector[i].email==inputEmail && vector[i].password==inputPassword){
                userFound= true;
                name = vector[i].fName;
                sName = vector[i].lName;

                break;
            }
        }
        if(userFound){
            cout <<"Welcome Admin " <<name<<" " <<sName << ". You are logged in!" << endl;
        }else{
            cout << "Invalid username and password" << endl;
        }
        // Implementing car renter login
    }else if (selector == 2){
        cout << "Enter your surName: \n";
        cin >> username;
        cout << "Enter your Password:  \n";
        cin >> inputPassword;


        ifstream dataFile;
        vector<User>vector; //use a vector to store the unknown number of users that you will read from the file
        dataFile.open("usersDB.txt");

        //checking errors while opening file
        if (dataFile.fail()){
            cerr << "File could not open \n";
            exit(1);
        }
        // Retreiving data from users text file
        string line;
        while (getline(dataFile, line)){ // this will loop through all the user data in the text file
        
            //split the line
            int position = line.find(",");
            string fName = line.substr(0, position);
            //erase the first name and get the next substring
            line.erase(0, position + 1);
            position = line.find(",");
            string lName = line.substr(0, position);
            //erase the surname and get the next substring
            line.erase(0, position + 1);
            position = line.find(",");
            string password = line.substr(0, position);

            //create a user object
            User user;
            user.fName = fName;
            user.lName = lName;
            user.password = password;

            //store the user in a vector. If using an array then make sure the array is large enough
            vector.push_back(user);

            
        }
        // doing the checks on user input data
        //go through your vector or array and check if the user is there
        bool userFound=false; 
        for(int i=0;i<vector.size();i++){
            if(vector[i].lName==username && vector[i].password==inputPassword){
                userFound= true;
                name = vector[i].fName;
                sName = vector[i].lName;

                break;
            }
        }

        //If user was found we grant access otherwise we deny
        if(userFound){
            cout <<"Welcome customer " <<name<<" " <<sName << ". You are logged in!" << endl;
        }else{
            cout << "Invalid username or password" << endl;
        }

    }else{
            cout << "You pressed "<< selector << " please try again! \n";
    }


}

int main(){
    registration();
    login();
    return 0;    
}

/* 
Author: Lasha Zibzibadze
Course: CSCI-135
Instructor: Genady Maryash

Class Network : Social Media Platform .
*/
#include <iostream>
#include <string>
using namespace std;

struct Post{
  string username;
  string message;
};

class Profile{
    private:
        string displayname;
        string username;
    public:
        Profile(string usrn, string dspn);
        Profile();
        string getUsername();
        string getFullName();
        void setDisplayName(string dspn);
};
//Constructors
Profile::Profile(){
    this->displayname= "";
    this->username= "";
}

Profile::Profile(string usrn, string dspn){
    username= usrn;
    displayname= dspn;
}
//getters
string Profile::getUsername(){
    return username;
}

string Profile::getFullName(){
    string new_format= displayname + " (@" + username + ")";
    return new_format;
}
//setter
void Profile::setDisplayName(string dspn){
    displayname= dspn;
}

class Network {
private:
  static const int MAX_USERS = 20; // max number of user profiles
  int numUsers;                    // number of registered users
  Profile profiles[MAX_USERS];     // user profiles array:
                                   // mapping integer ID -> Profile
  bool following[MAX_USERS][MAX_USERS];  // friendship matrix:
  // following[id1][id2] == true when id1 is following id2

  // Returns user ID (index in the 'profiles' array) by their username
  // (or -1 if username is not found)
  int findID (string usrn);
  static const int MAX_POSTS = 100;
  int numPosts;                    // number of posts
  Post posts[MAX_POSTS];           // array of all posts

public:
  // Constructor, makes an empty network (numUsers = 0)
  Network();
  // Attempts to sign up a new user with specified username and displayname
  // return true if the operation was successful, otherwise return false
  bool addUser(string usrn, string dspn);
  // Make 'usrn1' follow 'usrn2' (if both usernames are in the network).
  // return true if success (if both usernames exist), otherwise return false
  bool follow(string usrn1, string usrn2);

  // Print Dot file (graphical representation of the network)
  void printDot();
   // Add a new post
  bool writePost(string usrn, string msg);
  // Print user's "timeline"
  bool printTimeline(string usrn);

};

int Network::findID(string usrn){

    for(int ind=0; ind <= numUsers; ind++ ){
        if(profiles[ind].getUsername() == usrn){
            int id_number;
            id_number= ind;
            return id_number;
        }
    }


    return -1;
}

Network::Network(){
    numUsers = 0;
    //Setting users to have no followers
    for(int i=0; i< MAX_USERS; i++){
        for(int k=0; k< MAX_USERS; k++){
            following[i][k] == false;
        }
    }
    numPosts= 0;

}

bool Network::addUser(string usrn, string dspn){
    int counter= 0;
    if( usrn != "" && numUsers < MAX_USERS && findID(usrn) == -1){
        for(int i=0; i < usrn.size(); i++){
            if(!isdigit(usrn[i]) && !isalpha(usrn[i])){
                counter++;
            }
        }
        if(counter != 0){
            return false;
        }

        Profile fresh_user(usrn, dspn);
        profiles[numUsers] = fresh_user;
        numUsers= numUsers +1;

        return true;
    }
    else{
        return false;
    }

}

bool Network::follow(string usrn1, string usrn2){
    if(findID(usrn1) != -1 && findID(usrn2) != -1){

        following[findID(usrn1)][findID(usrn2)] = true;

        // if(usrn1 == usrn2){
        //     return false;
        // }
        return true;
    }
    else{
        return false;
    }

}

void Network::printDot(){
    char c= '"';
    cout<< "digraph {"<<endl;
    for(int i=0; i < numUsers; i++ ){
        //if(profiles[i].getUsername() != ""){
        cout<< "  " <<c << "@" << profiles[i].getUsername() << c << endl;
        //}
    }
    cout<<endl;
    for(int k= 0; k < numUsers; k++){
        for(int v=0; v < numUsers; v++){
            if(following[k][v] == true){
                cout<< "  " <<c << "@" << profiles[k].getUsername() << c << " -> " << c << "@" << profiles[v].getUsername() << c << endl;
            }
        }
    }
    cout<< "}";
}

bool Network::writePost(string usrn, string msg){
    if(findID(usrn) != -1 && usrn != ""){
        posts[numPosts].message = msg;
        posts[numPosts].username = usrn;
        numPosts++;
        return true;
    }
    else{
        return false;
    }
}

bool Network::printTimeline(string usrn){

    if(findID(usrn) != -1){
        for(int i= numPosts - 1;  i>= 0; i--){
            Post timeline_author= posts[i];
            if(timeline_author.username == usrn){
                cout<< profiles[findID(usrn)].getFullName() << ":" << " " << timeline_author.message<< endl; 
            }
            else if(following[findID(usrn)][findID(timeline_author.username)]){
                cout<< profiles[findID(timeline_author.username)].getFullName() << ":" << " " << timeline_author.message<< endl;
            }

        }
    }
    else{
        return false;
    }

    return true;
}

int main() {
  Network nw;
  // add three users
  nw.addUser("mario", "Mario");
  nw.addUser("luigi", "Luigi");
  nw.addUser("yoshi", "Yoshi");
   
  nw.follow("mario", "luigi");
  nw.follow("luigi", "mario");
  nw.follow("luigi", "yoshi");
  nw.follow("yoshi", "mario");

  // write some posts
  nw.writePost("mario", "It's a-me, Mario!");
  nw.writePost("luigi", "Hey hey!");
  nw.writePost("mario", "Hi Luigi!");
  nw.writePost("yoshi", "Test 1");
  nw.writePost("yoshi", "Test 2");
  nw.writePost("luigi", "I just hope this crazy plan of yours works!");
  nw.writePost("mario", "My crazy plans always work!");
  nw.writePost("yoshi", "Test 3");
  nw.writePost("yoshi", "Test 4");
  nw.writePost("yoshi", "Test 5");

  cout << endl;
  cout << "======= Mario's timeline =======" << endl;
  nw.printTimeline("mario");
  cout << endl;

  cout << "======= Yoshi's timeline =======" << endl;
  nw.printTimeline("yoshi");
  cout << endl;
}

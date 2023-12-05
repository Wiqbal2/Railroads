//UMBC - CSEE - CMSC 341 - Fall 2022 - Proj1
#pragma once
#include <iostream>
#include <string>
#include <list>
using namespace std;
enum DIRECTION {NORTH, SOUTH, EAST, WEST, NONE};
const int DEFNUMPASS = 10; // default number of passengers
class Grader;
class Tester;
class Railroad;
class Station{
    public:
    friend class Grader;
    friend class Tester;
    friend class Railroad;
    Station():m_code(0), m_passengers(0), 
        m_next(nullptr), m_previous(nullptr),
        m_north(nullptr), m_south(nullptr),
        m_east(nullptr), m_west(nullptr){}
    Station(int c, int p):m_code(c), m_passengers(p), 
        m_next(nullptr), m_previous(nullptr),
        m_north(nullptr),m_south(nullptr),
        m_east(nullptr), m_west(nullptr){}
    Station(int c, int p, Station* n, Station* s, Station* e, Station* w):
        m_code(c),m_passengers(p), 
        m_north(n),m_south(s),
        m_east(e),m_west(w){}
    ~Station(){}
    void setStationCode(int aValue){m_code = aValue;}
    int getStationCode(){return m_code;}
    void setNumPassengers(int p){m_passengers=p;}
    int getNumPassegers(){return m_passengers;}
    void setNext(Station * aNode){m_next=aNode;}
    Station * getNext(){return m_next;}
    void setPrevious(Station * aNode){m_previous = aNode;}
    Station * getPrevious(){return m_previous;}
    void setNorth(Station * aNode){m_north = aNode;}
    Station * getNorth(){return m_north;}
    void setSouth(Station * aNode){m_south = aNode;}
    Station * getSouth(){return m_south;}
    void setEast(Station * aNode){m_east = aNode;}
    Station * getEast(){return m_east;}
    void setWest(Station * aNode){m_west = aNode;}
    Station * getWest(){return m_west;}

    private:
    int m_code;//stores the station code number
    int m_passengers;// the number of passengers who board the train
    Station * m_next;
    Station * m_previous;
    Station * m_north;
    Station * m_south;
    Station * m_east;
    Station * m_west;
};

class Railroad{
    public:
    friend class Grader;
    friend class Tester;
    Railroad();
    Railroad(const Railroad & rhs);// copy constructor
    ~Railroad();// delete all memory
    void dump();// print the list of stations
    const Railroad & operator=(const Railroad & rhs);// overloaded assignment operator
    bool extendAtHead(int newCode, int passengers);
    bool extendAtTail(int newCode, int passengers);
    bool makeRoute(list< pair<int,DIRECTION> > route);
    int travel(list< pair<int,DIRECTION> > route);
    bool removeStation(int aCode);// this removes a node from the list
    void clearAllRoutes();// this clears all routes, resets all direction pointers
    bool setNumPassengers(int code, int passengers);
    void clearNetwork();// delete all memory and reset all member variables

    private:
    int m_numStations;// number of stations in the network
    Station * m_head;
    Station * m_tail;

    // ***************************************************
    // Any private helper functions must be delared here!
    // ***************************************************
    bool checkFirst(list< pair<int,DIRECTION> > route);
    bool checkForModify(int code);
    int checkForNone(list< pair<int,DIRECTION> > route);
    //bool Railroad::findRemove(list< pair<int,DIRECTION> > route, int code);
    //bool Railroad::helpRemove(list< pair<int,DIRECTION> > route,int code);
    
    






};
//UMBC - CSEE - CMSC 341 - Fall 2022 - Proj1
//#include "railroad.h"
Railroad::Railroad(){
    //Default constructor creates an empty object and initializes member variables.
    
    Station temp(0,0);
    m_numStations = 0;
    m_head = nullptr;
    m_tail = nullptr;
    
    

}

Railroad::~Railroad(){
    //Destructor deallocates all memory and reinitializes member variables.
    clearNetwork();
    
}

void Railroad::clearNetwork(){
    //This public function deallocates all memory and reinitializes member variables.

    //if only one station
    //if more than one station
    if (m_head == nullptr){
        delete m_head;
        delete m_tail;
        m_head = nullptr;
        m_tail = nullptr;
        m_numStations = 0;
    }
    else{
        Station * temp = nullptr;
        
        while(m_head != nullptr){
            temp = m_head;
            temp->setNorth(nullptr);
            temp->setEast(nullptr);
            temp->setWest(nullptr);
            temp->setSouth(nullptr);
            m_head = temp->getNext();
            delete temp;
        }
        m_head = nullptr;
        m_tail = nullptr;
        m_numStations = 0;
        
    }
    
}

bool Railroad::extendAtHead(int newCode, int passengers){
    /*This function creates and inserts a new Station object at the head of the list. 
    If the insertion is successful the function returns true, 
    otherwise it returns false. Since the station codes must be unique in the list 
    this function will not insert the station if it already exists.*/

    bool check = false;//station code does not exist
    Station *temp = m_head;
    if (newCode < 1){
        cout<<"code is less than 1" <<endl;
        return false;
    }
    while(temp != nullptr && check != true){
        
        if (temp->getStationCode() != newCode){
            //Station code has not been detected yet 
            check = false;
        }
        else{
            //The station code exists
            check = true;
        }
        temp = temp->getNext();
    }

    //return false, Station code does exist
    if (check == true){
        return false;
    }
    else{
        if (newCode < 0){
            cout<<"stationcode must be greater than 0"<<endl;
            return false;
        }
        Station *insert = new Station(newCode,passengers);

        //if list is empty
        if (m_head == nullptr){
            m_head = insert;
            m_tail = insert;
            //successfully inserted
            m_numStations += 1;
            return true;
        }
        //atleast or more than one
        else{
            
            insert->setNext(m_head);
            m_head->setPrevious(insert);
            m_head = insert;  
            m_numStations += 1;
            //successfully inserted  

            return true;        
        }
    }
    
    
}

bool Railroad::extendAtTail(int newCode, int passengers){
    /*This function creates and inserts a new Station object at the tail of the list. 
    If the insertion is successful the function returns true, 
    otherwise it returns false. Since the station codes must be unique in the list 
    this function will not insert the station if it already exists.*/
    
    bool check = false;//station code does not exist
    //dummy node
    Station *temp = m_head;
    //stop when the end is reached and stop when the boolis true(same code exists)
    

    if (newCode < 1){
        cout<<"code is less than 1" <<endl;
        return false;
    }
    while(temp != nullptr ){
        
       //traverse through linked list
       
        if (temp->getStationCode() != newCode){
            
            
            //Station code has not been detected yet 
            check = false;
            
        }
        else{
            //The station code exists
            
            check = true;
        }
        
        temp = temp->getNext();
       
    }
    //return false, Station code does exist
    
    if (check == true){
        
        return false;
    }
    else{
        
        //creating new station object node
        Station *insert = new Station(newCode,passengers);
        
        //if list is empty
        if (m_head == nullptr){
            
            m_head = insert;
            m_tail = insert;
            //successfully inserted
            m_numStations += 1;
            return true;
        }
        //atleast one or more than one
        else{
            
            insert->setPrevious(m_tail);
            m_tail->setNext(insert);
            m_tail = insert;  
            m_numStations += 1;
            //successfully inserted  
            return true;        
        }
    }
}

void Railroad::dump(){
    if (m_head != nullptr){
        int northCode, southCode, eastCode, westCode;
        Station *temp = m_head;
        while(temp != nullptr){
            if (temp->m_north != nullptr) northCode = temp->m_north->m_code;
            else northCode = -1;
            if (temp->m_south != nullptr) southCode = temp->m_south->m_code;
            else southCode = -1;
            if (temp->m_east != nullptr) eastCode = temp->m_east->m_code;
            else eastCode = -1;
            if (temp->m_west != nullptr) westCode = temp->m_west->m_code;
            else westCode = -1;
            cout << temp->m_code << 
                    " (" << 
                    "P: " << temp->m_passengers << 
                    ", N: " << northCode <<
                    ", S: " << southCode <<
                    ", E: " << eastCode <<
                    ", W: " << westCode <<
                    ")" << endl;
            temp = temp->m_next;
        }
    }
}
bool Railroad::checkFirst(list< pair<int,DIRECTION> > route){
    //check If the first node of the route exists
    for (list<pair<int,DIRECTION > >::iterator it = route.begin(); it != route.end(); ++it){
        Station *temp = m_head;
        while(temp != nullptr){
            if(it->first != temp->getStationCode()){
                temp = temp->getNext();
            }
            else{
                return true;
            }
        }
        return false;
    }


}

bool Railroad::checkForModify(int code){
    //if station is not present this function creates the station and inserts it into the tail.
        Station *temp = m_head;
        while (temp != nullptr){
            if (temp->getStationCode() != code){
                temp = temp->getNext();
            }
            else{
                return true;
            }
        }
        extendAtTail(code, DEFNUMPASS);
        cout<<"NEW station has been added "<<endl;
        return false;
    
}

bool Railroad::makeRoute(list< pair<int,DIRECTION> > route){
    /*
This function allows for creating a route. The route parameter is a list of pair objects which are inserted in the order that defines the route. 
Every pair contains a station code and a direction, e.g. (2, NORTH) indicates that the route continues from station 2 in the north direction to 
the next station in route. 
If the provided route is invalid the function returns false and the linked list remains unchanged. If the route is valid and it is created successfully 
the function returns true. The route is considered invalid in the following cases:
If the first node of the route does not exist in the linked list.
If the route tries to modify an existing link from a node to another node.
If the provided list contains a valid route, we start from the first station in the list and set the links between stations. For example, if in the list we 
have (2, NORTH) followed by (5, SOUTH), the north direction of station 2 should point to the station 5. We continue setting all links specified by the route. 
If a station in the route does not exist in the linked list, first we insert it as a new node in the linked list then we set the link to it.
*/ 
    bool exist = false;
    for (list<pair<int,DIRECTION > >::iterator it = route.begin(); it != route.end(); ++it){    
        list <pair<int,DIRECTION > >:: iterator pair1;
        list <pair<int,DIRECTION > >:: iterator pair2;
        //check If the first node of the route exists
        if(checkFirst(route) == false){
            return false;
        }
        //original object we are currently on
        pair1 = it;
        //to access to next element of list object
        pair2 = ++pair1;
        cout<<"Oriinal station : "<<it->first<<" "<< it->second<<endl;
        cout<<"next station : "<<pair2->first<<" "<< pair2->second<<endl;

        Station *initial = m_head;
            //fininding if station is available in the list
        while(initial != nullptr  ){
            
            if(initial->getStationCode() != it->first){        
                initial = initial->getNext();
                
                
            }
            else{
                //it exists
                //station code found
                
                if(it->second == 0){
                    checkForModify(pair2->first);
                    //North
                    //traverse list one more time under the same for loop to find what the next station to be connected to is
                    
                    Station *temp2 = m_head;
                    
                    while(temp2!= nullptr){
                        //checking if pair2 station exists and if it needs to be inserted 
                        if(temp2->getStationCode() == pair2->first ){
                            //stop from making a route with the same station
                            if(initial->getStationCode() == temp2->getStationCode()){
                                cout<<"cant make route to same station"<<endl;
                                return false;
                            }
                            
                            //setting the direction of first temp to the second temps station
                            if (initial->getNorth() == nullptr){
                                initial->setNorth(temp2);
                                initial->setEast(nullptr);
                                initial->setWest(nullptr);
                                initial->setSouth(nullptr);
                                initial = nullptr;
                                temp2 = temp2->getNext();
                                

                            }
                            else{
                                cout<<"invalid route"<<endl;
                                return false;
                            }
                        }
                        else{
                            temp2 = temp2->getNext();
                        }
                    }
                }

                else if (it->second == 1){
                    
                    //South
                    //traverse list one more time under the same for loop to find what the next station to be connected to is
                    Station *temp2 = m_head;
                    checkForModify(pair2->first);
                    while(temp2!= nullptr){
                        if(temp2->getStationCode() == pair2->first ){
                            //stop from making a route with the same station
                            if(initial->getStationCode() == temp2->getStationCode()){
                                cout<<"cant make route to same station"<<endl;
                                return false;
                            }
                            //setting the direction of first temp to the second temps station
                            if (initial->getSouth() == nullptr){
                                initial->setSouth(temp2);
                                initial->setNorth(nullptr);
                                initial->setEast(nullptr);
                                initial->setWest(nullptr);
                                initial = nullptr;
                                temp2 = temp2->getNext();
                            }
                            else{
                                cout<<"overide a route"<<endl;
                                return false;
                            }
                            
                        }
                        else{
                            temp2 = temp2->getNext();
                        }
                        
                    }

                }

                 else if (it->second == 2){
                    //East
                    //traverse list one more time under the same for loop to find what the next station to be connected to is
                    checkForModify(pair2->first);
                    Station *temp2 = m_head;
                    while(temp2!= nullptr){
                        
                        if(temp2->getStationCode() == pair2->first ){
                            //stop from making a route with the same station
                            if(initial->getStationCode() == temp2->getStationCode()){
                                cout<<"cant make route to same station"<<endl;
                                return false;
                            }
                            //setting the direction of first temp to the second temps station
                            if (initial->getEast() == nullptr){
                                initial->setNorth(nullptr);
                                initial->setEast(temp2);
                                initial->setWest(nullptr);
                                initial->setSouth(nullptr);
                                initial = nullptr;
                                temp2 = temp2->getNext();       
                            }
                            else{
                                cout<<"overide a route"<<endl;
                                return false;
                            }
                        }
                        else{
                            temp2 = temp2->getNext();
                        }
                    }
                }

                else if (it->second == 3){
                    //West
                    //traverse list one more time under the same for loop to find what the next station to be connected to is
                    checkForModify(pair2->first);
                    Station *temp2 = m_head;
                    while(temp2!= nullptr){
                        
                        //check for if the the direction is already made for a station
                        if(temp2->getStationCode() == pair2->first ){
                            //stop from making a route with the same station
                            if(initial->getStationCode() == temp2->getStationCode()){
                                cout<<"cant make route to same station"<<endl;
                                return false;
                            }
                            //setting the direction of first temp to the second temps station
                            if (initial->getWest() == nullptr){
                                initial->setWest(temp2);
                                initial->setNorth(nullptr);
                                initial->setEast(nullptr);
                                initial->setSouth(nullptr);
                                initial = nullptr;
                                temp2 = temp2->getNext();
                            }
                            else{
                                cout<<"overide a route"<<endl;
                                return false;
                            }
                           
                            
                        }
                        else{
                            temp2 = temp2->getNext();
                        }
                    }
                }
                else if (it->second == 4){
                    //checking to see if this staton has any directions associated with it, making sure its emoty
                    if(initial->getEast() == nullptr && initial->getWest() == nullptr && initial->getNorth() == nullptr && initial->getSouth() == nullptr ){
                        //return false if the direction none was used before reaching the end of the list object pairs
                        if (checkForNone(route) > 1){
                            cout<<"No station can be assigned a direction in a route once None is used as a direction"<<endl;
                            return false;
                        }
                        //setting evrything to null because this is the end of the list
                        initial->setEast(nullptr);
                        initial->setWest(nullptr);
                        initial->setNorth(nullptr);
                        initial->setSouth(nullptr);
                        initial = nullptr;
                    }
                    else{
                        //attempt to overide a route
                        cout<<"overide a route"<<endl;
                        
                        //return false if the direction none was used before reaching the end of the list object pairs
                        return false;
                    }
                    //none
                
                }
                else{
                    
                    return false;
                }
            
            }
        
        }
    
    }
    cout<<"route made"<<endl;
    return true;
}


int Railroad::checkForNone(list< pair<int,DIRECTION> > route){
    //checks to see how many times the none direction is used
    int counter = 0;
    for (list<pair<int,DIRECTION > >::iterator it = route.begin(); it != route.end(); ++it){
        if (it->second == 4){
            counter++;
        }
    }
    return counter;

}



int Railroad::travel(list< pair<int,DIRECTION> > route){
    /*This function receives a list of pair objects. Every pair defines a station code and a direction. 
    This function starts from the first station in the parameter route and follows all links to the next 
    stations in the specified directions. If all links specified in the parameter route are valid the function 
    returns the total number of passengers in all stations of the route. If any station in the route does not exist 
    in the linked list or a link in the specified direction is not defined the function failes and returns -1 indicating an invalid route.*/

        int numPass = 0;
        int counter = 0;
        if (checkForNone(route) > 1){
            cout<<"cant have more than one none"<<endl;
            return -1;
        }
        
        
        for (list<pair<int,DIRECTION > >::iterator it = route.begin(); it != route.end(); ++it){
            list <pair<int,DIRECTION > >:: iterator pair3;
            list <pair<int,DIRECTION > >:: iterator pair4;
            pair3 = it;
            //to access to next element of list object
            pair4 = ++pair3;
        
            if (it->first == pair4->first){
                cout<<"invalid route cant travel to same route again"<<endl;
                return -1;
            }
            /*
            if(checkExist(it->first) != true){
                cout<<"station does not exist in the rout "<<endl;
                return -1;
            }
            */

        }
    
   
        for (list<pair<int,DIRECTION > >::iterator it = route.begin(); it != route.end(); ++it){
            list <pair<int,DIRECTION > >:: iterator pair1;
            list <pair<int,DIRECTION > >:: iterator pair2;
            bool valid = false;
            //original object we are currently on
            pair1 = it;
            //to access to next element of list object
            pair2 = ++pair1;
            Station *temp = m_head;
            
            Station *temp3 = m_head;
            if (temp3 == nullptr){
                cout<<"station is empty"<<endl;
                return -1;
            }
            else if (temp3->getStationCode() < 1){
                return -1;
            }

            while(temp3 != nullptr){
                    if (temp3->getStationCode() == it->first){
                        numPass += temp3->getNumPassegers();
                        
                        temp3 = nullptr;
                    }
                    else{
                        temp3 = temp3->getNext();
                    }
            }
        }
        return numPass;
        
    
}



bool Railroad::setNumPassengers(int code, int passengers){
        //This function allows for setting the number of passengers in a specific station indicated by code.
    Station *temp = m_head;
    //stop when the list if finished
    while(temp != nullptr){
        //check if station code matches code
        if(temp->getStationCode() == code){
            //if match found, set the num of passengers
            temp->setNumPassengers(passengers);
            return true;
        }
        else{
            //if code do not match for that station, move to the next one
            temp = temp->getNext();
        }
    }
    //station code was never found
    cout<<"station code not found "<<endl;
    return false;
    
}

bool Railroad::removeStation(int aCode){
    /*This function removes the node aCode from the linked list. If there is any link (as in a route) 
    from another station to the removed one the link must be removed (reset). If removal is successful 
    the function returns true otherwise it returns false. If the node does not exist the function returns false.
    */
    Station *temp = m_head;
    //stop when the list if finished
    
    while(temp != nullptr){
        
        
        if(temp->getEast() != nullptr){
            //check for connection in east
            if (temp->getEast()->getStationCode() == aCode){
                temp->setEast(nullptr);
            }
            
        }
        
        else if (temp->getWest() != nullptr){
            //check for connection in west
            if (temp->getWest()->getStationCode() == aCode){
                temp->setWest(nullptr);
            }
        }
        else if (temp->getNorth() != nullptr){
            //check for connection in north
            if (temp->getNorth()->getStationCode() == aCode){
                temp->setNorth(nullptr);
            }
            
        }
        else if (temp->getSouth() != nullptr){
            //check for connection in south
            if (temp->getSouth() != nullptr){
                
                temp->setSouth(nullptr);
            }
            
        }
         if (temp->getStationCode() == aCode){
            
            if (temp->getPrevious() != nullptr){
                temp->getPrevious()->setNext(temp->getNext());
                temp->setNorth(nullptr);
                temp->setSouth(nullptr);
                temp->setEast(nullptr);
                temp->setWest(nullptr);
                m_numStations --;
                return true;
                delete temp;
            }
            else if (temp->getNext() == nullptr && temp->getNext() == nullptr){
                
                
                temp->setNorth(nullptr);
                temp->setSouth(nullptr);
                temp->setEast(nullptr);
                temp->setWest(nullptr);
                m_numStations --;
                return true;
                delete temp;
            }
                
        }
        else{
            temp = temp->getNext();
            
        }

    }
    cout<<"station does not exist "<<endl;
    return false;
}


void Railroad::clearAllRoutes(){
    //set nsew to 0

    Station *temp = m_head;
    if (temp == nullptr){
        cout<<"list is empty"<<endl;
    }
    else{
        while (temp != nullptr){
        if (temp->getEast() != nullptr){
            temp->setEast(nullptr);
        }
        if (temp->getWest() != nullptr){
            temp->setWest(nullptr);
        }
        if (temp->getNorth() != nullptr){
            temp->setNorth(nullptr);
        }
        if (temp->getSouth() != nullptr){
            temp->setSouth(nullptr);
        }
        temp = temp->getNext();
        }
    }
    
}





const Railroad & Railroad::operator=(const Railroad & rhs){
    if (this != &rhs) {
        clearNetwork();
        Station * temp = rhs.m_head;
        while (temp != nullptr) {
            extendAtTail(temp->getStationCode(), temp->getNumPassegers());
            temp = temp->getNext();
        }
        Station * orig = rhs.m_head;
        Station * newCopy = m_head;

        while (orig != nullptr) {

            //Station * north = temp1->getNorth();
            if (orig->getNorth() != nullptr) {
                Station * findTemp = m_head;
                while(findTemp != nullptr){
                    if(findTemp->getStationCode() == orig->getNorth()->getStationCode()){
                        Station* myNorth = findTemp;
                        newCopy->setNorth(myNorth);
                        findTemp = nullptr;
                    }
                    else{
                        findTemp = findTemp->getNext();
                    }
                }
            }
            //Station * east = temp1->getEast();
            if (orig->getEast() != nullptr) {
                Station * findTemp = m_head;
                while(findTemp != nullptr){
                    if(findTemp->getStationCode() == orig->getEast()->getStationCode()){
                        Station* myEast = findTemp;
                        newCopy->setEast(myEast);
                        findTemp = nullptr;
                    }
                    else{
                        findTemp = findTemp->getNext();
                    }
                }
            }
            //Station * south = temp1->getSouth();
            if (orig->getSouth() != nullptr) {
                Station * findTemp = m_head;
                while(findTemp != nullptr){
                    if(findTemp->getStationCode() == orig->getSouth()->getStationCode()){
                        Station* mySouth = findTemp;
                        newCopy->setSouth(mySouth);
                        findTemp = nullptr;
                    }
                    else{
                        findTemp = findTemp->getNext();
                    }
                }
                
            }
            //Station * west = temp1->getWest();
            if (orig->getWest() != nullptr) {
                Station * findTemp = m_head;
                while(findTemp != nullptr){
                    if(findTemp->getStationCode() == orig->getWest()->getStationCode()){
                        Station* myWest = findTemp;
                        newCopy->setWest(myWest);
                        findTemp = nullptr;
                    }
                    else{
                        findTemp = findTemp->getNext();
                    }
                }
            }
            cout<<"Origial mem :"<<&orig<<" number "<<orig->getStationCode()<<endl;
            cout<<"copy mem :"<<&newCopy<<" number "<<newCopy->getStationCode()<<endl;
            orig = orig->getNext();
            newCopy = newCopy->getNext();
        }
    }
    return *this;
}

 Railroad::Railroad(const Railroad & rhs){
    m_head = nullptr;
    m_tail = nullptr;
    m_numStations = 0;
        clearNetwork();
        Station * temp = rhs.m_head;
        while (temp != nullptr) {
            extendAtTail(temp->getStationCode(), temp->getNumPassegers());
            temp = temp->getNext();
        }
        Station * orig = rhs.m_head;
        Station * newCopy = m_head;

        while (orig != nullptr) {

            //Station * north = temp1->getNorth();
            if (orig->getNorth() != nullptr) {
                Station * findTemp = m_head;
                while(findTemp != nullptr){
                    if(findTemp->getStationCode() == orig->getNorth()->getStationCode()){
                        Station* myNorth = findTemp;
                        newCopy->setNorth(myNorth);
                        findTemp = nullptr;
                    }
                    else{
                        findTemp = findTemp->getNext();
                    }
                }
            }
            //Station * east = temp1->getEast();
            if (orig->getEast() != nullptr) {
                Station * findTemp = m_head;
                while(findTemp != nullptr){
                    if(findTemp->getStationCode() == orig->getEast()->getStationCode()){
                        Station* myEast = findTemp;
                        newCopy->setEast(myEast);
                        findTemp = nullptr;
                    }
                    else{
                        findTemp = findTemp->getNext();
                    }
                }
            }
            //Station * south = temp1->getSouth();
            if (orig->getSouth() != nullptr) {
                Station * findTemp = m_head;
                while(findTemp != nullptr){
                    if(findTemp->getStationCode() == orig->getSouth()->getStationCode()){
                        Station* mySouth = findTemp;
                        newCopy->setSouth(mySouth);
                        findTemp = nullptr;
                    }
                    else{
                        findTemp = findTemp->getNext();
                    }
                }
                
            }
            //Station * west = temp1->getWest();
            if (orig->getWest() != nullptr) {
                Station * findTemp = m_head;
                while(findTemp != nullptr){
                    if(findTemp->getStationCode() == orig->getWest()->getStationCode()){
                        Station* myWest = findTemp;
                        newCopy->setWest(myWest);
                        findTemp = nullptr;
                    }
                    else{
                        findTemp = findTemp->getNext();
                    }
                }
            }
            cout<<"Origial mem :"<<&orig<<" number "<<orig->getStationCode()<<endl;
            cout<<"copy mem :"<<&newCopy<<" number "<<newCopy->getStationCode()<<endl;
            orig = orig->getNext();
            newCopy = newCopy->getNext();
        }
    
    
}
//UMBC - CSEE - CMSC 341 - Fall 2022 - Proj1
//#include "railroad.h"

class Tester{ // Tester class to implement test functions
    public:

    /**************************************
    * Test function declarations go here! *
    **************************************/
   bool testExtendAtHead(int num);
   bool testExtendAtTail(int num);
   bool testRemoveStationNormal();
   bool testRemoveStationError();
   bool testRemoveStationNormalRoute();
   bool testAssignmentNormal();
   bool testAssignmentEdge(int num);


};

int main(){
   Railroad aNetwork;
    for (int i=1;i<10;i++)
        aNetwork.extendAtTail(i,i*2);
    cout << "Create a route [(2,NORTH),(5,SOUTH),(8,NONE)]\n\n";
    list<pair<int,DIRECTION> > aRoute;
    aRoute.push_back(pair<int,DIRECTION>(2,NORTH));
    aRoute.push_back(pair<int,DIRECTION>(5,SOUTH));
    aRoute.push_back(pair<int,DIRECTION>(8,NONE));
    aNetwork.makeRoute(aRoute);

    
    cout << "Total travellers: " << aNetwork.travel(aRoute) << endl;
    cout << "\nDump of the list:\n\n";
    aNetwork.dump();
    cout << "\n\nRemove node 5.\n\n";
    aNetwork.removeStation(5);
    cout << "Removing node 5 invalidates the route passing through 5.\n\n";
    cout << "Total travellers: " << aNetwork.travel(aRoute) << endl;
    cout << "\nDump of the list:\n\n";
    aNetwork.dump();

    //Tests
    Tester tester;

    //testing extendAtHead()
    //Normal case
    cout<< "\tTesting normal case for extendAtHead();"<<endl;
    if (tester.testExtendAtHead(300) == true){
        cout<<"\nNormal case of extendAtHead works"<<endl;
    }
    else{
        cout<<"\nNormal case of extendAtHead does not work"<<endl;
    }
    //error case
    cout<<"\t Testing error case for extendAtHead();"<<endl;
    if (tester.testExtendAtHead(0) == false){
            cout<<"\nerror case of extendAtHead works"<<endl;
    }
    else{
        cout<<"\nerror case of extendAtHead does not work"<<endl;
    }

    //testing extendAtTail() 
    //normal case
    cout<< "\ttesting normal case for extendAtTail();"<<endl;
    if (tester.testExtendAtHead(300) == true){
        cout<<"\nNormal case of extendAtTail() works"<<endl;
    }
    else{
        cout<<"\nNormal case of extendAtTail() does not work"<<endl;
    }
    //error case
    cout<<"\ttesting error case for extendAtTail();"<<endl;
    if (tester.testExtendAtHead(0) == false){
            cout<<"\nerror case of extendAtTail() works"<<endl;
    }
    else{
        cout<<"\nerror case of extendAtTail() does not work"<<endl;
    }

    //testing removeStation
    //normal case
    cout<<"\t testing normal case of remove station"<<endl;
    if (tester.testRemoveStationNormal() == true){
        cout<<"\n normal case of remove station passed"<<endl;
    }
    else{
        cout<<"\n normal case of remove station failed"<<endl;
    }

    //error case
    cout<<"\t testing error case of remove station"<<endl;
    if (tester.testRemoveStationError() == false){
        cout<<"\n error case of remove station passed"<<endl;
    }
    else{
        cout<<"\n error case of remove station failed"<<endl;
    }

    //normal case with route 
    cout<<"\t testing normal case of remove station with a route"<<endl;
    if (tester.testRemoveStationNormalRoute() == true){
        cout<<"\n normal case with route of remove station passed"<<endl;
    }
    else{
        cout<<"\n normal case with routeof remove station failed"<<endl;
    }


    //normal case for =
    cout<<"\t Testing assignment operator for a normal case"<<endl;
    if (tester.testAssignmentNormal() == true){
        cout<<"\n normal case of assignemnt passed"<<endl;
    }
    else{
        cout<<"\n normal case of assignemnt failed"<<endl;
    }

    //edge case for =
    cout<<"\t Testing assignment operator for a edge case"<<endl;
    if (tester.testAssignmentEdge(1) == true){
        cout<<"\n edge case of assignemnt passed( 1 station)"<<endl;
        if(tester.testAssignmentEdge(2) == true){
            cout<<"\n edge case of assignemnt passed( 2 stations)"<<endl;
        }
    }
    else{
        cout<<"\n edge case of assignemnt failed"<<endl;
    }


    Railroad aPan;
    for (int i=1;i<10;i++){
        aPan.extendAtTail(i,i*2);
    }
    Railroad alil(aPan);
    cout<<"Copy Made"<<endl;
    

    
    
    

    


    return 0;
    
}

bool Tester::testAssignmentEdge(int num){
    Railroad aNetwork;
    for (int i = 1; i < num; i++) {
        aNetwork.extendAtTail(i,i*2);
    }
    Railroad aCopy;
    aCopy = aNetwork;
    Station *temp1 = aNetwork.m_head;
    Station *temp2 = aCopy.m_head;

    while (temp1 != nullptr && temp2 != nullptr) {
        if (temp1 == temp2) {
            return false;
        }
        temp1 = temp1->getNext();
        temp2 = temp2->getNext();
    }
    return true;


}

bool Tester::testAssignmentNormal(){
    Railroad aNetwork;
    for (int i = 1; i < 20; i++) {
        aNetwork.extendAtTail(i,i*2);
    }
    Railroad aCopy;
    aCopy = aNetwork;
    Station *temp1 = aNetwork.m_head;
    Station *temp2 = aCopy.m_head;

    while (temp1 != nullptr && temp2 != nullptr) {
        if (temp1 == temp2) {
            return false;
        }
        temp1 = temp1->getNext();
        temp2 = temp2->getNext();
    }
    return true;

}

bool Tester::testRemoveStationNormalRoute(){
    Railroad aNetwork;
    for (int i=1;i<10;i++){
        aNetwork.extendAtHead(i,i*2);
        
    }
    list<pair<int,DIRECTION > > aNew;
    aNew.push_back(pair<int,DIRECTION>(2,NORTH));
    aNew.push_back(pair<int,DIRECTION>(3,EAST));
    aNew.push_back(pair<int,DIRECTION>(5,SOUTH));
    aNew.push_back(pair<int,DIRECTION>(8,NONE));
    cout<<'l'<<endl;
    aNetwork.makeRoute(aNew);
    
    if (aNetwork.removeStation(8) == true){
        cout<<"It passed"<<endl;
        return true;
    }
    else{
        return false;
    }
}


//testing removeStation for error case
bool Tester::testRemoveStationError(){
    Railroad aNetwork;
    for (int i=1;i<10;i++){
        aNetwork.extendAtHead(i,i*2);
        
    } 
    if (aNetwork.removeStation(250) == false){
        return false;
    }
    else{
        return true;
    }
}

//testing removStation for normal case
bool Tester::testRemoveStationNormal(){
    Railroad aNetwork;
    for (int i=1;i<5;i++){
        aNetwork.extendAtHead(i,i*2);
        
    } 
    for(int i = 1; i < 5; i++){
        if(aNetwork.removeStation(i) == false){
        return false;
        }
    
    }
    
    return true;
    

}


//normal and error case for extendAtTail
bool Tester::testExtendAtTail(int num){
    bool works = false;
    Railroad network1;
    for (int i=1;i<num;i++){
        if (network1.extendAtTail(i,i*2) == true){
            works = true;
        }
        else{
            return false;
        }
    }
    if (works == true){
        return true;
    }
    else{
        return false;
    }
}

//normal and error case for extendAtHead
bool Tester::testExtendAtHead(int num){
    bool works = false;
    Railroad network1;
    for (int i=1;i<num;i++){
        if (network1.extendAtHead(i,i*2) == true){
            works = true;
        }
        else{
            return false;
        }
    }
    if (works == true){
        return true;
    }
    else{
        return false;
    }
}

//UMBC - CSEE - CMSC 341 - Fall 2022 - Proj1
#include "railroad.h"
//Title : proj1
//Date :  10/04/2022
//Name : Waleed Iqbal
//Description: This is the implemented railroad.cpp file which holds all the functions for use
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

    if (m_head == nullptr){
        delete m_head;
        delete m_tail;
        m_head = nullptr;
        m_tail = nullptr;
        m_numStations = 0;
    }
    else{
        //if more than one station
        Station * temp = nullptr;
        
        while(m_head != nullptr){
            //set erveything to null
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
        //check if station code is larger than 1
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
        
    }
    return false;


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
                        //return false if the direction none was used before reaching the end of the list object pairs
                        return false;
                    }
                    //none
                
                }
                else{
                    //if direction was attempted to overite
                    return false;
                }
            
            }
        
        }
    
    }
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
        //check to see if the None direction is not used more than once
        if (checkForNone(route) > 1){
            return -1;
        }
        
        for (list<pair<int,DIRECTION > >::iterator it = route.begin(); it != route.end(); ++it){
            list <pair<int,DIRECTION > >:: iterator pair3;
            list <pair<int,DIRECTION > >:: iterator pair4;
            //curr elemt of the list
            pair3 = it;
            //to access next element after the curr
            pair4 = ++pair3;
            //to check smae station is not pointint to itself
            if (it->first == pair4->first){
                return -1;
            }
            

        }
        for (list<pair<int,DIRECTION > >::iterator it = route.begin(); it != route.end(); ++it){
            list <pair<int,DIRECTION > >:: iterator pair1;
            list <pair<int,DIRECTION > >:: iterator pair2;
            
            //original object we are currently on
            pair1 = it;
            //to access to next element of list object
            pair2 = ++pair1;
            Station *temp3 = m_head;
            if (temp3 == nullptr){
                return -1;
            }
            //check if station code is not less than 1
            else if (temp3->getStationCode() < 1){
                return -1;
            }

            while(temp3 != nullptr){
                    if (temp3->getStationCode() == it->first){
                        //adding number of passangers per station
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
    
    return false;
    
}


bool Railroad::checkDirection(int acode) {
    //checks if there is a direction pointing to code that is being removed

    //check if station exists
    Station * temp = matchStation(acode);
    
    if ( temp == nullptr){
        return false;
    }
        Station * temp1 = m_head;
        while(temp1 != nullptr){
            if (temp1->getSouth() == temp) {
                temp1->setSouth(nullptr);
                return true;
            }
            else if (temp1->getNorth() == temp) {
                temp1->setNorth(nullptr);
                return true;
            }
            else if (temp1->getEast() == temp) {
                temp1->setEast(nullptr);
                return true;
            }
            else if (temp1->getWest() == temp) {
                temp1->setWest(nullptr);
                return true;
            }
            temp1=temp1->getNext();
        }
        
    return true;
}

Station * Railroad::matchStation(int code){
    //checks to see if station exists in linked list
    Station *temp = m_head;
    while (temp != nullptr) {
        if (temp->getStationCode() == code) {
            return temp;
        }
        else {
            temp = temp->getNext();
        }
    }
    return temp;
}

bool Railroad::removeStation(int aCode){

    Station *temp = matchStation(aCode);
    //station does not exist
    if (temp == nullptr) {
        return false;
    }
    else {        
        //remove station
        if (temp->getPrevious() != nullptr) {
            checkDirection(aCode);
            temp->getPrevious()->setNext(temp->getNext());
            
        }
        if (temp->getNext() != nullptr) {
            checkDirection(aCode);
            temp->getNext()->setPrevious(temp->getPrevious());
            
        }
        if (temp == m_head) {
            checkDirection(aCode);
            m_head = temp->getNext();
            
        }
        if (temp == m_tail) {
            checkDirection(aCode);
            m_tail = temp->getPrevious();
        }
            
    }

    temp->setNorth(nullptr);
    temp->setEast(nullptr);
    temp->setWest(nullptr);
    temp->setSouth(nullptr);
    //delete once previous and next have been linked
    delete temp;
    m_numStations--;
    return true;    
}

void Railroad::clearAllRoutes(){
    //set eveyrthing to 0


    Station *temp = m_head;
    //check for when list is empty
    
    if (temp != nullptr){
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
    //assignment operator makes a deep copy
    if (this != &rhs) {
        clearNetwork();
        Station * temp = rhs.m_head;
        while (temp != nullptr) {
            //creating linked list copy of rhs
            extendAtTail(temp->getStationCode(), temp->getNumPassegers());
            temp = temp->getNext();
        }
        Station * orig = rhs.m_head;
        Station * newCopy = m_head;

        while (orig != nullptr) {

            // north 
            //check if there is a north direction
            if (orig->getNorth() != nullptr) {
                Station * findTemp = m_head;
                while(findTemp != nullptr){
                    if(findTemp->getStationCode() == orig->getNorth()->getStationCode()){
                        Station* myNorth = findTemp;
                        //assign new copy's direction
                        newCopy->setNorth(myNorth);
                        findTemp = nullptr;
                    }
                    else{
                        findTemp = findTemp->getNext();
                    }
                }
            }
            
            //check if there is a east direction

            if (orig->getEast() != nullptr) {
                Station * findTemp = m_head;
                while(findTemp != nullptr){
                    if(findTemp->getStationCode() == orig->getEast()->getStationCode()){
                        Station* myEast = findTemp;
                        //assign new copy's direction
                        newCopy->setEast(myEast);
                        findTemp = nullptr;
                    }
                    else{
                        findTemp = findTemp->getNext();
                    }
                }
            }
            //west
            if (orig->getWest() != nullptr) {
                Station * findTemp = m_head;
                while(findTemp != nullptr){
                    if(findTemp->getStationCode() == orig->getWest()->getStationCode()){
                        Station* myWest = findTemp;
                        //assign new copy's direction
                        newCopy->setWest(myWest);
                        findTemp = nullptr;
                    }
                    else{
                        findTemp = findTemp->getNext();
                    }
                }
                
            }
            //south
            if (orig->getSouth() != nullptr) {
                Station * findTemp = m_head;
                while(findTemp != nullptr){
                    if(findTemp->getStationCode() == orig->getSouth()->getStationCode()){
                        Station* mySouth = findTemp;
                        //assign new copy's direction
                        newCopy->setSouth(mySouth);
                        findTemp = nullptr;
                    }
                    else{
                        findTemp = findTemp->getNext();
                    }
                }
            }
            
            orig = orig->getNext();
            newCopy = newCopy->getNext();
        }
    }
    return *this;
}

Railroad::Railroad(const Railroad & rhs){
    //The copy constructor creates a deep copy of rhs.
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

           //north

            if (orig->getNorth() != nullptr) {
                Station * findTemp = m_head;
                while(findTemp != nullptr){
                    if(findTemp->getStationCode() == orig->getNorth()->getStationCode()){
                        Station* myNorth = findTemp;
                        //assign new copy's direction
                        newCopy->setNorth(myNorth);
                        findTemp = nullptr;
                    }
                    else{
                        findTemp = findTemp->getNext();
                    }
                }
            }
            //east
            if (orig->getEast() != nullptr) {
                Station * findTemp = m_head;
                while(findTemp != nullptr){
                    if(findTemp->getStationCode() == orig->getEast()->getStationCode()){
                        Station* myEast = findTemp;
                        //assign new copy's direction
                        newCopy->setEast(myEast);
                        findTemp = nullptr;
                    }
                    else{
                        findTemp = findTemp->getNext();
                    }
                }
            }
            //west
            if (orig->getWest() != nullptr) {
                Station * findTemp = m_head;
                while(findTemp != nullptr){
                    if(findTemp->getStationCode() == orig->getWest()->getStationCode()){
                        Station* myWest = findTemp;
                        //assign new copy's direction
                        newCopy->setWest(myWest);
                        findTemp = nullptr;
                    }
                    else{
                        findTemp = findTemp->getNext();
                    }
                }
                
            }
            //south
            if (orig->getSouth() != nullptr) {
                Station * findTemp = m_head;
                while(findTemp != nullptr){
                    if(findTemp->getStationCode() == orig->getSouth()->getStationCode()){
                        Station* mySouth = findTemp;
                        //assign new copy's direction
                        newCopy->setSouth(mySouth);
                        findTemp = nullptr;
                    }
                    else{
                        findTemp = findTemp->getNext();
                    }
                }
            }
            
            orig = orig->getNext();
            newCopy = newCopy->getNext();
        }   
}
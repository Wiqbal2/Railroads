//UMBC - CSEE - CMSC 341 - Fall 2022 - Proj1
#include "railroad.h"
//Title : proj1
//Date :  10/04/2022
//Name : Waleed Iqbal
//Description: This is test file which tests all the functions from railroad.cpp

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
   bool testCopyConstruct(int num);
   bool testCopyConstructEdge(int num);
   bool testMakeRouteError1() ;
   bool testMakeRouteError2() ;
   bool testMakeRouteNormal();
   bool testTravelNormal();
   bool testTravelError1();
   bool testTravelError2();






};

int main(){
   Railroad aNetwork;
    for (int i=1;i<10;i++)
        aNetwork.extendAtTail(i,i*2);
    cout << "Create a route [(2,NORTH),(5,SOUTH),(8,NONE)]\n\n";
    list<pair<int,DIRECTION>> aRoute;
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
    
    //copy constructor normal
    cout<<"\t Testing Copy constructor for a normal case"<<endl;
    if (tester.testCopyConstruct(10) == true){
        cout<<"\n normal case for copy Constructor passed"<<endl;
    }
    else{
        cout<<"\n normal case for copy Constructor failed"<<endl;
    }

    //copy constructor edge cases 1 station and 0 stations
    cout<<"\t Testing Copy constructor for a edge case (1 station)"<<endl;
    if (tester.testCopyConstruct(1) == true){
        cout<<"\n edge case for copy Constructor passed"<<endl;
        cout<<"\t Testing Copy constructor for a edge case (0 station)"<<endl;

        if(tester.testCopyConstructEdge(0) == false){
            cout<<"\n edge case for copy Constructor passed"<<endl;
        }
    }
    else{
        cout<<"\n normal case for copy Constructor failed"<<endl;
    }

    //make route error case 1
    cout<<"\t Testing makeroute() for an error case ( if first station  in route does not exist in linked list)"<<endl;
    if (tester.testMakeRouteError1() == false){
        cout<<"makeroute for error case passed"<<endl;
    }
    else{
        cout<<"makeroute for error case failed"<<endl;
    }
    //make route error case 2
    cout<<"\t Testing makeroute() for an error case ( list tries to overwrite an existing link)"<<endl;
    if (tester.testMakeRouteError2() == false){
        cout<<"makeroute for error case passed"<<endl;
    }
    else{
        cout<<"makeroute for error case failed"<<endl;
    }

    //make route error case 2
    cout<<"\t Testing makeroute() for a normal case"<<endl;
    if (tester.testMakeRouteNormal() == true){
        cout<<"makeroute for normal case passed"<<endl;
    }
    else{
        cout<<"makeroute for normal case failed"<<endl;
    }
    //travel for a normal
    cout<<"\t Testing travel()for a normal case"<<endl;
    if (tester.testTravelNormal() == true){
        cout<<"travel for normal case passed"<<endl;
    }
    else{
        cout<<"travel for normal case failed"<<endl;
    }

    cout<<"\t Testing travel()for an error case (pointing to the same station back to back)"<<endl;
    if (tester.testTravelError1() == false){
        cout<<"travel for an error case passed"<<endl;
    }
    else{
        cout<<"travel for an error case failed"<<endl;
    }

    cout<<"\t Testing travel()for an error case (repeated none)"<<endl;
    if (tester.testTravelError2() == false){
        cout<<"travel for an error case passed"<<endl;
    }
    else{
        cout<<"travel for an error case failed"<<endl;
    }










    

    
    
    

    


    return 0;
    
}

bool Tester::testTravelError2(){
    Railroad aNew;
    for (int i=1;i<10;i++){
        aNew.extendAtTail(i,i*2);
    }
    list<pair<int,DIRECTION>> newRoute;
    newRoute.push_back(pair<int,DIRECTION>(2,NORTH));
    newRoute.push_back(pair<int,DIRECTION>(3,SOUTH));

    newRoute.push_back(pair<int,DIRECTION>(4,NONE));
    newRoute.push_back(pair<int,DIRECTION>(8,NONE));
    aNew.makeRoute(newRoute);
    if (aNew.travel(newRoute) != -1){
        return true;
    }
    else {
        return false;
    }
}

//Testing travel()for an error case (pointing to the same station back to back)
bool Tester::testTravelError1(){
    Railroad aNew;
    for (int i=1;i<10;i++){
        aNew.extendAtTail(i,i*2);
    }
    list<pair<int,DIRECTION>> newRoute;
    newRoute.push_back(pair<int,DIRECTION>(2,NORTH));
    //setting to same station
    newRoute.push_back(pair<int,DIRECTION>(2,SOUTH));
    newRoute.push_back(pair<int,DIRECTION>(8,NONE));
    aNew.makeRoute(newRoute);
    if (aNew.travel(newRoute) != -1){
        return true;
    }
    else {
        return false;
    }

}


//test travel() for a normal case
bool Tester::testTravelNormal(){
    Railroad aNew;
    for (int i=1;i<10;i++){
        aNew.extendAtTail(i,i*2);
    }
    list<pair<int,DIRECTION>> newRoute;
    newRoute.push_back(pair<int,DIRECTION>(2,NORTH));
    newRoute.push_back(pair<int,DIRECTION>(5,SOUTH));
    newRoute.push_back(pair<int,DIRECTION>(8,NONE));
    aNew.makeRoute(newRoute);
    if (aNew.travel(newRoute) != -1){
        return true;
    }
    else {
        return false;
    }

}

//test makeRoute for a normal case
bool Tester::testMakeRouteNormal(){

    Railroad aNew;
    for (int i=1;i<10;i++){
        aNew.extendAtTail(i,i*2);
    }
    list<pair<int,DIRECTION>> newRoute;
    newRoute.push_back(pair<int,DIRECTION>(2,NORTH));
    newRoute.push_back(pair<int,DIRECTION>(5,SOUTH));
    newRoute.push_back(pair<int,DIRECTION>(8,NONE));

    if (aNew.makeRoute(newRoute) == true){
        return true;
    }
    else{
        return false;
    }
    
    
}
//test makeroute for second error case
bool Tester::testMakeRouteError2(){
    Railroad aNew;
    for (int i=1;i<20;i++){
        aNew.extendAtTail(i,i*2);
    }
    list<pair<int,DIRECTION>> aList;
    aList.push_back(pair<int,DIRECTION>(12,EAST));
    aList.push_back(pair<int,DIRECTION>(14,EAST));
    aList.push_back(pair<int,DIRECTION>(12,EAST));
    
    if (aNew.makeRoute(aList) == false) {
        return false;
    }
    else {
        return true;
    }
}


//test makeroute for first error case
bool Tester::testMakeRouteError1() {
    Railroad aNew;
    for (int i=1;i<10;i++){
        aNew.extendAtTail(i,i*2);
    }
    list<pair<int,DIRECTION>> aList;
    aList.push_back(pair<int,DIRECTION>(12,EAST));
    
    if (aNew.makeRoute(aList) == false) {
        return false;
    }
    else {
        return true;
    }
}


//test copy constructor for edge case
bool Tester::testCopyConstructEdge(int num){
    Railroad aNetwork;
    aNetwork.extendAtTail(num,num);
    Railroad aCopy(aNetwork);
    
    Station *temp1 = aNetwork.m_head;
    Station *temp2 = aCopy.m_head;
    if (temp1 == nullptr && temp2 == nullptr){
        return false;
    }

    while (temp1 != nullptr && temp2 != nullptr) {
        if (temp1 == temp2) {
            return false;
        }
        temp1 = temp1->getNext();
        temp2 = temp2->getNext();
    }
    return true;
}

//testing copy constructor for normal case
bool Tester::testCopyConstruct(int num){
    Railroad aNetwork;
    for (int i = 1; i < num; i++) {
        aNetwork.extendAtTail(i,i*2);
    }
    Railroad aCopy(aNetwork);
    
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

//testing assignemnt oprator for edge cases
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
//testing assignemnt operator for normal case
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
//test if remove route works when the station has links to it
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
    
    aNetwork.makeRoute(aNew);
    
    if (aNetwork.removeStation(8) == true){
        
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


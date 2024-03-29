#include <iostream>
#include <string.h>
using namespace std;

class Airplane{
private:
    char ID[12];
    char *company_name;
    char company_airport[20];
    int state;
    int flight_hours;
    void copy(const Airplane & other){
        strcpy(this->ID,other.ID);
        strcpy(this->company_airport,other.company_airport);
        this->state=other.state;
        this->flight_hours=other.flight_hours;
        this->company_name=new char [strlen(other.company_name)+1];
        strcpy(this->company_name,other.company_name);
    }
public:
    Airplane(char *ID="", char *company_name="",char *company_airport="",int flight_hours=0,int state=0){
        strcpy(this->ID,ID);
        this->company_name=new char [strlen(company_name)+1];
        strcpy(this->company_name,company_name);
        strcpy(this->company_airport,company_airport);
        this->state=state;
        this->flight_hours=flight_hours;
    }
    Airplane(const Airplane & other){
        copy(other);
    }
    ~Airplane(){
        delete [] company_name;
    }
    Airplane &operator=(const Airplane & other){
        if(this!=&other) {
            delete[]company_name;
            copy(other);
        }
        return *this;
    }
    void print(){
        cout << "ID: " << ID << " - ";
        if(state == 0){
            cout << "NOT_";
        }if(state == 1){
            cout << "REPAIRING ";
        }else{
            cout <<"WORKING ";
        }
        cout << company_name << ", " << flight_hours << ", " << company_airport <<endl;
    }
    char *getCompanyName() const {
        return company_name;
    }

    const char *getCompanyAirport() const {
        return company_airport;
    }

    int getState() const {
        return state;
    }

    int getFlightHours() const {
        return flight_hours;
    }
    void setState(int state) {
        Airplane::state = state;
    }
};

class AirportService{
private:
    char airport_name[20];
    Airplane *airplanes;
    int numberOfAirplanes;
    void copy(const AirportService & other){
        strcpy(this->airport_name, other.airport_name);
        this->numberOfAirplanes = other.numberOfAirplanes;
        this->airplanes = new Airplane [this->numberOfAirplanes];
        for (int i = 0; i < this->numberOfAirplanes; ++i) {
            this->airplanes[i] = other.airplanes[i];
        }
    }
public:
    AirportService(char *airport_name="",Airplane *airplanes=0,int numberOfAirplanes=0){
        strcpy(this->airport_name,airport_name);
        this->numberOfAirplanes=numberOfAirplanes;
        this->airplanes=new Airplane[this->numberOfAirplanes];
        for(int i=0;i>numberOfAirplanes;i++){
            this->airplanes[i]=airplanes[i];
        }
    }
    AirportService(const AirportService & other){
        copy(other);
    }
    AirportService & operator = (const AirportService & other){
        if(this == &other){
            return *this;
        }
        delete[]airplanes;
        copy(other);
        return *this;
    }

    void addAirplane(Airplane plane){
        if (plane.getState()==0){
            int flag = -1;
            plane.setState(1);
            for(int i=0;i<numberOfAirplanes;i++){
                if(strcmp(airplanes[i].getCompanyName(),plane.getCompanyName())==0){
                    flag=i;
                    break;
                }
            }
            if(flag==-1){
                Airplane *tmp=new Airplane[numberOfAirplanes+1];
                for(int i=0;i<numberOfAirplanes;i++){
                    tmp[i]=airplanes[i];
                }
                delete[]airplanes;
                tmp[numberOfAirplanes]=plane;
                numberOfAirplanes++;
                airplanes=tmp;
            }
            else{
                Airplane *tmp=new Airplane[numberOfAirplanes+1];
                for(int i=0, j=0;i<numberOfAirplanes;i++){
                    if(i!=flag) {
                        tmp[j] = airplanes[i];
                        j++;
                    }
                    else{
                        if(plane.getFlightHours()>airplanes[i].getFlightHours()){
                            tmp[j]=plane;
                            j++;
                        }
                    }
                }
                delete[]airplanes;
                airplanes=tmp;
            }
        }
    }

    Airplane serviceOldestAirplane(){
        int oldestAirplanePosition,maxHours=0;
        for(int i=0;i<numberOfAirplanes;i++){
            if(maxHours<airplanes[i].getFlightHours()){
                maxHours=airplanes[i].getFlightHours();
                oldestAirplanePosition=i;
            }
            if(maxHours==airplanes[i].getFlightHours()){
                if(strcmp(this->airport_name,airplanes[i].getCompanyAirport())==0){
                    oldestAirplanePosition=i;
                }
            }
        }
        airplanes[oldestAirplanePosition].setState(2);
        Airplane plane = airplanes[oldestAirplanePosition];
        Airplane *tmp=new Airplane[numberOfAirplanes-1];
        for(int i=0,j=0;i<numberOfAirplanes;i++){
            if(i!=oldestAirplanePosition) {
                tmp[j] = airplanes[i];
                j++;
            }

        }
        delete[]airplanes;
        airplanes=tmp;
        numberOfAirplanes--;
        return plane;
    }
    void print(){
        cout<<airport_name<<endl;
        for(int i=0;i<numberOfAirplanes;i++){
            airplanes[i].print();
        }
    }
};

int main() {
    int testCase;
    cin >> testCase;
    char ID[12];
    char company_name[20];
    char company_airport[20];
    int flight_hours;
    int state;
    if (testCase == 1) {
        cout << "TESTING CONSTRUCTOR FOR AIRPLANE" << endl;
        Airplane a;
        cout << "TEST FOR DEFAULT CONSTRUCTOR PASSED" << endl;
        Airplane a1("ZHN-96-TY", "FINKI-Airline", "TMF", 13);
        cout << "TEST FOR CONSTRUCTOR WITH 3 ARGUMENTS PASSED" << endl;
        Airplane a2("ZHN-96-TA", "FINKI1-Airline", "TMF", 13, 0);
        cout << "TEST FOR CONSTRUCTOR WITH 4 ARGUMENTS PASSED" << endl;
    } else if (testCase == 2) {
        cout << "TESTING COPY-CONSTRUCTOR AND OPERATOR = (ASSIGNMENT) FOR AIRPLANE" << endl;
        Airplane p("ZHN-96-TA", "FINKI-Airline", "TMF", 13, 0);
        Airplane p1(p);
        cout << "TEST FOR COPY CONSTRUCTOR PASSED" << endl;
        Airplane p2;
        p2 = p;
        cout << "TEST FOR OPERATOR = (ASSIGNMENT) PASSED" << endl;
    } else if (testCase == 3) {
        cout << "TESTING PRINT() FOR AIRPLANE" << endl;
        cin>>ID>>company_name>>company_airport>>flight_hours>>state;
        Airplane p(ID, company_name, company_airport, flight_hours, state);
        p.print();
    } else if (testCase == 4) {
        cout << "TESTING CONSTRUCTOR FOR AIRPORTSERVICE" << endl;
        AirportService as("FINKI");
        cout << "TEST PASSED" << endl;
        //cisto



    } else if (testCase == 5)
    {
        cout << "TESTING ADD() AND PRINT() FOR AIRPORTSERVICE" << endl;
        AirportService as("FINKI");
        int n;
        cin>>n;
        for(int i=0; i<n; i++){
            cin>>ID>>company_name>>company_airport>>flight_hours>>state;
            Airplane p(ID, company_name, company_airport, flight_hours, state);
            as.addAirplane(p);
        }
        as.print();
    } else if (testCase == 6) {
        cout << "TESTING serviceOldestAirplane() AND PRINT() FOR AIRPORTSERVICE" << endl;
        AirportService as("FINKI");
        int n;
        cin>>n;
        for(int i=0; i<n; i++){
            cin>>ID>>company_name>>company_airport>>flight_hours>>state;
            Airplane p(ID, company_name, company_airport, flight_hours, state);
            as.addAirplane(p);
        }
        Airplane p = as.serviceOldestAirplane();
        cout<<"Removed plane:"<<endl;
        p.print();
        cout<<"-----------------"<<endl;
        as.print();
    }  else if (testCase == 7) {
        cout << "TESTING COPY CONSTRUCTOR AND OPERATOR = FOR AIRPORTSERVICE" << endl;
        AirportService as("FINKI");
        Airplane a1("ZHN-96-TY", "FINKI-Airline", "TMF", 13);
        as.addAirplane(a1);

        AirportService s1 = as; //copy constructor
        AirportService s2;
        s2 = s1; //operator =
        s1.print();
        s2.print();
    }
    return 0;
}

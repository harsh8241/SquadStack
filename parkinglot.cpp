#include<bits/stdc++.h>
using namespace std;
/*The Idea here was to define our parking lot which contains slots where we would park our car*/
//our car has features like registration no, age of its driver, and the lot alloted to it,which differentiate it from other cars
class Car{
    private:
        string registrationNumber;
        int driverAge;
        int lotAlloted;
    public:
        //Non Parametrized constructor
        Car(){
            this->registrationNumber = "NONE";
            this->driverAge = -1;
            this->lotAlloted = -1;
        }
        //Parametrized constructor
        Car(string registrationNumber,int driverAge,int lotAlloted){
            this->registrationNumber = registrationNumber;
            this->driverAge = driverAge;
            this->lotAlloted = lotAlloted;
        }
        //getters and stters
        string getCarNo(){
            return registrationNumber;
        }
        void setRegNo(string registrationNumber){
            this->registrationNumber=registrationNumber;
        }

        string getRegNo(){
            return registrationNumber;
        }

        void setdriverAge(int driverAge){
            this->driverAge=driverAge;
        }
        
        int getdriverAge(){
            return driverAge;
        }

        void setLotAlloted(int lotAlloted){
            this->lotAlloted=lotAlloted;
        }

        int getLotAlloted(){
            return lotAlloted;
        }
};
//we have a slot which contaions a car
class Slot{
        Car c;
        bool isOccupied;
    public:
        Slot(){
            isOccupied = false;
        }
        //occupy the slot
        void occupy(string carno,int age,int slotno){
            c.setRegNo(carno);
            c.setdriverAge(age);
            c.setLotAlloted(slotno);
            isOccupied = true;
        }
        //free the slot
        void unoccupy(){
            isOccupied=false;
            c.setRegNo("");
            c.setdriverAge(-1);
            c.setLotAlloted(-1);
        }
        //getters
        string getCarParkedNo(){
            return c.getCarNo();
        }
        int getCarAge(){
            return c.getdriverAge();
        }
};
//multiple slots would make up our parking lot
class parking_lot{

    private:
        //continious n slots where wecan park our cars.
        vector<Slot> slots;
        //min priority queue which stores the smallest availabe free space on top
        priority_queue<int,vector<int>,greater<int> >  freeslot;
        //maps the age of the driver to the cars driven by the same aged driver 
        unordered_map<int,set<int>> carForAge;
        //maps the registration of the car to the slot at which it is parked
        unordered_map<string,int> slotOfcarRegNo;

    public:
        //parametrized constructor
        parking_lot(int n){
            slots.resize(n+1);
            for(int i=1;i<=n;i++){
                freeslot.push(i);
            }
        }
        //function to park the car
        void park(string carno, int age){
            //condition if the parking is full
            if(!freeslot.size()){
                cout<<"We are sorry, our parking is full at the moment.\n";
                return;
            }
            /*if the parking is not full, we occupy the min available slot and 
            add this slot to the group of slots owned by the drivers of the same age*/
            int slotno=freeslot.top();
            freeslot.pop();
            carForAge[age].insert(slotno);
            slots[slotno].occupy(carno,age,slotno);
            slotOfcarRegNo[carno] = slotno;
            cout<<"Car with vehicle registration number "<<carno<<" has been parked at slot number "<<slotno<<'\n';
        }
        //funtion to remove the car from the parking lot
        void leave(int slotno){
            string carToLeaveRegNo = slots[slotno].getCarParkedNo();
            slotOfcarRegNo.erase(carToLeaveRegNo);
            int ageOfCarAtSlot = slots[slotno].getCarAge();
            carForAge[ageOfCarAtSlot].erase(slotno);
            slots[slotno].unoccupy();
            freeslot.push(slotno);
            cout<<"Slot number "<<slotno<<" vacated, the car with vehicle registration number "<<carToLeaveRegNo<<
            " left the space, the driver of the car was of age "<<ageOfCarAtSlot<<'\n';
        }
        //getter functions
        void getSlotNumbersFromAge(int x){
            for(auto it:carForAge[x]){
                cout<<it<<',';
            }
            cout<<'\n';
        }
        void getSlotNumberFromRegNo(string carno){
            cout<<slotOfcarRegNo[carno]<<'\n';
        }
        void getRegistrationNumbersFromAge(int age){
            for(auto it=carForAge[age].begin();it!=carForAge[age].end();it++){
                cout<<slots[*it].getCarParkedNo()<<',';
            }
            cout<<'\n';
            
        }
};
int main(){
    freopen("input.txt","r",stdin);
    string job;
    //declaring our parking lot dynamically
    parking_lot *parkingLot;

    while(cin>>job){
        if(job=="Create_parking_lot"){
            int lotcount;
            cin>>lotcount;
            parkingLot= new parking_lot(lotcount);
            cout<<"Created parking of "<<lotcount<<" slots\n";
        }
        else if(job=="Park"){
            string regno;
            string consume;
            int age;
            cin>>regno>>consume>>age;
            parkingLot->park(regno,age);
        }
        else if(job=="Slot_numbers_for_driver_of_age"){
            int age;
            cin>>age;
            parkingLot->getSlotNumbersFromAge(age);
        }
        else if(job=="Slot_number_for_car_with_number"){
            string regno;
            cin>>regno;
            parkingLot->getSlotNumberFromRegNo(regno);
        }
        else if(job=="Leave"){
            int slotNo;
            cin>>slotNo;
            parkingLot->leave(slotNo);
        }
        else if(job=="Vehicle_registration_number_for_driver_of_age"){
            int age;
            cin>>age;
            parkingLot->getRegistrationNumbersFromAge(age);
        }
    }
    delete parkingLot;

    return 0;
}

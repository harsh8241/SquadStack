#include<bits/stdc++.h>
using namespace std;

class Car{
    private:
        string registrationNumber;
        int driverAge;
        int lotAlloted;
    public:
        Car(){
            this->registrationNumber = "NONE";
            this->driverAge = -1;
            this->lotAlloted = -1;
        }
        Car(string registrationNumber,int driverAge,int lotAlloted){
            this->registrationNumber = registrationNumber;
            this->driverAge = driverAge;
            this->lotAlloted = lotAlloted;
        }
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
class Slot{
        Car c;
        bool isOccupied;
    public:
        Slot(){
            isOccupied = false;
        }

        void occupy(string carno,int age,int slotno){
            c.setRegNo(carno);
            c.setdriverAge(age);
            c.setLotAlloted(slotno);
            isOccupied = true;
        }

        void unoccupy(){
            isOccupied=false;
            c.setRegNo("");
            c.setdriverAge(-1);
            c.setLotAlloted(-1);
        }
        string getCarParkedNo(){
            return c.getCarNo();
        }
        int getCarAge(){
            return c.getdriverAge();
        }
};
class parking_lot{

    private:
        vector<Slot> slots;
        priority_queue<int,vector<int>,greater<int> >  freeslot;


        unordered_map<int,unordered_set<int>> carForAge;
        unordered_map<string,int> slotOfcarRegNo;

    public:
        parking_lot(int n){
            slots.resize(n+1);
            for(int i=1;i<=n;i++){
                freeslot.push(i);
            }
        }
        void park(string carno, int age){
            // cout<<carno<<' '<<age<<'\n';
            int slotno=freeslot.top();
            freeslot.pop();
            carForAge[age].insert(slotno);
            slots[slotno].occupy(carno,age,slotno);
            slotOfcarRegNo[carno] = slotno;
            cout<<"Car with vehicle registration number "<<carno<<" has been parked at slot number "<<slotno<<'\n';
        }
        void leave(int slotno){
            // cout<<slotno<<'\n';
            string carToLeaveRegNo = slots[slotno].getCarParkedNo();
            slotOfcarRegNo.erase(carToLeaveRegNo);
            int ageOfCarAtSlot = slots[slotno].getCarAge();
            carForAge[ageOfCarAtSlot].erase(slotno);
            slots[slotno].unoccupy();
            freeslot.push(slotno);
            cout<<"Slot number "<<slotno<<" vacated, the car with vehicle registration number "<<carToLeaveRegNo<<
            "left the space, the driver of the car was of age "<<ageOfCarAtSlot<<'\n';
        }
        void getSlotNumbersFromAge(int x){
            // cout<<x<<'\n';
            for(auto it:carForAge[x]){
                cout<<it<<',';
            }
            cout<<'\n';
        }
        void getSlotNumberFromRegNo(string carno){
            // cout<<carno<<'\n';
            cout<<slotOfcarRegNo[carno]<<'\n';
        }
        void getRegistrationNumbersFromAge(int age){
            // cout<<age<<'\n';
            for(auto it=carForAge[age].begin();it!=carForAge[age].end();it++){
                cout<<slots[*it].getCarParkedNo()<<',';
            }
            cout<<'\n';
            
        }
};
int main(){
    freopen("input.txt","r",stdin);
    string job;
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
    return 0;
    
}

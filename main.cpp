#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

class Person
{
protected:
    string name;
    string surname;
    int age;

public:
    Person(string name = "unknown", string surname = "unknown", int age = 0) : name(name), surname(surname), age(age) {}
    string getName(void)
    {
        return name;
    }
    string getSurname(void)
    {
        return surname;
    }
    void display(void) const
    {
        cout << "\nname: " << name << " " << "\nsurname: " << surname << "\nage: " << age << endl;
    }
};
class Guest : public Person
{
private:
    int guestId;

public:
    Guest(string name = "unknown", string surname = "unknown", int age = 0, int     guestId = 0): Person(name,surname,age), guestId(guestId){}

    void displayGuest(void) const {
        cout << "---Guest information--"<<endl;
        display();
        cout << "ID: " << guestId <<endl; 
    }
    int getGuestId(void) const {
        return guestId;
    }
};
class Worker {
    protected:  
        string position;
        double salary;
    public:
        Worker(string position = "unknown",double salary = 0.00): position(position),salary(salary) {}
        void displayworker(void) const {
            cout << "position: " << position << "\nSalary: " << salary << "SAR" << endl;
        }
};
class Employee: public Person, public Worker{
    public:
        Employee(string name = "unknown",string surname = "unknown", int age = 0,string position = "unknown",double salary = 0.00): Person(name,surname,age),Worker(position,salary){}
        void displayEmployee(void) const {
            cout << "--Employee information--" << endl;
            display();
            displayworker();
        }
};
class Room{
    private:
        string roomNumber;
        string roomType;
        int floor;
        int capacity;
        double nightlyPrice;
        bool available;
    public:
        Room(string roomNumber = "000",string roomType = "unset",int floor = 0,int capacity = 0,double nightlyPrice = 0.00,bool available = true):roomNumber(roomNumber),roomType(roomType),floor(floor),capacity(capacity),nightlyPrice(nightlyPrice),available(available){}
        void display(void) const {
            cout << "Room: " << roomNumber << "\nRoom Type: " << roomType << "\nFloor: " << floor << "\ncapacity: " << capacity << "\nNight Price: " << nightlyPrice << "\nAvailable: " << available << endl;
        }
        bool isAvailable(void){
            return available;
        }
        string getRoomNumber(void){
            return roomNumber;
        }
        double getNightlyPrice(void){
            return nightlyPrice;
        }
        void setAvailable(bool status){
            available = status;
        }
        bool operator == (const Room& other){
            return this->roomNumber == other.roomNumber;
        }
        bool operator < (const Room& other){
            return this->nightlyPrice < other.nightlyPrice;
        }
};
class Hotel{
    private:
        string hotelName;
        string address;
        Room rooms[50];
        Guest guests[50];
        Employee employees[10];
        int roomCount,guestCount,employeeCount;
    public:
        Hotel(string hotelName = "unknown",string address = "Buraydah"):hotelName(hotelName),address(address),roomCount(0),guestCount(0),employeeCount(0){}

        void addRoom(Room r){
            if(roomCount < 50){
                rooms[roomCount++] = r;
            }else {
                cout << "No room available!" << endl;
            }
        }
        void addGuest(Guest g){
            if(guestCount < 50){
                guests[guestCount++] = g;
            } else {
                cout << "No space available for new guests" << endl;
            }
        }
        void addEmployee(Employee e){
            if(employeeCount < 10){
                employees[employeeCount ++] = e;
            }else{
                cout << "No Vacancy Available!" << endl;
            }
        }
        void showAvailableRoom(){
            cout << "--Available Room at "<<hotelName<<" --" << endl;
            for(int i = 0; i < roomCount; ++i){
                if(rooms[i].isAvailable()){
                    rooms[i].display();
                }
            }
        }
        void ProcessReservation(Guest guest, Room& room){
            int night = 5;
            if(!room.isAvailable()){
                cout << "Room: " << room.getRoomNumber() << " is not available. "<< endl;
                return;
            }
            room.setAvailable(false);
            for(int i = 0; i < roomCount; ++i){
                 if(rooms[i] == room){
                    rooms[i].setAvailable(false);
                    break;
                }
            }
            cout << "Reservation Processed for Guest: " << guest.getName() << " "<< guest.getSurname() << "\n for Room: " << room.getRoomNumber() << " for " << night << " nights." << endl;
            double totalCost = night * room.getNightlyPrice();
            cout << "Total Cost: " << totalCost << " SAR" << endl;
        }
};
int main()
{
    Hotel hotel("Al Faisaliah Hotel", "Buraydah");
    Room room1("101", "Single", 1, 1, 200.00, true);
    Room room2("102", "Double", 1, 2, 350.00, true);
    Room room3("201", "Suite", 2, 4, 500.00, true);

    hotel.addRoom(room1);
    hotel.addRoom(room2);
    hotel.addRoom(room3);

    Guest guest1("Mohammed", "Mudayri", 30, 1);
    Guest guest2("Ahmad", "Harbi", 28, 2);

    hotel.addGuest(guest1);
    hotel.addGuest(guest2);

    Employee employee1("Mohemmed", "Alhassan", 35, "Manager", 5000.00);
    Employee employee2("Usman", "Saleh", 40, "Receptionist", 3000.00);

    hotel.addEmployee(employee1);
    hotel.addEmployee(employee2);

    hotel.showAvailableRoom();

    hotel.ProcessReservation(guest1, room1);
    hotel.ProcessReservation(guest2, room2);

    hotel.showAvailableRoom();

    return 0;
}
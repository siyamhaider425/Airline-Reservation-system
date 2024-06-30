#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

// Class to store passenger details
class Passenger {
public:
    string name;
    int age;
    string passportNumber;

    Passenger(string name, int age, string passportNumber)
        : name(name), age(age), passportNumber(passportNumber) {}
};

// Class to store flight details
class Flight {
public:
    string flightNumber;
    string destination;
    string departureTime;
    vector<Passenger> passengers;

    Flight(string flightNumber, string destination, string departureTime)
        : flightNumber(flightNumber), destination(destination), departureTime(departureTime) {}

    // Method to add a passenger to the flight
    void addPassenger(Passenger p) {
        passengers.push_back(p);
    }

    // Method to display flight details
    void displayFlightDetails() const {
        cout << "Flight Number: " << flightNumber << "\n";
        cout << "Destination: " << destination << "\n";
        cout << "Departure Time: " << departureTime << "\n";
        cout << "Passengers: \n";
        for (const auto& passenger : passengers) {
            cout << "  Name: " << passenger.name << ", Age: " << passenger.age << ", Passport Number: " << passenger.passportNumber << "\n";
        }
    }
};

// Class to manage the airline system
class AirlineManagementSystem {
public:
    vector<Flight> flights;

    // Method to add a flight to the system
    void addFlight(Flight f) {
        flights.push_back(f);
    }

    // Method to book a ticket for a passenger on a specific flight
    void bookTicket(string flightNumber, Passenger p) {
        for (auto& flight : flights) {
            if (flight.flightNumber == flightNumber) {
                flight.addPassenger(p);
                cout << "Ticket booked for " << p.name << " on flight " << flightNumber << "\n";
                return;
            }
        }
        cout << "Flight not found.\n";
    }

    // Method to display all flights in the system
    void displayAllFlights() const {
        if (flights.empty()) {
            cout << "No flights available.\n";
            return;
        }
        for (const auto& flight : flights) {
            flight.displayFlightDetails();
        }
    }
};

// Function to get passenger details from user
Passenger getPassengerDetails() {
    string name, passportNumber;
    int age;

    cout << "Enter passenger name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    getline(cin, name);

    cout << "Enter passenger age: ";
    while (!(cin >> age) || age <= 0) { // Input validation for age
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid age. Please enter a valid age: ";
    }

    cout << "Enter passport number: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    getline(cin, passportNumber);

    return Passenger(name, age, passportNumber);
}

// Function to get flight details from user
Flight getFlightDetails() {
    string flightNumber, destination, departureTime;

    cout << "Enter flight number: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    getline(cin, flightNumber);

    cout << "Enter destination: ";
    getline(cin, destination);

    cout << "Enter departure time (e.g., 10:00 AM): ";
    getline(cin, departureTime);

    return Flight(flightNumber, destination, departureTime);
}

int main() {
    AirlineManagementSystem ams;
    int choice;

    do {
        cout << "\nAirline Management System\n";
        cout << "1. Add Flight\n";
        cout << "2. Book Ticket\n";
        cout << "3. Display All Flights\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        while (!(cin >> choice)) { // Input validation for menu choice
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter a number between 1 and 4: ";
        }

        switch (choice) {
            case 1: {
                Flight flight = getFlightDetails();
                ams.addFlight(flight);
                break;
            }
            case 2: {
                string flightNumber;
                cout << "Enter flight number to book ticket: ";
                cin >> flightNumber;
                Passenger passenger = getPassengerDetails();
                ams.bookTicket(flightNumber, passenger);
                break;
            }
            case 3: {
                ams.displayAllFlights();
                break;
            }
            case 4: {
                cout << "Exiting...\n";
                break;
            }
            default: {
                cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
    } while (choice != 4);

    return 0;
}

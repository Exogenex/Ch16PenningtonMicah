// Micah Pennington
// April 26 2022 ©
// Chapter 16 Program

// Specification for the Employee class
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

class Employee {
private:
	string name;		// Employee name
	int number;		// Employee number
	string hireDate;	// Hire date

public:
	// Exception class
	class InvalidEmployeeNumber {
	private:
		int numberEntered;
		string message;
	public:
		InvalidEmployeeNumber(int numberEnteredIN, string messageIN) { numberEntered = numberEnteredIN; message = messageIN; }
		int getNumberEntered() { return numberEntered; }
		string getMessage() { return message; }
	};

	// Constructor
	Employee(string nameIN = "", int numberIN = 0, string hireDateIN = "") {
		name = nameIN;
		if (numberIN >= 0 && numberIN < 1000) number = numberIN;
		else { throw InvalidEmployeeNumber(numberIN, "Error: Invalid Employee Number (Not in rage of 0-999)"); }
		hireDate = hireDateIN;
	}

	// Mutators
	void setName(string n) { name = n; }
	void setNumber(int num) {
		if (num >= 0 && num < 1000) number = num;
		else { throw InvalidEmployeeNumber(num, "Error: Invalid Employee Number (Not in rage of 0-999)"); }
	}
	void setHireDate(string date) { hireDate = date; }

	// Accessors
	string getName() const { return name; }
	int getNumber() const { return number; }
	string getHireDate() const { return hireDate; }
};


// Specification for the ProductionWorker Class

#include <string>
using namespace std;

class ProductionWorker : public Employee {
private:
	int shift;	// The worker's shift
	double payRate;	// The worker's hourly pay rate

public:
	// Exception classes
	class InvalidShift {
	private:
		int shiftEntered;
		string message;
	public:
		InvalidShift(int shiftEnteredIN, string messageIN) { shiftEntered = shiftEnteredIN; message = messageIN; }
		int getShiftEntered() { return shiftEntered; }
		string getMessage() { return message; }
	};

	class InvalidPayRate {
	private:
		int rateEntered;
		string message;
	public:
		InvalidPayRate(int rateEnteredIN, string messageIN) { rateEntered = rateEnteredIN; message = messageIN; }
		int getRateEntered() { return rateEntered; }
		string getMessage() { return message; }
	};

	// Constructor
	ProductionWorker(string nameIN = "", int numberIN = 0, string hireDateIN = "", int shiftIN = 1, double payRateIN = 0.0) : Employee(nameIN, numberIN, hireDateIN) {
		if (shiftIN == 1 || shiftIN == 2) { shift = shiftIN; }
		else { throw InvalidShift(shiftIN, "Error: Invalid Shift (!= 1 or 2)"); }
		if (payRateIN >= 0) { payRate = payRateIN; }
		else { throw InvalidPayRate(payRateIN, "Error: Invalid Pay Rate (Negative Number)"); }
	}

	// Mutators
	void setShift(int shiftIN) {
		if (shiftIN == 1 || shiftIN == 2) { shift = shiftIN; }
		else { throw InvalidShift(shiftIN, "Error: Invalid Shift (not 1 or 2)"); }
	}
	void setPayRate(double payRateIN) {
		if (payRateIN >= 0) { payRate = payRateIN; }
		else { throw InvalidPayRate(payRateIN, "Error: Invalid Pay Rate (Negative Number)"); }
	}

	// Accessors
	int getShiftNumber() const { return shift; }

	string getShiftName() const {
		if (shift == 1) return "Day";
		else if (shift == 2) return "Night";
		else return "Invalid";
	}
	double getPayRate() const { return payRate; }
};

int main() {

	cout << "Constructor errors:\n";

	// Employee object constructed with Employee number too low
	try { Employee e = Employee("Dave", -1, "4/26/2022"); }
	catch (Employee::InvalidEmployeeNumber ex) {
		cout << ex.getMessage() << '\n';
		cout << "Number entered was: " << ex.getNumberEntered() << '\n';
	}
	// Employee object constructed with Employee number too high
	try { Employee e = Employee("Dave II", 1000, "4/26/2022"); }
	catch (Employee::InvalidEmployeeNumber ex) {
		cout << ex.getMessage() << '\n';
		cout << "Number entered was: " << ex.getNumberEntered() << '\n';
	}


	// Production Worker object constructed with wrong shift value
	try { ProductionWorker pw = ProductionWorker("Dave III", 3, "4/26/2022", 0, 3.3); }
	catch (ProductionWorker::InvalidShift ex) {
		cout << ex.getMessage() << '\n';
		cout << "Shift entered was: " << ex.getShiftEntered() << '\n';
	}
	// Production Worker object constructed with invalid pay rate
	try { ProductionWorker pw = ProductionWorker("Dave IV", 4, "4/26/2022", 1, -4.4); }
	catch (ProductionWorker::InvalidPayRate ex) {
		cout << ex.getMessage() << '\n';
		cout << "Pay rate entered was: " << ex.getRateEntered() << '\n';
	}

	cout << "\n\nSet errors:\n";

	Employee emp = Employee();

	// Employee object set Employee number too low
	try { emp.setNumber(-77777); }
	catch (Employee::InvalidEmployeeNumber ex) {
		cout << ex.getMessage() << '\n';
		cout << "Number entered was: " << ex.getNumberEntered() << '\n';
	}
	// Employee object set Employee number too high
	try { emp.setNumber(999999); }
	catch (Employee::InvalidEmployeeNumber ex) {
		cout << ex.getMessage() << '\n';
		cout << "Number entered was: " << ex.getNumberEntered() << '\n';
	}

	ProductionWorker powo = ProductionWorker();

	// Production Worker object constructed with wrong shift value
	try { powo.setShift(93); }
	catch (ProductionWorker::InvalidShift ex) {
		cout << ex.getMessage() << '\n';
		cout << "Shift entered was: " << ex.getShiftEntered() << '\n';
	}
	// Production Worker object constructed with invalid pay rate
	try { powo.setPayRate(-40.4); }
	catch (ProductionWorker::InvalidPayRate ex) {
		cout << ex.getMessage() << '\n';
		cout << "Pay rate entered was: " << ex.getRateEntered() << '\n';
	}


	return EXIT_SUCCESS;
}
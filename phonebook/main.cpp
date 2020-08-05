#include <iostream>
#include <string>
#include <vector>
 
class PhoneBook {
public:
	struct Contact {
		std::string phoneNumber_, name_, adress_;
		int id_;
		Contact(std::string phoneNumber, std::string name, std::string adress, int id) : phoneNumber_(phoneNumber), name_(name), adress_(adress), id_(id) {} 
	};
	void PrintContact(const Contact& currentContact) const {
		std::cout << currentContact.phoneNumber_ << ' ' << currentContact.name_ << ' ' << currentContact.adress_ << ' ' << currentContact.id_ << "\n";
	}
	bool Check(const std::string number, const std::string sub_number) {
		return (sub_number.length() <= number.length() && number.substr((int)sub_number.length()) == sub_number);
	}
	void AddNew() {
		std::string newNumber, newName, newAdress;
		std::cout << "Enter his phone number:\n";
		std::cin >> newNumber;
		std::cout << "Enter his name:\n";
		std::cin >> newName;
		std::cout << "Enter his adress:\n";
		std::cin >> newAdress;
		int wasId = 0;
		for (auto& currentContact : contacts_) {
			if (currentContact.name_ == newName || currentContact.phoneNumber_ == newNumber) {
				wasId = currentContact.id_;
				break;
			}
		}
		if (wasId != 0) {
			std::cout << "There is such contact with ID " << wasId << "\n"; 
		}
		else {
			contacts_.push_back({newNumber, newName, newAdress, ++count_});
		}
	}
	void FindByName() {
		
	}
	void FindByPhoneNumber() {
		std::cout << "Enter what phone number to find:\n";
		std::string numberForFind;
		std::cin >> numberForFind;
		std::vector<Contact> suitable;
		for (auto& currentContact : contacts_) {
			if (Check(currentContact.phoneNumber_, numberForFind)) {
				suitable.push_back(currentContact);
			}
		}
		if (suitable.empty()) {
			std::cout << "There are no contacts with such phone number\n";
		}
		else {
			for (auto& current_contact : suitable) {
				PrintContact(current_contact);
			}
		}
	}
	void FindById() {
		std::cout << "What ID do you want to find?\n";
		int findID;
		bool was = false;
		std::cin >> findID;
		for (auto& currentContact : contacts_) {
			if (currentContact.id)_ == findID) {
				PrintContact(currentContact);
				was = true;
				break;
			}
		}
		if (!was) {
			std::cout << "There is no such ID\n";
		}
	}
	void DeleteById() {
		std::cout << "What ID do you want to delete?\n";
		int delID, need = -1;
		std::cin >> delID;
		for (int number = 0; number < contacts_.size(); number++) {
			if (contacts[number].id_ == delID) {
				need = number;
				break;
			}
		}
		if (need == -1) {
			std::cout << "There is no such ID\n";
		}
		else {
			contacts_.erase(contacts_.begin() + need);
		}
	}
	void ShowContacts() {
		for (auto& currentContact : contacts_) {
			PrintContact(currentContact);
		}
	}
private:
    std::vector<Contact> contacts_;
    int count_ = 0;
};
 
int ChooseAction() {
	std::cout << "Choose action:\n";
	std::cout << "1. Add contact\n";
	std::cout << "2. Find contact by name\n";
	std::cout << "3. Find contact by phone number\n";
	std::cout << "4. Find contact by id\n";
	std::cout << "5. Delete contact by id\n";
	std::cout << "6. Show contacts with the same adress\n";
	int action;
	std::cin >> action;
	return action;
}
 
void Solve() {
    PhoneBook phonebook;
	int action = ChooseAction();
//	std::cout << "DEBUG : " << action << std::endl;
	switch (action) {
		case 1: {
			phonebook.AddNew();
			break;
		}
		case 2: {
			phonebook.FindByName();
			break;
		}
		case 3: {
			phonebook.FindByPhoneNumber(); 
			break;
		}
		case 4: {
			phonebook.FindById();
			break;
		}
		case 5: {
			phonebook.DeleteById();
			break;
		}
		case 6: {
			phonebook.ShowContacts();
			break;
		}
	}
}
 
int main() {
	Solve();
	return 0;
}

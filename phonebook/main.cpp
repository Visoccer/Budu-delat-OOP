#include <iostream>
#include <string>
#include <vector>
 
int count;
 
class PhoneBook {
public:
	struct Contact {
		std::string phone_number, name, adress;
		int id;
		Contact(std::string phone_number, std::string name, std::string adress, int id) {
			this->phone_number = phone_number;
			this->name = name;
			this->adress = adress;
			this->id = id; 
		}
	};
	std::vector<Contact> contacts;
	void PrintContact(Contact& current_contact) {
		std::cout << current_contact.phone_number << ' ' << current_contact.name << ' ' << current_contact.adress << ' ' << current_contact.id << "\n";
	}
	bool Check(std::string number, std::string sub_number) {
		return (sub_number.length() <= number.length() && number.substr((int)sub_number.length()) == sub_number);
	}
	void AddNew() {
		std::string new_number, new_name, new_adress;
		std::cout << "Enter his phone number:\n";
		std::cin >> new_number;
		std::cout << "Enter his name:\n";
		std::cin >> new_name;
		std::cout << "Enter his adress:\n";
		std::cin >> new_adress;
		int was_id = 0;
		for (auto& current_contact : contacts) {
			if (current_contact.name == new_name || current_contact.phone_number == new_number) {
				was_id = current_contact.id;
				break;
			}
		}
		if (was_id != 0) {
			std::cout << "There is such contact with Id " << was_id << "\n"; 
		}
		else {
			contacts.push_back({new_number, new_name, new_adress, ++count});
		}
	}
	void FindByName() {
 
	}
	void FindByPhoneNumber() {
		std::cout << "Enter what phone number to find:\n";
		std::string number_for_find;
		std::cin >> number_for_find;
		std::vector<Contact> suitable;
		for (auto& current_contact : contacts) {
			if (Check(current_contact.phone_number, number_for_find)) {
				suitable.push_back(current_contact);
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
 
	}
	void DeleteById() {
 
	}
	void ShowContacts() {
 
	}
} phonebook;
 
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
	int action = ChooseAction();
	std::cout << "DEBUG : " << action << std::endl;
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

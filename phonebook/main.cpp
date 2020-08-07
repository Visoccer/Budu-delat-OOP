#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>

//using namespace std;

class Number {
public:
    Number(std::string data) : data_(data) {}
    Number() {}
    
    std::string GetData() {
        return data_;
    }
private:
    std::string data_;
};
 
class Name {
public:
    Name(std::vector<std::string> data) : data_(data) {}
    Name() {}
    
    std::vector<std::string> GetData() {
        return data_;
    }
private:
    std::vector<std::string> data_;
};
 
class Adress {
public:
    Adress(std::string data) : data_(data) {}
    Adress() {}

    std::string GetData() {
        return data_;
    }
private:
    std::string data_;
};

std::vector<std::string> ConvertToVector(const std::string words) {
    std::vector<std::string> convertedVector;
    std::string currentWord;
    for (int i = 0; i < words.size(); i++) {
        char symbol = words[i];
        if (symbol >= 'A' && symbol <= 'Z') {
            symbol = char('a' + int(symbol - 'A'));
        }
        if (symbol != ' ') {
            convertedVector.push_back(currentWord);
            currentWord.clear();
        }
        else {
            currentWord.push_back(symbol);
        }
    }
    if (!currentWord.empty()) {
        convertedVector.push_back(currentWord);
    }
    sort(convertedVector.begin(), convertedVector.end());
    return convertedVector;
}

class Contact {
public:	
    Contact(Number number, Name name, Adress adress) : 
        number_(number), name_(name), adress_(adress) {}
    Contact() {}
    
    //getters
    std::string GetNumber() {
        return number_.GetData();
    }
    std::vector<std::string> GetName() {
        return name_.GetData();
    }
    std::string GetAdress() {
        return adress_.GetData();
    }
    
    //setters
    void SetNumber(const std::string number) {
        number_ = number;
    }
    void SetName(const std::string name) {
        std::vector<std::string> convertedName = ConvertToVector(name);
        name_ = convertedName;
    }
    void SetAdress(const std::string adress) {
        adress_ = adress;
    }

private:
    Number number_;
    Name name_;
    Adress adress_;
};
 
class PhoneBook {
public:
    int Check(const std::string number, const std::vector<std::string> name) {
        for (auto& iteration : contacts_) {
            auto& contact = iteration.second;
            if (contact.GetNumber() == number || contact.GetName() == name) {
                return iteration.first;
            }
        }
        return -1;
    }
    
    bool CheckAdress(const std::string subAdress, const std::string adress) {
        int len = subAdress.length();
        return (len <= adress.length() && subAdress == adress.substr(0, len));
    }
    
    int AddContact(const std::string number, const std::string name, const std::string adress) {
        std::vector<std::string> convertedName = ConvertToVector(name);
        int check = Check(number, convertedName);
        if (check != -1) {
            return check;
        }
        else {
            Contact newContact = {number, convertedName, adress};
            contacts_[++count_] = {number, convertedName, adress};
            return 0;
        }
    }
    
    int FindName(const std::string name) {
        std::vector<std::string> convertedName = ConvertToVector(name);
        for (auto& iteration : contacts_) {
            auto& contact = iteration.second;
            if (contact.GetName() == convertedName) {
                return iteration.first;
            }
        }
        return -1;
    }
    
    int FindNumber(const std::string number) {
        for (auto& iteration : contacts_) {
            auto& contact = iteration.second;
            if (contact.GetNumber() == number) {
                return iteration.first;
            }
        }
        return -1;
    }
    
    Contact FindID(const int id) {
        return contacts_[id];
    }
    
    void DeleteID(const int id) {
        contacts_.erase(contacts_.find(id));
    }
    
    std::vector<Contact> FindAdress(const std::string adress) {
        std::vector<Contact> finded;
        for (auto& iteration : contacts_) {
            auto& contact = iteration.second;
            std::string currentAdress = contact.GetAdress();
            if (CheckAdress(adress, currentAdress)) {
                finded.push_back(contact);
            }
        }
        return finded;
    }
    
private:
    std::unordered_map<int, Contact> contacts_;
    int count_ = 0;
};
 
void Solve() {
    PhoneBook phonebook;
}
 
int main() {
    Solve();
    return 0;
}

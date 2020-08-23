#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

//using namespace std;

class Number {
public:
    Number(std::string data) : data_(data) {}
    Number() {}
    
    const std::string& GetData() const {
        return data_;
    }
    void SetData(const std::string& data) {
        data_ = data;
    }
private:
    std::string data_;
};
 
class Name {
public:
    Name(std::string data) : data_(data) {}
    Name() {}
    
    const std::string& GetData() const {
        return data_;
    }
    void SetData(const std::string& data) {
        data_ = data;
    }
private:
    std::string data_;
};
 
class Adress {
public:
    Adress(std::string data) : data_(data) {}
    Adress() {}

    const std::string& GetData() const {
        return data_;
    }
    void SetData(const std::string& data) {
        data_ = data;
    }
private:
    std::string data_;
};

class NameBuffer {
public:
    NameBuffer(std::vector<std::string> data) : data_(data) {}
    NameBuffer() {}
    
    const std::vector<std::string>& GetData() const {
        return data_;
    }
    void SetData(const std::vector<std::string>& data) {
        data_ = data;
    }
private:
    std::vector<std::string> data_;
};

std::vector<std::string> ConvertToVector(const std::string& words) {
    std::vector<std::string> convertedVector;
    std::string currentWord;
    for (size_t i = 0; i < words.size(); i++) {
        char symbol = words[i];
        if (symbol >= 'A' && symbol <= 'Z') {
            symbol = char('a' + int(symbol - 'A'));
        }
        if (symbol != ' ') {
            convertedVector.push_back(currentWord);
            currentWord.clear();
        } else {
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
    Contact(Number number, Name name, Adress adress, NameBuffer nameBuffer)  
        : number_(number), name_(name), adress_(adress), nameBuffer_(nameBuffer) {}
    Contact() {}
    const std::string& GetNumber() const {
        return number_.GetData();
    }
    const std::string& GetName() const {
        return name_.GetData();
    }
    const std::string& GetAdress() const {
        return adress_.GetData();
    }
    const std::vector<std::string>& GetNameBuffer() const {
        return nameBuffer_.GetData();
    }
    
    void SetNumber(const std::string& number) {
        number_.SetData(number);
    }
    void SetName(const std::string& name) {
        std::vector<std::string> convertedName = ConvertToVector(name);
        name_.SetData(name);
        nameBuffer_.SetData(convertedName);
    }
    void SetAdress(const std::string& adress) {
        adress_.SetData(adress);
    }

private:
    Number number_;
    Adress adress_;
    Name name_;
    NameBuffer nameBuffer_;
};
 
class PhoneBook {
public:
    const std::unordered_map<int, Contact>& GetContacts() const {
        return contacts_;
    }
      
    int Check(const std::string& number, const std::vector<std::string>& name) {
        for (auto& iteration : contacts_) {
            auto& contact = iteration.second;
            if (contact.GetNumber() == number || contact.GetNameBuffer() == name) {
                return iteration.first;
            }
        }
        return -1;
    }
    
    bool CheckAdress(const std::string& subAdress, const std::string& adress) {
        int len = subAdress.length();
        return (len <= adress.length() && subAdress == adress.substr(0, len));
    }
    
    int AddContact(const std::string& number, const std::string& name, const std::string& adress) {
        std::vector<std::string> convertedName = ConvertToVector(name);
        int check = Check(number, convertedName);
        if (check != -1) {
            return -check;
        } else {
            contacts_[++count_] = {number, name, adress, convertedName};
            return count_;
        }
    }
    
    int FindName(const std::string& name) {
        std::vector<std::string> convertedName = ConvertToVector(name);
        for (auto& iteration : contacts_) {
            auto& contact = iteration.second;
            if (contact.GetNameBuffer() == convertedName) {
                return iteration.first;
            }
        }
        return -1;
    }
    
    int FindNumber(const std::string& number) {
        for (auto& iteration : contacts_) {
            auto& contact = iteration.second;
            if (contact.GetNumber() == number) {
                return iteration.first;
            }
        }
        return -1;
    }
    
    Contact* FindID(const int id) {
        if (contacts_.find(id) != contacts_.end()) {
            return &contacts_[id];
        } else {
            return nullptr;
        }
    }
    
    void DeleteID(const int id) {
        contacts_.erase(contacts_.find(id));
    }
    
    std::vector<Contact> FindAdress(std::string& adress) {
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

void PrintContact(const Contact& contact) {
    std::cout << contact.GetNumber() << ' ' << contact.GetName() << ' ' << contact.GetAdress() << ", ";
}

void ShowContacts(PhoneBook& phoneBook) {
    std::unordered_map<int, Contact> contacts = phoneBook.GetContacts();
    for (auto& iteration : contacts) {
        PrintContact(iteration.second);
        std::cout << "ID : " << iteration.first << "\n";
    }
}

void ShowAdresses(PhoneBook& phoneBook, std::string& adress) {
    std::vector<Contact> suitable = phoneBook.FindAdress(adress);
    for (auto& contact : suitable) {
        PrintContact(contact);
    }
}

void Solve() {
    PhoneBook phoneBook;
    phoneBook.AddContact("+228", "Sokarev Ivan", "ULITSA BSUIR");
    ShowContacts(phoneBook);
    /*std::string adress = "ULITSA";
    ShowAdresses(phoneBook, adress);*/
    phoneBook.FindID(1)->SetName("Stas Bokun GOD");
    ShowContacts(phoneBook);
}
 
int main() {
    Solve();
    return 0;
}

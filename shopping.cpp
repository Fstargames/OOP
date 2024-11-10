#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>

// Base class
class Item {
protected:
    std::string name;
    double price;

public:
    Item(const std::string& name, double price) : name(name), price(price) {}
    virtual ~Item() = default;

    // Virtual method to display item information
    virtual void display() const {
        std::cout << "Item: " << name << ", Price: $" << price;
    }

    virtual void persist(std::ofstream& ofs) const = 0;
    virtual std::string getType() const = 0; // Pure virtual function for type
};

class Grocery : public Item{
    double weight;

    public:
        Grocery(const std::string& name, double price, double weight) 
            : Item(name, price), weight(weight){}

        void display() const override {
            Item::display();
            std::cout << ", Type: Grocery, Weight: " << weight << " kg" << std::endl;
        }

        void persist(std::ofstream& ofs) const override {
            ofs << "Grocery " << name << " " << price << " " << weight << "\n";
        }

        static std::unique_ptr<Item> restore(std::ifstream& ifs) {
            std::string name;
            double price, weight;
            ifs >> name >> price >> weight;
            return std::make_unique<Grocery>(name, price, weight);
        }



        std::string getType() const override {return "Grocery";}

};

class Electronics : public Item{
    int warrantyPeriod;

    public:
        Electronics(const std::string& name, double price, int warrantyPeriod) 
            : Item(name, price), warrantyPeriod(warrantyPeriod) {}
    
        void display() const override {
            Item::display();
            std::cout << ", Type: Electronics, Warranty: " << warrantyPeriod << " months" << std::endl;
        }

        void persist(std::ofstream& ofs) const override{
            ofs << "Electronics " << name << " " << price << " " << warrantyPeriod << "\n";
        }

        static std::unique_ptr<Item> restore(std::ifstream& ifs){
            std::string name;
            double price;
            int warrantyPeriod;
            ifs >> name >> price >> warrantyPeriod;
            return std::make_unique<Electronics>(name, price, warrantyPeriod);
        }

        std::string getType() const override {return "Electronics";}


};

class Clothing : public Item{
    std::string size;

    public:
        Clothing(const std::string& name, double price, std::string& size)
            : Item(name, price), size(size) {}

        void display() const override {
            Item::display();

            std::cout << ", Type: Clothing, Size: " << size << std::endl;
        }

        void persist(std::ofstream& ofs) const override{
            ofs << "Clothing " << name << " " << price << " "<< size << "\n";
        }

        static std::unique_ptr<Item> restore(std::ifstream& ifs) {
            std::string name, size;
            double price;
            ifs >> name >> price >> size;
            return std::make_unique<Clothing>(name, price, size);
        }

        std::string getType() const override {return "Clothing";}
        
        
};

class Book : public Item{
    std::string author;

    public:
        Book(std::string& name, double price, std::string& author)
            : Item(name, price), author(author) {}

        void display() const override{
            Item::display();

            std::cout << ", Type: Book, Author: " << author << std::endl;
        }

        void persist(std::ofstream& ofs) const override {
            ofs << "Book " << name << " " << price << " " << author << "\n";
        }

        static std::unique_ptr<Item> restore(std::ifstream& ifs){
            std::string name, author;
            double price;
            ifs >> name >> price >> author;
            return std::make_unique<Book>(name, price, author);
        }

        std::string getType() const override {return "Book";}
};

class Toy : public Item{
    int ageRecommendation;

    public:
        Toy(std::string& name, double price, int ageRecommendation)
            : Item(name, price), ageRecommendation(ageRecommendation){}

        void display() const override{
            Item::display();

            std::cout << ", Type: Toy, Age Recommendation: " << ageRecommendation << " years and above " << std::endl;

        }

        void persist(std::ofstream& ofs) const override{
            ofs << "Toy " << name << " "<< price << " " << ageRecommendation << "\n";
        }

        static std::unique_ptr<Item> restore(std::ifstream& ifs){
            std::string name;
            double price;
            int ageRecommendation;
            ifs >> name >> price >> ageRecommendation;
            return std::make_unique<Toy>(name, price, ageRecommendation);
        }

        std::string getType() const override {return "Toy";}
};

std::vector<std::unique_ptr<Item>> restoreCollection(std::ifstream& ifs){
    std::vector<std::unique_ptr<Item>> items;
    std::string type;

    while (ifs >> type){
        if (type == "Grocery"){
            items.push_back(Grocery::restore(ifs));
        }
        if (type == "Electronics"){
            items.push_back(Electronics::restore(ifs));
        }
        if (type == "Clothing"){
            items.push_back(Clothing::restore(ifs));
        }
        if (type == "Book"){
            items.push_back(Book::restore(ifs));
        }
        if (type == "Toy"){
            items.push_back(Toy::restore(ifs));
        }
        
    }

    return items;
}

int main() {
   // std::vector<std::unique_ptr<Item>> items;
    char choice;

    // Restoring

    std::ifstream ifs("items.txt");
    auto items = restoreCollection(ifs);
    ifs.close();

    std::cout << "Restored items:\n";
    for (const auto& item : items){
        item->display();
    }

    do{
        std::cout << "\n Add an item: \n";
        std::cout << "1. Grocery\n";
        std::cout << "2. Electronics\n";
        std::cout << "3. Clothing\n";
        std::cout << "4. Book\n";
        std::cout << "5. Toy\n";
        std::cout << "Enter your choice (q to quit): ";
        std::cin >> choice;

        if (choice == 'q') break;

        std::string name;
        double price;
        std::cout << "Enter item name: ";
        std::cin >> name;
        std::cout << "Enter item price: ";
        std::cin >> price;

        switch (choice) {
            case '1': {
                double weight;
                std::cout << "Enter weight: ";
                std::cin >> weight;
                items.push_back(std::make_unique<Grocery>(name, price, weight));
                break;

            }
            case '2' : {
                int warrantyPeriod;
                std::cout << "Enter warranty period";
                std::cin >> warrantyPeriod;
                items.push_back(std::make_unique<Electronics>(name, price, warrantyPeriod));
                break;
            }
            case '3':{
                std::string size;
                std::cout << "Enter size: ";
                std::cin >> size;
                items.push_back(std::make_unique<Clothing>(name, price, size));
                break;
            }
            case '4': {
                std::string author;
                std::cout << "Enter author name: ";
                std::cin >> author;
                items.push_back(std::make_unique<Book>(name, price, author));
                break;
            }
            case '5': {
                int ageRecommendation;
                std::cout << "Enter age recommendation: ";
                std::cin >> ageRecommendation;
                items.push_back(std::make_unique<Toy>(name, price, ageRecommendation));
                break;
            }
            default:
                std::cout << "Invalid choice!" << std::endl;
                break;
        } 

    }while (true);

    //Saving to file

    std::ofstream ofs("items.txt");
    for(const auto& item : items){
        item -> persist(ofs);
    }
    ofs.close();
    
    std::cout << "\n All items in collection: \n";
    for(const auto& item : items){
        item -> display();
    }

    return 0;
}


#include <iostream>
#include <vector>
#include <algorithm>

// Base class representing a product
class Product {
protected:
    std::string name;
    std::string category;
    double price;
    int quantity;
    int id;

public:
    // Constructor
    Product(const std::string& name, const std::string& category, double price, int quantity, int id)
            : name(name), category(category), price(price), quantity(quantity), id(id) {}

    // Getter methods
    std::string getName() const {
        return name;
    }
    std::string getCategory() const {
        return category;
    }
    double getPrice() const {
        return price;
    }
    int getQuantity() const {
        return quantity;
    }
    int getId() const {
        return id;
    }

    // Display product details
    virtual void displayDetails() const {
        std::cout << "Product Name: " << name << std::endl;
        std::cout << "Category: " << category << std::endl;
        std::cout << "Price: $" << price << std::endl;
        std::cout << "Quantity: " << quantity << std::endl;
        std::cout << "ID: " << id << std::endl;
    }

    // Overloaded less than operator for sorting
    bool operator<(const Product& other) const {
        return price < other.price;
    }

    // Destructor
    virtual ~Product() = default;
};

// Derived class representing a food product
class Food : public Product {
private:
    std::string expiryDate;

public:
    // Constructor
    Food(const std::string& name, const std::string& category, double price, int quantity, int id, const std::string& expiryDate)
            : Product(name, category, price, quantity, id), expiryDate(expiryDate) {}

    // Display food product details
    void displayDetails() const override {
        Product::displayDetails();
        std::cout << "Expiry Date: " << expiryDate << std::endl;
    }

    // Destructor
    ~Food() override = default;
};

// Derived class representing an electronics product
class Electronics : public Product {
private:
    std::string brand;

public:
    // Constructor
    Electronics(const std::string& name, const std::string& category, double price, int quantity, int id, const std::string& brand)
            : Product(name, category, price, quantity, id), brand(brand) {}

    // Display electronics product details
    void displayDetails() const override {
        Product::displayDetails();
        std::cout << "Brand: " << brand << std::endl;
    }

    // Destructor
    ~Electronics() override = default;
};

// Class representing an inventory
class Inventory {
private:
    std::vector<Product*> products;

public:
    // Add a product to the inventory
    void addProduct(Product* product) {
        products.push_back(product);
    }

    // Remove a product from the inventory by ID
    void removeProduct(int id) {
        auto it = std::find_if(products.begin(), products.end(), [id](Product* product) {
            return product->getId() == id;
        });

        if (it != products.end()) {
            delete *it;
            products.erase(it);
            std::cout << "Product with ID " << id << " has been removed." << std::endl;
        } else {
            std::cout << "Product with ID " << id << " not found." << std::endl;
        }
    }

    // Search for a product by name
    void searchProduct(const std::string& name) {
        auto it = std::find_if(products.begin(), products.end(), [name](Product* product) {
            return product->getName() == name;
        });

        if (it != products.end()) {
            (*it)->displayDetails();
        } else {
            std::cout << "Product with name " << name << " not found." << std::endl;
        }
    }

    // Display details of all products in the inventory
    void displayAllProducts() const {
        if (products.empty()) {
            std::cout << "No products in inventory." << std::endl;
        } else {
            for (const auto& product : products) {
                product->displayDetails();
                std::cout << "---------------------" << std::endl;
            }
        }
    }

    // Sort products in the inventory by price
    void sortProductsByPrice() {
        std::sort(products.begin(), products.end(), [](Product* a, Product* b) {
            return *a < *b;
        });
    }

    // Destructor
    ~Inventory() {
        for (const auto& product : products) {
            delete product;
        }
    }
};

int main() {
    Inventory inventory;

    // Create some sample products
    Product* product1 = new Food("Apple", "Fruits", 1.99, 100, 1, "2023-05-20");
    Product* product2 = new Electronics("Phone", "Electronics", 499.99, 20, 2, "Apple");
    Product* product3 = new Electronics("laptop", "Electronics", 899.99, 15, 3, "HP");
    Product* product4 = new Food("Cheese", "Dairy products", 15, 50, 4, "2023-04-11");


    // Add the products to the inventory
    inventory.addProduct(product1);
    inventory.addProduct(product2);
    inventory.addProduct(product3);
    inventory.addProduct(product4);

    std::cout << "Welcome to the Inventory Management System!" << std::endl;

    while (true) {
        // Display menu options
        std::cout << "\nPlease select an option:" << std::endl;
        std::cout << "1. Add Product" << std::endl;
        std::cout << "2. Remove Product" << std::endl;
        std::cout << "3. Search Product" << std::endl;
        std::cout << "4. Display All Products" << std::endl;
        std::cout << "5. Sort Products by Price" << std::endl;
        std::cout << "6. Exit" << std::endl;

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                // Add a new product to the inventory
                std::cout << "Enter product details:" << std::endl;
                std::string name, category, expiryDate, brand;
                double price;
                int quantity, id;

                std::cout << "Name: ";
                std::cin >> name;
                std::cout << "Category: ";
                std::cin >> category;
                std::cout << "Price: $";
                std::cin >> price;
                std::cout << "Quantity: ";
                std::cin >> quantity;
                std::cout << "ID: ";
                std::cin >> id;

                std::cout << "1. Food\n2. Electronics" << std::endl;
                int typeChoice;
                std::cin >> typeChoice;

                if (typeChoice == 1) {
                    std::cout << "Expiry Date: ";
                    std::cin >> expiryDate;
                    inventory.addProduct(new Food(name, category, price, quantity, id, expiryDate));
                } else if (typeChoice == 2) {
                    std::cout << "Brand: ";
                    std::cin >> brand;
                    inventory.addProduct(new Electronics(name, category, price, quantity, id, brand));
                } else {
                    std::cout << "Invalid choice." << std::endl;
                }

                break;
            }
            case 2: {
                // Remove a product from the inventory
                std::cout << "Enter product ID to remove: ";
                int id;
                std::cin >> id;
                inventory.removeProduct(id);
                break;
            }
            case 3: {
                // Search for a product in the inventory
                std::cout << "Enter product name to search: ";
                std::string name;
                std::cin >> name;
                inventory.searchProduct(name);
                break;
            }
            case 4:
                // Display all products in the inventory
                inventory.displayAllProducts();
                break;
            case 5:
                // Sort products in the inventory by price
                inventory.sortProductsByPrice();
                std::cout << "Products sorted by price." << std::endl;
                break;
            case 6:
                // Exit the program
                std::cout << "Exiting..." << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice." << std::endl;
        }
    }
}

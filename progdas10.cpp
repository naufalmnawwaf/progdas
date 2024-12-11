#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// Class User untuk menyimpan informasi pengguna dan pemesanan
class User {
public:
    int id;
    string name;
    string email;
    string phone;
    string password;
    vector<string> orders; // Menyimpan daftar pemesanan kendaraan

    // Constructor untuk User
    User(int userId, string userName, string userEmail, string userPhone, string userPassword) {
        id = userId;
        name = userName;
        email = userEmail;
        phone = userPhone;
        password = userPassword;
    }

    // Fungsi untuk menambah pemesanan
    void addOrder(string vehicleName) {
        orders.push_back(vehicleName); // Menambah kendaraan yang dipesan
        cout << "Pemesanan kendaraan '" << vehicleName << "' berhasil dilakukan!" << endl;
    }

    // Fungsi untuk melihat semua pemesanan
    void viewOrders() {
        if (orders.empty()) {
            cout << "Anda belum melakukan pemesanan." << endl;
        } else {
            cout << "Daftar Pemesanan Anda:" << endl;
            for (const string& order : orders) {
                cout << "- " << order << endl;
            }
        }
    }

    // Fungsi untuk menyimpan data pengguna ke file CSV
    void saveToFile(ofstream& outFile) {
        outFile << id << "," << name << "," << email << "," << phone << "," << password << "\n";
    }

    // Fungsi untuk menyimpan pemesanan ke file CSV
    void saveOrdersToFile(ofstream& outFile) {
        for (const string& order : orders) {
            outFile << id << "," << order << "\n";
        }
    }
};

// Class Kendaraan untuk mengelola data kendaraan
class Vehicle {
public:
    int id;
    string name;
    double price;
    bool isAvailable;

    // Constructor untuk kendaraan
    Vehicle(int vehicleId, string vehicleName, double vehiclePrice)
        : id(vehicleId), name(vehicleName), price(vehiclePrice), isAvailable(true) {}

    // Fungsi untuk menampilkan informasi kendaraan
    void displayInfo() {
        cout << "Nama Kendaraan: " << name << endl;
        cout << "Harga: " << price << endl;
        cout << (isAvailable ? "Tersedia" : "Tidak Tersedia") << endl;
    }

    // Fungsi untuk menyimpan kendaraan ke file CSV
    void saveToFile(ofstream& outFile) {
        outFile << id << "," << name << "," << price << "," << (isAvailable ? "Tersedia" : "Tidak Tersedia") << "\n";
    }
};

// Class untuk menangani sistem pendaftaran dan login
class System {
private:
    vector<User> users;
    vector<Vehicle> vehicles;
    User* loggedInUser = nullptr;

public:
    // Constructor untuk menginisialisasi kendaraan
    System() {
        // Data kendaraan yang ditambahkan
        vehicles.push_back(Vehicle(1, "Vespa Sprint", 35000));
        vehicles.push_back(Vehicle(2, "Vespa GTS", 75000));
        vehicles.push_back(Vehicle(3, "Vespa Primavera", 52000));
        vehicles.push_back(Vehicle(4, "Vespa LX 125", 45000));
    }

    // Fungsi untuk pendaftaran pengguna
    void registerUser() {
        string name, email, phone, password;
        int id = users.size() + 1; // ID pengguna baru

        cout << "Masukkan nama: ";
        cin >> name;
        cout << "Masukkan email: ";
        cin >> email;
        cout << "Masukkan nomor telepon: ";
        cin >> phone;
        cout << "Masukkan password: ";
        cin >> password;

        User newUser(id, name, email, phone, password);
        users.push_back(newUser);
        cout << "Pendaftaran berhasil!" << endl;
    }

    // Fungsi untuk login
    bool login() {
        string email, password;

        cout << "Masukkan email: ";
        cin >> email;
        cout << "Masukkan password: ";
        cin >> password;

        for (auto& user : users) {
            if (user.email == email && user.password == password) {
                loggedInUser = &user;
                cout << "Login berhasil, selamat datang " << user.name << "!" << endl;
                return true;
            }
        }

        cout << "Email atau password salah." << endl;
        return false;
    }

    // Fungsi untuk menampilkan daftar kendaraan
    void displayVehicles() {
        if (vehicles.empty()) {
            cout << "Tidak ada kendaraan tersedia." << endl;
            return;
        }

        cout << "Daftar Kendaraan Tersedia:" << endl;
        for (auto& vehicle : vehicles) {
            vehicle.displayInfo();
        }
    }

    // Fungsi untuk pemesanan kendaraan
    void makeBooking() {
        if (loggedInUser == nullptr) {
            cout << "Anda harus login terlebih dahulu!" << endl;
            return;
        }

        cout << "Pilih kendaraan untuk memesan (masukkan ID kendaraan): ";
        int vehicleId;
        cin >> vehicleId;

        if (vehicleId < 1 || vehicleId > vehicles.size()) {
            cout << "ID kendaraan tidak valid!" << endl;
            return;
        }

        Vehicle& vehicle = vehicles[vehicleId - 1];
        if (!vehicle.isAvailable) {
            cout << "Kendaraan ini tidak tersedia!" << endl;
            return;
        }

        loggedInUser->addOrder(vehicle.name); // Menambahkan pemesanan ke pengguna
        vehicle.isAvailable = false; // Menandakan kendaraan sudah dipesan
    }

    // Fungsi untuk melihat pemesanan pengguna
    void viewUserOrders() {
        if (loggedInUser == nullptr) {
            cout << "Anda harus login terlebih dahulu!" << endl;
            return;
        }

        loggedInUser->viewOrders(); // Menampilkan pemesanan pengguna
    }
    
    // Fungsi untuk menyimpan data pengguna dan kendaraan ke file CSV
    void saveDataToFile() {
        ofstream userFile("users.csv");
        ofstream vehicleFile("vehicles.csv");
        ofstream orderFile("orders.csv");

        if (!userFile.is_open() || !vehicleFile.is_open() || !orderFile.is_open()) {
            cout << "Error opening file!" << endl;
            return;
        }

        // Menyimpan data pengguna
        for (auto& user : users) {
            user.saveToFile(userFile);
        }

        // Menyimpan data kendaraan
        for (auto& vehicle : vehicles) {
            vehicle.saveToFile(vehicleFile);
        }

        // Menyimpan data pemesanan
        for (auto& user : users) {
            user.saveOrdersToFile(orderFile);
        }

        userFile.close();
        vehicleFile.close();
        orderFile.close();

        cout << "Data berhasil disimpan ke file!" << endl;
    }
    // Struktur untuk data ulasan
    struct Ulasan {
    int idReview;
    int idUser;
    int idKendaraan;
    int rating;
    string komentar;
    };
    
    // Fungsi untuk membaca data dari file CSV
    void loadDataFromFile() {
        ifstream userFile("users.csv");
        ifstream vehicleFile("vehicles.csv");
        ifstream orderFile("orders.csv");

        if (!userFile.is_open() || !vehicleFile.is_open() || !orderFile.is_open()) {
            cout << "Error opening file!" << endl;
            return;
        }

        string line;

        // Membaca data pengguna
        while (getline(userFile, line)) {
            stringstream ss(line);
            string name, email, phone, password;
            int id;

            getline(ss, name, ',');
            getline(ss, email, ',');
            getline(ss, phone, ',');
            getline(ss, password, ',');
            ss >> id;

            users.push_back(User(id, name, email, phone, password));
        }

        // Membaca data kendaraan
        while (getline(vehicleFile, line)) {
            string name;
            double price;
            bool isAvailable;
            int id;

            stringstream ss(line);
            ss >> id;
            ss.ignore(1, ',');
            getline(ss, name, ',');
            ss >> price;
            ss.ignore(1, ',');
            string availability;
            getline(ss, availability);
            isAvailable = (availability == "Tersedia");

            vehicles.push_back(Vehicle(id, name, price));
        }

        // Membaca data pemesanan
        while (getline(orderFile, line)) {
            stringstream ss(line);
            int userId;
            string order;

            ss >> userId;
            ss.ignore(1, ',');
            getline(ss, order);

            for (auto& user : users) {
                if (user.id == userId) {
                    user.orders.push_back(order);
                    break;
                }
            }
        }

        userFile.close();
        vehicleFile.close();
        orderFile.close();
    }
};

int main() {
    System system;

    // Menu sistem
    int choice;
    while (true) {
        cout << "\n===== Sistem Penyewaan Kendaraan =====" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Lihat Daftar Kendaraan" << endl;
        cout << "4. Pesan Kendaraan" << endl;
        cout << "5. Lihat Pemesanan" << endl;
        cout << "6. Simpan Data" << endl;
        cout << "7. Keluar" << endl;
        cout << "Pilih menu: ";
        cin >> choice;

        switch (choice) {
            case 1:
                system.registerUser();
                break;
            case 2:
                if (!system.login()) {
                    cout << "Login gagal, coba lagi." << endl;
                }
                break;
            case 3:
                system.displayVehicles();
                break;
            case 4:
                system.makeBooking();
                break;
            case 5:
                system.viewUserOrders();
                break;
            case 6:
                system.saveDataToFile();
                break;
            case 7:
                cout << "Keluar dari sistem." << endl;
                return 0;
            default:
                cout << "Pilihan tidak valid." << endl;
        }
    }

    return 0;
}

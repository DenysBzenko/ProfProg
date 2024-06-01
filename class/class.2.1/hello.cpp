#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

const std::string FILENAME = "user.txt";

class UserStats {
public:
    void load() {
        std::ifstream infile(FILENAME);
        if (!infile) {
            std::cerr << "Failed to open file for reading.\n";
            return;
        }

        std::string name;
        int count;
        while (infile >> name >> count) {
            stats[name] = count;
        }
        std::cout << "Loaded stats from file.\n";
    }

    void save() const {
        std::ofstream outfile(FILENAME);
        if (!outfile) {
            std::cerr << "Failed to open file for writing.\n";
            return;
        }

        for (const auto& [name, count] : stats) {
            outfile << name << " " << count << "\n";
        }
        std::cout << "Saved stats to file.\n";
    }

    void reset(const std::string& name) {
        if (name == "bread") {
            stats.clear();
            std::cout << "All history cleared.\n";
        } else {
            stats.erase(name);
            std::cout << "Statistics reset for " << name << ".\n";
        }
    }

    void greet(const std::string& name) {
        if (stats.find(name) == stats.end()) {
            stats[name] = 1;
            std::cout << "Welcome, " << name << "!\n";
        } else {
            stats[name]++;
            std::cout << "Hello again(x" << stats[name] << "), " << name << "!\n";
        }
    }

private:
    std::unordered_map<std::string, int> stats;
};

int main(int argc, char* argv[]) {
    std::cout << "Program started.\n";

    if (argc < 2 || argc > 3) {
        std::cerr << "Usage: " << argv[0] << " <name> [delete]\n";
        return 1;
    }

    std::string name = argv[1];
    UserStats userStats;
    userStats.load();

    if (name == "bread" || (argc == 3 && std::string(argv[2]) == "delete")) {
        userStats.reset(name);
    } else {
        userStats.greet(name);
    }

    userStats.save();
    std::cout << "Program finished.\n";
    return 0;
}

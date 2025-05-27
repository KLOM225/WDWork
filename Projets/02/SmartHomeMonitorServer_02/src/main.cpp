#include "Configuration.hpp"
#include <iostream>

int main() {
    try {
        Configuration & config = Configuration::getInstance();
        std::cout << "Server IP: " << config.GetIP() << std::endl;
        std::cout << "Port: " << config.GetPort() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Configuration error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
    
}

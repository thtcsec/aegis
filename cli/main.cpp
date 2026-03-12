#include <iostream>
#include <string>
#include <vector>

void printUsage() {
    std::cout << "Aegis - Secure Systems Language\n\n";
    std::cout << "Usage:\n";
    std::cout << "  aegis build <file.aeg>    Compile Aegis source\n";
    std::cout << "  aegis run <file.aeg>      Run Aegis program\n";
    std::cout << "  aegis check <file.aeg>    Run security analysis\n";
    std::cout << "  aegis scan <target>       Scan target for vulnerabilities\n";
    std::cout << "  aegis -c <code>           Execute Aegis code directly\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage();
        return 1;
    }

    std::string arg1 = argv[1];

    if (arg1 == "build") {
        if (argc < 3) {
            std::cout << "Error: No file specified\n";
            return 1;
        }
        std::cout << "Building " << argv[2] << "...\n";
        // TODO: Implement build
    } else if (arg1 == "run") {
        if (argc < 3) {
            std::cout << "Error: No file specified\n";
            return 1;
        }
        std::cout << "Running " << argv[2] << "...\n";
        // TODO: Implement run
    } else if (arg1 == "check") {
        if (argc < 3) {
            std::cout << "Error: No file specified\n";
            return 1;
        }
        std::cout << "Checking security for " << argv[2] << "...\n";
        // TODO: Implement security check
    } else if (arg1 == "scan") {
        if (argc < 3) {
            std::cout << "Error: No target specified\n";
            return 1;
        }
        std::cout << "Scanning " << argv[2] << "...\n";
        // TODO: Implement scan
    } else if (arg1 == "-c" || arg1 == "--command") {
        if (argc < 3) {
            std::cout << "Error: No code specified\n";
            return 1;
        }
        std::cout << "Executing direct command...\n";
        std::cout << "Code: " << argv[2] << "\n";
        // TODO: Implement direct execution
    } else {
        printUsage();
        return 1;
    }

    return 0;
}

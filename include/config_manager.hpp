#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <iomanip>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std::chrono;
using namespace std::filesystem;

namespace ConfigManager {
    struct ConfigEditor {
        static void createConfig() {
            path configPath{ temp_directory_path() };
            configPath.append("config");
            std::ofstream configFile;

            if (!exists(configPath)) {
                create_directory(configPath);

                configPath.append("Config.txt");
                configFile.open(configPath, std::ios::out);
                configFile.close();
            }
            else {
                configPath.append("Config.txt");
                configFile.open(configPath, std::ios::out);
                configFile.close();
            }
        }

        static void writeConfig(std::string content) {
            path configPath{ temp_directory_path() };
            configPath.append("config/Config.txt");
            std::cout << configPath << std::endl;
            std::ofstream configFile;

            if (!exists(configPath)) {
                createConfig();

                configFile.open(configPath, std::ios::out);
                configFile << content;
                configFile.close();
            } else {
                configFile.open(configPath, std::ios::out);
                configFile << content;
                configFile.close();
            }

        }

        static void appendToConfig(std::string content) {
            path configPath{ temp_directory_path() };
            configPath.append("config/Config.txt");
            std::ofstream configFile;

            if (!exists(configPath)) {
                createConfig();

                configFile.open(configPath, std::ios::out|std::ios::app);
                configFile << content;
                configFile.close();
            } else {
                configFile.open(configPath, std::ios::out|std::ios::app);
                configFile << content;
                configFile.close();
            }
        }

        static std::vector<std::string> readConfig() {
            path configPath{ temp_directory_path() };
            configPath.append("config/Config.txt");
            std::ifstream configFile;
            std::vector<std::string> line_from_files;

            if (!exists(configPath)) {
                createConfig();

                return line_from_files;
            } else {
                configFile.open(configPath);

                std::copy(std::istream_iterator<std::string>(configFile),
                std::istream_iterator<std::string>(), 
                std::back_inserter(line_from_files));

                configFile.close();

                return line_from_files;
            }

            return line_from_files;
        }

        static void removeConfig() {
            path configPath{ temp_directory_path() };
            configPath.append("config/Config.txt");
            std::fstream configFile;

            if (!exists(configPath)) {
                createConfig();
                return;
            } else {
                configFile.open(configPath, std::ios::out|std::ios::trunc);
                configFile.close();
            }
        }
        
    };
}
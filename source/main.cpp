#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <iomanip>
#include <vector>
#include "../include/directory_looker.hpp"
#include "../include/file_mangement.hpp"
#include "../include/config_manager.hpp"

using namespace std::chrono;
using namespace std::filesystem;

// Converts the input from an std::string into an int for a switch-case statment
int convertInputToInt(std::string input) {
    for (auto& c : input) {
        c = tolower(c);
    }

    if (input == "change directory" || input == "cd") return 1;
    else if (input == "create file" || input == "file -c") return 2;
    else if (input == "delete file" || input == "file -d") return 3;
    else if (input == "copy file" || input == "file -C") return 4;
    else if (input == "move file" || input == "file -m") return 5;
    else if (input == "rename file" || input == "file -r") return 6;
    else if (input == "list" || input == "ls") return 7;
    else if (input == "find files" || input == "file -f") return 8;
    else if (input == "edit file" || input == "file -e") return 9;
    else if (input == "help" || input == "h") return 10;
    else return 0;

    return -1;
}

int main(int argc, char** argv) {
    std::vector<std::string> lineFromFiles = ConfigManager::ConfigEditor::readConfig();
    std::string shortcut_path;
    if (!lineFromFiles.empty()) shortcut_path = lineFromFiles[0];

    std::string Input;
    path new_path{ current_path() };
    bool mainLoop = true;

    std::string argument;
    std::stringstream ss;
    if (argc > 1) {
        ss << argv[1];
        ss >> argument;
    }

    if (argc == 1) {
        FileOperations::Directory::list_directories(new_path);

        // Main Loop for the rest of the program
        while (mainLoop) {
            // Gets command input from the user
            std::cout << "Select an option to do (press Q to quit): " << std::endl;
            getline(std::cin, Input);
            std::cout << "Input given: " << Input << std::endl;

            if (Input == "Q" || Input == "q") mainLoop = false; // Quits if the program detects the letter q

            switch (convertInputToInt(Input)) { // If the input is not q, then the input is passed through here
                case 1: { // Change directory
                    std::string file_path_str;
                    std::cout << "Enter the directory to change into (.. to go back): " << std::endl;
                    getline(std::cin, file_path_str);

                    int pos = file_path_str.find("~");
                    
                    if (pos >= 0) {
                        if (!lineFromFiles.empty()) {
                            try {
                                int vectorPos = shortcut_path.find("=");
                                shortcut_path = shortcut_path.substr(0, vectorPos);

                                std::string file_path_sub = file_path_str.substr(pos + 1);

                                path new_new_path{ current_path() };
                                new_new_path.append(shortcut_path + file_path_sub);
                                current_path(new_new_path);

                                FileOperations::Directory::list_directories(current_path());
                            } catch (std::exception& e) {
                                std::cerr << "ERROR: " << e.what() << std::endl;
                            }

                        } else {
                            std::cerr << "ERROR: No home directory shortcut found. Please set it up using the config setup tool by doing ./FileManager.out -s or --Setup" << std::endl;
                        }
                    } else if (pos == -1){
                        path new_new_path{ current_path() };
                        new_new_path.append(std::move(file_path_str));
                        current_path(new_new_path);

                        FileOperations::Directory::list_directories(current_path());
                    }

                    break;
                }

                case 2: { // Create file
                    std::string file_name;
                    std::string content;

                    std::cout << "Enter file name here: " << std::endl;
                    getline(std::cin, file_name);
                    std::cout << "Enter content here: " << std::endl;
                    getline(std::cin, content);
                    FileOperations::FileCreate::createFile(std::move(file_name), std::move(content));

                    FileOperations::Directory::list_directories(current_path());
                    break;
                }
                
                case 3: { // Delete file
                    std::string file_path_name;

                    std::cout << "Enter file name here: " << std::endl;
                    getline(std::cin, file_path_name);
                    path del_path{ current_path() };
                    del_path.append(file_path_name);

                    FileOperations::FileDelete::deleteFile(std::move(del_path));

                    FileOperations::Directory::list_directories(current_path());
                    break;
                }

                case 4: { // Copy file
                    std::string first_file_name;
                    std::string second_file_path;

                    std::cout << "Enter the first file name here: " << std::endl;
                    getline(std::cin, first_file_name);
                    std::cout << "Enter the second path to copy to: " << std::endl;
                    getline(std::cin, second_file_path);

                    path first_path{ current_path() };
                    first_path.append(first_file_name);
                    path second_path{ second_file_path };
                    second_path.append(first_file_name);

                    FileOperations::FileMove::copyFile(std::move(first_path), std::move(second_path));

                    FileOperations::Directory::list_directories(current_path());
                    break;
                }

                case 5: { // Move file
                    std::string first_file_name;
                    std::string second_file_path;

                    std::cout << "Enter the first file name here: " << std::endl;
                    getline(std::cin, first_file_name);
                    std::cout << "Enter the second path to move to: " << std::endl;
                    getline(std::cin, second_file_path);

                    path first_path{ current_path() };
                    first_path.append(first_file_name);
                    path second_path{ second_file_path };
                    second_path.append(first_file_name);

                    FileOperations::FileMove::moveFile(std::move(first_path), std::move(second_path));

                    FileOperations::Directory::list_directories(current_path());
                    break;
                }

                case 6: { // Rename file
                    std::string path_to_rename_file_str;
                    std::string rename_text;

                    std::cout << "Enter the file you would like to rename: " << std::endl;
                    getline(std::cin, path_to_rename_file_str);
                    std::cout << "Enter the name you want to rename the file to: " << std::endl;
                    getline(std::cin, rename_text);

                    path first_path{ current_path() };
                    first_path.append(path_to_rename_file_str);
                    
                    FileOperations::FileRename::renameFile(std::move(first_path), std::move(rename_text));

                    FileOperations::Directory::list_directories(current_path());
                    break;
                }

                case 7: // List
                FileOperations::Directory::list_directories(current_path());
                break;
                
                case 8: { // Find files
                    std::string extension_to_look;
                    
                    std::cout << "Enter the extension you want to look for: " << std::endl;
                    getline(std::cin, extension_to_look);

                    FileOperations::Directory::find_files_with_extension(current_path(), extension_to_look);

                    break;
                }

                case 9:
                std::cout << "Text editor coming soon" << std::endl;
                break;

                case 10: // Help
                std::cout << "File Manager by EmreTech:" << "\n\tchange directory | Change the current directory (.. to go back)" << 
                "\n\tcreate file | Creates almost any file (i.e. txt or xml)" << "\n\tdelete file | Deletes a file" << 
                "\n\tmove file | Moves one file to another location" << "\n\tcopy file | Copies one file to another location" << 
                "\n\trename file | Renames a file to another name" << 
                "\n\tlist | Lists all files in current directory (called when you change current directories)" << 
                "\n\tedit file | Edits almost any file (i.e. txt or xml)" << 
                "\n\tfind files | Finds a file with a certain extension" << std::endl;
                break;

            }

        }
    } else if (argument == "-s" || argument == "--Setup") { // If the setup mode is enabled
        bool setupLoop = true;
        int setup_function;
        ConfigManager::ConfigEditor::createConfig();

        while (setupLoop) { // Setup loop for the rest of the program
            std::cout << "Welcome to config setup! Type in a command below (q to quit): " << std::endl;
            getline(std::cin, Input);

            for (auto& c : Input) c = tolower(c);

            if (Input == "q") break;
            
            if (Input == "add home directory shortcut") setup_function = 1;
            else if (Input == "change home directory shortcut") setup_function = 2;
            else if (Input == "remove home directory shortcut") setup_function = 3;
            else if (Input == "help") setup_function = 4;
            else setup_function = 0;
            

            switch (setup_function) {
                case 1: {
                    std::string setup_input = "home_directory=";
                    std::cout << "Enter the path for your home directory: " << std::endl;
                    getline(std::cin, setup_input);

                    ConfigManager::ConfigEditor::appendToConfig(setup_input);
                    break;
                }

                case 2: {
                    std::string setup_input;
                    std::cout << "Enter the new path for your home directory:" << std::endl;
                    getline(std::cin, setup_input);

                    setup_input += "=home_directory";

                    ConfigManager::ConfigEditor::removeConfig();
                    ConfigManager::ConfigEditor::writeConfig(setup_input);
                    break;
                }

                case 3: 
                ConfigManager::ConfigEditor::removeConfig();
                break;

                case 4:
                std::cout << "Config Setup for File Manager by EmreTech" << 
                "\n\tAdd home directory shortcut | Adds a shortcut to your home directory (use ~ to access the home directory)" <<
                "\n\tChange home directory shortcut | Clears the config and changes the home directory shortcut" <<
                "\n\tRemove home directory shortcut | Removes the home directory shortcut" << std::endl;
                break;
                
            }

        }
    }

    return EXIT_SUCCESS; 
}
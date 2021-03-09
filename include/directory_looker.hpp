#pragma once

#include <iostream>
#include <filesystem>
#include <vector>
#include <iomanip>

using namespace std::chrono;
using namespace std::filesystem;

namespace FileOperations {
    struct Directory {
        Directory(){}  

        // Describes the content of a directory entry from a directory iterator (code from C++ Crash Course)
        static void describe(const directory_entry& entry) {
         try {
            if(entry.is_directory()) {
                std::cout << "           *";
            } else {
                std::cout << std::setw(12) << entry.file_size();
            }
            const auto lw_time = duration_cast<seconds>(entry.last_write_time().time_since_epoch());
            std::cout << std::setw(12) << lw_time.count() << " " << entry.path().filename().string() << "\n";
            } catch(const std::exception& e) {
                std::cout << "Error accessing " << entry.path().string() << ": " << e.what() << std::endl;
            }
        }

        // Lists all files and directories under a certain path (code from C++ Crash Course)
        static void list_directories(const path p) {
            std::cout << p.native() << std::endl;

            std::cout << "Size         Last Write  Name\n";
            std::cout << "------------ ----------- ------------\n";
            for(const auto& entry : directory_iterator{ p }) describe(entry);
        }

        // Looks at a certain directory to find files with a matching extension
        static void find_files_with_extension(const path p, const std::string extension) {
            size_t files_found{ 0 };
            size_t files_looked{ 0 };
            std::vector<std::string> names_of_files_found{ "" };

            std::cout << "Finding files with extension " << extension << "..." << std::endl;

            for (const auto& entry : directory_iterator{ p }) {
                files_looked++;
                if (entry.path().extension() == extension) {
                    files_found++;
                    names_of_files_found.emplace_back(entry.path().filename().native());

                    std::cout << "Found file " << entry.path().filename().native() << ". " << files_found << " file(s) found so far." << std::endl;
                }
            }

            std::cout << "File(s) with the following names were found: " << "\n";

            for (size_t x{ 0 }; x < names_of_files_found.size(); x++) {
                std::cout << "\t" << names_of_files_found[x] << std::endl;
            }

            std::cout << "\nLooked at " << files_looked << " files." << std::endl;
            names_of_files_found.clear();
            names_of_files_found.shrink_to_fit();
        }
    };
}
#pragma once

#include <iostream>
#include <filesystem>
#include <fstream>
#include <iomanip>

using namespace std::chrono;
using namespace std::filesystem;

namespace FileOperations {
    struct FileCreate {
        FileCreate(){}

        // Creates a file with some sample content using ofstream
        static void createFile(std::string file_name, std::string content) {
            std::ofstream File(file_name);
            File << content;
            File.close();
        }
    };

    struct FileDelete {
        FileDelete(){}

        // Deletes a file at the specifed path
        static void deleteFile(path file_path) {
            remove(file_path);
        }
    };

    struct FileMove {
        FileMove(){}

        // Copies one file to another location
        static void copyFile(path first_file, path second_file) {
            copy(first_file, second_file);
        }

        // Copies one file to another location with copying options
        static void copyFile(path first_file, path second_file, copy_options options) {
            copy(first_file, second_file, options);
        }

        // Moves one file to another location
        static void moveFile(path first_file, path second_file) {
            copy(first_file, second_file);
            remove(first_file);
        }

        // Moves one file to another location with copying options
        static void moveFile(path first_file, path second_file, copy_options options) {
            copy(first_file, second_file, options);
            remove(first_file);
        }
    };

    struct FileRename {
        FileRename(){}

        // Renames a file to another name
        static void renameFile(path file_to_rename, std::string rename_to) {
            rename(file_to_rename, rename_to);
        }
    };
}
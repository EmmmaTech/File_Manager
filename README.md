# File_Manager
This is a simple, Terminal inspired File Manager made completely inside of C++. You can do a lot of file-related actions, like creating files, deleting files, copying/moving files, and renaming files. 
Editing files feature is coming soon just because how complicated a text editor is.

# Compiling

To compile this program, you need CMake and some sort of C++ compiler that supports the C++17 standard. The exact compilation instructions can differ from Windows to Unix-based operating systems, so Google might be your best bet if it doesn't work.

## macOS

You first need to install the compliation tools needed for this program. You can do that with the command
```bash
xcode-select --install
```

Once it is done installing, you need to install CMake. This can be installed via their website or via Homebrew if it's installed. To install with Homebrew, use
```bash
brew install cmake
```

You can now ``git clone`` this repo to any folder that is easily accessible and use the Terminal to change into it. Now run the commands below:
```bash
mkdir build && cd build
cmake ..
make
```

It should work with no errors. If you get errors, report it to the Issue Tracker.

## Ubuntu 20.04 and above

#### These instructions might work with older versions of Ubuntu, haven't completely checked

You first need to install the complication tools needed for this program. You can do that with the command
```bash
sudo apt update && sudo apt install build-essential
```

Once it is done installing, you need to install CMake. The recommended way is by using apt again. Install by doing:
```bash
sudo apt install cmake
```

You can now ``git clone`` this repo to any folder that is easily accessible and use the Terminal to change into it. Now run the commands below:
```bash
mkdir build && cd build
cmake ..
make
```

It should work with no errors. If you get errors, report it to the Issue Tracker.

# License

This repo uses the MIT License. Read the LICENSE file for more details.

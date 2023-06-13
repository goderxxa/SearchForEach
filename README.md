# -----------------------SearchForEach----------------------
### - It searches for words in text files.
### - It can index documents.
### - It can provide relevant documents based on your requests.
### - It can make output ANSWERS.JSON with relevant documents.


#### Windows build
##### -install mingw compiler
##### -install system variables path to cmake.exe folder

##### open CMD 
##### cd SearchForEach
##### mkdir build
##### cd build
##### -G "CodeBlocks - MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..
##### cmake --build.

### Programm consists of that files 
config.json,
requests.json,
SearchForEach.exe,
Test (folder)
____
### How to use it

#### Programm has simple 3 commands
##### '-1' - exit
##### '-2' - show dictionary
##### '-3' - update text base

##### - use a REQUESTS.JSON file to add or remove requests.
##### - Place text files in the "Test" folder (or any other folder paths for searching files can be added to the CONFIG.JSON field "files" )
##### - You can obtain the relevance of a request by entering it in the command line.

The project uses the Nlohmann Json library to work with JSON files.
It uses googletests to test this progect.
It also utilizes threads to improve indexing efficiency.
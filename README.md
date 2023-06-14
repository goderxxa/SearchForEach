# -----------------------SearchForEach----------------------
### - It searches for words in text files.
### - It can index documents.
### - It can provide relevant documents based on your requests.
### - It can make output ANSWERS.JSON with relevant documents.


#### Windows build
##### -install mingw compiler
##### -install cmake
##### -install system variables path to cmake.exe folder

##### open CMD 
##### cd SearchForEach
##### mkdir build
##### cd build
##### cmake -G "CodeBlocks - MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..
##### cmake --build .

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

#### Youtube video how to build progect
[![build video](https://github.com/goderxxa/SearchForEach/blob/master/prg/video.png)](https://www.youtube.com/watch?v=DfH6WQ6D14Q)

## Add requests to requests.json
## Add filepaths to config.json (/test and /test2)
#### Request 1 "milk water", "sugar"
### result
![test1 image](https://github.com/goderxxa/SearchForEach/blob/master/prg/test%201.png)
____
#### Request 2 "moscow is the capital of russia"
### result
![test2 image](https://github.com/goderxxa/SearchForEach/blob/master/prg/test%202.png)

### Test progect youtube video
[![build video](https://github.com/goderxxa/SearchForEach/blob/master/prg/video.png)](https://www.youtube.com/watch?v=-aQmf-QL6cs)

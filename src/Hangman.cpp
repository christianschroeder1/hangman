#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

string failstates[] = { R"(         


          
          
          
  
 
----------------)",R"(

         
          
          
          
  / \
 |   |
----------------)",R"(

   |      
   |       
   |       
   |       
  / \
 |   |
----------------)" ,R"(
   +-------+
   |/      
   |       
   |       
   |       
  / \
 |   |
----------------)" ,R"(
   +-------+
   |/      |
   |       
   |       
   |       
  / \
 |   |
----------------)" ,R"(
   +-------+
   |/      |
   |       O
   |       
   |       
  / \
 |   |
----------------)" ,R"(
   +-------+
   |/      |
   |       O
   |       |
   |       
  / \
 |   |
----------------)" ,R"(
   +-------+
   |/      |
   |       O
   |       |
   |      / 
  / \
 |   |
----------------)" ,R"(
   +-------+
   |/      |
   |       O
   |       |
   |      / \
  / \
 |   |
----------------)" ,R"(
   +-------+
   |/      |
   |       O
   |      /|
   |      / \
  / \
 |   |
----------------)" ,R"(
   +-------+
   |/      |
   |       O
   |      /|\
   |      / \
  / \
 |   |
----------------)"};
string win = R"( 
      /$$      /$$       /$$$$$$       /$$   /$$
     | $$  /$ | $$      |_  $$_/      | $$$ | $$
     | $$ /$$$| $$        | $$        | $$$$| $$
     | $$/$$ $$ $$        | $$        | $$ $$ $$
     | $$$$_  $$$$        | $$        | $$  $$$$
     | $$$/ \  $$$        | $$        | $$\  $$$
     | $$/   \  $$       /$$$$$$      | $$ \  $$
     |__/     \__/      |______/      |__/  \__/
)";

string title = R"(

      /$$   /$$        /$$$$$$        /$$   /$$        /$$$$$$        /$$      /$$        /$$$$$$        /$$   /$$
     | $$  | $$       /$$__  $$      | $$$ | $$       /$$__  $$      | $$$    /$$$       /$$__  $$      | $$$ | $$
     | $$  | $$      | $$  \ $$      | $$$$| $$      | $$  \__/      | $$$$  /$$$$      | $$  \ $$      | $$$$| $$
     | $$$$$$$$      | $$$$$$$$      | $$ $$ $$      | $$ /$$$$      | $$ $$/$$ $$      | $$$$$$$$      | $$ $$ $$
     | $$__  $$   -  | $$__  $$   -  | $$  $$$$   -  | $$|_  $$   -  | $$  $$$| $$   -  | $$__  $$   -  | $$  $$$$
     | $$  | $$      | $$  | $$      | $$\  $$$      | $$  \ $$      | $$\  $ | $$      | $$  | $$      | $$\  $$$
     | $$  | $$      | $$  | $$      | $$ \  $$      |  $$$$$$/      | $$ \/  | $$      | $$  | $$      | $$ \  $$
     |__/  |__/      |__/  |__/      |__/  \__/       \______/       |__/     |__/      |__/  |__/      |__/  \__/
                                                                                                                                                                                                 
)";
string looser = R"(
      /$$        /$$$$$$   /$$$$$$   /$$$$$$  /$$$$$$$$ /$$$$$$$  /$$
     | $$       /$$__  $$ /$$__  $$ /$$__  $$| $$_____/| $$__  $$| $$
     | $$      | $$  \ $$| $$  \ $$| $$  \__/| $$      | $$  \ $$| $$
     | $$      | $$  | $$| $$  | $$|  $$$$$$ | $$$$$   | $$$$$$$/| $$
     | $$      | $$  | $$| $$  | $$ \____  $$| $$__/   | $$__  $$|__/
     | $$      | $$  | $$| $$  | $$ /$$  \ $$| $$      | $$  \ $$    
     | $$$$$$$$|  $$$$$$/|  $$$$$$/|  $$$$$$/| $$$$$$$$| $$  | $$ /$$
     |________/ \______/  \______/  \______/ |________/|__/  |__/|__/
)";

    


vector<string> allwords = { "apple", "banana", "cat", "dog", "elephant", "frog", "grape", "house", "ice", "jungle", "kite", "lion", "mountain", "night", "ocean", "piano", "queen", "river", "sun", "tree", "umbrella", "violet", "window", "xylophone", "yacht", "zebra", "air", "book", "cloud", "door", "egg", "fire", "garden", "hat", "island", "juice", "key", "lake", "moon", "nest", "orange", "pen", "quilt", "road", "star", "train", "unicorn", "village", "water", "xenon", "yarn", "zone", "actor", "ball", "circle", "desk", "earth", "forest", "gold", "hill", "idea", "jacket", "king", "leaf", "music", "note", "oasis", "paper", "queen", "rose", "song", "table", "unit", "voice", "wall", "x-ray", "yard", "zeal", "angle", "bridge", "cloud", "dance", "engine", "flower", "game", "heart", "iceberg", "jewel", "knight", "light", "mirror", "needle", "ocean", "puzzle", "quartz", "rocket", "stone", "tiger", "umbrella", "valley", "whale", "xylophone", "yogurt", "zinc" };

string allowedletters[] = { "a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z" };
string word = "searchedword";
string displayword = "";
string message = "";
string wrongletters = "";

int fails = 0;
bool playing = true;



void Readwordsfromfile() {

    //reads the file wordlist.txt and adds the words to the list

    ifstream MyReadFile("wordlist.txt");
    if (!MyReadFile) {
        message = "could not read wordlist.txt. using default words.";
        return;
    }
    
    allwords.clear();
    string line;
    while (getline(MyReadFile, line)) {
        allwords.push_back(line);
    }

    MyReadFile.close();
}

string Displaywrongletters() {

    //displays the list of letters that the player has already tried. seperated by ",".


    string result;
    for (int i = 0; i < wrongletters.length(); i++) {
        if (i > 0)
            result += ",";
        result += wrongletters[i];
    }
    return result;
}

bool falseinput(string input) {

    //checks whether the letter entered by the player belongs to the list of allowed letters
    bool found = false;
    for (const std::string& letter : allowedletters) {
        if (input == letter) {
            found = true;
            break;
        }
    }

    if (!found)
        cout << "please pick a letter \n";

    return found;
}

void Clearscreen() {

//Clears the console on different platforms

#ifdef _WIN32
    system("cls"); // nur auf Windows
#elif __linux__
    system("clear");
#elif __APPLE__
    system("clear");
#endif

}

bool Alreadytried(char letter) {

    //checks if the player already tried a letter.
    bool found = false;
    for (int i = 0; i < wrongletters.length(); i++) {
        if (letter == wrongletters[i]) {
            found = true;
            message = "you already tried this one";
            break;
        }
    }

    return found;

}

void Setup() {

    Readwordsfromfile();

    fails = 0;
    wrongletters = "";

    //Randomly picks a word from the wordlist
    std::srand(static_cast<unsigned>(time(nullptr)));
    int index = std::rand() % allwords.size();
    word = allwords[index];

    displayword = "";
    for (int i = 0; i < word.length(); i++) {
        displayword += "_";
    }

    cout << title;
    cout << "PRESS ENTER TO PLAY:";


    cin.ignore();



}

void Continuescreen() {

    //Asks the player if they want to keep playing
    cout << "Play again? (y/n)";
    string answer;
    cin >> answer;
    if (answer == "y")
        Setup();
    else
        playing = false;

}

void Helpscreen() {

    

    string helpstring = R"(
#######################################################################
#                                                                     #
#                                 HELP                                #
#                                                                     #
#######################################################################
#   Try to guess the word by typing in one letter at a time.          #
#   you need to guess the whole word before the acii graphic of a     #
#   hanging person is been drawn completely.                          #
#                                                                     #
#   Only type in lower case letters. no numbers or other symbols.     #
#   have fun.                                                         #
#                                                                     #
#######################################################################
)";
    Clearscreen();
    cout << helpstring;
    cin.ignore();

}

void Checkinput(string answer) {

    //processes the playerinput

    if (answer == "help") {
        Helpscreen();
    }
    if (answer == "quit") {
        playing = false;
    }


    if (!falseinput(answer)) {
        message = "please use only lower case letters.";
        cin.ignore();
    }

    else {        
        if (!Alreadytried(answer[0])) {

            bool isinword = false;
            for (int i = 0; i < word.length(); i++) {
                if (answer[0] == word[i]) {
                    displayword[i] = answer[0];
                    isinword = true;
                }
            }

            if (!isinword) {
                wrongletters += answer[0];
                fails++;

                if (fails >= 11) {
                    Clearscreen();
                    cout << looser;
                    cout << "\n the word was: \n";
                    cout << word;
                    cout << "\n\n\n";
                    Continuescreen();

                }
            }

            if (displayword == word) {
                Clearscreen();
                cout << win;
                cout << "\n\n";
                cout << "Yay, you won!\n\n";
                cout << "The word was:\n";
                cout << displayword;
                cout << "\n\n\n\n\n";
                Continuescreen();
            }
        }

    }
}

void Mainloop() {

    Clearscreen();
    cout << "Guess the word.\n";
    cout << failstates[fails];
    cout << "\n\n";
    cout << "Word: "+displayword;
    cout << "\n";
    cout << "wrong: "+ Displaywrongletters();
    cout << "\n\n";
    cout << message;
    cout << "\n\n\n";

    cout << "type in a letter: ";
    string answer;
    cin >> answer;

    message = "";
    Checkinput(answer);




}

int main() {

    Setup();
    //Setup

    //round
    while (playing) {
        Mainloop();


        

    }
}
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <map>

int main(int argc, char**argv) {
    std::string param;
    size_t pos;
    int max_value = 50;
    std::string high_scores_filename = "high_scores.txt";
    std::string userName = "";
    std::map<std::string, int> bestResults;

    std::ifstream in_file{high_scores_filename};
    if (in_file.is_open()) {
        std::string line;
        int attempts, tmpAttempts;
        while (true) {
            in_file >> line;
            in_file >> userName;
            in_file >> line;
            in_file >> attempts;
            if(bestResults.count(userName) == 0) {
                bestResults[userName] = attempts;
            } else {
                tmpAttempts = bestResults[userName];
                if(tmpAttempts > attempts)
                    bestResults[userName] = attempts;
            }
            in_file.ignore(1000, '\n');
            if (in_file.fail()) {
                break;
            }
        }
    }

    for(int i = 1; i<argc; i++) {
        param = argv[i];
        if((pos = param.find("-max=")) != std::string::npos) {
            std::string tmp = param.substr(pos + 5, param.length());
            max_value = std::stoi(tmp);
            std::cout << "max value is " << max_value << "\n";
        }
        if(param == "-table") {
            if(bestResults.size() > 0) {
                std::cout << "High scores table:" << std::endl;

                for(auto it = bestResults.begin(); it != bestResults.end(); it++) {
                    // Print the information to the screen
                    std::cout << "Username: " << it->first << " attempts: " << it->second << std::endl;
                }
            } else {
                std::cout << "There are no file with results or cannot read file: " << high_scores_filename << "\n";
            }

            return 0;
        }
    }

    std::cout << "Hello, input your name:\n";

    std::cin >> userName;

    std::srand(std::time(nullptr));
    const int random_value = std::rand() % max_value;

    int i = 0;
    int guessNumber;

    do {
        i++;
        std::cout << "Input your guess number[" << i << "]:\n";
        std::cin >> guessNumber;
        if(guessNumber == -1)
            break;
        if(guessNumber < random_value)
            std::cout << "Your number less than random\n";
        else if(guessNumber > random_value)
            std::cout << "Your number is bigger than random\n";
    } while (guessNumber != random_value);

    if(guessNumber == random_value) {
        std::cout << "Congratulation, " << userName << ", the number is: " << random_value << "\n";
        std::cout << "Your attempts count: " << i << "\n";
        std::time_t timeRes = std::time(nullptr);

        std::ofstream out_file{high_scores_filename, std::ios_base::app};
        if (!out_file.is_open()) {
			std::cout << "Failed to open file for write: " << high_scores_filename << "!" << std::endl;
			return -1;
		}
        out_file << "Name: " << userName << " attempts: " << i << " date: " << std::ctime(&timeRes);
    } else
        std::cout << "You break game";
}

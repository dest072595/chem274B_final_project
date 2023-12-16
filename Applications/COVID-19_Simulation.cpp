#include "../Include/Cellular_Automata.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

struct Person{
    int state;
    int age;
    int step;
    int toRecover;
    int toHealthy;
    int toSick;
    int toDead;
};

// enum State{
//     dead;
//     recovered;
//     healthy;

// };

// template class Cellular_Automata<Person>;
bool checkSick3(std::array<std::array<Person, 3>, 3> Neighborhood, std::string type) {

    // if not type "full" than cross performed
    if(Neighborhood[0][1].state == 2 or
       Neighborhood[1][0].state == 2 or
       Neighborhood[1][2].state == 2 or
       Neighborhood[2][1].state == 2) {
        if(type == "full") {
            if(Neighborhood[0][0].state == 2 or
            Neighborhood[0][2].state == 2 or
            Neighborhood[2][0].state == 2 or
            Neighborhood[2][2].state == 2) {
                return true;
            }
        } else {
            return true;
        }
    } 
    return false;
    
}

Person superSpread3(std::array<std::array<Person, 3>, 3> Neighborhood, std::string neighborType) {
    // if dead, stay dead
    if(Neighborhood[1][1].state == 3) {
        return Neighborhood[1][1];
    } 
    // if neighbor sick, make sick
    else if(checkSick3(Neighborhood, neighborType)) {
        Neighborhood[1][1].state ++;
    }
    return Neighborhood[1][1];
}

std::function<Person(std::array<std::array<Person,3>,3>)> superSpread3Wrapped(std::string neighborhoodType) {
    // return neighborhoodType->Person {
    return [neighborhoodType](std::array<std::array<Person,3>,3> Neighborhood)->Person {
        return superSpread3(Neighborhood, neighborhoodType);
    };
}

Person specifySteps3(std::array<std::array<Person, 3>, 3> Neighborhood, std::string neighborType) {
    // if dead, stay dead
        if(Neighborhood[1][1].state == 3) {
            return Neighborhood[1][1];
        } 
        // if neighbor sick, make worse
        else if(checkSick3(Neighborhood, neighborType)) {
            Neighborhood[1][1].step++;
            // Check threshold to see progression
            if(Neighborhood[1][1].state == 0 & Neighborhood[1][1].step > Neighborhood[1][1].toHealthy) {
                Neighborhood[1][1].state++;
                Neighborhood[1][1].step = 0;
            } else if(Neighborhood[1][1].state == 1 & Neighborhood[1][1].step > Neighborhood[1][1].toSick) {
                Neighborhood[1][1].state++;
                Neighborhood[1][1].step = 0;
            } else if(Neighborhood[1][1].state == 2 & Neighborhood[1][1].step > Neighborhood[1][1].toDead) {
                Neighborhood[1][1].state++;
                Neighborhood[1][1].step = 0;
            }
            return Neighborhood[1][1];


        } // if no sick, recover if old enough
        else if(Neighborhood[1][1].state == 2 & Neighborhood[1][1].step >= Neighborhood[1][1].toRecover) {
            Neighborhood[1][1].state = 0;
            Neighborhood[1][1].step = 0;
        }
        return Neighborhood[1][1];
}

std::function<Person(std::array<std::array<Person,3>,3>)> specifySteps3Wrapped(std::string neighborhoodType) {
    // return neighborhoodType->Person {
    return [neighborhoodType](std::array<std::array<Person,3>,3> Neighborhood)->Person {
        return specifySteps3(Neighborhood, neighborhoodType);
    };
}

int main(void) {
    std::string line, test, var, neighborhood, rule;
    int  numSteps, outputFreq, height, width, stat, count;
    std::function<Person(std::array<std::array<Person,3>,3>)> ruleFunc;
    
    std::vector<std::vector<Person>> initBoard;
    
    std::ifstream initState("../Applications/input_file.txt");
    
    count = 0;
    if(initState.is_open()) {
        // std::cout << var << std::endl;
        while(!initState.eof()) {
            while(std::getline(initState, line)) {
                std::istringstream iss(line);
                iss >> test;
                if(test == "//") {
                    iss >> var;
                } else {
                    std::istringstream iss(line);
                    if(var == "steps") {
                        iss >> numSteps;

                    } else if(var == "freq") {
                        iss >> outputFreq;

                    } else if(var == "height") {
                        iss >> height;

                    } else if(var == "width") {
                        iss >> width;

                        // Initialize initBoard with Person objects
                        for(int i=0; i<width; i++) {
                            std::vector<Person> pvec;
                            initBoard.push_back(pvec);
                            for(int ii=0; ii<height; ii++) {
                                Person p;
                                initBoard[i].push_back(p);
                            }
                        }

                    } else if (var == "neighborhood") {
                        iss >> neighborhood;
                        
                    } else if (var == "rule") {
                        iss >> rule;

                        if(rule == "superSpread") {
                            ruleFunc = superSpread3Wrapped(neighborhood);

                        } 
                        // else if(rule == "specifySteps") {
                        //     ruleFunc = superSpread3Wrapped(neighborhood)
                        // }
                        
                    } else {
                        for(int i=0; i<width; i++) {
                            iss >> stat;
                            std::cout << stat << " " << count << " " << i << std::endl;
                            if(var == "state") {
                                initBoard.at(count).at(i).state = stat;
                            } else if (var == "age") {
                                initBoard.at(count).at(i).age = stat;
                            } else if (var == "toRecover") {
                                initBoard.at(count).at(i).toRecover = stat;
                            } else if (var == "toHealthy") {
                                initBoard.at(count).at(i).toHealthy = stat;
                            } else if (var == "toSick") {
                                initBoard.at(count).at(i).toSick = stat;
                            } else if (var == "toDead") {
                                initBoard.at(count).at(i).toDead = stat;
                            }
                        }
                        count ++;
                        if(count == height) {
                            count = 0;
                            // std::cout << "Filled '" << var << "'" << std::endl;
                        }

                    
                    }
                }

                std::cout << var << std::endl;
            }
        }
    } else {
        std::cout << "ERROR LOADING FILE" << std::endl;
    }
    initState.close();
    // create update rule 
    auto outOfBoundsRule = PeriodicBoundaryRule<Person>();
    
    // Testing
    std::cout << "before loop" << std::endl;
    for(int i=0; i<height; i++) {
        for(int ii=0; ii<width; ii++) {
            std::cout << initBoard.at(i).at(ii).state << " ";
        }
        std::cout << std::endl;
    }

    Cellular_Automata<Person, 3, 3> board(initBoard, ruleFunc, outOfBoundsRule);
    
    std::cout << "Initial state set. Running simmulation" << std::endl;
    // Run the simulation
    count = 1;
    for(int i=0; i<numSteps; i++) {
        
        if(count == outputFreq) {
            count = 0;
            // Create output file
            std::string filename;
            filename = "../Utils/Visualization/Data/" + std::to_string(i) + ".csv";
            std::ofstream of(filename);

            // Create current state board
            std::vector<std::vector<Person>> currState;
            currState = board.getState();
            if(of.is_open()) {
                // Loop through board and output state attribute.
                for(int h=0; h<height; h++) {
                    for(int w=0; w<width; w++) {
                        of << currState.at(h).at(w).state << ", ";
                    }
                    of << std::endl;
                } 
            } else {
                std::cout << "ERROR OUTFILE NOT OPEN" << std::endl;
            }
            
        }

        board.update();
        count++;
    }
    // std::array<std::array<>> updateRules; // function takes array and returns single value 
    // std::vector<std::vector<Person, 3> 3> outOfBoundsRule;
}

// struct Person{
//     int state;
//     int age;
//     int step;
//     int toRecover; # Condense these to one
//     int toHealthy;
//     int toSick;
//     int toDead;
// };


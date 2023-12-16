// Chem 274B: Software Engineering Fundamentals for
//            Molecular Sciences  
// 
// Group 11 
//
// This is file is a simple demonstrator and tester of the Cellular_Automata 
// With a custom struct and update rules
// It shows the how to create and exercise cellular automata
// It shows examples of provided rules and how they behave
// As well as how to construct your own more complicated behavior

#include "Cellular_Automata.h"

struct Person{
    char health = 'h'; 
};

void print_state(const std::vector<std::vector<Person>>& state){
    for(auto vec : state){
        for(auto p : vec){
            std::cout << p.health << " "; 
        }
        std::cout << std::endl;
    }
    std::cout << std::endl; 
}

int main(){
    // rows of the initial state 
    constexpr size_t rows = 5; 
    // columns of the inital state
    constexpr size_t cols = 8; 
    // rows in the neighborhood
    constexpr size_t n_rows = 3; 
    // columns in the neighborhood
    constexpr size_t n_cols  = 3; 

    // create a 4 row by 5 column initial state
    std::vector<std::vector<Person>> initial_state (rows, std::vector<Person>(cols, Person())); 
    initial_state.at(0).at(0) = Person{'c'};
    initial_state.at(3).at(5) = Person{'c'};
    initial_state.at(4).at(2) = Person{'c'};
    initial_state.at(0).at(3) = Person{'q'};
    initial_state.at(2).at(1) = Person{'q'};


    // create update rule 
    std::function<Person (const std::array<std::array<Person, n_cols>, n_rows>) > updateRule = [](const std::array<std::array<Person, n_cols>, n_rows> neighborhood)-> Person 
    {   
        Person p = neighborhood.at((n_rows - 1) /2).at((n_cols - 1) /2);
    
        Person r; 
        if (p.health == 'h')
            r.health = 'c';
        else 
            r.health = 'q' ;
        
        if (neighborhood.at(0).at(1).health == 'q')
            r.health = 'h';
        return r;

    }; 
    
    // create update rule 
    auto outOfBoundsRule = PeriodicBoundaryRule<Person>;

    Cellular_Automata<Person, n_rows, n_cols> CA (
        initial_state, 
        updateRule, 
        outOfBoundsRule
    );

    for (int i = 0; i < 6; i++){
        print_state(CA.getState()); 
        CA.update();   
    }
   
    return 0; 
}
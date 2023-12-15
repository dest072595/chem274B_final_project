#include "Cellular_Automata.h"

struct Person{
    char health = 'h'; 
};

void print_state(std::vector<std::vector<Person>> state){
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
    constexpr size_t rows = 2; 
    // columns of the inital state
    constexpr size_t cols = 3; 
    // rows in the neighborhood
    constexpr size_t n_rows = 3; 
    // columns in the neighborhood
    constexpr size_t n_cols  = 3; 

    // create a 4 row by 5 column initial state
    std::vector<std::vector<Person>> initial_state (rows, std::vector<Person>(cols, Person())); 

    // create update rule 
        // This rule replaces everyone with a regular person
    std::function<Person (const std::array<std::array<Person, n_cols>, n_rows>&) > updateRule = [](const std::array<std::array<Person, n_cols>, n_rows>& arr)-> Person {return Person();}; 
    

    // create boundary rule 
        // This rule does nothing
    std::function<void(std::vector<std::vector<Person>>&, size_t, size_t)> outOfBoundsRule = [](std::vector<std::vector<Person>>& state, size_t rpad, size_t cpad)->void{};

    print_state(initial_state);

    Cellular_Automata<Person, n_rows, n_cols> CAP (
        initial_state, 
        updateRule, 
        outOfBoundsRule
    );

    auto intial_out_state = CAP.getState();
    std::cout << "in main " << std::endl;
    print_state(intial_out_state); 

    return 0; 
}
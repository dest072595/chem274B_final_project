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
    constexpr size_t rows = 2; 
    // columns of the inital state
    constexpr size_t cols = 3; 
    // rows in the neighborhood
    constexpr size_t n_rows = 1; 
    // columns in the neighborhood
    constexpr size_t n_cols  = 1; 

    // create a 4 row by 5 column initial state
    std::vector<std::vector<Person>> initial_state (rows, std::vector<Person>(cols, Person())); 

    // create update rule 
        // This rule replaces everyone with a 'c' person
    std::function<Person (const std::array<std::array<Person, n_cols>, n_rows>) > updateRule = [](const std::array<std::array<Person, n_cols>, n_rows>& neighborhood)-> Person 
    {   
        // print out 
        // for(auto vec : neighborhood){
        //     for(auto p : vec){
        //         std::cout << p.health << " ";
        //     }
        //     std::cout << std::endl; 
        // }
        // std::cout<< std::endl;
        
        Person p = neighborhood.at((n_rows - 1) /2).at((n_cols - 1) /2);
    
        Person r; 
        if (p.health == 'h')
            r.health = 'c';
        else 
            r.health = 'q' ;
        return r;

    }; 
    

    // create boundary rule 
        // This rule does nothing
    //std::function<void(std::vector<std::vector<Person>>&, size_t, size_t)> outOfBoundsRule = [](std::vector<std::vector<Person>>& state, size_t rpad, size_t cpad)->void{};
    auto outOfBoundsRule = FixedBoundary<Person>(Person{'x'});

    Cellular_Automata<Person, n_rows, n_cols> CAP (
        initial_state, 
        updateRule, 
        outOfBoundsRule
    );


    print_state(initial_state);

    CAP.update(); 
    print_state(CAP.getState()); 
    print_state(CAP.gimme()); 

    CAP.update(); 
    print_state(CAP.getState()); 
    print_state(CAP.gimme()); 
    
    return 0; 
}
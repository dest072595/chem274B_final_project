// Chem 274B: Software Engineering Fundamentals for
//            Molecular Sciences  
// 
// Group 11 
//
// This is file is a simple demonstrator and tester of the Cellular_Automata 
// With the "Straight Conditional" provided update rule and <int> datatype

#include "Cellular_Automata.h"

int main(){
    // rows in the neighborhood
    constexpr size_t n_rows = 1; 
    // columns in the neighborhood
    constexpr size_t n_cols  = 1; 

    std::vector<std::vector<int>> initial_state = {{0,1,2,3,4,5}};
    
    
    // create update rule 
    auto outOfBoundsRule = PeriodicBoundaryRule<int>;

    std::map<int,int> update_map {
        {0,1},
        {1,2},
        {2,4},
        {4,3},
        {3,5},
        {5,0}
    };

    auto updateRule = StraightConditionalRule<int>(update_map);

    Cellular_Automata<int, n_rows, n_cols> CA (
        initial_state, 
        updateRule, 
        outOfBoundsRule
    );

    for (int i = 0; i < 10; i++){
        std::cout << CA;
        CA.update(); 
    }

    return 0; 
}
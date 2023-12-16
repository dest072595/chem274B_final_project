// Chem 274B: Software Engineering Fundamentals for
//            Molecular Sciences  
// 
// Group 11 
//
// This is file is a simple demonstrator and tester of the Cellular_Automata 
// With the Neighboor Conditional Rule provided update rule and <int> datatype

#include "Cellular_Automata.h"


int main(){
    // rows in the neighborhood
    constexpr size_t n_rows = 3; 
    // columns in the neighborhood
    constexpr size_t n_cols  = 3; 

    std::vector<std::vector<int>> initial_state = {
        {0,1,0,0,0,0},
        {0,0,0,0,0,0},
        {0,0,0,0,0,0}
    };
    
    
    // create update rule 
    auto outOfBoundsRule = PeriodicBoundaryRule<int>;

    std::map<int,int> external_transition_map {
    {1,1}
    };

    std::map<int,int> internal_transition_map {
        {1,2},
        {2,3},
        {3,4},
        {4,5},
        {5,5}
    };

    auto updateRule = NeighborConditionalRule<int>(
        external_transition_map,
        internal_transition_map, 
        MooreNeighborhood<int>
    );

    Cellular_Automata<int, n_rows, n_cols> CA (
        initial_state, 
        updateRule, 
        outOfBoundsRule
    );

    for (int i = 0; i < 8; i++){
        std::cout << CA; 
        std::cout << std::endl; 
        CA.update(); 
    }

    return 0; 
}
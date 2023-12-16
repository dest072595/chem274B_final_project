// Chem 274B: Software Engineering Fundamentals for
//            Molecular Sciences  
// 
// Group 11 
//
// This is file is a simple demonstrator and tester of the Cellular_Automata 
// With the "Majority Rule" provided update rule and <bool> datatype, and 
// Fixed Boundary Conditions, and printing

#include "Cellular_Automata.h"

int main(){
    // rows in the neighborhood
    constexpr size_t n_rows = 1; 
    // columns in the neighborhood
    constexpr size_t n_cols  = 3; 

    std::vector<std::vector<bool>> initial_state = {{
        true, false, true, false, true, false, true, 
        false, true, true, false, true, false, true, 
        false, true, true, true, false, false, false, 
        true, false
    }};
    
    
    // create update rule 
    auto outOfBoundsRule = FixedBoundaryRule<bool>(false);

    Cellular_Automata<bool, n_rows, n_cols> CA (
        initial_state, 
        MajorityRule, 
        outOfBoundsRule
    );

    for (int i = 0; i < 10; i++){
        std::cout << CA; 
        CA.update(); 
    }

    return 0; 
}
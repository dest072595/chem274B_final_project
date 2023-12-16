#pragma once

#include <array> 
#include <vector>
#include <functional>
#include <exception>
#include <iostream>
#include <map> 

template <typename T, size_t n_rows, size_t n_cols> 
class Cellular_Automata {
    // This class provides a generic framework for performing 2D cellular Automata simulations
    // 1D simulations are supported by specifying a single row
    private: 
        std::vector<std::vector<T>> _hidden_state; 
        std::function< T (const std::array<std::array<T, n_cols>, n_rows>)> _updateRule;
        std::function<void (std::vector<std::vector<T>>& state, int rpad, int cpad)> _outOfBoundsRule; 
        
        size_t _step; 
        int _rpad; 
        int _cpad;

        // private helper for calculating updates
        const std::array<std::array<T, n_cols>, n_rows> get_neighborhood_around(int row, int col);
    public:
        // Initializer takes initial state, update rule and out of bounds rule
        Cellular_Automata(
            const std::vector<std::vector<T>>& initial_state, 
            std::function< T (const std::array<std::array<T, n_cols>, n_rows>)> updateRule, 
            std::function<void (std::vector<std::vector<T>>& state, size_t, size_t)> outOfBoundsRule 
        );

        // Updates the state one Step
        void update();

        // Returns the Current Simulation Step
        int getStep() const;

        // Returns the output state of the Simulation
        const std::vector<std::vector<T>> getState() const; 
    
}; 

#include "../Source/Cellular_Automata.tpp"
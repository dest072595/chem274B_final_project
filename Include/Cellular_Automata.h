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

        const std::array<std::array<T, n_cols>, n_rows> get_neighborhood_around(int row, int col)
        {
            // Helper Function for Calculating the Update Step
           std::array<std::array<T, n_cols>, n_rows> neighborhood {};
            for(int i = - _rpad ; i <= _rpad; i++){
                for(int j = -_cpad ; j <= _cpad; j++){
                    neighborhood.at(i + _rpad).at(j + _cpad) = _hidden_state.at(row + i).at(col + j); 
                }
            }
            return neighborhood; 
        }
    public: 
        Cellular_Automata(
            const std::vector<std::vector<T>>& initial_state, 
            std::function< T (const std::array<std::array<T, n_cols>, n_rows>)> updateRule, 
            std::function<void (std::vector<std::vector<T>>& state, size_t, size_t)> outOfBoundsRule 
        )
        {

        // Checking Input Rows
        if(initial_state.size() == 0){
            throw std::invalid_argument("intial state number of rows must be a positive natural number"); 
        }

        // Checking Input Cols 
        if(initial_state.at(0).size() == 0){
            throw std::invalid_argument("intial state number of rows must be a positive natural number"); 
        }

        // Checking Neighborhood Rows
        if(n_rows % 2 == 0){
            throw std::invalid_argument("n_rows must be a natural, odd number"); 
        }else{
            _rpad = (n_rows - 1) / 2;
        }

        // Checking Neighborhood Cols
        if(n_cols % 2 == 0){
            throw std::invalid_argument("n_cols must be a natural, odd number"); 
        }else{
            _cpad = (n_cols - 1) / 2; 
        }

        // Initialize the hidden state empty 
        _hidden_state = std::vector<std::vector<T>> ( initial_state.size() + (2 * _rpad), std::vector<T> (initial_state.at(0).size() + (2 * _cpad)));


        // Copy intial state to center of hidden state
        for(int i = 0; i < initial_state.size(); i++){
            std::copy(
                initial_state.at(i).begin(),
                initial_state.at(i).end(),
                _hidden_state.at(i + _rpad).begin() + _cpad 
            );
        }

        // Store update rule 
        _updateRule = updateRule; 

        // Store OOB rule 

        _outOfBoundsRule = outOfBoundsRule; 

        // Perform OOB Rule
        _outOfBoundsRule(_hidden_state, _rpad, _cpad); 

        _step = 0; 
        // end of constructor
        }


        // Iterates the Simulation one Step 
        void update(){
            // Initialize Empty State
            std::vector<std::vector<T>> next_hidden_state (_hidden_state.size(),std::vector<T>(_hidden_state.at(0).size())); 

            // Calculate New Inbounds State  
            for(int i = _rpad; i < _hidden_state.size() - _rpad; i++){
            for(int j = _cpad; j < _hidden_state.at(0).size() - _cpad; j++){
                next_hidden_state.at(i).at(j) = _updateRule(get_neighborhood_around(i,j));
            }
            }

            // Update Out Of Bonds State
            _outOfBoundsRule(next_hidden_state, _rpad, _cpad); 

            // Replace Old State with New State
            _hidden_state = next_hidden_state; 

            // Incriment Step Counter 
            _step += 1; 
        }

        // Returns the Current Simulation Step
        int getStep(){
            return _step; 
        }

        // Returns the output state of the Simulation
        const std::vector<std::vector<T>> getState() const{
            std::vector<std::vector<T>> out_state (_hidden_state.size() - (2 * _rpad), std::vector<T>(_hidden_state.at(0).size() - (2 * _cpad), T())); 

            for(size_t i = 0; i < out_state.size(); i++){
            for(size_t j = 0; j < out_state.at(0).size(); j++){
                out_state.at(i).at(j) = _hidden_state.at(i + _rpad).at(j + _cpad);
            }
            }
            return out_state; 
        }
    
}; 

// helper function for copying around data in a std::vector<std::vector<T>> 
template<typename T> 
void copy_data_around(
    std::vector<std::vector<T>>& data, 
    int source_row, 
    int source_col, 
    int dest_row, 
    int dest_col, 
    int num_rows_to_copy, 
    int num_cols_to_copy
    )
{
    for(int i = 0; i < num_rows_to_copy; i++){
    for(int j = 0; j < num_cols_to_copy; j++){
        data.at(dest_row + i).at(dest_col + j) = data.at(source_row + i).at(source_col + j); 
    }
    }
}

// Periodic Boundary Condition Function, Automatically makes an update rule for a given typename T
template<typename T>
std::function<void (std::vector<std::vector<T>>& state, int rpad, int cpad)> PeriodicBoundaryRule(){
    return [](std::vector<std::vector<T>>& state, size_t rpad, size_t cpad){
        int rows = state.size();
        int cols = state.at(0).size(); 

        int start_row = rpad;
        int start_col = cpad;
        int end_row = rows - rpad;
        int end_col = cols - cpad;

        // Copy data to the top padding
        copy_data_around(state, start_row, start_col, 0, start_col, rpad, end_col - start_col);

        // Copy data to the bottom padding
        copy_data_around(state, start_row, start_col, rows - rpad, start_col, rpad, end_col - start_col);

        // Copy data to the left padding
        copy_data_around(state, start_row, start_col, start_row, 0, end_row - start_row, cpad);

        // Copy data to the right padding
        copy_data_around(state, start_row, start_col, start_row, cols - cpad, end_row - start_row, cpad);

        // Copy data to the top-left corner
        copy_data_around(state, start_row, start_col, 0, 0, rpad, cpad);

        // Copy data to the top-right corner
        copy_data_around(state, start_row, end_col - cpad, 0, cols - cpad, rpad, cpad);

        // Copy data to the bottom-left corner
        copy_data_around(state, end_row - rpad, start_col, rows - rpad, 0, rpad, cpad);

        // Copy data to the bottom-right corner
        copy_data_around(state, end_row - rpad, end_col - cpad, rows - rpad, cols - cpad, rpad, cpad);    
    };
}

// helper function for filling data in a std::vector<std::vector<T>> 
template<typename T> 
void fill_data(
    std::vector<std::vector<T>>& data,
    const T value, 
    int dest_row, 
    int dest_col, 
    int num_rows_to_fill, 
    int num_cols_to_fill
    )
{
    for(int i = 0; i < num_rows_to_fill; i++){
    for(int j = 0; j < num_cols_to_fill; j++){
        data.at(dest_row + i).at(dest_col + j) = value; 
    }
    }
}

// Periodic Boundary Condition Function, Automatically makes an update rule for a given typename T
template<typename T>
std::function<void (std::vector<std::vector<T>>& state, int rpad, int cpad)> FixedBoundaryRule(const T value){
    return [value](std::vector<std::vector<T>>& state, size_t rpad, size_t cpad){
        int rows = state.size();
        int cols = state.at(0).size(); 

        int start_row = rpad;
        int start_col = cpad;
        int end_row = rows - rpad;
        int end_col = cols - cpad;

        // Copy data to the top padding
        fill_data(state, value, 0, start_col, rpad, end_col - start_col);

        // Copy data to the bottom padding
        fill_data(state, value, rows - rpad, start_col, rpad, end_col - start_col);

        // Copy data to the left padding
        fill_data(state, value, start_row, 0, end_row - start_row, cpad);

        // Copy data to the right padding
        fill_data(state, value, start_row, cols - cpad, end_row - start_row, cpad);

        // Copy data to the top-left corner
        fill_data(state, value, 0, 0, rpad, cpad);

        // Copy data to the top-right corner
        fill_data(state, value, 0, cols - cpad, rpad, cpad);

        // Copy data to the bottom-left corner
        fill_data(state, value, rows - rpad, 0, rpad, cpad);

        // Copy data to the bottom-right corner
        fill_data(state, value, rows - rpad, cols - cpad, rpad, cpad);    
    };
}

template<typename T>
std::function<void (std::vector<std::vector<T>>& state, size_t rpad, size_t cpad)> StraightConditionalTransition(const std::map<T,T>& value){
    return [](std::vector<std::vector<T>>& state, size_t rpad, size_t cpad){};
}

// Update Rule for "Majority Rule" as Described in Lecture
std::function<bool (const std::array<std::array<bool,3>,1>) > MajorityRule = [](const std::array<std::array<bool,3>,1> neighborhood)-> bool 
{   
    int count = 0; 
    if (neighborhood.at(0).at(0))
        count += 1; 
    if (neighborhood.at(0).at(1))
        count += 1; 
    if (neighborhood.at(0).at(2))
        count += 1;

    return count >= 2;
}; 


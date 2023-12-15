#pragma once

#include <array> 
#include <vector>
#include <functional>
#include <exception>
#include <format> 
#include <iostream>

template <typename T, size_t n_rows, size_t n_cols> 
class Cellular_Automata {
    private: 
        std::vector<std::vector<T>> _hidden_state; 
        std::function< T (const std::array<std::array<T, n_cols>, n_rows>)> _updateRule;
        std::function<void (std::vector<std::vector<T>>& state, size_t rpad, size_t cpad)> _outOfBoundsRule; 
        
        size_t _step; 
        size_t _rpad; 
        size_t _cpad;

        const std::array<std::array<T, n_rows>, n_cols>& get_neighborhood_around(size_t row, size_t col)
        {
            // empty initialization
            std::array<std::array<T, (2 * _cpad + 1)>, (2 * _rpad + 1)> n {};

            for(size_t i = row; i < row + (2 * _rpad) + 1; i++){
                for(size_t j = col; j < col + (2 * _cpad) + 1; j++){
                    n.at(i).at(j) = _hidden_state.at(i + _rpad).at(j + _cpad); 
                }
            }
            return n; 
        }
    public: 
        Cellular_Automata(
            const std::vector<std::vector<T>>& initial_state, 
            std::function< T (const std::array<std::array<T, n_cols>, n_rows>)> updateRule, 
            std::function<void (std::vector<std::vector<T>>& state, size_t, size_t)> outOfBoundsRule 
        )
        {
        
        std::cout << "checkpoint 1" << std::endl;
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

        std::cout << "checkpoint 2" << std::endl;
        // Initialize the hidden state empty 
        
        _hidden_state = std::vector<std::vector<T>> ( initial_state.size() + (2 * _rpad), std::vector<T> (initial_state.at(0).size() + (2 * _cpad)));

        std::cout << "_hidden_state.size() is :" << _hidden_state.size() << std::endl; 
        std::cout << "_hidden_state.at(0).size() is: " << _hidden_state.at(0).size() << std::endl; 

        std::cout << "checkpoint 3" << std::endl;
        // Copy intial state to center of hidden state
        for(size_t i = 0; i < initial_state.size(); i++){
            std::copy(
                initial_state.at(i).begin(),
                initial_state.at(i).end(),
                _hidden_state.at(i + _rpad).begin() + _cpad 
            );
        }

        std::cout << "_hidden_state.size() is :" << _hidden_state.size() << std::endl; 
        std::cout << "_hidden_state.at(0).size() is: " << _hidden_state.at(0).size() << std::endl; 

        std::cout << "checkpoint 4" << std::endl;
        
        // Store update rule 
        _updateRule = updateRule; 

        // Store OOB rule 

        _outOfBoundsRule = outOfBoundsRule; 

        // Perform OOB Rule
        _outOfBoundsRule(_hidden_state, _rpad, _cpad); 
        std::cout << "_hidden_state.size() is :" << _hidden_state.size() << std::endl; 
        std::cout << "_hidden_state.at(0).size() is: " << _hidden_state.at(0).size() << std::endl; 


        _step = 0; 
        // end of constructor
        std::cout << "checkpoint 5" << std::endl;
        }


        // Iterates the Simulation one Step 
        void update(){
            // Initialize Empty State
            std::vector<std::vector<T>> next_hidden_state (_hidden_state.size(),std::vector<T>(_hidden_state.at(0).size())); 
            
            // Calculate New Inbounds State  
            for(size_t i = _rpad; i < _hidden_state.size() - _rpad; i++){
            for(size_t j = _rpad; j < _hidden_state.at(0).size() - _cpad; j++){
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
            std::cout << "_rpad is " << _rpad << std::endl;
            std::cout << "_cpad is " << _cpad << std::endl;
            std::cout << "_hidden_state.size() is :" << _hidden_state.size() << std::endl; 
            std::cout << "_hidden_state.at(0).size() is: " << _hidden_state.at(0).size() << std::endl; 
            std::vector<std::vector<T>> out_state (_hidden_state.size() - (2 * _rpad), std::vector<T>(_hidden_state.at(0).size() - (2 * _cpad), T())); 
            std::cout << "test" << std::endl; 

            for(size_t i = 0; i < out_state.size(); i++){
            for(size_t j = 0; j < out_state.at(0).size(); j++){
                std::cout << "i is: " << i << " and j is: " << j << std::endl;
                out_state.at(i).at(j) = _hidden_state.at(i + _rpad).at(j + _cpad);
            }
            }
            return out_state; 
        }
    
}; 
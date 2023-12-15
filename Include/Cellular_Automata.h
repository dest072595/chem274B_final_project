#pragma once 

#include <vector>
#include <functional>
#include <exception>
#include <format> 

template <typename T> 
class Cellular_Automata {
    private: 
        std::vector<std::vector<T>> _hiddenState; 
        std::function< T (const std::array<std::array<T, size_t n_rows>, size_t n_cols>)> _updateRule;
        std::function<void (std::vector<std::vector<T>>& state, size_t rpad, size_t cpad,)> _outOfBoundsRule; 
        
        int _step; 
        int _rpad; 
        int _cpad;

        const std::array<std::array<T, size_t n_rows>, size_t c_cols>& get_neighboorhood_around(size_t row, size_t col)
        {
            std::array<std::array<T>, (2 * _rpad + 1), (2 * _cpad +1)> n;
            for(i = row; i < row + (2 * _rpad) + 1; i++){
                for(j = col; j < col + (2 * _cpad) + 1, j++){
                    n.at(i).at(j) = _hiddenState.at(i + _npad).at(j + _cpad); 
                }
            }
            return &n; 
        }
    public: 
        Cellular_Automata(
            const std::vector<std::vector<T>>& initial_state, 
            std::function< T (const std::array<std::array<T, size_t n_rows>, size_t n_cols>)> updateRule, 
            std::function<void (std::vector<std::vector<T>>& state, size_t rpad, size_t cpad,)> outOfBoundsRule 
        ){

        // Checking Input Rows
        if(initial_state.size() == 0){
            throw std::invalid_argument(
                std::format(
                    "intial state number of rows must be a positive natural number, provided: {}",
                    initial_state.size()
                    )
                ); 
        }

        // Checking Input Cols 
        if(initial_state.at(0).size() == 0){
            throw std::invalid_argument(
                std::format(
                    "intial state number of rows must be a positive natural number, provided: {}",
                    initial_state.at(0).size()
                    )
                ); 
        }

        // Checking Neighborhood Rows
        if(n_width % 2 == 0){
            throw std::invalid_argument(
                std::format(
                    "n_rows must be a natural, odd number, provided: {}",
                    n_rows)
                    ); 
        }else{
            _rpad = (n_rows - 1) / 2;
        }

        // Checking Neighborhood Cols
        if(n_height % 2 == 0){
            throw std::invalid_argument(
                std::format(
                    "n_cols must be a natural, odd number, provided: {}",
                    n_cols
                    )
                ); 
        }else{
            _cpad = (n_cols - 1) / 2; 
        }

        // Initialize the hidden state empty 
        _hiddenState = std::vector<std::vector<T>>((initial_state.size() + (2 * _rpad)), std::vector<T>((initial_state.at(0).size() + (2 * _cpad), T())))

        // Copy intial state to center of hidden state
        for(int i = 0; i < initial_state.size(); i++){
            std::copy(
                initial_state.at(i).begin(),
                initial_state.at(i).end(),
                _hiddenState_state.at(i + _rpad).begin() + _cpad 
            );
        }
        
        // Store update rule 
        _updateRule = updateRule; 

        // Store OOB rule 

        _outOfBoundsRule = outOfBoundsRule; 

        // Perform OOB Rule
        _outOfBoundsRule(_hiddenState, _rpad, _cpad); 

        _step = 0; 
        // end of constructor
        }



        void update(){
            // Initialize Empty State
            std:vector<std::vector<T>> next_hidden_state (_hiddenState.size(),std::vector<T>(_hiddenState.at(0).size(), T())); 
            // Copy old state over 
            for(size_t i = _rpad; i < _hiddenState.size() - _rpad; i++){
            for(size_t j = _rpad; j < _hiddenState.at(0).size() - _cpad; j++){
                _hidden_state.at(i).at(j) = _updateRule(get_neighboorhood_around(i,j))
            }
            }
            _outOfBoundsRule(next_hidden_state, _rpad, _cpad); 
            _hiddenState = next_hidden_state; 
            _step += 1; 
        }

        int getStep(){
            return _step; 
        }

        const std::vector<std::vector<T>>& getState() const{
            std::vector<std::vector<T>> out_state (_hiddenState.size() - (2 * _rpad), std::vector<T>(_hiddenState.at(0).size() - (2 * _cpad), T())); 
            for(size_t i = _rpad; i < _hiddenState.size() - _rpad; i++){
            for(size_t j = _rpad; j < _hiddenState.at(0).size() - _cpad; j++){
                _hidden_state.at(i).at(j) = _updateRule(get_neighboorhood_around(i,j))
            }
            }
        }
    
}; 

#include "../Source/Data_Structures/Cellular_Automata.tpp"
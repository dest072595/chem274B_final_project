#pragma once


template <typename T, std::size_t n_height, std::size_t n_width> 
Cellular_Automata<T>::Cellular_Automata(const std::vector<std::vector<T>>& initial_state, 
        std::function< T (std::array<std::array<T, size_t n_height>,  n_width>)> updateRule, 
        std::function< std::vector<std::vector<T>> (std::vector<std::vector<T>>& state, size_t hpad, size_t wpad)> outOfBoundsRule 
        ); 
    ){ 
    } 


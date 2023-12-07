#include <vector>
#include <functional>

template <typename T,size_t n_width, size_t n_height> 
class Cellular_Automata {
    private: 
        std::vector<std::vector<T>> _hiddenState; 
        int _step; 
        int _hpad;
        int _wpad; 
    public: 
        Cellular_Automata(const std::vector<std::vector<T>>& initial_state, 
        std::function< T (std::array<std::array<T, n_height>, n_width>)> updateRule (), 
        std::function< std::vector<std::vector<T>> (std::vector<std::vector<T>>, hpad, wpad)> outOfBoundsRule () 
        ); 
        void update();
        int getStep();
        const std::vector<std::vector<T>>& getState() const;  
    
}; 
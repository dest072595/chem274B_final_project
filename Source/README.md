# CHEM 274B

Last updated: Dec 15, 2023

Contributors: Austin Glover, Destinee Maldonaldo, Sam Wollenburg

### Subdirectories

### Files

- Cellular_Automata.h : Templated cellular automata class containing the functions.
  - `Cellular_Automata()` : Initialize with the initial state (a vector of vectors containing type T), an updateRule, and an outOfBoundsRule. If ints are used, then predefined update rules can be used. The cellular automata class has the following funtions.
    - `update()` : This iteraties the cellular automata by one step.
    - `getStep()` : This returns the current iteration number of the simulation.
    - `getState()` : Returns the current state of the simulation.
  - `copy_data_around()` : Is a helper function that copies data from a source cell to a destination cell. This is used for creating certain boundary conditions.
  - `PeriodicBoundary()` : Predefined update rule that creates a periodic boundary for the simulation. Uses `copy_data_around()`.
  - `fill_data()` : Helper function that fills data with a certain value. Starts at the destination row and column and fills a defined number of rows and columns
  - `FixedBoundary()` : Predeined update rule that creates a fixed boundary with a user defined value.

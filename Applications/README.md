# CHEM 274B

Last updated: Dec 15, 2023

Contributors: Austin Glover, Destinee Maldonaldo, Sam Wollenburg

### Subdirectories

### Files

- COVID-19_simulation.cpp : The COVID-19 simulation C++ source file. This application uses the cellular automata class as means of provided a viral spreading simulation. This simulation contains two different update rules with the ability to add in the future. The first update rule is called `superSpread`. This rule causes a cell to become sick if any of its neighbors are sick. If a cell is sick and a neighbor around it is sick then the cell will die. The second update rule is called `specifySteps` this rule allows for the user to define how many iterations must pass before the disease progresses. This also allows for the cells to recover.
- input_file.txt : This file is the user defined input that allows for the initial conditions, update rule, and boudary condition to follow. The input file is formatted in the following manner. Lines that are marked with `//` indicate to the program which variable is on the next line. These lines must follow the patter of `// variable_name`. The following are the variable names and their function.
  - `steps` : The number of iterations the simultion will perfor
  - `freq` : Defines the frequency the output files will be generated. For example, a value of 3 would only provided an output csv file every third iteration.
  - `height` : The height of the matrix.
  - `width` : This width of the matrix.
  - `neighborhood` : This selects the type of neighborhood to use. Currently either `full` for the Moore neighborhood, or `cross` for the Von Neumann neighborhood have been implemented.
  - `updateRule` : Specifies the update rule to be used. The most primative rule is `superSpread`. This allows for a healthy cell to become sick if a sick cell is nearby, and allows for sick cell to die if a sick cell is nearby. A more advanced rule is `specifySteps` which allows for the user to define how many iterations are required before the disaese is allowed to progress. This can be configured so that becoming sick occurs quickly, but dieing requires more time. This can also allow for cells to recover if they are sick and are not near any sick cells.
  - `boundaryRule` : Specifies the boundary rule to be used. The boundary rules are `periodic` and `fixed`. 
  - `state` : This is the initial state. It is a `height` by `width` matrix of ints seperated by spaces. 0 represents a recovered cell, 1 represents a healthy cell, 2 represents a sick cell, and 3 represents a dead cell. The additional recovered step is to allow for extra immunity to be granted after being sick. With the current rules it requires a cell to become healthy before becoming sick.
  - `age` : Age is currently not in use, but it is planned to use this variable in future rules. This idea is to allow for older cells to be more suceptible to the disease progressing.
  - `toRecover` : This is a `height` by `width` matrix of ints seperated by spaces. Each cell represents a person's required number of iterations before recovery is allowed.
  - `toHealthy` : This is a `height` by `width` matrix of ints seperated by spaces. Each cell represents a person's required number of iterations before becoming healthy is allowed.
  - `toSick` : This is a `height` by `width` matrix of ints seperated by spaces. Each cell represents a person's required number of iterations before being sick is allowed.
  - `toDead` : This is a `height` by `width` matrix of ints seperated by spaces. Each cell represents a person's required number of iterations before death is allowed.
- Makefile : Contains targets:
  - `all` : Makes all applications.
  - `clean` : Removes all applications from ../Bin.
  - `COVID-19_simulation` : Compiles the COVID-19_simulation.
- README.md : This file.

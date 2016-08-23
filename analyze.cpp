// Supply data file argument to run e.g. './analyze "directory/sheffield.data"'
// Reads data from file to a 'DataSet' object 
// Displays analysis of data and gives the user the option to select graphs
// generated from result.

#include <iostream>
#include <cstdlib>
#include "data.hpp"

using namespace std;

// Main loop, with the command line arguments supplied by the user at runtime 
int main(int argc, char** argv){
  bool running = true;
  bool showGraphOptions = true;
  int userInput;

  // Try to perform analysis, display any errors to user
  try
  {
    // First check to see that the user has supplied at least 1 argument
    if(argc <=1)
    {
        throw string("Error: Please supply a single command line argument"
                     " specifying the data file path.\n");
    }

    // Create a dataset based on the data at the specified directory location
    DataSet data(argv[1]);
    // Display the lowest Minimum Temperature for the data file supplied
    data.showLowestMinimumTemperature();
    // Display the Year with the Highest Total Rainfall for the data file supplied
    data.showYearWithHighestTotalRainfall();
    // Present user with the option to display one of three graphs
    while(showGraphOptions)
    {
        // Request the user input
        cout << "Graph 1: Maximum Temperature as a function of Time" << endl;
        cout << "Graph 2: Sunshine as a function of Time" << endl;
        cout << "Graph 3: Maximum Temperature as a function of "
             << "Sunshine Hours\n" 
             << endl;
        cout << "Select a graph to display by entering a digit from 1 to 3:";
        // Keep a reference to the user response
        cin >> userInput;
        // Set options to false, as the user has now selected information
        showGraphOptions = false;
        // Attempt to identify user input
        switch(userInput)
        {
          case 1:
            // Display Maximum Temperature Graph
            cout << "\nGraph One: This graph shows Maximum Temperature as"
                 << " a function of Time. "
                 << endl;
            data.showTempTimePlot();
          break;
          case 2:
            // Display Sunshine Hours Graph
            cout << "\nGraph Two: This graph shows Sunshine Hours as a"
                 << " function of Time."
                 << endl;
            data.showSunshineTimePlot();
          break;
          case 3:
            // Display Maximum Temperature / Sunshine Hours Graph
            cout << "\nGraph Three: This graph shows Maximum Temperature"
                 << " as a function of Sunshine Hours"
                 << endl;
            data.showTemperatureSunshinePlot();
          break;
          default:
            // No input recognised, display error message and ask again
            cout << "Invalid, try again. \n" << endl;
            // Set options back to true to allow new information selection
            showGraphOptions = true;
            // Clear input stream and dump current input in a string variable
            // to free the while loop to request input at the next iteration
            cin.clear();
            string ignoreLine;
            getline(cin, ignoreLine);
          break;
        }
    }
  }
  catch (string e)
  {
    // Display the error 
    cout << e <<endl;
    // Stop execution of the program with an error code
    running = false;
  }// End try

  // Check for errors and return appropriate code
  if (running)
  {
    // Stopped as expected
    return EXIT_SUCCESS;
  }
  else
  {
    // Error occurred
    return EXIT_FAILURE;
  }
}// End main loop
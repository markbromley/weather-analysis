// Method implementations for the 'MonthData' and 'DataSet' classes

#include <iostream>
#include <fstream>
#include <vector>
#include "data.hpp"
#include "gnuplot_i.hpp"

using namespace std;

// Overload the stream extraction operator for the an input stream and a
// 'MonthData' object so that each word separated by whitespace is directly 
// inserted as the attribute to the 'MonthData' object.
istream& operator >> (istream& in, MonthData& month)
{
    in >> month.year;
    in >> month.month;
    in >> month.tempMax;
    in >> month.tempMin;
    in >> month.airFrost;
    in >> month.rainFall;
    in >> month.sunShineTime;
    // Return the input stream so the operator can still be daisy chained
    return in;
}

// DataSet Constructor. A string is taken as the only argument, which is 
// expected to indicate the relative file path to a data file
DataSet::DataSet(string fileName)
{
    MonthData data;
    string line;
    // Convert the filename to a C-String and attempt to open the file
    // If the file cannot be opened an exception is thrown
    ifstream file(fileName.c_str());
    if (not file.is_open())
    {
        throw string("Error: Cannot open the data file from the supplied "
                     "file path. Please check file path is correct.\n");
    }
    // Check if the file has been successfully opened
    if(file)
    {
        // Skip the first four lines (the header) and pass to line variable
        for (int i = 0; i < 4 ; i++)
        {
            getline(file, line);
        } // End of for loop
        // Extract each data line into a 'MonthData' object and push onto
        // the back of the dataSet vector
        while(file >> data)
        {
            dataSet.push_back(data);
        } // End while
    } // End if
}// End method

// Displays lowest Minimum Temperature for the given data set
// and the Month/ Year it occurred in
void const DataSet::showLowestMinimumTemperature()
{
    // We can safely assume at least one record. Set the lowest Minimum
    // Temperature to a high value, to ensure removed.
    float lowestMinTemp = 10000;
    int lowestMinTempYear;
    int lowestMinTempMonth;
    vector<MonthData>::iterator i;
    // Iterate over the dataSet vector and check to see if the 
    // Minimum Temperature each month is lower than the current minimum for the
    // dataset
    for (i = dataSet.begin(); i != dataSet.end(); i++)
    {
        // Check to see if the current object contains a lower Minimum 
        // Temperature than currently known minimum for entire set
        if (lowestMinTemp > (i) -> getTempMin())
        {
            lowestMinTemp = (i) -> getTempMin();
            lowestMinTempYear = (i) -> getYear();
            lowestMinTempMonth = (i) -> getMonth();
        }
    }

    // Display the results to the user in the terminal window
    cout << "\nThe lowest minimum temperature was " 
         << lowestMinTemp 
         << " degrees C, in month number "
         << lowestMinTempMonth
         << " in the year " 
         <<lowestMinTempYear 
         << endl; 
}

// Display the year with highest total rainfall
void const DataSet::showYearWithHighestTotalRainfall()
{
    // Initialise highest rainfall to a negative to ensure removed
    float highestRainfall = -1;
    int highestRainfallYear;
    float tempRainFallMeasure = 0;
    vector<MonthData>::iterator i;
    // For each object in the dataset, check to see if the rainfall for that
    // month is greater than currently known highest rainfall for the whole set
    for (i = dataSet.begin(); i != dataSet.end(); i++)
    {
        // Check to see if the current object contains a higher Rainfall
        // than currently known highest for entire dataset
        tempRainFallMeasure += (i) -> getRainFall();
        if( ((i) -> getMonth()) == 12 ){
        // We have now had 12 months
            if(highestRainfall < tempRainFallMeasure)
            {
                highestRainfall = tempRainFallMeasure;
                highestRainfallYear = (i) -> getYear();
            }
            //Reset the tempRainFall counter to 0
            tempRainFallMeasure = 0;
        }
    }

    // Display the results to the user in the terminal window
    cout << "The highest year total rainfall was " 
         << highestRainfall 
         << "mm, in the year " 
         << highestRainfallYear 
         << "\n" 
         << endl; 
}

// Prevents any graphs generated from being immediately dismissed. Requires user
// to press a key to dismiss the graph.
void const DataSet::waitForKey ()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) 
// every key press registered, also arrow keys
    cout << endl << "Press any key to continue..." << endl;

    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    _getch();
#elif defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__)
    cout << endl << "Press ENTER to continue..." << endl;
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::cin.get();
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::cin.get();
#endif
    return;
}

// Displays line graph of Maximum Temperature as a function of Time 
void const DataSet::showTempTimePlot()
{
    // Create the vectors necessary to populate the graph
    vector<double> temperatureVector;
    vector<double> yearVector;
    vector<MonthData>::iterator i;
    double tempTime;
    // Maximum Temperature as a function of time
    // Extract time from dataset (built from the Year and Month)
    for (i = dataSet.begin(); i != dataSet.end(); i++)
    {
        // Use the Year and Month for each record to create a time value in
        // years, with the month represented as a fraction
        tempTime = ((i) -> getYear()) + (float(1.0/12.0) * (((i)-> getMonth())-1));
        // Add the Maximum Temperature to the back of the temperatureVector
        temperatureVector.push_back((i) -> getTempMax());
        // Add the newly generated time stamp to the back of the yearVector
        yearVector.push_back(tempTime);
    }
    // Display the graph
    Gnuplot plot(yearVector,temperatureVector,"Graph to show Maximum"
     " Temperature as a function of Time", "lines", "Time (Years)", "Maximum\
      Temperature (Degrees C)");
    // Call the waitForKey method to prevent the generated plot from 
    // being immediately dismissed
    waitForKey();
}

// Displays line graph of Sunshine Hours as a function of Time 
void const DataSet::showSunshineTimePlot()
{
    // Create the vectors necessary to populate the graph
    vector<double> sunshineVector;
    vector<double> yearVector;
    vector<MonthData>::iterator i;
    double tempTime;
    // Sunshine Hours as a function of Time 
    // Extract time from dataset (built from the Year and Month)
    for (i = dataSet.begin(); i != dataSet.end(); i++)
    {
        // Use the Year and Month for each record to create a time value in
        // years, with the month represented as a fraction
        tempTime = ((i) -> getYear()) + (float(1.0/12.0) * (((i)-> getMonth())-1));
        // Add the Sunshine Hours to the back of the sunshineVector
        sunshineVector.push_back((i) -> getSunShineTime());
        // Add the newly generated time stamp to the back of the yearVector
        yearVector.push_back(tempTime);
    }

    // Call GNUPLOT to display the graph
    Gnuplot plot(yearVector,sunshineVector,"Graph to show Sunshine Hours as"
     " a function of Time", "lines", "Time (Years)", "Sunshine Time (Hours)");
    // Call the waitForKey method to prevent the generated plot from 
    // being immediately dismissed
    waitForKey();
}

// Displays scatter graph of Maximum Temperature as a function of Sunshine Hours
void const DataSet::showTemperatureSunshinePlot()
{
    // Create the vectors necessary to populate the graph
    vector<double> sunshineVector;
    vector<double> temperatureVector;
    vector<MonthData>::iterator i;
    //Maximum Temperature as a function of Sunshine Hours
    for (i = dataSet.begin(); i != dataSet.end(); i++)
    {
        // Add the Sunshine Hours to the back of the sunshineVector
        sunshineVector.push_back((i) -> getSunShineTime());
        // Add the Maximum Temperature to the back of the temperatureVector
        temperatureVector.push_back((i) -> getTempMax());
    }
    // Call GNUPLOT to display the graph
    Gnuplot plot(sunshineVector, temperatureVector, "Graph to show Maximum"
     " Temperature as a function of Sunshine Hours", "points", "Sunshine Time \
     (Hours)", "Maximum Temperature (Degrees C)");
    // Call the waitForKey method to prevent the generated plot from 
    // being immediately dismissed
    waitForKey();
}
// Prevent double inclusion
#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>
#include <vector>

/**
* Represents a single record from a weather dataset.
*
* Data represented includes year, month, maximum temperature, minimum
* temperature, days of air frost, rainfall (in mm) and hours of sunshine. 
*
*/
class MonthData{

    // Set the stream extraction operator as a friend of the class when supplied 
    // with input and a 'MonthData' object (allow access to private attributes)
    friend std::istream& operator >> (std::istream& in, MonthData& month);

    public:
        /** MonthData Constructor */
        MonthData(){}

        /** The year for the current record */
        int getYear() { return year; }

        /** The month for the current record */
        int getMonth() const { return month; }

        /** The Maximum Temperature in degrees C for the current record */
        float getTempMax() { return tempMax; }
        
        /** The Minimum Temperature in degrees C for the current record  */
        float getTempMin() { return tempMin; }

        /** The days of Air Frost for the current record */
        int getAirFrost() { return airFrost; }

        /** The Rain Fall in mm for the current record */
        float getRainFall() { return rainFall; }

        /** The hours of Sunshine for the current record */
        float getSunShineTime() { return sunShineTime; }

    private:
        /** The year of the current record */
        int year; 

        /** The month of the current record */
        int month;

        /** The days of air frost for the current record */
        int airFrost;

        /** The amount of rain fall (mm) for the current record */
        float rainFall;

        /** The number of hours of Sunshine for the current record */
        float sunShineTime;

        /** The Maximum Temperature in degrees C for the current record */
        float tempMax;

        /** The Minimum Temperature in degrees C for the current record */
        float tempMin;
};// End class

/**
* Represents the all records from a given dataset.
*
* Stores a vector of 'MonthData' objects. The directory location of the dataset
* should be provided during instantiation.
*
*/
class DataSet{

    public:
        /**
        * DataSet Constructor.
        *
        * Creates representation of the supplied data file, representing each
        * individual record as a 'MonthData' object.
        *
        * @param directory The path to the dataset file
        */
        DataSet(std::string directory);

        /** Displays the Minimum Temperature of the dataset */
        void const showLowestMinimumTemperature();

        /** Displays the year with highest total rainfall from the dataset */
        void const showYearWithHighestTotalRainfall();

        /* Prevents graphs from being dismissed without key press */
        void const waitForKey();

        /** Displays line graph of Maximum Temperature against Time */
        void const showTempTimePlot();

        /** Displays line graph of Sunshine Hours against Time */
        void const showSunshineTimePlot();

        /** Displays scatter graph of Maximum Temperature against Sunshine Hours */
        void const showTemperatureSunshinePlot();

    private:
        /** Vector to hold each individual 'MonthData' object */
        std::vector<MonthData> dataSet;
};// End class

// End include guard
#endif
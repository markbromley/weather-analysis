# Weather Data Analysis

Author: Mark Bromley
Date: March 2014

## Summary

This simple program was used to help with the processing of weather data records, (sample data included).

The program represent each record as a 'MonthData' object and the whole set of records as a 'DataSet' object, (a vector of 'MonthData' objects).

GNUPlot is used to display some simple results from the data, which can be selected for viewing by the user.

## Running & Viewing

Depends on GNUPlot. To install with Ubuntu:

- sudo apt-get install gnuplot gnuplot-x11

To make, run 'make' whilst in the project directory. Supply data file argument to run e.g. './analyze "sheffield.data"'.

Screenshots of the running program can be found in the 'screenshots' directory.

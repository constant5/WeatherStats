# WeatherStats
Code Clinic Project 1 in C++

This problem is about calculating statistics from a data set. Weather data was captured from Lake Ponderay in northern Idaho. There are almost 20 megabytes of data from the years 2012 through 2015. That data is available in `\data` and includes several attributes including: date, time, air temperature, barometric pressure, dew point, and others. 

The program accepts a beginning date time, ending date time, and an attribute name. Inclusive of those dates and times, the program fits a linear curve to the attribute series.  In this problem, I practice OOP by creating a class to hold weather records and extending the chrono:time_point object with some useful methods to create a DateTime object.  I also use boost for the linear regression and finally use the matplotlibcpp library to plot the data and fitted line.  Mmatplotlibcpp is a wrapper for Python's matplotliob and NumPy modules which is probably not a very efficient or distributable solution but gets the job done. 

The solution can be built in VS, after including boost and matplotlibcpp. 


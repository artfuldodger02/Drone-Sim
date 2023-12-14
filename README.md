# team-010-15-hw4
# Drone Sim Data Collection Singleton
  For our project, our group decided to implement a singleton for data collection and analysis.
  
  
  The singleton records information about each package, including pickup and dropoff location, traversal time, the strategy it used, the downtime experienced before being picked up, and the distance traveled
  
  
  Once prompted to close the program, the singleton then compiles this data together and performs analysis on the different search strategies used, determining the average distance traveled and the average time it took each strategy to complete
  
  
  The analysis also lists the speed of each strategy, in case of future changes to the program where the drone speed becomes variable, as well as statistics for a beeline strategy, in case that is implemented as a default search strategy.
  
  
  The singleton then outputs this information as a CSV file for data collection and observation. 

# team-010-15-hw4
## Andrew Carlson (carl6090) & Josh Subhan (subha013)
# Drone Sim Data Collection Singleton
## Summary
  For our project, our group decided to implement a singleton for data collection and analysis.
  
  
  The singleton records information about each package, including pickup and dropoff location, traversal time, the strategy it used, the downtime experienced before being picked up, and the distance traveled
  
  
  Once prompted to close the program, the singleton then compiles this data together and performs analysis on the different search strategies used, determining the average distance traveled and the average time it took each strategy to complete
  
  
  The analysis also lists the speed of each strategy, in case of future changes to the program where the drone speed becomes variable, as well as statistics for a beeline strategy, in case that is implemented as a default search strategy.
  
  
  The singleton then outputs this information as a CSV file for data collection and observation. 
  
## How to run
  The Singleton automatically collects data when the sim starts and packages are scheduled. To output the CSV file, end the sim using the end simulation button in the schedule html page.
  
## Sprint retrospective
  Our group did a total of 2 sprints, the first lasting 15 days and the second lasting 5 days. The first sprint was mainly reserved for discussion of the project, creating a plan for how to approach it, creating a UML diagram, and creating the header and cc file and providing doxygen comments. We intended to complete the implementation of the singleton into the simulation model as well in the sprint, but the other tasks ended up taking more time than expected and that task had to be dealt with in sprint 2.
  
  Sprint 2 mostly involved testing and bugfixing the implementation of the singleton into the simulation model. Many of our issues came from conflicts between variable types during arithmatic and incorrectly referenced instances of singleton variables. Once the program itself was working, we then moved onto the final steps of linting, dockization, and presentation creation.
    

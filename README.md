# Solar-System-Simulation-Interstellar-Theme
- Solar system simulation that includes the sun, earth, mars, venus, and mercury. The relative position and speed the planets accurately models what the actual orbits are in the real solar system. Additionally, the time is kept track of. When the simulation is over, it displays the final state of the solar system when it ended.
- The music and poem verse are inspired from the movie Interstellar.
- The project was done with SFML 2.5.1.
- Link to video demo: https://www.youtube.com/watch?v=zIb-SWPBKIs

# Instructions
- The program expects the total time and time of each step (think of that as one iteration of the simulation, or one iteration of the window loop) to be received as command line arguments. Additionaly, console input is redirected from the file "res/solar_system.txt".
- From the command line, running the program would look like: **./SolarSystemSimulation 1000000000 500 < planets.txt**. In this case, the total time is 1 billion seconds and every time step is 500 seconds.
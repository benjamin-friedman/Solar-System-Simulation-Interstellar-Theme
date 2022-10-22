# Solar-System-Simulation-Interstellar-Theme
- Simulation for the sun, earth, mars, venus, and mercury. The relative position and speed the planets accurately models what the actual orbits are in the real solar system. Additionally, the time is kept track of.
- The music and poem verse are inspired from the movie Interstellar.
- The project was done with Microsoft Visual Studio 2017 using SFML 2.5.1, but a Makefile is also provided so the program can be run from the command line in Linux.
- Link to video demo: https://www.youtube.com/watch?v=zIb-SWPBKIs

# Instructions
- The program expects the total time and time of each step (think of that as one iteration of the simulation, or one iteration of the window loop) to be received from the command line. Additionaly, console input is redirected from the file "planets.txt".
- From the command line, running the program would look like: **./NBody 1000000000 5000 < planets.txt**. In this case, the total time is 1 billion seconds and every simulates 500 seconds.
- To run this program in Visual Studio 2017, the command line arguments can be set in the project's properties. Right click on the project, click on properties, go to the "Debugging" section, and there is a section to set the command line arguments. This is also assuming you have SFML installed on your computer and properly set up in Visual Studio 2017.

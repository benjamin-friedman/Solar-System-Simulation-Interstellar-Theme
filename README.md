# Solar-System-Simulation-Interstellar-Theme
- Solar system simulation that includes the sun, earth, mars, venus, and mercury. The relative position and speed the planets accurately models what the actual orbits are in the real solar system. Additionally, the time is kept track of. When the simulation is over, it displays the final state of the solar system when it ended.
- The music and poem verse are inspired from the movie Interstellar.
- Link to video demo: https://www.youtube.com/watch?v=zIb-SWPBKIs

# Instructions
- The project was done using C++ and SFML in Linux (Ubuntu). Follow the instructions on SFML's website for how to install it on Linux. https://www.sfml-dev.org/tutorials/2.5/start-linux.php. A different package manager might have to be used depending on what version of Linux is being used.
- A Makefile is provided to compile the code and create an executable file named SolarSystemSimulation. The Makefile is setup to work for SFML when it has been installed on the standard path in Linux.
- Enter "make" to compile the code and create the executable file.
- To run the program, enter **./SolarSystemSimulation [total time] [time step] < res/solar_system.txt**. The total time represents the total time of the simulation, and time step represents one step of the simulation (some passage of time in the solar system, or one iteration of the window loop). For example, **./SolarSystemSimulation 1000000000 500 < res/solar_system.txt** would run the simulation for 1 billion seconds with each time step being 500 seconds.
- SFML can be used in other systems aside from Linux. Refer to the website: https://www.sfml-dev.org/index.php. If this program is run in another system and in an environment that doesn't use the command line directly, the command line arguments would have to be set manually in some other way. For example, SFML can be used in Microsoft Visual Studio on Windows where the command line arguments can be set in the IDE's settings.
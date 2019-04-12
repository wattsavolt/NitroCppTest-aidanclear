Build Process:
1. Download MinGW.
2. Download Eclipse for C++ development.
3. Add MinGW as a toolchain to Eclipse. On windows, add $MinGWPath\bin to Windows Sytem Variables under Path.
4. Create workspace for rectangle test code.
5. Import the three projects as existing projects (under General) into Eclipse.
6. Download rapidjson from here https://github.com/miloyip/rapidjson.
7. Add the rapidjson folder into the Eclipse workspace folder. It needs to be in this folder for the projects to compile.
8. Compile all projects.
9. Add RectangleIntersectionLib lib file to Debug/Release folder of RectangleIntersectionTest or Unitests before running these projects. 
10. RectangleIntersectionTest expects a file name. You can pass this as an argument in run configurations. An absolute path can be used or just put the file in the project folder.
11. The sample.json file in the RectangleIntersectionTest is the same as the sample provided in the instructions.

Project Setup:
UnitTests and RectangleIntersectionTests are exe projects that both reference RectangleIntersectionLib project.

Running UnitTests will run all of the unit tests.

The projects are configured for C++ 11.

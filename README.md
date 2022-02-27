# Algorithm Engineering
Assignments and project of the lecture Algorithm Engineering at FSU Jena
## Scan Enhancer
The scan enhancer removes backgrounds from your ppm scans.
###Installing
To install, simply clone the directory and 
install the binary. <br>
```$./install.sh``` <br>
The binary will be installed to ```/usr/local/bin```. 
You can also build  the program manually or in your IDE of choice with CMake. The target <em>scanEnhancer</em> will
run the program, while <em>testEnhancer</em> will run the unit tests.
###Usage
To run the program, simply call ```scanEnhancer <input> <output>```
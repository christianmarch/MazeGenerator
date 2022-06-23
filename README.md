# MazeGenerator
## Istruzioni compilazione con VSCode (Windows)
#### Senza libreria grafica (visualizzazione su terminale)
1. Commentare metodo display_grid_sfml() (Commentare righe 142-227 su Grid.cpp)
2. Commentare `#include  <SFML/Graphics.hpp>` alla riga 6 di Grid.cpp
3. Decommentare `test.display_grid();` e commentare `test.display_grid_sfml(WIDTH, HEIGHT, CELL_SIZE);` alle righe 289-290 di main.cpp
4. Rimuovere il MAKEFILE dalla cartella principale
5. Compilare con `g++ main.cpp -o main`
6. Eseguire con `main.exe`
#### Con libreria grafica
1. Installare la libreria SFML da https://www.sfml-dev.org/download/sfml/2.5.1/ ed inserirla in C:\Program Files\
2. Nel file c_cpp_properties.json generato da VSCode aggiungere in "configuration"-->"includePath" il percorso della cartella include di SFML-2.5.1 (`"C:\\Program Files\\SFML-2.5.1\\include"`)
3. Avviare il MAKEFILE

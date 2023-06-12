### CI5437 - Inteligencia Artificial 1
##### Prof. Carlos Infante

# Proyecto 1

<div style='text-align: right;'>
Por <a href='https://www.github.com/chrischriscris'>Chus</a> | <a href='https://www.github.com/fungikami'>K</a>
</div>
 
## 1. Introducción

En materia de Inteligencia Artificial, los algoritmos de búsqueda informada son de relevancia para encontrar soluciones a distintos problemas. A* e IDA* son algoritmos de búsqueda informada que utilizan una función heurística para guiar la búsqueda hacia la solución óptima. Mientras mejor sea la heurística, más eficiente será el algoritmo. En particular, la heurística llamada PDB (Pattern Database) permite resolver el problema al proyectarlo en un espacio de estados de menor dimensión, para así solucionar cada subproblema de manera independiente. Si al sumar las soluciones de cada subproblema se cumplen con las características de admisibilidad y consistencia, entonces la heurística PDB es aditiva. En cambio, si no se cumple lo anterior, es no-aditiva y se puede tomar el máximo de las soluciones.

Por ello, en el siguiente trabajo se estudiará el modelo de espacio de estados y los diferentes algoritmos de búsqueda heurística (A* e IDA*) en distintos problemas como N-puzzle, Top-Spin, Torres de Hanoi y Cubo de Rubik.

## 2. Árboles de búsqueda

### 2.1. Implementación de algoritmos de búsqueda

Para estudiar el factor de ramificación de los árboles de búsqueda de cada problema, se implementaron los algoritmos de Búsqueda en Amplitud (*BFS*) y Búsqueda en Profundidad Iterativa (*IDDFS*). Para cada problema, se ejecutaron los algoritmos con y sin eliminación de duplicados, y se registró el número de estados generados a cada profundidad. 
### 2.2. Resultados experimentales

#### 2.2.1. Búsqueda en Amplitud (BFS)
En la siguiente tabla (Tabla 1) se muestran los resultados obtenidos al ejecutar el algoritmo de búsqueda BFS para cada problema durante varios segundos (hasta que la memoria RAM se agotara). En particular, se muestra el número de estados generados en el último nivel alcanzado, así como la ramificación promedio de los árboles de búsqueda.

Para mayor detalles sobre el número de estados generados en cada profundidad y su factor de ramificación, los resultados se encuentran en el archivo `SearchTree/BFS_IDDFS.ods`.

| Puzzle |  Nro. de estados (SP) | Ramificación (SP) | Tiempo (SP) | Nro. de estados (CP) | Ramificación (CP) | Tiempo (CP) |
|:------:|:----------------------------:|:----------------------:| :-------------------:|:----------------------:| :-------------------:|:----------------------:|
|  15-puzzle  | 109602413 | 3.236 | 5s | 163211917 | 2.130 | 6s |
|  24-puzzle  | 67324011 | 3.444 | 4s | 109399155 | 2.340 | 5.5s |
| Top Spin 12-4 | 39089245 | 12 | 5s | 221869069 | 7.872 | 6s |
| Top Spin 14-4 | 113522235 | 14 | 6s | 55567064 | 8.425 | 5.5s |
| Top Spin 17-4 | 25646167 | 17 | 5.5s | 131954182 | 9.171 | 5s |
| Hanoi Tower 4-12 | 76856812 | 5.663 | 5s | 33063208 | 5.14 | 4.5s |
| Hanoi Tower 4-14 | 13569751 | 5.633 | 3.2s | 33063208 | 5.14 | 5s |
| Hanoi Tower 4-18 | 13569751 | 5.633 | 3.5s | 33063208 | 5.14 | 3s |
| Rubik 3x3x3 | 36012943 | 18 | 4s | 8331112 | 13.348 | 3.5s |

Tabla 1 BFS sin y con eliminación de duplicados

En las siguientes figuras se muestra los gráficos obtenidos

| ![NoPruning](./SearchTree/BFSNoPruning.png) | ![Pruning](./SearchTree/BFSPruning.png) |
|:-----------------------------:|:-----------------------------:|
| Figura 2.1 | Figura 2.2 |



#### 2.2.2. Búsqueda en Profundidad Iterativa (IDDFS)
En la siguiente tabla (Tabla 2) se muestran los resultados obtenidos al ejecutar el algoritmo de búsqueda IDDFS para cada problema durante 15 minutos. En particular, se muestra el número de estados generados en el último nivel alcanzado, así como la ramificación promedio de los árboles de búsqueda.

Para mayor detalles sobre el número de estados generados en cada profundidad y su factor de ramificación, los resultados se encuentran en el archivo `SearchTree/BFS_IDDFS.ods`.

| Puzzle |  Nro. de estados (SP) | Ramificación (SP) | Nro. de estados (CP) | Ramificación (CP) |
|:------:|:----------------------------:|:----------------------:| :-------------------:|:----------------------:|
|  15-puzzle  | 38896297583 | 3.236 | 32507303773 | 2.130 |
|  24-puzzle  |  33773166807  | 3.483 | 19269183847 | 2.341 |
| Top Spin 12-4 | 67546215517 | 12 | 13752303583 | 7.873 |
| Top Spin 14-4 | 22250358075 | 14 | 33239982329 | 8.425 |
| Top Spin 17-4 | 7411742281 | 17 | 11100301327 | 9.171 |
| Hanoi Tower 4-12 | 14306094361 | 5.729 | 4604326123 | 5.201 |
| Hanoi Tower 4-14 | 14306094361 | 5.729 | 24021362452 | 5.217 |
| Hanoi Tower 4-18 | 14306094361 | 5.729 | 4604326123 | 5.201 |
| Rubik 3x3x3 | 11668193551 | 18 | 19815150304 | 13.348 |

Tabla 2 IDDFS sin y con eliminación de duplicados



En las siguientes figuras se muestra el número de estados generados en cada profundidad de los árboles de búsqueda, para cada problema.

| ![NoPruning](./SearchTree/IDDFSNoPruning.png) | ![Pruning](./SearchTree/IDDFSPruning.png) |
|:-----------------------------:|:-----------------------------:|
| Figura 2.1 | Figura 2.2 |


### 2.3. Análisis de resultados

Al observar las tablas y las gráficas anteriores, se puede observar como la eliminación de duplicados reduce significativamente el número de estados generados en cada profundidad. Por ejemplo, para el caso de 15-puzzle sin pruning, el número de estados generados con profundidad 15 es de 10<sup>7</sup>, mientras que con pruning es de 10<sup>5</sup>. 

En particular, para el Top-Spin y el Cubo de Rubik 3x3x3, el factor de ramificación sin eliminación de duplicados, se mantiene igual en cada profundidad. Esto se debe a que en estos puzzles no tienen estados inválidos que reduzcan el número de posibles movimientos, como podría ocurrir en el 15-puzzle o en las Torres de Hanoi. Por otro lado, se puede observar que el número de estados generados con eliminación de duplicados hasta una profundidad cercana de 10 en los distintos casos de la Torre de Hanoi es igual. Esto se debe a que, dado que se parte del estado final, no es posible mover los discos más grandes, por lo que los primeros movimientos son los mismos en cada caso hasta cierta profundidad.

Ahora, al comparar la cantidad de estados generados por profundidad entre puzzles, se puede observar que para el Top-Spin y el Cubo de Rubik 3x3x3 se tiene un crecimiento acelerado en el número de estados generados (más de 10<sup>10</sup> estados en una profundidad de 9), mientras que para las Torres de Hanoi y el 15-puzzle el crecimiento es más lento (10<sup>4</sup> estados en profundidad 10). Esto se debe a que en los primeros puzzles se tienen más movimientos posibles que en los últimos, por lo que el factor de ramificación es mayor y puede ser un indicador en el rendimiento de los algoritmos de búsqueda. 

Al comparar entre los distintos algoritmos de búsqueda, la primera diferencia es que con IDDFS se logra llegar a profundidades mayores que con BFS. Esto se debe a que, el consumo de memoria de BFS es mucho mayor que el de IDDFS, por lo que se puede llegar a un límite de memoria antes de llegar a un tiempo de ejecución establecido. Sin embargo, el tiempo de ejecución que puede tomarle a IDDFS llegar a cierta profundidad es mucho mayor que el de BFS. Por ejemplo, para el caso de Cubo de Rubik 3x3x3, el BFS (sin pruning) tomó 4 segundos en llegar a profundidad 6, mientras que para el IDDFS le tomó más 8 minutos.

## 3. Heurísticas

### 3.1. Implementación de heurísticas

#### N-Puzzles (15-puzzle, 24-puzzle)

##### Distancia Manhattan:
Se implementó la distancia Manhattan para el caso de 15-puzzle.

##### PDBs Aditivos:
Las abstracciones utilizadas para generar los PDBs corresponden a subdivisiones del problema, al eliminar piezas del puzzle para ser resueltas por separado. En particular, se utilizó la siguiente abstracción:

| ![15puzzle](./Heuristics/15puzzle.png) | ![24puzzle](./Heuristics/24puzzle.png) |
|:-----------------------------:|:-----------------------------:|
| Figura 3.1 | Figura 3.2 |


#### Torre de Hanoi (4-12, 4-14, 4-18)

##### Máximo de PDBs:

#### Top Spin (12-4, 14-4, 17-4)

##### Máximo de PDBs:



#### Cubo de Rubik 3x3x3

##### Máximo de PDBs:



## 4. Algoritmos de búsqueda informada

### 4.1. Implementación de algoritmos de búsqueda informada

Para el estudio de los algoritmos de búsqueda informada, se implementaron los algoritmos de A* y IDA*.


### 4.2. Resultados experimentales

### 4.3. Análisis de resultados

## 5. Conclusiones


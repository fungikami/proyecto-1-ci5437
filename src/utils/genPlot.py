import matplotlib.pyplot as plt

# Plot data from files
def plotData(files, title, labels, xLabel="Depth", yLabel="Nodes expanded"):
    for i in range(len(files)):
        with open(files[i], "r") as f:
            # JUST PLOT COLUMN: "Number of states"
            data = f.readlines()
            data = [line.strip().split(",") for line in data]

            # Skip first line
            data = data[1:]
            
            data = [line[1] for line in data]
            data = [int(line) for line in data]
            print(data)

            plt.plot(data, label=labels[i])

    # Y axis 10**1, 10**2, 10**3, 10**4, 10**5, 10**6...
    plt.yscale("log")
    plt.xlabel(xLabel)
    plt.ylabel(yLabel)
    plt.title(title)
    plt.legend()
    plt.show()

# SEARCH ALGORITHMS
noPruning = [
    "15puzzle_np.csv",
    "24puzzle_np.csv",
    "topSpin12-4_np.csv",
    "topSpin14-4_np.csv",
    "topSpin17-4_np.csv",
    "hanoiTower4-12_np.csv",
    "hanoiTower4-14_np.csv",
    "hanoiTower4-18_np.csv",
    "rubik3Sticker_np.csv",
]

pruning = [
    "15puzzle_p.csv",
    "24puzzle_p.csv",
    "topSpin12-4_p.csv",
    "topSpin14-4_p.csv",
    "topSpin17-4_p.csv",
    "hanoiTower4-12_p.csv",
    "hanoiTower4-14_p.csv",
    "hanoiTower4-18_p.csv",
    "rubik3Sticker_p.csv",
]

labels = [
    "15-puzzle", 
    "24-puzzle", 
    "Top Spin 12-4", 
    "Top Spin 14-4", 
    "Top Spin 17-4", 
    "Hanoi Tower 4-12", 
    "Hanoi Tower 4-14", 
    "Hanoi Tower 4-18", 
    "Rubik 3-sticker"
]


# BFS
noPruningBFS = [ "data/BFS/" + file for file in noPruning ]
pruningBFS = [ "data/BFS/" + file for file in pruning ]
plotData(noPruningBFS, "BFS (No pruning) \nNodes expanded vs Depth", labels)
plotData(pruningBFS, "BFS (Pruning) \nNodes expanded vs Depth", labels)

# IDDFS
noPruningIDDFS = [ "data/IDDFS/" + file for file in noPruning ]
pruningIDDFS = [ "data/IDDFS/" + file for file in pruning ]
plotData(noPruningIDDFS, "IDDFS (No pruning) \nNodes expanded vs Depth", labels)
plotData(pruningIDDFS, "IDDFS (Pruning) \nNodes expanded vs Depth" , labels)

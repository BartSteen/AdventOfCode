def split(line): 
    return [int(ch) for ch in line]

#read in input
f = open("input.txt")
hmap = [split(line) for line in f.read().split("\n")]

# check for low points
lp = []
coords = []

for i in range(len(hmap)):
    for j in range(len(hmap[i])):
        val = hmap[i][j]
        if (i > 0):
            if hmap[i-1][j] <= val:
                continue
        if (i < len(hmap) - 1):
            if hmap[i+1][j] <= val:
                continue
        if (j > 0):
            if hmap[i][j-1] <= val:
                continue
        if (j < len(hmap[i]) - 1):
            if hmap[i][j+1] <= val:
                continue
        lp.append(hmap[i][j])
        coords.append((i,j))

#calculate score
score = 0
for val in lp:
    score += 1 + val

print("part 1 result: " + str(score))

#part 2

#print(coords)

def findLowerNeighbours(point):
    x,y = point
    val = hmap[x][y]
    nbs = []

    if val == 9:
        nbs.append(point)

    if (x > 0):
        if hmap[x-1][y] < val:
            nbs.append((x-1,y))
    if (x < len(hmap) - 1):
        if hmap[x+1][y] < val:
            nbs.append((x+1, y))
    if (y > 0):
        if hmap[x][y-1] < val:
            nbs.append((x,y-1))
    if (y < len(hmap[x]) - 1):
        if hmap[x][y+1] < val:
            nbs.append((x, y+1))
    return nbs

#returns the cordinates that flow to the point: (a,b)
def findBasin(point, bas):
    bas.append(point)
    x,y = point
    if (x > 0):
        if (((x-1, y) not in bas) and all( p in bas for p in findLowerNeighbours((x-1,y)))):
            findBasin((x-1, y), bas)

    if (x < len(hmap) - 1):
        if (((x+1, y) not in bas) and all( p in bas for p in findLowerNeighbours((x+1,y)))):
            findBasin((x+1, y), bas)
    if (y > 0):
        if (((x, y-1) not in bas) and all( p in bas for p in findLowerNeighbours((x,y-1)))):
            findBasin((x, y-1), bas)
    if (y < len(hmap[x]) - 1):
        if (((x, y+1) not in bas) and all( p in bas for p in findLowerNeighbours((x,y+1)))):
            findBasin((x, y+1), bas)
    
    return bas

#for co in coords:
#    print(findBasin(co, []))

#get the three largest
sizes = [len(findBasin(co, [])) for co in coords]
sizes.sort(reverse=True)

prod = 1
for i in range(min(3, len(sizes))):
    prod = prod * sizes[i]
print("part 2 result: " + str(prod))

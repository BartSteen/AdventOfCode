f = open("carinput.txt", "r")
lines = f.readlines()

input = []

for line in lines:
    input.append(list(map(int, line.split(" "))))


input.sort(key=lambda x: (x[2], x[1]))


curDay = -1
curIndex = 0
sol = []

while (curIndex < len(input)):
    if (input[curIndex][1] < curDay):
        curIndex+=1
    else:
        sol.append(input[curIndex])
        curDay = input[curIndex][2] + 1

#improvement round
change = True
while change:
    change = False
    sol.sort(key=lambda x: x[2])
    for i in range(len(sol)):
        if i == 0:
            startv = -1
        else:
            startv = sol[i-1][2]
        if i == len(sol)-1:
            endv = 1000
        else:
            endv = sol[i+1][1]

        #improvement range = [startv, endv]
        best = sol[i]
        for inp in input:
            if inp[1] > startv and inp[2] < endv and inp[2] - inp[1] > best[2] - best[1]:
                best = inp


        if best != sol[i]:
            change = True
            sol[i] = best
            break





for s in sol:
    print(s[0], end= " ")



#Dynamic programming?
#2d array 


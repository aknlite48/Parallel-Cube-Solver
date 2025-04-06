#cube solver
#2x2
import random

import argparse

parser = argparse.ArgumentParser(description="E")
parser.add_argument('-s', type=int, required=True, help="Number of shuffles")
args = parser.parse_args()

solved = [1,2,3,4,5,6,7,8]
moves_list = ["d","di","r","ri","f","fi"]

def move(c,m):
    if m=="d":
        c[4],c[5] = c[5],c[4]
        c[5],c[7] = c[7],c[5]
        c[6],c[7] = c[7],c[6]
    if m=="di":
        c[4],c[6] = c[6],c[4]
        c[6],c[7] = c[7],c[6]
        c[7],c[5] = c[5],c[7]
    if m=="r":
        c[3],c[7] = c[7],c[3]
        c[7],c[5] = c[5],c[7]
        c[5],c[1] = c[1],c[5]
    if m=="ri":
        c[1],c[3] = c[3],c[1]
        c[1],c[5] = c[5],c[1]
        c[5],c[7] = c[7],c[5]
    if m=="f":
        c[2],c[6] = c[6],c[2]
        c[6],c[7] = c[7],c[6]
        c[7],c[3] = c[3],c[7]
    if m=="fi":
        c[2],c[3] = c[3],c[2]
        c[3],c[7] = c[7],c[3]
        c[7],c[6] = c[6],c[7]


def shuffle(c,n_moves):
    moves_list = ["d","di","r","ri","f","fi"]
    shuff=[]
    for i in range(0,n_moves):
        m = random.choice(moves_list)
        move(c,m)
        shuff.append(m)
    return shuff




#c = move(solved,"r")
#print(c)
#print(solved)
#BFS to solve
#store states as the moves required to get there

def solve(c):
    c_orig = [i for i in c]
    if c_orig == solved:
        print("already solved")
    moves_list = ["d","di","r","ri","f","fi"]
    Q = []
    depth = 0
    for i in moves_list:
        Q.append([i])
    k = 1
    while len(Q)>0:
        #print('iteration %i'%(k))
        s = Q.pop(0)
        print("current depth: %i || Nodes searched: %i || Nodes list: %i"%(depth,k,len(Q)),end='\r')
        c = [i for i in c_orig]
        if len(s)>depth:
            depth = len(s)
        for i in s:
            move(c,i)
        if c==solved:
            sol = s
            print('\nSolution found')
            #print('iterations=%i'%(k))
            c = [i for i in c_orig]
            break
        for i in moves_list:
            s1 = s+[i]
            Q.append(s1)
        k+=1
    return sol

c = [i for i in solved]

#shuff = shuffle(c,int(input('shuffle:')))
shuff = shuffle(c,args.s)
#shuff = shuffle(c,20)
print(shuff)
#print(c)

sol = solve(c)
print(sol)







import numpy as np
K = []
Sgm = []
F = []
Z = []
K_num = {}

def data_input():
    global K,Sgm,F,S,Z
    with open('nfa.txt', 'r') as f:
        lines = f.readlines()
    Sgm = lines[0].split()
    F = np.zeros((len(lines)-1)*len(Sgm), dtype=np.int32).reshape((len(lines)-1),len(Sgm))
    K_num['#'] = -1
    for i in range(1,len(lines)):
        K.append(lines[i][0])
        K_num[K[i-1]] = i-1
    for i in range(1,len(lines)):
        for j in range(len(lines[i][1:].split())):
            if len(lines[i][1:].split()[j]) > 1: # 能到多处
                mul = int(''.join([str(K_num[n]) for n in lines[i][1:].split()[j].split('_')]))
                F[i-1,j] = -mul #用于区分
            else:
                F[i-1,j] = K_num[lines[i][1:].split()[j]]

def ns2n(n):
    if n < -1:
        n = -n
        m = []
        while n > 0:
            m.append(str(n%10))
            n //= 10 
        return [int(mm) for mm in m]#np.array(m, dtype=np.int32)
    elif n == -1: #因为闭包函数的m接收list
        return []
    else:
        return [n]
    
def e_closure(K): # 传入状态集，不申明global可以这么写
    global II
    for k in K:
        n = F[k][0]
        m = ns2n(n) 
        II.add(k)
        if len(m) > 0:
            for n in m:            
                if n not in II:
                    II.add(n)        
                    II = II.union(e_closure([n]))           
    return II

def move(k, sgm): #传入状态和符号
    n = F[k, sgm] 
    return ns2n(n) #状态集
    
pre_I_queue = [] #新的 DFA集合，即将要访问的集合
I_queue = [] # DFA 集合队列
II = set() #求闭包前都要初始化
I = e_closure({0}) #一个set
pre_I_queue.append(I)
I_queue.append(I)
F_DFA = np.zeros(3).reshape(-1,3)

def main():
    while 1:
        global I,II #当前状态
        
        if len(pre_I_queue) == 0:
            break
        else:
            I = pre_I_queue[0]
            print(I, end='')           
            for sgm in range(1,len(Sgm)):
                I_next = set()
                print(" SGM:", sgm, end=',')
                for i in I:
                    II = set()
                    e_move = e_closure(move(i,sgm))
                    II = set()
#                     print(i, e_move, end='')
                    II = set()
                    I_next = I_next.union(e_move)
                print(I_next, end='')
                if I_next not in I_queue and len(I_next)!=0:
                    I_queue.append(I_next)
                    pre_I_queue.append(I_next)                  
            pre_I_queue.pop(0) 
            print()
    print("DFA状态数为：",len(I_queue)) 
	
data_input()	
main()

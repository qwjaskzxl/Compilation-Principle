NonTermSet = set()  # 非终结符集合
TermSet = set()  # 终结符集合
First = {}  # First集
Follow = {}  # Follow集
GramaDict = {}  # 处理过的产生式
Code = []  # 读入的产生式
AnalysisList = {}  # 分析表
StartSym = ""  # 开始符号
EndSym = '#'  # 结束符号为“#“
Epsilon = "~"  # 由于没有epsilon符号用“~”代替


# 构造First集
def getFirst():
    global NonTermSet, TermSet, First, Follow, FirstA
    for X in NonTermSet:
        First[X] = set()  # 初始化非终结符First集为空
    for X in TermSet:
        First[X] = set(X)  # 初始化终结符First集为自己
    Change = True
    while Change:  # 当First集没有更新则算法结束
        Change = False
        for X in NonTermSet:
            for Y in GramaDict[X]:
                k = 0
                Continue = True
                while Continue and k < len(Y):
                    if not First[Y[k]] - set(Epsilon) <= First[X]:  # 没有一样的就添加，并且改变标志
                        if Epsilon not in First[Y[k]] and Y[k] in NonTermSet and k > 0:  # Y1到Yi候选式都有~存在
                            Continue = False
                        else:
                            First[X] |= First[Y[k]] - set(Epsilon)
                            Change = True
                    if Epsilon not in First[Y[k]]:
                        Continue = False
                    k += 1
                if Continue:  # X->~或者Y1到Yk均有~产生式
                    First[X] |= set(Epsilon)
                    # FirstA[Y] |= set(Epsilon)


# 构造Follow集
def getFollow():
    global NonTermSet, TermSet, First, Follow, StartSym
    for A in NonTermSet:
        Follow[A] = set()
    Follow[StartSym].add(EndSym)  # 将结束符号加入Follow[开始符号]中
    Change = True
    while Change:  # 当Follow集没有更新算法结束
        Change = False
        for X in NonTermSet:
            for Y in GramaDict[X]:
                for i in range(len(Y)):
                    if Y[i] in TermSet:
                        continue
                    Flag = True
                    for j in range(i + 1, len(Y)):  # continue
                        if not First[Y[j]] - set(Epsilon) <= Follow[Y[i]]:
                            Follow[Y[i]] |= First[Y[j]] - set(Epsilon)  # 步骤2 FIRST(β)/~ 加入到FOLLOW(B)中。
                            Change = True
                        if Epsilon not in First[Y[j]]:
                            Flag = False
                        break
                    if Flag:
                        if not Follow[X] <= Follow[Y[i]]:  # 步骤3 β->~,把FOLLOW(A)加到FOLLOW(B)中
                            Follow[Y[i]] |= Follow[X]
                            Change = True


# 构造分析表
def getAnalysisList():
    for nonX in NonTermSet:
        AnalysisList[nonX] = dict()
        row = AnalysisList[nonX]
        flag = True
        for Y in GramaDict[nonX]:
            for term in TermSet:
                if term in First[Y[0]] and term in First[nonX]:
                    row[term] = nonX+'->'+Y
        if Epsilon in First[nonX] and flag:
            flag = False
            for tmp in Follow[nonX]:
                row[tmp] = nonX+'->'+Epsilon
    print('分析表:')
    for nonX in NonTermSet:
        print('     ', nonX, AnalysisList[nonX])


# 查询分析表
def findAnalysisList(non, ter):
    try:
        tmp = AnalysisList[non][ter]
        X, Y = tmp.split('->')
    except Exception as e:
        print('find error ')  # M[A,a]为空，发现语法错误
        print(e)
        pass
    return Y


# 显示格式
def display(show_list):
    for item in show_list:
        print('     %-25s' % item, end='')
    print()


# LL(1)分析器
def analyzer():
    head = ["Stack", "StackTop", 'NowStr', "InputStr", "Action"]
    # inputStr = 'i+i*i' + EndSym
    inputStr = input("请输入表达式：") + EndSym
    print('分析过程：')
    display(head)
    stack = []
    location = 0
    stack.append(EndSym)
    stack.append(StartSym)
    stack_top = stack.pop()
    while stack_top != EndSym and location < len(inputStr):
        if stack_top in TermSet and inputStr[location] == stack_top:  # x = a != '#'，
            mess = '匹配，弹出栈顶符号' + stack_top + '并读入输入串的下一符号' + inputStr[location + 1]
            display([stack, stack_top, inputStr[location], inputStr[location + 1: len(inputStr)], mess])
            location += 1
            stack_top = stack.pop()
        elif stack_top in NonTermSet and inputStr[location] in TermSet:  # x为一非终结符A,则查M[A,a]
            result = findAnalysisList(stack_top, inputStr[location])
            if result == Epsilon:  # M[A,a]中的产生式为A->~，只将A弹出
                mess = '弹出栈顶符号' + stack_top + '因M[' + stack_top + ',' + inputStr[location] + ']中为' + stack_top
                mess = mess + '->~,故不压栈'
            else:  # M[A,a]中的产生式右部符号串按逆序逐一压入栈中
                mess = '弹出栈顶符号' + stack_top + ',将M[' + stack_top + ',' + inputStr[
                    location] + ']中的' + stack_top + '->' + result + '的' + result
                mess = mess + '逆序压栈'
                tmp_list = []
                for char in result:
                    tmp_list.append(char)
                tmp_list.reverse()
                stack.extend(tmp_list)
            display([stack, stack_top, inputStr[location], inputStr[location + 1: len(inputStr)], mess])
            stack_top = stack.pop()
        else:
            break
    if stack_top == EndSym and inputStr[location] == EndSym:  # x = a = '#' 分析成功,分析器停止工作
        display([[], '#', '#', '', '匹配，分析成功'])
        print()
        print('************************')
        print('*   Analysis Success   *')
        print('************************')
    else:
        print('Analysis Error')


# 读取文法
def readGrammar():
    try:
        file = open('grammar.txt', 'r')
        for line in file:
            line = line.replace('\n', "")
            Code.append(line)
    except IOError as e:
        print(e)
        exit()
    finally:
        file.close()
    return Code


# 初始化
def init():
    global NonTermSet, TermSet, First, Follow, StartSym, Code
    Code = readGrammar()
    n = int(len(Code))
    print('产生式个数:', n)
    StartSym = Code[0][0]
    print("开始符号：", StartSym)
    print('产生式：G[', StartSym, ']:')
    for i in range(n):
        X, Y = Code[i].split('->')
        print('     ', Code[i])
        NonTermSet.add(X)
        Y = Y.split('|')
        for Yi in Y:
            TermSet |= set(Yi)
        if X not in GramaDict:
            GramaDict[X] = set()
        GramaDict[X] |= set(Y)  # 生成产生式集
    TermSet -= NonTermSet
    print('非终结符:', NonTermSet)
    print('终结符:', TermSet)
    getFirst()
    getFollow()
    print("FIRST集:")
    for k in NonTermSet:
        print('     FIRST[', k, ']: ', First[k])
    print("FOLLOW集:")
    for k, v in Follow.items():
        print('     FOLLOW[', k, ']: ', v)
    TermSet -= set(Epsilon)
    TermSet |= set(EndSym)
    getAnalysisList()
    analyzer()

init()

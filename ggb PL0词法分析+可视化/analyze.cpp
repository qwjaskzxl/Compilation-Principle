#include <stdio.h>
#include <string.h>
#include "pl0.h"
#include <windows.h> 
int flag=0;

void error(int n)
{
	char space[81];
	memset(space, 32, 81);
	space[cc-1] = 0;
	printf("****出现错误\n");
	fprintf(fa1, "****出现错误\n");
	err++;
}

char* getSym(int n)
{
	return symbolName[n];
}
char* getCate(int n)
{
	return category[n];
}

anotheCheck()
{
	strcpy(id, a);	//自身值放在id中 
	int k,i = 0;
	int j = norw-1;
	do
	{
   		k = (i+j)/2;
   		if(strcmp(id, word[k]) <= 0)
      		j = k-1;
   		if(strcmp(id, word[k]) >= 0)
       		i = k+1;
	}while(i <= j);

	if(i-1 > j)		//如果找到了，i、j差为2。（保留字）	
		{
   			sym = wsym[k]; 
		}
	else											
		{
   			sym = ident;  //未找到(标识符)
		}   
}
	
int getch()
{
    if(cc == ll)								  //一行字符取完 
    {
        if(feof(fin))                             //文件全部读完才返回-1 
        {
        	if(flag==1)
				anotheCheck();
//	  		printf("%4d: %4d    %s\n",counter,sym,a);
			SymNumber[counter]=sym;
			strcpy(SymName[counter],getSym(sym));
			strcpy(SymValue[counter],a);
			strcpy(SymCate[counter],getCate(sym));
			counter++;
            return -1;
        }
        ll = 0;
        cc = 0;
        //printf("%d ", cx);
        //fprintf(fa1, "%d", cx);
        ch = ' ';
        while(ch != 10) 						 //取一行字符到line中 
        {
            if(fscanf(fin, "%c", &ch) == EOF)    //文件全读完跳出 
            {
                line[ll] = 0;
                break;
            }
//            printf("%c", ch);
//            fprintf(fa1, "%c", ch);		//将读取到的字符逐个往fa1中写入（包含空格）				
            line[ll] = ch;
            ll++;
        }
//        printf("\n");
        //fprintf(fa1, "\n");
    }
    ch = line[cc];    //下一个字符赋给ch，并把指针加1 
    cc++;
    return 0;
}

//每调用一次，获取一个单词。忽略空格，但是不是以空格分割。
int getsym() //调用一次获取一个单词 
{
    int i, j, k;
    while(ch == ' ' || ch == 10 || ch == 9)   //忽略空格，换行符，tab 
    {
        getchdo;  				    //ch指向下一个非空格的字符，读完就再读取一行字符 
    }	
    if(ch >= 'a' && ch <= 'z')			//标识符、保留字 
    {
    	flag=1;
        k = 0;
        memset(a,0,sizeof(a));
        do
        {
            if(k < al)
            {
                a[k] = ch;
                k++;
            }
            getchdo;
        }while(ch >= 'a' && ch <= 'z' || ch >= '0' && ch <= '9');
    
    
        a[k] = 0;
        strcpy(id, a);	//自身值放在id中 
        i = 0;
        j = norw-1;
        do
        {
            k = (i+j)/2;
            if(strcmp(id, word[k]) <= 0)
                j = k-1;
            if(strcmp(id, word[k]) >= 0)
                i = k+1;
        }while(i <= j);
        
        if(i-1 > j)		//如果找到了，i、j差为2。（保留字）	
        {
            sym = wsym[k]; 
        }
        else											
        {
            sym = ident;  //未找到(标识符)
        }   
        flag=0;
    }
    else
    {
    	k = 0;
    	memset(a,0,sizeof(a));
        if(ch >= '0' && ch <= '9')     	//数字 ，组成无符号整数存放在num中 
        {
            num = 0;
            sym = number;
            do
            {
            	a[k] = ch;
                num = num * 10 + ch - '0';
                k++;
                getchdo;
            }while(ch >= '0' && ch <= '9');
            a[k] = 0;
            k--;
            if(k > nmax)
            {
                error(30);
            }   
        }
        else						   	//界符、运算符 （双符号类型的要单独判断，其他查表） 
        {
        	a[k] = ch;
        	k++;
            if(ch == ':')			//':'
            {
                getchdo;
                if(ch == '=')
                {
                	a[k] = ch;
                	k++;
                    sym = becomes;
                    getchdo;
                }
                else
                {
                    sym = nul;
                }
            }
            else
            {
                if(ch == '<')	 	
                {
                    getchdo;
                    if(ch == '=')
                    {
                        sym = leq;	//'<='
                        a[k] = ch;
                		k++;
                        getchdo;
                    }
                    else
                    {
                        sym = lss;	//'<'
                    }
                }
                else
                {
                    if(ch == '>')	
                    {
                        getchdo;
                        if(ch == '=')
                        {
                            sym = geq;//'>='
                            a[k] = ch;
                			k++;
                            getchdo;
                        }
                        else
                        {
                            sym = gtr;//'>'
                        }
                    }
                    else 
					{
						
						sym = ssym[ch]; 	//查表，不能查到的单个字符用nul 
                    	if(sym != period)   
                    	{
                    	    getchdo;
                    	}
                    	else						 
                    		{
                    			SymNumber[counter]=sym;
                    			a[k]=0; 
								strcpy(SymName[counter],getSym(sym));
								strcpy(SymValue[counter],a);
								strcpy(SymCate[counter],getCate(sym));
								counter++;
								return -1; 		//碰到'.',程序结束,返回-1。
					}		}
                }
            }
        a[k] = 0;    
        }
    
    }
//	counter++;
//	printf("%4d: %4d    %s\n",counter,sym,a);
	SymNumber[counter]=sym;
	strcpy(SymName[counter],getSym(sym));
	strcpy(SymValue[counter],a);
	strcpy(SymCate[counter],getCate(sym));
	counter++;
    return 0;
}

void init()
{
	int i;
	for(int i = 0; i < 256; i++)
		ssym[i] =  nul;
	ssym['+'] = plus;
	ssym['-'] = minus;
	ssym['*'] = times;
	ssym['/'] = slash;
	ssym['('] = lparen;
	ssym[')'] = rparen;
	ssym['='] = eql;
	ssym[','] = comma;
	ssym['.'] = period;
	ssym['#'] = neq;
	ssym[';'] = semicolon;
	
	strcpy(&(word[0][0]), "begin");
	strcpy(&(word[1][0]), "call");
	strcpy(&(word[2][0]), "const");
	strcpy(&(word[3][0]), "do");
	strcpy(&(word[4][0]), "end");
	strcpy(&(word[5][0]), "if");
	strcpy(&(word[6][0]), "odd");
	strcpy(&(word[7][0]), "procedure");
	strcpy(&(word[8][0]), "read");
	strcpy(&(word[9][0]), "then");
	strcpy(&(word[10][0]), "var");
	strcpy(&(word[11][0]), "while");
	strcpy(&(word[12][0]), "write");
	
	wsym[0] = beginsym;
	wsym[1] = callsym;
	wsym[2] = constsym;
	wsym[3] = dosym;
	wsym[4] = endsym;
	wsym[5] = ifsym;
	wsym[6] = oddsym;
	wsym[7] = procsym;
	wsym[8] = readsym;
	wsym[9] = thensym;
	wsym[10] = varsym;
	wsym[11] = whilesym;
	wsym[12] = writesym;
	
} 

int main()
{
//	printf("请输入要分析的文件名\n");
//	scanf("%s", fname);
	fin = fopen("input.txt", "r");
	if(fin) 
	{
//		printf("请输入要保存的文件名\n");
//		scanf("%s", fname);
		fa1 = fopen("output.txt", "w");
		init();
		err = 0;
		cc = cx = ll = 0;
		ch = ' ';
		while(getsym() != -1)
		{
			
		}
		printf("词法分析，分析出单词数量：%d\n\n",counter);
		printf("序号     单词         类型编码          类型符号            实际类型\n\n"); 
		fprintf(fa1,"词法分析，分析出单词数量：%d\n\n",counter);
		fprintf(fa1,"序号     单词         类型编码          类型符号            实际类型\n\n");
		for(int i=0;i<counter;i++)
		{
			printf("%-8d %-16s%-15d%-20s%-20s\n",i+1,SymValue[i],SymNumber[i],SymName[i],SymCate[i]);
			fprintf(fa1,"%-8d %-16s%-15d%-20s%-20s\n",i+1,SymValue[i],SymNumber[i],SymName[i],SymCate[i]);
		}
		printf("\n\n分析完毕");
		fclose(fa1);
	}
	else
	{
		printf("找不到文件\n");
	}
	printf("\n");
//	system("pause");
	exit(0);
	return 0;
}

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
	printf("****���ִ���\n");
	fprintf(fa1, "****���ִ���\n");
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
	strcpy(id, a);	//����ֵ����id�� 
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

	if(i-1 > j)		//����ҵ��ˣ�i��j��Ϊ2���������֣�	
		{
   			sym = wsym[k]; 
		}
	else											
		{
   			sym = ident;  //δ�ҵ�(��ʶ��)
		}   
}
	
int getch()
{
    if(cc == ll)								  //һ���ַ�ȡ�� 
    {
        if(feof(fin))                             //�ļ�ȫ������ŷ���-1 
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
        while(ch != 10) 						 //ȡһ���ַ���line�� 
        {
            if(fscanf(fin, "%c", &ch) == EOF)    //�ļ�ȫ�������� 
            {
                line[ll] = 0;
                break;
            }
//            printf("%c", ch);
//            fprintf(fa1, "%c", ch);		//����ȡ�����ַ������fa1��д�루�����ո�				
            line[ll] = ch;
            ll++;
        }
//        printf("\n");
        //fprintf(fa1, "\n");
    }
    ch = line[cc];    //��һ���ַ�����ch������ָ���1 
    cc++;
    return 0;
}

//ÿ����һ�Σ���ȡһ�����ʡ����Կո񣬵��ǲ����Կո�ָ
int getsym() //����һ�λ�ȡһ������ 
{
    int i, j, k;
    while(ch == ' ' || ch == 10 || ch == 9)   //���Կո񣬻��з���tab 
    {
        getchdo;  				    //chָ����һ���ǿո���ַ���������ٶ�ȡһ���ַ� 
    }	
    if(ch >= 'a' && ch <= 'z')			//��ʶ���������� 
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
        strcpy(id, a);	//����ֵ����id�� 
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
        
        if(i-1 > j)		//����ҵ��ˣ�i��j��Ϊ2���������֣�	
        {
            sym = wsym[k]; 
        }
        else											
        {
            sym = ident;  //δ�ҵ�(��ʶ��)
        }   
        flag=0;
    }
    else
    {
    	k = 0;
    	memset(a,0,sizeof(a));
        if(ch >= '0' && ch <= '9')     	//���� ������޷������������num�� 
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
        else						   	//���������� ��˫�������͵�Ҫ�����жϣ�������� 
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
						
						sym = ssym[ch]; 	//������ܲ鵽�ĵ����ַ���nul 
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
								return -1; 		//����'.',�������,����-1��
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
//	printf("������Ҫ�������ļ���\n");
//	scanf("%s", fname);
	fin = fopen("input.txt", "r");
	if(fin) 
	{
//		printf("������Ҫ������ļ���\n");
//		scanf("%s", fname);
		fa1 = fopen("output.txt", "w");
		init();
		err = 0;
		cc = cx = ll = 0;
		ch = ' ';
		while(getsym() != -1)
		{
			
		}
		printf("�ʷ�����������������������%d\n\n",counter);
		printf("���     ����         ���ͱ���          ���ͷ���            ʵ������\n\n"); 
		fprintf(fa1,"�ʷ�����������������������%d\n\n",counter);
		fprintf(fa1,"���     ����         ���ͱ���          ���ͷ���            ʵ������\n\n");
		for(int i=0;i<counter;i++)
		{
			printf("%-8d %-16s%-15d%-20s%-20s\n",i+1,SymValue[i],SymNumber[i],SymName[i],SymCate[i]);
			fprintf(fa1,"%-8d %-16s%-15d%-20s%-20s\n",i+1,SymValue[i],SymNumber[i],SymName[i],SymCate[i]);
		}
		printf("\n\n�������");
		fclose(fa1);
	}
	else
	{
		printf("�Ҳ����ļ�\n");
	}
	printf("\n");
//	system("pause");
	exit(0);
	return 0;
}

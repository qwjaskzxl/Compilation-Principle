#define norw 13 		/*�ؼ��ָ���*/ 
#define nmax 14			//number�����λ�� 
#define al 10			//���ŵ���ĳ��� ���ž���+ - �����
#define cxmax 200		//���������������

enum symbol {
	nul, ident, number, plus, minus, times, slash, oddsym, eql, neq,
	lss, leq, gtr, geq, lparen, rparen, comma, semicolon, period, becomes,
	beginsym, endsym, ifsym, thensym, whilesym, writesym, readsym, dosym, 
	callsym, constsym, varsym, procsym,
};

char symbolName[50][12] =
	{"nul", "ident", "number", "plus", "minus", "times", "slash", "oddsym", "eql", "neq",
	"lss", "leq", "gtr", "geq", "lparen", "rparen", "comma", "semicolon", "period", "becomes",
	"beginsym", "endsym", "ifsym", "thensym", "whilesym", "writesym", "readsym", "dosym", 
	"callsym", "constsym", "varsym", "procsym"};
	
char category[50][12] =
	{"δ֪", "��ʶ��", "����", "�����", "�����", "�����", "�����", "������","�����", "�����",
	"�����", "�����", "�����", "�����", "���", "���", "���", "���", "���", "�����",
	"������","������","������","������","������","������","������","������","������","������","������","������"};
		
int SymNumber[5000];
char SymName[5000][30];
char SymValue[5000][30];
char  SymCate[5000][30];

int counter = 0;

FILE* fa1;				//����������ļ����׵�ַ �׵�ַ�������ָ�� 
char ch;				//getch��ȡ���ַ� 
enum symbol sym;
char id[al+1];			//��ǰ��ident
int num; 
int cc, ll; 			//getch������
int cx; 				//���������ָ�룬ȡֵ��Χ0-cxmax-1 
char line[81];
char a[al+1];			//��ȡһ������ ��ʱ�������� 
 
char word[norw][al];	//������13�� ����begin end if ʲô�� 
enum symbol wsym[norw]; //�����ֶ�Ӧ�ķ��� begin��Ӧbeginsym 
enum symbol ssym[256];	//���ַ��ķ���ֵ 
 
FILE* fin; 
FILE* fout;
char fname[al];			//������ļ���
int err;
 
#define getchdo			if(-1==getch()) return -1;
 
void error(int n);

#define norw 13 		/*关键字个数*/ 
#define nmax 14			//number的最大位数 
#define al 10			//符号的最的长度 符号就是+ - 神马的
#define cxmax 200		//最多的虚拟机代码数

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
	{"未知", "标识符", "常数", "运算符", "运算符", "运算符", "运算符", "保留字","运算符", "运算符",
	"运算符", "运算符", "运算符", "运算符", "界符", "界符", "界符", "界符", "界符", "运算符",
	"保留字","保留字","保留字","保留字","保留字","保留字","保留字","保留字","保留字","保留字","保留字","保留字"};
		
int SymNumber[5000];
char SymName[5000][30];
char SymValue[5000][30];
char  SymCate[5000][30];

int counter = 0;

FILE* fa1;				//输出分析的文件和首地址 首地址是虚拟机指针 
char ch;				//getch读取的字符 
enum symbol sym;
char id[al+1];			//当前的ident
int num; 
int cc, ll; 			//getch计数器
int cx; 				//虚拟机代码指针，取值范围0-cxmax-1 
char line[81];
char a[al+1];			//读取一个符号 暂时存在这里 
 
char word[norw][al];	//保留字13个 就是begin end if 什么的 
enum symbol wsym[norw]; //保留字对应的符号 begin对应beginsym 
enum symbol ssym[256];	//单字符的符号值 
 
FILE* fin; 
FILE* fout;
char fname[al];			//输入的文件名
int err;
 
#define getchdo			if(-1==getch()) return -1;
 
void error(int n);

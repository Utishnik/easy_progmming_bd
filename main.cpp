#include <iostream>
#include <string>
#include <string.h>
#include <fstream>

//#define Debug1

using namespace std;

const int count_col = 2;
const int max_len_str = 256;
string path_bd = "baza_data.txt";
const int MaxCountToken = 1024;



const int type_cnt = 3;
const int max_len_type_name = 32;
char map_type[type_cnt][max_len_str] = {
	"Int",
	"String",
	"Double"
};


void write(char str[count_col]);
string* read();
void rwrite();

void write(char str[count_col][max_len_str])
{
	ofstream file;
	file.open(path_bd, ofstream::app);

	if (!file.is_open()) { printf("error open file!\n"); return; }
	for (int i = 0; i < count_col; i++) file << str[i] << " ";
	file << endl;
	file.close();

}

struct DOUBLE {
	double a;
	int col;
	int str;
};

struct STRING {
	string a;
	int col;
	int str;
};

struct INTEGER {
	int a;
	int col;
	int str;
};

struct Map_Value_BD_Str {
	int start_indx;
	int end_indx;
};

void find_value_in_bd(char* value, string* db, int col_count, int str_len)
{
	int** tokens_len_list = (int**)malloc(sizeof(int*) * col_count);
	int* iterator_Tokens = (int*)malloc(sizeof(int) * MaxCountToken);
	for (int i = 0; i < MaxCountToken; i++)
		iterator_Tokens[i] = 0;

	string* find_bd = (string*)malloc(sizeof(string) * col_count);
	int* len_list = (int*)malloc(sizeof(int) * col_count);

	if (find_bd != 0)
		memset(find_bd, 0, sizeof(string) * col_count);
	for (int i = 0; i < col_count; i++)
	{
		string str_BD;
		/*	for (int j = 0; (db->c_str())[i][j] != '\0';j++)
		{
			str_BD[j] = (db[i]->c_str())[j];
		}*/
		int len_s_bd = 0;

		for (int j = 0; db[i][j] != '\0'; j++) { str_BD[j] = (db[i][j]); len_s_bd++; }


		//printf("%s\n", str_BD);


		//printf("\t [ %d ]\n", len_s_bd);

		string str_BD_no_probel_in_start_penis_hui_blyat_aaaa = "";

		int iterator = 0;

		for (int k = 0; k < len_s_bd; k++)
		{
			if (str_BD[k] == ' ')
				iterator++;
			else
				break;
		}

		//printf("%d = i\n", iterator);

		for (int k = 0; k < len_s_bd - iterator; k++) str_BD_no_probel_in_start_penis_hui_blyat_aaaa[k] = '.';



		for (int k = iterator; k < len_s_bd; k++)
			str_BD_no_probel_in_start_penis_hui_blyat_aaaa[k - iterator] = str_BD[k];
		str_BD_no_probel_in_start_penis_hui_blyat_aaaa[len_s_bd - iterator] = '\0';


		for (int o = 0; o < len_s_bd; o++)
			find_bd[i][o] = str_BD_no_probel_in_start_penis_hui_blyat_aaaa[o];
		len_list[i] = len_s_bd;

		/*	for (int o = 0; o < len_s_bd; o++)
				printf("%c", find_bd[i][o]);
			printf("\n");*/

	}


	for (int i = 0; i < col_count; i++)
	{
		tokens_len_list[i] = (int*)malloc(sizeof(int) * MaxCountToken);
	}
#ifdef Debug1
	printf("DB\n");
#endif
	for (int i = 0; i < col_count; i++)
	{
		int cnt_tok = 0;
		string copy_str_bd = find_bd[i];

		string tokens[MaxCountToken];
		int token_char_iterator = 0;
#ifdef Debug1
		printf("DB2\n");
#endif

		for (int j = 0; j < len_list[i]; j++)
		{
			if (copy_str_bd[j] == ' ')
			{

				tokens[iterator_Tokens[i]][token_char_iterator + 1] = '\0';

				tokens_len_list[i][iterator_Tokens[i]] = token_char_iterator;

				printf("%d\n", iterator_Tokens[i]);
				iterator_Tokens[i]++;
				tokens[iterator_Tokens[i]] = " ";
				token_char_iterator = 0;
				cnt_tok++;
			}
			else {
				tokens[iterator_Tokens[i]][token_char_iterator] = copy_str_bd[j];
				token_char_iterator++;
			}

		}
#ifdef Debug1
		printf("DB3\n");
#endif





		//for (int j = 0; j < cnt_tok+1; j++) {
		//	for (int o = 0; o < len_list[i]; o++)
		//	{
		//		printf("%c", tokens[j][o]);

		//	}
		//	printf("\n");
		//}

		int str_number = -1;
		bool isfind = true;


		//printf("%d\n", cnt_tok);
		for (int j = 0; j < cnt_tok + 1; j++)
		{
			/*	for (int o = 0; o < tokens_len_list[j]; o++)
				{
					printf("%c", tokens[j][o]);
				}
				printf("\n");*/
			if (strlen(value) == strlen(tokens[j].c_str()))
			{
				for (int k = 0; k < strlen(value); k++)
				{
					if (value[k] != tokens[j][k]) { break; isfind = false; }
				}
			}
			else
			{
				isfind = false;
				break;
			}

			if (isfind) {
				str_number = i + 1;
				//printf("%d\n", str_number);
			}
			isfind = false;
		}


	}


	for (int i1 = 0; i1 < col_count; i1++) {
		for (int j1 = 0; j1 < iterator_Tokens[i1]; j1++)
		{
			printf("LEN \t %d\n", tokens_len_list[i1][j1]);
		}
	}

	for (int i = 0; i < col_count; i++)
	{
		free(tokens_len_list[i]);
	}
	free(tokens_len_list);
	free(find_bd);
	free(len_list);



}
#define Max_Db_Size 1024
string  *read(int *retsize)
{
	int double_iterator;
	int string_iterator;
	int int_iterator;

	ifstream rfile;
	rfile.open(path_bd);
	if (!rfile.is_open()) { printf("error open read file!!!\n"); return NULL; }

	string str = "";
	int count_str = 0;

	string* db = (string*)malloc(sizeof(string) * Max_Db_Size);

	{
		int i = 0;
		while (!rfile.eof())
		{
			str = "";
			getline(rfile, str);
			db[i] = str;
			i++;
			count_str++;
		}
	}

	*retsize=count_str;

	rfile.close();

	return db;

}

int counter_probels_string(const char* str)
{
	int counter = 0;
	for (int i = 0; i < strlen(str); i++)
		if (str[i] == ' ') counter++;
	return counter;
}


void add_str_end_probel( char *str)
{
	int len=strlen(str);
	str[len]=' ';
	str[len+1]='\0';
}



int *find_token( char* str,  char* token,int len_list_token_number,int *len_ret)
{
	int count_probel = counter_probels_string(str);
	printf("%d\n", count_probel);
	char** tokens = (char**)malloc(sizeof(char*) * (count_probel + 10));

	for (int i = 0; i < count_probel+10; i++)
		tokens[i] = (char*)malloc(sizeof(char)  * strlen(str));


	printf("len = %ld\n", strlen(str));
	printf("db1\n");

	int itrator = 0;
	int iter_char = 0;

	add_str_end_probel(str);

	for(int i=0;i<strlen(str);i++)
	{
		if (str[i] != ' ')
		{
			tokens[itrator][iter_char] = str[i];
		}
		iter_char++;
		if (str[i] == ' ')
		{
			tokens[itrator][iter_char-1] = '\0';
			itrator++;
			iter_char = 0;
		}
	}



	/*for (int i = 0; i < strlen(str); i++)
	{

		if (str[i] != ' ') { tokens[itrator][iter_char] = str[i]; printf("%c", tokens[itrator][iter_char]); }
		printf("\n%d\n", i);
		iter_char++;
		if (str[i] == ' ')
		{
			printf("\n");
			for (int j = 0; j < strlen(str); j++)
			{
				tokens[itrator][j] = ' ';
			}

			tokens[itrator][iter_char] = '\0';
			iter_char = 0; itrator++;



		}

	}*/


	int findtklen=strlen(token);

	int *list_number_token=(int*)malloc(sizeof(int)*len_list_token_number);
	



	int iteratorn2=0;
	for (int i = 0; i < itrator; i++)
	{
		int lentk=strlen(tokens[i]);

		if(lentk==findtklen)	
		{
			bool boolean1=false;
			for(int j=0;j<lentk;j++)
			{
				if(tokens[i][j]==token[j])
				{
					boolean1=true;
				}
				else
				{
					boolean1=false;
					break;
				}
			}
			if(boolean1==false) {continue;}
			else {list_number_token[iteratorn2]=i;iteratorn2++;}
		}
		else
		{
			continue;
		}
	}

	*len_ret=iteratorn2;

	for (int i = 0; i < (count_probel + 10); i++)
		free((void*)tokens[i]);

	free(tokens);

	

	if(iteratorn2>0) return list_number_token;
	else return NULL;

}

int main()
{
	//char str1[64]="3.1415";
	//char str2[64] = "niger";
	//char arr[count_col][256];

	//for (int i = 0; i < 64; i++)
	//{
	//	arr[0][i] = str1[i];
	//}
	//for (int i = 0; i < 64; i++)
	//{
	//	arr[1][i] = str2[i];
	//}

	//write(arr);

	string testdb[3] = {
		"   niger 1  ",
		"ilya niger  dyra",
		"aaa 3.14 "
	};

	char value[10] = "niger";

	//find_value_in_bd(value, testdb, 3, 0);


	 char o1[1024] = "121 ilia pizdaliz ebaniy hhhh   gfffg 121 121  pi 344334";
	 char o2[1024] = "  ";

	int retlen=0;
	string *bd=read(&retlen);

	if(bd==NULL) printf("empty bazadata!\n");

	for(int i=0;i<retlen;i++)
	{
		cout <<bd[i]<<endl;
	}


	system("pause");
}

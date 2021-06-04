#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct instruction_s 
{ 
	int step; 
	int index; 
};
char* get_word(char* s, int n);
void get_sentence(char** lines, struct instruction_s* instructions, int n_instructions, char* sentence);

int main(int argc,char **argv)
{
	char* text[10000];
	FILE* textfile;
	textfile = fopen(argv[1],"r");	
	FILE* instructiontext ;
	
	instructiontext=fopen(argv[2],"r");	 
	int index = 0;				
	char line[200] ;
	
	while(!feof(textfile)){		
	
		fgets(line,200,textfile);

		text[index] =  malloc(sizeof(char)*200);
		strcpy(text[index],line) ;
		
		memset(line,'\0',sizeof(line));
		
		
		index++;
	}
	int a=0;
	struct instruction_s instruction1;
	struct instruction_s *pointer;
	pointer = &instruction1;
	
	pointer=(struct instruction_s *)malloc(sizeof(struct instruction_s)*200);
	
	for(;!feof(instructiontext);a++)		
	{	

		fscanf(instructiontext,"%d %d",&pointer[a].step,&pointer[a].index);

		pointer[a].index -=1;
	}
	int n_instructions = a-1;
	char sentence[10000]={0};
	get_sentence(text,pointer,n_instructions,sentence);
	
	printf("%s\n",sentence);
	
	fclose(textfile);
	fclose(instructiontext);
	return 0;
}
void get_sentence(char** lines, struct instruction_s* instructions, int n_instructions, char* sentence)

{
	int a=0,lineindex,j = 0;
	while(j<200)
	{
		sentence[j] = 0;
		j += 1;
	}
	char* word;
	lineindex = (instructions[a].step)- 1;
	word = get_word(lines[lineindex],instructions[a].index) ;
	
	
	a = 0;
	while(word[a]>10)
	{
		if(word[a]>='A' && word[a]<='Z')
		{
			word[a]+=32;
		}
		a += 1;
	}
	a = 0;
	
	strcat(sentence,word);
	
	a++;
	for(;a<n_instructions;a++){
		lineindex+=instructions[a].step;
		
		word=get_word(lines[lineindex],instructions[a].index);	
		int a=0;
		while(word[a]>10)
		{
			if(word[a]>='A' && word[a]<='Z')
			{
				word[a]+=32;
			}
			else
			{
				word[a] = word[a];
			}
			a += 1;
		}
		strcat(sentence," ");
		strcat(sentence,word);
	}

}


char* get_word(char* s,int n)
{
	int a=0;
	int counter = 0;
	int spac = 0;
	char* last;
	last=(char*)malloc(sizeof(char)*50);
	while(counter<=n && s[a]!=10)
	{
		if (((s[a] > 122 || s[a] < 97) && (s[a] > 90 || s[a] < 65)))
		{
			spac=0;
		}
		else if(((s[a] <= 122 && s[a] >= 97) || (s[a] <= 90 && s[a] >= 65)) && spac == 0 )
		{
			counter++;
			spac=1;
		}
		else 
		{
			counter = counter;
		}
	a += 1;
	}
	a--;
	counter = 0;
	while((s[a]>=65 && s[a]<=90) || (s[a]>=97 && s[a]<=122))
	{
		
		last[counter] = s[a] ;
		a += 1;
		counter +=1;
	}
	last[counter]=0;
	return last;
}

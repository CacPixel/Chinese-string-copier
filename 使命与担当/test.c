#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <locale.h>
int main()
{
	FILE* fp1;
	FILE* fp2;
	char character[5048] = { 0 };
	char main_note[5048];
	int length = 0;
	fp1 = fopen("ʹ���뵣��.txt", "r");
	fp2 = fopen("ѧϰ�ʼ�.txt", "w");
	setlocale(LC_ALL, "zh-CN");
	scanf("%s", main_note);
	while (!feof(fp1))
	{
		fscanf(fp1, "%c", &character[length]);
		if (character[length] != '\n' || isgraph(character[length]))
		{
			/*����һ�����ڲ��Զ�����ӳ��ȵļ��*/
			length++;
			printf("���Ӷ�ȡ�У���ǰ����Ϊ%d\n", length);
			Sleep(100);
		}
		else if (character[length] == 0xA3)
		{
			character[length + 1] = '\0';
			printf("��������ˣ�����Ϊ��%d", strlen(character));  //������û������
			Sleep(1000);
			length = 0;
			if ((strstr(character, main_note)) != 0)
			{
				fprintf(fp2, "%s\n", character);
			}
		}
		else
		{
			character[length] = '\0';
			length = 0;
			if ((strstr(character, main_note)) != 0)
			{
				fprintf(fp2, "%s\n", character);
			}
		}

	}
	fclose(fp1);
	fclose(fp2);
	return 0;
}

#include <stdio.h>
#include <string.h>

int main()
{
	FILE* fp1;
	FILE* fp2;
	char all[5048] = { 0 };  //存放从文件读取的所有字符
	char main_note[5048];  //输入的笔记关键词
	int pos1, pos2;  //用于标定字符串范围
	char found = 0;  //判断是否找到的变量
	char buf[5048] = { 0 };

	fp1 = fopen("使命与担当.txt", "r");
	fp2 = fopen("学习笔记.txt", "w");


	for (int i = 0; !feof(fp1); i++)//从 fp1 读取所有字符
	{
		fscanf(fp1, "%c", &all[i]);
	}
	fclose(fp1);

	scanf("%s", main_note);  //输入需要记录的笔记内容

	pos1 = -1;
	pos2 = -1;
	for (int i = 0; all[i] != 0;)
	{
		if (all[i] == 10)//寻找 \n
		{
			pos1 = pos2 + 1;
			pos2 = i;  //重新标定字符串范围
			found = 1;
		}
		else if (all[i] == (char)0xa1)
		{
			if (all[i + 1] == (char)0xa3)//寻找句号
			{
				if (all[i + 2] != (char)0xa1 && all[i + 3] != (char)0xb1 && all[i + 4] != (char)0xa3 && all[i + 5] != (char)0xac) //排除文章引用一段话后 。”， 的情况
				{
					pos1 = pos2 + 1;
					pos2 = i + 1;
					found = 1;
				}

			}
		}
		else if (all[i] == (char)0xa3)
		{
			if (all[i + 1] == (char)0xba)//寻找冒号
			{
				if (all[i + 2] != (char)0xa1 && all[i + 3] != (char)0xb0) //排除文章引用一段话前 ：“ 的情况
				{
					pos1 = pos2 + 1;
					pos2 = i + 1;
					found = 1;
				}

			}
		}

		if (found)
		{
			for (int i = 0; i < 5048; i++) //清空buf
			{
				buf[i] = 0;
			}
			for (int j = 0; j < pos2 - pos1 + 1; j++) //将一句完整的话存入buf
			{
				buf[j] = all[pos1 + j];
			}
			if (strstr(buf, main_note)) //若 buf 里有输入的笔记关键字则输出到文件
			{
				fputs(buf, fp2);
				fputs("\n\n", fp2);
			}
		}


		if (all[i] >= 0 && all[i] <= 127) //当前字符是ASCII范围则向前进 1 否则是汉字进 2
		{
			i++;
		}
		else
		{
			i += 2;
		}
		found = 0;
	}
	puts("Done!");
	fclose(fp2);
	return 0;
}

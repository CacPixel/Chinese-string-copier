#include <stdio.h>
#include <string.h>

int main()
{
	FILE* fp1;
	FILE* fp2;
	char all[5048] = { 0 };  //��Ŵ��ļ���ȡ�������ַ�
	char main_note[5048];  //����ıʼǹؼ���
	int pos1, pos2;  //���ڱ궨�ַ�����Χ
	char found = 0;  //�ж��Ƿ��ҵ��ı���
	char buf[5048] = { 0 };

	fp1 = fopen("ʹ���뵣��.txt", "r");
	fp2 = fopen("ѧϰ�ʼ�.txt", "w");


	for (int i = 0; !feof(fp1); i++)//�� fp1 ��ȡ�����ַ�
	{
		fscanf(fp1, "%c", &all[i]);
	}
	fclose(fp1);

	scanf("%s", main_note);  //������Ҫ��¼�ıʼ�����

	pos1 = -1;
	pos2 = -1;
	for (int i = 0; all[i] != 0;)
	{
		if (all[i] == 10)//Ѱ�� \n
		{
			pos1 = pos2 + 1;
			pos2 = i;  //���±궨�ַ�����Χ
			found = 1;
		}
		else if (all[i] == (char)0xa1)
		{
			if (all[i + 1] == (char)0xa3)//Ѱ�Ҿ��
			{
				if (all[i + 2] != (char)0xa1 && all[i + 3] != (char)0xb1 && all[i + 4] != (char)0xa3 && all[i + 5] != (char)0xac) //�ų���������һ�λ��� ������ �����
				{
					pos1 = pos2 + 1;
					pos2 = i + 1;
					found = 1;
				}

			}
		}
		else if (all[i] == (char)0xa3)
		{
			if (all[i + 1] == (char)0xba)//Ѱ��ð��
			{
				if (all[i + 2] != (char)0xa1 && all[i + 3] != (char)0xb0) //�ų���������һ�λ�ǰ ���� �����
				{
					pos1 = pos2 + 1;
					pos2 = i + 1;
					found = 1;
				}

			}
		}

		if (found)
		{
			for (int i = 0; i < 5048; i++) //���buf
			{
				buf[i] = 0;
			}
			for (int j = 0; j < pos2 - pos1 + 1; j++) //��һ�������Ļ�����buf
			{
				buf[j] = all[pos1 + j];
			}
			if (strstr(buf, main_note)) //�� buf ��������ıʼǹؼ�����������ļ�
			{
				fputs(buf, fp2);
				fputs("\n\n", fp2);
			}
		}


		if (all[i] >= 0 && all[i] <= 127) //��ǰ�ַ���ASCII��Χ����ǰ�� 1 �����Ǻ��ֽ� 2
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

#include "head.h"

int menu_select()
{
	int MenuItem;

	printf("\n ");
	printf("          |  **************����ϵͳ**************       |              \n");
	printf("          | ----------------------------------------    |          \n");
	printf("          |                  ���˵���                   |          \n");
	printf("          | ----------------------------------------    |          \n");
	printf("          |	  1 ^ ^ ^ ^ @ ��ʾ������Ϣ @ ^ ^ ^ ^  	    |             \n");
	printf("          |	  2 ^ ^ ^ ^ @ ��ʾѡ����Ϣ @ ^ ^ ^ ^  	    |             \n");
	printf("          |	  3 ^ ^ ^ ^ @  ���д��   @ ^ ^ ^ ^	        |             \n");
	printf("          |	  4 ^ ^ ^ ^ @ ��ʾѡ�ֳɼ� @ ^ ^ ^ ^	    |             \n");
	printf("          |	  5 ^ ^ ^ ^ @ ��ʾѡ������ @ ^ ^ ^ ^	    |             \n");
	printf("          |	  0 ^ ^ ^ ^ @ ���沢�˳�ϵͳ@   ^ ^ ^ ^ 	    |             \n");

	do
	{
		printf("\n������ѡ��(0-5):");
		fflush(stdin);
		scanf("%d", &MenuItem);
	} while (MenuItem<0 || MenuItem>5);

	return MenuItem;
}
/**********************************************
*Function Name:r_show
*Description:������Ϣ
***********************************************/
void r_show()
{
	int i;
	FILE *fp;
	fp = fopen("rater.txt", "r+");
	if (fp == NULL)
	{
		printf("�ļ���ʧ�ܣ�\n");
		exit(-1);
	}
	else
	{
		printf("�������Ա𣬵绰\n");
		for (i = 0; i<6; i++)
		{
			fscanf(fp, "%s %s %ld\n", &r[i].name, &r[i].sex, &r[i].num);
		}
		for (i = 0; i<6; i++)
		{
			printf("%2s %3s %8ld\n", r[i].name, r[i].sex, r[i].num);
		}
	}
	fclose(fp);
}
/**********************************************
*Function Name:p_show
*Description:ѡ����Ϣ
***********************************************/
void p_show()
{
	int i;
	FILE *fp;
	fp = fopen("player.txt", "r+");
	if (fp == NULL)
	{
		printf("�ļ���ʧ�ܣ�\n");
		exit(-1);
	}
	else
	{
		printf("���  ����   �Ա�  ��Ŀ����  ���  ��Ŀ��� �༶  �绰����\n");
		for (i = 0; i<6; i++)
		{
			fscanf(fp, "%d %s %s %s %s %s %s %ld\n", &p[i].snum, &p[i].name, &p[i].sex, &p[i].act, &p[i].acte, &p[i].pacte, &p[i].sclass, &p[i].num);
		}
		for (i = 0; i<6; i++)
		{
			printf("%3d %6s %4s %9s %3s %8s %10s %9ld\n", p[i].snum, p[i].name, p[i].sex, p[i].act, p[i].acte, p[i].pacte, p[i].sclass, p[i].num);
		}
	}
	fclose(fp);
}
/**********************************************
*Function Name:score
*Description:���
***********************************************/
extern void score()
{
	float grade[10];
	float sum;
	int i, j, n, x;
	float temp;
	for (n = 0; n < 6; n++)
	{
		printf("---����� %d λѡ�ִ��---\n", p[n].snum);
		for (x = 0; x < 5; x++)
		{
			printf("��� %d λ���д��:\n", x + 1);
			scanf("%f", &grade[x]);
		}
		for (i = 0; i < 5; i++)
		{
			for (j = 0; j < 5; j++)
			{
				if (grade[j] > grade[j + 1])
				{
					temp = grade[j];
					grade[j] = grade[j + 1];
					grade[j + 1] = temp;
				}
			}
		}
		sum = 0;
		for (i = 1; i < 4; i++)
		{
			sum = sum + grade[i];
		}
		p[n].grade = sum / 4.0;
		printf("ƽ���ɼ���%.2f\n", p[n].grade);
	}
}

/**********************************************
*Function Name:show
*Description:ѡ�ֳɼ�
***********************************************/
extern void show()
{
	int i;
	printf("��� ����   �Ա�  ��Ŀ���� ��� ��Ŀ���   �༶    �绰����  ƽ���ɼ�\n");
	for (i = 0; i < 5; i++)
	{
		printf("%3d %6s %4s %9s %5s %9s %10s %9ld %8.2f\n", p[i].snum, p[i].name, p[i].sex, p[i].act, &p[i].acte, &p[i].pacte, p[i].sclass, p[i].num, p[i].grade);
	}
}

/**********************************************
*Function Name:grade
*Description:ѡ������
***********************************************/
extern void placing()
{
	int i, j;
	int x;
	struct Player r[100];
	struct Player temp;
	for (i = 0; i < 6; i++)
	{
		r[i] = p[i];
	}
	x = 0;
	for (i = 0; i < 6; i++)
	{
		if (strcmp(p[i].acte, "A") == 0)
		{
			sing[x] = r[i];
			x++;
		}
	}
	samount = x;
	for (i = 0; i < x - 1; i++)
	{
		for (j = 0; j < x - 1; j++)
		{
			if (sing[j].grade < sing[j + 1].grade)
			{
				temp = sing[j];
				sing[j] = sing[j + 1];
				sing[j + 1] = temp;
			}
		}
	}
	printf("----����������----\n");
	printf("��� ����   �Ա�  ��Ŀ���� ��� ��Ŀ���   �༶    �绰����  ƽ���ɼ�  ����\n");
	for (i = 0; i < x; i++)
	{
		printf("%3d %6s %4s %9s %3s %8s %10s %9ld %8.2f %5d\n",sing[i].snum, sing[i].name, sing[i].sex, sing[i].act, &sing[i].acte, sing[i].pacte, sing[i].sclass, sing[i].num, sing[i].grade, i + 1);
	}
	//�赸ѡ������
	//struct Student dance[100];
	x = 0;
	for (i = 0; i < 6; i++)
	{
		if (strcmp(p[i].acte, "B") == 0)
		{
			dance[x] = r[i];
			x++;
		}
	}
	damount = x;
	for (i = 0; i < x - 1; i++)
	{
		for (j = 0; j < x - 1; j++)
		{
			if (dance[j].grade < dance[j + 1].grade)
			{
				temp = dance[j];
				dance[j] = dance[j + 1];
				dance[j + 1] = temp;
			}
		}
	}
	printf("----�赸������----\n");
	printf("��� ����   �Ա�  ��Ŀ���� ��� ��Ŀ���   �༶    �绰����  ƽ���ɼ�  ����\n");
	for (i = 0; i < x; i++)
	{
		printf("%3d %6s %4s %9s %3s %8s %10s %9ld %8.2f %5d\n", dance[i].snum, dance[i].name, dance[i].sex, dance[i].act, dance[i].acte, dance[i].pacte, dance[i].sclass, dance[i].num, dance[i].grade, i + 1);
	}
}
//����ģ��
int samount;
int damount;
extern void save()
{
	int i;
	FILE *fp;
	FILE *fw;
	fp = fopen("sing.txt", "w");
	fw = fopen("dance.txt", "w");
	if (fp == NULL)
	{
		printf("�ļ���ʧ�ܣ�\n");
		exit(-1);
	}
	else
	{
		for (i = 0; i<samount; i++)
		{
			fprintf(fp, "%d %s %s %s %s %s %s %ld %.2f %d\n",sing[i].name, sing[i].sex, sing[i].act, &sing[i].acte, sing[i].pacte, sing[i].sclass, sing[i].num, sing[i].grade, i + 1);
		}
	}
	fclose(fp);
	if (fw == NULL)
	{
		printf("�ļ���ʧ�ܣ�\n");
		exit(-1);
	}
	else
	{
		for (i = 0; i<damount; i++)
		{
			fprintf(fw, "%d %s %s %s %s %s %s %ld %.2f %d\n", dance[i].name, dance[i].sex, dance[i].act, dance[i].acte, dance[i].pacte, dance[i].sclass, dance[i].num, dance[i].grade, i + 1);
		}
	}
	fclose(fp);
}
int main()
{
	while (1)
	{
		switch (menu_select())
		{
		case 1:
			r_show();
			break;
		case 2:
			p_show();
			break;
		case 3:
			score();
			break;
		case 4:
			show();
			break;
		case 5:
			placing();
			break;
		case 0:
			save();
			printf("Thank you for using��\n");
			system("pause");
			return 0;
		}
	}
}
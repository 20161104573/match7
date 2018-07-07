#include "head.h"

int menu_select()
{
	int MenuItem;

	printf("\n ");
	printf("          |  **************评分系统**************       |              \n");
	printf("          | ----------------------------------------    |          \n");
	printf("          |                  主菜单项                   |          \n");
	printf("          | ----------------------------------------    |          \n");
	printf("          |	  1 ^ ^ ^ ^ @ 显示裁判信息 @ ^ ^ ^ ^  	    |             \n");
	printf("          |	  2 ^ ^ ^ ^ @ 显示选手信息 @ ^ ^ ^ ^  	    |             \n");
	printf("          |	  3 ^ ^ ^ ^ @  裁判打分   @ ^ ^ ^ ^	        |             \n");
	printf("          |	  4 ^ ^ ^ ^ @ 显示选手成绩 @ ^ ^ ^ ^	    |             \n");
	printf("          |	  5 ^ ^ ^ ^ @ 显示选手排名 @ ^ ^ ^ ^	    |             \n");
	printf("          |	  0 ^ ^ ^ ^ @ 保存并退出系统@   ^ ^ ^ ^ 	    |             \n");

	do
	{
		printf("\n请输入选项(0-5):");
		fflush(stdin);
		scanf("%d", &MenuItem);
	} while (MenuItem<0 || MenuItem>5);

	return MenuItem;
}
/**********************************************
*Function Name:r_show
*Description:裁判信息
***********************************************/
void r_show()
{
	int i;
	FILE *fp;
	fp = fopen("rater.txt", "r+");
	if (fp == NULL)
	{
		printf("文件打开失败！\n");
		exit(-1);
	}
	else
	{
		printf("姓名，性别，电话\n");
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
*Description:选手信息
***********************************************/
void p_show()
{
	int i;
	FILE *fp;
	fp = fopen("player.txt", "r+");
	if (fp == NULL)
	{
		printf("文件打开失败！\n");
		exit(-1);
	}
	else
	{
		printf("序号  姓名   性别  节目名称  类别  节目类别 班级  电话号码\n");
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
*Description:打分
***********************************************/
extern void score()
{
	float grade[10];
	float sum;
	int i, j, n, x;
	float temp;
	for (n = 0; n < 6; n++)
	{
		printf("---请给第 %d 位选手打分---\n", p[n].snum);
		for (x = 0; x < 5; x++)
		{
			printf("请第 %d 位裁判打分:\n", x + 1);
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
		printf("平均成绩：%.2f\n", p[n].grade);
	}
}

/**********************************************
*Function Name:show
*Description:选手成绩
***********************************************/
extern void show()
{
	int i;
	printf("序号 姓名   性别  节目名称 类别 节目类别   班级    电话号码  平均成绩\n");
	for (i = 0; i < 5; i++)
	{
		printf("%3d %6s %4s %9s %5s %9s %10s %9ld %8.2f\n", p[i].snum, p[i].name, p[i].sex, p[i].act, &p[i].acte, &p[i].pacte, p[i].sclass, p[i].num, p[i].grade);
	}
}

/**********************************************
*Function Name:grade
*Description:选手排名
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
	printf("----唱歌类排名----\n");
	printf("序号 姓名   性别  节目名称 类别 节目类别   班级    电话号码  平均成绩  排名\n");
	for (i = 0; i < x; i++)
	{
		printf("%3d %6s %4s %9s %3s %8s %10s %9ld %8.2f %5d\n",sing[i].snum, sing[i].name, sing[i].sex, sing[i].act, &sing[i].acte, sing[i].pacte, sing[i].sclass, sing[i].num, sing[i].grade, i + 1);
	}
	//舞蹈选手排名
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
	printf("----舞蹈类排名----\n");
	printf("序号 姓名   性别  节目名称 类别 节目类别   班级    电话号码  平均成绩  排名\n");
	for (i = 0; i < x; i++)
	{
		printf("%3d %6s %4s %9s %3s %8s %10s %9ld %8.2f %5d\n", dance[i].snum, dance[i].name, dance[i].sex, dance[i].act, dance[i].acte, dance[i].pacte, dance[i].sclass, dance[i].num, dance[i].grade, i + 1);
	}
}
//保存模块
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
		printf("文件打开失败！\n");
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
		printf("文件打开失败！\n");
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
			printf("Thank you for using！\n");
			system("pause");
			return 0;
		}
	}
}
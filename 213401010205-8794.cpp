#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <windows.h>
# 
using namespace std;

/*ͨѶ¼����Ԫ��*/
typedef struct {
	int num;		 //���
	string name;     //����
	string phonenum; //�绰
	string address;  //��ַ
	string relation; //����
}ElemType;

/*ͨѶ¼����*/
typedef struct Node {
	ElemType data;
	struct Node* next;
}Node, * LinkList;

/*���������б�*/
void Read_LinkList(LinkList& L);                         //��ȡ��Ϣ
void Save_LinkList(const LinkList& L);                   //������Ϣ
void Init_LinkList(LinkList& L);                         //��ʼ��ͨѶ¼����
void Create_LinkList(LinkList& L);                       //������ϵ��
void Delete_LinkList(LinkList& L);                       //ɾ����ϵ��
void Query_LinkList(const LinkList& L);                  //��ѯ��ϵ��
void Modify_LinkList(LinkList& L);                       //�޸���ϵ��
void Print_LinkList(const LinkList& L);                  //ͨѶ¼��ʾ
bool compare(const ElemType& t1, const ElemType& t2);    //����sort�����Ĺ�ϵ
void Sort_LinkList(LinkList& L);                         //ͨѶ¼����
void Clear_LinkList(LinkList& L);                        //ͨѶ¼���
void menu(LinkList& L);      //���ز˵�

/*�������---������*/
int main()
{
	system("color 70");
	LinkList L;
	Init_LinkList(L);
	Read_LinkList(L);
	menu(L);

	return 0;
}

void reRead_LinkList(LinkList& L)
{
	Node* p = L;

	ifstream file("book.txt", ios::in);
	int len = 0;

	file >> len;
	ElemType tem;
	while (len--)
	{

		file >> tem.num >> tem.name >> tem.phonenum >> tem.address >> tem.relation;
		Node* t = new Node;
		t->data = tem;
		t->next = NULL;
		p->next = t;
		p = p->next;//β�巨
	}

	file.close();
}

/*������Ϣ����*/
void reSave_LinkList(LinkList& L)
{
	Node* t = L, * cnt = L;

	ofstream ofile("book.txt", ios::out);
	int len = 0;
	while (cnt->next)
	{
		len++;
		cnt = cnt->next;
	}

	ofile << len << endl;
	while (t)
	{
		if (t != L)

			ofile << t->data.num << "\t" << t->data.name << "\t" << t->data.phonenum << "\t" << t->data.address << "\t" << t->data.relation << endl;
		t = t->next;
	}

	ofile.close();
}

/*��ȡ��Ϣ����*/
void Read_LinkList(LinkList& L)
{
	Node* p = L;
	ifstream infile("contact.txt", ios::in);

	int len = 0;
	infile >> len;

	ElemType tem;
	while (len--)
	{
		infile >> tem.num >> tem.name >> tem.phonenum >> tem.address >> tem.relation;

		Node* t = new Node;
		t->data = tem;
		t->next = NULL;
		p->next = t;
		p = p->next;//β�巨
	}
	infile.close();

}

/*������Ϣ����*/
void Save_LinkList(LinkList& L)
{
	Node* t = L, * cnt = L;
	ofstream outfile("contact.txt", ios::out);

	int len = 0;
	while (cnt->next)
	{
		len++;
		cnt = cnt->next;
	}
	outfile << len << endl;

	while (t)
	{
		if (t != L)
			outfile << t->data.num << "\t" << t->data.name << "\t" << t->data.phonenum << "\t" << t->data.address << "\t" << t->data.relation << endl;

		t = t->next;
	}
	outfile.close();
}


/*��ʼ��ͨѶ¼��������*/
void Init_LinkList(LinkList& L)
{
	L = new Node;
	L->next = NULL;
}

/*������ϵ�˺���*/
void Create_LinkList(LinkList& L)
{
	system("cls");
	cout << "\t\t\t**************��ӭ����������ϵ�˹���***************" << endl;
	Node* t = L;
	int i = 1, flag = 1;
	while (t->next)
	{
		i++;
		t = t->next;
	}
	while (flag)
	{
		Node* p = new Node;
		cout << "\t\t\t����������";
		cin >> p->data.name;
		cout << "\t\t\t����绰��";
		cin >> p->data.phonenum;
		cout << "\t\t\t�����ַ��";
		cin >> p->data.address;
		cout << "\t\t\t������飺";
		cin >> p->data.relation;
		p->data.num = i++;
		p->next = NULL;
		t->next = p;
		t = t->next;
		Save_LinkList(L); //���Ķ��������ļ���
		cout << "\t\t\t���ӳɹ����Ƿ�������ӣ���1 �� 0 ��" << endl;
		cout << "\t\t\t��ѡ��0-1����";
		cin >> flag;
	}
}

/*ɾ����ϵ�˺���*/
void Delete_LinkList(LinkList& L)
{
	system("cls");
	cout << "\t\t\t**************��ӭ����ɾ����ϵ�˹���***************" << endl;
	int sel = 0;
	Node* p = L, * t = NULL;
	ElemType tem;
	cout << "\t\t\t-----------------" << endl;
	cout << "\t\t\t1 �����ɾ��" << endl;
	cout << "\t\t\t2 ������ɾ��" << endl;
	cout << "\t\t\t3 �������˵�" << endl;
	cout << "\t\t\t-----------------" << endl;
	cout << "\t\t\t��ѡ��1-3����";
	cin >> sel;
	while (sel < 1 || sel>3)
	{
		cout << "\t\t\t���벻�Ϸ�,������ѡ��1-3����";
		cin >> sel;
	}
	if (sel == 1)
	{
		int flag = 0;
		cout << "\t\t\t�������ɾ����ϵ�˵ı�ţ�";
		cin >> tem.num;
		while (p->next)
		{

			t = p->next;
			if (t->data.num == tem.num)
			{
				cout << "\t\t\t��ɾ����ϵ����Ϣ���£�" << endl;
				cout << "\t\t\t���\t" << "����\t" << "��ϵ�绰\t" << "��ͥ��ַ\t" << "����" << endl;
				cout << "\t\t\t" << t->data.num << "\t" << t->data.name << "\t" << t->data.phonenum << "\t" << t->data.address << "\t" << t->data.relation << endl;
				flag = 1;
				break;
			}
			p = p->next;
		}
		if (flag == 0) cout << "\t\t\t���޴��ˣ��޷�ɾ����" << endl;
		else
		{
			cout << "\t\t\tȷ��ɾ������1 �� 0 ��" << endl;
			cout << "\t\t\t��ѡ��0-1����";
			cin >> sel;
			while (sel < 0 || sel>1)
			{
				cout << "\t\t\t���벻�Ϸ�,������ѡ��0-1����";
				cin >> sel;
			}
			if (sel == 0);
			else if (sel == 1)
			{
				p->next = t->next;
				delete t;
				cout << "\t\t\tɾ���ɹ���" << endl;
				Save_LinkList(L); //�Ķ��������ļ���
			}
		}
		cout << "\n\t\t\t";
		system("pause");
		Delete_LinkList(L);
	}
	else if (sel == 2)
	{
		int flag = 0;
		cout << "\t\t\t�������ɾ����ϵ�˵�������";
		cin >> tem.name;
		while (p->next)
		{
			t = p->next;
			if (t->data.name == tem.name)
			{
				cout << "\t\t\t��ɾ����ϵ����Ϣ���£�" << endl;
				cout << "\t\t\t���\t" << "����\t" << "��ϵ�绰\t" << "��ͥ��ַ\t" << "����" << endl;
				cout << "\t\t\t" << t->data.num << "\t" << t->data.name << "\t" << t->data.phonenum << "\t" << t->data.address << "\t" << t->data.relation << endl;
				flag = 1;
				break;
			}
			p = p->next;
		}
		if (flag == 0) cout << "\t\t\t���޴��ˣ��޷�ɾ����" << endl;
		else
		{
			cout << "\t\t\tȷ��ɾ������1 �� 0 ��" << endl;
			cout << "\t\t\t��ѡ��0-1����";
			cin >> sel;
			while (sel < 0 || sel>1)
			{
				cout << "\t\t\t���벻�Ϸ�,������ѡ��0-1����";
				cin >> sel;
			}
			if (sel == 0);
			else if (sel == 1)
			{
				p->next = t->next;
				delete t;
				cout << "\t\t\tɾ���ɹ���" << endl;
				Save_LinkList(L); //�Ķ��������ļ���
			}
		}
		cout << "\n\t\t\t";
		system("pause");
		Delete_LinkList(L);
	}
	else if (sel == 3) return;
}

/*��ѯ��ϵ�˺���*/
void Query_LinkList(const LinkList& L)
{
	system("cls");
	cout << "\t\t\t**************��ӭ������ѯ��ϵ�˹���***************" << endl;
	int sel = 0;
	Node* t = L;
	ElemType tem;
	cout << "\t\t\t-----------------" << endl;
	cout << "\t\t\t1 ����Ų�ѯ" << endl;
	cout << "\t\t\t2 ��������ѯ" << endl;
	cout << "\t\t\t3 �������˵�" << endl;
	cout << "\t\t\t-----------------" << endl;
	cout << "\t\t\t��ѡ��1-3����";
	cin >> sel;
	while (sel < 1 || sel>3)
	{
		cout << "\t\t\t���벻�Ϸ�,������ѡ��1-3����";
		cin >> sel;
	}
	if (sel == 1)
	{
		int flag = 0;
		cout << "\t\t\t���������ѯ��ϵ�˵ı�ţ�";
		cin >> tem.num;
		while (t->next)
		{
			t = t->next;
			if (t->data.num == tem.num)
			{
				cout << "\t\t\t����ѯ��ϵ����Ϣ���£�" << endl;
				cout << "\t\t\t���\t" << "����\t" << "��ϵ�绰\t" << "��ͥ��ַ\t" << "����" << endl;
				cout << "\t\t\t" << t->data.num << "\t" << t->data.name << "\t" << t->data.phonenum << "\t" << t->data.address << "\t" << t->data.relation << endl;
				flag = 1;
				break;
			}
		}
		if (flag == 0) cout << "\t\t\t���޴��ˣ�" << endl;
		cout << "\n\t\t\t";
		system("pause");
		Query_LinkList(L);
	}
	else if (sel == 2)
	{
		int flag = 0;
		cout << "\t\t\t���������ѯ��ϵ�˵�������";
		cin >> tem.name;
		while (t->next)
		{
			t = t->next;
			if (t->data.name == tem.name)
			{
				cout << "\t\t\t����ѯ��ϵ����Ϣ���£�" << endl;
				cout << "\t\t\t���\t" << "����\t" << "��ϵ�绰\t" << "��ͥ��ַ\t" << "����" << endl;
				cout << "\t\t\t" << t->data.num << "\t" << t->data.name << "\t" << t->data.phonenum << "\t" << t->data.address << "\t" << t->data.relation << endl;
				flag = 1;
				break;
			}
		}
		if (flag == 0) cout << "\t\t\t���޴��ˣ�" << endl;
		cout << "\n\t\t\t";
		system("pause");
		Query_LinkList(L);
	}
	else if (sel == 3)
	{
		return;
	}
}

/*�޸���ϵ�˺���*/
void Modify_LinkList(LinkList& L)
{
	system("cls");
	cout << "\t\t\t**************��ӭ�����޸���ϵ�˹���***************" << endl;
	int sel = 0;
	Node* t = L;
	ElemType tem;
	cout << "\t\t\t-----------------" << endl;
	cout << "\t\t\t1 ������޸�" << endl;
	cout << "\t\t\t2 �������޸�" << endl;
	cout << "\t\t\t3 �������˵�" << endl;
	cout << "\t\t\t-----------------" << endl;
	cout << "\t\t\t��ѡ��1-3����";
	cin >> sel;
	while (sel < 1 || sel>3)
	{
		cout << "\t\t\t���벻�Ϸ�,���������롾1-3����";
		cin >> sel;
	}
	if (sel == 1)
	{
		int flag = 0;
		cout << "\t\t\t��������޸���ϵ�˵ı�ţ�";
		cin >> tem.num;
		while (t->next)
		{
			t = t->next;
			if (t->data.num == tem.num)
			{
				cout << "\t\t\t���޸���ϵ����Ϣ���£�" << endl;
				cout << "\t\t\t���\t" << "����\t" << "��ϵ�绰\t" << "��ͥ��ַ\t" << "����" << endl;
				cout << "\t\t\t" << t->data.num << "\t" << t->data.name << "\t" << t->data.phonenum << "\t" << t->data.address << "\t" << t->data.relation << endl;
				flag = 1;
				break;
			}
		}
		if (flag == 0) cout << "\t\t\t���޴��ˣ��޷��޸ģ�" << endl;
		else
		{
			ElemType tem;
			cout << "\t\t\t�����޸ĺ����ϵ����Ϣ��" << endl;
			cout << "\t\t\t����������";
			cin >> tem.name;
			cout << "\t\t\t����绰��";
			cin >> tem.phonenum;
			cout << "\t\t\t�����ַ��";
			cin >> tem.address;
			cout << "\t\t\t������飺";
			cin >> tem.relation;
			tem.num = t->data.num;
			cout << "\t\t\tȷ���޸ģ���1 �� 0 ��" << endl;
			cout << "\t\t\t��ѡ��0-1����";
			cin >> sel;
			while (sel < 0 || sel>1)
			{
				cout << "\t\t\t���벻�Ϸ�,������ѡ��0-1����";
				cin >> sel;
			}
			if (sel == 0);
			else if (sel == 1)
			{
				t->data = tem;
				cout << "\t\t\t�޸ĳɹ���" << endl;
				Save_LinkList(L); //���Ķ��������ļ���
			}
		}
		cout << "\n\t\t\t";
		system("pause");
		Modify_LinkList(L);
	}
	else if (sel == 2)
	{
		int flag = 0;
		cout << "\t\t\t��������޸���ϵ�˵�������";
		cin >> tem.name;
		while (t->next)
		{
			t = t->next;
			if (t->data.name == tem.name)
			{
				cout << "\t\t\t���޸���ϵ����Ϣ���£�" << endl;
				cout << "\t\t\t���\t" << "����\t" << "��ϵ�绰\t" << "��ͥ��ַ\t" << "����" << endl;
				cout << "\t\t\t" << t->data.num << "\t" << t->data.name << "\t" << t->data.phonenum << "\t" << t->data.address << "\t" << t->data.relation << endl;
				flag = 1;
				break;
			}
		}
		if (flag == 0) cout << "\t\t\t���޴��ˣ��޷��޸ģ�" << endl;
		else
		{
			ElemType tem;
			cout << "\t\t\t�����޸ĺ����ϵ����Ϣ��" << endl;
			cout << "\t\t\t����������";
			cin >> tem.name;
			cout << "\t\t\t����绰��";
			cin >> tem.phonenum;
			cout << "\t\t\t�����ַ��";
			cin >> tem.address;
			cout << "\t\t\t������飺";
			cin >> tem.relation;
			tem.num = t->data.num;
			cout << "\t\t\tȷ���޸ģ���1 �� 0 ��" << endl;
			cout << "\t\t\t��ѡ��0-1����";
			cin >> sel;
			while (sel < 0 || sel>1)
			{
				cout << "\t\t\t���벻�Ϸ�,������ѡ��0-1����";
				cin >> sel;
			}
			if (sel == 0);
			else if (sel == 1)
			{
				t->data = tem;
				cout << "\t\t\t�޸ĳɹ���" << endl;
				Save_LinkList(L); //���Ķ��������ļ���
			}
		}
		cout << "\n\t\t\t";
		system("pause");
		Delete_LinkList(L);
	}
	else if (sel == 3) return;
}

/*ͨѶ¼��ʾ����*/
void Print_LinkList(const LinkList& L)
{
	system("cls");
	cout << "\t\t\t***************��ӭ����ͨѶ¼��ʾ����***************" << endl;
	Node* t = L->next;
	cout << "\t\t\t-----------------------------------------------------" << endl;
	cout << "\t\t\t���\t" << "����\t" << "��ϵ�绰\t" << "��ͥ��ַ\t" << "����" << endl;
	cout << "\t\t\t-----------------------------------------------------" << endl;
	while (t)
	{
		cout << "\t\t\t" << t->data.num << "\t" << t->data.name << "\t" << t->data.phonenum << "\t\t" << t->data.address << "\t\t" << t->data.relation << endl;
		t = t->next;
	}
	cout << "\t\t\t-----------------------------------------------------" << endl;
	cout << "\t\t\t";
	system("pause");
}

/*ͨѶ¼��������sort�����ĵ���������*/
bool compare(const ElemType& t1, const ElemType& t2)
{
	return t1.name < t2.name;
}

/*ͨѶ¼������*/
void Sort_LinkList(LinkList& L)//����Ӣ����ĸ������˳��
{
	system("cls");
	cout << "\t\t\t***************��ӭ����ͨѶ¼������***************" << endl;
	Node* p = L;
	int cnt = 0, i = 0;
	while (p->next)
	{
		p = p->next;
		cnt++;
	}
	ElemType* arr = new ElemType[cnt];
	p = L;
	while (p->next)
	{
		p = p->next;
		arr[i++] = p->data;
	}
	sort(arr, arr + cnt, compare);
	p = L, i = 0;
	while (p->next)
	{
		p = p->next;
		p->data = arr[i++];
		p->data.num = i;
	}
	cout << "\t\t\t��ͨѶ¼���������������£�" << endl;
	Node* t = L->next;
	cout << "\t\t\t-----------------------------------------------------" << endl;
	cout << "\t\t\t���\t" << "����\t" << "��ϵ�绰\t" << "��ͥ��ַ\t" << "����" << endl;
	cout << "\t\t\t-----------------------------------------------------" << endl;
	while (t)
	{
		cout << "\t\t" << t->data.num << "\t" << t->data.name << "\t" << t->data.phonenum << "\t" << t->data.address << "\t" << t->data.relation << endl;
		t = t->next;
	}
	cout << "\t\t\t-----------------------------------------------------" << endl;
	Save_LinkList(L); //�Ķ��������ļ���
	cout << "\t\t\t";
	system("pause");
}

/*���ͨѶ¼����*/
void Clear_LinkList(LinkList& L)
{
	int sel = 0;
	system("cls");
	cout << "\t\t\t**************��ӭ����ͨѶ¼��չ���*************" << endl;
	cout << "\t\t\t-----------------" << endl;
	cout << "\t\t\t1 ȷ�����ͨѶ¼" << endl;
	cout << "\t\t\t2 �������˵�" << endl;
	cout << "\t\t\t-----------------" << endl;
	cout << "\t\t\t������ѡ��1-2����";
	cin >> sel;
	while (sel < 1 || sel>2)
	{
		cout << "\t\t\t���벻�Ϸ�,���������롾1-2����";
		cin >> sel;
	}
	if (sel == 1)
	{
		Node* head = L;
		if (head == NULL)
		{
			return;
		}
		//�������,�ǲ����ͷ�ڵ�ģ���˴ӵ�һ�������ݵĽڵ㿪ʼ�ͷ�
		Node* curNode = head->next;
		while (curNode != NULL)
		{
			//�ȱ�ס��һ���ڵ��λ��
			Node* nextNode = curNode->next;
			free(curNode);
			curNode = nextNode;
		}
		//��ͷ���nextָ���ÿ�
		head->next = NULL;
		Save_LinkList(L);
		cout << "\n\t\t\t";
		system("pause");
	}
	else if (sel == 2) return;
}
void different()
{
	FILE* fp1, * fp2;
	int line_num = 0, len = 0;
	char buf1[1024] = { 0 }; // �����ݻ���
	char buf2[1024] = { 0 }; // �����ݻ���

	fp1 = fopen("book.txt", "r");
	if (NULL == fp1) {
		printf("open %s failed.\n", "book.txt");

	}

	fp2 = fopen("contact.txt", "r");
	if (NULL == fp2) {
		printf("open %s failed.\n", "contact.txt");

	}


	while (fgets(buf1, 1024, fp1) && fgets(buf2, 1024, fp2))
	{
		line_num++;
		len = strlen(buf1);
		if (buf1[len - 1] == '\n') buf1[len - 1] = '\0';
		len = strlen(buf2);
		if (buf2[len - 1] == '\n') buf2[len - 1] = '\0';
		if (strcmp(buf1, buf2) != 0)
		{
			printf("��%d��\n", line_num);
			printf("%s\n", buf1);
			printf("%s\n", buf2);
		}

	}

	while (fgets(buf1, 1024, fp1)) {
		line_num++;
		printf("f2�ļ�%d��������\n", line_num);
	}


	while (fgets(buf2, 1024, fp2)) {
		line_num++;
		printf("f1�ļ�%d��������\n", line_num);
	}


	fclose(fp1);
	fclose(fp2);



}
void copy()
{

	char src[20] = { "contact.txt" };
	char dest[20] = { "book.txt" };
	char ch;
	FILE* fp1, * fp2;
	if ((fp1 = fopen(src, "r")) == NULL)
	{
		cout << " not open src";
		exit(0);
	}
	if ((fp2 = fopen(dest, "w")) == NULL)
	{
		cout << "not open dest";
		exit(0);
	}
	while ((ch = fgetc(fp1)) != EOF)
	{
		fputc(ch, fp2);
	}

	fclose(fp1);
	fclose(fp2);
	cout << "copy ����";

}
/*���ز˵�����*/
void menu(LinkList& L)
{
	char sel;
	system("cls");
	cout << "\t\t\t***********��ӭ����ͨѶ¼����ϵͳ***********" << endl;
	cout << "\t\t\t����Խ������²���:" << endl;
	cout << "\t\t\t|------------------------------------------|" << endl;
	cout << "\t\t\t|             1   ������ϵ��               |" << endl;
	cout << "\t\t\t|------------------------------------------|" << endl;
	cout << "\t\t\t|             2   ɾ����ϵ��               |" << endl;
	cout << "\t\t\t|------------------------------------------|" << endl;
	cout << "\t\t\t|             3   �޸���ϵ��               |" << endl;
	cout << "\t\t\t|------------------------------------------|" << endl;
	cout << "\t\t\t|             4   ��ѯ��ϵ��               |" << endl;
	cout << "\t\t\t|------------------------------------------|" << endl;
	cout << "\t\t\t|             5   ͨѶ¼��ʾ               |" << endl;
	cout << "\t\t\t|------------------------------------------|" << endl;
	cout << "\t\t\t|             6   ͨѶ¼����               |" << endl;
	cout << "\t\t\t|------------------------------------------|" << endl;
	cout << "\t\t\t|             7   ͨѶ¼���               |" << endl;
	cout << "\t\t\t|------------------------------------------|" << endl;
	cout << "\t\t\t|             8   ����ͨѶ¼               |" << endl;
	cout << "\t\t\t|------------------------------------------|" << endl;
	cout << "\t\t\t|             9  �Ƚ��븱���Ĳ�ͬ          |" << endl;
	cout << "\t\t\t|------------------------------------------|" << endl;
	cout << "\t\t\t|             0   �˳�                     |" << endl;
	cout << "\t\t\t|------------------------------------------|" << endl;
	cout << "\t\t\t��ѡ��0-9����";
	cin >> sel;
	while (sel < '0' || sel>'9')
	{
		cout << "\t\t\t����Ƿ�,������ѡ��0-9����";
		cin >> sel;
	}
	switch (sel)
	{
	case '1':
		Create_LinkList(L);
		menu(L);
		break;
	case '2':
		Delete_LinkList(L);
		menu(L);
		break;
	case '3':
		Modify_LinkList(L);
		menu(L);
		break;
	case '4':
		Query_LinkList(L);
		menu(L);
		break;
	case '5':
		Print_LinkList(L);
		menu(L);
		break;
	case '6':
		Sort_LinkList(L);
		menu(L);
		break;
	case '7':
		Clear_LinkList(L);
		menu(L);
		break;
	case'8':
		copy();
		break;
	case'9':
		different();
		break;
	case '0':
		exit(0);
		break;
	default:
		menu(L);
	}
}
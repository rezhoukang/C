#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h> //ʺɽ���
#include <stdlib.h>//�������ļ�
#include <string.h>
void start();
char welcome();
void all_core(char role);
/*�������(pure)*/int check(const char* user_name, const char* user_password)//const��Ŀ�������ѱ���ֻ����д
{
	FILE* file = fopen("password.txt", "r"); // ���ļ���ֻ��ģʽ
	if (file == NULL) {
		perror("���˺�δע�������ע��\n");
		return 0;
	}
	char file_user_name[50], file_password[50];
	while (fscanf(file, "%s %s", file_user_name, file_password) == 2) {//��ʱ��ȡ2��%s��Ϊ���,ÿ��file��ָ����һ��
		file_user_name[strcspn(file_user_name, "\n")] = '\0';
		file_password[strcspn(file_password, "\n")] = '\0';
		if (strcmp(file_user_name, user_name) == 0 && strcmp(file_password, user_password) == 0) {
			fclose(file);
			//temp_name(user_name);Ϊʲô���˻��
			return 1; // ƥ��ɹ�����¼�ɹ���ע��ʧ��
		}
		else if (strcmp(file_user_name, user_name) == 0) {
			fclose(file);
			return 2; // ����ԣ��û�����ͬע��ʧ��
		}
	}
	fclose(file);
	return 0; // ƥ��ʧ��,��¼ʧ��,ע��ɹ�
}
/*ע���������(pure)*/int user_in(char* user_name, char* password)
{
	FILE* file;
	file = fopen("password.txt", "a"); // ׷��ģʽ���ļ�
	if (file == NULL) {
		perror("error");
		return 1; // ���ش���״̬
	}
	fprintf(file, "%s %s\n", user_name, password);
	fclose(file); // �ر��ļ�
	printf("�û����������ѳɹ�д�뵽 password.txt �ļ���\n");
	return 0;
}
/*ͼ������ṹ(pure)*/typedef struct book// ����ͼ��ṹ��//��struct����typedef����ζ��һ��ѽ,�����ͺ������Ͷ�������Ŷ���Ҷ�дһ���Ͳ�����˹���
{
	int id;             // ͼ��ID
	char title[100];    // ͼ�����
	char author[100];   // ����
	int year;           // �������
	struct book* next;  // ָ����һ��ͼ���ָ��
} book;
/*��¼��ǰ�û���(pure)*/void temp_name(char* name)
{
	FILE* file;
	file = fopen("temp.txt", "w");
	fprintf(file, "%s", name);
	fclose(file);
}
/*���ݽ�����(pure)*/void data_intolink(book* temp)
{
	printf("������ͼ��ID(��0�˳�): ");
	scanf("%d", &temp->id);
	getchar();  // ���ն���Ļ��з�
	if (temp->id == 0)return;
	printf("������ͼ�����: ");
	fgets(temp->title, sizeof(temp->title), stdin);
	temp->title[strcspn(temp->title, "\n")] = '\0';
	printf("����������: ");
	fgets(temp->author, sizeof(temp->author), stdin);
	temp->author[strcspn(temp->author, "\n")] = '\0';
	printf("������������: ");
	scanf("%d", &temp->year);
	getchar();
}
/*��������*/book* creatlink()//���ؽṹ��ָ�����͵ĺ���
{
	book* head, * p, * q;
	head = (book*/*�����Ϊ�˷���ָ�븳ֵ��head���Լ��˸��Ǻ�*/)malloc(sizeof(book));//����һ������
	head->next = NULL;
	p = head;//ָ��head
	q = (book*)malloc(sizeof(book));//q�ֽ���һ������
	do {//��q���鿪ʼ�洢��head����
		data_intolink(q);
		if (q->id == 0) break;
		p->next = q;//q���Ŵ�ʱ��p->next
		p = q;//pͬq��ʱ��ַ��pqҪ����
		q = (book*)malloc(sizeof(book));//q�����ˣ�ȥ����һ��������
	} while (1);
	p->next = NULL;
	return head;
}
/*��ӡ����       �����ò��û��ô�ã������������        */void printlink(book* head)
{
	book* p;
	printf("%-10s%-30s%-30s%-10s\n", "id", "title", "author", "year");
	for (p = head->next; p != NULL; p = p->next) {
		printf("%-10d%-30s%-30s%-10d\n", p->id, p->title, p->author, p->year);
	}
}
/*ɾ��admin�����*/void book_out(int out_id)
{
	FILE* file, * temp, * name;
	int id;
	char title[50];
	char author[50];
	char role[50];
	int year, correct = 0;
	file = fopen("admin", "r");//ͬ��
	if (file == NULL) {
		printf("ͼ���û����\n");
		return;
	}
	temp = fopen("new_admin", "w");
	while (fscanf(file, "%d\t%s\t%s\t%d", &id, title, author, &year) == 4) {
		if (id == out_id)correct++;
	}
	if (correct == 0) {
		fclose(file);fclose(temp);
		remove("new_admin");
		printf("û���Ȿ��\n");
		return;
	}//����ƾ�ս���
	rewind(file);//��ͷ��ʼ
	while (fscanf(file, "%d\t%s\t%s\t%d", &id, title, author, &year) == 4) {
		if (id != out_id) {
			fprintf(temp, "%d\t%s\t%s\t%d\n", id, title, author, year);//����
		}
	}
	fclose(file);fclose(temp);
	if (remove("admin") != 0) {
		printf("ɾ���ļ�ʧ�ܣ�\n");
		return;
	}

	if (rename("new_admin", "admin") != 0) {
		printf("�������ļ�ʧ�ܣ�\n");//����֣��Ҽ��˼��㣬�ٲ���������
		return;
	}
	
	printf("ͼ��ɾ���ɹ���\n");
}
/*ɾ����ǰ�û������,ͬʱ��admin��*/void check_outin(int out_id)
{
	FILE* now_user, * temp, * temp_user, * admin;
	int id;
	char title[100];
	char author[100];
	int year, correct = 0;
	char user[50];//��ǰ�û���
	temp_user = fopen("temp.txt", "r");
	fgets(user, sizeof(user), temp_user);//�ڶ������������������������˿�Ϸ�
	fclose(temp_user);
	user[strcspn(user, "\n")] = '\0';
	now_user = fopen(user, "r");//ͬ��
	if (now_user == NULL) {
		system("cls");
		perror("��û����飬��ʲô�飿\n");
		all_core('1');
	}
	temp = fopen("new.txt", "w");
	admin = fopen("admin", "a");
	while (fscanf(now_user, "%d\t%s\t%s\t%d", &id, title, author, &year) == 4) {//���ֿ������Ƿ����ֿ�������䣬ʵ�����ö���
		if (id == out_id)
			correct++;
	}
	if (correct == 0) {
		fclose(now_user); fclose(temp); fclose(admin);
		system("cls");
		printf("û���Ȿ�飬���һ�\n");
		all_core('1');}//����ƾ�ս���
	rewind(now_user);
	while (fscanf(now_user, "%d\t%s\t%s\t%d", &id, title, author, &year) == 4) {
		if (id != out_id) {
			fprintf(temp, "%d\t%s\t%s\t%d\n", id, title, author, year);//����
		}
		else if (id == out_id) {
			fprintf(admin, "%d\t%s\t%s\t%d\n", id, title, author, year);//��admin���
		}
	}
	fclose(now_user); fclose(temp); fclose(admin);//���رղ�����
	remove(user);//ɾ��
	rename("new.txt", user);
	printf("����ɹ���\n");
}
/*�鿴admin�����*/void print_admin()
{
	system("cls");
	FILE* file = fopen("admin", "r"); // ���ļ���ֻ��ģʽ
	if (file == NULL) {
		system("cls");
		perror("ͼ���û����");
		all_core('3');
	}
	int id;
	char title[100];
	char author[100];
	int year;
	printf("��⣺\n");
	printf("%-10s%-30s%-30s%-10s\n", "id", "title", "author", "year");
	while (fscanf(file, "%d\t%s\t%s\t%d", &id, title, author, &year) == 4) {//��ʱ��ȡ4����Ϊ���,ÿ��file��ָ����һ��
		title[strcspn(title, "\n")] = '\0';
		author[strcspn(author, "\n")] = '\0';
		printf("%-10d%-30s%-30s%-10d\n", id, title, author, year);
	}
	fclose(file);//������ǹر��ˣ���bug�Ұ���
}
/*�鿴��ǰ�û������*/void print_user()
{
	system("cls");
	char name[50];
	FILE* user = fopen("temp.txt", "r");
	fgets(name, sizeof(name), user);
	name[strcspn(name, "\n")] = '\0';
	FILE* file = fopen(name, "r"); // ���ļ���ֻ��ģʽ
	if (file == NULL) {
		system("cls");
		perror("�㲢û�н����");
		all_core('1');
	}
	int id;
	char title[100];
	char author[100];
	int year;
	printf("�����飺\n");
	printf("%-10s%-30s%-30s%-10s\n", "id", "title", "author", "year");
	while (fscanf(file, "%d\t%s\t%s\t%d", &id, title, author, &year) == 4) {//��ʱ��ȡ4����Ϊ���,ÿ��file��ָ����һ��
		//id[strcspn(id, "\n")] = '\0';
		title[strcspn(title, "\n")] = '\0';
		author[strcspn(author, "\n")] = '\0';
		//year[strcspn(year, "\n")] = '\0';
		printf("%-10d%-30s%-30s%-10d\n", id, title, author, year);
	}
	fclose(file);//������ǹر��ˣ���bug�Ұ���
}
/*���������*/void book_in(book* head)//����admin�����ǽ�����ˣ�����user�����Ǳ����ǽ��ߵļ�¼�������һ�
{
	FILE* log, * temp_name;
	char name[50];
	int check_id;
	char check_title[50];
	char check_author[50];
	int check_year; int cant_bookin=0;
	temp_name = fopen("temp.txt", "r");
	fgets(name, sizeof(name), temp_name);//�ڶ������������������������˿�Ϸ�
	name[strcspn(name, "\n")] = '\0';
	fclose(temp_name);
	log = fopen(name, "a");//a��a+�����Դ��޴������ļ�
	book* p;
	FILE* admin = fopen("admin", "r");
	if (strcmp(name, "admin") != 0)//���Ƿ���������˭��Ȩ��hhh
		for (p = head->next; p != NULL; p = p->next) {// ��ͼ����������д���ļ���ÿ����ռһ��
			while (fscanf(admin, "%d\t%s\t%s\t%d", &check_id, check_title, check_author, &check_year) == 4) {
				if (p->id == check_id && strcmp(p->title, check_title) == 0 && strcmp(p->author, check_author) == 0 && p->year == check_year) {
					cant_bookin++;
				}
			}
			if (cant_bookin == 0) {
				fclose(admin);
				fclose(log);
				system("cls");
				printf("�����ȿ�����ʲô���ٽ��\n");
				all_core('1');
			}
			rewind(admin);
			while (fscanf(admin, "%d\t%s\t%s\t%d", &check_id, check_title, check_author, &check_year) == 4){
				if (p->id == check_id && strcmp(p->title, check_title) == 0 && strcmp(p->author, check_author) == 0 && p->year == check_year) {
					fprintf(log, "%d\t%s\t%s\t%d\n", p->id, p->title, p->author, p->year);//����
					fclose(admin);
					fclose(log);
					book_out(p->id);//����user���룬��adminɾ��
				}
			}
		}
	else
		for (p = head->next; p != NULL; p = p->next)
			fprintf(log, "%d\t%s\t%s\t%d\n", p->id, p->title, p->author, p->year);//����
	fclose(admin);
	fclose(log);
	printf("ͼ����Ϣ�ѳɹ����浽 %s �ļ���\n", name);
}
/*�û��͹���Ա�Ķ���ѡ��ʵ��*/void core_choose(int role)
{
again_choose:
	book* link = NULL;//��int����һ��
	int out_id;
	char choose = getchar();
	getchar();
	if (role == 1) {//user
		switch (choose) {
		case '0': system("cls"); start(); break;//����
		case '1': do {
			printf("�����뻹��ͼ��ID��(��0�˳�)");
			scanf("%d", &out_id); getchar();
			if (out_id == 0) break;
			check_outin(out_id);
		} while (1); system("cls"); all_core('1'); break;//����
		case '2': link = creatlink(); book_in(link); system("cls"); printf("�ѳɹ�����\n"); all_core('1'); break;//���飬������ƾ�ս�
		case '3': print_admin(); all_core('1'); break;//�鿴
		case '4': print_user(); all_core('1'); break;//�鿴
		default:printf("��������ȷ����!\n"); goto again_choose;
		}
	}
	else if (role == 3) {//admin
		switch (choose) {
		case '0': system("cls"); start(); break;//����
		case '1': /*  book *  */link = creatlink();
			book_in(link); system("cls"); printf("�ѳɹ��������ͼ��\n"); printlink(link);  all_core('3'); break;//�����
		case '2': do {
			printf("������Ҫɾ����ͼ��ID��(��0�˳�)");
			scanf("%d", &out_id); getchar();
			if (out_id == 0) break;
			book_out(out_id);
		} while (1); system("cls");  all_core('3'); break;//ɾ����
		case '3':  print_admin(); all_core('3'); break;//����
		default:printf("��������ȷ����!\n"); goto again_choose;
		}
	}
}
/*�û��͹���Ա�Ķ���ҳ*/void all_core(char role)
{
	if (role == '1') {//user
		//����choose���ѵ�������ţ�
		printf("------------------------------user\n");
		printf("\t  1. ����\n");
		printf("\t  2. ���� \n");
		printf("\t  3. �鿴������\n");
		printf("\t  4. �鿴������\n");
		printf("\t  0. ������һ��\n");
		printf("----------------------------------\n");
		printf("��������������:");
		core_choose(1);
	}
	else if (role == '3') {//admin
		printf("------------------------------admin\n");
		printf("\t  1. �����\n");
		printf("\t  2. ɾ����\n");
		printf("\t  3. �鿴������\n");
		printf("\t  0. ������һ��\n");
		printf("----------------------------------\n");
		printf("��������������:");
		core_choose(3);
	}
}
/*��¼����*/void login()
{
	char user_name[50], user_password[50];
	printf("<*********�����������˺ź�����********>\n");
	printf("�˺�:\t");
	fgets(user_name, sizeof(user_name), stdin);//��βȥ��\n��0���������뱣��\n��
	user_name[strcspn(user_name, "\n")] = '\0';
	printf("����:\t");
	fgets(user_password, sizeof(user_password), stdin);
	user_password[strcspn(user_password, "\n")] = '\0';
	if (check(user_name, user_password) == 1) {
		system("cls");
		printf("��½�ɹ�\n");
		temp_name(user_name);
		return;
	}
	else {
		system("cls");
		printf("damn��bro�����������˺Ŵ�����\n");
		//while (1);//û����ı�ע���ۣ�����˵�����Ϊ�˵��Բ��˳�;
		start();
	}
}
/*ע�����*/void signup()
{
	char user_name[50], user_password[50];
	printf("<*********�����������˺ź�����********>\n");
	printf("�˺�:\t");
	fgets(user_name, sizeof(user_name), stdin);
	user_name[strcspn(user_name, "\n")] = '\0';
	printf("����:\t");
	fgets(user_password, sizeof(user_password), stdin);
	user_password[strcspn(user_password, "\n")] = '\0';
	if (check(user_name, user_password) == 0) {
		user_in(user_name, user_password);// �����û���������
		system("cls");
		printf("ע��ɹ���\n");
	}
	else {
		system("cls");
		printf("�û����Ѵ���,ע��ʧ��\n");
		start();
	}
}
/*������¼*/void admin()
{
	char user_name[50], user_password[50];
	printf("\t�˺�:");
	fgets(user_name, sizeof(user_name), stdin);
	user_name[strcspn(user_name, "\n")] = '\0';
	printf("\t����:");
	fgets(user_password, sizeof(user_password), stdin);
	user_password[strcspn(user_password, "\n")] = '\0';
	if (strcmp(user_name, "admin") == 0 && strcmp(user_password, "114514") == 0) {//��ͬ����0
		system("cls");
		printf("��½�ɹ�\n");
		temp_name(user_name);
	}
	else {
		system("cls");
		printf("damn,");
		printf("bro!  admin������\"114514\"\n");
		//while (1);//û����ı�ע���ۣ�����˵�����Ϊ�˵��Բ��˳�;
		start();
	}
}
/*��ҳѡ��ʵ��(ѡ����ڶ�Ӧ������)*/void welcome_choose(char choose)
{
	switch (choose) {
	case '1': login(); return; break;
	case '2': signup(); start(); break;
	case '3': admin(); break;
	case '0': exit(0); break;
	default:system("cls"); printf("��������ȷ����!\n");  start(); break;
	}
}
/*��ҳ*/char welcome()//��ӭ����
{
	printf("=====��ӭ��������������ϵͳ=====\n");
	printf("----------------------------------\n");
	printf("\t  1. �û���¼\n");
	printf("\t  2. ע���˺�\n");
	printf("\t  3. ����Ա��¼\n");
	printf("\t  0. �˳�\n");
	printf("----------------------------------\n");
	printf("<*********��������������:********>\n");
	printf("==================================\n");
	char choose = getchar();
	getchar();
	welcome_choose(choose);
	return choose;
}
/*�ο�ʼ�ĵط�*/void start()
{
	char choose = welcome();
	//�ϵ��룬���ں�
	all_core(choose);
	while (1);//û����ı�ע���ۣ�����˵�����Ϊ�˵��Բ��˳�;
	//���������Ϊ�˷�����һҳ������ǰ������Ƕ�ף�����ֵ���ǵ�һ��ѡ�񣬱��������һ������ֵ���ļ��棬�е��鷳����ȫ�ֱ������ҵ�������д�����
	//��δ�������������ɺ������д���ˣ������߼���д���ˣ���ʣ������һ��ûд
}
int main()
{
	start();
	return 0;
}






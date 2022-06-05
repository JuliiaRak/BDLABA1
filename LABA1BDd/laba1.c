#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

# define N 400
# define KEY_LEN 11
# define NAME_LEN 201
# define ADRESS_LEN 201
# define DELETED_LEN 11

int number_T = 0;
int number_V = 0;
int k_T = 1;
int k_I = 1;
int k_P = 1;

typedef struct company_fl
{
    char keyC[KEY_LEN];
    char nameC[NAME_LEN];
    char adressC[ADRESS_LEN];
    int year;
    int flag;
    int link;
    int col_link;
} companyFL;

typedef struct product
{
    char keyG[KEY_LEN];
    char nameG[NAME_LEN];
    int duration;
    char description[NAME_LEN];
    int flag;
    int link;
} product;

typedef struct company_ind
{
    char key[KEY_LEN];
    int adress;
    int flag;
} companyInd;

void insert_C()
{
    printf("Ввести код компанії, назву, адресу и рік заснування:");
    FILE* fl;
    char name[] = "company.txt";
    unsigned int s[DELETED_LEN];
    fl = fopen(name, "rb+");
    companyFL t;
    scanf("%10s%200s%200s%d", &(t.keyC), &(t.nameC), &(t.adressC), &(t.year));

    t.flag = 1;
    t.link = -1;
    t.col_link = 0;

    fseek(fl, 0, SEEK_SET);
    fread(&s, sizeof(int), DELETED_LEN, fl);
    int l = -1;
    if (s[0] != 0 && s[0] < k_T)
    {
        l = s[0];
        int i = 1;
        while (i < DELETED_LEN)
        {
            s[i - 1] = s[i];
            i++;
        }
    }
    else
    {
        l = k_T;
        k_T++;
    }

    fseek(fl, (long)l * sizeof(companyFL) + (long)DELETED_LEN * sizeof(int), SEEK_SET);
    fwrite(&t, sizeof(companyFL), 1, fl);
    FILE* ind;
    char name1[] = "companyInd.txt";
    ind = fopen(name1, "rb+");
    companyInd t_I;
    int h = 0;
    while (h < KEY_LEN)
    {
        t_I.key[h] = t.keyC[h];
        h++;
    }
    t_I.adress = l;
    t_I.flag = 1;
    fseek(ind, (long)k_I * sizeof(companyInd), SEEK_SET);
    k_I++;
    fwrite(&t_I, sizeof(companyInd), 1, ind);
    printf("Success\n");
    fclose(fl);
    fclose(ind);
}

companyFL get_C()
{
    printf("Ввести код компанії:");
    FILE* ind;
    char name[] = "companyInd.txt";
    ind = fopen(name, "rb");
    char key_[KEY_LEN];
    scanf("%10s", key_);
    companyInd t;
    int l;
    while (!feof(ind))
    {
        fread(&t, sizeof(companyInd), 1, ind);
        if (strcmp(t.key, key_) == 0)
        {
            l = t.adress;
            break;
        }
    }
    FILE* fl;
    char name1[] = "company.txt";
    fl = fopen(name1, "rb");
    companyFL t_fl;
    fseek(fl, (long)(l * sizeof(companyFL) + DELETED_LEN * sizeof(int)), SEEK_SET);
    fread(&t_fl, sizeof(companyFL), 1, fl);
    fclose(fl);
    fclose(ind);
    companyFL f;
    f.adressC[0] = '-1';
    f.link = -1;
    f.nameC[0] = '-1';
    f.year = -1;
    if (t_fl.flag == -1) { printf("Видалено\n"); return f; }
    else
        return t_fl;
}

void update_C()
{
    printf("Ввести код компанії:");
    FILE* ind;
    char name[] = "companyInd.txt";
    ind = fopen(name, "rb");
    char key_[KEY_LEN];
    scanf("%10s", key_);
    companyInd t;
    int l;
    while (!feof(ind))
    {
        fread(&t, sizeof(companyInd), 1, ind);
        if (strcmp(t.key, key_) == 0)
        {
            l = t.adress;
            break;
        }
    }
    FILE* fl;
    char name1[] = "company.txt";
    fl = fopen(name1, "rb+");
    companyFL t_fl;
    fseek(fl, (long)(l * sizeof(companyFL) + DELETED_LEN * sizeof(int)), SEEK_SET);
    fread(&t_fl, sizeof(companyFL), 1, fl);
    printf("Вкажіть поле для зміни:\n");
    char p[100];
    scanf("%s", p);
    if (p[0] == 'n')
    {
        char n[NAME_LEN];
        scanf("%s", n);
        strcpy(t_fl.nameC, n);
    }
    if (p[0] == 'a')
    {
        char a[ADRESS_LEN];
        scanf("%s", a);
        strcpy(t_fl.adressC, a);
    }
    if (p[0] == 'y')
    {
        int y;
        scanf("%d", &y);
        t_fl.year = y;
    }
    fseek(fl, (long)(l * sizeof(companyFL) + DELETED_LEN * sizeof(int)), SEEK_SET);
    fwrite(&t_fl, sizeof(companyFL), 1, fl);
    printf("Success\n");
    fclose(fl);
    fclose(ind);
}

void del_C()
{
    printf("Введіть ключ компанії:\n");
    FILE* ind;
    char name[] = "companyInd.txt";
    ind = fopen(name, "rb");
    char key_[KEY_LEN];
    scanf("%10s", key_);
    companyInd t;
    int c = 0;
    int ll;
    while (!feof(ind))
    {
        c++;
        fread(&t, sizeof(companyInd), 1, ind);
        if (strcmp(t.key, key_) == 0)
        {
            ll = t.adress;
            break;
        }
    }
    t.flag = -1;
    fseek(ind, (long)(c * sizeof(companyInd)), SEEK_SET);
    fwrite(&t, sizeof(companyInd), 1, ind);

    FILE* fl;
    char name1[] = "company.txt";
    fl = fopen(name1, "rb+");
    companyFL t_fl;
    fseek(fl, (long)(ll * sizeof(companyFL) + DELETED_LEN * sizeof(int)), SEEK_SET);
    fread(&t_fl, sizeof(companyFL), 1, fl);
    t_fl.flag = -1;
    fseek(fl, (long)(ll * sizeof(companyFL) + DELETED_LEN * sizeof(int)), SEEK_SET);
    fwrite(&t_fl, sizeof(companyFL), 1, fl);
    unsigned int s[DELETED_LEN];
    fseek(fl, 0, SEEK_SET);
    fread(&s, sizeof(int), DELETED_LEN, fl);

    int i = 0;
    while (s[i] > 0 && s[i] <= k_T) i++;
    s[i] = ll;
    fseek(fl, 0, SEEK_SET);
    fwrite(&s, sizeof(int), DELETED_LEN, fl);
    int ln = t_fl.link;
    FILE* gm;
    char name2[] = "games.txt"; //////////////////////
    gm = fopen(name2, "rb+");
    product pr;
    while (ln != -1)
    {
        fseek(gm, (long)(ln * sizeof(product) + DELETED_LEN * sizeof(int)), SEEK_SET);
        fread(&pr, sizeof(product), 1, gm);

        pr.flag = -1;
        fseek(gm, (long)(ln * sizeof(product) + DELETED_LEN * sizeof(int)), SEEK_SET);
        fwrite(&pr, sizeof(product), 1, gm);
        fseek(gm, 0, SEEK_SET);
        fread(&s, sizeof(int), DELETED_LEN, gm);
        i = 0;
        while (s[i] > 0 && s[i] <= k_P) i++;
        s[i] = ln;
        ln = pr.link;
        fseek(gm, 0, SEEK_SET);
        fwrite(&s, sizeof(int), DELETED_LEN, gm);
    }
    printf("Success\n");
    fclose(fl);
    fclose(gm);
    fclose(ind);
}

void insert_G()
{
    printf("Введите ключ компанії:\n");
    FILE* ind;
    char name[] = "companyInd.txt";
    ind = fopen(name, "rb");
    char key_[KEY_LEN];
    scanf("%10s", key_);
    companyInd t;
    int ll;
    while (!feof(ind))
    {
        fread(&t, sizeof(companyInd), 1, ind);
        if (strcmp(t.key, key_) == 0)
        {
            ll = t.adress;
            break;
        }
    }
    FILE* fl;
    char name1[] = "company.txt";
    fl = fopen(name1, "rb+");
    companyFL t_fl;
    fseek(fl, (long)(ll * sizeof(companyFL) + DELETED_LEN * sizeof(int)), SEEK_SET);
    fread(&t_fl, sizeof(companyFL), 1, fl);
    t_fl.col_link++;
    fseek(fl, (long)(ll * sizeof(companyFL) + DELETED_LEN * sizeof(int)), SEEK_SET);
    fwrite(&t_fl, sizeof(companyFL), 1, fl);
    product p;
    printf("Ввести ключ, продукт, опис и ціну:\n");
    scanf("%10s%200s%200s%d", &(p.keyG), &(p.nameG), &(p.description), &(p.duration));
    p.link = -1;
    p.flag = 1;

    FILE* gm;
    char name2[] = "games.txt";  ///////////////////////////
    gm = fopen(name2, "rb+");
    unsigned int s[DELETED_LEN];
    fseek(gm, 0, SEEK_SET);
    fread(&s, sizeof(int), DELETED_LEN, gm);
    int l = -1;
    if (s[0] != 0 && s[0] < k_P)
    {
        l = s[0];
        int i = 1;
        while (i < DELETED_LEN)
        {
            s[i - 1] = s[i];
            i++;
        }
    }
    else
    {
        l = k_P;
        k_P++;
    }
    if (t_fl.link == -1)
    {
        t_fl.link = l;
        fseek(fl, (long)(ll * sizeof(companyFL) + DELETED_LEN * sizeof(int)), SEEK_SET);
        fwrite(&t_fl, sizeof(companyFL), 1, fl);

    }
    else
    {
        int ln = t_fl.link;
        int ln_ = t_fl.link;
        product pr;
        while (ln != -1)
        {
            fseek(gm, (long)(ln * sizeof(product) + DELETED_LEN * sizeof(int)), SEEK_SET);
            fread(&pr, sizeof(product), 1, gm);
            ln_ = ln;
            ln = pr.link;
        }
        pr.link = l;
        fseek(gm, (long)(ln_ * sizeof(product) + DELETED_LEN * sizeof(int)), SEEK_SET);
        fwrite(&pr, sizeof(product), 1, gm);
    }
    fseek(gm, (long)(l * sizeof(product) + DELETED_LEN * sizeof(int)), SEEK_SET);
    fwrite(&p, sizeof(product), 1, gm);
    printf("Success\n");
    fclose(gm);
    fclose(fl);
    fclose(ind);
}

product get_G()
{

    printf("Ввести ключ компанії:\n");
    FILE* ind;
    char name[] = "companyInd.txt";
    ind = fopen(name, "rb");
    char key_[KEY_LEN];
    scanf("%10s", key_);
    companyInd t;
    int ll;
    while (!feof(ind))
    {
        fread(&t, sizeof(companyInd), 1, ind);
        if (strcmp(t.key, key_) == 0)
        {
            ll = t.adress;
            break;
        }
    }
    FILE* fl;
    char name1[] = "company.txt";
    fl = fopen(name1, "rb+");
    companyFL t_fl;
    fseek(fl, (long)(ll * sizeof(companyFL) + DELETED_LEN * sizeof(int)), SEEK_SET);
    fread(&t_fl, sizeof(companyFL), 1, fl);
    printf("Ввести ключ продукту:\n");
    char key_1[KEY_LEN];
    scanf("%10s", key_1);
    FILE* gm;
    char name2[] = "games.txt"; //////////
    gm = fopen(name2, "rb+");
    product p;
    int ln = t_fl.link;
    fseek(gm, (long)(ln * sizeof(product) + DELETED_LEN * sizeof(int)), SEEK_SET);
    fread(&p, sizeof(product), 1, gm);
    ln = p.link;
    while (strcmp(p.keyG, key_1) != 0 && ln != -1)
    {

        fseek(gm, (long)(ln * sizeof(product) + DELETED_LEN * sizeof(int)), SEEK_SET);
        fread(&p, sizeof(product), 1, gm);
        ln = p.link;
        if (strcmp(p.keyG, key_1) == 0) break;
    }
    fclose(fl);
    fclose(ind);
    fclose(gm);
    product nl;
    nl.description[0] = '-1';
    nl.duration = -1;
    nl.link = -1;
    nl.nameG[0] = '-1';
    if (p.flag == -1 || strcmp(p.keyG, key_1) != 0) { printf("Видалено\n"); return nl; }
    else
        return p;
}

void update_G()
{
    printf("Ввести ключ компанії:\n");
    FILE* ind;
    char name[] = "companyInd.txt";
    ind = fopen(name, "rb");
    char key_[KEY_LEN];
    scanf("%10s", key_);
    companyInd t;
    int ll;
    while (!feof(ind))
    {
        fread(&t, sizeof(companyInd), 1, ind);
        if (strcmp(t.key, key_) == 0)
        {
            ll = t.adress;
            break;
        }
    }
    FILE* fl;
    char name1[] = "company.txt";
    fl = fopen(name1, "rb+");
    companyFL t_fl;
    fseek(fl, (long)(ll * sizeof(companyFL) + DELETED_LEN * sizeof(int)), SEEK_SET);
    fread(&t_fl, sizeof(companyFL), 1, fl);
    int pos_p = t_fl.link;
    printf("Ввести ключ продукту:\n");
    char key_1[KEY_LEN];
    scanf("%10s", key_1);
    FILE* gm;
    char name2[] = "games.txt"; /////////////
    gm = fopen(name2, "rb+");
    product p;
    fseek(gm, (long)(t_fl.link * sizeof(product) + DELETED_LEN * sizeof(int)), SEEK_SET);
    fread(&p, sizeof(product), 1, gm);
    while (strcmp(p.keyG, key_1) != 0 && !feof(gm))
    {
        pos_p = p.link;
        fseek(gm, (long)(p.link * sizeof(product) + DELETED_LEN * sizeof(int)), SEEK_SET);
        fread(&p, sizeof(product), 1, gm);
    }
    printf("Вкажіть поле для зміни:\n");
    char pp[100];
    scanf("%s", pp);
    if (pp[0] == 'n')
    {
        char n[NAME_LEN];
        scanf("%s", n);
        strcpy(p.nameG, n);
    }
    if (pp[0] == 'd' && pp[1] == 'i')
    {
        char a[NAME_LEN];
        scanf("%s", a);
        strcpy(p.description, a);
    }
    if (pp[0] == 'd' && pp[1] == 'u')
    {
        int y;
        scanf("%d", &y);
        p.duration = y;
    }
    fseek(gm, (long)(pos_p * sizeof(product) + DELETED_LEN * sizeof(int)), SEEK_SET);
    fwrite(&p, sizeof(product), 1, gm);
    printf("Успішно\n");
    fclose(gm);
    fclose(fl);
    fclose(ind);
}

void del_G()
{
    printf("Ввести ключ компанії:\n");
    FILE* ind;
    char name[] = "companyInd.txt";
    ind = fopen(name, "rb");
    char key_[KEY_LEN];
    scanf("%10s", key_);
    companyInd t;
    int ll;
    while (!feof(ind))
    {
        fread(&t, sizeof(companyInd), 1, ind);
        if (strcmp(t.key, key_) == 0)
        {
            ll = t.adress;
            break;
        }
    }
    FILE* fl;
    char name1[] = "company.txt";
    fl = fopen(name1, "rb+");
    companyFL t_fl;
    fseek(fl, (long)(ll * sizeof(companyFL) + DELETED_LEN * sizeof(int)), SEEK_SET);
    fread(&t_fl, sizeof(companyFL), 1, fl);
    int pos_p = t_fl.link;

    printf("Ввести ключ продукту:\n");
    char key_1[KEY_LEN];
    scanf("%10s", key_1);
    FILE* gm;
    char name2[] = "games.txt";
    gm = fopen(name2, "rb+");
    product p;
    product p_prev;
    fseek(gm, (long)(t_fl.link * sizeof(product) + DELETED_LEN * sizeof(int)), SEEK_SET);
    fread(&p, sizeof(product), 1, gm);

    if (t_fl.col_link == 1)
    {

        t_fl.col_link--;
        t_fl.link = -1;

        fseek(fl, (long)(ll * sizeof(companyFL) + DELETED_LEN * sizeof(int)), SEEK_SET);
        fwrite(&t_fl, sizeof(companyFL), 1, fl);

        p.flag = -1;
        fseek(gm, (long)(pos_p * sizeof(product) + DELETED_LEN * sizeof(int)), SEEK_SET);
        fwrite(&p, sizeof(product), 1, gm);
        unsigned int s[DELETED_LEN];
        fseek(gm, 0, SEEK_SET);
        fread(&s, sizeof(int), DELETED_LEN, gm);
        int i = 0;
        while (s[i] > 0 && s[i] <= k_P) i++;
        s[i] = pos_p;
        fseek(gm, 0, SEEK_SET);
        fwrite(&s, sizeof(int), DELETED_LEN, gm);
    }
    else
        if (t_fl.col_link == 2 && strcmp(p.keyG, key_1) == 0)
        {
            t_fl.link = p.link;
            t_fl.col_link--;
            fseek(fl, (long)(ll * sizeof(companyFL) + DELETED_LEN * sizeof(int)), SEEK_SET);
            fwrite(&t_fl, sizeof(companyFL), 1, fl);
            p.flag = -1;
            fseek(gm, (long)(pos_p * sizeof(product) + DELETED_LEN * sizeof(int)), SEEK_SET);
            fwrite(&p, sizeof(product), 1, gm);
            unsigned int s[DELETED_LEN];
            fseek(gm, 0, SEEK_SET);
            fread(&s, sizeof(int), DELETED_LEN, gm);
            int i = 0;
            while (s[i] > 0 && s[i] <= k_P) i++;
            s[i] = pos_p;
            fseek(gm, 0, SEEK_SET);
            fwrite(&s, sizeof(int), DELETED_LEN, gm);
        }
        else
        {
            p_prev = p;
            int pos_p_prev = pos_p;
            fseek(gm, (long)(p.link * sizeof(product) + DELETED_LEN * sizeof(int)), SEEK_SET);
            fread(&p, sizeof(product), 1, gm);
            pos_p = p_prev.link;
            while (strcmp(p.keyG, key_1) != 0 && !feof(gm))
            {
                p_prev = p;
                pos_p_prev = pos_p;
                fseek(gm, (long)(p.link * sizeof(product) + DELETED_LEN * sizeof(int)), SEEK_SET);
                fread(&p, sizeof(product), 1, gm);
                pos_p = p_prev.link;
            }
            p_prev.link = p.link;
            p.flag = -1;
            fseek(gm, (long)(pos_p_prev * sizeof(product) + DELETED_LEN * sizeof(int)), SEEK_SET);
            fwrite(&p_prev, sizeof(product), 1, gm);
            fseek(gm, (long)(pos_p * sizeof(product) + DELETED_LEN * sizeof(int)), SEEK_SET);
            fwrite(&p, sizeof(product), 1, gm);
            unsigned int s[DELETED_LEN];
            fseek(gm, 0, SEEK_SET);
            fread(&s, sizeof(int), DELETED_LEN, gm);
            int i = 0;
            while (s[i] > 0 && s[i] <= k_P) i++;
            s[i] = pos_p;
            fseek(gm, 0, SEEK_SET);
            fwrite(&s, sizeof(int), DELETED_LEN, gm);
        }
    printf("Success\n");
    fclose(fl);
    fclose(ind);
    fclose(gm);
}

void show_I()
{
    FILE* ind;
    char name[] = "companyInd.txt";
    ind = fopen(name, "rb");
    companyInd t;
    fread(&t, sizeof(companyInd), 1, ind);
    while (!feof(ind))
    {
        fread(&t, sizeof(companyInd), 1, ind);
        if (t.flag != -1)
            printf("Ключ: %s\n Адреса: %d\n", t.key, t.adress);
    }
    fclose(ind);
}

void show_C()
{
    FILE* fl;
    char name[] = "company.txt";
    fl = fopen(name, "rb");
    companyFL t;
    fseek(fl, (long)(sizeof(companyFL) + DELETED_LEN * sizeof(int)), SEEK_SET);
    int k = 1;
    while (!feof(fl) && k < k_T)
    {
        k++;
        fread(&t, sizeof(companyFL), 1, fl);
        if (t.flag != -1)
            printf("Ключ: %s\n Назва: %s\n Адреса: %s\n Рік: %d\n", t.keyC, t.nameC, t.adressC, t.year);
    }
    fclose(fl);
}

void show_G()
{
    printf("Ввести ключ компанії:\n");
    FILE* ind;
    char name[] = "companyInd.txt";
    ind = fopen(name, "rb");
    char key_[KEY_LEN];
    scanf("%10s", key_);
    companyInd t;
    int ll;
    while (!feof(ind))
    {
        fread(&t, sizeof(companyInd), 1, ind);
        if (strcmp(t.key, key_) == 0)
        {
            ll = t.adress;
            break;
        }
    }
    FILE* fl;
    char name1[] = "company.txt";
    fl = fopen(name1, "rb+");
    companyFL t_fl;
    fseek(fl, (long)(ll * sizeof(companyFL) + DELETED_LEN * sizeof(int)), SEEK_SET);
    fread(&t_fl, sizeof(companyFL), 1, fl);
    int ln = t_fl.link;
    int k = 1;
    FILE* gm;
    char name2[] = "games.txt";
    gm = fopen(name2, "rb+");
    product p;
    while (ln != -1)
    {
        fseek(gm, (long)(ln * sizeof(product) + DELETED_LEN * sizeof(int)), SEEK_SET);
        fread(&p, sizeof(product), 1, gm);
        ln = p.link;
        printf("Ключ: %s\n Продукт: %s\n Ціна: %d\n Опис: %s\n", (p.keyG), (p.nameG), (p.duration), (p.description), (p.link));
        k++;
    }
    fclose(ind);
    fclose(fl);
    fclose(gm);
}



int main()
{

    setlocale(LC_ALL, "Russian");
    while (1)
    {
        char s[101];
        scanf("%100s", &s);

        if (s[0] == 'i' && s[7] == 'C')
        {
            insert_C();
        }
        if (s[0] == 'i' && s[7] == 'G')
        {
            insert_G();
        }
        if (s[0] == 'g' && s[4] == 'C')
        {
            companyFL t;
            t = get_C();
            if (t.year != -1)
                printf("Ключ: %s\n Назва: %s\n Адреса: %s\n Рік заснування: %d\n", (t.keyC), (t.nameC), (t.adressC), (t.year));
        }
        if (s[0] == 'g' && s[4] == 'G')
        {
            product t;
            t = get_G();
            if (t.duration != -1)
                printf("Ключ: %s\n Продукт: %s\n Ціна: %d\n Опис %s\n", (t.keyG), (t.nameG), (t.duration), (t.description));
        }
        if (s[0] == 'u' && s[7] == 'C')
        {
            update_C();
        }
        if (s[0] == 'u' && s[7] == 'G')
        {
            update_G();
        }
        if (s[0] == 'd' && s[4] == 'G')
        {
            del_G();
        }
        if (s[0] == 'd' && s[4] == 'C')
        {
            del_C();
        }
        if (s[0] == 's' && s[5] == 'I')
        {
            show_I();
        }
        if (s[0] == 's' && s[5] == 'C')
        {
            show_C();
        }
        if (s[0] == 's' && s[5] == 'G')
        {
            show_G();
        }
    }

    return 0;
}
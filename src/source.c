
#include<string.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
const int SIZE = 41;
char* nums = "0123456789ABCDEF";

int val(char a){
    switch (a)
    {
    case 'A':
        return 10;
        break;
    case 'B':
        return 11;
        break;
    case 'C':
        return 12;
        break;
    case 'D':
        return 13;
        break;
    case 'E':
        return 14;
        break;
    case 'F':
        return 15;
        break;
    default:
        return a-48;
        break;
    }
}
void turn(char* str){
    char temp[SIZE];
    int i = strlen(str)-1;
    int i2 = 0;
    while(i >= 0){
        temp[i2] = str[i];
        i-=1;
        i2++;
    }
    temp[i2] = '\0';
    strcpy(str, temp);
}
void swap(char** a, char** b)
{
    char *temp = *a;
    *a = *b;
    *b = temp;

}
//dodawanie pisemne
void add(char *a, char *b, int base, char *sum){
    if(strlen(a) < strlen(b))
    {
        swap(&a, &b);
    }
    int a_iter = strlen(a)-1;
    int b_iter = strlen(b)-1;
    int i = 0;
    int num = 0;
    int car = 0;
    while(a_iter>=0 && b_iter>=0){
        num = (val(a[a_iter]) + val(b[b_iter]) + car) % base;
        car = (val(a[a_iter]) + val(b[b_iter]) + car) / base;
        
        sum[i] = nums[num];
        i++;
        a_iter -=1 ;
        b_iter -= 1;
        
    }
    if(a_iter >= 0)
    {
        while(a_iter >= 0){
            num = (val(a[a_iter]) + car) % base;
            car = (val(a[a_iter]) + car) / base;
            a_iter-=1;
            sum[i] = nums[num];
            i++;
        }
    }
    if (car > 0){ sum[i] = nums[car]; i++;}
    sum[i] = '\0';
    turn(sum);
    return;
}
int change_to_int(char *a, int base){
    int iter = strlen(a) - 1;
    int out = 0;
    int i = 0;
    while(iter >= 0){
        out += val(a[iter]) * pow(base, i);
        if(out > 1000000) return -1;
        iter-=1;
        i++;
    }
    return out;
}
int are_equal(char* a, char*b){
    if(strlen(a) != strlen(b)) return 0;
    for(int i = 0; i < strlen(a); ++i){
        if(a[i] != b[i]) return 0;
    }
    return 1;
}
void decichange (int a, int to_base, char* out){

    int i = 0;
    int num = 0;        
    while(a > 0){
        num = a%to_base;
        a = (a - num) / to_base;
        out[i] = nums[num];
        i++;
    }
    out[i] = '\0';
    turn(out);
    return;
}
//zamiana podstawy systemu
void change(char *a, int from_base, int to_base, char *out){ 
    int a_iter = strlen(a) - 1;
    int num = 0;
    int i = 0;
    char comp[SIZE];
    char temp_out[SIZE];
    char tab[SIZE];
    comp[0] = '\0';
    temp_out[0] = '\0';
    while ( a_iter >= 0 ){
        num = (val(a[a_iter]) *(int)pow(from_base, i));
        
        decichange(num, to_base, comp);       
        
        add(temp_out, comp, to_base, tab);
        printf("%s", tab);
        strcpy(temp_out, tab);

        a_iter-=1;
        i++;
    }
    
    strcpy(out, temp_out);
    return;
}   
//mnozenie pisemne
void multiply(char* a, char* b, int base, char *out){
    if(strlen(a) < strlen(b))
    {
        swap(&a, &b);
    }
    int a_iter = strlen(a)-1;
    int b_iter = strlen(b)-1;
    int i = 0;
    int num = 0;
    int car = 0;
    char temp_out[SIZE];
    temp_out[0] = '0';
    temp_out[1] = '\0';        
    int k = 0;

    while(b_iter >= 0)
    {
        if(b[b_iter] != '0'){
            i = 0;
            char comp[SIZE];
            for(int j = 0; j < k; j++){
                comp[i] = '0';
                i++;
            }
            while(a_iter >= 0)
            {
                num = ((val(a[a_iter]) * val(b[b_iter])) +car) % base;
                car = ((val(a[a_iter]) * val(b[b_iter])) +car) / base;
                a_iter-=1;
                comp[i] = nums[num];
                i++;
            } 
            if(car > 0){ comp[i] = nums[car]; i++; }
            comp[i] = '\0';
            char tab[SIZE];
            turn(comp);
            add(temp_out, comp, base, tab);
            strcpy(temp_out, tab);
        }
        a_iter = strlen(a) - 1;
        b_iter -= 1;
        k++;

    }
    strcpy(out, temp_out);

    return;
}
//potegowanie - wielokrotne mnozenie(podstawowe)
void power(char* a, char* pow, int base, char *out){
    if(pow[0] == '0'){
        out[0] = 0;
        return;
    }
    char temp[SIZE];
    strcpy(temp, a);
    int b = change_to_int(pow, base);

    if(b == -1){
        printf("ERROR! the power of %s is too big!", pow);
        abort;
    }
    for(int i = 1; i < b; ++i)
    {
        multiply(a, temp, base, out);
        if(strlen(out) > SIZE ) {
            printf("ZA DUZA POTEGA ");
            out[0] = '\0';
            return;}
        strcpy(temp, a);
        strcpy(a, out);
    }
    return;
}
void divide(char* a, char* b, int base, char *out){
    char temp[SIZE];
    char comp[SIZE];
    out[0] = '\0';
    comp[0] = '\0';
    int i = 0;
    while(are_equal(temp, a) == 0 && strlen(comp) <= strlen(a)){
        add(comp, b, base, temp);
        strcpy(comp, temp);
        i++;
    }
    if(strlen(comp) > strlen(a)) return;
    decichange(i, base, out);
    return;
}


//do zrobienia: modulo

int main() {
    FILE *inf;
    FILE *outf;
    //FILE *out;
    char *in_path = "in.txt";
    char *out_path = "out.txt";
    inf = fopen(in_path, "r");
    outf = fopen(out_path, "w");
    char base_str[SIZE];
    int base = 10;
    char str[SIZE];
    char str2[SIZE];
    char out[SIZE];
    while(fscanf(inf, "%s", str) != EOF){
        fputs(str, outf);
        fputs(" ", outf);
        if(str[0] >= 48 && str[0] < 59){
            

            base = atoi(str);

            fscanf(inf, "%s", str2);

            fputs(str2, outf);
            fputs("\n\n", outf);

            int base2 = atoi(str2);
            int k = 1;
            fscanf(inf, "%s", str);
            fputs(str, outf);
            fputs("\n\n", outf);
            change(str, base, base2, out);
            fputs(out, outf);
            fputs("\n\n", outf);
            continue;
        }
        if(str[0] == '+'){
            
            fscanf(inf, "%s", base_str);

            fputs(base_str, outf);
            fputs("\n\n", outf);

            base = atoi(base_str);
            
            fscanf(inf, "%s", str);
            
            fputs(str, outf);
            fputs("\n\n", outf);

            fscanf(inf, "%s", str2);
            
            fputs(str2, outf);
            fputs("\n\n", outf);

            add(str, str2, base, out);
            
            fputs(out, outf);
            fputs("\n\n", outf);
            continue;
        }
        if(str[0] == '*'){
            
            fscanf(inf, "%s", base_str);

            fputs(base_str, outf);
            fputs("\n\n", outf);

            base = atoi(base_str);

        
            fscanf(inf, "%s", str);
            fputs(str, outf);
            fputs("\n\n", outf);
            fscanf(inf, "%s", str2);
            fputs(str2, outf);
            fputs("\n\n", outf);
            multiply(str, str2, base, out);
            fputs(out, outf);
            fputs("\n\n", outf);
            continue;
            
        }
        if(str[0] == '^'){
            fscanf(inf, "%s", base_str);

            fputs(base_str, outf);
            fputs("\n\n", outf);

            base = atoi(base_str);
            
            fscanf(inf, "%s", str);
            fputs(str, outf);
            fputs("\n\n", outf);
            fscanf(inf, "%s", str2);
            
            fputs(str2, outf);
            fputs("\n\n", outf);
            power(str, str2, base, out);

            fputs(out, outf);
            fputs("\n\n", outf);
            continue;
        }
            
        
        if(str[0] == '/'){
            fscanf(inf, "%s", base_str);

            fputs(base_str, outf);
            fputs("\n\n", outf);

            base = atoi(base_str);
            
            fscanf(inf, "%s", str);
            
            fputs(str, outf);
            fputs("\n\n", outf);

            fscanf(inf, "%s", str2);
            
            fputs(str2, outf);
            fputs("\n\n", outf);

            divide(str, str2, base, out);
            
            if(out[0] == '\0'){
                fputs("undividable", outf);
                fputs("\n\n", outf);
            }
            else {
                fputs(out, outf);
                fputs("\n\n", outf);
            }
            continue;
        }
        
            
    
    }

CLOSE:
    fclose(inf);
    fclose(outf);





    /*int baset = 16;
    char at[SIZE];
    at[0] = 'F';
    char* bt = "9";
    char outt[SIZE];
    //add(a, b, base, out);
    //printf("%s", out);
    //multiply(a, b, base, out);
    power(at, bt, baset , outt);

    printf("%s", outt);
*/

    return 0;
}


#include<string.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
const int SIZE = 82;
//do zrobienia: czas obliczen

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
int is_greater(char *greater, char *less){
    if(strlen(greater) > strlen(less)) return 1;
    if(strlen(greater) < strlen(less)) return 0;
    int i = 0;
    while(i < strlen(greater)){
        if(val(greater[i]) > val(less[i])) return 1;
        if(val(less[i]) > val(greater[i])) return 0;
        i++;
    }
    return 0;
}
//dodawanie pisemne
void add(char *a_in, char *b_in, int base, char *sum){
    int swapped = 0;
    if(strlen(a_in) < strlen(b_in))
    {
        swap(&a_in, &b_in);
        swapped = 1;
    }
    char a[SIZE];
    char b[SIZE];
    strcpy(a, a_in);
    strcpy(b, b_in);
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
    if(swapped){
        swap(&a_in, &b_in);
    } 
    return;
}
int change_to_int(char *a, int base){
    int iter = strlen(a) - 1;
    int out = 0;
    int i = 0;
    while(iter >= 0){
        out += val(a[iter]) * pow(base, i);
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
void change_f_int (int a, int to_base, char* out){

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
        
        change_f_int(num, to_base, comp);       
        
        add(temp_out, comp, to_base, tab);
        strcpy(temp_out, tab);

        a_iter-=1;
        i++;
    }
    
    strcpy(out, temp_out);
    return;
}   
//mnozenie pisemne
void multiply(char* a_in, char* b_in, int base, char *out){
    int swapped = 0;
    if(strlen(a_in) < strlen(b_in))
    {
        swap(&a_in, &b_in);
        swapped = 1;
    }
    char a[SIZE];
    char b[SIZE];
    strcpy(a, a_in);
    strcpy(b, b_in);
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
            car = 0;

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
    if(swapped){
        swap(&a_in, &b_in);
    }
    return;
}
//potegowanie - wielokrotne mnozenie, usprawnione, zwraca -1 gdy liczba jest za duża
int power(char* a, char* pow, int base, char *out){
    if(pow[0] == '0'){
        out[0] = 0;
        return 0;
    }
    char temp1[SIZE];
    char temp2[SIZE];
    char prev[SIZE];
    prev[0] = 0;
    prev[1] = '\0';
    strcpy(temp1, a);
    strcpy(temp2, a);
    int b = change_to_int(pow, base);
    if(b * strlen(a) > SIZE-1) return -1;
    int i = 2;
    while( i <= b )
    {
        if(strlen(out) > SIZE || (are_equal(temp1, temp2) && strlen(temp1) >= 42) ) {
            out[0] = '\0';
            return -1;}
        multiply(temp1, temp2, base, out);
        if(i*2 <= b){
            strcpy(temp2, out);
            strcpy(temp1, out);
            i = i * 2;
        }
        else{
            strcpy(temp2, a);
            strcpy(temp1, out);
            i++;
        }
        
    }
    return 0;
}

void divide(char* a, char* b, int base, char *out){
    if(is_greater(b, a)){
        out[0] = 0;
        out[1] = '\0';
        return;
    }
    char temp[SIZE];
    temp[0] = '\0';
    char comp1[SIZE];
    char comp2[SIZE];
    strcpy(comp2, b);
    strcpy(comp1, b);
    char ref[SIZE];
    out[0] = '\0';
    int do_binary = 1;
    int i = 1;
    while(is_greater(a, temp) && !are_equal(a, temp)){
        if(do_binary){add(comp1, comp2, base, ref);}
        if(is_greater(a, ref) && do_binary)
        {
            strcpy(comp1, ref);
            strcpy(comp2, ref);
            strcpy(temp, ref);
            i = i * 2;
        }
        else{
            do_binary = 0;
            add(comp1, b, base, temp);
            strcpy(comp1, temp);
            i++;
        }
    }
    if(is_greater(temp, a)) i = i-1;
    change_f_int(i, base, out);
    return;
}
//modulo za pomocą wyszukiwania binarnego
void modulo(char *a, char *b, int base, char *mid){
    char prev[SIZE];
    char n[SIZE];
    char temp[SIZE];

    divide(a, b, base, n);
    multiply(b, n, base, prev);
    if(are_equal(prev, a)){
        mid[0] = '0';
        mid[1] = '\0';
        return;
    }
    char head[SIZE];
    strcpy(head, b);
    char tail[SIZE];
    tail[0] = '0';
    tail[1] = '\0';
    char sum[SIZE];
    sum[0] = '\0';
    temp[0] = '\0';
    mid[0] = '\0';
    int j = 0;
    while(!are_equal(head, tail)){

        sum[0]='\0';
        add(tail, head, base, sum);        


        divide(sum, "2", base, mid);

        temp[0] ='\0';
        add(prev, mid, base, temp);
        if(is_greater(temp, a)){
            strcpy(head, mid);
        }
        else if(are_equal(temp, a)){
            return;
        }
        else if(!is_greater(temp, a)){
            strcpy(tail, mid);
        }
    }


    return;
}

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
            if(power(str, str2, base, out) == 0){
            fputs(out, outf);
            fputs("\n\n", outf);
            }
            else {
                fputs("ERROR! Number is too big! \n\n", outf);
            
            }
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
        if(str[0] == '%'){
            
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

            modulo(str, str2, base, out);

            fputs(out, outf);
            fputs("\n\n", outf);
            continue;
        }

            
    
    }

CLOSE:
    fclose(inf);
    fclose(outf);
    return 0;
}

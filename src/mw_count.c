
#include<string.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
const int SIZE = 82;

char* nums = "0123456789ABCDEF";

void format(char *in){
    int n = strlen(in);
    int i = 0;
    char out[SIZE];
    while(in[i] == '0'){
        i++;
    }
    if(in[i] == '\0'){
        out[0] = '0';
        out[1] = '\0';
    }
    else {
        int j = 0;
        while(in[i+1] != '\0')
        {
            out[j] = in[i];
            i++;
            j++;
        }
    }
    strcpy(in, out);
    return;
}
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
void add(char *a, char *b, int base, char *sum){
    int swapped = 0;
    if(strlen(a) < strlen(b))
    {
        swap(&a, &b);
        swapped = 1;
    }
    int a_iter = strlen(a)-1;
    int b_iter = strlen(b)-1;
    int i = 0;
    int num = 0; 
    int car = 0; //carried value
    while(a_iter>=0 && b_iter>=0){
        num = (val(a[a_iter]) + val(b[b_iter]) + car) % base;
        car = (val(a[a_iter]) + val(b[b_iter]) + car) / base;
        
        sum[i] = nums[num];
        i++;
        a_iter -= 1 ;
        b_iter -= 1;
        
    }
    if(a_iter >= 0)
    {
        while(a_iter >= 0){
            num = (val(a[a_iter]) + car) % base;
            car = (val(a[a_iter]) + car) / base;
            a_iter -= 1;
            sum[i] = nums[num];
            i++;
        }
    }
    if (car > 0){ sum[i] = nums[car]; i++;}
    sum[i] = '\0';
    turn(sum);
    if(swapped){
        swap(&a, &b);
    } 
    return;
}

int change_to_int(char *a, int base){
    int iter = strlen(a) - 1;
    int out = 0;
    int i = 0;
    while(iter >= 0){
        out += val(a[iter]) * pow(base, i);
        iter -= 1;
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
void change_from_int (int a, int to_base, char* out){
    if(a == 0){
        out[0] = '0';
        out[1] = '\0';
        return;
    }
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
    char single_value[SIZE];
    char sum[SIZE];
    char temp[SIZE];
    single_value[0] = '\0';
    sum[0] = '\0';
    while ( a_iter >= 0 ){
        num = (val(a[a_iter]) *(int)pow(from_base, i));
        
        change_from_int(num, to_base, single_value);       
        
        add(sum, single_value, to_base, temp);
        strcpy(sum, temp);

        a_iter -= 1;
        i++;
    }
    
    strcpy(out, sum);
    return;
}   
//mnozenie pisemne
void multiply(char* a, char* b, int base, char *out){
    int swapped = 0;
    if(strlen(a) < strlen(b))
    {
        swap(&a, &b);
        swapped = 1;
    }
    int a_iter = strlen(a)-1;
    int b_iter = strlen(b)-1;
    int i = 0;
    int num = 0;
    int car = 0;
    char temp_out[SIZE];
    temp_out[0] = '0';
    temp_out[1] = '\0';        
    int comp_zeros = 0;

    while(b_iter >= 0)
    {
        if(b[b_iter] != '0'){
            
            i = 0;
            car = 0;
            char comp[SIZE];
            for(int j = 0; j < comp_zeros; j++){
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
            char temp[SIZE];
            turn(comp);
            add(temp_out, comp, base, temp);
            strcpy(temp_out, temp);
        }
        a_iter = strlen(a) - 1;
        b_iter -= 1;
        comp_zeros++;

    }
    strcpy(out, temp_out);
    if(swapped){
        swap(&a, &b);
    }
    return;
}
//potegowanie - wielokrotne mnozenie, usprawnione, zwraca -1 gdy liczba jest za duża
int power(char* a, char* pow, int base, char *out){
    if(pow[0] == '0'&&pow[1] == '\0'){
        out[0] = '1';
        out[1] = '\0';
        return 0;
    }

     if(pow[0] == '1'&&pow[1] == '\0'){
        strcpy(out, a);
        return 0;
    }
    if(a[0] == '1' && a[1] == '\0'){
        out[0] = '1';
        out[1] = '\0';
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
void sub_one(char *a, int base){
    int a_iter = strlen(a);
    int i = 0;
    while(a_iter >= 0 && a[a_iter] == '0'){
        a_iter-=1;
    }
    int value = val(a[a_iter]) - 1;
    a[a_iter] = nums[value];
    a_iter++;
    while(a_iter < strlen(a))
    {
        a[a_iter] = nums[base-1];
    }
    format(a);

}
//dzielenie szybkie
void divide(char* a, char* b, int base, char *out){
    if(is_greater(b, a)){
        out[0] = '0';
        out[1] = '\0';
        return;
    }
    if(b[0] == '1' && b[1] == '\0'){
        strcpy(out, a);
        return;
    }
    char temp[SIZE];
    temp[0] = '\0';
    char comp1[SIZE];
    char comp2[SIZE];
    strcpy(comp1, b);
    char ref[SIZE];
    out[0] = '\0';
    int do_exponentially = 1;
    int exp_dec = 1;
    char count[SIZE];
    count[0] = '1';
    count[1] = '\0';
    char temp2[SIZE];
    temp2[0] = '\0';
    int count_dec = 0;
    char exp[SIZE];
    while(is_greater(a, temp) && exp_dec > 0){
        if(do_exponentially) { multiply(comp1, b, base, ref); exp_dec++; }
        if(!is_greater(ref, a) && do_exponentially)
        {
            strcpy(comp1, ref);
            strcpy(temp, ref);
            multiply(count, b, base, temp2);
            strcpy(count, temp2);
            count_dec = change_to_int(count, base) - 1;

        }
        else
        {
            change_from_int(exp_dec, base, temp2);
            power(b, temp2, base, comp2);
            add(comp1, comp2, base, ref ); 
            do_exponentially = 0;

            if(!is_greater(ref, a)){
                
                change_from_int(exp_dec-1, base, exp);
                power(b, exp , base, comp2);
                strcpy(comp1, ref );
                strcpy(temp, ref);
                add(count, comp2, base, temp2);
                strcpy(count, temp2);
            }
            else{
                count_dec-=1;
                exp_dec-=1;
                if(exp_dec == 0) break;
            }
        }

    }
    strcpy(out, count);
    count[0] = '\0';
    if(is_greater(temp, a)) sub_one(out, base);
    return;
}
//modulo za pomocą wyszukiwania binarnego
void modulo(char *a, char *b, int base, char *mid){
    char prev[SIZE];
    char n[SIZE];

    divide(a, b, base, n);
    multiply(b, n, base, prev);
    if(are_equal(prev, a)){
        mid[0] = '0';
        mid[1] = '\0';
        return;
    }
    char temp[SIZE];
    char head[SIZE];
    strcpy(head, b);
    char tail[SIZE];
    tail[0] = '0';
    tail[1] = '\0';
    char sum[SIZE];
    sum[0] = '\0';
    temp[0] = '\0';
    mid[0] = '\0';
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

int main(int atgc, char *argv[]) {
    FILE *inf;
    FILE *outf;
    //FILE *out;
    char *in_path = argv[1];
    char outpth0[SIZE];
    strcpy(outpth0, argv[1]);
    for(int i = 0; i< strlen(outpth0)-1; i++)
    {

        if(outpth0[i]=='i' && outpth0[i+1] == 'n'){
            outpth0[i] = '\0';
            break;
            } 
        if(outpth0[i]=='.'){
            outpth0[i] = '_';
            outpth0[i+1]='\0';
            break;
        
        }
            
    }
    char out_path[SIZE];
    sprintf(out_path, "%sout.txt", outpth0);
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

            format(str);

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

            format(str);
            format(str2);

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

            format(str);
            format(str2);

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
            
            format(str);
            
            format(str2);
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

            format(str);
            format(str2);

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

            format(str);
            format(str2);
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

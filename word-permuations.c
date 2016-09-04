/*
 *    Word Permutations
 *    
 *    Author: Afaan Bilal
 *    URL: https://afaan.ml
 *    
 *    Display all possible permutaions for a set of characters.
 *    
 *    (c) 2016 Afaan Bilal
 *    Released under the MIT License
 *     
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void base_convert(char * num, short fromBase, short toBase)
{
    long result = 0;
    long number = 0;
    int i = 0;
    int nLen = strlen(num);
    int resDigitCount = 0;
    long temp;
    
    for (i = 0; i < nLen; i++)
    {
        number = number * 10 + (int)(num[i] - '0');
    }
    
    i = 0;
    while (number > 0)
    {
        result += (number % toBase) * pow(fromBase, i++);
        number /= toBase;
    }
    
    // INCREMENT ONE (FOR PERMUTAIONS ONLY)
    if (toBase == 10) result++;
    // PERMUTAIONS ONLY END
    
    temp = result;
    while (temp > 0)
    {
        resDigitCount++;
        temp /= 10;
    }
    for (i = 0; i < nLen - resDigitCount; i++)
        num[i] = '0';
    for (i = nLen - 1; i >= nLen - resDigitCount; i--)
    {
        num[i] = (char)((result % 10) + '0');
        result /= 10;
    }
}

int binSearch(char * arr, char s, long ubound)
{
    long bottom = 0, top = ubound;
    long mid;
    do
    {
        mid = (top + bottom) / 2;
        if (arr[mid] < s)
            bottom = mid + 1;
        else if (arr[mid] > s)
            top = mid - 1;
    } while (bottom <= top && arr[mid] != s);
    return (arr[mid] == s);
}

int binSearch2(char ** arr, char * s, long ubound)
{
    long bottom = 0, top = ubound;
    long mid;
    int res = 0;
    do
    {
        mid = (top + bottom) / 2;
        res = strcmp(arr[mid], s);
        if (res < 0)
            bottom = mid + 1;
        else if (res > 0)
            top = mid - 1;
    } while (bottom <= top && res != 0);
    return (res == 0);
}

void sort(char * arr)
{
    int len = strlen(arr);
    int i, j, min = 0;
    char tmp;
    for (i = 0; i < len; i++)
    {
        min = i;
        for (j = i + 1; j < len; j++)
        {
            if (arr[min] > arr[j])
                min = j;
        }
        tmp = arr[i];
        arr[i] = arr[min];
        arr[min] = tmp;
    }
}

int main()
{
    char chars[10];
    char * keys;
    char * u_chars;
    char * cur_word;
    char ** words;
    short lcount = 0, ucount = 0; 
    long wcount = 0, real_wcount = 0;
    long i = 0, j = 0, k = 0;
    long len = 0;
    
    printf("WORD PERMUTATIONS\n\n");
    printf("Enter characters (MAX: 7): ");
    scanf("%s", chars);
    printf("\nEntered chars: %s", chars);
    sort(chars);
    printf("\nSorted chars: %s", chars);
    lcount = strlen(chars);
    u_chars = (char*)malloc(lcount * sizeof(char));
    while (i < lcount)
    {
        if (binSearch(u_chars, chars[i], ucount) == 0)
            u_chars[ucount++] = chars[i];
        i++;
    }
    
    wcount = pow(lcount, lcount);
    real_wcount = pow(ucount, lcount);
    printf("\nTotal  Characters  : %d", lcount);
    printf("\nTotal  Permutations: %ld", wcount);
    printf("\nUnique Permutations: %ld", real_wcount);
    
    printf("\n\nAllocating memory...");
    // Allocating memory
    
    keys = (char*)malloc((lcount + 1) * sizeof(char));
    
    words = (char**)malloc(real_wcount * sizeof(char*));
    for (i = 0; i < real_wcount; i++)
        words[i] = (char*)malloc((lcount + 1) * sizeof(char));
    
    cur_word = (char*)malloc((lcount + 1) * sizeof(char));
    
    //memcheck
    if (keys == NULL || words == NULL || cur_word == NULL)
    {
        printf("Memory allocation failed!");
        getch();
        return -1;
    }
    
    printf("Done.");
    
    // zero keys
    for (i = 0; i < lcount; i++)
        keys[i] = '0';
    keys[i] = '\0';
    
    printf("\nPERMUTING...");
    
    for (i = 0; i < wcount; i++)
    {
        for (j = 0; j < lcount; j++)
        {
            int key = keys[j] - '0';
            cur_word[j] = chars[key];
        }
        cur_word[j] = '\0';
        
        base_convert(keys, lcount, 10); // ALSO INCREMENTS ONE INTERNALLY
        base_convert(keys, 10, lcount);
        
        if (binSearch2(words, cur_word, len) == 0)
        {
            for (k = 0; k <= lcount; k++)
                words[len][k] = cur_word[k];
            len++;
        }
    }
    
    printf("\nWORDS: \n");
    for (i = 0; i < real_wcount; i++)
    {
        printf("%s\t", words[i]);
        if ((i+1) % 14 == 0) printf("\n");
    }
    
    getch();
    // release memory
    free(u_chars);
    free(keys);
    free(cur_word);
    free(words);
    return 0;
}

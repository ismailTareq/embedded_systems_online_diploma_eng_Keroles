#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5
char *get_word(char* text, int start, int end)
{
    char *word;
    int i,index=0;
    word = (char *)calloc(end-start,sizeof(char));
    for(i=start;i<=end;i++)
    {
        word[index++]=text[i];
    }
    word[index] = 0;
    return word;
}
char **get_sentence(char* text, int start, int end)
{
    char **sentence;
    int word_counter = 1;
    int i,index=0;
    int begining = start;

    for(i=start;i<=end;i++)
    {
        if(text[i]==' ')
            word_counter++;
    }
    sentence = (char **)calloc(word_counter,sizeof(char *));
    for(i=start;i<=end;i++)
    {
        if(text[i]==' ')
        {
            sentence[index++] = get_word(text, begining, i-1);
            begining = i+1;
        }
    }
    sentence[index]=get_word(text, begining, i-1);

    return sentence;
}

char*** get_paragraph(char* text, int start, int end)
{
    char ***paragraph;
    int sentence_counter = 0;
    int i,index=0;
    int begining = start;

    for(i=start;i<=end;i++)
    {
        if(text[i]=='.')
            sentence_counter++;
    }
    paragraph = (char ***)calloc(sentence_counter,sizeof(char **));
    for(i=start;i<=end;i++)
    {
        if(text[i]=='.')
        {
            paragraph[index++] = get_sentence(text, begining, i-1);
            begining = i+1;
        }
    }
    return paragraph;
}

char**** get_document(char* text)
{
    char ****document;
    int paragraph_counter = 1;
    int i,index=0;
    int begining = 0;

    for(i=0;text[i];i++)
    {
        if(text[i]=='\n')
            paragraph_counter++;
    }
    document = (char ****)calloc(paragraph_counter,sizeof(char ***));
    for(i=0;text[i];i++)
    {
        if(text[i]=='\n')
        {
            document[index++] = get_paragraph(text, begining, i-1);
            begining = i+1;
        }
    }
    document[index] = get_paragraph(text, begining, i-1);
    return document;

}

char* kth_word_in_mth_sentence_of_nth_paragraph(char**** Doc, int k, int m, int n) {
    return Doc[n-1][m-1][k-1];
}

char** kth_sentence_in_mth_paragraph(char**** Doc, int k, int m) {
    return Doc[m-1][k-1];
}

char*** kth_paragraph(char**** Doc, int k) {
    return Doc[k-1];
}




char* get_input_text() {
    int paragraph_count;
    scanf("%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    getchar();
    for (int i = 0; i < paragraph_count; i++) {
        scanf("%[^\n]%*c", p[i]);
        strcat(doc, p[i]);
        if (i != paragraph_count - 1)
            strcat(doc, "\n");
    }

    char* returnDoc = (char*)malloc((strlen (doc)+1) * (sizeof(char)));
    strcpy(returnDoc, doc);
    return returnDoc;
}

void print_word(char* word) {
    printf("%s", word);
}

void print_sentence(char** sentence) {
    int word_count;
    scanf("%d", &word_count);
    for(int i = 0; i < word_count; i++){
        printf("%s", sentence[i]);
        if( i != word_count - 1)
            printf(" ");
    }
}

void print_paragraph(char*** paragraph) {
    int sentence_count;
    scanf("%d", &sentence_count);
    for (int i = 0; i < sentence_count; i++) {
        print_sentence(*(paragraph + i));
        printf(".");
    }
}

int main()
{
    char* text = get_input_text();
    char**** document = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            char* word = kth_word_in_mth_sentence_of_nth_paragraph(document, k, m, n);
            print_word(word);
        }

        else if (type == 2){
            int k, m;
            scanf("%d %d", &k, &m);
            char** sentence = kth_sentence_in_mth_paragraph(document, k, m);
            print_sentence(sentence);
        }

        else{
            int k;
            scanf("%d", &k);
            char*** paragraph = kth_paragraph(document, k);
            print_paragraph(paragraph);
        }
        printf("\n");
    }
}

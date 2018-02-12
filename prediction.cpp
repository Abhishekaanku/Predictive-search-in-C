#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<conio.h>
struct node {
    char data;
    struct node *ch[27];
    int is_end;
};
struct lst {
    char *word;
    struct lst *next;
};
char get_index(char lt) {
    if(lt>='A' && lt<='Z') {
        lt+='a'-'A';
    }
    else if(lt<'A' || lt>'z') {
        lt=26+'a';
    }
    return lt;
}
void insert(struct node *head,char *word) {
	struct node *p=head,*q=p;;
    int pt=0,i;
    int len=strlen(word);
    while(pt<len-1) {
        char lt=get_index(word[pt]);
        q=p->ch[(int)(lt-'a')];
        if(q==NULL) {
            q=(struct node *)malloc(sizeof(struct node));
            q->data=word[pt];
            for(i=0;i<27;++i) {
                q->ch[i]=NULL;
            }
            q->is_end=0;
            p->ch[(int)(lt-'a')]=q;
        }
        ++pt;
        if(pt==len-1) {
            q->is_end=1;
        }
        p=q;
    }
}
void append(struct lst **head,char *word) {
	struct lst *node1=*head;
	struct lst *node2=(struct lst *)malloc(sizeof(struct lst ));
	node2->word=word;
	node2->next=node1;
	*head=node2;
}
void fill_words(struct node *head,struct lst **w_list,char *word) {
		if(head->is_end) {
        	append(w_list,word);
    	}
        for(int i=0;i<27;++i) {
        	if(head->ch[i]) {
        		int j,l=strlen(word);
    			char *temp=(char *)malloc((2+l)*sizeof(char));
    			for(j=0;j<l;++j) {
        			temp[j]=word[j];
    			}
    			temp[j++]=head->ch[i]->data;
    			temp[j]='\0';
            	fill_words(head->ch[i],w_list,temp);
			}
        }
}
struct lst *get_words(struct node *head,char *word) {
	struct node *p=head;
    int pt=0,len=strlen(word);
    while(pt<len)  {
        char m=get_index(word[pt]);
        p=p->ch[(int)(m-'a')];
        if(p==NULL) {
        	printf("No words found!\n");
            return NULL;
        }
        ++pt;
    }
    struct lst *w_list=NULL;
    fill_words(p,&w_list,word);
    return w_list;
}
void display(struct lst *head) {
	if(head!=NULL) {
		display(head->next);
		puts(head->word);
	}
}
int main() {
    int i,j,k=0;
    struct node *head=(struct node *)malloc(sizeof(struct node ));
    head->data='H';
    for(i=0;i<27;++i) {
        head->ch[i]=NULL;
    }
    FILE *fp=fopen("word_list.txt","r");
    char temp[30];
    while(fgets(temp,50,fp)) {
        if(strcmp(temp,"\n")!=0) {
            insert(head,temp);
            ++k;
        }
    }
    fclose(fp);
    printf("Completed parsing %d words in the file\n",k);
    while(1) {
    	printf("Enter your predictive word: ");
    	scanf("%s",temp);
    	if(strcmp(temp,"0")==0) {
    		break;
		}
    	struct lst *word_list=get_words(head,temp);
    	display(word_list);
	}
	return 0;
}

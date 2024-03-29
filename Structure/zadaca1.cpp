#include<stdio.h>
#include<string.h>
typedef struct Movie{
    char ime[101],zanr[41];
    float rating;

}Movie;
typedef struct StreamingService{
    char ime[51];
    Movie movies[30];
    int n;

}StreamingService;
void print(StreamingService *s,int n){
    for(int i=0;i<n;i++){
        printf("%s\n",s[i].ime);
        for(int j=0;j<s[i].n;j++){
            printf("%s %.1f\n",s[i].movies[j].ime,s[i].movies[j].rating);
        }
    }
}
void showBestStreamingService(StreamingService *s,int n,char *zanr){
    int max=-1,id=-1,flag=0;
    for(int i=0;i<n;i++){
        int suma=0;
        for(int j=0;j<s[i].n;j++){
            if(!strcmp(s[i].movies[j].zanr,zanr)){
                ++suma;
                flag=1;
            }
        }
        if(suma>max){
            max=suma;
            id=i;
        }
    }
    if(flag)printf("Best streaming service is: %s",s[id].ime);
    else printf("No service has movies of the given genre.");

}
int main() {
    int num_services;
    scanf("%d", &num_services);
    StreamingService services[num_services];

    //read streaming services
    for(int i=0;i<num_services;i++){
        scanf("%s %d",services[i].ime,&services[i].n);
        for(int j=0;j<services[i].n;j++){
            scanf("%s %f %s",services[i].movies[j].ime,&services[i].movies[j].rating,services[i].movies[j].zanr);
        }
    }

    //print
    print(services,num_services);

    //call to best streaming service
    char genre[40];
    scanf("%s", genre);
    showBestStreamingService(services, num_services, genre);

    return 0;
}


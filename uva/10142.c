#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void print_scores( int voters, int cand, int scores[][20]){
    int i, j;
    
    for(i=0; i<voters; i++){
        for(j=0; j<cand; j++){
            printf("%d ", scores[i][j]);
        }
        printf("\n");
    }
}
int main(){
    int i, j, n,nc, t, vc, nb, rb, has_winner, min,max, max_count, min_count, elim_count, first_test;
    char cand[20][81];
    int cand_eliminated[20];
    int cand_votes[20];
    int ballots[1000][20];
    char buf[128];
    first_test = 1;
    scanf("%d", &n);
    for(;n-->0;){
       if(first_test){
           first_test = 0;
       }else{
           printf("\n");
       }
       scanf("%d", &nc);
       fgetc(stdin);
       for(i=0; i<nc; i++){
          fgets(cand[i],81,stdin);
       }
       vc = 0;
       while (fgets(buf, 128, stdin) > 0){
           if(buf[0]=='\n')
               break;
           
           j=0;
           nb=0;
           rb=0;
           while( (rb = sscanf( (char*)(((void*)buf)+nb), "%d", &t))>0){
               ballots[vc][j++]=t-1;
               nb+= t<10?2:3;
           }
           vc++;
       }
       
       for(i=0;i<nc;i++){
           cand_eliminated[i]=0;
       }

       has_winner = 0;
       while (!has_winner){
           for(i=0;i<nc;i++){
               cand_votes[i]=0;
           }

           for (i=0;i<vc; i++){
               for(j=0; j<nc; j++){
                   if(!cand_eliminated[ballots[i][j]]){
                       cand_votes[ballots[i][j]]++;
                       break;
                   }
               }
           }
          /*for(i=0; i<nc; i++){
               printf("%d %s\n", cand_votes[i], cand[i]);
           }*/
           min = 1<<10;
           max = -1;
           for(i=0; i<nc; i++){
               if(!cand_eliminated[i]) {
                   if(cand_votes[i]< min){
                       min=cand_votes[i];
                   }
                   if(cand_votes[i] > max){
                       max = cand_votes[i];
                   }
               }
           }
           /*printf("MIN == %d\n", min);
            */
           
           if(max > vc/2){
               for(i=0; i<nc; i++){

                   if(cand_votes[i] == max){
                       printf("%s", cand[i]);
                       has_winner = 1;
                       break;
                   }
                }
            }
           if(has_winner)
               break;
           elim_count = 0;
           if (min != max){
               for(i=0; i<nc; i++){
                   if(cand_votes[i] == min){
                       cand_eliminated[i]=1;
                       elim_count++;
                   }
               }
           }
           max_count = 0;
           min_count = 0;
           if(elim_count == 0){ 
               for(i=0; i<nc; i++){
                   if(!cand_eliminated[i]){
                       if(cand_votes[i] == max){
                           max_count++;
                       }else{
                           min_count++;
                      }
                   }
                }
                if(max_count >= 2 && min_count == 0){
                    for(i=0; i<nc; i++){
                        if(cand_votes[i]==max){
                            printf("%s", cand[i]);
                        }
                    }
                    has_winner = 1;
                }
           }
        }
    }
    return 0;
}

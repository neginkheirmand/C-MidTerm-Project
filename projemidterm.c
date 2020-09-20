#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>   

int n, m;

//---
int r_o_p[1000][1000];
int c_o_p[1000][1000];
int next_r_o_p[10000][10000];
int next_c_o_p[10000][10000];
int num_khabardari[1000];//tedad dozdhayie ke har kalantari az jaygaheshun khabar dare
int khabardari[1000][1000];//har satr neshun dahandeye shomareye kalantarie va sotun neshandeye ine ke kodum yeki az dozd haro mitunn bebinn
//havasemun hast ke shomareE az dozdha ke mirizim hamvare az 1 shuru mishe yani 0 NIST

int numberof_k;
int numberof_p_ineach_k[1000];

//---
int r_thief[1000];
int c_thief[1000];
int next_r_thief[1000];
int next_c_thief[1000];

int dozdharo_gereftn[1000];//harvaght dozdi ra gereftnd dar dosdharo_gereftn[index_dozd] adad yek gharar midahim.
int khabardari_dozdha[1000];
int number_of_thieves;
//...

int jadval_game[1000][1000];//[n][m]

int sum_o_p=0;
int tekunnakhordn=0;
int tedadmarahel=0;
//tedad marhale hayi ke anjam mishe hamun zamanie ke tul mikeshe



int millisleep(unsigned ms)
{
    SetLastError(0);
    Sleep(ms);
    return GetLastError() ?-1 :0;
}



void colorme( int vurudi)
{
    HANDLE  hConsole;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //rangha az 1 shuru mishan ama vurudi mitune -1 ham bashe.
    //-1, 1, 2, 3...
    if(vurudi<0){
        int k=1;
        SetConsoleTextAttribute(hConsole, k);
        printf("%4dT", vurudi*-1);
    }
    else{
        int k=vurudi+1;
        SetConsoleTextAttribute(hConsole, k);
        printf("%4dD", vurudi);
    }
    // you can loop k higher to see more color choices
    // for(k = 1; k < 255; k++)
    // {
    SetConsoleTextAttribute(hConsole, 7);    
    return ;
}



void print(){
    for (int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(jadval_game[i][j]<0){
                // printf("    T");
                colorme(jadval_game[i][j]);
            }
            else if(jadval_game[i][j]==0){
                printf("    -");
            }
            else if(jadval_game[i][j]>0){
                colorme(jadval_game[i][j]);
            }
        }
        printf("\n");
    }

    millisleep(500);
    system("cls");
    return;

}


int check_repetition( int vurudi_r, int vurudi_c){
    if(jadval_game[vurudi_r][vurudi_c]!=0){
        return 1;
    }
    return 0;
}
//this function w


int aya_hameye_dozdharo_gereftan(){
    for(int i=0; i<number_of_thieves; i++){
        if(dozdharo_gereftn[i]==0){
            return 0;
        }
    }
    return 1;
}


int aya_vojud_darad(int input, int shomare_kalantari){
    int i=0;
    while(khabardari[shomare_kalantari][i]!=0){
        if(khabardari[shomare_kalantari][i]==input){
            return 1;
        }
        i++;
    }

    return 0;
}//agar khuruji 1 bud yani ghablan tush bude agar 0 bud yani tush vojud nadashte


void add_to_the_arr(int input, int shomare_kalantari){
    //input az yek bishtar ast
    //ama agar ke input ra dar khod dashte bashad angah digar 
    // an ra ezafe nemikond
    int i=0;
    while(khabardari[shomare_kalantari][i]!=0){
        if(khabardari[shomare_kalantari][i]==input){
            return;
        }
        i++;
    }
    khabardari[shomare_kalantari][i]=input;
    return;
}

void print_kh_police(){
    for(int i=0; i<numberof_k; i++){
        printf("tedad dozdhayi ke kalantarie %d mibine hastesh %d\n", i+1, num_khabardari[i]);
    }
    printf("\n\n");
    return;
}


void aya_khabar_daran(){//in tabe baraye khabardari police hast
    int j=0;
    for(int i=0; i<numberof_k; i++){
        num_khabardari[i]=0;
        j=0;
        while(khabardari[i][j]!=0){
            khabardari[i][j]=0;
            j++;
        }
    }

    for(int z=1; z<=number_of_thieves; z++){
        if(dozdharo_gereftn[z-1]==1){
            continue;
        }
        for(int i=r_thief[z-1]-2; (i<n)&&(i<=r_thief[z-1]+2); i++){
            if(i>=0){
                for(int j=c_thief[z-1]-2; (j<m)&&(j<=c_thief[z-1]+2); j++){
                    if(j>=0){
                        if(jadval_game[i][j]>0 && aya_vojud_darad(z,(jadval_game[i][j])-1)==0){//age be poliC reCD be sharti ke in dozd z ro 
                        //ghablan yeki dige az police haye hamin kalantari nadide bashe be tedad khabardarihaye in kalantari yedune ezafe kon;
                        num_khabardari[(jadval_game[i][j])-1]++;
//hala mikham ke z ro be tah satr (jadval_game[i][j]-1) va sotuni ke avalin 0 az un satr hast ezafe koni
                        add_to_the_arr(z , (jadval_game[i][j])-1);
                        }
                    }
                    else{
                        continue;
                    }
                }
            }
            else{
                continue;
            }
        }
    }
    // print_kh_police();
    return;
}

void delete_from_the_array(int input, int shomare_kalantari){
    //in tabe input ro az in satr bekan va hameye badihash ro yedune shift bede chap
    int i=0;
    while(khabardari[shomare_kalantari][i]!=input){
        i++;
    }
    khabardari[shomare_kalantari][i]=0;
    i++;
    while(khabardari[shomare_kalantari][i]!=0){
        khabardari[shomare_kalantari][i-1]=khabardari[shomare_kalantari][i];
        i++;
    }
    khabardari[shomare_kalantari][i-1]=0;
    return;
}



void nextplacewithoutknowing(int index_k, int index_p){

    //in ghesmate avalesh column jadid ro tu array next_c_o_p set mikone;
    if(c_o_p[index_k][index_p]>0){
        //mituni aghab biyarish
        if(c_o_p[index_k][index_p]<m-1){
            //mituni jelo bebarish
            next_c_o_p[index_k][index_p]=c_o_p[index_k][index_p]+rand()%3;
            next_c_o_p[index_k][index_p]--;
            //chon mikhahim tuye bazeye -1 ta 1 bashe
        }
        else if(c_o_p[index_k][index_p]==m-1){
            //nemituni jelo bebarish
            next_c_o_p[index_k][index_p]=c_o_p[index_k][index_p]+rand()%2;
            next_c_o_p[index_k][index_p]--;
            //chon bayad -1 ya 0 bashe
        }
    }
    if(c_o_p[index_k][index_p]==0){
        //nemituni aghab bebarish
        if(c_o_p[index_k][index_p]<m-1){
            //mituni jelo bebarish
            next_c_o_p[index_k][index_p]=c_o_p[index_k][index_p]+rand()%2;
        }
         else if(c_o_p[index_k][index_p]==m-1){
            //nemituni jelo bebarish
            //koln nemituni kari bokoni
            next_c_o_p[index_k][index_p]=c_o_p[index_k][index_p];
        }

    }


    //in ghesmate row jadid ro tu array next_c_o_p set mikone;
    if(r_o_p[index_k][index_p]>0){
        //mituni bala biyarish
        if(r_o_p[index_k][index_p]<n-1){
            //mituni payin bebarish
            next_r_o_p[index_k][index_p]=r_o_p[index_k][index_p]+(rand()%3);
            next_r_o_p[index_k][index_p]--;
            //chon mikhahim tuye bazeye -1 ta 1 bashe
        }
        else if(r_o_p[index_k][index_p]==n-1){
            //nemituni payin bebarish
            next_r_o_p[index_k][index_p]=r_o_p[index_k][index_p]+(rand()%2);
            next_r_o_p[index_k][index_p]--;
            //chon bayad -1 ya 0 bashe
        }
    }
    else if(r_o_p[index_k][index_p]==0){
        //nemituni bala bebarish
        if(r_o_p[index_k][index_p]<n-1){
            //mituni payin bebarish
            next_r_o_p[index_k][index_p]=r_o_p[index_k][index_p]+(rand()%2);
        }
        else if(r_o_p[index_k][index_p]==n-1){
           // nemituni payin bebarish
           //koln nemituni tekun bokhori
            next_r_o_p[index_k][index_p]=r_o_p[index_k][index_p];
        }
    }
    
    if(next_r_o_p[index_k][index_p]==r_o_p[index_k][index_p]&&next_c_o_p[index_k][index_p]==c_o_p[index_k][index_p]){
        tekunnakhordn++;
        return;
    }
    
    //agar in tabe ro seda bezani bayad behesh indexk va indexp ro bedi unm behet jaye jadide policet ro mide va varedesh mikone tu next_r_o_p
    //va tuye next_c_o_p
    if(jadval_game[(next_r_o_p[index_k][index_p])][(next_c_o_p[index_k][index_p])]==0){
        jadval_game[(r_o_p[index_k][index_p])][(c_o_p[index_k][index_p])]=0;
        jadval_game[(next_r_o_p[index_k][index_p])][(next_c_o_p[index_k][index_p])]=index_k+1;
        return;
    }
    //hamishe yadet bashe adadi ke tuye jadval neshun mide yedune bishtar az unie ke compiler fekr mikone
    else{//farz ine ke in police faghat momkene tuye khune haye khali ya tuye khunehaye police haye dige bere chon dozdi dar didesh nabude.
        jadval_game[(r_o_p[index_k][index_p])][(c_o_p[index_k][index_p])]=index_k+1;
        next_r_o_p[index_k][index_p]=r_o_p[index_k][index_p];
        next_c_o_p[index_k][index_p]=c_o_p[index_k][index_p];
        tekunnakhordn++;
        return;
    }
}


void put_into_oldpolice(int index_k, int index_p){
    r_o_p[index_k][index_p]=next_r_o_p[index_k][index_p];
    c_o_p[index_k][index_p]=next_c_o_p[index_k][index_p];
    return;
}


void in_dozd_ro_begir(int index_dozd){
    dozdharo_gereftn[index_dozd]=1;
    jadval_game[r_thief[index_dozd]][c_thief[index_dozd]]=0;
    //khat balayi serfn baraye ine ke akharin dast bud dige dozdi tuye jadval nabashe
    //un dozd dige mord.
    //pas police ha ham dige uno nemibinn
    int j=0;
    for(int i=0; i<numberof_k; i++){
        j=0; 
        while(khabardari[i][j]!=0){
            if(khabardari[i][j]==index_dozd+1){
                delete_from_the_array(index_dozd+1, i);
                num_khabardari[i]--;
            }
            j++;
        }
    }
    return;
}



void dozd_kodum_samte(int index_k, int index_p, int R_ofknower, int C_ofknower, int index_of_thief){
    if(R_ofknower>r_thief[index_of_thief]){
        //bayad sai koni bebarish bala
        if(C_ofknower>c_thief[index_of_thief]){
            //bayad sai koni bebarish samte chap
            if(jadval_game[R_ofknower-1][C_ofknower-1]<=0){
                //yani hich kodum az police haye dige tush nist ya dozd tushe boro bala chap
                    if(jadval_game[R_ofknower-1][C_ofknower-1]<0){
                        in_dozd_ro_begir((jadval_game[R_ofknower-1][C_ofknower-1]+1)*-1);//in tabe ham array dozdharo_gereftn ro 1 mikone 
                        //ham mire va khabardari police ha ro az un dozd pak mikone. engari ke dige dozde vojud nadare
                        // print();
                        if(aya_hameye_dozdharo_gereftan()==1){
                            printf("jadval_game ghabl az etmam bazi hast:\n");
                            print();
                            exit(0);
                        }
                    }
                jadval_game[R_ofknower][C_ofknower]=0;
                jadval_game[R_ofknower-1][C_ofknower-1]=index_k+1;
                next_c_o_p[index_k][index_p]=C_ofknower-1;
                next_r_o_p[index_k][index_p]=R_ofknower-1;

                return;
            }
            else if(jadval_game[R_ofknower-1][C_ofknower]<=0){
                //age tuye gotre samte dozd poliC bud pas bebareshbala
                    if(jadval_game[R_ofknower-1][C_ofknower]<0){
                        in_dozd_ro_begir((jadval_game[R_ofknower-1][C_ofknower]+1)*-1);
                    }

                jadval_game[R_ofknower][C_ofknower]=0;
                jadval_game[R_ofknower-1][C_ofknower]=index_k+1;
                next_c_o_p[index_k][index_p]=C_ofknower;
                next_r_o_p[index_k][index_p]=R_ofknower-1;
                return;
            }
            else if(jadval_game[R_ofknower][C_ofknower-1]<=0){
                //age tuye gotre samte dozd poliC va bala ham poliC bud bebaresh samte chap
                if(jadval_game[R_ofknower][C_ofknower-1]<0){
                in_dozd_ro_begir((jadval_game[R_ofknower][C_ofknower-1]+1)*-1);
                }
                jadval_game[R_ofknower][C_ofknower]=0;
                jadval_game[R_ofknower][C_ofknower-1]=index_k+1;
                next_c_o_p[index_k][index_p]=C_ofknower-1;
                next_r_o_p[index_k][index_p]=R_ofknower;
                return;
            }
            else{
                //na ghotri na chapi na balayi nemishod harekat kard sare jash negahdar
                jadval_game[R_ofknower][C_ofknower]=index_k+1;
                next_r_o_p[index_k][index_p]=R_ofknower;
                next_c_o_p[index_k][index_p]=C_ofknower;
                tekunnakhordn++;
                return;
            }
        }
        else if(C_ofknower<c_thief[index_of_thief]){
            //bayd sai koni bebarish bala va rast
            if(jadval_game[R_ofknower-1][C_ofknower+1]<=0){
                //mibarimesh bala rast
                if(jadval_game[R_ofknower-1][C_ofknower+1]<0){
                    in_dozd_ro_begir((jadval_game[R_ofknower-1][C_ofknower+1]+1)*-1);
                    if(aya_hameye_dozdharo_gereftan()==1){
                        printf("bazi ghabl az tamum shodn in sheklie:\n");
                        print();
                        exit(0);
                    }
                }
                jadval_game[R_ofknower][C_ofknower]=0;
                jadval_game[R_ofknower-1][C_ofknower+1]=index_k+1;
                next_r_o_p[index_k][index_p]=R_ofknower-1;
                next_c_o_p[index_k][index_p]=C_ofknower+1;
                return;
            }
            else if(jadval_game[R_ofknower-1][C_ofknower]<=0){
                //age tuye khuneye ghotrie bala rast poliC bud mibarimesh bala

                if(jadval_game[R_ofknower-1][C_ofknower]<0){
                    in_dozd_ro_begir((jadval_game[R_ofknower-1][C_ofknower]+1)*-1);
                }
                jadval_game[R_ofknower][C_ofknower]=0;
                jadval_game[R_ofknower-1][C_ofknower]=index_k+1;
                next_r_o_p[index_k][index_p]=R_ofknower-1;
                next_c_o_p[index_k][index_p]=C_ofknower;
                return;
            }
            else if(jadval_game[R_ofknower][C_ofknower+1]<=0){
                //age tuye khuneye ghotrie bala rast poliC bud va tuye balayi ham poliC bud mibarimesh rast

                if(jadval_game[R_ofknower-1][C_ofknower+1]<0){
                    in_dozd_ro_begir((jadval_game[R_ofknower-1][C_ofknower+1]+1)*-1);
                }
                jadval_game[R_ofknower][C_ofknower]=0;
                jadval_game[R_ofknower][C_ofknower+1]=index_k+1;
                next_r_o_p[index_k][index_p]=R_ofknower;
                next_c_o_p[index_k][index_p]=C_ofknower+1;
                return;
            }
            else{
                //na ghotri na balayi na rasti nemishod harekat kard sare jash negahdar
                jadval_game[R_ofknower][C_ofknower]=index_k+1;
                next_r_o_p[index_k][index_p]=R_ofknower;
                next_c_o_p[index_k][index_p]=C_ofknower;
                tekunnakhordn++;
                return;
            }
        }
        else if(c_thief[index_of_thief]==C_ofknower){
            //az nazar rast o chapi tuye ye sotunid
            //bayad faghat sai koni bebarish bala
            //mn dar inja deghatmikonm ke hata agar bala ham ja nabud bebarish bala rast ya bebarish bala chap ham khube, na?
            //tuye ghablia nabayad check mikarD ke az jadval mizane birun ya na chon midunestim ke ye khunee vojud dare ke tush dozd hast.
            //ama inja age nakhaym daghighn mostaghim berim bayad check konim
            if(jadval_game[R_ofknower-1][C_ofknower]<=0){
                //mituni mostaghim yedune bala bebarish

                if(jadval_game[R_ofknower-1][C_ofknower]<0){
                    in_dozd_ro_begir((jadval_game[R_ofknower-1][C_ofknower]+1)*-1);
                    if(aya_hameye_dozdharo_gereftan()==1){ 
                        printf("jadval_game ghabl az etmam bazi hast:\n");
                        print();
                        exit(0);
                    }
                }
                jadval_game[R_ofknower][C_ofknower]=0;
                jadval_game[R_ofknower-1][C_ofknower]=index_k+1;
                next_r_o_p[index_k][index_p]=R_ofknower-1;
                next_c_o_p[index_k][index_p]=C_ofknower;
                return;
            }
            else if(jadval_game[R_ofknower-1][C_ofknower+1]<=0){
                //inja shart mizarim ke ye vaght az jadval birun nazane vaghT mostaghim nemirim
                if(C_ofknower+1<m){
                    // agar nemishod bala bebarish mostaghiman pas rast bala boro

                    if(jadval_game[R_ofknower-1][C_ofknower+1]<0){
                        in_dozd_ro_begir((jadval_game[R_ofknower-1][C_ofknower+1]+1)*-1);
                    }

                    jadval_game[R_ofknower][C_ofknower]=0;
                    jadval_game[R_ofknower-1][C_ofknower+1]=index_k+1;
                    next_r_o_p[index_k][index_p]=R_ofknower-1;
                    next_c_o_p[index_k][index_p]=C_ofknower+1;
                    return;
                }
            }
            else if(jadval_game[R_ofknower-1][C_ofknower-1]<=0){
                //nemituni mostaghim bala ya  bala rast bebarish pas bebaresh bala chap
                //hamchenan bayad check konim ke az jadval birun nazane
                if(C_ofknower>0){
                    if(jadval_game[R_ofknower-1][C_ofknower-1]<0){
                        in_dozd_ro_begir((jadval_game[R_ofknower-1][C_ofknower-1]+1)*-1);
                    }
                    jadval_game[R_ofknower][C_ofknower]=0;
                    jadval_game[R_ofknower-1][C_ofknower-1]=index_k+1;
                    next_r_o_p[index_k][index_p]=R_ofknower-1;
                    next_c_o_p[index_k][index_p]=C_ofknower-1;
                    return;
                }
            }
            else{
                //na bala, na bala rast, na balla chap nemitunibabrish;
                //tekun nakhor
                jadval_game[R_ofknower][C_ofknower]=index_k+1;
                next_r_o_p[index_k][index_p]=R_ofknower;
                next_c_o_p[index_k][index_p]=C_ofknower;
                tekunnakhordn++;
                return;
            }
        }
    }
    else if(R_ofknower<r_thief[index_of_thief]){
        //bayad bebarish payin
        if(C_ofknower>c_thief[index_of_thief]){
            //bayad sai koni bebarish payin chap
            if(jadval_game[R_ofknower+1][C_ofknower-1]<=0){
                //mituni bebarish payin chap
                if(jadval_game[R_ofknower+1][C_ofknower-1]<0){
                    in_dozd_ro_begir((jadval_game[R_ofknower+1][C_ofknower-1]+1)*-1);
                    if(aya_hameye_dozdharo_gereftan()==1){
                    printf("jadval_game ghabl az etmam bazi hast:\n");
                    print();
                    exit(0);
                    }
                }
                jadval_game[R_ofknower][C_ofknower]=0;
                jadval_game[R_ofknower+1][C_ofknower-1]=index_k+1;
                next_r_o_p[index_k][index_p]=R_ofknower+1;
                next_c_o_p[index_k][index_p]=C_ofknower-1;
                return;
            }
            else if(jadval_game[R_ofknower+1][C_ofknower]<=0){
                //nemituni bebarish payin chap pas bebaresh payin


                if(jadval_game[R_ofknower+1][C_ofknower]<0){
                    in_dozd_ro_begir((jadval_game[R_ofknower+1][C_ofknower]+1)*-1);
                }
                jadval_game[R_ofknower][C_ofknower]=0;
                jadval_game[R_ofknower+1][C_ofknower]=index_k+1;
                next_r_o_p[index_k][index_p]=R_ofknower+1;
                next_c_o_p[index_k][index_p]=C_ofknower;
                return;
            }
            else if(jadval_game[R_ofknower][C_ofknower-1]<=0){
                //nemituni bebarish payin chap ya payin pas bebaresh chap

                if(jadval_game[R_ofknower][C_ofknower-1]<0){
                    in_dozd_ro_begir((jadval_game[R_ofknower][C_ofknower-1]+1)*-1);
                }
                jadval_game[R_ofknower][C_ofknower]=0;
                jadval_game[R_ofknower][C_ofknower-1]=index_k+1;
                next_r_o_p[index_k][index_p]=R_ofknower;
                next_c_o_p[index_k][index_p]=C_ofknower-1;
                return;
            }
            else{
                //nemituni bebarish payin chap ya payin ya chap, pas tekuneshnade
                jadval_game[R_ofknower][C_ofknower]=index_k+1;
                next_r_o_p[index_k][index_p]=R_ofknower;
                next_c_o_p[index_k][index_p]=C_ofknower;
                tekunnakhordn++;
                return;
            }
        }
        else if(C_ofknower<c_thief[index_of_thief]){
            //bayad sai koni bebarish payin rast
            if(jadval_game[R_ofknower+1][C_ofknower+1]<=0){
            //mibarimesh payin rast
                if(jadval_game[R_ofknower+1][C_ofknower+1]<0){
                    in_dozd_ro_begir((jadval_game[R_ofknower+1][C_ofknower+1]+1)*-1);
                    if(aya_hameye_dozdharo_gereftan()==1){
                    printf("jadval_game ghabl az etmam bazi hast:\n");
                    print();
                    exit(0);
                    }
                }
                jadval_game[R_ofknower][C_ofknower]=0;
                jadval_game[R_ofknower+1][C_ofknower+1]=index_k+1;
                next_c_o_p[index_k][index_p]=C_ofknower+1;
                next_r_o_p[index_k][index_p]=R_ofknower+1;
                return;
            }
            else if(jadval_game[R_ofknower+1][C_ofknower]<=0){
            //nemituni bebarish payin rast mibarish payin

                if(jadval_game[R_ofknower+1][C_ofknower]<0){
                    in_dozd_ro_begir((jadval_game[R_ofknower+1][C_ofknower]+1)*-1);
                }
                jadval_game[R_ofknower][C_ofknower]=0;
                jadval_game[R_ofknower+1][C_ofknower]=index_k+1;
                next_c_o_p[index_k][index_p]=C_ofknower;
                next_r_o_p[index_k][index_p]=R_ofknower+1;
                return;
            }
            else if(jadval_game[R_ofknower][C_ofknower+1]<=0){
            //nemituni bebarish payin rast ya payin mibarish rast

                if(jadval_game[R_ofknower][C_ofknower+1]<0){
                    in_dozd_ro_begir((jadval_game[R_ofknower][C_ofknower+1]+1)*-1);
                }
                jadval_game[R_ofknower][C_ofknower]=0;
                jadval_game[R_ofknower][C_ofknower+1]=index_k+1;
                next_c_o_p[index_k][index_p]=C_ofknower+1;
                next_r_o_p[index_k][index_p]=R_ofknower;
                return;
            }
            else{
                //nemituni bebarish payin rast ya payin ya rast pas tekun nakhor
                jadval_game[R_ofknower][C_ofknower]=index_k+1;
                next_r_o_p[index_k][index_p]=R_ofknower;
                next_c_o_p[index_k][index_p]=C_ofknower;
                tekunnakhordn++;
                return;
            }
        }
        else if(C_ofknower==c_thief[index_of_thief]){
            //bayad bebarish payin
            if(jadval_game[R_ofknower+1][C_ofknower]<=0){
                if(jadval_game[R_ofknower+1][C_ofknower]<0){
                    in_dozd_ro_begir((jadval_game[R_ofknower+1][C_ofknower]+1)*-1);
                    if(aya_hameye_dozdharo_gereftan()==1){
                        printf("jadval_game ghabl az etmam bazi hast:\n");
                        print();
                        exit(0);
                    }
                }
                jadval_game[R_ofknower][C_ofknower]=0;
                jadval_game[R_ofknower+1][C_ofknower]=index_k+1;
                next_r_o_p[index_k][index_p]=R_ofknower+1;
                next_c_o_p[index_k][index_p]=C_ofknower;
                return;
            }
            //age natunesti ke mostaghim payin bebarish bebaresh rast payin ya chap payin ama deghat kon ke az jadval birun nazani
            if(jadval_game[R_ofknower+1][C_ofknower+1]<=0){
                //bebaresh payin rast
                if(C_ofknower+1<m){
                    if(jadval_game[R_ofknower+1][C_ofknower+1]<0){
                        in_dozd_ro_begir((jadval_game[R_ofknower+1][C_ofknower+1]+1)*-1);
                    }
                    jadval_game[R_ofknower][C_ofknower]=0;
                    jadval_game[R_ofknower+1][C_ofknower+1]=index_k+1;
                    next_c_o_p[index_k][index_p]=C_ofknower+1;
                    next_r_o_p[index_k][index_p]=R_ofknower+1;
                    return;
                }
            }
            if(jadval_game[R_ofknower+1][C_ofknower-1]<=0){
                //bebaresh payin chap
                if(C_ofknower>0){
                    if(jadval_game[R_ofknower+1][C_ofknower-1]<0){
                        in_dozd_ro_begir((jadval_game[R_ofknower+1][C_ofknower-1]+1)*-1);
                    }
                    jadval_game[R_ofknower][C_ofknower]=0;
                    jadval_game[R_ofknower+1][C_ofknower-1]=index_k+1;
                    next_c_o_p[index_k][index_p]=C_ofknower-1;
                    next_r_o_p[index_k][index_p]=R_ofknower+1;
                    return;
                }
            }

            //nemituni tekun bedish pas sare jat bemun
            jadval_game[R_ofknower][C_ofknower]=index_k+1;
            next_r_o_p[index_k][index_p]=R_ofknower;
            next_c_o_p[index_k][index_p]=C_ofknower;
            return;
        }
    }
    else if( R_ofknower==r_thief[index_of_thief]){
        //nabayad bala payinesh koni
        if(C_ofknower>c_thief[index_of_thief]){
            //bayad sai koni bebarish chap
            if(jadval_game[R_ofknower][C_ofknower-1]<=0){
                if(jadval_game[R_ofknower][C_ofknower-1]<0){
                    in_dozd_ro_begir((jadval_game[R_ofknower][C_ofknower-1]+1)*-1);
                    if(aya_hameye_dozdharo_gereftan()==1){
                    printf("jadval_game ghabl az etmam bazi hast:\n");
                    print();
                    exit(0);
                    }
                }
                jadval_game[R_ofknower][C_ofknower]=0;
                jadval_game[R_ofknower][C_ofknower-1]=index_k+1;
                next_c_o_p[index_k][index_p]=C_ofknower-1;
                next_r_o_p[index_k][index_p]=R_ofknower;
                return;
            }
            //okey ma behtare ke bebarimesh be samte chap faghat vali age bala chap ya payin chap ham kaC nabud bebarimesh unja
            //ham sud kardim, na??
            //baraye chand ta dozd ghesmate emtiazi soal che ghalati mikhay bokoni??
            // else if(R_ofknower>0||R_ofknower<n-1){
            if(R_ofknower>0){
                //natunesti mostaghim chap bebarish ama mituni bebarish bala va chap agar khali bud
                if(jadval_game[R_ofknower-1][C_ofknower-1]==0||jadval_game[R_ofknower-1][C_ofknower-1]<0){
                    // if(jadval_game[R_ofknower-1][C_ofknower-1]==-1){
                    //     printf("dozd ro police%d az kalantari%d tuye r=%d va c=%d gereftesh\n ", index_p+1, index_k+1, R_ofknower-1, C_ofknower-1);
                    //     printf("jadval_game ghabl az etmam bazi hast:\n");
                    //     print();
                    //     exit(0);
                    // }
                    jadval_game[R_ofknower][C_ofknower]=0;
                    jadval_game[R_ofknower-1][C_ofknower-1]=index_k+1;
                    next_r_o_p[index_k][index_p]=R_ofknower-1;
                    next_c_o_p[index_k][index_p]=C_ofknower-1;
                    return;
                }
            }
            if(R_ofknower<n-1){
                //mostaghim chap ke nashod ama mituni biyarish payin va chap agar:
                if(jadval_game[R_ofknower+1][C_ofknower-1]==0||jadval_game[R_ofknower+1][C_ofknower-1]<0){
                    // if(jadval_game[R_ofknower+1][C_ofknower-1]==-1){
                    //     printf("dozd ro police%d az kalantari%d tuye r=%d va c=%d gereftesh\n ", index_p+1, index_k+1, R_ofknower+1, C_ofknower-1);
                    //     printf("jadval_game ghabl az etmam bazi hast:\n");
                    //     print();
                    //     exit(0);
                    // }
                    jadval_game[R_ofknower][C_ofknower]=0;
                    jadval_game[R_ofknower+1][C_ofknower-1]=index_k+1;
                    next_r_o_p[index_k][index_p]=R_ofknower+1;
                    next_c_o_p[index_k][index_p]=C_ofknower-1;
                    return;
                }
            }
            //tuye ye khatin ama hich rahi baraye nazdik tar shodn be un nadari
            jadval_game[R_ofknower][C_ofknower]=index_k+1;
            next_r_o_p[index_k][index_p]=R_ofknower;
            next_c_o_p[index_k][index_p]=C_ofknower;
            tekunnakhordn++;
            return;
        // }
        }
        else if(C_ofknower<c_thief[index_of_thief]){
            //bayad beri samte rast
            if(jadval_game[R_ofknower][C_ofknower+1]<=0){
                if(jadval_game[R_ofknower][C_ofknower+1]<0){
                    in_dozd_ro_begir((jadval_game[R_ofknower][C_ofknower+1]+1)*-1);
                    if(aya_hameye_dozdharo_gereftan()==1){
                    printf("jadval_game ghabl az etmam bazi hast:\n");
                    print();
                    exit(0);
                    }
                }
                jadval_game[R_ofknower][C_ofknower]=0;
                jadval_game[R_ofknower][C_ofknower+1]=index_k+1;
                next_r_o_p[index_k][index_p]=R_ofknower;
                next_c_o_p[index_k][index_p]=C_ofknower+1;
                return;
            }
            // else if(R_ofknower>0||R_ofknower<n-1){
            if(R_ofknower>0){
                //yani mituni biyarish bala va rast
                if(jadval_game[R_ofknower-1][C_ofknower+1]<=0){
                    if(jadval_game[R_ofknower-1][C_ofknower+1]<0){
                        in_dozd_ro_begir((jadval_game[R_ofknower-1][C_ofknower+1]+1)*-1);
                        if(aya_hameye_dozdharo_gereftan()==1){
                            printf("jadval_game ghabl az etmam bazi hast:\n");
                            print();
                            exit(0);
                        }
                    }
                    jadval_game[R_ofknower][C_ofknower]=0;
                    jadval_game[R_ofknower-1][C_ofknower+1]=index_k+1;
                    next_r_o_p[index_k][index_p]=R_ofknower-1;
                    next_c_o_p[index_k][index_p]=C_ofknower+1;
                    return;
                }

            }
            if(R_ofknower<n-1){
                //yani mituni bebarish payin va rast
                if(jadval_game[R_ofknower+1][C_ofknower+1]<=0){
                    if(jadval_game[R_ofknower+1][C_ofknower+1]<0){
                        in_dozd_ro_begir((jadval_game[R_ofknower+1][C_ofknower+1]+1)*-1);
                        if(aya_hameye_dozdharo_gereftan()==1){
                            printf("jadval_game ghabl az etmam bazi hast:\n");
                            print();
                            exit(0);
                        }
                    }
                    jadval_game[R_ofknower][C_ofknower]=0;
                    jadval_game[R_ofknower+1][C_ofknower+1]=index_k+1;
                    next_r_o_p[index_k][index_p]=R_ofknower+1;
                    next_c_o_p[index_k][index_p]=C_ofknower+1;
                    return;
                }
            }
            //tuye ye radifid ama hich rahi baraye nazDk shodn be un nadari
            jadval_game[R_ofknower][C_ofknower]=index_k+1;
            next_c_o_p[index_k][index_p]=C_ofknower;
            next_r_o_p[index_k][index_p]=R_ofknower;
            tekunnakhordn++;
            return;
            // }
        }
    }
}


int the_neareast_thief(int index_k, int index_p){
//this function should take the poliman's station and serial number and return the serial number of the nearest thief around him.
//like this he will know where he should go. we'll need that index in the function of dozd_kodum_samte
//aval ruye moraba kuchik tar harekat mikonim ke 8 ta khune bishtar nadare
    for(int i=r_o_p[index_k][index_p]-1; i<n && i<=r_o_p[index_k][index_p]+1; i++){
        if(i>=0){
            for(int j=c_o_p[index_k][index_p]-1; j<m && j<=c_o_p[index_k][index_p]+1; j++){
                if(j>=0){
                    if(jadval_game[i][j]<0&&dozdharo_gereftn[(jadval_game[i][j]+1)*-1]==0){
                        return ((jadval_game[i][j]+1)*-1);
                    }
                }else{
                    continue;
                }
            }
        }else{
            continue;
        }
    }
//agar tuye un 8 ta khuneye nazdiktar chizi bud ke ta alan return shode bud pas tuye un khunehaye ba faseleye 2 hastan

    for(int i=r_o_p[index_k][index_p]-2; i<n && i<=r_o_p[index_k][index_p]+2; i++){
        if(i>=0){
            for(int j=c_o_p[index_k][index_p]-2; j<m && j<=c_o_p[index_k][index_p]+2; j++){
                if(j>=0){
                    if(jadval_game[i][j]<0&&dozdharo_gereftn[(jadval_game[i][j]+1)*-1]==0){
                        return ((jadval_game[i][j]+1)*-1);
                    }
                }else{
                    continue;
                }
            }
        }else{
            continue;
        }
    }
    //age recd be inja yani khode police kaCo nadide va serfan az bisim fahmide ke dozd kojast inja dige bayad morajeE konim be khabardari[][]
    //ke tush shomareye dozdhayi ke har kalantari azashun khabardare ro negah midare
    // system("cls");
    // print();
    // printf("\n alan khodesh kaCo nemibine vali dare mire donbale dozD ke hamkalantariash behesh goftn va in hamin dozde \n");
    // getchar();
    int j=0;
    while(khabardari[index_k][j]!=0){
        if(dozdharo_gereftn[khabardari[index_k][j]-1]==0){
            return (khabardari[index_k][j]-1);
        }
        j++;
    }
    
}
//returns the index of the nearest thief;



void makanjadidpoliceknower(int index_k){
//chon police haye kalantari ke behem pas dadi hame khabar daran mn ruye arayeye next_r_thief va next_c_thief hame harekat mikonm
// va khuneye jadid hameye afrad un kalantari ro avaz mikonm
int index_thief;
    for(int j=0; j<numberof_p_ineach_k[index_k]; j++){
        index_thief=the_neareast_thief(index_k, j);
        dozd_kodum_samte(index_k, j, r_o_p[index_k][j], c_o_p[index_k][j], index_thief);
        r_o_p[index_k][j]=next_r_o_p[index_k][j];
        c_o_p[index_k][j]=next_c_o_p[index_k][j];
    }
}





//__________________________________
void tabeyekomaki_khabardaridozd(int i){
    for(int y=r_thief[i]-2; y<n && y<=r_thief[i]+2; y++){
        if(y>=0){
            for(int x=c_thief[i]-2; x<m && x<=c_thief[i]+2; x++){
                if(x>=0){
                    if(jadval_game[y][x]>0){
                        khabardari_dozdha[i]=1;
                        return;
                    }
                }else{
                    continue;
                }
            }
        }else{
            continue;
        }
        
    }
    return;
}

void print_kh_dozd(){
    for(int i=0; i<number_of_thieves; i++){
        printf("khabardari dozd %d hast %d\n", i+1, khabardari_dozdha[i]);
    }
    printf("\n\n");
    return;
}

void aya_dozdha_khabar_daran(){
    for(int i=0; i<number_of_thieves; i++){
        khabardari_dozdha[i]=0;
        tabeyekomaki_khabardaridozd(i);
    }
    // print_kh_dozd();
    return;
}




void next_row_of_thief(int shomareye_dozd){
    if(r_thief[shomareye_dozd]>0){
        //mituni bala biyarish
        if(r_thief[shomareye_dozd]<n-1){
            //mituni payin bebarish
            next_r_thief[shomareye_dozd]=r_thief[shomareye_dozd]+rand()%3;
            next_r_thief[shomareye_dozd]--;
            //chon mikhahim tuye bazeye -1 ta 1 bashe
        }
        else if(r_thief[shomareye_dozd]==n-1){
            //nemituni payin bebarish
            next_r_thief[shomareye_dozd]=r_thief[shomareye_dozd]+rand()%2;
            next_r_thief[shomareye_dozd]--;
            //chon bayad -1 ya 0 bashe
        }
    }
    if(r_thief[shomareye_dozd]==0){
        //nemituni bala bebarish
        if(r_thief[shomareye_dozd]<n-1){
            //mituni payin bebarish
            next_r_thief[shomareye_dozd]=r_thief[shomareye_dozd]+rand()%2;
        }
        else if(r_thief[shomareye_dozd]==n-1){
         //   nemituni payin bebarish
         next_r_thief[shomareye_dozd]=r_thief[shomareye_dozd];
        }

    }
}


void next_col_of_thief(int shomareye_dozd){
    if(c_thief[shomareye_dozd]>0){
        //mituni aghab biyarish
        if(c_thief[shomareye_dozd]<m-1){
            //mituni jelo bebarish
            next_c_thief[shomareye_dozd]=c_thief[shomareye_dozd]+rand()%3;
            next_c_thief[shomareye_dozd]--;
            //chon mikhahim tuye bazeye -1 ta 1 bashe
        }
        else if(c_thief[shomareye_dozd]==m-1){
            //nemituni jelo bebarish
            next_c_thief[shomareye_dozd]=c_thief[shomareye_dozd]+rand()%2;
            next_c_thief[shomareye_dozd]--;
            //chon bayad -1 ya 0 bashe
        }
    }
    if(c_thief[shomareye_dozd]==0){
        //nemituni aghab bebarish
        if(c_thief[shomareye_dozd]<m-1){
            //mituni jelo bebarish
            next_c_thief[shomareye_dozd]=c_thief[shomareye_dozd]+rand()%2;
        }
         else if(c_thief[shomareye_dozd]==m-1){
            //nemituni jelo bebarish
            next_c_thief[shomareye_dozd]=c_thief[shomareye_dozd];
        }

    }
}
//in tabe motmaen mishe ke adaD ke behesh khuruji mide hatman tuye jadval bashe



void makanjadiddozdha(int index_thief){
    next_col_of_thief(index_thief);
    next_row_of_thief(index_thief);


    if(r_thief[index_thief]==next_r_thief[index_thief]&&c_thief[index_thief]==next_c_thief[index_thief]){
        tekunnakhordn++;
        return;
    }
    else if(check_repetition(next_r_thief[index_thief], next_c_thief[index_thief])==1){
        //age did ke khuneE ke dare mire tush, tush police hast sare jash mimune
        tekunnakhordn++;
        next_r_thief[index_thief]=r_thief[index_thief];
        next_c_thief[index_thief]=c_thief[index_thief];
        
    }

    jadval_game[r_thief[index_thief]  ][c_thief[index_thief]]=0;
    jadval_game[next_r_thief[index_thief]][next_c_thief[index_thief]]=-1*(index_thief+1);
    //tuye jadval 0 motealegh be khune haye khalie va shomareye dozdha az -1 shoru mishavad
    r_thief[index_thief]=next_r_thief[index_thief];
    c_thief[index_thief]=next_c_thief[index_thief];
    return;
}




int majmue_payini(int index_thief){
    int answer=0;
    for(int i=r_thief[index_thief]+1; (i<n)&&(i<=r_thief[index_thief]+2); i++){
        for(int j=c_thief[index_thief]-2; (j<m)&&(j<=c_thief[index_thief]+2); j++){
            if(j>=0){
                if(jadval_game[i][j]>0){
                    answer++;
                }
            }
            else{
                continue;
            }
        }
    }
    return answer;
}


int majmue_balayi(int index_thief){
    int answer=0;
    for(int i=r_thief[index_thief]-2; i<r_thief[index_thief]; i++){
        if(i>=0){
            for(int j=c_thief[index_thief]-2; (j<m)&&(j<=c_thief[index_thief]+2); j++){
                if(j>=0){
                    if(jadval_game[i][j]>0){
                    answer++;
                    }
                }
                else{
                    continue;
                }
            }
        }
        else{
            continue;
        }
    }
    return answer;
}


int majmue_chapi(int index_thief){
    int answer=0;
    for(int i=c_thief[index_thief]-2; i<c_thief[index_thief]; i++){
        if(i>=0){
            for(int j=r_thief[index_thief]-2; (j<n)&&(j<=r_thief[index_thief]+2); j++){
                if(j>=0){
                    if(jadval_game[j][i]>0){
                    answer++;
                    }
                }
                else{
                    continue;
                }
            }
        }
        else{
            continue;
        }
    }
    return answer;
}



int majmue_rasti(int index_thief){
    int answer=0;
    for(int i=c_thief[index_thief]+1; i<m&&i<=c_thief[index_thief]+2; i++){
        for(int j=r_thief[index_thief]-2; (j<n)&&(j<=r_thief[index_thief]+2); j++){
            if(j>=0){
                if(jadval_game[j][i]>0){
                    //shart bala baraye ine ke agar tuye khunehayi ke dare rushun harekat mikone dosD bud un shomareye manfie dozd tasir
                    //nadashte bashe
                    answer++;
                }
            }
            else{
                continue;
            }
        }
    }

    return answer;
}



void makanjadiddozd_knower(int shomareye_dozd){
    int majmue_khunehaye_payin= majmue_payini(shomareye_dozd);
    int majmue_khunehaye_bala=majmue_balayi(shomareye_dozd);
    int majmue_khunehaye_chap=majmue_chapi(shomareye_dozd);
    int majmue_khunehaye_rast=majmue_rasti(shomareye_dozd);
     //jolo va aghab raftan ro hala set mikonim:
    if(majmue_khunehaye_rast>majmue_khunehaye_chap && c_thief[shomareye_dozd]-1>=0){
        //biyaresh chap
        next_c_thief[shomareye_dozd]=c_thief[shomareye_dozd]-1;
    }
    else if(majmue_khunehaye_rast<majmue_khunehaye_chap&&c_thief[shomareye_dozd]+1<m){
        next_c_thief[shomareye_dozd]=c_thief[shomareye_dozd]+1;
    }

    else{
        next_c_thief[shomareye_dozd]=c_thief[shomareye_dozd];
    }

    //bala va payin raftan ro hala set mikonim:


    if(majmue_khunehaye_bala>majmue_khunehaye_payin&&r_thief[shomareye_dozd]+1<n){

        next_r_thief[shomareye_dozd]=r_thief[shomareye_dozd]+1;
    }
    else if(majmue_khunehaye_bala<majmue_khunehaye_payin&&r_thief[shomareye_dozd]-1>=0){
        next_r_thief[shomareye_dozd]=r_thief[shomareye_dozd]-1;
    }
    else{
        next_r_thief[shomareye_dozd]=r_thief[shomareye_dozd];
    }

    if(r_thief[shomareye_dozd]==0||r_thief[shomareye_dozd]==n-1){
        if(majmue_khunehaye_rast==0&&c_thief[shomareye_dozd]<m-1){
            next_c_thief[shomareye_dozd]=c_thief[shomareye_dozd]+1;
        }
        else if(majmue_khunehaye_chap==0&&c_thief[shomareye_dozd]>0){
            next_c_thief[shomareye_dozd]=c_thief[shomareye_dozd]-1;
        }
    }

    if(c_thief[shomareye_dozd]==0||c_thief[shomareye_dozd]==m-1){
        if(majmue_khunehaye_payin==0&&r_thief[shomareye_dozd]<n-1){
            next_r_thief[shomareye_dozd]=r_thief[shomareye_dozd]+1;
        }
        else if(majmue_khunehaye_bala==0&&r_thief[shomareye_dozd]>0){
            next_r_thief[shomareye_dozd]=r_thief[shomareye_dozd]-1;
        }
    }
    if(majmue_khunehaye_bala==majmue_khunehaye_payin && majmue_khunehaye_bala==0){
        //yani police ya police ha daghighan tuye khat to hastn
        if(majmue_khunehaye_chap!=0&&majmue_khunehaye_rast!=0){
            //yani daran az do taraf behet nazdik mishan pas ya payin boro ya bal age mituni
            if(r_thief[shomareye_dozd]>0){
                next_r_thief[shomareye_dozd]=r_thief[shomareye_dozd]-1;
                next_c_thief[shomareye_dozd]=c_thief[shomareye_dozd];
            }
            else if(r_thief[shomareye_dozd]<n-1){
                next_r_thief[shomareye_dozd]=r_thief[shomareye_dozd]+1;
                next_c_thief[shomareye_dozd]=c_thief[shomareye_dozd];
            }
        }
    }

    if(check_repetition(next_r_thief[shomareye_dozd], next_c_thief[shomareye_dozd])==1){
        //age khuneyi ke mikhay tush beri, tush police bud naro, sare jat bebun
        next_c_thief[shomareye_dozd]=c_thief[shomareye_dozd];
        next_r_thief[shomareye_dozd]=r_thief[shomareye_dozd];
        tekunnakhordn++;
    }
        jadval_game[r_thief[shomareye_dozd]][c_thief[shomareye_dozd]]=0;
        r_thief[shomareye_dozd]=next_r_thief[shomareye_dozd];
        c_thief[shomareye_dozd]=next_c_thief[shomareye_dozd];
        jadval_game[r_thief[shomareye_dozd]][c_thief[shomareye_dozd]]=-1*(shomareye_dozd+1);
    return;
}




int main(){
    while(1<2){
        printf("Please enter the number of rows:\n");
        scanf("%d", &n);
        printf("Please enter the number of columns\n");
        scanf("%d", &m);
        printf("Please enter the number of police stations\n");
        scanf("%d",&numberof_k);
        for(int i=0; i<numberof_k; i++){
            printf("Please enter the number of polices in police station number %d\n", i+1);
            scanf("%d", &numberof_p_ineach_k[i]);
            sum_o_p+=numberof_p_ineach_k[i];
        }
        if(sum_o_p>=(n*m)){
            printf("the number of polices are to many for the space chosen for this game, please try with more reasonable numbers\n");
            continue;
        }
        printf("please enter the number of thieves\n");
        scanf("%d", &number_of_thieves);
        if(sum_o_p+number_of_thieves>(n*m)){
            printf("the number of thieves entered are too many for the GameBoard, please try with more resonable numbers\n");
            continue;
        }
        time_t t=time(NULL);
        srand(t);

        //makan avalieye dozdharo set mikonim
        for(int i=0; i<number_of_thieves; i++){
            r_thief[i]=rand()%n;
            c_thief[i]=rand()%m;
            while(check_repetition(r_thief[i], c_thief[i])==1){
                r_thief[i]=rand()%n;
                c_thief[i]=rand()%m;
            }
            jadval_game[r_thief[i]][c_thief[i]]=-1*(i+1);
        }

        for(int i=0; i<numberof_k; i++){
            for(int j=0; j<numberof_p_ineach_k[i]; j++){
                r_o_p[i][j]=(rand()%n);
                c_o_p[i][j]=(rand()%m);
                while(check_repetition(r_o_p[i][j], c_o_p[i][j])==1){
                    r_o_p[i][j]=(rand()%n);
                    c_o_p[i][j]=(rand()%m);
                }
                jadval_game[r_o_p[i][j]][c_o_p[i][j]]=i+1;
            }
        }
        system("cls");
        print();
        aya_dozdha_khabar_daran();
        system("cls");
        while(1>0){
            if(aya_hameye_dozdharo_gereftan()==1){
                return 0;
            }
            for(int i=0; i<number_of_thieves; i++){
                if(dozdharo_gereftn[i]==1){
                    continue;
                }

                else if(khabardari_dozdha[i]==0 && dozdharo_gereftn[i]==0){
                    makanjadiddozdha(i);
                }
                else if(khabardari_dozdha[i]==1 && dozdharo_gereftn[i]==0){
                    makanjadiddozd_knower(i);
                }
            }
            print();
            aya_khabar_daran();
            system("cls");
            for(int i=0; i<numberof_k; i++){
                for(int j=0; j<numberof_p_ineach_k[i]; j++){
                    if(num_khabardari[i]>0){
                        makanjadidpoliceknower(i);
                        aya_khabar_daran();
                        break;
                    }
                    else if(num_khabardari[i]==0){
                        nextplacewithoutknowing(i, j);
                    }
                    put_into_oldpolice(i, j);
                    aya_khabar_daran();
                }
            }
            print();
            aya_dozdha_khabar_daran();
            system("cls");
            tedadmarahel++;
        }

    }
    return 0;
}
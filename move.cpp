#include "move.h"

Move::Move()
{
    finaldepth=4;//leave this on 4 after testes
    nbr_noeuds=0;
}

int Move::heuristique(int player, Board table, int p)
{
    int score=0;
    for(int i=0;i<24;i++)
    {
        if(table.boardArea[i]==p && (table.checkMill(i) == player))
        {
            score++;
        }

    }
    return score;
}

void Move::voisin(int i,vector<int>* v,int state[24],int with)
{
    switch(i){
case 0:
    {
        if(state[1]==with)
            (*v).push_back(1);
        if(state[9]==with)
            (*v).push_back(9);
        break;
    }
case 1:
    {
        if(state[0]==with)
            (*v).push_back(0);
        if(state[2]==with)
            (*v).push_back(2);
        if(state[4]==with)
            (*v).push_back(4);
        break;
    }
case 2:
    {
        if(state[1]==with)
            (*v).push_back(1);
        if(state[14]==with)
            (*v).push_back(14);
        break;
    }
case 3:
    {
        if(state[4]==with)
            (*v).push_back(4);
        if(state[10]==with)
            (*v).push_back(10);
        break;
    }
case 4:
    {
        if(state[3]==with)
            (*v).push_back(3);
        if(state[5]==with)
            (*v).push_back(5);
        if(state[7]==with)
            (*v).push_back(7);
        if(state[1]==with)
            (*v).push_back(1);
        break;
    }
case 5:
    {
        if(state[4]==with)
            (*v).push_back(4);
        if(state[13]==with)
            (*v).push_back(13);
        break;
    }
case 6:
    {
        if(state[7]==with)
            (*v).push_back(7);
        if(state[11]==with)
            (*v).push_back(11);
        break;
    }
case 7:
    {
        if(state[4]==with)
            (*v).push_back(4);
        if(state[6]==with)
            (*v).push_back(6);
        if(state[8]==with)
            (*v).push_back(8);
        break;
    }
case 8:
    {
        if(state[7]==with)
            (*v).push_back(7);
        if(state[12]==with)
            (*v).push_back(12);
        break;
    }
case 9:
    {
        if(state[0]==with)
            (*v).push_back(0);
        if(state[21]==with)
            (*v).push_back(21);
        if(state[10]==with)
            (*v).push_back(10);
        break;
    }
case 10:
    {
        if(state[9]==with)
            (*v).push_back(9);
        if(state[11]==with)
            (*v).push_back(11);
        if(state[3]==with)
            (*v).push_back(3);
        if(state[18]==with)
            (*v).push_back(18);
        break;
    }
case 11:
    {
        if(state[6]==with)
            (*v).push_back(6);
        if(state[15]==with)
            (*v).push_back(15);
        if(state[10]==with)
            (*v).push_back(10);
        break;
    }
case 12:
    {
        if(state[8]==with)
            (*v).push_back(8);
        if(state[17]==with)
            (*v).push_back(17);
        if(state[13]==with)
            (*v).push_back(13);
        break;
    }
case 13:
    {
        if(state[5]==with)
            (*v).push_back(5);
        if(state[20]==with)
            (*v).push_back(20);
        if(state[12]==with)
            (*v).push_back(12);
        if(state[14]==with)
            (*v).push_back(14);
        break;
    }
case 14:
    {
        if(state[2]==with)
            (*v).push_back(2);
        if(state[23]==with)
            (*v).push_back(23);
        if(state[13]==with)
            (*v).push_back(13);
        break;
    }
case 15:
    {
        if(state[16]==with)
            (*v).push_back(16);
        if(state[11]==with)
            (*v).push_back(11);
        break;
    }
case 16:
    {
        if(state[19]==with)
            (*v).push_back(19);
        if(state[15]==with)
            (*v).push_back(15);
        if(state[17]==with)
            (*v).push_back(17);
        break;
    }
case 17:
    {
        if(state[12]==with)
            (*v).push_back(12);
        if(state[16]==with)
            (*v).push_back(16);
        break;
    }
case 18:
    {
        if(state[19]==with)
            (*v).push_back(19);
        if(state[10]==with)
            (*v).push_back(10);
        break;
    }
case 19:
    {
        if(state[16]==with)
            (*v).push_back(16);
        if(state[22]==with)
            (*v).push_back(22);
        if(state[18]==with)
            (*v).push_back(18);
        if(state[20]==with)
            (*v).push_back(20);
        break;
    }
case 20:
    {
        if(state[19]==with)
            (*v).push_back(19);
        if(state[13]==with)
            (*v).push_back(13);
        break;
    }
case 21:
    {
        if(state[9]==with)
            (*v).push_back(9);
        if(state[22]==with)
            (*v).push_back(22);
        break;
    }
case 22:
    {
        if(state[21]==with)
            (*v).push_back(21);
        if(state[23]==with)
            (*v).push_back(23);
        if(state[19]==with)
            (*v).push_back(19);
        break;
    }
case 23:
    {
        if(state[22]==with)
            (*v).push_back(22);
        if(state[14]==with)
            (*v).push_back(14);
        break;
    }
    }
}

int Move::alphabeta1(int state[24],int depth,int ismax,int in,int alpha, int beta)
{
    Board table(state);

    if(depth==1)
    {
        if(table.checkMill(in) == 2)
            return 2000;
        if(table.checkMill(in) == 1)
            return 1000;
    }

    if(depth!=0)
    {
        if(table.checkMill(in) == 2)
            return 400/depth;
    }
    if(depth==finaldepth)
    {
        return (100*heuristique(-1,table,0)-50*heuristique(1,table,0));
    }

    int save[24];
    int scores[24];
    for(int i=0;i<24;i++)
    {
        save[i]=table.boardArea[i];
        scores[i]=-9999;
    }
    if(ismax==1)
    {
        int bestValue = +10000000; // PLUS INFINI
        vector<int> fils;
        for(int i=0;i<24;i++)
        {
            if(table.boardArea[i]==0)
            {
                table.boardArea[i]=1;

                if(table.checkMill(i) == 1)
                for(int i=0;i<24;i++)
                {
                    if(table.boardArea[i]==0&& table.checkMill(i) == 2)
                    {
                        vector<int> v;
                        voisin(i,&v,table.boardArea,-1);
                         vector<int>::iterator it;
                            for (it = v.begin(); it != v.end(); it++)
                            {
                               table.boardArea[*it]=0;
                            }
                        break;
                    }
                }
                int son=alphabeta1(table.boardArea,depth+1,-1,i,alpha,beta);
                fils.push_back(son);
                table.boardArea[i]=0;
                scores[i]=son;
                nbr_noeuds++;

                bestValue = min( bestValue, son);
                    beta = min( beta, bestValue);
                    if (beta<alpha)
                        break;
            }
        }
        for(int j=0;j<24;j++)
        {
            if(scores[j]==*min_element(fils.begin(),fils.end())) {
                if(depth==0)
                    {
                    cout<<"ma value : "<<scores[j];
                    return j;
                    }
            }
            else  {
                return scores[j];
            }
        }
    }

    else if(ismax==-1)
    {
        int bestValue = -10000000; // MOINS INFINI
        vector <int> fils;
        for(int i=0;i<24;i++)
        {
            if(table.boardArea[i]==0)
            {
                table.boardArea[i]=-1;
                if(table.checkMill(i) == 2)
                for(int i=0;i<24;i++)
                {
                    if(table.boardArea[i]==0&&table.checkMill(i) == 1)
                    {
                        vector<int> v;
                        voisin(i,&v,table.boardArea,1);
                         vector<int>::iterator it;
                            for (it = v.begin(); it != v.end(); it++)
                            {
                               table.boardArea[*it]=0;
                            }
                        break;
                    }
                }
                int son=alphabeta1(table.boardArea,depth+1,1,i,alpha,beta);
                fils.push_back(son);
                table.boardArea[i]=0;
                scores[i]=son;
                nbr_noeuds++;


                bestValue = max( bestValue, son);
                    alpha = max( alpha, bestValue);
                    if (beta<alpha)
                        break;
            }
        }
        for(int j=0;j<24;j++)
        {
            if(scores[j]==*max_element(fils.begin(),fils.end()))
                if(depth==0)
                {
                    cout<<"ma value : "<<scores[j];
                    return j;
                }
            else {
                return scores[j];
            }
        }
    }
}

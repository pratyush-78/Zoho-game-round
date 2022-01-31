#include <bits/stdc++.h>
using namespace std;

int mat[20][20];
int R, C;

int A=0, B=0;
int prevA=0, prevB=0;
int score = 0, total;

string name[400][400];
bool edge[400][400];

void printmat()
{
    int k=1, l=1;
    for(int i=0; i<R; i++)
    {
        for(int j=0; j<C; j++)
        {
            cout<<mat[i][j]<<" ";
            // check for edge
            if(j<C-1 && edge[k][k+1]==1)
                cout<<"-- ";
            else
                cout<<"   ";
            k++;
        }
        cout<<"\n";
        for(int j=0; j<C; j++)
        {
            
        if(i<R-1 && edge[l][l+C])
        {
            cout<<"| "<<" "<<name[i][j]<<" ";
        }
        else
            cout<<"  "<<name[i][j]<<"  ";
        l++;
        }
        cout<<endl;
        
    }
}

void checkscore(int player)
{
    int prev = score;
    int curr=0;
    for(int i=0; i<R-1; i++)
    {
        for(int j=0; j<C-1; j++)
        {
            int init = mat[i][j];
            if(edge[init][init+1] && edge[init][init+C] && edge[init+1][init+C+1] && edge[init+C][init+C+1])
            {
                curr++;
                if(name[i][j] == " ")
                {
                    if(player==0)
                        name[i][j] = "A";
                    else
                        name[i][j] = "B";
                }
            }
        }
    }
    
    if(curr>prev)
    {
        if(player==0)
            A+= (curr-prev);
        else
            B +=(curr-prev);
    }
    score = curr;
}

bool check(int from, int to)
{
    int x,y;
    int dx[] = {0,1,0,-1};
    int dy[] = {1,0,-1,0};

    for(int i=0; i<R; i++)
    {
        for(int j=0; j<C; j++)
        {
            if(mat[i][j]==from)
            {
                x=i;
                y=j;
            }
        }
    }

    for(int i=0; i<4; i++)
    {
        int a=x+dx[i], b=y+dy[i];
        if(a>=0 && b>=0 && a<R && b<C)
        {
            if(mat[a][b]==to)
            return 1;
        }
    }
    return 0;
}

int main()
{
    memset(edge, 0, sizeof edge);
    cout<<"enter r & c";
    cin>>R>>C;
    cout<<"initializing a matrix of : "<<R<<" x "<<C<<endl;
    
    // make mat as 1 2 3
    //             4 5 6 
    
    int k=1;
    for(int i=0; i<R; i++)
        for(int j=0; j<C; j++)
            mat[i][j] = k++;

    for(int i=0; i<R-1; i++)
        for(int j=0; j<C; j++)
            name[i][j] = " ";
            
    int turn=0;         // 0->A , 1->B
    int from, to;
    total = (R-1)*(C-1);
    while(1)
    {
                if(A>prevA || B>prevB || A+B==total)
        {
            if(A+B==total)
            {
                if(A>B)
                    cout<<"A won";
                else if(B>A)
                    cout<<"B won";
                else
                    cout<<"Tie";
                cout<<endl;
                return 0;
            } 
            
            prevA=A;
            prevB=B;
        }
        printmat();
        cout<<"Enter the edge for player : "<<(turn==0 ? "A: ": "B: ");
        cin>>from>>to;
        
        if(edge[from][to])
        {
            cout<<"already present, enter again: "<<endl;;
            continue;
        }
        if(!check(from, to))
        {
            cout<<"No path from "<<from<<" to "<<to<<". enter again"<<endl;;
            continue;
        }
        edge[from][to] = 1;
        edge[to][from] = 1;
        
        checkscore(turn);
        
        cout<<"current score : A : "<<A<<" B: "<<B<<endl;

        if(A>prevA || B>prevB || A+B==total)
        {
            // if(A+B==total)
            // {
            //     if(A>B)
            //         cout<<"A won";
            //     else if(B>A)
            //         cout<<"B won";
            //     else
            //         cout<<"Tie";
            //     cout<<endl;
            // } 
            
            prevA=A;
            prevB=B;
            continue;
        }
        
        turn = !turn;
    }

    return 0;
}

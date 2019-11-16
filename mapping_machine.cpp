#include<iostream>
#include<iomanip>
#include<fstream>
#define inf 100
using namespace std;
class position{
    friend class map;
    private:
        char val;//'0'dust   '1'wall   'C'cleaned
        int dist;//dist from R to every position
        int row;//row=r
        int col;//col=c
        int dist_s;//dist from selected node to every position
};
class map{
    private:
        position **arr;
        int rows;
        int cols;
        int cur_B;
        int max_B;
        position *R;//recharge 
        position *C;//cleaner
        bool found_path;//if find the shortest from u to v set true else keep searching
        position *keep_path;//keep the shortest path from u to v
    public:
        map(){
            //intitialization
            ofstream fo;
            ifstream fh("floor.data");
            fo.open;
            fh>>rows>>cols>>max_B;
            cur_B=max_B;
            arr=new position*[rows];
            for(int r=0;r<rows;r++){
                arr[r]=new position[cols];
            }
            for(int r=0;r<rows;r++){
                for(int c=0;c<cols;c++){
                    fh>>arr[r][c].val;
                    arr[r][c].row=r;
                    arr[r][c].col=c;
                    arr[r][c].dist=inf;
                    if(arr[r][c].val=='R'){
                        R=&arr[r][c];
                        C=R;
                    }
                }
            }

            fh.close();
            fo.close();
            set_dist(R,0);

            //bad algorithm 
            //go through every position that have not be cleared.
            fo<<C->row<<" "<<C->col<<" Battery:"<<cur_B<<endl;
            for(int r=0;r<rows;r++){
                for(int c=0;c<cols;c++){
                    if(arr[r][c].val=='0'){
                        print(C->row,C->col);
                        if(arr[r][c].dist>cur_B-arr[r][c].dist_s){
                            go(*R);
                            print(C->row,C->col);
                        }
                        go(arr[r][c]);
                    }
                }
            }
            print(C->row,C->col);
            go(*R);

        }
        

        void set_dist(position *p,int d){
            if(p->val=='1'){
                return;
            }
            else{
                if(d<p->dist){
                    p->dist=d;
                    if(p->row+1<rows)
                        set_dist(&arr[p->row+1][p->col],d+1);
                    if(p->col+1<cols)
                        set_dist(&arr[p->row][p->col+1],d+1);
                    if(p->row-1>=0)
                        set_dist(&arr[p->row-1][p->col],d+1);
                    if(p->col-1>=0)
                        set_dist(&arr[p->row][p->col-1],d+1);
                }
            }
        }
        
        void print(int r,int c){
            for(int r=0;r<rows;r++){
                for(int c=0;c<cols;c++){
                    arr[r][c].dist_s=inf;
                }
            }
            set_dist_s(&arr[r][c],0);
        }
        void set_dist_s(position *p,int d){
            if(p->val=='1'){
                return;
            }
            else{
                if(d<p->dist_s){
                    p->dist_s=d;
                    if(p->row+1<rows)
                        set_dist_s(&arr[p->row+1][p->col],d+1);
                    if(p->col+1<cols)
                        set_dist_s(&arr[p->row][p->col+1],d+1);
                    if(p->row-1>=0)
                        set_dist_s(&arr[p->row-1][p->col],d+1);
                    if(p->col-1>=0)
                        set_dist_s(&arr[p->row][p->col-1],d+1);
                }
            }
        }
        //最短路徑
        void go(position v){
            found_path=false;
            keep_path=new position[v.dist_s];
            go_allpath(*C,v);
            if(C->row==R->row&&C->col==R->col){
                cur_B=max_B;
            }
        }
        void go_allpath(position u,position v){
            if(u.row==v.row&&u.col==v.col){
                found_path=true;
                keep_path[u.dist_s].row=v.row;
                keep_path[u.dist_s].col=u.col;
                C=&arr[v.row][v.col];
                for(int i=1;i<=v.dist_s;i++){
                    arr[keep_path[i].row][keep_path[i].col].val='C';
                    cur_B--;
                    fo<<keep_path[i].row<<" "<<keep_path[i].col<<" Battery:"<<cur_B<<endl;
                }
                return;
            }
            else{
                if(u.row+1<rows&&u.dist_s+1==arr[u.row+1][u.col].dist_s&&found_path==false){
                    keep_path[u.dist_s].row=u.row;
                    keep_path[u.dist_s].col=u.col;
                    go_allpath(arr[u.row+1][u.col],v);
                }
                if(u.col+1<cols&&u.dist_s+1==arr[u.row][u.col+1].dist_s&&found_path==false){
                    keep_path[u.dist_s].row=u.row;
                    keep_path[u.dist_s].col=u.col;
                    go_allpath(arr[u.row][u.col+1],v);
                }
                if(u.row-1<rows&&u.dist_s+1==arr[u.row-1][u.col].dist_s&&found_path==false){
                    keep_path[u.dist_s].row=u.row;
                    keep_path[u.dist_s].col=u.col;
                    go_allpath(arr[u.row-1][u.col],v);
                }
                if(u.row-1<cols&&u.dist_s+1==arr[u.row][u.col-1].dist_s&&found_path==false){
                    keep_path[u.dist_s].row=u.row;
                    keep_path[u.dist_s].col=u.col;
                    go_allpath(arr[u.row][u.col-1],v);
                }
            }
        }
        //外掛程式
        void print_map(){
            for(int r=0;r<rows;r++){
                for(int c=0;c<cols;c++){
                    fo<<arr[r][c].val;
                }
                fo<<'\n';
            }
        }

        void print_dist(){
            for(int r=0;r<rows;r++){
                for(int c=0;c<cols;c++){
                    fo<<setw(5)<<arr[r][c].dist;
                }
                fo<<'\n';
            }
        }

        void print_dist_s(){
            for(int r=0;r<rows;r++){
                for(int c=0;c<cols;c++){
                    fo<<setw(5)<<arr[r][c].dist_s;
                }
                fo<<'\n';
            }
        }

};

int main(){
    map m;
}
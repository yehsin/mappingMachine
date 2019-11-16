#include<iostream>
<<<<<<< HEAD
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
=======
#include<fstream>
using namespace std;

//if cost is same, go straight or 
//not clean node is higher prioroty
//Set a target to run(using stack)
//如果cost一樣(都沒clean過或都clean過)預設先走直線再走橫線
//去時,以homePower最大為target
//如果到target電力還很多,找下一個target(跟自己最近的)

class Traveltree;
class treenode;
class map;
class machine;

class treenode{
    friend class map;
    friend class Traveltree;
    private:
        int cost; // the step that the node distance from R
        int type;
        int ID = 0;
        bool cleaned;
        treenode *up,*down,*left,*right;
    public:
    treenode();
    treenode(int type):type(type),cleaned(0){
        if(type);
        else{
            cleaned =1;
            cost = -1;
        } 

    }
    ~treenode();
    treenode * getup(){
        return this->up;
    }
    treenode * getdown(){
        return this->down;
    }
    treenode * getleft(){
        return this->left;
    }
    treenode * getright(){
        return this->right;
    }
    int gettype(){
        return this->type;
    }
    int getcost(){
        return this->cost;
    }
    int getID(){
        return this->ID;
    }
    void setID(int n){
        this->ID = n;
    }
    void setcost(int n){
        this->cost = n;
    }
    void setcleaned(int n){
        cleaned = n;
        //cost = 3;
    }
    bool getclean(){
        return this->cleaned;
    }
};

/*class Traveltree{
    private :
        treenode *self;
        Traveltree *Root,*last,*up_child,*down_child,*left_child,*right_child;
    public:
        static int id;
        Traveltree(treenode *s){
            id++;
            Root->self = s;
            Root->self->setID(id);
            last = Root;
        }
        void insertTraveltree(treenode *a){
            if(a->getright()->getID()>a->ID){
                a->setID(a->getID);
                insertTraveltree(a->right);               
            }
            if(a->getup()->getID()>a->ID){
                a->setID(a->ID);
                insertTraveltree(a->up);
            } 
            if(a->getleft()->getID()>a->ID){
                a->setID(id);
                insertTraveltree(a->left);
            }
            if(a->getdown()->getID()>a->ID) {
                a->setID(a->ID+1);
                insertTraveltree(a->down);
            }
            else if(a == NULL || a->type ==1){
                return;
            }
        }
        void findNextTree(treenode *z){ 
            treenode *tmp = z;
            if(z->down->getID() != z->getID()+1){
                if(z->down->getID() != z->getID()){
                    tmp = tmp->down;
                }
                else{
                    tmp = tmp -> left;
                }
            }
        }
};*/

class map{
    friend class machine;
    private:
        treenode ***floor;
        treenode *Root;
        int *notCleanBuf;
        int width,heigh;
    public:
        map(int n,int m,char *arr){
            notCleanBuf = new int(n*m);
            width = n;
            heigh = m;
            //build_floor(arr);
            floor = new treenode**[n];
            for (int i=0;i<width;i++){
                floor[i] = new treenode*[heigh];
                for(int j = 0;j<heigh;j++){
                    notCleanBuf[i*width+j] = 1;
                    int type = *(arr+i*width+j)-'0';
                    floor[i][j] = new treenode(type);
                    if(type == 'R'-'0'){
                        Root = floor[i][j];
                        Root->type = 'R';
                    }
                }
            }   
            build_tree((treenode*) *floor);
        }
        ~map(){
            for(int i=0;i<width;i++){
                for(int j=0;j<heigh;j++){
                    delete[] floor[i][j];
                }
            }
            delete[] floor;
            delete[] notCleanBuf;
        }
        void build_tree(treenode *a){
            for(int i = 1;i<width-1;i++){
                for(int j=1;j<heigh-1;j++){
                    if(floor[i-1][j]->type!=1) floor[i][j]->up = floor[i-1][j];
                    else floor[i][j]->up = NULL;
                    if(floor[i+1][j]->type !=1) floor[i][j]->down = floor[i+1][j];
                    else floor[i][j]->down = NULL;
                    if(floor[i][j+1]->type !=1) floor[i][j]->right = floor [i][j+1];
                    else floor[i][j]->right = NULL;
                    if(floor[i][j-1]->type !=1) floor[i][j]->left = floor[i][j-1];
                    else floor[i][j]->left = NULL;
                }
            }
            BSF(&Root,0);
        }
        void BSF(treenode ** a,int cost){
            if((*a)->getcost()>cost){
                (*a)->setcost(cost);
            }
            if((*a)->getup()){
                treenode *up = (*a)->getup();
                BSF(&up,cost+1);
            } 
            if((*a)->getright()){
                treenode *right = (*a)->getright();
                BSF(&right,cost+1);
            } 
            if((*a)->getdown()){
                treenode *down = (*a)->getdown();
                BSF(&down,cost+1);
            } 
            if((*a)->getleft()){
                treenode *left = (*a)->getleft();
                BSF(&left,cost+1);
            } 
        }
        /*void buildTravelTree(treenode **a){
            int i = 0;
            int j = 0;
            while(floor[i][j]->type){
                i++;
                if(i == heigh-1){
                    i = 0;
                    j++;
                }
            }
            treenode *tmp = floor[i][j];
            while(tmp){
                
            }
        }*/
        int getwidth(){
            return width;
        }

        int getheigh(){
            return heigh;
        }
        

        //void clean(){};
};

class machine{
    private:
        friend class treeNode;
        int powerFull;
        int power;
        int buf[1000000];
        treenode *cleaner;
    public:
        machine(int n):powerFull(n), power(n){}
        ~machine();
        
        void clean(map *floor){
            int heigh = floor->getheigh();
            int row=0;
            int columns =0;
            //Traveltree maptree(floor->floor[0][0]);
            treenode* tmp = floor->Root;
            cleaner = tmp;
            int Row = tmp->getID();
            /*while(floor->floor[row][columns]->gettype() == 1){
                columns++;
                if(columns == floor->getwidth()-1){
                    columns =0;
                    row++;
                }
                tmp = floor->floor[row][columns];
            }//找到最上面的點了*/
            while(Row >= 0){
                cleanRow(&tmp,Row);
                Row--;
                
            }
            backToRoot(&tmp);
            while(Row!=heigh){
                
                Row++;
                cleanRow(&tmp,Row);
                
            }
            backToRoot(&tmp);
        }

        void isRefresh(treenode*tmp){
            if(tmp->getcost() == power){
                int step = backToRoot(&tmp);
                backToNode(&tmp,buf,step);
            }
        }

        void cleanRow(treenode **tmp,int Row){
            int right=0;
            if((*tmp)->getID()!= Row){ //貼著牆壁走
                if(Row>(*tmp)->getID()){
                    while((*tmp)->getup()->getID()!=Row || (*tmp)->getup()==NULL){
                        while((*tmp)->getdown()->getID() == (*tmp)->getID() && (*tmp)->getdown()){
                            (*tmp) = (*tmp)->getdown();
                            power--;
                            isRefresh(*tmp);
                        }
                        if((*tmp)->getleft()!=NULL){
                            *tmp = (*tmp)->getleft();
                            power--;
                            isRefresh(*tmp);
                        }
                    }

                }
                else{
                    while((*tmp)->getdown()->getID()!=Row || (*tmp)->getdown() == NULL){
                        while((*tmp)->getdown()->getID() == (*tmp)->getID() && (*tmp)->getdown()){
                            (*tmp) = (*tmp)->getdown();
                            power--;
                            isRefresh(*tmp);
                        }
                        if((*tmp)->getdown()==NULL){
                            if((*tmp)->getleft()!=NULL){
                                *tmp = (*tmp)->getleft();
                                power--;
                                isRefresh(*tmp);
                            }
                        }
                    }
                }
            }
            if((*tmp)->getright()->getID() == (*tmp)->getID()) right = 1;
            if((*tmp)->getup()->getID()==(*tmp)->getID()){
                treenode * up = (*tmp)->getup();
                power--;
                isRefresh(*tmp);
                cleanRow(&up,Row);
            }
            if((*tmp)->getup()->getID() == (*tmp)->getID()){
                treenode * down = (*tmp)->getdown();
                power--;
                isRefresh(*tmp);
                cleanRow(&down,Row);
            }
            while((*tmp)->getleft() && (*tmp)->getleft()->getID() == (*tmp)->getID()){
                (*tmp)->setcleaned(1);
                power--;
                isRefresh(*tmp);
                *tmp = (*tmp)->getleft();
            }
            if(right ==1){
                while(*tmp){
                    (*tmp)->setcleaned(1);
                    power--;
                    isRefresh(*tmp);
                    *tmp = (*tmp)->getright();
                }
            }
            
        }

        void backToNode(treenode ** tmp,int *buf,int count){
            while(count){
                count--;
                power--;
                if(buf[count] == 1){
                    *tmp = (*tmp)->getup();
                    buf[count]=0;
                }
                else if(buf[count]==2){
                    *tmp = (*tmp)->getdown();
                    buf[count]=0;
                }
                else if(buf[count] == 3){
                    *tmp = (*tmp)->getleft();
                    buf[count]=0;
                }
                else{
                    *tmp = (*tmp)->getright();
                    buf[count]=0;
                }
            }
        }

        int backToRoot(treenode **tmp){
            static int count;
            treenode *greatest = NULL;
            treenode *up = (*tmp)->getup();
            treenode *down = (*tmp)->getdown();
            treenode *left = (*tmp)->getleft();
            treenode* right = (*tmp)->getright();
            while(!greatest){
                if(up) {
                    greatest = up;
                }
                else if(down) {
                    greatest = down;
                }
                else if(left) {
                    greatest = left;
                }
                else if(right) {
                    greatest = right;
                }
            }
            if(up){
                if(up->getcost()<= greatest->getcost() && up->getclean() == 0){
                    greatest = up;
                    buf[count] = 1;
                }
            }
            if(down){
                if(down->getcost()<=greatest->getcost() && down->getclean() ==0){
                    greatest = down;
                    buf[count] = 2;
                }
            }
            if(left){
                if(left->getcost()<=greatest->getcost() && left->getclean() ==0){
                    greatest = left;
                    buf[count] = 3;
                }
            }
            if(right){
                if(right->getcost()<=greatest->getcost() && left->getclean()==0){
                    greatest = right;
                    buf[count] = 4;
                }
            }
            
            *tmp = greatest;
            greatest->setcleaned(1);
            power--;
            if(*tmp == cleaner){
                power = powerFull;
                return count;
            }
            count++;
            backToRoot(tmp);
        }

        
        bool iswall(treenode *a){
            if(a->gettype() == 1){
                return 1;
            }
            else if(a->gettype()==0) {
                return 0;
>>>>>>> master
            }
        }

};

int main(){
<<<<<<< HEAD
    map m;
=======
    //ifstream ifile("floor.data",ios::in);
    int width,heigh,power;
    char input[80];
    
    int count = 0;
    cin>>width>>heigh>>power;
    int h = heigh;
    //cout<<heigh;
    int matrix[heigh][width];
    while(h){
        h--;
        //fgets(input,sizeof(input),stdin);
        for(int i=0;i<width;i++){

            cin>>matrix[count][i];
        }
        //cout<<input;
        count++;
    }
    for(int i=0;i<width;i++){
        for(int j = 0;j<heigh;j++){
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
    
    
    map *mapping = new map(width,heigh,(char*)matrix);
    //machine *Super_Hero = new machine(power);
    //Super_Hero->clean(mapping);
>>>>>>> master
}
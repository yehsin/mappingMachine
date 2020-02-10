#include<iostream>
#include<fstream>
#include<iomanip>
#include<memory.h>
#include<time.h>
using namespace std;
clock_t startc,endc;
//if cost is same, go straight or 
//not clean node is higher prioroty
//Set a target to run(using stack)
//如果cost一樣(都沒clean過或都clean過)預設先走直線再走橫線
//去時,以homePower最大為target
//如果到target電力還很多,找下一個target(跟自己最近的)
fstream ifile("floor.data",ios::in);
ofstream outfile ("final.path");
class Traveltree;
class treenode;
class map;
class machine;
int stepCount = 0;

class queue{
    private:
        friend class treenode;
        queue *next,*cur,*Root;
        treenode *content;
    public:
        queue(treenode *a){
            this->content = a;
            this->next = NULL;
            cur = Root = this;
        }
        void push(treenode* a){
            queue *newN = new queue(a);
            cur->next = newN;
            cur = newN;
        }
        ~queue(){
            while(Root){
                queue* tmp = Root;
                Root = Root->next;
                free(tmp);
                tmp = NULL;
            }
        }
        queue* getnext(){
            return this->next;
        }
        queue* getRoot(){
            return Root;
        }
        treenode* getcontent(){
            return this->content;
        }
};

class stack{
    private:
        friend class treenode;
        stack *next,*prev,*cur;
        treenode *content;
        int direction;
    public:
        stack(treenode *a){
            this->content = a;
            this->next = NULL;
            this->prev = NULL;
            cur = this;
        }
        void insert(treenode *a,int dir){
            stack *newN = new stack(a);
            newN ->content = a;
            newN->direction = dir;
            cur->next = newN;
            newN->prev = cur;
            cur = newN;
        }
        void del(){
            stack *tmp = cur;
            cur = cur->prev;
            free(tmp);
        }
        stack* getcur(){
            return cur;
        }
        treenode* gettreenode(){
            return cur->content;
        }
        int getdir(){
            return direction;
        }
    
};

class treenode{
    friend class map;
    friend class Traveltree;
    private:
        int cost = 10000; // the step that the node distance from R
        int type;
        int ID = -1;
        int row,column;
        bool cleaned = 0;
        treenode *up,*down,*left,*right;
    public:
    treenode(){
        up = down = left = right = NULL;
    };
    /*treenode(int type):type(type),cleaned(0){
        if(type);
        else{
            cleaned =1;
            cost = -1;
        } 

    }*/
    ~treenode(){};
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
    int getrow(){
        return this->row;
    }
    int getcol(){
        return this->column;
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
        cleaned = 1;
        //cost = 3;
    }
    bool getclean(){
        return this->cleaned;
    }
};


static int id;
class map{
    friend class machine;
    private:
        treenode **floor;
        treenode *Root;
        int *notCleanBuf;
        int width,heigh;
    public:
         
        map(int n,int m){
            
            notCleanBuf = new int[m*n];
            width = n;
            heigh = m;

            char matrix[heigh][width];
            for(int i=0;i<heigh;i++){
                for(int j=0;j<width;j++){ 
                    ifile>>matrix[i][j];
                }
            }
            
            /*for(int i=0;i<heigh;i++){
                for(int j=0;j<width;j++){ 
                    cout<<matrix[i][j]<<" ";
                }
                cout<<endl;
            }*/

            floor = new treenode*[heigh];
            for (int i=0;i<heigh;i++){
                floor[i]=new treenode[width];
                for(int j = 0;j<width;j++){
                    notCleanBuf[i*heigh+j] = 1;
                    int type = matrix[i][j]-'0';
                    floor[i][j].type=type;
                    if(floor[i][j].type == 1){
                        floor[i][j].cleaned = 1;
                        floor[i][j].cost = -1;
                    }
                    floor[i][j].row = i;
                    floor[i][j].column = j;
                    if(type == 'R'-'0'){ 
                        Root = &(floor[i][j]);
                        Root->type = 'R'; 
                        Root->cost = 0 ; 
                    }
                }
            }
            //cout<<endl;
            /*for(int i=0;i<heigh;i++){
                for(int j=0;j<width;j++){
                    cout<<floor[i][j].type<<" ";
                }
                cout<<endl;
            }*/
            build_tree(*floor);
        }
        ~map(){
            for(int i=0;i<width;i++){
                delete[] floor[i];
            }
            delete[] floor;
            delete[] notCleanBuf;
        }
        void build_tree(treenode *a){
            for(int i=1;i<heigh-1;i++){

                for(int j=1;j<width-1;j++){
                    if(floor[i-1][j].type!=1) {
                        floor[i][j].up = &(floor[i-1][j]);
                        if(floor[i][j].up == Root){
                            Root->down = &(floor[i][j]);
                        }
                    }
                    else {
                        floor[i][j].up = NULL;
                    }
                    if(floor[i+1][j].type !=1) {
                        floor[i][j].down = &(floor[i+1][j]);
                        if(floor[i][j].down == Root){
                            Root->up = &(floor[i][j]);
                        }
                    }
                    else {
                        floor[i][j].down = NULL;
                    }
                    if(floor[i][j+1].type !=1) {
                        floor[i][j].right = &(floor[i][j+1]);
                        if(floor[i][j].right == Root){
                            Root->left = &(floor[i][j]);
                        }
                    }
                    else {
                        floor[i][j].right = NULL;
                    }
                    if(floor[i][j-1].type !=1) {
                        floor[i][j].left = &(floor[i][j-1]);
                        if(floor[i][j].left == Root){
                            Root->right = &(floor[i][j]);
                        }
                    }
                    else {
                        floor[i][j].left = NULL;
                    }
                }
            }
            BSF(&Root,0);
            buildTravelTree();
            for(int i=0;i<heigh;i++){
                for(int j = 0;j<width;j++){
                    cout<<floor[i][j].getID()<<setw(4);
                }
                cout<<endl;
            }
        }
        void BSF(treenode ** a,int cost){
            (*a)->setcost(cost);
            if((*a)->getup()!=NULL && (*a)->up->type!=1 && (*a)->up->cost>cost+1){
                treenode *up = (*a)->getup();
                BSF(&up,cost+1);
    
            }
            if((*a)->getright()!=NULL && (*a)->right->type!=1 && (*a)->right->cost>cost+1){
                treenode *right = (*a)->getright();
                BSF(&right,cost+1);
                
            } 
            if((*a)->getdown()!=NULL && (*a)->down->type!=1 && (*a)->down->cost>cost+1){
                treenode *down = (*a)->getdown();
                BSF(&down,cost+1);
            } 
            if((*a)->getleft()!=NULL && (*a)->left->type!=1 && (*a)->left->cost>cost+1){
                treenode *left = (*a)->getleft();
                BSF(&left,cost+1); 
            }
            
            return;
            
        }
        
        void buildTravelTree(){
            int R = 0;
            int j = 0;
            while(R<heigh){
                while(floor[R][j].type ==1){
                    j++;
                    if(j == width){
                        R++;
                        j = 0;
                        id++;
                        
                    }
                    if(R == heigh) break;
                }
                if(R == heigh) break;
                buildLevel(&floor[R][j]);
                R++;
                j=0;
                id++;

            }
            R = 0;
            j = 0;
            id = 0;
            while(R<heigh){  //再檢查一次把沒被設ID的設值
                while(floor[R][j].type ==1){
                    j++;
                    if(j == width){
                        R++;
                        j = 0;
                        id++;   
                    }
                    if(R == heigh) break;
                }
                if(R == heigh) break;
                buildLevelCheck(&floor[R][j]);
                R++;
                j=0;
                id++;

            }
        }
        void buildLevel(treenode *tmp){
            tmp->ID = id;
            if(tmp->left){
                treenode *left_tmp = tmp->left;
                while(left_tmp){
                    left_tmp->ID = id;
                    if(left_tmp->up){
                        if(left_tmp->up->ID < left_tmp->ID);
                        else buildLevel(left_tmp->up);
                    }
                    left_tmp = left_tmp->left;
                }
            }
            if(tmp->right){
                treenode *right_tmp = tmp->right;
                while(right_tmp){
                    right_tmp->ID = id;
                    if(right_tmp->up){
                        if(right_tmp->up->ID < right_tmp->ID);
                        else buildLevel(right_tmp->up);
                    }
                    right_tmp = right_tmp->right;
                }
            }
            if(tmp->up){
                if(tmp->up->ID < tmp->ID);
                else{
                    buildLevel(tmp->up);
                }
            }
        }

        void buildLevelCheck(treenode *tmp){
            tmp->ID = id;
            if(tmp->left){
                treenode *left_tmp = tmp->left;
                while(left_tmp){
                    left_tmp->ID = id;
                    if(left_tmp->up){
                        if(left_tmp->up->ID!=-1);
                        else buildLevelCheck(left_tmp->up);
                    }
                    if(left_tmp->down){
                        if(left_tmp->down->ID!=-1);
                        else buildLevelCheck(left_tmp->down);
                    }
                    left_tmp = left_tmp->left;
                }
            }
            if(tmp->right){
                treenode *right_tmp = tmp->right;
                while(right_tmp){
                    right_tmp->ID = id;
                    if(right_tmp->up){
                        if(right_tmp->up->ID!=-1);
                        else buildLevelCheck(right_tmp->up);
                        
                    }
                    if(right_tmp->down){
                        if(right_tmp->down->ID!=-1);
                        else buildLevelCheck(right_tmp->down);
                    }
                    right_tmp = right_tmp->right;
                }
            }
            if(tmp->up){
                if(tmp->up->ID!=-1);
                else{
                    buildLevelCheck(tmp->up);
                }
            }
            if(tmp->down){
                if(tmp->down->ID != -1);
                else{
                    buildLevelCheck(tmp->down);
                }
            }
        }
                

        int getwidth(){
            return width;
        }

        int getheigh(){
            return heigh;
        }
};

class machine{
    private:
        friend class treeNode;
        queue *output;
        int powerFull;
        int power;
        int buf[1000000];
        treenode *cleaner;
    public:
        machine(int n):powerFull(n), power(n){}
        ~machine();
        
        void clean(map *floor){
            
            int heigh = floor->getheigh();
            int width= floor->getwidth();

            treenode* tmp = floor->Root;
            tmp->setcleaned(1);
            cleaner = tmp;
            output = new queue(cleaner);
            int Row = tmp->getID();
            cleanRow(&tmp,Row,floor);

            int home = backToRoot(&tmp); // BACK TO R

            if(tmp->getcost() != 0){ //when it not at R
                home =backToRoot(&tmp);
            }

            outfile<<stepCount<<endl;
            queue* print = output->getRoot(); //To store the road which it have traveled
            while(print){
                outfile << print->getcontent()->getrow() <<" "<< print->getcontent()->getcol()<<endl;
                print = print->getnext();
            }
            /*for(int i=0;i<heigh;i++){
                for(int j=0;j<width;j++){
                    cout<<floor->floor[i][j].getclean();
                }
                cout<<endl;
            }*/
        }

        void isRefresh(treenode*tmp){
            //cout<<tmp->getrow()<<" "<<tmp->getcol()<<" "<<power<<" "<<tmp->getcost()<<endl;
            output->push(tmp);
            if(tmp->getcost() >= power){
                int step = backToRoot(&tmp);
                backToNode(&tmp,buf,step);
            }
        }

        void cleanRow(treenode **tmp,int Row,map *floor){
            treenode *cur = *tmp;
            //先走左邊再走右邊//最後要回到一開始的點
            //如果遇到往上或往下=>走然後遞迴
            //走完回來
            treenode *record = cur;//記錄這個點
            treenode *detect = record;

            stack *buf = new stack(NULL);
            if(cur->getleft() && cur->getleft()->getID() == Row ){ //左掃
                while(cur->getleft()){
                    cur = cur->getleft();
                    cur->setcleaned(1);
                    power--;
                    stepCount++;
                    if(cur == floor->Root){
                        power = powerFull;
                    }
                    isRefresh(cur);
                }
            }
            if(cur->getright() && cur->getright()->getID() == Row){ //右掃
                while(cur->getright()){
                    cur = cur->getright();
                    cur->setcleaned(1);
                    power--;
                    stepCount++;
                    if(cur == floor->Root){
                        power = powerFull;
                    }
                    isRefresh(cur);
                }
            }
            treenode *prev = cur;

            while(cur){
                if(cur->getup() && cur->getup()->getID() == Row && cur->getup()->getclean() == 0){
                    cur= cur->getup();
                    cur->setcleaned(1);
                    power--;
                    stepCount++;
                    isRefresh(cur);
                    cleanRow(&cur,Row,floor);
                    cur = cur->getdown();
                    power--;
                    stepCount++;
                    isRefresh(cur);
                }

                if(cur->getup() && cur->getup() ->getID() !=Row && cur->getup()->getclean() == 0){
                    buf->insert(cur,1);
                    
                }
                if(cur->getdown() && cur->getdown()->getID() == Row && cur->getdown()->getclean() == 0){
                    cur= cur->getdown();
                    cur->setcleaned(1);
                    power--;
                    stepCount++;
                    isRefresh(cur);
                    cleanRow(&cur,Row,floor);
                    cur = cur->getup();
                    power--;
                    stepCount++;
                    isRefresh(cur);
                }
                if(cur->getdown() && cur->getdown()->getID()!=Row && cur->getdown()->getclean() == 0){
                    buf->insert(cur,2);
                }
                prev = cur;
                cur = cur->getleft();
                if(cur){
                    power--;
                    stepCount++;
                    isRefresh(cur);
                }
                
            }
            cur = prev;
            while(buf->getcur()->gettreenode()!=NULL){
                while(cur != buf->getcur()->gettreenode()){
                    
                    if(buf->getcur()->gettreenode()->getcol()>cur->getcol()){
                        cur = cur->getright();
                        power--;
                        stepCount++;
                        isRefresh(cur);
                    }
                    else{
                        cur = cur->getleft();
                        power--;
                        stepCount++;
                        isRefresh(cur);
                    }
                    
                }
                
                if(buf->getcur()->getdir() == 1 && cur->getup()->getclean() == 0){
                    cur = cur->getup();
                    cur->setcleaned(1);
                    power--;
                    stepCount++;
                    isRefresh(cur);
                    cleanRow(&cur,cur->getID(),floor);
                    cur = cur->getdown();
                    power--;
                    stepCount++;
                    isRefresh(cur);
                    buf->del();
                }

                else if(buf->getcur()->getdir()==1 && cur->getup()->getclean() != 0){
                    buf->del();
                }

                else if(buf->getcur()->getdir()==2 && cur->getdown()->getclean() ==0){
                    cur = cur->getdown();
                    cur->setcleaned(1);
                    power--;
                    stepCount++;
                    isRefresh(cur);
                    cleanRow(&cur,cur->getID(),floor);
                    cur = cur->getup();
                    power--;
                    stepCount++;
                    isRefresh(cur);
                    buf->del();
                }
                else if(buf->getcur()->getdir()==2 && cur->getdown()->getclean() !=0){
                    buf->del();
                }
            }
            while(cur != record){
                if(record->getcol()>cur->getcol()){
                   cur = cur->getright();
                    power--;
                    stepCount++;
                    isRefresh(cur);
                }
                else{
                    cur = cur->getleft();
                    power--;
                    stepCount++;
                    isRefresh(cur);
                }
                
            }
            *tmp = cur;
            return;
        }

        /*int detectLeftAllClean(treenode*tmp){
            while(tmp){
                if(tmp->getclean() == 0) {
                    return 1;
                    break;
                }
                tmp = tmp->getleft();
            }
            return 0;
        }
        int detectRightAllClean(treenode*tmp){
            while(tmp){
                if(tmp->getclean() == 0) {
                    return 1;
                    break;
                }
                tmp = tmp->getright();
            }
            return 0;
        }*/
            

        void backToNode(treenode ** tmp,int *buf,int count){
            while(count>=0){
                power--;
                stepCount++;
                if(buf[count] == 1){
                    *tmp = (*tmp)->getdown();
                    output->push(*tmp);
                    //outfile<<(*tmp)->getrow()<<" "<<(*tmp)->getcol()<<endl;
                    //cout<<(*tmp)->getrow()<<" "<<(*tmp)->getcol()<<endl;
                    buf[count]=0;
                }
                else if(buf[count]==2){
                    *tmp = (*tmp)->getup();
                    output->push(*tmp);
                    //outfile<<(*tmp)->getrow()<<" "<<(*tmp)->getcol()<<endl;
                    //cout<<(*tmp)->getrow()<<" "<<(*tmp)->getcol()<<endl;
                    buf[count]=0;
                }
                else if(buf[count] == 3){
                    *tmp = (*tmp)->getright();
                    output->push(*tmp);
                    //outfile<<(*tmp)->getrow()<<" "<<(*tmp)->getcol()<<endl;
                    //cout<<(*tmp)->getrow()<<" "<<(*tmp)->getcol()<<endl;
                    buf[count]=0;
                }
                else{
                    *tmp = (*tmp)->getleft();
                    output->push(*tmp);
                    //outfile<<(*tmp)->getrow()<<" "<<(*tmp)->getcol()<<endl;
                    //cout<<(*tmp)->getrow()<<" "<<(*tmp)->getcol()<<endl;
                    buf[count]=0;
                }
                count--;
            }
            return;
        }

        int backToRoot(treenode **tmp){
            if((*tmp)->getcost() == 0) {
                power = powerFull;
                return 0;
            }
            static int count;
            treenode *greatest = NULL;
            treenode *up = (*tmp)->getup();
            treenode *down = (*tmp)->getdown();
            treenode *left = (*tmp)->getleft();
            treenode* right = (*tmp)->getright();

            while(!greatest){
                if((*tmp)->getup() && (*tmp)->getcost()>=up->getcost()) {
                    greatest = up;
                }
                else if((*tmp)->getdown() && (*tmp)->getcost()>=down->getcost()) {
                    greatest = down;
                }
                else if((*tmp)->getleft() && (*tmp)->getcost()>=left->getcost()) {
                    greatest = left;
                }
                else if((*tmp)->getright()&& (*tmp)->getcost()>=right->getcost()) {
                    greatest = right;
                }
            }
            if((*tmp)->getup()){
                
                if(up->getcost()<= greatest->getcost()){
                    if(up->getclean()==greatest->getclean());
                    else if(up->getclean() ==0 && greatest->getclean() ==1){
                        greatest = up;
                    }
                    
                }
            }
            if((*tmp)->getdown()){
                if(down->getcost()<=greatest->getcost()){
                    if(down->getclean()==greatest->getclean());
                    else if(down->getclean() ==0 && greatest->getclean() ==1){
                        greatest = down;
                    }
                }
            }
            if((*tmp)->getleft()){
                if(left->getcost()<=greatest->getcost()){
                    if(left->getclean()==greatest->getclean());
                    else if(left->getclean() ==0 && greatest->getclean() ==1){
                        greatest = left;
                    }
                }
            }
            if((*tmp)->getright()){
                if(right->getcost()<=greatest->getcost()){
                    if(right->getclean()==greatest->getclean());
                    else if(right->getclean() ==0 && greatest->getclean() ==1){
                        greatest = right;
                    }
                }
            }
            if(greatest == (*tmp)->getup()){
                buf[count] = 1;
            }
            else if(greatest == (*tmp)->getdown()){
                buf[count] = 2;
            }
            else if(greatest == (*tmp)->getleft()){
                buf[count] = 3;
            }
            else if(greatest == (*tmp)->getright()){
                buf[count] = 4;
            }
            *tmp = greatest;
            output->push(*tmp);
            //cout<<greatest->getrow()<<" "<<greatest->getcol()<<endl;
            //outfile<<greatest->getrow()<<" "<<greatest->getcol()<<endl;
            power--;
            stepCount++;
            if(*tmp == cleaner){
                power = powerFull;
                int ans = count;
                count = 0;
                return ans;
            }
            count++;
            return backToRoot(tmp);
        }
};

int main(){


    int width,heigh,power;
    char input[2000];
    
    int count = 0;
    ifile>>heigh>>width>>power;
    //cout<<heigh<<width<<power;
    int h = heigh;
    startc = clock();
    map *mapping = new map(width,heigh);
    machine *Super_Hero = new machine(power);
    Super_Hero->clean(mapping);
    cout<<stepCount<<endl;
    endc = clock();
    printf("%f",(double)(endc-startc)/CLOCKS_PER_SEC);
    ifile.close();
    outfile.close();
}
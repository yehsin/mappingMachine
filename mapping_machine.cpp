#include<iostream>
#include<fstream>
#include<iomanip>
#include<memory.h>
using namespace std;

//if cost is same, go straight or 
//not clean node is higher prioroty
//Set a target to run(using stack)
//如果cost一樣(都沒clean過或都clean過)預設先走直線再走橫線
//去時,以homePower最大為target
//如果到target電力還很多,找下一個target(跟自己最近的)
fstream ifile("floor.data",ios::in);
class Traveltree;
class treenode;
class map;
class machine;
int stepCount = 0;
class treenode{
    friend class map;
    friend class Traveltree;
    private:
        int cost = 10000; // the step that the node distance from R
        int type;
        int ID = -1;
        int row,column;
        bool cleaned;
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
            //build_floor(arr);

            char matrix[heigh][width];
            for(int i=0;i<heigh;i++){
                for(int j=0;j<width;j++){ 
                    ifile>>matrix[i][j];
                }
            }
            
            for(int i=0;i<heigh;i++){
                for(int j=0;j<width;j++){ 
                    cout<<matrix[i][j]<<" ";
                }
                cout<<endl;
            }

            floor = new treenode*[heigh];
            for (int i=0;i<heigh;i++){
                floor[i]=new treenode[width];
                for(int j = 0;j<width;j++){
                    //puts("O");
                    notCleanBuf[i*heigh+j] = 1;
                    /*puts("DD");*/
                    int type = matrix[i][j]-'0';
                    //cout<<type<<" ";
                    //puts("WW");
                    floor[i][j].type=type;
                    //cout<<floor[3][0].type;
                    //puts("QQ");
                    if(floor[i][j].type == 1){
                        floor[i][j].cleaned = 1;
                        floor[i][j].cost = -1;
                    }
                    floor[i][j].row = i;
                    floor[i][j].column = j;
                    //cout<<floor[i][j].row<<" ";
                    if(type == 'R'-'0'){
                        //puts("us");
                        Root = &(floor[i][j]);
                        Root->type = 'R'; 
                        Root->cost = 0 ; 
                    }
                }
            }
            cout<<endl;
            for(int i=0;i<heigh;i++){
                for(int j=0;j<width;j++){
                    cout<<floor[i][j].type<<" ";
                }
                cout<<endl;
            }  
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
                //puts("II");

                for(int j=1;j<width-1;j++){
                    if(floor[i-1][j].type!=1) {
                        floor[i][j].up = &(floor[i-1][j]);
                        if(floor[i][j].up == Root){
                            Root->down = &(floor[i][j]);
                        }
                    }
                    else {
                        floor[i][j].up = NULL;
                        //puts("UU");
                    }
                    if(floor[i+1][j].type !=1) {
                        floor[i][j].down = &(floor[i+1][j]);
                        if(floor[i][j].down == Root){
                            Root->up = &(floor[i][j]);
                        }
                    }
                    else {
                        floor[i][j].down = NULL;
                        //puts("DD");
                    }
                    if(floor[i][j+1].type !=1) {
                        floor[i][j].right = &(floor[i][j+1]);
                        if(floor[i][j].right == Root){
                            Root->left = &(floor[i][j]);
                        }
                    }
                    else {
                        floor[i][j].right = NULL;
                        //puts("RR");
                    }
                    if(floor[i][j-1].type !=1) {
                        floor[i][j].left = &(floor[i][j-1]);
                        if(floor[i][j].left == Root){
                            Root->right = &(floor[i][j]);
                        }
                    }
                    else {
                        floor[i][j].left = NULL;
                        //puts("LL");
                    }
                }
                //puts("KK");
            }
            //puts("PP");
            BSF(&Root,0);
            //puts("IOP");
            buildTravelTree();
            for(int i=0;i<heigh;i++){
                for(int j = 0;j<width;j++){
                    cout<<floor[i][j].cost<<setw(5);
                }
                cout<<endl;
            }
        }
        void BSF(treenode ** a,int cost){
            (*a)->setcost(cost);
            //cout<<"R"<<Root->getup()->getcost();
            //puts("1");
            if((*a)->getup()!=NULL && (*a)->up->type!=1 && (*a)->up->cost>cost+1){
                //puts("2");
                treenode *up = (*a)->getup();
                BSF(&up,cost+1);
                //cout<<"R"<<Root->getID()<<" "<<endl;
                //puts("2 Over");    
            }
            if((*a)->getright()!=NULL && (*a)->right->type!=1 && (*a)->right->cost>cost+1){
                //puts("3");
                treenode *right = (*a)->getright();
                BSF(&right,cost+1);
                //puts("3 Over");
                
            } 
            if((*a)->getdown()!=NULL && (*a)->down->type!=1 && (*a)->down->cost>cost+1){
                //puts("4");
                treenode *down = (*a)->getdown();
                BSF(&down,cost+1);
                //puts("4 Over");
            } 
            if((*a)->getleft()!=NULL && (*a)->left->type!=1 && (*a)->left->cost>cost+1){
                //puts("5");
                treenode *left = (*a)->getleft();
                BSF(&left,cost+1); 
            }
            
            return;
            
        }
        
        void buildTravelTree(){
            //treenode *tmp = &(floor[i][j]);
            int R = 0;
            int j = 0;
            while(R<heigh){
                //cout<<R;
                while(floor[R][j].type ==1){
                    j++;
                    if(j == width){
                        R++;
                        j = 0;
                        id++;
                        
                    }
                    //cout<<R<<heigh;
                    if(R == heigh) break;
                }
                if(R == heigh) break;
                //cout<<R;
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
                //cout<<R;
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
                        if(left_tmp->up->ID<left_tmp->ID);
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
                        if(right_tmp->up->ID<right_tmp->ID);
                        else buildLevel(right_tmp->up);
                        
                    }
                    right_tmp = right_tmp->right;
                }
            }
            if(tmp->up){
                if(tmp->up->ID<tmp->ID);
                else{
                    buildLevel(tmp->up);
                }
            }
        }

        void buildLevelCheck(treenode *tmp){
            tmp->ID = id;
            //cout<<id<<"ID"<<endl;
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
            int width= floor->getwidth();
            int row=0;
            int columns =0;
            treenode* tmp = floor->Root;
            tmp->setcleaned(1);
            cleaner = tmp;
            int Row = tmp->getID();
            //cout<<Row<<endl;
            /*while(Row > 0){
                cleanRow(&tmp,Row,floor);
                puts("MINMIN");
                Row--;
            }*/
            cleanRow(&tmp,Row,floor);
            int home = backToRoot(&tmp);
            //cout<<tmp->getrow()<<" "<<power<<endl;
            puts("SS");
            /*Row = tmp->getID()+1;
            while(Row<heigh){
                cleanRow(&tmp,Row,floor);
                puts("OK!");
                Row++;
            }*/
            if(tmp->getcost() != 0){
                home =backToRoot(&tmp);
            }
            
        }

        void isRefresh(treenode*tmp){
            cout<<tmp->getrow()<<" "<<tmp->getcol()<<" "<<power<<endl;
            if(tmp->getcost() == power){

                cout<<tmp->getID();
                int step = backToRoot(&tmp);
                backToNode(&tmp,buf,step);
            }
        }

        void cleanRow(treenode **tmp,int Row,map *floor){
            treenode *cur = *tmp;
            int uuu=0;
            /*if(cur->getID()!= Row){
                if(Row > cur->getID()){ //往下調
                    while(cur->getID() != Row){
                        if(cur->getdown() && cur->getdown()->getID() == Row){
                            cur = cur->getdown();
                            cur->setcleaned(1);
                            power--;
                            stepCount++;
                            isRefresh(cur);
                        }
                        else if(cur->getleft() && uuu==0){ //左看看
                            if(cur->getleft()->getleft() ==NULL) uuu=1;
                            cur = cur->getleft();
                            power--;
                            stepCount++;
                            isRefresh(cur);
                            
                        }
                        
                        else if(cur->getright()){ //右看看
                            cur = cur->getright();
                            power--;
                            stepCount++;
                            isRefresh(cur);
                        }
                        if(cur->getright() == NULL) return;
                    }
                }

                else if(Row <cur->getID()){ // 往上調
                    while(cur->getID()!=Row){
                        if(cur->getup() && cur->getup()->getID() == Row){
                            cur = cur->getup();
                            cur->setcleaned(1);
                            power--;
                            stepCount++;
                            isRefresh(cur);
                        }
                        else if(cur->getleft()&& uuu==0){
                            if(cur->getleft()->getleft()) uuu=1;
                            cur = cur->getleft();
                            power--;
                            stepCount++;
                            isRefresh(cur);
                        }
                        else if(cur->getright()){
                            cur = cur->getright();
                            power--;
                            stepCount++;
                            isRefresh(cur);
                        }
                    }
                }

            }*/
            //調整到Row
            //先走左邊再走右邊//最後要回到一開始的點
            //如果遇到往上或往下=>走然後遞迴//走完回來
            
            treenode *record = cur;//記錄這個點
            
            
            treenode *detect = record;
            int LeftIsClean = detectLeftAllClean(detect);
            //int RightIsClean = detectRightAllClean(detect);
            

            if(cur->getleft() && cur->getleft()->getID() == Row && LeftIsClean ==1){
                while(cur->getleft()){
                    cur = cur->getleft();
                    cur->setcleaned(1);
                    power--;
                    stepCount++;
                    if(cur == floor->Root){
                        power = powerFull;
                    }
                    isRefresh(cur);
                    puts("L");
                }
            }
            while(cur != record){
                if(cur->getup() && cur->getup()->getID() == Row && cur->getup()->getclean() == 0){
                    puts("LBU=");
                    cur = cur->getup();
                    cur->setcleaned(1);
                    power--;
                    stepCount++;
                    if(cur == floor->Root){
                        power = powerFull;
                    }
                    isRefresh(cur);

                    cleanRow(&cur,Row,floor);
                    cur = cur->getdown();
                    power--;
                    stepCount++;
                    if(cur == floor->Root){
                        power = powerFull;
                    }
                    isRefresh(cur);
                    
                }
                else if(cur->getup() && cur->getup()->getID()!=Row && cur->getup()->getclean() == 0){
                    puts("LBU!");
                    cur = cur->getup();
                    cur->setcleaned(1);
                    power--;
                    stepCount++;
                    if(cur == floor->Root){
                        power = powerFull;
                    }
                    isRefresh(cur);

                    cleanRow(&cur,cur->getup()->getID(),floor);
                     cur = cur->getdown();
                    power--;
                    stepCount++;
                    if(cur == floor->Root){
                        power = powerFull;
                    }
                    isRefresh(cur);
                }
                if(cur->getdown() && cur->getdown()->getID() == Row && cur->getdown()->getclean() == 0){
                    puts("LBD=");
                    cur = cur->getup();
                    cur->setcleaned(1);
                    power--;
                    stepCount++;
                    if(cur == floor->Root){
                        power = powerFull;
                    }
                    isRefresh(cur);

                    cleanRow(&cur,Row,floor);
                    cur = cur->getdown();
                    power--;
                    stepCount++;
                    if(cur == floor->Root){
                        power = powerFull;
                    }
                    isRefresh(cur);
                }
                else if(cur->getdown() && cur->getdown()->getID()!=Row && cur->getdown()->getclean()==0){
                    puts("LBD!");
                    cur = cur->getdown();
                    cur->setcleaned(1);
                    power--;
                    stepCount++;
                    if(cur == floor->Root){
                        power = powerFull;
                    }
                    isRefresh(cur);

                    cleanRow(&cur,Row,floor);
                    cur = cur->getup();
                    power--;
                    stepCount++;
                    if(cur == floor->Root){
                        power = powerFull;
                    }
                    isRefresh(cur);
                }
                cur = cur->getright();
                power--;
                stepCount++;
                if(cur == floor->Root){
                    power = powerFull;
                }
                isRefresh(cur);
            }
            
            detect = record;
            int RightIsClean = detectRightAllClean(detect);
            cout<<record->getrow()<<" "<<record->getcol()<<endl;
            if(cur->getright() && cur->getright()->getID() == Row && RightIsClean ==1){
                puts("R");
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
            while(cur != record){
                

                if(cur->getup() && cur->getup()->getID() == Row && cur->getup()->getclean() == 0){
                    puts("RBU=");
                    cur = cur->getup();
                    cur->setcleaned(1);
                    power--;
                    stepCount++;
                    if(cur == floor->Root){
                        power = powerFull;
                    }
                    isRefresh(cur);

                    cleanRow(&cur,Row,floor);
                    cur = cur->getdown();
                    power--;
                    stepCount++;
                    if(cur == floor->Root){
                        power = powerFull;
                    }
                    isRefresh(cur);

                }
                else if(cur->getup() && cur->getup()->getID()!=Row && cur->getup()->getclean() == 0){
                    puts("RBU!");
                    cur = cur->getup();
                    cur->setcleaned(1);
                    power--;
                    stepCount++;
                    if(cur == floor->Root){
                        power = powerFull;
                    }
                    isRefresh(cur);
                    //puts("Q");
                    cleanRow(&cur,cur->getup()->getID(),floor);
                    cur = cur->getdown();
                    power--;
                    stepCount++;
                    if(cur == floor->Root){
                        power = powerFull;
                    }
                    isRefresh(cur);
                }
                if(cur->getdown() && cur->getdown()->getID() == Row && cur->getdown()->getclean() == 0){
                    puts("RBD=");
                    cur = cur->getdown();
                    cur->setcleaned(1);
                    power--;
                    stepCount++;
                    if(cur == floor->Root){
                        power = powerFull;
                    }
                    isRefresh(cur);

                    cleanRow(&cur,Row,floor);
                    cur= cur->getup();
                    power--;
                    stepCount++;
                    if(cur == floor->Root){
                        power = powerFull;
                    }
                    isRefresh(cur);
                }
                else if(cur->getdown() && cur->getdown()->getID()!=Row && cur->getdown()->getclean()==0){
                    puts("RBD!");
                    cur = cur->getdown();
                    cur->setcleaned(1);
                    power--;
                    stepCount++;
                    if(cur == floor->Root){
                        power = powerFull;
                    }
                    isRefresh(cur);
                    puts("A");
                    cleanRow(&cur,Row,floor);
                    cur = cur->getup();
                    power--;
                    stepCount++;
                    if(cur == floor->Root){
                        power = powerFull;
                    }
                    isRefresh(cur);
                    puts("W");
                }
                cur = cur->getleft();
                power--;
                stepCount++;
                if(cur == floor->Root){
                    power = powerFull;
                }
                isRefresh(cur);
            }
            if(cur->getup() && cur->getup()->getID() == Row && cur->getup()->getclean() == 0){
                puts("U=");
                cur = cur->getup();
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
            else if(cur->getup() && cur->getup()->getID() !=Row && cur->getup()->getclean() == 0){
                cout<<cur->getID();
                puts("U!");
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
            }
            if(cur->getdown() && cur->getdown()->getID() == Row && cur->getdown()->getclean() ==0){
                cout<<Row<<" "<<cur->getID()<<" "<<cur->getdown()->getID();
                puts("D=");
                cur = cur->getdown();
                cur->setcleaned(1);
                power--;
                stepCount++;
                if(cur == floor->Root){
                    power = powerFull;
                }
                isRefresh(cur);
                cleanRow(&cur,Row,floor);
                cur = cur->getup();
                power--;
                stepCount++;
                if(cur == floor->Root){
                    power = powerFull;
                }
                isRefresh(cur);
            }
            else if(cur->getdown() && cur->getdown()->getID() != Row && cur->getdown()->getclean() ==0){
                cout<<Row<<" "<<cur->getID()<<" "<<cur->getdown()->getID();
                puts("D!");
                cur = cur->getdown();
                cur->setcleaned(1);
                power--;
                stepCount++;
                if(cur == floor->Root){
                    power = powerFull;
                }
                isRefresh(cur);
                cleanRow(&cur,cur->getID(),floor);
                cur = cur->getup();
                power--;
                stepCount++;
                if(cur == floor->Root){
                    power = powerFull;
                }
                isRefresh(cur);
            }
            *tmp = cur;
            return;
        }

        int detectLeftAllClean(treenode*tmp){
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
        }
            

        void backToNode(treenode ** tmp,int *buf,int count){
            //cout<<count;
            while(count>=0){
                power--;
                stepCount++;
                if(buf[count] == 1){
                    puts("down");
                    *tmp = (*tmp)->getdown();
                    buf[count]=0;
                }
                else if(buf[count]==2){
                    puts("UP");
                    *tmp = (*tmp)->getup();
                    buf[count]=0;
                }
                else if(buf[count] == 3){
                    puts("right");
                    *tmp = (*tmp)->getright();
                    buf[count]=0;
                }
                else{
                    puts("left");
                    *tmp = (*tmp)->getleft();
                    buf[count]=0;
                }
                count--;
            }
            return;
        }

        int backToRoot(treenode **tmp){
            static int count;
            cout<<"CCC"<<endl;
            treenode *greatest = NULL;
            treenode *up = (*tmp)->getup();
            treenode *down = (*tmp)->getdown();
            treenode *left = (*tmp)->getleft();
            treenode* right = (*tmp)->getright();
            //cout<<(*tmp)->getrow()<<endl;;
            while(!greatest){
                if((*tmp)->getup() && (*tmp)->getcost()>=up->getcost()) {
                    greatest = up;
                }
                else if((*tmp)->getdown() && (*tmp)->getcost()>=down->getcost()) {
                    //puts("PP");
                    greatest = down;
                }
                else if((*tmp)->getleft() && (*tmp)->getcost()>=left->getcost()) {
                    greatest = left;
                }
                else if((*tmp)->getright()&& (*tmp)->getcost()>=right->getcost()) {
                    greatest = right;
                }
            }
            //cout<<greatest->getcost()<<greatest->getrow()<<greatest->getcol()<<endl;
            if((*tmp)->getup()){
                
                if(up->getcost()<= greatest->getcost()){
                    if(up->getclean()==greatest->getclean());
                    else if(up->getclean() ==0 && greatest->getclean() ==1){
                        greatest = up;
                        //buf[count] = 1;
                        //cout<<"EE1"<<"1"<<endl;
                    }
                    
                }
            }
            cout<<greatest->getrow()<<" "<<greatest->getcol()<<" ";
            if((*tmp)->getdown()){
                if(down->getcost()<=greatest->getcost()){
                    if(down->getclean()==greatest->getclean());
                    else if(down->getclean() ==0 && greatest->getclean() ==1){
                        greatest = down;
                        //buf[count] = 2;
                        //cout<<"EE2"<<endl;
                    }
                }
            }
            cout<<greatest->getrow()<<" "<<greatest->getcol()<<" ";
            if((*tmp)->getleft()){
                if(left->getcost()<=greatest->getcost()){
                    if(left->getclean()==greatest->getclean());
                    else if(left->getclean() ==0 && greatest->getclean() ==1){
                        greatest = left;
                        //buf[count] = 3;
                        //cout<<"EE3"<<endl;
                    }
                }
            }
            cout<<greatest->getrow()<<" "<<greatest->getcol()<<" ";
            if((*tmp)->getright()){
                if(right->getcost()<=greatest->getcost()){
                    if(right->getclean()==greatest->getclean());
                    else if(right->getclean() ==0 && greatest->getclean() ==1){
                        greatest = right;
                        //buf[count] = 4;
                       //cout<<"EE4"<<endl;
                    }
                }
            }
            cout<<greatest->getrow()<<" "<<greatest->getcol()<<" ";
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
            cout<<greatest->getrow()<<" "<<greatest->getcol()<<endl;
            greatest->setcleaned(1);
            power--;
            stepCount++;
            if(*tmp == cleaner){
                power = powerFull;
                //cout<<cleaner->getcost();
                //cout<<buf[0]<<buf[1]<<endl;
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
    int h = heigh;
    //cin.get();
    //cout<<heigh;
    
    
    
    
    map *mapping = new map(width,heigh);
    machine *Super_Hero = new machine(power);
    Super_Hero->clean(mapping);
    cout<<stepCount<<endl;
    ifile.close();
}
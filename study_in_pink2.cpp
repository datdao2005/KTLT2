#include "study_in_pink2.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////
//Other functions
int HPlimitation(int n, float a){
    n = n*a + 0.999;
    n = max(min(n,500),0);
    return n;
}

int EXPlimitation(int n, float a){
    n = n*a + 0.999;
    n = max(min(n,900),0);
    return n;
}

int cardinal(int n){
    int s = 0;
    while(n>0){
        s += n%10;
        n = n/10;
        cout << s << " ";
    }
    if(s>=10) s = cardinal(s);
    return s;
}

int getDist(Position p1, Position p2){
    return abs(p1.getRow()-p2.getRow())+abs(p1.getCol()-p2.getCol());
}

//MapElement
MapElement :: MapElement (ElementType in_type) : type(in_type){} 
ElementType MapElement::getType() const {return type;}

 Path::Path(): MapElement(PATH){}

 Wall::Wall():MapElement(WALL){}

FakeWall::FakeWall(int in_req_exp) : MapElement(FAKE_WALL){req_exp = in_req_exp;}
int FakeWall::getReqExp() const{return req_exp;}
//Map
Map::Map(int num_rows, int num_cols, int num_walls, Position * array_walls, int num_fake_walls, Position * array_fake_walls)
:num_rows(num_rows), num_cols(num_cols){
     map = new MapElement ** [num_rows];
       for (int i = 0; i < num_rows; i++){
        map[i] = new MapElement *[num_cols];
        for (int j = 0; j < num_cols; j++){
            map[i][j] = new Path();
        }
       }     

     for(int i = 0; i < num_walls; i++){
        int r = array_walls[i].getRow();
            int c = array_walls[i].getCol();
            delete map[r][c];
            map[r][c] = new Wall();
     }

     for(int i = 0; i < num_fake_walls; i++){
        int r = array_walls[i].getRow();
            int c = array_walls[i].getCol();
            delete map[r][c];
            map[r][c] = new FakeWall((r*257 + c*139 + 89)% 900 +1);
     }      
}

 Map::~Map(){ //Xóa bản đồ 
        for (int i = 0; i < num_rows; i++){
            for (int j = 0; j < num_cols; j++){
                delete map[i][j];
            }
            delete []map[i];
        }
        delete [] map;
    }

bool Map::isValid (const Position & pos, MovingObject * mv_obj) const {
   int r = pos.getRow();
   int c = pos.getCol();
   if (r < 0 || r >= num_rows || c < 0 || c >= num_cols){ return false;}
   MapElement *ele = map[r][c];
   if (ele ->getType() == WALL) {return false;}
   else if (ele ->getType() == FAKE_WALL && mv_obj ->getCharacter() == "Watson"){
    FakeWall *fw = dynamic_cast<FakeWall*>(ele);
    Watson *wt = dynamic_cast<Watson*>(mv_obj);
     return (wt->getExp()>fw->getReqExp());
   }
   else return true;
}

  const Position Position::npos = Position(-1, -1); //Điểm trả về khi input không hợp lệ 
     Position::Position(int r, int c){
        this -> r = r;
        this -> c = c;
     }
    
     int Position::getRow() const{return r;}
     int Position::getCol() const {return c;}
     void Position::setRow(int r) { this ->r = r;}
     void Position::setCol(int c) { this ->c = c;}

    bool Position::isEqual(int in_r, int in_c) const{return (r == in_r) && (c == in_c);}
    bool Position::isEqual(Position pos) const{return (this->getRow()==pos.getRow())&&(this->getCol()==pos.getCol());}
    
     string Position::str() const{
        string baseStr = "(,)";
    string strCol = to_string(c);
    baseStr = baseStr.insert(2,strCol);
    string strRow = to_string(r);
    return baseStr.insert(1,strRow);
     }
        
//MovingObject
MovingObject :: MovingObject(int index, const Position pos, Map * map, const string & name = ""): 
index(index), pos(pos), map(map), name(name){}

string MovingObject::getCharacter(){return name;}

Position MovingObject::getCurrentPosition()const {return pos;}

//Character
Character::Character(int index, const Position pos, Map * map, const string & name = "") : MovingObject(index,pos,map,name){};
//Sherlock 
Sherlock::Sherlock(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp) 
: Character(index, pos, map, "Sherlock"){
        this -> moving_rule = moving_rule; 
        this -> init_exp = init_exp;
        this -> init_hp = init_hp;
        
        if (init_exp > 900) {init_exp = 900;}
        else if (init_exp < 0) {init_exp = 0;}

        if (init_hp > 500) {init_hp = 500;}
        else if (init_hp < 0) {init_hp = 0;}
        
    }
    
    Position Sherlock::getNextPosition(){
        char dir = moving_rule[index];
    int size = moving_rule.size();
    index = (index+1) % size;
    Position next_pos = pos;
    int C = next_pos.getCol(), R = next_pos.getRow();
    switch (dir) {
        case 'L': 
            next_pos.setCol(C-1); 
            break;
        case 'R': 
            next_pos.setCol(C+1); 
            break;
        case 'U': 
            next_pos.setRow(R-1); 
            break;
        case 'D': 
            next_pos.setRow(R+1); 
            break;
    }
    if (map->isValid(next_pos, this)) return next_pos;
    else return Position::npos;
       }

    void Sherlock::move(){
    Position next_pos = getNextPosition();
      if (!next_pos.isEqual(Position::npos)) {
         pos = next_pos;
        }
    }

string Sherlock::str() const{
    stringstream ss;
     ss << "Sherlock[index=" << index << ";pos=" << pos.str() << ";moving_rule=" << moving_rule << "]";
    return ss.str();
}

int Sherlock::getExp()const{return init_exp;}
int Sherlock::getHp()const {return init_hp;}
void Sherlock::setExp(int Exp){Exp = init_exp;}
void Sherlock::setHp (int Hp) {Hp = init_hp;}


//Watson
Watson::Watson(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp)
:Character(index, init_pos, map, "Watson"){
        
        this -> moving_rule = moving_rule; 
        this -> init_exp = init_exp;
        this -> init_hp = init_hp;
        
        if (init_exp > 900) {init_exp = 900;}
        else if (init_exp < 0) {init_exp = 0;}

        if (init_hp > 500) {init_hp = 500;}
        else if (init_hp < 0) {init_hp = 0;}
}

Position Watson::getNextPosition(){
        char dir = moving_rule[index];
    int size = moving_rule.size();
    index = (index+1) % size;
    Position next_pos = pos;
    int C = next_pos.getCol(), R = next_pos.getRow();
    switch (dir) {
        case 'L': 
            next_pos.setCol(C-1); 
            break;
        case 'R': 
            next_pos.setCol(C+1); 
            break;
        case 'U': 
            next_pos.setRow(R-1); 
            break;
        case 'D': 
            next_pos.setRow(R+1); 
            break;
    }
    if (map->isValid(next_pos, this)) return next_pos;
    else return Position::npos;
}

//Position Watson::getCurrentPosition()const{return pos;}

void Watson::move(){
     Position next_pos = getNextPosition();
        if (!next_pos.isEqual(Position::npos)) {
            pos = next_pos;
        }
}

int Watson::getExp()const{return init_exp;}
int Watson::getHp()const {return init_hp;}
void Watson::setExp(int Exp){Exp = init_exp;}
void Watson::setHp (int Hp) {Hp = init_hp;}

string Watson::str() const{ stringstream ss;
        ss << "Watson[index=" << index << ";pos=" << pos.str() << ";moving_rule=" << moving_rule << "]";
        return ss.str();}

//Criminal 
 Criminal::Criminal(int index, const Position & init_pos, Map * map, Sherlock * sherlock, Watson * watson):
        Character(index, init_pos, map, "Criminal"), sherlock(sherlock), watson(watson){};
Position Criminal::getNextPosition(){
    Position currentPos = this->getCurrentPosition();
    Position next = Position::npos;
    int MaxDis = -1;
    int r = pos.getRow(), c = pos.getCol();
    Position moving[4] = {Position(1, 0), Position(0, -1), Position(-1, 0), Position(0, 1)};
    for (int i = 0; i < 4; i++){
        Position newPos(currentPos.getRow() + moving[i].getRow(), currentPos.getCol() + moving[i].getCol());
        if(map->isValid(newPos, this)){
                int Dis = abs(newPos.getRow() - sherlock->getCurrentPosition().getRow()) + 
                          abs(newPos.getCol() - sherlock->getCurrentPosition().getCol()) +
                          abs(newPos.getRow() - watson->getCurrentPosition().getRow())+
                          abs(newPos.getCol() - watson->getCurrentPosition().getCol());
            if(Dis > MaxDis){
                MaxDis = Dis;
                next = newPos;
            }
        }
    }
    return next;
}


void Criminal::move(){
     Position next_pos = getNextPosition();
        if (next_pos.str() != Position::npos.str()){
            last_pos = pos;
            pos = next_pos;
        }
}

Position Criminal::getLastPosition(){return last_pos;}
string Criminal::str() const { stringstream ss;
        ss << "Criminal[index=" << index << ";pos=" << pos.str() << "]";
        return ss.str();}

bool Criminal::Caught(){
    return sherlock->getCurrentPosition().isEqual(this->getCurrentPosition())||
    watson->getCurrentPosition().isEqual(this->getCurrentPosition());
}

 int Criminal::getExp() const{return -1;}
 int Criminal::getHp() const{return -1;}
 void Criminal::setExp(int Exp){}
 void Criminal::setHp(int Hp){}

//ArrayMovingObject
 ArrayMovingObject::ArrayMovingObject(int capacity){
     this -> capacity = capacity;
     count = 0;
     arr_mv_objs = new MovingObject *[capacity];
 }

 ArrayMovingObject::~ArrayMovingObject(){ delete [] arr_mv_objs;} 
 
 bool ArrayMovingObject::isFull() const { return count == capacity;}

MovingObject * ArrayMovingObject::get(int index) const{return arr_mv_objs[index];}

 bool ArrayMovingObject::add ( MovingObject * mv_obj ){
    if(isFull()) {return false;}
    arr_mv_objs[count] = mv_obj;
    count++;
    return true;
 }
 int ArrayMovingObject::size() const{return count;} // return current number of elements in the array

 string ArrayMovingObject::str() const{
     stringstream ss;
    ss << "ArrayMovingObject[count=" << count << ";capacity=" << capacity << ";";
    for (int i = 0; i < count; i++){
        ss << arr_mv_objs[i]->str();
        if(i+1!=count) ss << ";";
    }
    ss << "]";
    return ss.str();
 }

 Configuration::Configuration(const string & filepath){
    ifstream file(filepath);
    string line;
    while (getline(file, line)){
        stringstream ss(line);
        string key;
        getline(ss, key, '=');
        if (key == "MAP_NUM_ROWS") ss >> map_num_rows;
        else if (key == "MAP_NUM_COLS") ss >> map_num_cols;
        else if (key == "MAX_NUM_MOVING_OBJECTS") ss >> max_num_moving_objects;
        else if (key == "ARRAY_WALLS") {
            string walls_str;
            ss >> walls_str;
            stringstream walls_ss(walls_str.substr(1, walls_str.size() - 2));
            string pos;
            int numW = 0;
            while (getline(walls_ss, pos, ';')) {
                arr_walls[numW] = Position(pos);
                numW++;
            }
            num_walls = numW;
        } 
        else if (key == "ARRAY_FAKE_WALLS") {
            string fakewalls_str;
            ss >> fakewalls_str;
            stringstream fakewalls_ss(fakewalls_str.substr(1, fakewalls_str.size() - 2)); 
            string pos;
            int num_f_w = 0;
            while (getline(fakewalls_ss, pos, ';')) {
                arr_fake_walls[num_f_w] = Position(pos);
                num_f_w++;
            }
            num_fake_walls = num_f_w;
        } 
        else if (key == "SHERLOCK_MOVING_RULE") ss >> sherlock_moving_rule;
        else if (key == "SHERLOCK_INIT_POS") {
            string pos;
            ss >> pos;
            sherlock_init_pos = Position(pos);
        }
        else if (key == "SHERLOCK_INIT_HP") ss >> sherlock_init_hp;
        else if (key == "SHERLOCK_INIT_EXP") ss >> sherlock_init_exp;
        else if (key == "WATSON_MOVING_RULE") ss >> watson_moving_rule;
        else if (key == "WATSON_INIT_POS") {
            string pos;
            ss >> pos;
            watson_init_pos = Position(pos);
        } 
        else if (key == "WATSON_INIT_HP") ss >> watson_init_hp;
        else if (key == "WATSON_INIT_EXP") ss >> watson_init_exp;
        else if (key == "CRIMINAL_INIT_POS") {
            string pos;
            ss >> pos;
            criminal_init_pos = Position(pos);
        }
        else if (key == "NUM_STEPS") ss >> num_steps;
    }
 }
 
 string Configuration::str() const{
    stringstream ss;
    string stringW="[", stringF="[";
    for(int i = 0; i<num_walls; i++){
        stringW+=arr_walls[i].str();
        if(i+1!=num_walls) stringW+=';';
    }
    stringW+=']';
    for(int i = 0; i<num_fake_walls; i++){
        stringF+=arr_fake_walls[i].str();
        if(i+1!=num_fake_walls) stringF+=';';
    }
    stringF+=']';
    ss << "Configuration[\n"
        << "MAP_NUM_ROWS=" << map_num_rows << "\n"
        << "MAP_NUM_COLS=" << map_num_cols << "\n"
        << "MAX_NUM_MOVING_OBJECTS=" << max_num_moving_objects << "\n"
        << "NUM_WALLS=" << num_walls << "\n"
        << "ARRAY_WALLS=" << stringW << "\n"
        << "NUM_FAKE_WALLS=" << num_fake_walls << "\n"
        << "ARRAY_FAKE_WALLS=" << stringF << "\n"
        << "SHERLOCK_MOVING_RULE=" << sherlock_moving_rule << "\n"
        << "SHERLOCK_INIT_POS=" << sherlock_init_pos.str() << "\n"
        << "SHERLOCK_INIT_HP=" << sherlock_init_hp << "\n"
        << "SHERLOCK_INIT_EXP=" << sherlock_init_exp << "\n"
        << "WATSON_MOVING_RULE=" << watson_moving_rule << "\n"
        << "WATSON_INIT_POS=" << watson_init_pos.str() << "\n"
        << "WATSON_INIT_HP=" << watson_init_hp << "\n"
        << "WATSON_INIT_EXP=" << watson_init_exp << "\n"
        << "CRIMINAL_INIT_POS=" << criminal_init_pos.str() << "\n"
        << "NUM_STEPS=" << num_steps << "\n"
        << "]";
    return ss.str();
 }

 Configuration::~Configuration(){
        delete[] arr_walls;
        delete[] arr_fake_walls;
 }

 int Configuration::takeNumsteps(){
        return num_steps;
 }

 Map Configuration::drawMap(){
        return Map(map_num_rows, map_num_cols, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
    }

Position Configuration::getSherlockInitPos() const {return sherlock_init_pos;}
string Configuration::getSherlockMovingRule() const {return sherlock_moving_rule;}    
int Configuration::getSherlockInitHp() const {return sherlock_init_hp;}
int Configuration::getSherlockInitExp() const {return sherlock_init_exp;}
Position Configuration::getWatsonInitPos() const {return watson_init_pos;}
string Configuration::getWatsonMovingRule() const {return watson_moving_rule;}    
int Configuration::getWatsonInitHp() const {return watson_init_hp;}
int Configuration::getWatsonInitExp() const {return watson_init_exp;}
Position Configuration::getCriminalInitPos() const {return criminal_init_pos;}
int Configuration::getMaxNumMovingObjects() const {return max_num_moving_objects;}

//Robot
 Robot::Robot (RobotType in_rb_type) : robot_type(in_rb_type), MovingObject(index, pos, map, name){} 
 RobotType Robot::getType(){return robot_type;}
 Robot::Robot(int index, const Position& pos, Map* map, Criminal * criminal):
  MovingObject(index, pos, map, "Robot"), criminal(criminal){
    this -> item = createItem();
  }
  void Robot::move(){
    Position next_pos = getNextPosition();
    if (!next_pos.isEqual(Position::npos)) pos = next_pos;
}

 string Robot::str() const{
        if(robot_type==C) return "";
        stringstream ss;
        ss << "Robot[pos=" << pos.str() << ";type=" << robot_type << ";dist=" << getDistance() << "]";
        return ss.str();
    }

 BaseItem* Robot::createItem(){
    int i = initPos.getRow(), j = initPos.getCol();
    int p = i*j;
    int s = cardinal(p);
    BaseItem *itemType;
    if (s>=0 &&s<=1) 
        itemType = new MagicBook();
    else if (s>=2&&s<=3) 
        itemType =  new EnergyDrink();
    else if (s>=4&&s<=5) 
        itemType =  new FirstAid();
    else if (s>=6&&s<=7) 
        itemType =  new ExcemptionCard();
    else{
        int t = (i*11+j)%4;
        string challenge;
        switch(t){
            case 0: 
                challenge = "RobotS"; 
                break;
            case 1: 
                challenge = "RobotC"; 
                break;
            case 2: 
                challenge = "RobotSW"; 
                break;
            case 3: 
                challenge = "all"; 
                break;
        }
        itemType =  new PassingCard(challenge);
    }
    return itemType;
 }
 void Robot::setItem(){
        item = this->createItem();
    }
 BaseItem *Robot::takeItem(){
    if(item!=NULL) {return item;}
        else return NULL;
 }

 int Robot::getExp()const{return -1;}
 RobotC::RobotC(int index, const Position & init_pos, Map *map, Criminal *criminal):Robot(C){}

 Position RobotC::getNextPosition(){
        return pos = criminal->getLastPosition();
 }

 int RobotC::getDistance() const{return -1;}

 int RobotC::getDistance (Sherlock* sherlock) const {
    Position currentPos = getCurrentPosition();
        return abs(currentPos.getRow() - sherlock->getCurrentPosition().getRow()) +
               abs(currentPos.getCol() - sherlock->getCurrentPosition().getCol());
 }
 
 int RobotC::getDistance(Watson * watson) const{
        Position currentPos = getCurrentPosition();
        return abs(currentPos.getRow() - watson->getCurrentPosition().getRow()) +
               abs(currentPos.getCol() - watson->getCurrentPosition().getCol());
    }
 
 //RobotS
RobotS::RobotS(int index, const Position & init_pos, Map *map , Criminal *criminal , Sherlock *sherlock):Robot(S), sherlock(sherlock){}

Position RobotS::getNextPosition(){
   Position currentPos = getCurrentPosition();
    Position next = Position::npos;
    int minDist = 100;
    Position moving[4] = {Position(1, 0), Position(0, -1), Position(-1, 0), Position(0, 1)};
    for (int i = 0; i < 4; ++i) {
        Position newPos(currentPos.getRow() + moving[i].getRow(), currentPos.getCol() + moving[i].getCol());
        if (map->isValid(newPos, this)) {
            int dist = abs(newPos.getRow() - sherlock->getCurrentPosition().getRow()) +
                       abs(newPos.getCol() - sherlock->getCurrentPosition().getCol());
            if (dist < minDist) {
                minDist = dist;
                next = newPos;
            }
        }
    }
    return next;
}
 
 int RobotS::getDistance() const{
        Position currentPos = getCurrentPosition();
        return abs(currentPos.getRow() - sherlock->getCurrentPosition().getRow()) +
               abs(currentPos.getCol() - sherlock->getCurrentPosition().getCol());
    }

    int RobotS::getDistance(Sherlock * sherlock) const{return -1;}
    int RobotS::getDistance(Watson * watson) const{return -1;}

    //RobotW
    RobotW::RobotW ( int index , const Position & init_pos , Map *map, Criminal *criminal , Watson *watson): 
    Robot(index, init_pos, map, criminal), watson(watson){}

    Position RobotW::getNextPosition(){
        Position currentPos = getCurrentPosition();
        Position nextPos = Position::npos;
        int minDist = 100;
        Position directions[] = {Position(-1, 0), Position(0, 1), Position(1, 0), Position(0, -1)};
        for (int i = 0; i<4; i++){
            Position newPos(currentPos.getRow() + directions[i].getRow(), currentPos.getCol() + directions[i].getCol());
            if (map->isValid(newPos, this)) {
                int distance = abs(newPos.getRow() - watson->getCurrentPosition().getRow()) +
                               abs(newPos.getCol() - watson->getCurrentPosition().getCol());
                if (distance < minDist){
                    minDist = distance;
                    nextPos = newPos;
                }
            }
        }
        return nextPos;
    }

    int RobotW::getDistance() const{
        Position currentPos = getCurrentPosition();
        return getDist(currentPos,watson->getCurrentPosition());
    }

    int RobotW::getDistance(Sherlock * sherlock) const{return -1;}
    int RobotW::getDistance(Watson * watson) const{return -1;}
//RobotSW
RobotSW::RobotSW(int index, const Position &init_pos, Map *map, Criminal *criminal, Sherlock *sherlock, Watson *watson):
Robot(robot_type),sherlock(sherlock),watson(watson){}

Position RobotSW::getNextPosition() {
    Position currentPos = getCurrentPosition();
    Position next = Position::npos;
    int minDist = 100;
    Position moving[4] = {Position(-2, 0), Position(0, 2), Position(2, 0), Position(0, -2)};
    for (int i = 0; i < 4; ++i) {
        Position newPos(currentPos.getRow() + moving[i].getRow(), currentPos.getCol() + moving[i].getCol());
        if (map->isValid(newPos, this)) {
            int dist = abs(newPos.getRow() - sherlock->getCurrentPosition().getRow()) +
                       abs(newPos.getCol() - sherlock->getCurrentPosition().getCol()) +
                       abs(newPos.getRow() - watson->getCurrentPosition().getRow()) +
                       abs(newPos.getCol() - watson->getCurrentPosition().getCol());
            if (dist < minDist) {
                minDist = dist;
                next = newPos;
            }
        }
    }
    return next;
}
int RobotSW::getDistance() const{
        Position currentPos = getCurrentPosition();
        return abs(currentPos.getRow() - sherlock->getCurrentPosition().getRow()) +
               abs(currentPos.getCol() - sherlock->getCurrentPosition().getCol()) +
               abs(currentPos.getRow() - watson->getCurrentPosition().getRow()) +
               abs(currentPos.getCol() - watson->getCurrentPosition().getCol());
    }
    int RobotSW::getDistance(Sherlock * sherlock) const{return -1;}
    int RobotSW::getDistance(Watson * watson) const{return -1;}

//BaseItem
BaseItem::BaseItem(ItemType item):item(item){}
ItemType BaseItem::getType(){return item;}

MagicBook::MagicBook():BaseItem(MAGIC_BOOK){}
 bool MagicBook::canUse(Character * obj, Robot * robot = NULL){
        return(obj->getExp()<=350);
    }
 void MagicBook::use(Character * obj, Robot * robot = NULL){
        obj->setExp(EXPlimitation(obj->getExp(), 1.25));
    }

EnergyDrink::EnergyDrink():BaseItem(ENERGY_DRINK){}
bool EnergyDrink::canUse(Character * obj, Robot * robot = NULL){
        return(obj->getExp()<=350&&obj->getHp()<=100);
    }
void EnergyDrink::use(Character * obj, Robot * robot = NULL){
        obj->setExp(HPlimitation(obj->getExp(), 1.5));
    }

FirstAid:: FirstAid(): BaseItem(FIRST_AID){}
 bool FirstAid::canUse(Character * obj, Robot * robot = NULL){
        return(obj->getExp()<=350&&obj->getHp()<=100);
    }

    void FirstAid::use(Character * obj, Robot * robot = NULL){
        obj->setExp(HPlimitation(obj->getExp(), 1.5));
    }
//ExcemptionCard
 ExcemptionCard::ExcemptionCard(): BaseItem(EXCEMPTION_CARD){}
 bool ExcemptionCard::canUse(Character * obj, Robot * robot){
        return(obj->getCharacter()=="Sherlock" && obj->getExp()%2==1);
    }
 void ExcemptionCard::use(Character * obj, Robot * robot){}

//PassingCard
PassingCard::PassingCard(string challenge):BaseItem(PASSING_CARD), challenge(challenge){}
 bool PassingCard::canUse(Character * obj, Robot * robot){
        return(obj->getCharacter()=="Watson"&&obj->getExp()%2==0);
    }
    void PassingCard::use(Character * obj, Robot * robot){
        if(challenge!="all"||(challenge!="RobotS"&&robot->getType()!=S)
        ||((challenge!="RobotC"&&robot->getType()!=C))||(challenge!="RobotSW"&&robot->getType()!=SW))
            obj->setExp(obj->getExp()-50);
    }
Node::Node(BaseItem* item) : item(item), next(NULL){}

//BaseBag
BaseBag::BaseBag(Character* obj): obj(obj), head(NULL), count(0){}
BaseBag::~BaseBag(){
    while(head!=NULL){ //Xóa node
            Node* temp = head;
            head = head->next;
            delete temp->item;
            delete temp;
        }
}

bool BaseBag::insert(BaseItem* item){
        Node* newNode = new Node(item); //Thêm một node mới vào
        newNode->next = head;
        head = newNode;
        ++count;
        return true;
    }

BaseItem* BaseBag::get(ItemType itemType){
        Node* delNode = head->next;
        while (delNode != NULL && delNode->item->getType() != itemType) {
            delNode = delNode->next;
        }
        // Check if the node to be deleted is the head node
        if (head->next == delNode) {
            Node* temp = head->next;
            BaseItem* itemToGet = temp->item;
            head->next = head->next->next;
            delete temp;
            return itemToGet;
        }
        // Find the node before the node to be deleted
        Node* prev = head;
        while (prev->next != delNode)
            prev = prev->next;
        // Swap the node to be deleted with the head node
        Node* temp = head->next;
        head->next = delNode;
        prev->next = temp;
        delNode->next = temp->next;
        BaseItem* itemToGet = temp->item;
        temp->next = head->next->next;
        // Delete the former head node
        delete temp;
        count--;
        return itemToGet;
    }

BaseItem* BaseBag::get(){
        if (head == NULL) return NULL;
        Node* prev = NULL;
        Node* curr = head;
        while(head!=NULL){
            if((curr->item->getType()==MAGIC_BOOK||curr->item->getType()==ENERGY_DRINK||curr->item->getType()==FIRST_AID)){
                if(curr->item->canUse(obj,NULL)){
                    return curr->item;
                }
            }
            prev = curr;
            curr = curr->next;
        }
        return NULL;
    }

    bool BaseBag::find(ItemType itemType){
    Node* findNode = head;
    while (findNode != nullptr){
        if(findNode->item->getType()==itemType)
            return true;
        findNode = findNode->next;
    }
    return false;
}

string BaseBag::str() const {
        stringstream ss;
        ss << "Bag[count=" << count << ";";
        Node* curr = head;
        while(curr!=NULL){
            ss << curr->item->getType() << ",";
            curr = curr->next;
        }
        ss << "]";
        return ss.str();
    }

int BaseBag::getNumItem() const{return count;}
//SherlockBag
SherlockBag::SherlockBag(Sherlock* sherlock): BaseBag(sherlock){}
bool SherlockBag::insert(BaseItem* item){
    if (count >= 13) return false;
    else return BaseBag::insert(item);
     }
//WatsonBag
WatsonBag::WatsonBag(Watson *watson): BaseBag(watson){}
bool WatsonBag::insert(BaseItem* item){
if (count >= 15) return false;
else return BaseBag::insert(item);
}

//
StudyPinkProgram::StudyPinkProgram(const string & config_file_path){
     config = new Configuration(config_file_path);
        map = new Map(config->drawMap());
        sherlock = new Sherlock(1, config->getSherlockMovingRule(), config->getSherlockInitPos(), map, config->getSherlockInitHp(), config->getSherlockInitExp());
        watson = new Watson(2, config->getWatsonMovingRule(), config->getWatsonInitPos(), map, config->getWatsonInitHp(), config->getWatsonInitExp());
        criminal = new Criminal(0, config->getCriminalInitPos(), map, sherlock, watson);
        arr_mv_objs = new ArrayMovingObject(config->getMaxNumMovingObjects());
        arr_mv_objs->add(criminal);
        arr_mv_objs->add(sherlock);
        arr_mv_objs->add(watson);
        sherlockBag = new SherlockBag(sherlock);
        watsonBag = new WatsonBag(watson);
}
bool StudyPinkProgram::isStop()const{
    return (sherlock->getHp() == 0 || watson->getHp() == 0 || criminal->Caught());
}

void StudyPinkProgram::printResult() const {
    if (sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition()))
        cout << "Sherlock caught the criminal" << endl;
    else if (watson->getCurrentPosition().isEqual(criminal->getCurrentPosition())) 
        cout << "Watson caught the criminal" << endl;
    else cout << "The criminal escaped" << endl;
}

void StudyPinkProgram::printStep(int si) const {
    cout << "Step: " << setw(4) << setfill('0') << si
            << "--"
            << sherlock->str() << "--|--" << watson->str() << "--|--" << criminal->str() << endl;
}

void StudyPinkProgram::run(bool verbose) {
    bool firstR = true;
    int criminalStep = 1;
    if (!isStop()) for (int istep = 1; istep <= config->takeNumsteps(); ++istep){
        for (int i = 0; i < arr_mv_objs->size(); ++i){
            if(!criminal->getNextPosition().isEqual(Position::npos)) criminalStep++;
            arr_mv_objs->get(i)->move();
        }
        if (isStop()){
            printStep(istep);
            break;
        }
        if(sherlock->getCurrentPosition().isEqual(watson->getCurrentPosition())){
            cout<<"Sherlock meets Watson "<<endl;
            if(sherlockBag->find(PASSING_CARD)==true&&watsonBag->find(EXCEMPTION_CARD)==true){
                while(sherlockBag->find(PASSING_CARD)&&watsonBag->getNumItem()<15)
                    watsonBag->insert(sherlockBag->get(PASSING_CARD));
                while(watsonBag->find(EXCEMPTION_CARD)&&sherlockBag->getNumItem()<13)
                    sherlockBag->insert(watsonBag->get(EXCEMPTION_CARD));
            }
        }
        for(int j = 3; j < arr_mv_objs->size(); j++){
            if(arr_mv_objs->get(j)->getCurrentPosition().isEqual(sherlock->getCurrentPosition())){
                Robot* robot = dynamic_cast<Robot*>(arr_mv_objs->get(j));
                bool excemption = false;
                if(robot){
                    if(sherlockBag->find(EXCEMPTION_CARD)&&sherlockBag->get(EXCEMPTION_CARD)->canUse(sherlock, robot)){
                        sherlockBag->get(EXCEMPTION_CARD);
                        excemption = true;
                    } 
                    if (robot->getType()==S){
                        cout<<"Sherlock meets RobotS"<<endl;
                        if (sherlock->getExp() > 400)
                            sherlockBag->insert(robot->takeItem());
                        else if(!excemption)
                            sherlock->setExp(EXPlimitation(sherlock->getExp(), 0.9));
                    }
                    else if (robot->getType()==W){
                        cout<<"Sherlock meets RobotW"<<endl;
                        sherlockBag->insert(robot->takeItem());
                    }
                    else if (robot->getType()==SW){
                        cout<<"Sherlock meets RobotSW"<<endl;
                        if (sherlock->getExp() > 300 && sherlock->getHp() > 335)
                            sherlockBag->insert(robot->takeItem());
                        else if(!excemption){
                            sherlock->setExp(EXPlimitation(sherlock->getExp(), 0.85));
                            sherlock->setExp(HPlimitation(sherlock->getHp(), 0.85));
                        }
                    } 
                    else if (robot->getType()==C){
                        cout<<"Sherlock meets RobotC"<<endl;
                        if (sherlock->getExp()>500){
                            sherlock->getCurrentPosition().setRow(criminal->getCurrentPosition().getRow());
                            sherlock->getCurrentPosition().setCol(criminal->getCurrentPosition().getCol());
                        }
                        else sherlockBag->insert((robot->takeItem()));
                    }
                }
                if (isStop()){
                    printStep(istep);
                    break;
                }
                sherlockBag->get();
            }
                else if(arr_mv_objs->get(j)->getCurrentPosition().isEqual(watson->getCurrentPosition())){
                    Robot* robot = dynamic_cast<Robot*>(arr_mv_objs->get(j));
                    bool pass = false;
                    if(robot){
                        if(watsonBag->find(PASSING_CARD)&&watsonBag->get(PASSING_CARD)->canUse(watson, robot)){
                            BaseItem* Item = watsonBag->get(PASSING_CARD);
                            Item->use(watson,robot);
                            pass = true;
                        }
                        if(robot->getType()==S||pass) cout<<"Watson meets RobotS"<<endl;
                        else if(robot->getType()==W){
                            cout<<"Watson meets RobotW"<<endl;
                            if (watson->getExp()>350||pass)
                                watsonBag->insert(robot->takeItem());
                            else sherlock->setExp(EXPlimitation(sherlock->getExp(), 0.9));
                        }
                        else if(robot->getType()==SW){
                            cout<<"Watson meets RobotSW"<<endl;
                            if ((watson->getExp()>600&&watson->getHp()>165)||pass)
                                watsonBag->insert(robot->takeItem());
                            else{
                                watson->setExp(EXPlimitation(watson->getExp(), 0.85));
                                watson->setExp(HPlimitation(watson->getHp(), 0.85));
                            }
                        } 
                        else if (robot->getType()==C){
                            cout<<"Watson meets RobotC"<<endl;
                            watsonBag->insert((robot->takeItem()));
                        } 
                    }
                    watsonBag->get();
                }
        }
        if(criminalStep%3==1){
            Robot* robot;
            if (firstR){
                robot = new RobotC(3, criminal->getLastPosition(), map, criminal);
                firstR = false;
            } 
            else{
                int distSherlock = getDist(criminal->getLastPosition(),sherlock->getCurrentPosition());
                int distWatson = getDist(criminal->getLastPosition(),watson->getCurrentPosition());
                if (distSherlock < distWatson)
                    robot = new RobotS(arr_mv_objs->size(), criminal->getLastPosition(), map, criminal, sherlock);
                else if (distWatson < distSherlock)
                    robot = new RobotW(arr_mv_objs->size(), criminal->getLastPosition(), map, criminal, watson);
                else robot = new RobotSW(arr_mv_objs->size(), criminal->getLastPosition(), map, criminal, sherlock, watson);
            }
            arr_mv_objs->add(robot);
            cout<<robot->str()<<endl;
        }

        if(verbose){
            printStep(istep);
            cout<<arr_mv_objs->size()<<endl;
            for(int j = 0; j<arr_mv_objs->size(); j++)
                cout<<arr_mv_objs->get(j)->str()<<endl;
            cout<<sherlockBag->str()<<endl;
            cout<<watsonBag->str()<<endl;
        } 
    }
    printResult();
}


StudyPinkProgram::~StudyPinkProgram(){
    delete config;
    delete map;
    delete sherlock;
    delete watson;
    delete criminal;
    delete arr_mv_objs;
    delete sherlockBag;
    delete watsonBag;
}

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////

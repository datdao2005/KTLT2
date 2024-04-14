#include "study_in_pink2.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////
class TestStudyInPink;

MapElement :: MapElement (ElementType in_type) : type(in_type){} //Lấy type trung gian qua in_type
ElementType MapElement::getType() const {return type;} //Lấy các type trong enum ElementTyp
int FakeWall::getReqExp()const{}

//Tạo bản đồ
Map::Map(int num_rows, int num_cols, int num_walls, Position * array_walls, int num_fake_walls, Position * array_fake_walls)
:num_rows(num_rows), num_cols(num_cols){

     map = new MapElement ** [num_rows];
       for (int i = 0; i < num_rows; i++){
        map[i] = new MapElement *[num_cols];
        for (int j = 0; j < num_cols; j++){
            map[i][j] = new Path();
            if (map[i][j] -> getType() == WALL){ //Tạo Walls
                map[i][j] = new Wall();
            }
        }
       }     

     for (int i = 0; i < num_rows; i++){
        map[i] = new MapElement *[num_cols];
        for (int j = 0; j < num_cols; j++){
            map[i][j] = new Path();
            if (map[i][j] -> getType() == FAKE_WALL){ //Tạo FakeWalls
                map[i][j] = new FakeWall();
            }
        }
       }     
           
}

 Map::~Map(){ //Xóa bản đồ 
        for (int i = 0; i < num_rows; i++){
            for (int j = 0; j < num_cols; j++){
                delete map[i][j];
            }
            delete map[i];
        }
        delete [] map;
    }

bool Map::isValid ( const Position & pos , MovingObject * mv_obj ) const {
   int r = pos.getRow();
   int c = pos.getCol();
   if(map[r][c] ->getType() == FAKE_WALL && mv_obj ->getCharacter() == "Watson"){
    FakeWall *ptr;
    Watson *watson;
    ptr = dynamic_cast<FakeWall*>(map[r][c]);
    watson = dynamic_cast<Watson*>(mv_obj);
    
   }
}

 static const Position npos(-1, -1); //Điểm trả về khi input không hợp lệ 
     Position::Position(int r=0, int c=0){
         r = r;
         c = c;
     }
    

     int Position::getRow() const{return r;}
     int Position::getCol() const {return c;}
     void Position::setRow(int r) { r = r;}
     void Position::setCol(int c) { c = c;}

    
     bool Position::isEqual(int in_r, int in_c)const{
        return in_r ==r && in_c == c;
     }
      Position::Position(const string & str_pos){
        this -> r = stoi(str_pos.substr(1, str_pos.find(',' - 1)));
        this -> c = stoi(str_pos.substr(str_pos.find(',') + 1, str_pos.find(')') - str_pos.find(',') - 1));
      }
     string Position::str() const{return "(" + to_string(r) + "," +to_string(c) + ")";}

     int Position::distance(Position pos) const{
        int dis_r = pos.getRow() - this -> getRow();
        int dis_c = pos.getCol() - this -> getCol();
        return abs(dis_r) + abs(dis_c);
     }
//MovingObject
MovingObject :: MovingObject(int index, const Position pos, Map * map, const string & name=""){
        this -> index = index;
        this -> pos = pos;
        this -> map = map;
        this -> name = name;
}
string MovingObject::getCharacter(){return name;}

MovingObject::~MovingObject(){delete map;} //giải phóng bộ nhớ

Position MovingObject::getNextPosition(){}

Position MovingObject::getCurrentPosition()const {return pos;}

void MovingObject::move(){}

//Sherlock 
Sherlock::Sherlock(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp) 
: MovingObject(index, init_pos, map, name) {
        index = index;
        this -> moving_rule = moving_rule; 
        this -> init_pos = init_pos;
        this -> init_exp = init_exp;
        this -> init_hp = init_hp;
        
        if (init_exp > 900) {init_exp = 900;}
        else if (init_exp < 0) {init_exp = 0;}

        if (init_hp > 500) {init_hp = 500;}
        else if (init_hp < 0) {init_hp = 0;}
        
    }

    Position Sherlock::getNextPosition(){
        int r = pos.getRow();
        int c = pos.getCol();
        switch(moving_rule[0]){
        case 'U' : r--; break;
        case 'D' : r++; break;
        case 'L' : c--; break;
        case 'R' : c++; break;
        }
        moving_rule = moving_rule.substr(1) + moving_rule[0];
        if(map -> isValid(Position(r,c), this)) return Position(r,c);
       }
    Position Sherlock::getCurrentPosition()const{return pos;}

void Sherlock::move(){
    pos = this -> getNextPosition();
}

 

string Sherlock::str() const{
    return "[index=" + to_string(index) + ";pos=";}

//Watson
Watson::Watson(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp)
:MovingObject(index, init_pos, map, name){
        index = index;
        this -> moving_rule = moving_rule; 
        this -> init_pos = init_pos;
        this -> init_exp = init_exp;
        this -> init_hp = init_hp;
        
        if (init_exp > 900) {init_exp = 900;}
        else if (init_exp < 0) {init_exp = 0;}

        if (init_hp > 500) {init_hp = 500;}
        else if (init_hp < 0) {init_hp = 0;}
}

Position Watson::getNextPosition(){
        int r = pos.getRow();
        int c = pos.getCol();
        switch(moving_rule[0]){
        case 'U' : r--; break;
        case 'D' : r++; break;
        case 'L' : c--; break;
        case 'R' : c++; break;
        }
        moving_rule = moving_rule.substr(1) + moving_rule[0];
        if(map -> isValid(Position(r,c), this)) return Position(r,c);
}

Position Watson::getCurrentPosition()const{return pos;}

void Watson::move(){
    pos = this -> getNextPosition();
}
string Watson::str() const{return ;}

//Criminal 
Criminal::Criminal(int index, const Position & init_pos, Map * map, Sherlock * sherlock, Watson * watson)
:MovingObject(index, init_pos, map, name)
{
    
}


//ArrayMovingObject
 ArrayMovingObject::ArrayMovingObject(int capacity){
     this -> capacity = capacity;
     count = 0;
     arr_mv_objs = new MovingObject *[capacity];
 }

 ArrayMovingObject::~ArrayMovingObject(){
    for(int i = 0; i < capacity; i++){
        delete arr_mv_objs[i];
    }
    delete [] arr_mv_objs;
 } //Tạo mảng di chuyển cho các nhân vật
 bool ArrayMovingObject::isFull() const {
    return count == capacity;
 }
 bool ArrayMovingObject::add ( MovingObject * mv_obj ){
    if(isFull()) {return false;}
    arr_mv_objs[count] = mv_obj;
    count++;
    return true;
 }
 int ArrayMovingObject::size() const{} // return current number of elements in the array

 string ArrayMovingObject::str() const{
    string str =  "ArrayMovingObject[count="+to_string(count)+";capacity="+to_string(capacity);
        for (int i = 0; i < count; i++){
            str += arr_mv_objs[i]->str();
        }
        return str;
 }

 Configuration::Configuration(const string & filepath){
    ifstream file(filepath);
    string line;
    while(file.eof() == false){
        getline(file,line);
        Takedata(line);
    }
    file.close();
 } //Tạo cấu hình cho chương trình
 void Configuration::Takedata(string line){
        string name = line.substr(0, line.find('='));
        string data = line.substr(line.find('=') + 1, line.length() - name.length());

        if (name == "MAP_NUM_ROWS"){map_num_rows = stoi(data);}
        else if (name == "MAP_NUM_COLS"){map_num_cols = stoi(data);}
        else if (name == "MAX_NUM_MOVING_OBJECTS"){max_num_moving_objects = stoi(data);}
        else if (name == "NUM_WALLS"){num_walls = stoi(data);}
        else if (name == "ARRAY_WALLS"){
            int count = 0;
            for (int i = 0; i < data.length(); i++){
                if(data[i] == '(') {count++;}
            }
        }
        else if (name == "NUM_FAKE_WALLS"){num_fake_walls = stoi(data);}
        else if (name == "ARRAY_FAKE_WALLS"){
            int count = 0;
            for (int i = 0; i < data.length(); i++){
                if(data[i] == '(') {count++;}
            }
         }
        else if (name == "SHERLOCK_MOVING_RULE"){sherlock_moving_rule = stoi(data);}
        else if (name == "SHERLOCK_INIT_POS"){sherlock_init_pos = Position(data);}
        else if (name == "SHERLOCK_INIT_HP"){sherlock_init_hp = stoi(data);}
        else if (name == "SHERLOCK_INIT_EXP"){sherlock_init_exp = stoi(data);}
        else if (name == "WATSON_MOVING_RULE"){watson_moving_rule = stoi(data);}
        else if (name == "WATSON_INIT_POS"){watson_init_pos = Position(data);}
        else if (name == "WATSON_INIT_HP"){watson_init_hp = stoi(data);}
        else if (name == "WATSON_INIT_EXP"){watson_init_exp = stoi(data);}
        else if (name == "CRIMINAL_INIT_POS"){criminal_init_pos = Position(data);}
        else if (name == "NUM_STEPS"){num_steps = stoi(data);}
 }
 Configuration::~Configuration(){}
 
 string Configuration::str() const{
    return "Configuration[MAP_NUM_ROWS=" + to_string(map_num_rows) +
    "\nMAP_NUM_COLS="+  to_string(map_num_cols)+
    "\nMAX_NUM_MOVING_OBJECTS=" + to_string(max_num_moving_objects)+
    "\n ARRAY_WALLS=" + to_string(arr_walls);
 }

 Robot::Robot (RobotType rb_type) : robot_type(rb_type){} //Tạo robot
 RobotType Robot::getType() const {return robot_type;}
 RobotC::RobotC ( int index , const Position & init_pos , Map * map ,RobotType robot_type , Criminal * criminal ){
    criminal = criminal;
 }

 RobotS::RobotS( int index , const Position & init_pos , Map * map ,RobotType robot_type , Criminal * criminal , Sherlock * sherlock){
    criminal = criminal;
    sherlock = sherlock;
 }

 int Robot::RobotW ( int index , const Position & init_pos , Map * map ,RobotType robot_type , Criminal * criminal , Watson * watson ){
    criminal = criminal;
    watson = watson;
 }

 int Robot::RobotSW( int index,  const Position & init_pos , Map * map ,RobotType robot_type , Criminal * criminal , Sherlock * sherlock , Watson* watson ){
    watson = watson;


 }

StudyPinkProgram::StudyPinkProgram(const string & config_file_path){}
bool StudyPinkProgram::isStop()const{}


////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////

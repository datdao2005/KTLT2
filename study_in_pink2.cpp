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
            delete map[i];
            for (int j = 0; i < num_cols; j++){
                delete map[i][j];
            }
        }
        delete [] map;
    }

bool Map::isValid ( const Position & pos , MovingObject * mv_obj ) const {
    if (pos == npos) {return false;}
}

 static const Position npos = Position(-1, -1); //Điểm trả về khi input không hợp lệ 
     Position::Position(int r=0, int c=0){
         r = r;
         c = c;
     }
    

     int Position::getRow() const{return r;}
     int Position::getCol() const {return c;}
     void Position::setRow(int r) { r = r;}
     void Position::setCol(int c) { c = c;}

     bool Position::isEqual(Position &pos1, Position &pos2){
    return pos1.getRow() == r &&  pos1.getCol() == c;
        
        //return pos1.getRow() == r && pos1.getCol() == c && pos2.getRow() == r && pos2.getCol() == c;
     }
     bool Position::isEqual(int in_r, int in_c)const{
        return in_r ==r && in_c == c;
     }
      Position::Position(const string & str_pos){
        this -> r = stoi(str_pos.substr(1, str_pos.find(',' - 1)));
        this -> c = stoi(str_pos.substr());
      }
     string Position::str() const{return "(" + to_string(r) + "," +to_string(c) + ")";}


MovingObject :: MovingObject(int index, const Position pos, Map * map, const string & name=""){
        this -> index = index;
        this -> pos = pos;
        this -> map = map;
        this -> name = name;
}

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

    Position Sherlock::getNextPosition(){return pos;}
    Position Sherlock::getCurrentPosition()const{return pos;}
void Sherlock::move(){
     Position new_position = getNextPosition();
      if (new_position != Position::npos) {
        pos = new_position;}
}
 string Position::toString() const {
    return "(" + to_string(getRow()) + "," + to_string(getCol()) + ")";}
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
Position Watson::getNextPosition(){}
Position Watson::getCurrentPosition()const{}

void Watson::move(){}
string Watson::str() const{return ;}

//Criminal 
Criminal::Criminal(int index, const Position & init_pos, Map * map, Sherlock * sherlock, Watson * watson)
:MovingObject(index, init_pos, map, name)
{
      
}


 ArrayMovingObject::ArrayMovingObject(int capacity){
     
 }

 ArrayMovingObject::~ArrayMovingObject(){} //Tạo mảng di chuyển cho các nhân vật
 bool ArrayMovingObject::isFull() const {
    return count == capacity;
 }
 bool ArrayMovingObject::add ( MovingObject * mv_obj ){}
 int ArrayMovingObject::size() const{} // return current number of elements in the array

 string ArrayMovingObject::str() const{return "ArrayMovingObject[count="+to_string(count)+";capacity="+to_string(capacity);}/*
 chưa đủ hết, phải thêm vào return phần obj*/

 Configuration::Configuration(const string & filepath){
    string myfile;
    ifstream Readfile(filepath);
    Readfile.close();
 } //Tạo cấu hình cho chương trình
 Configuration::~Configuration(){}
 
 string Configuration::str() const{
    return "Configuration[MAP_NUM_ROWS=" + to_string(map_num_rows) +
    "\nMAP_NUM_COLS="+  to_string(map_num_cols)+
    "\nMAX_NUM_MOVING_OBJECTS=" + to_string(max_num_moving_objects)+
    "\n ARRAY_WALLS="+ to_string(arr_walls);
 }

 Robot::Robot (RobotType rb_type) : robot_type(rb_type){} //Tạo robot
 RobotType Robot::getType() const {return robot_type;}
 int Robot::RobotC ( int index , const Position & init_pos , Map * map ,RobotType robot_type , Criminal * criminal ){}

 int Robot::RobotS( int index , const Position & init_pos , Map * map ,RobotType robot_type , Criminal * criminal , Sherlock * Sherlock ){}

 int Robot::RobotW ( int index , const Position & init_pos , Map * map ,RobotType robot_type , Criminal * criminal , Watson * watson ){}

 int Robot::RobotSW( int index,  const Position & init_pos , Map * map ,RobotType robot_type , Criminal * criminal , Sherlock * sherlock , Watson* watson ){}

StudyPinkProgram::StudyPinkProgram(const string & config_file_path){}
bool StudyPinkProgram::isStop()const{}


////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
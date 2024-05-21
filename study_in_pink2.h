/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 1
* Programming Fundamentals Spring 2023
* Author: Vu Van Tien
* Date: 02.02.2023
*/

//The library here is concretely set, students are not allowed to include any other libraries.
#ifndef _H_STUDY_IN_PINK_2_H_
#define _H_STUDY_IN_PINK_2_H_

#include "main.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Forward declaration
 class MovingObject;
 class Position;
 class Configuration;
 class Map;

 class Criminal;
 class RobotS;
 class RobotW;
 class RobotSW;
 class RobotC;

 class ArrayMovingObject;
 class StudyPinkProgram;

class BaseItem;
class BaseBag;
class SherlockBag;
 class WatsonBag;

class TestStudyInPink;

enum ItemType { MAGIC_BOOK, ENERGY_DRINK, FIRST_AID, EXCEMPTION_CARD, PASSING_CARD };
enum ElementType { PATH, WALL, FAKE_WALL };
enum RobotType { C=0, S, W, SW };

class MapElement {
protected:
    ElementType type;
public:
    MapElement(ElementType in_type);
    virtual ~MapElement() = 0;
    virtual ElementType getType() const;
    
};

class Path : public MapElement {
    public:
    Path();
};


class Wall : public MapElement {
    public:
    Wall();
};

class FakeWall : public MapElement {
    private:
    int req_exp;
    public:
    FakeWall(int in_req_exp);
    int getReqExp() const;
};

class Map {
private:
    int num_rows, num_cols;
        MapElement *** map;
public:
    Map(int num_rows, int num_cols, int num_walls, Position * array_walls, int num_fake_walls, Position * array_fake_walls) 
    : num_rows(num_rows), num_cols(num_cols){}
    ~Map();
    
    
    bool isValid (const Position &pos , MovingObject *mv_obj) const ;
};

class Position {
private:
    int r, c;
public:
    static const Position npos;

    Position(int r=0, int c=0);

    Position(const string & str_pos);

    int getRow() const;
    int getCol() const;
    void setRow(int r);
    void setCol(int c);

    string str() const;

    bool isEqual(const Position &other) const;
     int distance (Position pos) const;
};

class MovingObject {
protected:
    int index;
    Position pos;
    Map * map;
    string name;

public:
    MovingObject(int index, const Position pos, Map * map, const string & name="");
    virtual ~MovingObject();
     Position getNextPosition();
    Position getCurrentPosition() const;
    virtual void move() = 0;
    virtual string str() const = 0;
    string getCharacter();
   
};

class Character : public MovingObject{
    public:
    Character(int index, const Position pos, Map * map, const string & name);
    virtual ~Character(){}
    virtual int getExp() const = 0;
    virtual int getHp() const = 0;
    virtual void setExp(int Exp) = 0;
    virtual void setHp(int Hp) = 0;
};

class Sherlock : public Character {
private:
    // TODO
   string moving_rule;
   Map *map;
   int index = 0;
   Position init_pos;
   int init_hp, init_exp;
public:
        Position getNextPosition();
       Position getCurrentPosition() const;
        void move();
       string str() const;
       string name;
       int getExp()const;
       int getHp()const;
       void setExp(int Exp);
       void setHp(int Hp);
    Sherlock(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp);
    ~Sherlock(){}
    // getNextPosition
    // move
    // str
    // ...
};

class Watson : public Character {
private:
    // TODO
    string moving_rule;
   Map *map;
   int index;
   Position init_pos;
   int init_hp;
   int init_exp;
public:
     Position getNextPosition();
       Position getCurrentPosition() const;
        void move();
       string str() const;
       string name;
       int getExp()const;
       int getHp()const;
       void setExp(int Exp);
       void setHp(int Hp);
    Watson(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp);
    // getNextPosition
    // move
    // str
    // ...
};

class Criminal : public Character {
private:
    // TODO
    string moving_rule;
    int index;
    Position init_pos;
    Map * map;
    Sherlock * sherlock;
    Watson * watson;
    Position last_pos = Position::npos;
public:
    Position getNextPosition();
    Position getCurrentPosition() const;
    Position getLastPosition();
        void move();
       string str() const;
       string name;
       int getExp()const;
       int getHp()const;
       void setExp(int Exp);
       void setHp(int Hp);
       bool Caught();
    Criminal(int index, const Position & init_pos, Map * map, Sherlock * sherlock, Watson * watson);
    // getNextPosition
    // move
    // str
    // ...
};

class ArrayMovingObject {
private:
    // TODO
   int capacity, count;
   MovingObject **arr_mv_objs;
public:
    ArrayMovingObject(int capacity);
    ~ArrayMovingObject() ;
    bool isFull() const;
    bool add(MovingObject * mv_obj);
    MovingObject * get(int index) const;
    int size() const; // return current number of elements in the array
    string str() const;
};

class Configuration {
    friend class StudyPinkProgram;

private:
    // TODO
         int map_num_rows, map_num_cols, max_num_moving_objects, num_walls, num_fake_walls;
         Position* arr_walls = new Position[1000];
         Position* arr_fake_walls = new Position[1000];
         string sherlock_moving_rule;
         Position sherlock_init_pos;
         int sherlock_init_hp, sherlock_init_exp;
         string watson_moving_rule;
         Position watson_init_pos;
         int watson_init_hp, watson_init_exp;
         Position criminal_init_pos;
         int num_steps;
public:
    Configuration(const string & filepath);
    ~Configuration();
    string str() const;
    void Takedata(string line);
    int takeNumsteps();
    Map drawMap();
    Position getSherlockInitPos() const;
    string getSherlockMovingRule() const;
    int getSherlockInitHp() const;
    int getSherlockInitExp() const;
    Position getWatsonInitPos() const;
    string getWatsonMovingRule() const;
    int getWatsonInitHp() const;
    int getWatsonInitExp() const;
    Position getCriminalInitPos() const;
    int getMaxNumMovingObjects() const;
    
};

// Robot, BaseItem, BaseBag,...
class Robot : public MovingObject{
    protected:
     RobotType robot_type;
     BaseItem *item;
     Criminal *criminal;
     Position initPos;
    public:
    Robot(int index, const Position &pos, Map *map, Criminal *criminal);
    Robot (RobotType in_rb_type);
    virtual ~Robot(){};
    virtual RobotType getType() const;
     virtual int getDistance() const = 0;
    virtual int getDistance(Sherlock * sherlock) const = 0;
    virtual int getDistance(Watson * watson) const = 0;
    string str() const;
    BaseItem *createItem();
    void setItem();
    BaseItem *takeItem();
    int getExp()const;
    void move();
};

class RobotC : public Robot {
    Criminal *criminal;
    public:
    RobotC ( int index, const Position & init_pos, Map *map, Criminal *criminal);
    Position getNextPosition();
    int getDistance (Sherlock *sherlock) const;
    int getDistance(Watson *watson)const;
    int getDistance() const;
    
};

class RobotS : public Robot {
    Criminal *criminal;
    Sherlock *sherlock;
    public:
   RobotS (int index, const Position & init_pos, Map *map , Criminal *criminal , Sherlock *sherlock);
   int getDistance() const;
    int getDistance (Sherlock *sherlock) const;
    int getDistance(Watson *watson)const;
   Position getNextPosition();
  
};

class RobotW : public Robot {
    Criminal *criminal;
    Watson *watson;
    public:
    RobotW ( int index , const Position & init_pos , Map *map, Criminal *criminal , Watson *watson);
    int getDistance() const;
    int getDistance (Sherlock *sherlock) const;
    int getDistance(Watson *watson)const;
    Position getNextPosition();
    
};

class RobotSW : public Robot {
    Sherlock *sherlock;
    Watson *watson;
    Criminal *criminal;
    public:
    RobotSW(int index, const Position &init_pos, Map *map, Criminal *criminal, Sherlock *sherlock, Watson *watson);
    int getDistance() const;
    int getDistance(Sherlock *sherlock)const;
    int getDistance(Watson *watson)const;
    Position getNextPosition();

};
//Vật phẩm
class BaseItem {
    friend class TestStudyPink;
private:
    RobotType robot_type;
    ItemType item;
    public: 
     BaseItem(ItemType item);
    virtual bool canUse ( Character * obj , Robot * robot ) = 0;
    virtual void use ( Character * obj , Robot * robot ) = 0;
    ItemType getType();
};

//Các nhân vật


//Vật phẩm
class MagicBook : public BaseItem{
    public:
    MagicBook();
    bool canUse(Character *obj, Robot *robot);
    void use ( Character * obj, Robot *robot);
};
class EnergyDrink : public BaseItem{
    public:
    EnergyDrink();
    bool canUse(Character *obj, Robot *robot);
    void use(Character * obj, Robot *robot);
};
class FirstAid : public BaseItem{
    public:
    FirstAid();
     bool canUse(Character *obj, Robot *robot);
    void use(Character * obj, Robot *robot);
};
class ExcemptionCard : public BaseItem{
    public:
    ExcemptionCard();
     bool canUse(Character *obj, Robot *robot);
     void use(Character * obj, Robot *robot);
};
class PassingCard : public BaseItem{
    private:
    string challenge;
    public:
    PassingCard(string challenge);
     bool canUse(Character *obj, Robot *robot);
     void use(Character * obj, Robot *robot);
};

//Túi đồ 
struct Node{
    BaseItem* item;
    Node* next;
    Node(BaseItem* item);
};

class BaseBag{
        friend class TestStudyPink;
    protected:
    int count;
    Node *head;
    Character *obj;
    public:
     BaseBag(Character* obj);
    virtual ~BaseBag();
    virtual bool insert(BaseItem* item);
    virtual BaseItem* get(ItemType itemType);
    virtual BaseItem* get();
    virtual bool find(ItemType itemType);
    virtual string str() const;
    virtual int getNumItem() const;
};


 class SherlockBag : public BaseBag{
    public:
    SherlockBag(Sherlock* sherlock);
     bool insert(BaseItem* item) override;
 };
 class WatsonBag : public BaseBag{
    public:
    WatsonBag(Watson* watson);
     bool insert(BaseItem* item) override;
 };

class StudyPinkProgram {
private:
    // Sample attributes
    Configuration * config;
    Sherlock * sherlock;
    Watson * watson;
    Criminal * criminal;
    SherlockBag *sherlockBag;
    WatsonBag *watsonBag;
    Map * map;
    ArrayMovingObject * arr_mv_objs;


public:
    StudyPinkProgram(const string & config_file_path);

    bool isStop() const;

    void printResult() const {
        if (sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition())) {
            cout << "Sherlock caught the criminal" << endl;
        }
        else if (watson->getCurrentPosition().isEqual(criminal->getCurrentPosition())) {
            cout << "Watson caught the criminal" << endl;
        }
        else {
            cout << "The criminal escaped" << endl;
        }
    }

    void printStep(int si) const {
        cout << "Step: " << setw(4) << setfill('0') << si
            << "--"
            << sherlock->str() << "--|--" << watson->str() << "--|--" << criminal->str() << endl;
    }

    void run(bool verbose);

    ~StudyPinkProgram();
};

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* _H_STUDY_IN_PINK_2_H_ */

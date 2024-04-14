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
// class MovingObject;
// class Position;
// class Configuration;
// class Map;

// class Criminal;
// class RobotS;
// class RobotW;
// class RobotSW;
// class RobotC;

// class ArrayMovingObject;
// class StudyPinkProgram;

// class BaseItem;
// class BaseBag;
// class SherlockBag;
// class WatsonBag;

class TestStudyInPink;

enum ItemType { MAGIC_BOOK, ENERGY_DRINK, FIRST_AID, EXCEMPTION_CARD, PASSING_CARD };
enum ElementType { PATH, WALL, FAKE_WALL };
enum RobotType { C, S, W, SW };

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
    Path(): MapElement(PATH){}
    ~Path(){}
};


class Wall : public MapElement {
    public:
    Wall():MapElement(WALL){}
    ~Wall(){}
};

class FakeWall : public MapElement {
    private:
    int req_exp;
    public:
    FakeWall(int in_req_exp);
    FakeWall():MapElement(FAKE_WALL){}
    int getReqExp () const ; 
    ~FakeWall(){}
};

class Map {
private:
    int num_rows, num_cols;
        MapElement *** map;
public:
    Map(int num_rows, int num_cols, int num_walls, Position * array_walls, int num_fake_walls, Position * array_fake_walls) 
    : num_rows(num_rows), num_cols(num_cols){}
    ~Map();
    
    
    bool isValid ( const Position & pos , MovingObject * mv_obj ) const ;
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

    bool isEqual(MovingObject *mv_obj, Position &position);
    bool isEqual(int in_r, int in_c) const;
     string toString() const;
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
    virtual Position getNextPosition() = 0;
    Position getCurrentPosition() const;
    virtual void move() = 0;
    virtual string str() const = 0;
    string getCharacter ();
    
};

class Sherlock : public MovingObject {
private:
    // TODO
   string moving_rule;
   Map *map;
   int index;
   Position init_pos;
   int init_hp;
   int init_exp;
public:
        Position getNextPosition() = 0;
       Position getCurrentPosition() const{}
        void move() = 0;
       string str() const = 0;
       string name;
    Sherlock(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp);
    
    // getNextPosition
    // move
    // str
    // ...
   Position getNextPosition();
   void move();
   string str()const ;

};

class Watson : public MovingObject {
private:
    // TODO
    string moving_rule;
   Map *map;
   int index;
   Position init_pos;
   int init_hp;
   int init_exp;
public:
     Position getNextPosition() = 0;
       Position getCurrentPosition() const{}
        void move() = 0;
       string str() const = 0;
       string name;
    Watson(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp);
    // getNextPosition
    // move
    // str
    // ...
};

class Criminal : public MovingObject {
private:
    // TODO
    int index;
    const Position & init_pos;
    Map * map;
    Sherlock * sherlock;
    Watson * watson;
public:
    Position getNextPosition() = 0;
       Position getCurrentPosition() const{}
        void move() = 0;
       string str() const = 0;
       string name;
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
         Position arr_walls;
         Position arr_fake_walls;
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
};

// Robot, BaseItem, BaseBag,...
class Robot : public MovingObject{
    protected:
     RobotType robot_type;
     BaseItem *item;
     public:
    Robot (RobotType in_rb_type);
    virtual ~Robot() = 0;
    virtual RobotType getType() const;
   
    int RobotW ( int index , const Position & init_pos , Map * map ,RobotType robot_type , Criminal * criminal , Watson * watson ) ;
    int RobotSW( int index,  const Position & init_pos , Map * map ,RobotType robot_type , Criminal * criminal , Sherlock * sherlock , Watson* watson );
};

//Vật phẩm
class BaseItem {
    public: 
    virtual bool canUse ( Character * obj , Robot * robot ) = 0;
    virtual void use ( Character * obj , Robot * robot ) = 0;
};

//Các nhân vật
class Character : public MovingObject{};
class Sherlock_char : public Character{};
class Watson_char : public Character{};
class Criminal_char : public Character{};

class RobotC : public Robot{
    RobotC *robotC;
    public:
    RobotC (int index, const Position &init_pos, Map *map, RobotType robot_type, Criminal *criminal);
    int getDistance (Sherlock *sherlock);
    int getDistance (Watson *watson);
};
class RobotS : public Robot{
    RobotS(int index, const Position &init_pos, Map *map, RobotType robot_type, Criminal *criminal, Sherlock *sherlock);

};
class RobotW : public Robot{};
class RobotSW : public Robot{};

//Vật phẩm
class MagicBook : public BaseItem{};
class EnergyDrink : public BaseItem{};
class FirstAid : public BaseItem{};
class ExcemptionCard : public BaseItem{};
class PassingCard : public BaseItem{};

//Túi đồ 
class BaseBag{
    Character *obj;
    public:
    virtual bool insert ( BaseItem * item ) ; // return true if insert successfully
    virtual BaseItem * get () ; // return the item as described above , if not found , return NULL
    virtual BaseItem * get ( ItemType itemType ) ; // return the item as described above , if not found , return NULL
    virtual string str () const ;
};

 class SherlockBag : public BaseBag{};
 class WatsonBag : public BaseBag{};

class StudyPinkProgram {
private:
    // Sample attributes
    Configuration * config;
    
    Sherlock * sherlock;
    Watson * watson;
    Criminal * criminal;
    
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

    void run(bool verbose) {
        // Note: This is a sample code. You can change the implementation as you like.
        // TODO
        for (int istep = 0; istep < config->num_steps; ++istep) {
            for (int i = 0; i < arr_mv_objs->size(); ++i) {
                arr_mv_objs->get(i)->move();
                if (isStop()) {
                    printStep(istep);
                    break;
                }
                if (verbose) {
                    printStep(istep);
                }
            }
        }
        printResult();
    }

    ~StudyPinkProgram();
};

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* _H_STUDY_IN_PINK_2_H_ */

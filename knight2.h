
#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

enum ItemType { ANTIDOTE = 0, PHOENIXI, PHOENIXII, PHOENIXIII, PHOENIXIV };
class BaseBag;
class Events;
class BaseOpponent;
class BaseItem;
struct  ITEM
{
    string itemname;
    ITEM* nextitem;
};
struct LIST
{
    ITEM* head;
};

enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
class BaseKnight {
protected:
    float knightBaseDamage=0;
    int id;
    int maxhp;
    int hp;
    int level;
    int gil;
    int antidote;
    int phoenixdownI;
    int damage=hp*level*knightBaseDamage;
    BaseBag * bag=nullptr;
    KnightType knightType;

public:
    KnightType getType() {
        return knightType;
    }
    void setHp(int hp){
        this->hp=hp;
    }
    void setGil(int gil){
        this->gil=gil;
    }
    void setAntidote(int antidote){
        this->antidote=antidote;
    }
    void setPhoenixdownI(int phoenixdownI){
        this->phoenixdownI=phoenixdownI;
    }
    void sendgil(int &n){
        gil+=n;
        if (gil>999) {
            n=gil-999;
            gil=999;            
        }
        else n=0;
    }
    float getBaseDame(){
        return knightBaseDamage;
    }
    int getDamage(){
        return damage;
    }
    int getID() {
        return id;
    };
    int getHp() {
        return hp;
    };
    BaseBag* getBag(){
        return bag;
    }
    int getMaxHp() {
        return maxhp;
    };
    int getLevel() {
        return level;
    };
    int getGil() {
        return gil;
    };
    int getAntidote() {
        return antidote;
    };
    int getPhoenixdownI() {
        return phoenixdownI;
    };
    bool sendItem(ITEM* item);
    bool fight(BaseOpponent* opponent, int& gilsum, bool &omega, bool &hades, bool &winhades,bool &shield, bool &spear, bool &hair,bool &sword, ITEM* &item);
    static BaseKnight* create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
};
class PaladinKnight : public BaseKnight {
public:
    PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI) {
        this->knightBaseDamage=0.06;
        this->id = id;
        this->maxhp = maxhp;
        this->hp=maxhp;
        this->level = level;
        this->gil = gil;
        this->antidote = antidote;
        this->phoenixdownI = phoenixdownI;
        this->knightType = PALADIN;
    };
};
class LancelotKnight : public BaseKnight {
public:
    LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI) {
        this->knightBaseDamage=0.05;
        this->id = id;
        this->maxhp = maxhp;
        this->hp=maxhp;
        this->level = level;
        this->gil = gil;
        this->antidote = antidote;
        this->phoenixdownI = phoenixdownI;
        this->knightType = LANCELOT;
    };
};
class DragonKnight : public BaseKnight {
public:
    DragonKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI) {
        this->knightBaseDamage=0.075;
        this->id = id;
        this->maxhp = maxhp;
        this->hp=maxhp;
        this->level = level;
        this->gil = gil;
        this->antidote = antidote;
        this->phoenixdownI = phoenixdownI;
        this->knightType = DRAGON;
    };
};
class NormalKnight : public BaseKnight {
protected:
public:
    NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI) {
        this->id = id;
        this->maxhp = maxhp;
        this->hp=maxhp;
        this->level = level;
        this->gil = gil;
        this->antidote = antidote;
        this->phoenixdownI = phoenixdownI;
        this->knightType = NORMAL;
    };
};










class BaseBag {
protected:
    int count_item=0;
    LIST l;
    BaseKnight * knight;
    int max_items;
    int a=0,b=0;
public:
    BaseBag(BaseKnight* knight, int phoenixdownI, int antidote);
    ~BaseBag();
    bool usePhoenix();
    void useAntidote();
    virtual bool insertFirst(BaseItem* item);
    virtual BaseItem * get(ItemType itemType);
    virtual string toString() const;
    void delete3item();
};











class ArmyKnights {
protected:
    int count_knight;
    bool hasShield=false;
    bool hasSpear=false;
    bool hasHair=false;
    bool hasExcalibur=false;
    BaseKnight** army;
public:
    ArmyKnights(const string& file_armyknights);
    ~ArmyKnights() {
        delete[] army;
    };
    bool fight(BaseOpponent* opponent, bool &omega, bool &hades, bool &winhades,bool &shield, bool &spear, bool &hair,bool &sword);
    bool adventure (Events * events);
    int count() const;
    BaseKnight* lastKnight() const;

    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;

    void printInfo() const;
    void printResult(bool win) const;
};



class Events {
protected:
    int count_event;
    int i;//mã sự kiện
    int* events;

public:
    Events(const string& file_events);
    ~Events() {
        delete[] events;
    };
    int count() const;
    int get(int i) const;
};



class BaseOpponent{
    protected:
    int baseDamaged;
    int levelO;
    int gil;
    int evenid;
    public:
    virtual void setlevelO(int i, int even_id){
        levelO=(i+even_id)%10+1;
    }
    virtual int getgil(){
        return gil;
    }
    virtual int getDamaged(){
        return baseDamaged;
    }
    virtual int get_evenid(){
        return evenid;
    }
    virtual int getLevelO(){
        return levelO;
    }
};
class MadBear: public BaseOpponent{
    public:
    MadBear(){
        this->baseDamaged=10;
        this->gil=100;
        this->evenid=1;
    }
    

};
class Bandit: public BaseOpponent{
    public:
    Bandit(){
        this->baseDamaged=15;
        this->gil=150;
        this->evenid=2;
    }
};
class LordLupin: public BaseOpponent{
    public:
    LordLupin(){
        this->baseDamaged=45;
        this->gil=450;
        this->evenid=3;
    }
};
class Elf: public BaseOpponent{
    public:
    Elf(){
        this->baseDamaged=75;
        this->gil=750;
        this->evenid=4;
    }
};
class Troll: public BaseOpponent{
    public:
    Troll(){
        this->baseDamaged=95;
        this->gil=800;
        this->evenid=5;
    }
};
class Tornbery: public BaseOpponent{
    public:
    Tornbery(){
        this->evenid=6;
    }
};
class Queen : public BaseOpponent{
    public:
    Queen(){
        this->evenid=7;
    }
};
class NinaDeRings : public BaseOpponent{
    public:
    NinaDeRings(){
        this->evenid=8;
    }
};
class VuonSauRieng : public BaseOpponent{
    public:
    VuonSauRieng(){
        this->evenid=9;
    }
};
class Omega : public BaseOpponent{
    public:
    Omega(){
        this->evenid=10;
    }
};
class Hades : public BaseOpponent{
    public:
    Hades(){
        this->evenid=11;
    }
};
class GetPhoenixII : public BaseOpponent{
    public:
    GetPhoenixII(){
        this->evenid=112;
    }
};
class GetPhoenixIII : public BaseOpponent{
    public:
    GetPhoenixIII(){
        this->evenid=113;
    }
};
class GetPhoenixIV : public BaseOpponent{
    public:
    GetPhoenixIV(){
        this->evenid=114;
    }
};
class getShieldPaladin : public BaseOpponent{
    public:
    getShieldPaladin(){
        this->evenid=95;
    }
};
class getSpearLancelot : public BaseOpponent{
    public:
    getSpearLancelot(){
        this->evenid=96;
    }
};
class getHairGuinevere : public BaseOpponent{
    public:
    getHairGuinevere(){
        this->evenid=97;
    }
};
class getExcalibur: public BaseOpponent{
    public:
    getExcalibur(){
        this->evenid=98;
    }
};
class Ultimecia : public BaseOpponent{
    protected:
    int maxhp=5000;
    int hp=maxhp;
    public:
    Ultimecia(){
        this->evenid=99;
    }
    int getMaxhp(){
        return maxhp;
    }
    int getHp(){
        return hp;
    }
    void setHP(int hp){
        this->hp=hp;
    }
};


class BaseItem {
protected:
    ItemType itemtype;
public:
    static BaseItem* create_item(ItemType item);
    ItemType getType() {
        return itemtype;
    }
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
};
class Antidote : public BaseItem {
    public:
    Antidote() {
    this->itemtype = ANTIDOTE;
    }
    bool canUse(BaseKnight*knight){
        KnightType type_k=knight->getType();
        if (type_k==DRAGON) return false;
        else return true;
    }
    void use (BaseKnight * knight){
        int antidote=knight->getAntidote();
        antidote--;
        knight->setAntidote(antidote);
        return;
    }

};
class PhoenixI : public BaseItem {
    public:
    PhoenixI() {
    this->itemtype = PHOENIXI;
    }
    bool canUse(BaseKnight*knight){
        if (knight->getHp()<=0) return true;
        else return false;
    }
    void use(BaseKnight*knight){
        int hp=knight->getMaxHp();
        knight->setHp(hp);
    }
};
class PhoenixII : public BaseItem {
    public:
    PhoenixII() {
    this->itemtype = PHOENIXII;
    }
    bool canUse(BaseKnight*knight){
        if (knight->getHp()<(knight->getMaxHp())/4) return true;
        else return false;
    }
    void use(BaseKnight*knight){
        int hp=knight->getMaxHp();
        knight->setHp(hp);
    }
};
class PhoenixIII : public BaseItem {
    public:
    PhoenixIII() {
    this->itemtype = PHOENIXIII;
    }
    bool canUse(BaseKnight*knight){
        if (knight->getHp()<(knight->getMaxHp())/3) return true;
        else return false;
    }
    void use(BaseKnight*knight){
        int hp=knight->getHp();
        int maxhp=knight->getMaxHp();
        if(hp<=0) hp=maxhp/3;
        else hp+=maxhp/4;
        knight->setHp(hp);
    }
};
class PhoenixIV : public BaseItem {
    public:
    PhoenixIV() {
    this->itemtype = PHOENIXIV;
    }
    bool canUse(BaseKnight*knight){
        if (knight->getHp()<(knight->getMaxHp())/2) return true;
        else return false;
    }
    void use(BaseKnight*knight){
        int hp=knight->getHp();
        int maxhp=knight->getMaxHp();
        if(hp<=0) hp=maxhp/2;
        else hp+=maxhp/5;
        knight->setHp(hp);
    }
};





class KnightAdventure {
private:
    ArmyKnights * armyKnights;
    Events * events;

public:
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string &s);
    void loadEvents(const string &s);
    void run();
};

#endif // __KNIGHT2_H__
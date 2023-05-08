#include "knight2.h"

bool is_prime(int n) {
    int count = 0;
    if (n <= 1) return false;
    if (n > 1) {
        for (int i = 2; i <= n / 2; i++) {
            if (n % i == 0) count++;
        }
    }
    if (count == 0) return true;
    else return false;
}
bool Dragon(int n) {
    if ( (n==345) || (n==354) ) return 1;
    else if ( (n==435) || (n==453) ) return 1;
    else if ( (n==543) || (n==534) ) return 1;
    else return 0;
}
ITEM* create_item(string s){
    ITEM* item= new ITEM;
    item->itemname=s;
    item->nextitem=NULL;
    return item;
}
void khoi_tao(LIST& l){
    l.head=NULL;
}
void insert(LIST& l,ITEM * item){
    if (l.head==NULL) l.head=item;
    else {
        item->nextitem=l.head;
        l.head=item;
    }
}
void deletefirst(LIST& l){
    if (l.head==NULL) return;
    ITEM* temp=l.head;
    l.head=l.head->nextitem;
    delete temp;
}

void deleteItem(LIST& l, string item){
    for (ITEM* i=l.head;i!=NULL;i=i->nextitem){
        if (i->itemname==item) {
            i->itemname=l.head->itemname;
            deletefirst(l);
            break;
        }
    }
}




/* * * BEGIN implementation of class BaseBag * * */


bool BaseBag::insertFirst(BaseItem* item) {
    string s;
    
    if (count_item<max_items){       
        if (item->getType()==0) {
            s="Antidote";
            ITEM* t = create_item(s);
            insert(l,t);
            count_item++;
        }
        else if (item->getType()==1) {
            s="PhoenixI";
            ITEM* t = create_item(s);
            insert(l,t);
            count_item++;
        }
        else if (item->getType()==2) {
            s="PhoenixII";
            ITEM* t = create_item(s);
            insert(l,t);
            count_item++;
        }    
        else if (item->getType()==3) {
            s="PhoenixIII";
            ITEM* t = create_item(s);
            insert(l,t);
            count_item++;
        }
            
        else if (item->getType()==4) {
            s="PhoenixIV";
            ITEM* t = create_item(s);
            insert(l,t);
            count_item++;
        }
        return true;
    }
    return false;
}
BaseItem* BaseBag::get(ItemType itemType){
    string s;
    BaseItem* item;
    if (itemType==0){
        s="Antidote";
        deleteItem(l,s);
        return new Antidote;
    }
        if (itemType==1){
        s="PhoenixI";
        deleteItem(l,s);
        return new PhoenixI;
    }
        if (itemType==2){
        s="PhoenixII";
        deleteItem(l,s);
        return new PhoenixII;
    }
        if (itemType==3){
        s="PhoenixIII";
        deleteItem(l,s);
        return new PhoenixIII;
    }
        if (itemType==4){
        s="PhoenixIV";
        deleteItem(l,s);
        return new PhoenixIV;
    }
    return NULL;
}
BaseBag::BaseBag(BaseKnight* knight, int phoenixdownI, int antidote){
    khoi_tao(l);
    this->knight=knight;
    if (knight->getType()==DRAGON) 
        this->max_items=14;
    else if (knight->getType()==LANCELOT) 
        this->max_items=16;
    else if (knight->getType()==LANCELOT) 
        this->max_items=19;  
    else this->max_items=1000;  
    
    this->a=phoenixdownI;
    this->b=antidote;

    if (a>0) {
        for (int i=0;i<a;i++){
            if (count_item==max_items) break;
            else {
                BaseItem* t= new PhoenixI;
                this->insertFirst(t);
            }
        }
    }
    if (b>0) {
        if (knight->getType()!=DRAGON){
        for (int i=0;i<b;i++){
            if (count_item==max_items) break;
            else {
                BaseItem* t= new Antidote;
                this->insertFirst(t);
            }            
        }
    }
    }
}
void BaseBag::useAntidote(){
    BaseItem* item;
    for (ITEM*i=l.head;i!=NULL;i=i->nextitem){
        if (i->itemname=="Antidote") {
            item =new Antidote;
            if (item->canUse(knight)==true){
                item->use(knight);
                deleteItem(l,"Antidote");
                count_item--;
                delete item;
                break;
            }
        }
    }
}
bool BaseBag::usePhoenix(){
    BaseItem* item;
    for (ITEM* i=l.head;i!=NULL;i=i->nextitem){
        if (i->itemname=="PhoenixI") {
            item=new PhoenixI;
            if (item->canUse(knight)==true) {
                item->use(knight);
                count_item--;
                deleteItem(l,"PhoenixI");
                delete item;
                return true;
                }
        }
        else if (i->itemname=="PhoenixII") {
            item=new PhoenixI;
            if (item->canUse(knight)==true) {
                item->use(knight);
                count_item--;
                deleteItem(l,"PhoenixII");
                delete item;
            }

        }
        else if (i->itemname=="PhoenixIII") {
            item=new PhoenixI;
            if (item->canUse(knight)==true) {
                item->use(knight);
                count_item--;
                deleteItem(l,"PhoenixIII");
                delete item;
                return true;
            }

        }
        else if (i->itemname=="PhoenixIV") {
            item=new PhoenixI;
            if (item->canUse(knight)==true) {
                item->use(knight);
                count_item--;
                deleteItem(l,"PhoenixIV");
                delete item;
                return true;
            }

        }
    }
    return false;   
}

void BaseBag::delete3item(){
    if (l.head==NULL) return;  
    for (int i=0;i<3;i++){
        if (count_item==0) break;
       
            deletefirst(l);
            count_item--;        
    }
}
string BaseBag::toString() const{
    string s("");
    s+="Bag[count="+to_string(count_item)+";";
    for (ITEM* i=l.head;i!=NULL;i=i->nextitem)
    {   
        s+=i->itemname;
        if (i->nextitem!=NULL) s+=",";
    }
    s+="]";
    return s;
}
BaseBag::~BaseBag(){
    ITEM* t;
    while(l.head!=NULL){
        t=l.head;
        l.head=l.head->nextitem;
        delete t;
    }
}
/* * * END implementation of class BaseBag * * */






/* * * BEGIN implementation of class BaseKnight * * */

BaseKnight* BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI) {
    BaseKnight* k;
    if (is_prime(maxhp) == 1) k = new PaladinKnight(id, maxhp, level, gil, antidote, phoenixdownI);
    else if (Dragon(maxhp) == 1) k= new DragonKnight(id, maxhp, level, gil, antidote, phoenixdownI);
    else if (maxhp == 888) k= new LancelotKnight(id, maxhp, level, gil, antidote, phoenixdownI);
    else k = new NormalKnight(id, maxhp, level, gil, antidote, phoenixdownI);
    k-> bag=new BaseBag(k,k->getPhoenixdownI(),k->getAntidote());
    return k;
}
string BaseKnight::toString() const {
    string typeString[4] = { "PALADIN", "LANCELOT", "DRAGON", "NORMAL" };
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id)
        + ",hp:" + to_string(hp)
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
        + "," + bag->toString()
        + ",knight_type:" + typeString[knightType]
        + "]";
    return s;
}
bool BaseKnight::sendItem(ITEM* item){
    if(item->itemname=="PhoenixII"){
        BaseItem* it = new PhoenixII;
        return bag->insertFirst(it);
    }
    else if(item->itemname=="PhoenixIII"){
        BaseItem* it = new PhoenixIII;
        return bag->insertFirst(it);
    }
    else if(item->itemname=="PhoenixIV"){
        BaseItem* it = new PhoenixIV;
        return bag->insertFirst(it);
    }
    return false;
}
bool BaseKnight::fight(BaseOpponent* opponent, int& gilsum, bool &omega, bool &hades, bool &winhades,bool &shield, bool &spear, bool &hair,bool &sword, ITEM* &item){
    bool win=true;
    int levelO;   
    levelO=opponent->getLevelO();
    if (opponent->get_evenid()<=5){       
        if ( (level>=levelO) || (knightType==LANCELOT) || (knightType==PALADIN) )
        {
            gil+=opponent->getgil();
            if (gil>999) {
                gilsum=gil-999;
                gil=999;
            }
            return true;
        }
        else {
            int basedame=opponent->getDamaged();
            hp=hp-basedame*(levelO-level);    
            bag->usePhoenix();  
            if (hp>0) return true;
            else if (hp<=0) {
                if (gil>=100) {
                    gil-=100;
                    hp=maxhp/2;
                    return true;
                }
            }
        }
    }
    else if (opponent->get_evenid()==6){
        if (level>=levelO) {
            level++;
            if (level>10) level=10;
            return true;
        }
        if (knightType==DRAGON) return true;
        else {
            if (antidote>0) {
                bag->useAntidote();
                return true;
            }
            else{                   
                bag->delete3item();
                hp-=10;
                bag->usePhoenix();
                if (hp>0) return true;
                else if (hp<=0) {
                    if (gil>=100) {
                        gil-=100;
                        hp=maxhp/2;
                        return true;
                    }
                }           
            }
        }

    }
    else if (opponent->get_evenid()==7){
        if (level>=levelO) {
            gil*=2;
            if (gil>999){
                gilsum=gil-999;
                gil=999;
            }
        }
        else {
            if (knightType==PALADIN) return true;
            else gil/=2;
        }
        return true;
    }
    else if (opponent->get_evenid()==8){
        if (knightType==PALADIN){
            if (hp<maxhp/3){
                hp+=maxhp/5;
            }
            return true;
        }
        else {
            if (gil<50) {
                return true;
            }
            else {
                if (hp<maxhp/3) {
                    hp+=maxhp/5;
                    gil-=50;
                }
                return true;
            }
        }
    }
    else if (opponent->get_evenid()==9){
        hp=maxhp;
        return true;
    }
    else if (opponent->get_evenid()==10){
        if (omega==true) return true;
        else {
            omega=true;
            if ( ((level==10) && (hp==maxhp)) || (knightType==DRAGON)){
                level=10;
                gil=999;
                return true;
            }
            else {
                hp=0;
                bag->usePhoenix();
                if (hp>0) return true;
                else if (hp<=0) {
                    if (gil>=100){
                        hp=maxhp/2;
                        gil-=100;
                        return true;
                    }
                }
            }
        }
    }
    else if (opponent->get_evenid()==11){
        if (hades==true) return true;
        else {
            hades=true;
            if ( (level==10) || ( (level>=8) && (knightType==PALADIN) ) ){
                winhades=true;
                return true;
            }
            else {
                hp=0;
                bag->usePhoenix();
                if (hp>0) return true;
                else if (hp<=0) {
                    if (gil>=100){
                        hp=maxhp/2;
                        gil-=100;
                        return true;
                    }
                }
            }
        }
    }
    else if (opponent->get_evenid()==112){
        BaseItem* phoenix2= new PhoenixII;
        if(bag->insertFirst(phoenix2)==false){
            item=create_item("PhoenixII");
        }
        return true;
    }
    else if (opponent->get_evenid()==113){
        BaseItem* phoenix3= new PhoenixII;
        if(bag->insertFirst(phoenix3)==false){
            item=create_item("PhoenixIII");
        }
        return true;
    }
    else if (opponent->get_evenid()==114){
        BaseItem* phoenix4= new PhoenixII;
        if(bag->insertFirst(phoenix4)==false){
            item=create_item("PhoenixIV");
        }
        return true;
    }
    else if (opponent->get_evenid()==95){
        shield=true;
        return true;
    }
    else if (opponent->get_evenid()==96){
        spear=true;
        return true;
    }
    else if (opponent->get_evenid()==97){
        hair=true;
        return true;
    }
    else if (opponent->get_evenid()==98){
        if ((spear==true) && (shield==true) && (hair==true)) {
            sword=true;
            }
        return true;
    }
    return false;
}


/* * * END implementation of class BaseKnight * * */







/* * * BEGIN implementation of class ArmyKnights * * */
ArmyKnights::ArmyKnights(const string& file_armyknights) {
    int id = 1;
    ifstream input(file_armyknights);
    input >> count_knight;
    int maxhp, level, phoenixdownI, gil, antidote;
    army = new BaseKnight * [count_knight];
    for (int i = 0; i < count_knight; i++) {
        input >> maxhp >> level >> phoenixdownI >> gil >> antidote;
        army[i] = BaseKnight::create(id, maxhp, level, gil, antidote, phoenixdownI);
        id++;
    }
    input.close();
}
bool ArmyKnights::hasExcaliburSword() const{
    return this->hasExcalibur;
}
bool ArmyKnights::hasGuinevereHair() const{
    return this->hasHair;
}
bool ArmyKnights::hasLancelotSpear() const{
    return this->hasSpear;
}
bool ArmyKnights::hasPaladinShield() const{
    return this->hasShield;
}
BaseKnight* ArmyKnights::lastKnight() const {
    if (count_knight<=0) return NULL;
    else return army[count_knight - 1];
}
int ArmyKnights::count() const {
    return count_knight;
}
void ArmyKnights::printInfo() const {
    
    cout << "No. knights: " << this->count();
    if (this->count() > 0) {
        BaseKnight* lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout<< ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << endl 
        << string(50,'-') << endl;
}
bool ArmyKnights::fight(BaseOpponent* opponent, bool &omega, bool &hades, bool &winhades,bool &shield, bool &spear, bool &hair,bool &sword){

    bool win=true;

    ITEM*item=NULL;
    int gilsum=0;
    if (opponent->get_evenid()!=99){
        while (count_knight>0){
            BaseKnight*k=lastKnight();
            if (k->fight(opponent,gilsum,omega,hades,winhades,shield,spear,hair,sword,item)==true)
            {   
                win=true;
                if (gilsum>0)
                for(int i=count_knight-2;i>=0;i--){
                    army[i]->sendgil(gilsum);
                    if(gilsum==0) break;
                }
                if (winhades==true) hasShield==true;
                if (item!=NULL) {
                    for (int i=count_knight-2;i>=0;i--){
                        if(army[i]->sendItem(item)==true){
                            item=NULL;
                            break;
                        }
                    }
                    item=NULL;
                }
                if (shield==true) hasShield=true;
                if (spear==true) hasSpear=true;
                if (hair==true) hasHair=true;
                if (sword==true) hasExcalibur=true;
                break;
            }
            else {
                win=false;
                count_knight--;
            }
        }
    }

    return win;
    
}
void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}
bool ArmyKnights::adventure(Events* events){
    BaseOpponent* opponent;
        bool shield=false;
        bool spear=false;
        bool hair=false;
        bool sword=false;
        bool omega=false;
        bool hades=false;
        bool winhades=false;
        bool win;
    for (int i=0;i<events->count();i++){
        int id=events->get(i);
        switch (id)
        {
        case 1:
        {    
            opponent=new MadBear;   
            break;        
        }
        case 2:
        {    
            opponent=new Bandit;
            break;
        }
        case 3:
        {    
            opponent=new LordLupin;
            break;
        }
        case 4:
        {    
            opponent=new Elf;
            break;
        }
        case 5:
        {
            opponent=new Troll;
            break;
        }
        case 6:
        {
            opponent=new Tornbery;
            break;
        } 
        case 7:
        {
            opponent=new Queen;
            break;
        } 
        case 8:
        {
            opponent=new NinaDeRings;
            break;
        }
        case 9:
        {
            opponent=new VuonSauRieng;
            break;
        }
        case 10:
        {
            opponent=new Omega;
            break;
        } 
        case 11:
        {
            opponent=new Hades;
            break;
        }
        case 112:
        {
            opponent=new GetPhoenixII;
            break;
        }  
        case 113:
        {
            opponent=new GetPhoenixIII;
            break;
        }  
        case 114:
        {
            opponent=new GetPhoenixIV;
            break;
        }  
        case 95:
        {   
            opponent=new getShieldPaladin;
            break;
        } 
        case 96:
        {
            opponent=new getSpearLancelot;
            break;
        }     
        case 97:
        {
            opponent=new getHairGuinevere;
            break;
        }
        case 98:
        {
            opponent=new getExcalibur;
            break;
        } 
        default : {break;}          
        }
        if ((id==99)&&(count_knight>0)){
            Ultimecia* boss = (Ultimecia*)&opponent;
            int maxhp_boss=boss->getMaxhp();
            int hp_boss=maxhp_boss;
            int damage;
            if (hasExcalibur==true) win=true;
            else if ((hasSpear==true)&&(hasShield==true)&&(hasHair==true)){
                for (int i=count_knight-1;i>=0;i--){
                    if (army[i]->getType()!=NORMAL){
                        damage=army[i]->getDamage();
                        hp_boss-=damage;
                        if (hp_boss<=0) {
                            win=true;
                            this->printInfo();
                            return true;
                        }
                        else if ( (hp_boss>0)&&(i==0) ){
                            count_knight=0;
                            win=false;
                            this->printInfo();
                            return false;
                        }
                    }
                    else {
                        count_knight=0;
                        this->printInfo();
                        return false;
                    }
                }
            }
        }
        opponent->setlevelO(i,id);
        if (this->fight(opponent,omega,hades,winhades,shield,spear,hair,sword)==true) {   
            win=true;
        }
        else {
            win=false;
        }       
        this->printInfo();
        if (win==false) break;
    }
    return win;
}
/* * * END implementation of class ArmyKnights * * */











/* * * BEGIN implementation of class Events * * */
Events::Events(const string& file_events) {
    ifstream input(file_events); // Sử dụng ifstream thay vì fstream và không cần thiết sử dụng ios_base::in;
    input >> count_event;
    events = new int[count_event];
    for (int i = 0; i < count_event; i++) {
        input >> events[i];
    }
    input.close();
}
int Events::count() const {
    return count_event;
};
int Events::get(int i) const {
    return events[i];
};
/* * * END implementation of class Events * * */






/* * * BEGIN implementation of class BaseItem * * */
BaseItem* BaseItem::create_item(ItemType item) {
    switch (item)
    {
    case ANTIDOTE: {
        return new Antidote;
        break; }
    case PHOENIXI: {
        return new PhoenixI;
        break; }
    case PHOENIXII: {
        return new PhoenixII;
        break; }
    case PHOENIXIII: {
        return new PhoenixIII;
        break; }
    case PHOENIXIV: {
        return new PhoenixIV;
        break; }
    };
    return nullptr;
}


/* * * END implementation of class BaseItem * * */




/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() {
    armyKnights = nullptr;
    events = nullptr;
}
KnightAdventure::~KnightAdventure(){
    delete armyKnights;
    delete events;
}
void KnightAdventure::loadArmyKnights(const string &s){
    armyKnights= new ArmyKnights(s);
}
void KnightAdventure::loadEvents(const string &s){
    events=new Events(s);
}
void KnightAdventure::run(){
    armyKnights->printResult(this->armyKnights->adventure(events));
}

/* * * END implementation of class KnightAdventure * * */
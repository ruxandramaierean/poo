#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <set>
#include <utility>

using namespace std;

class Masini{
    private:
    string model;
    double pret;
    public:
    Masini(string model = "", double pret = 0.0){
        this->model = model;
        this->pret = pret;
    }
    ~Masini(){
        model.clear();
    }
    double get_pret(){
        return this->pret;
    }
    virtual void set_pret(double pret){
        this->pret = pret;
    }
    string get_model(){
        return this->model;
    }
    Masini& operator=(Masini m){
        ///
    }
    virtual void afisare(ostream &out);
    virtual void citire(istream &in);
    friend ostream& operator<<(ostream& out, Masini&);
    friend istream& operator>>(istream& in, Masini&);
};

void Masini::citire(istream &in){
    int ok = 0;
    do{
        cout<<"Modelul masinii:"<<endl;
        cout<<"1. MINI"<<endl;
        cout<<"2. MICA"<<endl;
        cout<<"3. COMPACTA"<<endl;
        cout<<"4. MONOVOLUM"<<endl;
        int option = 0;
        cout<<"Optiunea este: ";
        in>>option;
        if(option == 1){
            model = "mini";
            ok = 1;
        }
        else if(option == 2){
            model = "mica";
            ok = 1;
        }
        else if(option == 3){
            model = "compacta";
            ok = 1;
        }
        else if(option == 4){
            model = "monovolum";
            ok = 1;
        }
        else if(option < 1 || option > 4)
            cout<<"Selectie invalida! "<<endl;
    }while(ok == 0);
    cout<<endl;
    cout<<"Pretul masinii: ";
    in>>this->pret;
    cout<<endl;
}

istream& operator>>(istream& in, Masini& m){
    m.citire(in);
    return in;
}

void Masini::afisare(ostream &out){
    out<<"Modelul masinii: ";
    out<<model;
    cout<<endl;
    out<<"Pretul masinii: ";
    out<<this->pret;
    out<<endl;
}

ostream& operator<<(ostream& out, Masini& m)
{
    m.afisare(out);
    return out;
}


///---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


class monovolume:public Masini{
    private:
    bool nou;
    double reducere;
    int ani_vechime;
    string luna;
    public:
    monovolume(string model = "", double pret = 0.0, bool nou = 0, double reducere = 0.0, int ani_vechime = 0, string luna = ""):Masini("monovolum", pret){
        this->nou = nou;
        this->reducere = reducere;
        this->ani_vechime = ani_vechime;
        this->luna = luna;
    }
    ~monovolume(){}
    bool get_stare(){
        return nou;
    }
    double get_reducere(){
        return reducere;
    }
    string get_luna(){
        return this->luna;
    }
    int get_ani_vechime(){
        return this->ani_vechime;
    }
    ///string model = "", double pret = 0.0, bool nou = 0, double reducere = 0.0, int ani_vechime = 0, string luna = ""
    bool operator==(monovolume& m){
        if(this->get_pret() != m.get_pret()) return 0;
        else if(this->nou != m.nou) return 0;
        else if (this->reducere != m.reducere) return 0;
        else if(this->ani_vechime != m.ani_vechime) return 0;
        else if(this->luna != m.luna) return 0;
        return 1;
    }
    void afisare(ostream &out);
    void citire(istream& in);
    friend ostream& operator<<(ostream& out, monovolume&);
    friend istream& operator>>(istream& in, monovolume&);
};

void monovolume::citire(istream& in){

    int ok1 = 0;
    do{
        Masini::citire(in);
        if(this->get_model() != "monovolum"){
            ok1=1;
            cout<<"Selectie invalida!"<<endl;
        }
        else ok1=0;
    }while(ok1==1);
    int ok = 1;
    int x;
    do{
        cout<<"Starea masinii: (1 - nou / 0 - second hand)";
        in>>x;
        if(x < 0 || x > 1){
            cout<<"Selectie invalida"<<endl;
            ok=0;
        }
        else ok = 1;
    }while(ok==0);
    this->nou = x;
    ///consideram ca lunile de vara ar fi iunie, iulie, august

    if (nou == false){
        cout<<"Luna actuala: ";
        in>>this->luna;
        cout<<endl;
        if(luna == "iunie" || luna == "Iunie" || luna == "IUNIE" || luna == "iulie" || luna == "Iulie" || luna == "IULIE" || luna == "august" || luna == "August" || luna == "AUGUST"){
            reducere = 0.1;
            set_pret(get_pret() - get_pret()*reducere);
        }
        else{
            cout<<"Ani vechime ai masinii: ";
            in>>ani_vechime;
            reducere = 0.01*ani_vechime;
            set_pret(get_pret() - get_pret()*reducere);
        }
    }
    cout<<endl;
}
istream& operator>>(istream& in, monovolume& m){
    m.citire(in);
    return in;
}
void monovolume::afisare(ostream& out){
    Masini::afisare(out);
    cout<<"Starea monovolumului: ";
    if (nou == true) cout<<"nou"<<endl;
    else cout<<"second hand"<<endl;
}

ostream& operator<<(ostream& out, monovolume& m)
{
    m.afisare(out);
    return out;
}


///---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


class masini_mici: public Masini{
    private:
    double lungime;
    string tip; //hatchback, combi, sedan
    public:
    masini_mici(string model = "", double pret = 0.0, string tip = "", double lungime = 0.0):Masini(model, pret){
        this->tip = tip;
        this->lungime = lungime;
    }
    ~masini_mici(){
        tip.clear();
    }
    void afisare(ostream &out);
    void citire(istream& in);
    friend ostream& operator<<(ostream& out, masini_mici&);
    friend istream& operator>>(istream& in, masini_mici&);
};
void masini_mici::afisare(ostream& out){
    Masini::afisare(out);
    out<<"Tipul masinii este: ";
    out<<tip;
    out<<endl;
    out<<"Lungimea masinii este: ";
    out<<lungime;
    out<<endl;
    out<<endl;
}
ostream& operator<<(ostream& out, masini_mici& m){
    m.afisare(out);
    return out;
}
void masini_mici::citire(istream& in){
    int ok1 = 0;
    do{
        Masini::citire(in);
        if(this->get_model() == "monovolum"){
            ok1=1;
            cout<<"Selectie invalida!";
        }
        else ok1 = 0;
    }while(ok1==1);

    int ok = 0;
    do{
        cout<<"Modelul masinii:"<<endl;
        cout<<"1. HATCHBACK"<<endl;
        cout<<"2. COMBI"<<endl;
        cout<<"3. SEDAN"<<endl;
        int option = 0;
        cout<<"Optiunea este: ";
        in>>option;
        if(option == 1){
            this->tip = "hatchback";
            ok = 1;
        }
        else if(option == 2){
            this->tip = "combi";
            ok = 1;
        }
        else if(option == 3){
            this->tip = "sedan";
            ok = 1;
        }
        else if(option < 1 || option > 3)
            cout<<"Selectie invalida! "<<endl;
    }while(ok == 0);

    int ok2 = 0;
    cout<<endl;
    do{
        cout<<"Lungimea masinii este: ";
        in>>lungime;
        if(this->get_model() == "mini"){
            if(lungime > 4 ){
                cout<<"Selectie invalida\n";
                ok2 = 1;
            }
            else break;
        }
        else if(this->get_model() == "mica"){
            if(lungime < 3.85 || lungime > 4.1){
                cout<<"Selectie invalida\n";
                ok2 = 1;
            }else break;
        }
        else if (this->get_model() == "compacta"){
            if(lungime < 4.2 || lungime > 4.5){
                cout<<"Selectie invalida\n";
                ok2 = 1;
            }else break;
        }
    }while(ok == 1);
    cout<<endl;
}
istream& operator>>(istream& in, masini_mici& m){
    m.citire(in);
    return in;
}

///---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


template <class T>
class Vanzare{
    private:
    static int nr_vanzari;
    static int nr_stoc;
    set < pair < T*, bool > > *stoc;
    set < pair < T*, bool > > *vandute;
    public:
    //constructor
    Vanzare(int nr_stoc = 0, int nr_vanzari = 0){
        set < pair < T*, bool > > * stoc= new set < pair < T*, bool > >;
        set < pair < T*, bool > > * vandute= new set < pair < T*, bool > >;
        this->nr_vanzari = nr_vanzari;
        this->nr_stoc = nr_stoc;
    }
    ~Vanzare(){
        delete nr_stoc;
        delete nr_stoc;
        stoc.clear();
        vandute.clear();
    }
    //getteri, setteri
    static int get_nr_stoc(){
        return nr_stoc;
    }
    static int get_nr_vanzari(){
        return nr_vanzari;
    }
    void add(T* ceva){
        this->nr_stoc ++;
        stoc->insert(ceva);
    }
    T operator -=(T ceva){
        nr_vanzari --;
        nr_stoc --;
        stoc->erase(stoc->find(ceva));
        vandute->insert(ceva);
        return *stoc;
    }

};
template <class T>
int Vanzare<T>::nr_stoc = 0;
template <class T>
int Vanzare<T>::nr_vanzari = 0;


///---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


template <> class Vanzare <monovolume>{
    private:
    set < pair < monovolume*, bool > > *stoc;
    set < pair < monovolume*, bool > > *vandute;
    static int nr_stoc;
    static int nr_vanzari;
    public:
    ///constructor
    Vanzare(int nr_stoc = 0, int nr_vanzari = 0){
        this->vandute = vandute;
        this->stoc = stoc;
        this->nr_stoc = nr_stoc;
        this->nr_vanzari = nr_vanzari;
        set < pair < monovolume*, bool > > * stoc= new set < pair < monovolume*, bool > >;
        set < pair < monovolume*, bool > > * vandute= new set < pair < monovolume*, bool > >;
    }
    ///destructor
    ~Vanzare(){
        stoc->clear();
        vandute->clear();
    }
    void get_stoc(){
        set < pair < monovolume*, bool> >::iterator it = stoc->begin();
        while(it != stoc->end()){
            cout<<*it->first<<endl<<endl;
            it++;
        }
        cout<<endl;
    }
    void get_vandute(){
        set < pair < monovolume*, bool> >::iterator it = vandute->begin();
                while(it != vandute->end()){
                    cout<<*it->first<<endl<<endl;
                    it++;
                }
     
        cout<<endl;
    }
    void add(monovolume* m, bool nou){
        this->nr_stoc ++;
        stoc->insert(make_pair(m, nou));
    }
    void sell(monovolume* m, bool nou){
        this->nr_stoc--;
        this->nr_vanzari++;
        stoc->erase(stoc->find(make_pair(m, nou)));
        vandute->insert(make_pair(m, nou));
        
    }
};

int Vanzare<monovolume>::nr_stoc = 0;
int Vanzare<monovolume>::nr_vanzari = 0;

///---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


void menu_output(){
    cout<<"RUXANDRA MAIEREAN - GRUPA 212 - PROIECT 3 - CAR DEALERSHIP"<<endl;
    cout<<endl;
    cout<<"=========================================================="<<endl;
    cout<<endl;
    cout<<"                         Meniu: "<<endl;
    cout<<endl;
    cout<<"1. Citirea si afisarea a n masini mici (folosind upcast)."<<endl;
    cout<<"2. Citirea si afisarea a n masini."<<endl;
    cout<<"3. Citirea si afisarea a n monovolume."<<endl;
    cout<<"4. Adaugarea unui monovolum in stoc. "<<endl;
    cout<<"5. Stergerea unui monovolum din stoc. "<<endl;
    cout<<"6. Stergerea unei masini din stoc (folosind operatorul -=)."<<endl;
    cout<<"0. EXIT!"<<endl;
    cout<<endl;
}
void menu(){
    int option = 0;
    Vanzare<monovolume> *x;
    x = new Vanzare<monovolume>;
    do{

        menu_output();
        cout<<"Introduceti numarul actiunii: ";
        cin>>option;
        if(option < 0 || option > 5){
            cout<<"Selectie invalida!"<<endl;
        }
        else if(option == 0){
            cout<<"EXIT!! "<<endl;
        }
        else if(option == 1){
            int n = 0;
            cout<<"Numarul de masini mici care se citesc: ";
            cin>>n;
            cout<<endl;
            Masini **v = new Masini*[n];
            for(int i = 0; i < n; i++){
                v[i] = new masini_mici;
                cin>>*v[i];
            }
            for(int i = 0; i < n; i++){
                cout<<*v[i];
            }
        }
        else if (option == 2){
            int n = 0;
            cout<<"Numarul de monovolume care se citesc: ";
            cin>>n;
            cout<<endl;
            Masini **v = new Masini*[n];
            for(int i = 0; i < n; i++){
                v[i] = new Masini;
                cin>>*v[i];
            }
            for(int i = 0; i < n; i++){
                cout<<*v[i];
            }
        }
        else if (option == 3){
            int n = 0;
            cout<<"Numarul de monovolume care se citesc: ";
            cin>>n;
            cout<<endl;
            monovolume **v = new monovolume*[n];
            for(int i = 0; i < n; i++){
                v[i] = new monovolume;
                cin>>*v[i];
            }
            for(int i = 0; i < n; i++){
                cout<<*v[i];
            }
        }
        else if(option == 4){
            monovolume *m;
            m = new monovolume;
            cin>>*m;
            bool stare = m->get_stare();
            x->add(m, stare);
            x->get_stoc();

        }
        else if(option ==5){
            monovolume *m;
            m = new monovolume;
            cin>>*m;
            bool stare = m->get_stare();
            x->sell(m, stare);
            x->get_stoc();
            x->get_vandute();
        }
        system("pause"); ///Pauza - Press any key to continue...
        system("cls");
    }while(option!=0);
}
int main(){
    menu();
    return 0;
}

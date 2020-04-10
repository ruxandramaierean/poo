#include <iostream>
#include <stdlib.h>

using namespace std;

class node{
protected:
    int info;
    node* next;

public:
    ///constructor
    node() {next = NULL; info = 0;}
    node(int i, node* n)
    {
        this->next = new node;
        this->next = n;
        this->info = i;
    }

    ///destructor
    ~node(){delete next;}

    ///getteri, setteri
    void set_info(int x){info = x;}
    void set_next(node* n)
    {
        this->next = n;
    }
    virtual node *get_next(){return next;}
    int get_info(){return info;}

    bool hasNext()
    {
        if(next != NULL)
            return true;
        else
            return false;
    }

    ///copy constructor
    node(node& copyNode)
    {
        this->info = copyNode.info;
        this->next = copyNode.next;
    }

    ///operator =
    node& operator=(node &n)
    {
        this->next = new node;
        this->info = n.info;
        this->next = n.next;
    }

    ///cin si cout
    virtual void citire(istream &in);
    virtual void afisare(ostream &out);
    friend istream& operator>>(istream&, node&);
    friend ostream& operator<<(ostream&, node&);
};
void node::citire(istream& in)
{
    cout<<"nod = ";
    in>>info;

}
istream& operator>>(istream& in, node& nod)
{
    nod.citire(in);
    return in;
}
void node::afisare(ostream& out)
{
    out<<"Nodul este: ";
    out<<info;
}
ostream& operator<<(ostream& out, node& nod)
{
    nod.afisare(out);
    return out;
}



///----------------------------------------------------------------------------



class double_node : public node{
private:
    node *prev;
public:
    ///constructor
    double_node():node(){prev = NULL;}
    ///constructor
    double_node(int info, node* next, node* prev):node(info, next)
    {
        this->prev = prev;
    }
    ///destructor
    ~double_node(){delete next; delete prev; info = -1;}

    ///copy constructor
    double_node(double_node& n):node(n)
    {
        this->prev = n.prev;
    }

    ///operator =
    double_node& operator=(double_node& n)
    {
        this->info = n.info;
        this->next = new node;
        this->prev = new node;
        this->next = n.next;
        this->prev = prev;
    }

    ///getteri, setteri
    double_node *get_next(){return (double_node*)next;}
    void set_prev(double_node* n){this->prev = n;}
    double_node *get_prev(){return (double_node*) prev;}

    ///cin si cout
    void citire(istream &in);
    void afisare(ostream &out);
    friend istream& operator>>(istream&, double_node&);
    friend ostream& operator<<(ostream&, double_node&);
};

void double_node::citire(istream& in)
{
   cout<<"Introduceti un nod dublu: "<<endl;
   node::citire(in);

}
istream& operator>>(istream& in, double_node& nod)
{
    nod.citire(in);
    return in;
}
void double_node::afisare(ostream& out)
{
    out<<"Nodul este: ";
    out<<get_info();
}
ostream& operator<<(ostream& out, double_node& nod)
{
    nod.afisare(out);
    return out;
}



///------------------------------------------------------------------------------


class doublyLinkedList
{
protected:
    double_node *head, *tail;
    int length;
public:
    friend class double_node;
    ///constructor
    doublyLinkedList()
    {
        this->head = NULL;
        this->tail = NULL;
        this->length = 0;
    }
    doublyLinkedList(double_node *head, double_node* tail, int length)
    {
        this->head = new double_node;
        this->tail = new double_node;
        this->head = head;
        this->tail = tail;
        this->length = length;
    }
    ///destructor
    ~doublyLinkedList()
    {
        double_node *current = head;
        while ( current ){
            double_node* next =  current->get_next();
            delete current;
            current = next;
        }
    }

    ///operator=
    doublyLinkedList operator=(doublyLinkedList& lista)
    {
        double_node*  nod1 = lista.head;
        double_node*  nod2 = head;
        while(nod2 != lista.tail)
        {
            head = lista.head;
            nod1 = (double_node*) nod1->get_next();
            nod2 = (double_node*) nod2->get_next();
        }
        tail = lista.tail;
        length = lista.length;
    }

    ///getteri, setteri
    double_node* get_head(){return this->head;}
    double_node* get_tail(){return this->tail;}

    int Size(bool update)
    {
        if(!update)
        {
            return this->length;
        }
        int s = 0;
        double_node* temp = this->head;
        while (temp)
        {
            s++;
            temp = temp->get_next();
        }
        this->length = s;
        return this->length;
    }

    virtual void addTail(int info)
    {

        double_node *n = new double_node;
        n->set_info(info);
        n->set_next(NULL);
        n->set_prev(NULL);

        if(head == NULL)
        {
            head = n;
        }
        else
        {
            double_node* nod_curent = new double_node;
            nod_curent = head;

            while (nod_curent->get_next() != NULL)
                nod_curent = (double_node*) nod_curent->get_next();

            nod_curent->set_next(n);
            n->set_prev(nod_curent);
        }
        length++;
        tail = n;
    }

    ///copy constructor
    doublyLinkedList (doublyLinkedList& lista)
    {
        cout<<"pula";
        this->length = lista.length;
        this->head = lista.head;
        lista.head = (double_node*)lista.head->get_next();
        cout<<"pula1";
        for (int i = 1; i < lista.length-1; i++)
            {
                this->addTail(lista.head->get_info());
                lista.head = (double_node*)lista.head->get_next();
            }
        cout<<"pula2";
        this->tail = lista.tail;
    }

    void addHead(int info)
    {
        double_node* n = new double_node;
        n->set_info(info);
        n->set_next(NULL);
        n->set_prev(NULL);

        if(head==NULL)
            head = tail = n;
        else
        {
            head->set_prev(n);
            n->set_next(head);
            head = n;
        }
        length++;
    }

    ///cin si cout
    virtual void citire(istream &in);
    virtual void afisare(ostream &out);
    friend istream& operator>>(istream&, doublyLinkedList&);
    friend ostream& operator<<(ostream&, doublyLinkedList&);

};
inline void doublyLinkedList::citire(istream& in )
{
    int date,n, i;
    cout<<"Introduceti umarul de noduri: ";
    in>>n;

    for(i = 0; i < n; i++)
    {
        in>>date;
        addTail(date);
    }
}
istream& operator>>(istream& in, doublyLinkedList& lista)
{
    lista.citire(in);
    return in;
}
inline void doublyLinkedList::afisare(ostream& out)
{
    while(head!=NULL)
    {
        out<<head->get_info()<<" ";
        head = (double_node*)head->get_next();
    }

}
ostream& operator<<(ostream& out, doublyLinkedList& lista)
{
    lista.afisare(out);
    return out;
}


///---------------------------------------------------------------------------------------------------------------


class circularList:public doublyLinkedList
{
private:
public:
    ///constructor
    circularList():doublyLinkedList(){};
    circularList(double_node* head, double_node* tail, int length):doublyLinkedList(head, tail, length)
    {
        tail->set_next(head);
        head->set_prev(tail);
    }
    ///destructor
    ~circularList()
    {
        double_node *current = head;
        while (current)
        {
            double_node* next = current->get_next();
            delete current;
            current = next;
        }
    }
    ///copy constructor
    circularList(circularList& lista):doublyLinkedList(lista)
    {
        tail->set_next(head);
        head->set_prev(tail);
    }

    int get_length(){return length;}
    ///operator=
    circularList operator=(circularList& lista)
    {
        double_node*  nod1 = lista.head;
        double_node*  nod2 = head;
        while(nod2 != lista.tail)
        {
            head = lista.head;
            nod1 = (double_node*) nod1->get_next();
            nod2 = (double_node*) nod2->get_next();
        }
        tail = lista.tail;
        length = lista.length;
        tail->set_next(head);
        head->set_prev(tail);
    }
    ///cin si cout
    void citire(istream &in);
    void afisare(ostream &out);
    friend istream& operator>>(istream&, circularList&);
    friend ostream& operator<<(ostream&, circularList&);

    void deleteNode(int key)
    {
        if(head == NULL) return;

        double_node* curr = head, *prev_1;

        while(curr->get_info() != key)
        {
            ///nodul e in lista?
            if(curr->get_next() == head)
            {
                cout<<"Lista nu are nodul cu valoarea "<<key<<"!!"<<endl;
                return;
            }
            prev_1 = curr;
            curr = curr->get_next();
        }

        ///lista are doar un nod
        if(curr->get_next() == head && prev_1 == NULL)
        {
            head = NULL;
            free(curr);
            return;
        }

        ///daca lista are mai multe noduri, mai intai verificam daca este primul
        if(curr == head)
        {
            ///mut prev la ultimul nod din lista
            prev_1 = head->get_prev();
            ///mut head cu un nod mai incolo
            head = head->get_next();

            prev_1->set_next(head);
            head->set_prev(prev_1);
            free(curr);
        }
        ///verific daca e ultimul nod din lista
        else if(curr->get_next() == head)
        {
            prev_1->set_next(head);
            head->set_prev(prev_1);
            free(curr);
        }
        ///inseamna ca e in restul listei
        else
        {
            double_node* temp = curr->get_next();
            prev_1->set_next(temp);
            temp->set_prev(prev_1);
            free(curr);
        }
    }
};
void circularList::citire(istream& in)
{
    doublyLinkedList::citire(in);
    tail->set_next(head);
    head->set_prev(tail);
}
istream& operator>>(istream& in, circularList& lista)
{
    lista.citire(in);
    return in;
}
void circularList::afisare(ostream& out)
{
  double_node *i = head->get_next();
  while(i)
    {
      cout<<*i<<endl;
      if(i == head)
        break;
      i = i->get_next();
    }
}
ostream& operator<<(ostream& out, circularList& lista)
{
    lista.afisare(out);
    return out;
}



///-----------------------------------------------------------------------------------------------------------------


void josephus()
{
    circularList l;
    cout<<"Se citeste o lista circulara: "<<endl;
    cin>>l;
    cout<<endl<<"Introduceti din cati in cati pasi vreti sa se elimine un nod: ";
    int m;
    cin>>m;
    double_node *ptr1 = l.get_head(), *ptr2 = l.get_head();
    ///cat timp nu a ramas decat un nod in lista
    while(ptr1->get_next() != ptr1)
    {
        int c = 1;
        while(c != m)
        {
            ptr2 = ptr1;
            ptr1 = ptr1->get_next();
            c++;
        }
        ptr2->set_next(ptr1->get_next());
        ptr1 = ptr2->get_next();
    }
    cout<<"Pozitia Josephus este: "<<ptr1->get_info()<<endl;
}


///------------------------------------------------------------------------------------------------------------------

void menu_output()
{
    cout<<"RUXANDRA MAIEREAN - GRUPA 212 - LISTA CIRCULARA"<<endl;
    cout<<"Menu:"<<endl;
    cout<<"1. Citirea a n liste circulare."<<endl;
    cout<<"2. Afisarea a n liste circulare."<<endl;
    cout<<"3. Stergerea unui nod din lista circulara."<<endl;
    cout<<"4. Problema lui Josephus."<<endl;
    cout<<"0. Exit!"<<endl;
}

void menu()
{
    int option = 0;
    circularList lista[10];
    int n = 0;
    do
    {
        menu_output();
        cout<<"Introduceti numarul actiunii: ";
        cin>>option;
        if (option < 0 || option > 4)
            cout<<"Selectie invalida!"<<endl;
        if (option == 0)
            cout<<"EXIT!"<<endl;
        if (option == 1)
        {
            cout<<"Numarul de liste circulare care se citesc: ";
            cin>>n;
            cout<<endl;
            for(int i = 0; i < n; i++)
            {
                cout<<"Se citeste a "<<i+1<<"-a lista circulara:"<<endl;
                cin>>lista[i];
                cout<<endl;
            }
        }
        if (option == 2)
        {
            if (n == 0)
                cout<<"Nu s-a citit nicio lista!"<<endl;
            else
            {
                for(int i = 0; i < n; i++)
                {
                    cout<<"Se afiseaza a "<<i+1<<"-a lista circulara:"<<endl;
                    cout<<lista[i]<<endl;
                }
            }
        }
        if(option == 3)
        {
            circularList l;
            cout<<"Se citeste o lista circulara: "<<endl;
            cin>>l;
            int x;
            cout<<"Ce nod vreti sa se stearga din lista? ";
            cin>>x;
            l.deleteNode(x);
            cout<<l;
        }
        if(option == 4)
        {

            josephus();
        }
        system("pause"); ///Pauza - Press any key to continue...
        system("cls");

    }while(option != 0);
}
int main()
{

    menu();
    return 0;
}

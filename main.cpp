#include<iostream>
#include<string>
#include<vector>
using namespace std;
class student {



public:
    student(string name, int year, int number_credits, double gen_average) {
        this->name = name;
        this->year = year;
        this->number_credits = number_credits;
        this->gen_average = gen_average;

    }

    student(const student &student1) {
        name = student1.name;
        year = student1.year;
        number_credits = student1.number_credits;
        gen_average = student1.gen_average;


    }

    student() {}

    string getname() {
        return this->name;
    }


    void setname(string name){
        this->name = name;
    }



    int getnage() {
        return this->year;
    }



    void setage(int age) {
        this->year = age;
    }


    int getnumber_credits() {
        return this->number_credits;
    }



    void setnumber_credits(int number_credits) {
        this->number_credits = number_credits;
    }

    double getgen_average() {
        return this->gen_average;
    }



    void setgen_average(double gen_average) {
        this->gen_average = gen_average;
    }

    friend istream &operator>>(istream &in, student &student1) {
        cout << "Nume: ";
        in >> student1.name;
        cout << "An: ";
        in >> student1.year;
        cout << "Numar credite: ";
        in >> student1.number_credits;
        cout << "Medie student: ";
        in >> student1.gen_average;

        return in;
    }
    friend ostream &operator <<(ostream &out,student &student1)
    {
        cout<<"Nume:";
        out<<student1.name<<"\n";
        cout<<"An:";
        out<<student1.year<<"\n";
        cout<<"Numar credite:";
        out<<student1.number_credits<<"\n";
        cout<<"Medie student:";
        out<<student1.gen_average<<"\n";
        return out;
    }

    bool operator ==(student student1)
    {
        return student1.getname().compare(this->name) == 0;
    }

    student &operator=(student const&student1)
    {
        this->name=student1.name;
        this->year=student1.year;
        this->gen_average=student1.gen_average;
        this->number_credits=student1.number_credits;
        return *this;
    }

    bool operator !=(student& student1)
    {
        return student1.getname().compare(this->name) == 1;
    }

private:
    string name;
    int year;
    int number_credits;
    double gen_average;








};

class Grupa{
public:
    friend istream& operator>>(istream& in,Grupa& grupa1)
    {
        cout<<"Introduceti nr studenti:";
        in>>grupa1.nr_studenti;
        cout<<"Introduceti Studentii:"<<"\n";
        student student1;
        double s=0;
        for(int i=0;i<grupa1.nr_studenti;i++) {
            in >> student1;
            grupa1.studenti.push_back(student1);
            s=s+student1.getgen_average();

        }
        s=s/double(grupa1.nr_studenti);
        grupa1.stud_average=s;

        return in;

    }

    student &operator []( int index) {
        return studenti[index];
    }


    friend ostream& operator<<(ostream& out,Grupa& grupa1)
    {

        out<<grupa1.nr_studenti<<"\n";
        student student1;
        for(int i=0;i<grupa1.nr_studenti;i++){
            out<<grupa1[i];
        }
        out<<"Medie studenti:";
        out<<grupa1.stud_average;

        return out;

    }

    bool operator==(Grupa const grupa1) {
        bool ok = 1;
        if (this->nr_studenti != grupa1.nr_studenti)
            ok = 0;
        if (this->stud_average != grupa1.stud_average)
            ok = 0;
        if (ok) {
            for (int i = 0; i < nr_studenti; i++){
                student student1;
                student1=this->studenti[i];
                bool gasit=0;
                for (int j = 0; j < nr_studenti; j++)
                    if (student1 == grupa1.studenti[j])
                    {
                        gasit=1;
                        break;
                    }
                if(gasit==0) {
                    ok=0;
                    break;
                }
            }
        }
        return ok;
    }
    bool operator!=(Grupa const grupa1) {
        bool ok = 1;
        if (this->nr_studenti != grupa1.nr_studenti)
            ok = 0;
        if (this->stud_average != grupa1.stud_average)
            ok = 0;
        if (ok) {
            for (int i = 0; i < nr_studenti; i++){
                student student1;
                student1=this->studenti[i];
                bool gasit=0;
                for (int j = 0; j < nr_studenti; j++)
                    if (student1 == grupa1.studenti[j])
                    {
                        gasit=1;
                        break;
                    }
                if(gasit==0) {
                    ok=0;
                    break;
                }
            }
        }
        return 1-ok;
    }




    int getnr_studenti()
    {
        return nr_studenti;
    }
    void setnumar_studenti(int)
    {
        this->nr_studenti=nr_studenti;
    }
    double getstud_average()
    {
        return stud_average;
    }




    Grupa(int nr_studenti)
    {
        studenti.resize(nr_studenti);
    }

    Grupa()
    {
    }




    void  Elim_student(student& student1)
    {

        double suma=stud_average*double(nr_studenti);
        suma=suma-student1.getgen_average();
        suma=suma/double(nr_studenti-1);
        stud_average=suma;
        for(int i=0;i<nr_studenti;i++)
            if(studenti[i]==student1)
            {for(int j=i;j<nr_studenti-1;j++)
                    studenti[j]=studenti[j+1];
                break;}
        nr_studenti--;
        this->studenti.resize(nr_studenti);

    }

    void Plus_student(student& student1)
    {
        double suma=stud_average*double(nr_studenti);
        suma=suma+student1.getgen_average();
        suma=suma/(nr_studenti+1);
        stud_average=suma;
        studenti.push_back(student1);
        nr_studenti++;
    }
    bool verif(student& student1)
    {for(int i=0;i<nr_studenti;i++)
        {if(studenti[i]==student1)
                return 1;}
        return 0;


    }


    Grupa &operator +=(Grupa  &grupa1){
        for(int i=0;i<nr_studenti;i++)
            grupa1.Plus_student(studenti[i]);
        return grupa1;
    }

    Grupa &operator -=(Grupa  &grupa1){
        for(int i=0;i<nr_studenti;i++)
            if(grupa1.verif(studenti[i]))
                grupa1.Elim_student(studenti[i]);
        return grupa1;
    }
    Grupa &operator=(Grupa const&grupa1)
    {
        this->nr_studenti=grupa1.nr_studenti;
        this->stud_average=grupa1.stud_average;
        this->studenti=grupa1.studenti;

        return *this;
    }






private:
    int nr_studenti;
    vector <student> studenti;
    double stud_average;

};

int main()
{
    student student1;
    student student2;
    Grupa grupa2;
    Grupa grupa1;
    cin>>student1;
    cin>>student2;
    cin>>grupa1;
    cin>>grupa2;
    cout<<grupa1.getstud_average()<<"\n";//media generala a grupei 1
    cout<<grupa1.getnr_studenti()<<"\n";// nr de stud. din grupa 1
    cout<<student1.getgen_average()<<"\n";//media studentului 1
    cout<<student1.getname()<<"\n";// numele stud 1
    cout<<student1.getnumber_credits()<<"\n";// nr de credite stud1
    cout<<student1.getnage()<<"\n";//anul stud. 1
    grupa1+=grupa2; //in grupa 2 punem tot ce contine grupa1
    cout<<grupa2<<"\n";
    grupa1=grupa2;// grupa 1 va fi inlocuita cu grupa 2
    cout<<grupa1<<"\n";
    grupa1-=grupa2;//Facem in grupa 2 intersectia dintre grupa 2 si grupa 1
    cout<<grupa2<<"\n";
    if(grupa1==grupa2)//Verificam daca grupele sunt egale
        cout<<"1"<<"\n";
    else cout<<"0"<<"\n";

    if(grupa1!=grupa2)//Verificam daca grupele sunt diferite
        cout<<"1"<<"\n";


    grupa1.Plus_student(student1);//Adaug studentul 1 in grupa 1
    cout<<grupa1<<"\n";
    grupa1.Elim_student(student1);// Elimin studentul 1 din grupa 1,oferindu-se rezultate corecte
    // doar in cazul in care studentul Se afla in grupa
    cout<<grupa1<<"\n";

    if(student1==student2)//Verific daca 2 studenti au acelasi nume//
        cout<<"1"<<"\n";
    if(student1!=student2)//Verific daca 2 studenti au nume diferit//
        cout<<"0"<<"\n";

    cout<<grupa1.verif(student1);







}
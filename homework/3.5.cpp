#include<iostream>
#include<string>

class Person{
    friend std::istream& read_person(std::istream&, Person&);
    friend std::ostream& print(std::ostream&, const Person&);
    public:
        Person()=default;
        //Person(std::string n="no", std::string s="no" ,std::string a="no" ,int p=0 ,int sa=0):name(n),sex(s),address(a),phonenumber(p),salary(sa){}
        Person(std::string n, std::string s, std::string a, int p, int sa):name(n),sex(s),address(a),phonenumber(p),salary(sa){}
        virtual std::ostream& show(){
            return std::cout<<name<<" "<<sex<<" "<<address<<" "<<phonenumber<<" "<<salary;
        };
    private:
    protected:
        std::string name, sex, address;
        int phonenumber,salary;
};

std::istream& read_person(std::istream& is, Person& p){
    std::cout<<"input:name,sex,address,phonenumber,salary";
    is>>p.name>>p.sex>>p.address>>p.phonenumber>>p.salary;
    return is;
};
std::ostream& print(std::ostream& os, Person& p){
    os.tie(&p.show());
    return os;
}
class Teacher : virtual public Person{
    friend std::istream& read_teacher(std::istream&, Teacher&);
    friend std::ostream& print(std::ostream&, const Person&);
    public:
        Teacher()=default;
        //Teacher(std::string p="no"):post(p){}
        Teacher(std::string n, std::string s, std::string a, int p, int sa, std::string po):Person(n,s,a,p,sa),post(po){}
        //每个类各自控制自己的接口 这里用基类 Person 的构造函数去初始化
        virtual std::ostream& show() override{
            return std::cout<<name<<" "<<sex<<" "<<address<<" "<<phonenumber<<" "<<salary<<"\n"<<post;
        };
    private:
    protected:
        std::string post;
};

std::istream& read_teacher(std::istream& is, Teacher& p){
    std::cout<<"input:name,sex,address,phonenumber,salary,post";
    is>>p.name>>p.sex>>p.address>>p.phonenumber>>p.salary>>p.post;
    return is;
}

class Cadre : virtual public Person{
    friend std::istream& read_cadre(std::istream&, Cadre&);
    friend std::ostream& print(std::ostream&, const Person&);
    public:
        virtual std::ostream& show() override{
            return std::cout<<name<<" "<<sex<<" "<<address<<" "<<phonenumber<<" "<<salary<<"\n"<<job;
        };
        Cadre()=default;
        //Cadre(std::string j="no"):job(j){}
        Cadre(std::string n, std::string s, std::string a, int p, int sa, std::string j):Person(n,s,a,p,sa),job(j){}
    private:
    protected:
        std::string job;
};

std::istream& read_cadre(std::istream& is, Cadre& p){
    std::cout<<"input:name,sex,address,phonenumber,salary,job";
    is>>p.name>>p.sex>>p.address>>p.phonenumber>>p.salary>>p.job;
    return is;
}

class TeacherCadre : public Teacher, public Cadre{
    friend std::istream& read_teacher_cadre(std::istream&, TeacherCadre&);
    friend std::ostream& print(std::ostream&, const Person&);
    public:
        virtual std::ostream& show() override{
            return std::cout<<name<<" "<<sex<<" "<<address<<" "<<phonenumber<<" "<<salary<<"\n"<<post<<" "<<job;
        };
        TeacherCadre()=default;
        TeacherCadre(std::string n, std::string s, std::string a, int p, int sa, std::string po, std::string j):Teacher(n,s,a,p,sa,po),Cadre(n,s,a,p,sa,j){}
        //Q: 这就是虚继承吗
    private:
    protected:
};

std::istream& read_teacher_cadre(std::istream& is, TeacherCadre& p){
    std::cout<<"input:name,sex,address,phonenumber,salary,post,job";
    is>>p.name>>p.sex>>p.address>>p.phonenumber>>p.salary>>p.post>>p.job;
    return is;
}

void screen(){
    std::cout<<"请按照要求输入数字\n"<<"0: 退出\n";
    std::cout<<"1:展示列表\n"<<"10:Person\n"<<"20:Teacher\n"<<"30:Cadre\n";
    std::cout<<"40:TeacherCadre\n"<<std::endl;
}
int main(){
    while(1){
        int n;
        screen();
        std::cin>>n;
        Person a;
        Teacher b;
        Cadre c;
        TeacherCadre d;
        switch(n)
        {
        case 0:
            std::cout<<"exit"<<std::endl;
            return 0;
            break;
        case 1:
            std::cout<<"功能未推出"<<std::endl;
            break;
        case 10:
            read_person(std::cin,a);
            std::cout<<"echo"<<std::endl;
            print(std::cout,a);
            break;
        case 20:
            read_teacher(std::cin,b);
            std::cout<<"echo"<<std::endl;
            print(std::cout,b);
            break;
        case 30:
            read_cadre(std::cin,c);
            std::cout<<"echo"<<std::endl;
            print(std::cout,c);
            break;
        case 40:
            read_teacher_cadre(std::cin,d);
            std::cout<<"echo"<<std::endl;
            print(std::cout,d);
            break;
        default:
            std::cout<<"输入错误"<<std::endl;
            break;
        }
    }
}
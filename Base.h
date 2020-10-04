#ifndef CL_BASE_H
#define CL_BASE_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
class Base
{
protected:
    //координаты установки
    int x, y;
    //состояние объекта
    int _num;
    //имя объекта
    string _name;
    //путь до объекта
    string _path;

public:
    //конструктор по умолчанию
    Base();
    //параметризированный конструктор
    Base(string _name, int _num);
    //метод получения имени объекта
    string GetName();
    //метод получения пути до объекта
    string GetPath();
    //метод добавления объекта в подчинённые
    void Push(Base* p_child);
    //перегрузка метода поиска объекта на дереве по его пути
    Base* Find(string obj_path);
    Base* Find(string _path, string obj_path);
    Base* Find1(string _path, string obj_path);
    //методы поиска объекта по его имени
    Base* search(string name);
    Base* search1(string _path, string name, Base* p_parent);

    typedef void (Base ::* T_SIG) (string&);
    typedef void (Base ::* T_HEN) (Base* bs, string&);
#define SIG_D(sig_f) (T_SIG) (&sig_f)
#define HEN_D(hen_f) (T_HEN) (&hen_f)

    //структура для хранения связей
    struct o_sh
    {
        T_SIG p_sig;
        Base* p_obj;
        T_HEN p_hen;
    };

    //метод первоначального заполнения файла
    void FieldBuild();
    //установка метода сигнала и обработчика по умолчанию
    void SetDefault();
    //установка связи
    void set_conn(T_SIG p_sig, Base* p_obj, T_HEN p_hen);
    //удаление связи
    void del_conn(T_SIG p_sig, Base* p_obj, T_HEN p_hen);
    //вызов сигнала
    void emit_conn(T_SIG p_sig, string& s_com);
    //метод сигнала
    virtual void signal(string& text);
    //метод обработчика
    virtual void hendler(Base *ob, string &text);
    //метод вывода содержимого файла
    void PrintFile();


    //указатель на метод сигнала
    void (Base::* signalptr) (string&);
    //указатель на метод обработчика
    void (Base::* hendlerptr) (Base*, string&);
    //метод обработчика сигнала успешной вставки
    void PasteSymbol(Base* p_ob, string& s_text);
    //сокращенная установка связи
    void SetConnections(Base* Second);
    //установка позиции вставки
    void SetPosition(int X, int Y, string a);

    //итератор для контейнера children
    vector<Base*> ::iterator it_child;
    //контейнер указателей потомков
    vector<Base*> children;
    //итератор для контейнера connects связей между сигналами и обработчиками
    vector<o_sh*> ::iterator it_conn;
    //контейнер связей между сигналами и обработчиками
    vector<o_sh*> connects;

};
#endif

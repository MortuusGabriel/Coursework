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
    //���������� ���������
    int x, y;
    //��������� �������
    int _num;
    //��� �������
    string _name;
    //���� �� �������
    string _path;

public:
    //����������� �� ���������
    Base();
    //������������������� �����������
    Base(string _name, int _num);
    //����� ��������� ����� �������
    string GetName();
    //����� ��������� ���� �� �������
    string GetPath();
    //����� ���������� ������� � ����������
    void Push(Base* p_child);
    //���������� ������ ������ ������� �� ������ �� ��� ����
    Base* Find(string obj_path);
    Base* Find(string _path, string obj_path);
    Base* Find1(string _path, string obj_path);
    //������ ������ ������� �� ��� �����
    Base* search(string name);
    Base* search1(string _path, string name, Base* p_parent);

    typedef void (Base ::* T_SIG) (string&);
    typedef void (Base ::* T_HEN) (Base* bs, string&);
#define SIG_D(sig_f) (T_SIG) (&sig_f)
#define HEN_D(hen_f) (T_HEN) (&hen_f)

    //��������� ��� �������� ������
    struct o_sh
    {
        T_SIG p_sig;
        Base* p_obj;
        T_HEN p_hen;
    };

    //����� ��������������� ���������� �����
    void FieldBuild();
    //��������� ������ ������� � ����������� �� ���������
    void SetDefault();
    //��������� �����
    void set_conn(T_SIG p_sig, Base* p_obj, T_HEN p_hen);
    //�������� �����
    void del_conn(T_SIG p_sig, Base* p_obj, T_HEN p_hen);
    //����� �������
    void emit_conn(T_SIG p_sig, string& s_com);
    //����� �������
    virtual void signal(string& text);
    //����� �����������
    virtual void hendler(Base *ob, string &text);
    //����� ������ ����������� �����
    void PrintFile();


    //��������� �� ����� �������
    void (Base::* signalptr) (string&);
    //��������� �� ����� �����������
    void (Base::* hendlerptr) (Base*, string&);
    //����� ����������� ������� �������� �������
    void PasteSymbol(Base* p_ob, string& s_text);
    //����������� ��������� �����
    void SetConnections(Base* Second);
    //��������� ������� �������
    void SetPosition(int X, int Y, string a);

    //�������� ��� ���������� children
    vector<Base*> ::iterator it_child;
    //��������� ���������� ��������
    vector<Base*> children;
    //�������� ��� ���������� connects ������ ����� ��������� � �������������
    vector<o_sh*> ::iterator it_conn;
    //��������� ������ ����� ��������� � �������������
    vector<o_sh*> connects;

};
#endif

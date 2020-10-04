#include "Class_1.h"
#include "Class_2.h"
#include "Class_3.h"

//������������������� �����������
cl_app::cl_app(string _name, int _num) :Base(_name, _num)
{
}

//����������� �� ���������
cl_app::cl_app() : Base()
{
}

//������ �������� ���������
void cl_app::exec()
{
	SetDefault();
	cl_app app;
	//���������� ����� �����������
	app.FieldBuild();
	//��������� ������ ����� ���������
	Base* Printer = new Base();
	Printer->SetDefault();
	Base* Position = new Base();
	Position->SetDefault();
	Base* Paster = new Base();
	Paster->SetDefault();
	Paster->hendlerptr = &Base::PasteSymbol;
	Position->SetConnections(Paster);
	/*Printer->SetConnections(this);
	Paster->SetConnections(Printer);*/

	//���� ������ ������ ������
	int x, y;
	string symbol;
	cin >> x >> y >> symbol;


	//���� ����������� ��� ����� ���������� (0;0)
	while (x != 0 && y != 0) {
		//������ �������
		Position->SetPosition(x, y, symbol);
		//���� ��������� ������
		cin >> x >> y >> symbol;
	}

	//����� ������ ������ ����������� �����
	Printer->PrintFile();
}

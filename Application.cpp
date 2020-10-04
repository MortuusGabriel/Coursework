#include "Class_1.h"
#include "Class_2.h"
#include "Class_3.h"

//параметризированный конструктор
cl_app::cl_app(string _name, int _num) :Base(_name, _num)
{
}

//конструктор по умолчанию
cl_app::cl_app() : Base()
{
}

//запуск основной программы
void cl_app::exec()
{
	SetDefault();
	cl_app app;
	//заполнение файла восьмерками
	app.FieldBuild();
	//установка связей между объектами
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

	//ввод первой тройки данных
	int x, y;
	string symbol;
	cin >> x >> y >> symbol;


	//цикл завершается при вводе координаты (0;0)
	while (x != 0 && y != 0) {
		//выдача сигнала
		Position->SetPosition(x, y, symbol);
		//ввод очередной тройки
		cin >> x >> y >> symbol;
	}

	//вызов метода вывода содержимого файла
	Printer->PrintFile();
}

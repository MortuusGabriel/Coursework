#include "Base.h"

//конструктор по умолчанию
Base::Base()
{
}
//параметризированный конструктор
Base::Base(string _name, int _num)
{
	this->_name = _name;
	this->_num = _num;
}
//метод получения имени объекта
string Base::GetName()
{
	return _name;
}
//метод получения пути до объекта
string Base::GetPath()
{
	return _path;
}
//метод добавления объекта в подчинённые
void Base::Push(Base* p_child)
{
	this->children.push_back(p_child);
}
//метод поиска объекта по его пути
Base* Base::Find(string _name)
{
	if (this->GetName() == _name) {
		return this;
	}
	Base* q;
	for (Base* i : children) {
		q = i->Find(_name);
		if (q != nullptr) {
			return q;
		}
	}
	return nullptr;
}
//метод поиска объекта по его пути
Base* Base::Find(string _path, string _name)
{
	if (this->GetName() == _name && this->GetPath() == _path) {
		return this;
	}
	Base* q;
	for (Base* i : children) {
		q = i->Find1(_path, _name);
		if (q != nullptr) {
			return q;
		}
	}
	return nullptr;
}
//метод поиска объекта по его пути
Base* Base::Find1(string _path, string _name)
{
	if (this->GetName() == _name && this->GetPath() + "/" +
		_name == _path) {
		return this;
	}
	Base* q;
	for (Base* i : children) {
		q = i->Find1(_path, _name);
		if (q != nullptr) {
			return q;
		}
	}
	return nullptr;
}
//метод поиска объекта по его имени
Base* Base::search(string name)
{
	this->_path = name;
	string text = "";
	int i = 1;
	while (i != name.length() && name[i] != '/') {
		text += name[i];
		i++;
	}
	name.erase(0, i);
	if (name == "") {
		return Find("/" + text, text);
	}
	else {
		return search1("/" + text, name, Find(text));
	}
}
//метод поиска объекта по его имени
Base* Base::search1(string _path, string name, Base* p_parent)
{
	string text = "";
	int i = 1;
	_path = _path + "/";
	while (i != name.length() && name[i] != '/') {
		text += name[i];
		_path += name[i];
		i++;
	}
	name.erase(0, i);
	if (name == "") {
		return Find(_path, text);
	}
	else {
		return search1(_path, name, Find(text));
	}
}
//метод первоначального заполнения файла
void Base::FieldBuild()
{
	fstream fs;
	fs.open("field.txt", ios::out);

	if (!fs.is_open()) {
		exit(-1);
	}

	for (int i = 0; i < 10; i++) {
		for (int i = 0; i < 10; i++) {
			fs << "8";
		}
		fs << endl;
	}

	fs.close();
}
//установка метода сигнала и обработчика по умолчанию
void Base::SetDefault()
{
	signalptr = &Base::signal;
	hendlerptr = &Base::hendler;
}
//установка связи
void Base::set_conn(T_SIG p_sig, Base* p_obj, T_HEN p_hen)
{
	it_conn = connects.begin();
	while (it_conn != connects.end()) {
		if ((*it_conn)->p_sig == p_sig && (*it_conn)->p_obj == p_obj
			&& (*it_conn)->p_hen == p_hen) {
			return;
		}
		it_conn++;
	}
	o_sh* ptr = new o_sh();
	ptr->p_sig = p_sig;
	ptr->p_obj = p_obj;
	ptr->p_hen = p_hen;
	connects.push_back(ptr);
}
//удаление связи
void Base::del_conn(T_SIG p_sig, Base* p_obj, T_HEN p_hen)
{
	if (connects.size() == 0) {
		return;
	}
	it_conn = connects.begin();
	while (it_conn != connects.end()) {
		if ((*it_conn)->p_sig == p_sig && (*it_conn)->p_obj == p_obj
			&& (*it_conn)->p_hen == p_hen) {
			connects.erase(it_conn);
			return;
		}
		it_conn++;
	}
}
//вызов сигнала
void Base::emit_conn(T_SIG p_sig, string& s_com)
{
	if (connects.size() == 0) {
		return;
	}
	bool flag = false;
	it_conn = connects.begin();
	while (it_conn != connects.end()) {
		if ((*it_conn)->p_sig == p_sig) {
			T_HEN t_hen = (*it_conn)->p_hen;
			((*it_conn)->p_obj->*t_hen)(nullptr, s_com);
		}
		it_conn++;
	}
}
//указатель на метод сигнала
void Base::signal(string& text)
{
}
//указатель на метод обработчика
void Base::hendler(Base* ob, string& text)
{
}
//метод вывода содержимого файла
void Base::PrintFile()
{
	string mystr;
	vector <string > Out;
	ifstream fin("field.txt");
	while (getline(fin, mystr))
	{
		Out.push_back(mystr);
	}
	fin.close();
	for (int i = 0; i < Out.size(); i++) {
		if (i > 0) cout << endl;
		cout << Out[i];
	}
}
//метод обработчика сигнала успешной вставки
void Base::PasteSymbol(Base* p_ob, string& str)
{
	if ((!(int(str[2]) <= int('z') && int(str[2]) >= int('a'))) && ((!
		(int(str[2]) <= int('Z') && int(str[2]) >= int('A'))))) {
		ofstream fout;
		fout.open("field.txt", ios::app);
		fout << "Not a letter of the Latin alphabet: " << str[2] << endl;
		return;
	}
	else {
		int X = int(str[0]) - 48;
		int Y = int(str[1]) - 48;
		string mystr;
		vector <string> out;
		ifstream fin("field.txt");
		int i = 1;
		while (getline(fin, mystr))
		{
			if (i == X) {
				mystr[Y - 1] = str[2];
			}
			out.push_back(mystr);
			i++;
		}
		fin.close();
		ofstream fout;
		fout.open("field.txt");
		for (auto i : out) {
			fout << i << endl;
		}
		fout.close();
	}
}
//сокращенная установка связи
void Base::SetConnections(Base* Second)
{
	set_conn(signalptr, Second, Second->hendlerptr);
}
//установка позиции вставки
void Base::SetPosition(int X, int Y, string a)
{
	string b = to_string(X) + to_string(Y) + a;
	if (X <= 0 || X > 10 || Y <= 0 || Y > 10) {
		ofstream FieldFile;
		FieldFile.open("field.txt", ios::app);
		FieldFile << "Coordinate is wrong ( " << X << ", " << Y << " )" << endl;
		return;
	}
	else {
		x = X;
		y = Y;
		emit_conn(signalptr, b);
		return;
	}

}

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>

using namespace std;

struct list;
struct s_list;
list *head = NULL;
list *node = NULL;
s_list *s_head = NULL;
s_list *s_node = NULL;
int *arr;
int *element;
int a_size, l_size, s_size, l_check = 0, a_check = 0, s_check = 0;

void a_insert(int *&arr, int &size);
void a_del_by_id(int *&arr, int &size, int id);
void a_del_by_value(int *&arr, int &size);
void a_get_by_id(int *& arr, int id, int *&element);
void a_get_by_value(int *&arr, int &size, int *element);
void array_by_size(int *&arr, int &size);
void array_from_file(int *&arr, int &size);
void array_by_elements(int *&arr, int &size);

list * create_list(int data);
void add_node(int data, list *head);
void add_node(int data, list *head);
void l_insert(list *&head, int &size);
void l_del_by_id(list *&head, int &size, int id);
void l_del_by_value(list *&head, int &size);
void l_get_by_id(list *&head, list *&element, int &size, int id);
void l_get_by_value(list *&head, list *&element, int &size);
void list_by_size(list *&head, int &size);
void list_from_file(list *&head, int &size);
void list_by_elements(list *&head, int &size);
void delete_list(list *&head, int &size);
void l_get(list *&head, int size, list *&element);

s_list * create_s_list(int data);
void s_add_node(int data, s_list *head);
void delete_s_list(s_list *&head, int &size);
void s_insert(s_list *&head, int &size);
void s_del_by_id(s_list *&head, int &size, int id);
void s_del_by_value(s_list *&head, int &size);
void s_get_by_id(s_list *&head, s_list *&element, int &size, int id);
void s_get(s_list *&head, int size, s_list *&element);
void s_get_by_value(s_list *&head, s_list *&element, int &size);
void s_list_by_size(s_list *&head, int &size);
void s_list_from_file(s_list *&head, int &size);
void s_list_by_elements(s_list *&head, int &size);

void menu(int &l_check, int &a_check, int &s_check, int *&arr);

void create_array(int &a_check)
{
	cout << "Create a dymanic array:" << endl << "1. by size;";
	cout << endl << "2. by elements;" << endl<< "3. from file?" << endl;
	int start;
	cin >> start;
	switch (start)
	{
	case 1:
	{
		array_by_size(arr, a_size);
		a_check++;
		menu(l_check, a_check, s_check, arr);
	}
	break;
	case 2:
	{
		array_by_elements(arr, a_size);
		a_check++;
		menu(l_check, a_check, s_check, arr);
	}
	break;
	case 3:
	{
		array_from_file(arr, a_size);
		a_check++;
		menu(l_check, a_check, s_check, arr);
	}
	break;
	default:
	{
		cout << "Invalid input! Please try again." << endl;
		create_array(a_check);
	}
	break;
	}
}

void a_delete(int &size)
{
	int id;
	cout << "Enter the index (from 0 to " << (size - 1) << ") of the element you want to delete:" << endl;
	cin >> id;
	cin.clear();
	if (id > (size - 1))
	{
		cout << "Invalid index! Please try again." << endl;
		a_delete(size);
	}
	else
	{
		chrono::time_point<chrono::system_clock> start, end;
		start = chrono::system_clock::now();
		a_del_by_id(arr, size, id);
		end = chrono::system_clock::now();
		int dur = chrono::duration_cast<chrono::seconds>(end - start).count();
		cout << endl << "Deleting an element took " << dur << " seconds." << endl;
	}
}

void a_get(int size, int *&element)
{
	int id;
	cout << "Enter the index (from 0 to " << (size - 1) << ") of the element you want to get:" << endl;
	cin >> id;
	cin.clear();
	if (id > (size - 1))
	{
		cout << "Invalid index! Please try again." << endl;
		a_get(size, element);
	}
	else
	{
		chrono::time_point<chrono::system_clock> start, end;
		start = chrono::system_clock::now();
		a_get_by_id(arr, id, element);
		end = chrono::system_clock::now();
		int dur = chrono::duration_cast<chrono::seconds>(end - start).count();
		cout << "The address of this element: " << element;
		//cout << endl << "The value of your node: " << (*element).data; doesnt work idk
		cout << endl << "Getting an element took " << dur << " seconds." << endl;
	}
}

void linked_list(int &l_check)
{
	cout << "Create a doubly linked list:" << endl << "1. by size;";
	cout << endl << "2. by elements;" << endl << "3. from file?" << endl;
	int start;
	cin >> start;
	switch (start)
	{
	case 1:
	{
		list_by_size(head, l_size);
		l_check++;
		menu(l_check, a_check, s_check, arr);
	}
	break;
	case 2:
	{
		list_by_elements(head, l_size);
		l_check++;
		menu(l_check, a_check, s_check, arr);
	}
	case 3:
	{
		list_from_file(head, l_size);
		l_check++;
		menu(l_check, a_check, s_check, arr);
	}
	break;
	default:
	{
		cout << "Invalid input! Please try again." << endl;
		linked_list(l_check);
	}
	break;
	}
}

void l_delete(int &size)
{
	int id;
	cout << "Enter the index (from 0 to " << (size - 1) << ") of the node you want to delete:" << endl;
	cin >> id;
	cin.clear();
	if (id > (size - 1))
	{
		cout << "Invalid index! Please try again." << endl;
		l_delete(size);
	}
	else
	{
		chrono::time_point<chrono::system_clock> start, end;
		start = chrono::system_clock::now();
		l_del_by_id(head, size, id);
		end = chrono::system_clock::now();
		int dur = chrono::duration_cast<chrono::seconds>(end - start).count();
		cout << endl << "Deleting a node took " << dur << " seconds." << endl;
	}
}

void singly_linked_list(int &s_check)
{
	cout << "Create a singly linked list:" << endl << "1. by size;";
	cout << endl << "2. by elements;" << endl << "3. from file?" << endl;
	int start;
	cin >> start;
	switch (start)
	{
	case 1:
	{
		s_list_by_size(s_head, s_size);
		s_check++;
		menu(l_check, a_check, s_check, arr);
	}
	break;
	case 2:
	{
		s_list_by_elements(s_head, s_size);
		s_check++;
		menu(l_check, a_check, s_check, arr);
	}
	case 3:
	{
		s_list_from_file(s_head, s_size);
		s_check++;
		menu(l_check, a_check, s_check, arr);
	}
	break;
	default:
	{
		cout << "Invalid input! Please try again." << endl;
		singly_linked_list(s_check);
	}
	break;
	}
}

void s_delete(int &size)
{
	int id;
	cout << "Enter the index (from 0 to " << (size - 1) << ") of the node you want to delete:" << endl;
	cin >> id;
	cin.clear();
	if (id > (size - 1))
	{
		cout << "Invalid index! Please try again." << endl;
		s_delete(size);
	}
	else
	{
		chrono::time_point<chrono::system_clock> start, end;
		start = chrono::system_clock::now();
		s_del_by_id(s_head, size, id);
		end = chrono::system_clock::now();
		int dur = chrono::duration_cast<chrono::seconds>(end - start).count();
		cout << endl << "Deleting a node took " << dur << " seconds." << endl;
	}
}

void menu(int &l_check, int &a_check, int &s_check, int *&arr)
{
	cout << "Please choose your option." << endl;
	/*cout << "1. Create a dynamic array;" << endl << "2. Create a linked list;" << endl;
	cout << "3. Insert a new element into a dynamic array;" << endl << "4. Insert a new node into a linked list;" << endl;
	cout << "5. Delete an element from a dynamic array by its index;" << endl;
	cout << "6. Delete a node from a linked list by its index;" << endl;
	cout << "7. Delete an element from a dynamic array by its value;" << endl;
	cout << "8. Delete a node from a linked list by its value;" << endl;
	cout << "9. Get an element from a dynamic array by its index;" << endl;
	cout << "10. Get a node from a linked list by its index;" << endl;
	cout << "11. Get an element from a dynamic array by its value;" << endl;
	cout << "12. Get a node from a linked list by its value." << endl;
	*/
	cout << "Dynamic array:" << endl << "1. Create a new array;" << endl << "2. Insert a new element;" << endl;
	cout << "3. Delete an element by its index;" << endl << "4. Delete an element by its value;" << endl;
	cout << "5. Get an element by its index;" << endl << "6. Get an element by its value." << endl;
	cout << "Doubly linked list:" << endl << "7. Create a new list;" << endl << "8. Insert a new node;" << endl;
	cout << "9. Delete a node by its index;" << endl << "10. Delete a node by its value;" << endl;
	cout << "11. Get a node by its index;" << endl << "12. Get a node by its value." << endl;
	cout << "Singly linked list:" << endl << "13. Create a new list;" << endl << "14. Insert a new node;" << endl;
	cout << "15. Delete a node by its index;" << endl << "16. Delete a node by its value;" << endl;
	cout << "17. Get a node by its index;" << endl << "18. Get a node by its value." << endl;
	int start0;
	cin >> start0;
	cin.clear();
	switch (start0)
	{
	case 1:
	{
		if (a_check > 0)
		{
			cout << "Note: creating a new dynamic array will delete the previous one." << endl;
			free(arr);
		}
		create_array(a_check);
	}
	break;
	case 2:
	{
		if (a_check == 0)
		{
			cout << "You need to create an array first." << endl;
			create_array(a_check);
		}
		else
		{
			a_insert(arr, a_size);
			menu(l_check, a_check, s_check, arr);
		}
	}
	break;
	case 3:
	{
		if (a_check == 0)
		{
			cout << "You need to create an array first." << endl;
			create_array(l_check);
		}
		else
		{
			a_delete(a_size);
			menu(l_check, a_check, s_check, arr);
		}
	}
	break;
	case 4:
	{
		if (a_check == 0)
		{
			cout << "You need to create an array first." << endl;
			create_array(l_check);
		}
		else
		{
			a_del_by_value(arr,a_size);
			menu(l_check, a_check, s_check, arr);
		}
	}
	break;
	case 5:
	{
		if (a_check == 0)
		{
			cout << "You need to create an array first." << endl;
			create_array(l_check);
		}
		else
		{
			cout << "Maintenance :( This option is not available right now." << endl;
			//a_get(a_size, element);
			menu(l_check, a_check, s_check, arr);
		}
	}
	break;
	case 6:
	{
		if (a_check == 0)
		{
			cout << "You need to create an array first." << endl;
			create_array(l_check);
		}
		else
		{
			cout << "Maintenance :( This option is not available right now." << endl;
			//a_get_by_value(arr, a_size, element);
			menu(l_check, a_check, s_check, arr);
		}
	}
	break;
	case 7:
	{
		if (l_check > 0)
		{
			cout << "Note: creating a new doubly linked list will delete the previous one." << endl;
			delete_list(head, l_size);
		}
		linked_list(l_check);
	}
	break;
	case 8:
	{
		if (l_check == 0)
		{
			cout << "You need to create a list first." << endl;
			linked_list(l_check);
		}
		else
		{
			l_insert(head, l_size);
			menu(l_check, a_check, s_check, arr);
		}
	}
	break;
	case 9:
	{
		if (l_check == 0)
		{
			cout << "You need to create a list first." << endl;
			linked_list(l_check);
		}
		else
		{
			l_delete(l_size);
			menu(l_check, a_check, s_check, arr);
		}
	}
	break;
	case 10:
	{
		if (l_check == 0)
		{
			cout << "You need to create a list first." << endl;
			linked_list(l_check);
		}
		else
		{
			l_del_by_value(head, l_size);
			menu(l_check, a_check, s_check, arr);
		}
	}
	break;
	case 11:
	{
		if (l_check == 0)
		{
			cout << "You need to create a list first." << endl;
			linked_list(l_check);
		}
		else
		{
			l_get(head, l_size, node);
			menu(l_check, a_check, s_check, arr);
		}
	}
	break;
	case 12:
	{
		if (l_check == 0)
		{
			cout << "You need to create a list first." << endl;
			linked_list(l_check);
		}
		else
		{
			l_get_by_value(head, node, l_size);
			menu(l_check, a_check, s_check, arr);
		}
	}
	break;
	case 13:
	{
		if (s_check > 0)
		{
			cout << "Note: creating a new singly linked list will delete the previous one." << endl;
			delete_s_list(s_head, l_size);
		}
		singly_linked_list(s_check);
	}
	break;
	case 14:
	{
		if (s_check == 0)
		{
			cout << "You need to create a list first." << endl;
			singly_linked_list(s_check);
		}
		else
		{
			s_insert(s_head, s_size);
			menu(l_check, a_check, s_check, arr);
		}
	}
	break;
	case 15:
	{
		if (s_check == 0)
		{
			cout << "You need to create a list first." << endl;
			singly_linked_list(s_check);
		}
		else
		{
			s_delete(s_size);
			menu(l_check, a_check, s_check, arr);
		}
	}
	break;
	case 16:
	{
		if (s_check == 0)
		{
			cout << "You need to create a list first." << endl;
			singly_linked_list(s_check);
		}
		else
		{
			s_del_by_value(s_head, s_size);
			menu(l_check, a_check, s_check, arr);
		}
	}
	break;
	case 17:
	{
		if (s_check == 0)
		{
			cout << "You need to create a list first." << endl;
			singly_linked_list(s_check);
		}
		else
		{
			s_get(s_head, s_size, s_node);
			menu(l_check, a_check, s_check, arr);
		}
	}
	break;
	case 18:
	{
		if (s_check == 0)
		{
			cout << "You need to create a list first." << endl;
			singly_linked_list(s_check);
		}
		else
		{
			s_get_by_value(s_head, s_node, s_size);
			menu(l_check, a_check, s_check, arr);
		}
	}
	break;
	default:
	{
		cout << "Invalid input! Please try again." << endl;
		menu(l_check, a_check, s_check, arr);
	}
	break;
	}
}

int main()
{
	menu(l_check, a_check, s_check, arr);
	return 0;
}

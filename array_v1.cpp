#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <malloc.h>

using namespace std;

void a_insert(int *&arr, int &size)
{
	chrono::time_point<chrono::system_clock> start, end;
	int id, value;
	cout << "Enter the index (from 0 to " << size << ") of a new element:" << endl;
	cin >> id;
	cin.clear();
	if (id > size)
	{
		cout << "Invalid index! Please try again." << endl;
		a_insert(arr, size);
	}
	else
	{
		size++;
		arr = (int*)realloc(arr, size * sizeof(int));
		cout << "Enter the value of a new element:" << endl;
		cin >> value;
		cin.clear();
		start = chrono::system_clock::now();
		if (id == (size-1))
		{
			arr[id] = value;
		}
		else
		{
	
			for (int i = (size - 1); i > id; i--)
				arr[i] = arr[i - 1];
			arr[id] = value;

		}
		end = chrono::system_clock::now();
		int dur = chrono::duration_cast<chrono::seconds>(end - start).count();
		cout << "The array was updated:" << endl;
		for (int i = 0; i < size; i++)
			cout << arr[i] << " ";
		cout << endl << "Inserting a new element took " << dur << " seconds." << endl;
	}
}

void a_del_by_id(int *&arr, int &size, int id)
{
	if (id == (size-1))
	{
		size--;
		arr = (int*)realloc(arr, size * sizeof(int));
	}
	else
	{
		for (int i = id; i < (size - 1); i++)
			arr[i] = arr[i + 1];
		size--;
		arr = (int*)realloc(arr, size*sizeof(int));
	}
	cout << "The array was updated:" << endl;
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
}

void a_del_by_value(int *&arr, int &size)
{
	chrono::time_point<chrono::system_clock> start, end;
	cout << "Enter the value of the element you want to delete:" << endl;
	cout << "Note: if there is more than one element wich such value only the last one will be deleted." << endl;
	int value;
	cin >> value;
	cin.clear();
	int count = 0, id;
	start = chrono::system_clock::now();
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == value)
		{
			id = i;
			count++;
		}
	}
	if (count == 0)
	{
		cout << "There is no such element! Please try again." << endl;
		a_del_by_value(arr, size);
	}
	else
	{
		a_del_by_id(arr, size, id);
		end = chrono::system_clock::now();
		int dur = chrono::duration_cast<chrono::seconds>(end - start).count();
		cout << endl << "Deleting an element took " << dur << " seconds." << endl;
	}
}

void a_get_by_id(int *&arr, int id, int *&element)
{
	*element = arr[id];
}

void a_get_by_value(int *&arr, int &size, int *element)
{
	chrono::time_point<chrono::system_clock> start, end;
	int id, value, count = 0;
	cout << "Enter the value of the element you want to get from the array:" << endl;
	cout << "Note: if there is more than one element wich such value only the last one will be gotten." << endl;
	start = chrono::system_clock::now();
	cin >> value;
	cin.clear();
	for (int i = 0; i < size; i++)
	{
		if (arr[i]==value)
		{
			count++;
			id = i;
		}
	}
	if (count == 0)
	{
		cout << "There is no such node in the list! Please try again." << endl;
		a_get_by_value(arr, size, element);
	}
	else
	{
		a_get_by_id(arr, id, element);
	}
	end = chrono::system_clock::now();
	int dur = chrono::duration_cast<chrono::seconds>(end - start).count();
	cout << "The address of this element: " << element;
	cout << endl << "The value of your node: " << *element << endl;
	cout << "Getting your element from the array took " << dur << " seconds." << endl;
}

void array_by_size(int *&arr, int &size)
{
	chrono::time_point<chrono::system_clock> start, end;
	cout << "Please enter the size of an array:" << endl;
	cin >> size;
	if (size == 0)
	{
		cout << "Invalid size! Please try again." << endl;
		array_by_size(arr,size);
	}
	else
	{
		srand(time(NULL));
		start = chrono::system_clock::now();
		arr = (int*)malloc(size * sizeof(int));
		start = chrono::system_clock::now();
		cout << "Your array of " << size << " randomised elements:" << endl;
		for (int i = 0; i < size; i++)
		{
			arr[i] = rand() % 100;
			cout << arr[i] << " ";
		}
		end = chrono::system_clock::now();
		int dur = chrono::duration_cast<chrono::seconds>(end - start).count();
		cout << endl << "Creating your array took " << dur << " seconds." << endl;
	}
}

void array_from_file(int *&arr, int &size)
{
	cout << "Enter your array of integers in array.txt. Use arabic numerals." << endl;
	cout << "To start the reading of the array type in any number and press enter." << endl;
	int start;
	cin >> start;
	cin.clear();
	ifstream data("array.txt");
	if (!data.is_open())
		cout << "Error! Can't acces the file." << endl;
	else
	{
		chrono::time_point<chrono::system_clock> start, end;
		start = chrono::system_clock::now();
		int temp;
		size = 0;
		while (!data.eof())
		{
			data >> temp;
			size++;
		}
		if (size == 0)
		{
			cout << "The file is empty! Please try again." << endl;
			data.close();
			array_from_file(arr, size);
		}
		else
		{
			cout << "Your array of " << size << " elements:" << endl;
			arr = (int*)malloc(size * sizeof(int));
			data.seekg(0, data.beg);
			for (int i = 0; i < size; i++)
				data >> arr[i];
			data.close();
			end = chrono::system_clock::now();
			int dur = chrono::duration_cast<chrono::seconds>(end - start).count();
			for (int i = 0; i < size; i++)
				cout << arr[i] << " ";
			cout << endl << "Reading your array took " << dur << " seconds." << endl;
		}
	}
}

void array_by_elements(int *&arr, int &size)
{
	cout << "Please enter your array of integers, each of new line:" << endl;
	cout << "Make sure that the last element of your array is 0." << endl;
	chrono::time_point<chrono::system_clock> start, end;
	int value = 1, i = 1;
	arr = (int*)malloc(i * sizeof(int));
	start = chrono::system_clock::now();
	while (value != 0)
	{
		cin >> value;
		cin.clear();
		arr[i - 1] = value;
		i++;
		arr = (int*)realloc(arr, i * sizeof(int));
	}
	size = i-1;
	end = chrono::system_clock::now();
	int dur = chrono::duration_cast<chrono::seconds>(end - start).count();
	cout << "Your array of " << size << " elements:" << endl;
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << endl << "Creating your array took " << dur << " seconds." << endl;
}
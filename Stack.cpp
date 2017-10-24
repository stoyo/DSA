#include <iostream>

using namespace std;

template <typename T>
class DynamicStack {
private:
	T* array;      //Array with the values of the stack
	int topIndex; // Top element index
	int capacity; // Capacity of the stack

	bool full() const { return topIndex == capacity - 1; } //Checks if the stack is full
	void resize();                                         //Doubles the capacity

public:
	DynamicStack();                                    // Default constructor
	DynamicStack(const DynamicStack<T>&);              // Copy constructor
	DynamicStack& operator = (const DynamicStack<T>&); // Predefine operator =
	~DynamicStack() { delete array; };                  // Destructor

	bool empty() const { return topIndex == -1; }          //Checks if the stack is empty
	void push(T const& value);                //Adds a new element to the stack
	T pop();                                  //Removes the top element
	T top() const { return array[topIndex]; } //Returns the top element value
	int size() const { return topIndex + 1; }     //Returns the size of the stack
	void swap(int, int);                      //Exchanges the places of two elements from the current stack
	void swapstack(DynamicStack&);            // Exchanges the content of the current stack with a stack, submitted as an argument

											  //friend ostream& operator<<(ostream& ,const DynamicStack<T>&)
	friend ostream& operator<<(ostream& os, const DynamicStack<T>& other)
	{
		if (other.empty()) {
			os << "Empty stack!\n";
		}
		else {
			for (int i = 0; i <= other.topIndex;i++)
				os << other.array[i] << " ";
		}
		return os;
	} // Output the stack
};

template<typename T>
DynamicStack<T>::DynamicStack() : array(NULL), topIndex(-1), capacity(10) {
	array = new T[capacity];
}

template<typename T>
DynamicStack<T>::DynamicStack(const DynamicStack<T> &other) : array(NULL), topIndex(other.topIndex), capacity(other.capacity) {
	array = new T[capacity];
	for (int i = 0; i < capacity; i++) {
		array[i] = other.array[i];
	}
}

template<typename T>
DynamicStack<T>& DynamicStack<T>:: operator= (const DynamicStack<T> &other) {
	if (this != &other) {
		delete[] array;
		topIndex = other.topIndex;
		capacity = other.capacity;
		array = new T[capacity];
		for (int i = 0; i <= topIndex; i++)
			array[i] = other.array[i];
	}
	return *this;
}

template<typename T>
void DynamicStack<T>::resize()
{
	T* temp = array;
	capacity *= 2;
	array = new T[capacity];
	for (int i = 0; i <= topIndex; i++)
		array[i] = temp[i];
	delete[] temp;
}

template <typename T>
void DynamicStack<T>::push(T const& value) {
	if (full()) resize();
	array[++topIndex] = value;
}

template <typename T>
T DynamicStack<T>::pop() {
	if (empty()) {
		cerr << "Empty stack!" << endl;
	}
	else {
		return array[topIndex--];
	}
}

template <typename T>
void DynamicStack<T>::swap(int first, int second) {
	if (empty()) {
		cerr << "Empty Stack!\n";
	}
	else {
		if ((first >= 1 && first <= topIndex + 1) && (second >= 1 && second <= topIndex + 1)) {
			T temp = array[first - 1];
			array[first - 1] = array[second - 1];
			array[second - 1] = temp;
		}
		else
			cerr << "Incorrect index!\n";
	}
}

template <typename T>
void DynamicStack<T>::swapstack(DynamicStack& other) {

	T* temp = array;
	array = other.array;
	other.array = temp;

	int tempInt = capacity;
	capacity = other.capacity;
	other.capacity = tempInt;

	tempInt = topIndex;
	topIndex = other.topIndex;
	other.topIndex = tempInt;
}


int main()
{
	DynamicStack<double> st1;
	for (int i = 1;i <= 10;i++) {
		st1.push(i);
	}
	cout << st1 << "\nFinished test 1.\n";
	cout << st1.pop() << "\n" << st1 << "\nFinished test 2.\n";

	st1.swap(3, 4);
	st1.swap(5, 6);
	st1.swap(1, st1.size());
	cout << st1 << "\nFinished test 3.\n";

	cout << st1.top();

	DynamicStack<double> ds;
	ds = st1;
	cout << st1 << "\n" << ds << "\nFinished test 4.\n";

	DynamicStack<double> ds2(ds);
	cout << ds << "\n" << ds2 << "\nFinished test 5.\n";

	cout << "\n" << ds2 << "\n";
	for (int i = 1; i < 5; i++) {
		cout << i << ".Popped element: " << ds2.pop() << "\nCurrent state of the stack:\n" << ds2 << "\n";
	}
	cout << "Finished test 6.\n" << endl;

	cout << "\n" << ds2 << "\n" << ds << "\nSwapping...\n";
	ds2.swapstack(ds);
	cout << ds2 << "\n" << ds << "\nFinished test 7.\n";

	cout << "\n" << ds << "\nFunction 'size()' answer: " << ds.size() << "\nFinished test 8.\n";

	cout << "\n" << st1 << "\n";
	while (!st1.empty()) { st1.pop(); }
	cout << st1 << "Test Finished 9.\n";

	return 0;
}
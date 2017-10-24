
#include <algorithm>
#include <iostream>
#include <cstring>
#include <string>
#include <stdexcept>
using namespace std;


//!!!!!IMPORTANT
//The code for the class DrinkMachine starts at line 206
//If you don't read this have fun scrolling down to there :)


class Drinkable {
private:
    char* brand=NULL;
    int quantity=0;
public:
    Drinkable () {
        quantity = 0;
        brand=new char[1];
        brand[0]='\0';
    }

    Drinkable (Drinkable const &drnk) {
        setQuantity(drnk.getQuantity());
        setBrand(drnk.getBrand());

    }

    Drinkable &operator= (Drinkable const &drnk) {
        if (this != &drnk) {
            setQuantity(drnk.getQuantity());
            setBrand(drnk.getBrand());
        }

        return *this;
    }

    ~Drinkable () {
        delete[] brand;
    }

    void setQuantity(int newQuantity){
        if(newQuantity>=0)
            quantity = newQuantity;
        else quantity=0;

    }

    int getQuantity() const {
        return quantity;
    }

    char &operator[](int index)const{
        if(brand!=NULL && index>=0 && index<strlen(brand))
            return brand[index];

    }

    char* getBrand() const {
        return brand;
    }

    void setBrand(char const* newBrand) {
        if(brand!=NULL)
          delete[] brand;
        brand = new char[strlen(newBrand)+1];
        strcpy(brand, newBrand);
    }

    friend ostream& operator<< (ostream &output, Drinkable const& drnk) {

        output<<drnk.brand;

        output << " " << drnk.getQuantity()<<endl;

        return output;
    }
    void sell(){
        quantity-=1;
    }
};

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
    ~DynamicStack() { delete[] array; };                  // Destructor

    bool empty() const { return topIndex == -1; }          //Checks if the stack is empty
    void push(T const& value);                //Adds a new element to the stack
    T pop();                                  //Removes the top element
    T& top()const{ return array[topIndex]; } //Returns the top element value
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


class DrinkMachine{
private:
    DynamicStack<Drinkable> drinks;
    int capacity, current;
    bool validBrand(Drinkable const& drink){
        return drink.getBrand()!="Derby" && drink.getBrand()!="derby";
    }
    bool hasCapacity(Drinkable const& drink){
        return drink.getQuantity()+current<=capacity;
    }
public:
    DrinkMachine(){
        capacity=0;
        current=0;
    }
    DrinkMachine(int cap){
        capacity=(cap<0)? 0:cap;
    }

    DrinkMachine(int cap, DynamicStack<Drinkable> &drink){
        capacity=(cap<0)? 0:cap;
        while(!drink.empty()){
            addDrink(drink.top());
            drink.pop();
        }
    }

    void addDrink(Drinkable const& drink){
        if(validBrand(drink) && hasCapacity(drink))
        {
            current+=drink.getQuantity();
            drinks.push(drink);
        }
    }
    void sellDrink(){
        if(drinks.top().getQuantity()==0 && !drinks.empty())drinks.pop();
        if(drinks.empty())
        {
            throw runtime_error("The machine is empty, therefore it can not sell you a drink!");
        }
        drinks.top().sell();
        if(drinks.top().getQuantity()==0)drinks.pop();
        current--;
        /*Drinkable drnk(drinks.top());
        drnk.sell();
        drinks.pop();
        current-=(drnk.getQuantity()+1);
        addDrink(drnk);*/
        //Bad Workaround for the T top() in the stack which is now T& top
    }


    int const getCapacity()const{
        return capacity;
    }
    void increaseCapacityBy(int cap)
    {
        if(cap<0)
            throw runtime_error("You can not increase the capacity by a negative number!");
        capacity+=cap;
    }
    DrinkMachine &operator=(DrinkMachine const& dm){
        if(this!=&dm){
            drinks=dm.drinks;
            capacity=dm.capacity;
            current=dm.current;
        }
        return *this;
    }
    friend ostream& operator<<(ostream& os, DrinkMachine const& dm){
        os<<"The loaded drinks into the machine are: "<< dm.drinks << endl<< "The empty drink slots in this machine are: "<<dm.capacity-dm.current<<endl;
        return os;
    }

};
int main(){
    Drinkable mtndew;
    mtndew.setBrand("Mountain Dew");
    mtndew.setQuantity(10);
    cout << mtndew << endl;
    Drinkable empty;
    cout << empty << endl;
    cout << "Test 1 success\n";

    cout << mtndew.getBrand() << endl;
    cout << mtndew.getQuantity() << endl;
    cout << empty.getBrand() << endl;
    cout << empty.getQuantity() << endl;
    cout << "Test 2 success\n";

    Drinkable drink;
    drink = mtndew;
    cout << drink << endl;
    drink = empty;
    cout << drink << endl;
    cout << "Test 3 success\n";

    Drinkable drink1(empty);
    cout << drink1 << endl;
    Drinkable drink2(mtndew);
    cout << drink2 << endl;
    cout << "Test 4 success\n";

    Drinkable drink3;
    drink3.setBrand("Cola");
    drink3.setQuantity(-2);
    cout << drink3 << endl;
    drink3.setQuantity(5);
    cout << drink3 << endl;
    cout << "Test 5 success\n";

    cout << "Drinkable succeed all tests!\n";

    DrinkMachine dm;
    dm.increaseCapacityBy(100);
    cout << dm << endl;
    cout << "Test 6 success\n";

    dm.addDrink(mtndew);
    dm.addDrink(empty);
    dm.addDrink(drink3);
    cout << dm << endl;
    cout << "Test 7 success\n";

    dm.sellDrink();
    cout << dm << endl;
    dm.sellDrink();
    dm.sellDrink();
    cout << dm << endl;
    cout << "Test 8 success\n";

    dm.sellDrink();
    DrinkMachine drinkmachine(dm);
    drinkmachine.sellDrink();
    cout<<drinkmachine<<endl;
    cout << "Test 9 success\n";

    DrinkMachine dm2;
    dm2=drinkmachine;
    dm2.sellDrink();
    cout<<dm2<<endl;
    cout << "Test 10 success\n";
    return 0;
}
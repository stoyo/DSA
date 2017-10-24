#include <iostream>

using namespace std;

template <typename T>
class Node
{
    public:
        T data;
        Node* previous;
};

template<typename T>
class Stack
{
private:
    Node<T> *tip;
    int cap;
public:
    Stack()
    {
        tip=NULL;
        cap=0;
    }
    ~Stack(){
         while(!empty()){
             Node<T>* temp=tip;
             tip=tip->previous;
             delete temp;
             cap--;
         }   
    }
    Stack(Stack<T> const& stack){
        
        cap=stack.cap;
        if(cap>=1){
            Node<T>* temp=stack.tip;
            for(int i=0;i<cap;i++){
                push(temp->data);
                temp=temp->previous;
            }
        }
        else
            tip=NULL;
    }

    Stack& operator=(Stack<T> const& stack){
        if(this!=&stack){
            if(!empty()){
                while(!empty()){
                    Node<T>* temp=tip;
                    tip=tip->previous;
                    delete temp;
                    cap--;
                }   
            }

            cap=stack.cap;
            if(cap>=1){
                Node<T>* temp=stack.tip;
                for(int i=0;i<cap;i++){
                    push(temp->data);
                    temp=temp->previous;
                }
            }
            else
                tip=NULL;

        }
        return *this;
    }

    void push(T const& value) {
        Node<T> *ptr= new Node<T>;
        ptr->data = value;
        if(tip!=NULL)
            ptr->previous = tip;
        tip=ptr;
        cap++;
    }

    T pop() {
        T x;
        Node<T> *temp;
        if(empty())
        {
            throw runtime_error("The Stack is already empty you can't pop() more");
        }
        temp = tip;
        x=tip->data;
        tip = tip->previous;
        cap--;
        delete temp;
        return x;
    }

    void show() {
        Node<T> *ptr1 = tip;
        while(ptr1 != NULL)
        {
            cout << ptr1->data << " -> ";
            ptr1 = ptr1->previous;
        }
    }

    bool empty() const {
        return cap==0;
    }

    int const size() const {
        return cap;
    }

    T top () const{
        return tip->data;
    }

    void swap (int pos1, int pos2) {
        int end = max(pos1, pos2);
        int start = min(pos1, pos2);

        if(start >= 1 && end <= size() && start != end){
            Node<T> *fromTo = tip;
            Node<T> *toFrom = tip;

            for(int i = cap; i-1 > start; i--){
                if(i-1 > end) {
                    fromTo = fromTo->previous;
                }
                toFrom = toFrom->previous;
            }

            T temp = fromTo->data;
            fromTo->data = toFrom->data;
            toFrom->data = temp;
        }
        else if(end==start)
            cerr<<"You shan't swap an element with itself, dummy!"<<endl;
        else {
            cout << "Invalid arguments!" << endl;
        }
    }

    void swapstack (Stack& stack) {
        Node<T> *temp = tip;
        tip = stack.tip;
        stack.tip = temp;

        T tempcap=stack.cap;
        stack.cap=cap;
        cap=tempcap;
    }
    friend ostream& operator<<(ostream& os,Stack<T> const& stack){
        if(stack.empty())
            os<<"Empty stack!"<<endl;
        else{
            Node<T>* temp=stack.tip;
            for(int i=0;i<stack.cap;i++){
                os<<temp->data<<'\t';
                temp=temp->previous;
            }
            os<<endl;
        }
        return os;
    }
};

int main()
{
    Stack<double> st1;
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
    cout<< st1.pop();
	Stack<double> ds;
	ds = st1;
	cout << st1 << "\n" << ds << "\nFinished test 4.\n";

    Stack<double> ds2(ds);
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

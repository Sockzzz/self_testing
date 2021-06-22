    #include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;

///stack, array based implementation, size is fixed to 10, would have to be altered slightly to make it grow

struct stack{
    int contents[10];
    int size=0;
};

typedef struct stack;
//If a declaration uses typedef as storage-class specifier, every declarator in it defines an identifier as an alias to the type specified, ex: typedef A int; => that 'A' can be used to declare an int now => A myNum = 3; is a acceptable statement

bool hasRoom(stack myS){
    if(myS.size==10){
        cout<<"Stack is full, cannot add new item"<<endl;
        return false;
    }
    return true;

}

void addPiece(stack& myS, int toAdd){

    if(hasRoom(myS)==false){
        return;
    }
    else {
        myS.contents[myS.size] = toAdd;
        myS.size=myS.size+1;
    }

}

void removePiece(stack& myS){

    if(myS.size!=0){
        myS.size--;
    }

}

void printStack(stack myS){

    for(int i = 0; i < myS.size; ++i){
        cout<<myS.contents[i]<<endl;
    }

}

void run_array_stack(){

    stack myS;
    addPiece(myS,1);
    addPiece(myS,2);
    addPiece(myS,3);
    addPiece(myS,4);
    addPiece(myS,5);
    addPiece(myS,6);
    addPiece(myS,7);
    addPiece(myS,8);
    addPiece(myS,9);
    addPiece(myS,10);

    printStack(myS);
}

///stack linked list application
struct stack_node{

    int data;
    stack_node* next= nullptr;

};

class ll_stack{
private:
    stack_node* head;

public:

    ll_stack(int first_data);
    void push(int data);
    void pop();
    void printStack();
    ~ll_stack();

};

ll_stack::ll_stack(int first_data) {
    head = new stack_node;
    head->data=first_data;
}

void ll_stack::push(int data) {
    stack_node* temp = new stack_node;
    temp->data = data;
    temp->next = this->head;
    head = temp;
}

void ll_stack::pop() {
    stack_node* toDelete = head;
    head = head->next;
    delete toDelete;
}

void ll_stack::printStack() {
    stack_node* temp = head;
    while(temp!= nullptr){
        cout<<temp->data<<endl;
        temp = temp->next;
    }
}

ll_stack::~ll_stack() {
    stack_node* temp = head;
    stack_node* holder = head;
    while(temp!= nullptr){
        holder = holder ->next;
        delete temp;
        temp = holder;
    }
}

void run_ll_stack(){
    ll_stack myStack(1);
    myStack.push(2);
    myStack.push(3);
    myStack.push(4);
    myStack.push(5);
    myStack.push(6);
    myStack.push(7);
    myStack.push(8);
    myStack.push(9);
    myStack.push(10);

    myStack.printStack();
    cout<<endl;

    myStack.pop();
    myStack.pop();
    myStack.pop();
    myStack.pop();
    myStack.pop();

    myStack.printStack();
}


///Queue Array Based implementation (circular queue [best array implementation]) Note this array will be 10 items large, a scaling function to increase the size would have to be introduced to increase the size dynamically

#define SIZE_ARRAY_Q 10

class array_Q{
private:
    int items[SIZE_ARRAY_Q];
    int head = -1;
    int tail = -1;

public:
    bool isFull();
    bool isEmpty();
    void push(int data);
    void pop();
    void print();
};

bool array_Q::isFull() {
    if(head == 0 && tail == SIZE_ARRAY_Q - 1)
        return true;

    if(head == tail +1)
        return true;

    return false;
}

bool array_Q::isEmpty() {
    if(head == -1)
        return true;
    return false;
}

void array_Q::push(int data) {
    if(isFull()) {
        cout << "Queue is full cannot add element." << endl;
        return;
    }
    if(isEmpty()){
        head = 0;
        tail = 0;

        items[head] = data;
        cout<<"Inserted: "<<data<<" into Queue."<<endl;
        return;
    }
    tail = (tail + 1) % SIZE_ARRAY_Q;
    items[tail] = data;
    cout<<"Inserted: "<<data<<" into Queue."<<endl;
}

void array_Q::pop() {
    if(isEmpty()){
        cout<<"Queue is empty, cannot remove."<<endl;
    }
    else if(head == tail){
        head = tail = -1;
    }
    else {
        head = (head + 1) % SIZE_ARRAY_Q;
    }
}

void array_Q::print() {
    int temp;
    if(isEmpty())
        cout<<"Queue is empty, cannot print."<<endl;
    else if(head == tail){
        cout<<items[temp]<<endl;
    }
    else if(head<tail){
        for(temp = head; temp <= tail; ++temp){
            cout<<items[temp]<<endl;
        }
    }
    else{
        int cutoff = tail;
        for(temp = head; temp<SIZE_ARRAY_Q; ++temp){
            cout<<items[temp]<<endl;
        }
        for(temp = 0; temp<=tail; ++temp){
            cout<<items[temp]<<endl;
        }
    }
}

void run_array_circular_array(){
    array_Q myA;
    myA.push(1);
    myA.push(2);
    myA.push(3);
    myA.push(4);
    myA.push(5);
    myA.push(6);

    cout<<"First Print: "<<endl;
    myA.print();

    myA.pop();
    myA.pop();
    myA.pop();
    myA.pop();

    cout<<"Second Print: "<<endl;
    myA.print();


    myA.push(7);
    myA.push(8);
    myA.push(9);
    myA.push(10);
    myA.push(11);
    myA.push(12);
    myA.push(13);
    myA.push(14);
    myA.push(15);

    cout<<"Third Print: "<<endl;
    myA.print();
}

///Priority Queue implementation using Heap data structure; array will be of size 20, as with previous, growth functions could be implemented as well as switching to a vector instead of array for use constraints
#define PQ_ARRAY_SIZE 20

int pQ_list[PQ_ARRAY_SIZE];


void heapifyPQ(int (&arr)[PQ_ARRAY_SIZE], int size, int i){
    //cout<<"entered heapify"<<endl;
    int largest = i;
    int Lchild = (2*i) + 1;
    int Rchild = (2*i) + 2;
    cout<<"entered heap with arr[i]= "<<arr[i]<<endl;

    if(Lchild<size && arr[Lchild]>arr[i]){
        largest = Lchild;
        cout<<"value of arr[Lchild]: " << arr[Lchild]<<endl;
    }
    if(Rchild<size && arr[Rchild]>arr[i]){
        largest = Rchild;
        cout<<"value of arr[Rchild]: " << arr[Rchild]<<endl;
    }

    if(largest != i){
        cout<<"entered if"<<endl;
        //swap arr[i] with arr[largest]
        int temp = arr[i];
        arr[i]= arr[largest];
        arr[largest] = temp;

        //recursion call heapify again with largest as new i
        heapifyPQ(arr, size, largest);

    }
}

    void basic_printPQ(int (&arr)[PQ_ARRAY_SIZE], int &usedSpace){
        for(int i = 0; i<usedSpace; ++i){
            cout<<arr[i]<<endl;
        }
    }
//when inserting must be put in the array based on current place value and if the toAdd value is larger or smaller; regarding which one it must be places based on the left or right child using rule; since were using an array, keep track of usedSpace with local variable in the function
void insertPQ(int (&arr)[PQ_ARRAY_SIZE], int data, int &usedSpace){
    if(usedSpace == 0){
        arr[usedSpace] = data;
        ++usedSpace;
    }
    else{
        arr[usedSpace] = data;
        ++usedSpace;
        for(int i = (usedSpace/2) - 1; i >=0; i--){
            heapifyPQ(arr,usedSpace,i);

        }
    }
}


void deletePQ(int (&arr)[PQ_ARRAY_SIZE], int &usedSpace, int toRemove){ //in this implementation, the data itself must be given to remove
    int i;
    for(i = 0; i<usedSpace; ++i){
        if(arr[i]==toRemove)
            break;
    }
    int temp = arr[usedSpace-1];
    arr[usedSpace-1] = arr[i];
    arr[i] = temp;

    --usedSpace;
    for(int i = (usedSpace/2) - 1; i >=0; --i){
        heapifyPQ(arr,PQ_ARRAY_SIZE,i);
    }
}

void inOrderPQ(int (&arr)[PQ_ARRAY_SIZE], int &i){

    int largest = i;
    int Lchild = (2*i) + 1;
    int Rchild = (2*i) + 2;


}

void run_priorityQ_function(){

    int usedSpace = 0;
    int myA[PQ_ARRAY_SIZE];


    insertPQ(myA, 5, usedSpace);
    insertPQ(myA, 3, usedSpace);
    insertPQ(myA, 2,usedSpace);
    insertPQ(myA, 4, usedSpace);


    basic_printPQ(myA,usedSpace); cout<< endl;

    cout<<endl;

    //basic_printPQ(myA,usedSpace);
    cout <<endl<< "Hello, World!" << endl;

}

///Red black tree aka the better 2-3-4 trees; suck my ass
/*



*/


int main() {





    return 0;
}

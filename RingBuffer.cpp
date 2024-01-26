// RingBuffer.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
author: colin harding

RingBuffer is a circular queue 

uses vector as the memory space
queue is contained by head and tail positions
size is the queue size NOT the vector size

vars are public because well im lazy and did not want to use gets and sets since no one should be using this to mess with the code un intentionally
but i made them :)

i was inspired by the stack when you use malloc since its the hackers dream but im also lazy so im not replacing those things because that was harder than ifs 


main is defined to the pdf specifications but can be ignored

How does a computer eat? With mega-bytes.
feel free to give a 100% for the joke


*/
#include <iostream>
#include <vector>

using namespace std;

template <class T>
class Queue
{
  
public:  // vars
    vector<T> ringBuff;
    int head = 0;
    int tail = 0;
    int size = 0;
    
private: // vars


public:  //get set methods
    template <class T>
    void setVector(vector<T> x) {
        head = x;
    }
    template <class T>
    vector<T> getVector() {
        return ringBuff;
    }

    void setHead(int x) {
        head = x ;
    }
    int getHead() {
        return head;
    }
    void setTail(int x) {
        tail = x;
    }
    int getTail() {
        return tail;
    }
    void setSize(int x) {
        size = x;
    }
    int getSize() {
        return size;
    }


public:  //methods
   
    template <class T>
    void push(T x) {
        vector<T> temp;
       
        if (empty()) {//if queue is empty
            if(ringBuff.size() == 0){//first use
                ringBuff.push_back(x);
                size = 1;
            }
            else {//if it isnt empty but is marked empty
                ringBuff.at(head)=x;
                size = 1;
            }
            

        }else if (full()) {  
            //increase the size of the queue ||| add the element to just fill because size wont reflect they exist. you know, like the stack [(winky smirking face with a monocle)[[[
            for (int i = head; i < ringBuff.size(); i++) {//save the queue to be moved since tail is anchored we only worry about what is after head whether tail is after it does not matter
                temp.push_back(ringBuff.at(i));
            }//end for


            for (int i = size; i < (size * 2); i++) {//add space doesnt matter what it is
                ringBuff.push_back(x);
            }//end for
            

            int j = 0;
            for (int i = (-size + tail + ringBuff.size() + 1) % ringBuff.size(); j < temp.size(); i++) {//re inserts the queue in the right spot after being increased
                
                ringBuff.at(i) = temp.at(j);


                if (j == 0) {
                    head = i;
                               }


                j++;
            }//end for

            //add vvvv and adjust
            ringBuff.at(tail + 1) = x;
            tail =(tail+ 1)%ringBuff.size();
            size++;

        }else {//there is actually space for these bad boys
            //add vvvv and adjust
            ringBuff.at((tail+1)%ringBuff.size()) = x;
            tail = (tail + 1) % ringBuff.size();
            size++;

        }

        return;
       
    }


    void pop() {// we are now david copperfield and make things disappear even though they are definitely still there. 
        // just change position of head and ignore the old head
       
        size = size - 1;
        head = (head + 1)%ringBuff.size();
       
        return;

    }

    
    template <class T>
    T peek() {//return head if it exists otherwise null
        if (size == 0){
            return NULL;
        }else {
            return ringBuff.at(head);
        }
    }

    bool empty() {// this checks the queue not the vector size
        if (size == 0)
            return true;
        else {
            return false;
        }
    }


    bool full() {// if queue size is vector size, queue is full

        if (size == ringBuff.size()) {
            return true;
        }
        else {
            return false;
        }

    }


    void print() {// prints the queue without formatting
        cout << "queue: ";
        for (int i = 0; i < size; i++) {
            cout << ringBuff.at((i + head) % ringBuff.size()) << " ";
        }
        cout << endl;
    }


    void starPrint() {// see << overloading
        cout << "star: ";
        if (size == 0) {
            for (int i = 0; i < ringBuff.size(); i++) {
                if (i == head && i == tail) {
                    cout << "*ht ";
                }
                else {
                    cout << "* ";

                }
            }


        }
        else if (tail < head) {

            for (int i = 0; i < ringBuff.size(); i++) {

                if (i < tail) {
                    cout << ringBuff.at(i) << " ";
                }
                else if (i == tail) {
                    cout << ringBuff.at(i) << "t ";
                }
                else if (i == head) {
                    cout << ringBuff.at(i) << "h ";

                }
                else if (i > tail && i < head) {
                    cout << "*" << " ";

                }if (i > head) {
                    cout << ringBuff.at(i) << " ";
                }



            }//end for
        }
        else if (tail == head) {
            for (int i = 0; i < ringBuff.size(); i++) {
                if (i == head && i == tail) {
                    cout << ringBuff.at(i) << "ht ";
                }
                else {
                    cout << "* ";

                }
            }


        }
        else {

            for (int i = 0; i < ringBuff.size(); i++) {
                if (i == head) {
                    cout << ringBuff.at(i) << "h ";
                }
                else if (i < head) {
                    cout << "*" << " ";

                }
                else if (i < tail) {
                    cout << ringBuff.at(i) << " ";
                }
                else if (i == tail) {
                    cout << ringBuff.at(i) << "t ";
                }

                else {
                    cout << "*" << " ";
                }

            }



        }//end large if else
        cout << endl;
    }


private: //methods
    

public://constructors
    
    Queue() {
             
    }
    

public://overload

    template <class T>
    friend ostream& operator<<(ostream& os, const Queue<T>& q);


};//end queue class

template <class T>
ostream& operator<<(ostream& os, const Queue<T>& q)
{
    if (q.ringBuff.size() == 0) {
    os << "no elements";

    }
    else if (q.size == 0) {//when the queue size is 0
        for (int i = 0; i < q.ringBuff.size(); i++) {
            if (i == q.head && i == q.tail) {
                os << "*ht ";
            }
            else {
                os << "* ";

            }
        }


    }
    else if (q.tail < q.head) {//when it is wrapped print

        for (int i = 0; i < q.ringBuff.size(); i++) {

            if (i < q.tail) {
                os << q.ringBuff.at(i) << " ";
            }
            else if (i == q.tail) {
                os << q.ringBuff.at(i) << "t ";
            }
            else if (i == q.head) {
                os << q.ringBuff.at(i) << "h ";

            }
            else if (i > q.tail && i < q.head) {
                os << "*" << " ";

            }if (i > q.head) {
                os << q.ringBuff.at(i) << " ";
            }



        }//end for
    }
    else if (q.tail == q.head) {// 1 element
        for (int i = 0; i < q.ringBuff.size(); i++) {
            if (i == q.head && i == q.tail) {
                os << q.ringBuff.at(i) << "ht ";
            }
            else {
                os << "* ";

            }
        }


    }
    else {// in a line no wrapping

        for (int i = 0; i < q.ringBuff.size(); i++) {
            if (i == q.head) {
                os << q.ringBuff.at(i) << "h ";
            }
            else if (i < q.head) {
                os << "*" << " ";

            }
            else if (i < q.tail) {
                os << q.ringBuff.at(i) << " ";
            }
            else if (i == q.tail) {
                os << q.ringBuff.at(i) << "t ";
            }

            else {
                os << "*" << " ";
            }

        }



    }//end large if else
    os << endl;
    return os;
}

int main()
{
    Queue<int> queue;
    cout << queue;
    for (int j = 0; j < 3; j++) {
        cout << "Push " << 10 * (j + 1) << " items" << endl;
        for (int i = 0; i < 10 * (j + 1); i++) {
            queue.push(i);
           // queue.starPrint();
            cout << queue;
        }
        cout << endl;
        cout << "Pop " << 9 * (j + 1) << " items" << endl;
        for (int i = 0; i < 9 * (j + 1); i++) {
            queue.pop();
            //queue.starPrint();
            cout << queue;
        }
        cout << endl;
    }


   
}


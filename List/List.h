#pragma once

#include <iostream>
#include <assert.h>
using std::cout;
using std::endl;

template<class T>
  struct ListNode
  {
    T _data;
    ListNode<T>* _next;
    ListNode<T>* _prev;

    ListNode(const T& data = T())
      :_data(data)
       ,_next(NULL)
       ,_prev(NULL)
    {}

  };
  //迭代器的实现 
  template<class T,class Ref,class Ptr>
    struct _ListIterator
    {
      typedef ListNode<T> Node;
      typedef _ListIterator<T,Ref,Ptr> Self;

      Node* _node;

      _ListIterator(Node *node)
                :_node(node)
      {}

      Ref operator*()
      {
        return _node->_data;
      }

      Self& operator++()
      {
        _node = _node->_next;
        return *this;
      }

      bool operator!=(const Self& t1)
      {
        return _node != t1._node;
      }
    };

  template<class T>
    class List 
    {
      typedef ListNode<T> Node;
    public:
      typedef _ListIterator<T,T&,T*> iterator;
      typedef _ListIterator<T,const T&,const T*> const_iterator;
      iterator begin()
      {
        return _head->_next;
      }

      iterator end()
      {
        return _head;
      }

      const_iterator cbegin()const 
      {
        return _head->_next;
      }

      const_iterator cend()const 
      {
        return _head;
      }

      List()
        :_head(new Node)
      {
        _head->_next = _head;
        _head->_prev = _head;
      }

      List(const List<T>& l)
      {
        _head = new Node;
        _head->_next = _head;
        _head->_prev = _head;
        const_iterator it = l.cbegin();
        while(it != l.cend())
        {
          PushBack((*it));
          ++it;
        }
      }

      ~List()
      {
        Clear();
        delete _head;
        _head = NULL;
      }

      List<T>& operator=(List<T> l)
      {
        if(*this != l)
        {
          Swap(l);
        }
        return *this;
      }

      void Clear()
      {
        Node* cur = _head->_next;
        while(cur != _head){
          Node* tmp = cur->_next;
          delete cur;
          cur = tmp;
        }
        _head->_next = _head;
        _head->_prev = _head;
      }

      void Swap(List<T> l)
      {
        swap(_head,l._head);
      }
      
      //成员函数
      void PushBack(const T& x)
      {
        //Node* tmp = new Node(x);
        //Node* tail = _head->_prev;

        //tail->_next = tmp;
        //tmp->_prev = tail;
        //_head->_prev = tmp;
        //tmp->_next = _head;
        
        Insert(end(),x);
      }

      void PopBack()
      {
        //assert(_head);
        //Node* tmp = _head->_prev;
        //Node* tail = tmp->_prev;
        //tail->_next = _head;
        //_head->_prev = tail;
        //delete tmp;
        //tmp = NULL;
        
        Earse(end());
      }

      void PushFront(const T& x)
      {
        //Node* tmp = new Node(x);
        //Node *ret = _head->_next;
        //_head->_next = tmp;
        //tmp->_prev = _head;
        //tmp->_next = ret;
        //ret->_prev = tmp;
        
        Insert(begin(),x);
      }

      void PopFront()
      {
        //assert(_head);
        //Node* tmp = _head->_next;
        //_head->_next = tmp->_next;
        //delete tmp;
        //tmp = NULL;
        
        Earse(begin());
      }

      void Insert(iterator pos,const T& x) //指定位置之前插入
      {
        Node* newnode = new Node(x);
        Node* tmp = pos._node;
        Node* pre = tmp->_prev;
        
        pre->_next = newnode;
        newnode->_prev = pre;
        newnode->_next = tmp;
        tmp->_prev = newnode;
      }

      iterator Earse(iterator pos)
      {
        Node* del = pos._node;
        Node* nex = del->_next;
        Node* pre = del->_prev;
        
        pre->_next = nex;
        nex->_prev = pre;
        delete del;
        del = NULL;
        return iterator(nex); //可以用于解决迭代器失效的问题
      }
     
      bool empty()
      {
        return _head->_next == _head ? true : false;
      }

      size_t Size()
      {
        size_t count = 0;
        Node* tmp = _head->_next;
        while(tmp != _head){
          count++;
          tmp = tmp->_next;
        }
        return count;
      }

    private:
        Node* _head;
    };


void Test()
{
  List<int>l;
  l.PushBack(1);
  l.PushBack(2);
  l.PushBack(3);
  l.PushBack(4);
  //l.PushFront(1);
  //l.PopBack();
  //l.PopBack();
  //l.PopFront();
  //l.Insert(l.begin(),0);
  //l.Earse(l.begin());
  List<int>l2(l);

  List<int>::iterator it = l.begin();
  while(it != l.end())
  {
    cout << *it << "-";
    ++it;
  }
  cout << endl;

  List<int>::iterator it2 = l2.begin();
  while(it2 != l2.end())
  {
    cout << *it2 << "-";
    ++it2;
  }
  cout << endl;
  //cout << l.empty() << endl;
  //cout << l.Size() << endl;
}


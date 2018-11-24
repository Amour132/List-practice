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
  template<class T>
    struct _ListIterator
    {
      typedef ListNode<T> Node;
      typedef _ListIterator<T> Self;

      Node* _node;

      _ListIterator(Node *node)
                :_node(node)
      {}

      T operator*()
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
      typedef _ListIterator<T> iterator;
      iterator begin()
      {
        return _head->_next;
      }

      iterator end()
      {
        return _head;
      }

      List()
        :_head(new Node)
      {
        _head->_next = _head;
        _head->_prev = _head;
      }

      List(const List<T>& l);
      List<T>& operator=(List<T> l);
      
      //成员函数
      void PushBack(const T& x)
      {
        Node* tmp = new Node(x);
        Node* tail = _head->_prev;

        tail->_next = tmp;
        tmp->_prev = tail;
        _head->_prev = tmp;
        tmp->_next = _head;
      }

      void PopBack()
      {
        assert(_head);
        Node* tmp = _head->_prev;
        Node* tail = tmp->_prev;
        tail->_next = _head;
        _head->_prev = tail;
        delete tmp;
        tmp = NULL;
      }

      void PushFront(const T& x)
      {
        Node* tmp = new Node(x);
        Node *ret = _head->_next;
        _head->_next = tmp;
        tmp->_prev = _head;
        tmp->_next = ret;
        ret->_prev = tmp;
      }

      void PopFront()
      {
        assert(_head);
        Node* tmp = _head->_next;
        _head->_next = tmp->_next;
        delete tmp;
        tmp = NULL;
      }

      void Insert(iterator pos,const T& x);
      void Earse(iterator pos);
     
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
  l.PushFront(4);
  l.PushFront(5);
  //l.PopBack();
  //l.PopBack();
  l.PopFront();
  l.PushFront();
  List<int>::iterator it = l.begin();
  while(it != l.end())
  {
    cout << *it << "-";
    ++it;
  }
  cout << endl;
  cout << l.empty() << endl;
  cout << l.Size() << endl;
}


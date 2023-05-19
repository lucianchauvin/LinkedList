# ifndef LINKED_LIST
# define LINKED_LIST

# include <string>
# include <iostream>
 
using std::cout, std::endl, std::string, std::ostream;

template <class T>
struct Node {
    T data;
    
    Node<T>* next;
    Node<T>* prev;
    Node<T>(T data);
    ~Node<T>();
};

template <class T>
class LinkedList {
    private:
        size_t _size;
        Node<T>* _head;
        Node<T>* _tail;
    
    public:
        LinkedList();
        LinkedList(const LinkedList& other);
        LinkedList& operator=(const LinkedList& other);
        ~LinkedList();
        size_t size() const;
        bool empty() const;
        Node<T>* head() const;
        Node<T>* tail() const;
        void pushBack(T data);
        void pushFront(T data);
        bool remove(T data);
        bool insertData(T data, size_t index);
        void insertFunc(T data, bool (*func)(T, T));
        bool insertAfterData(T before, T data);
        bool contains(T data) const;
        void clear();
        T& operator[](size_t index) const;
        LinkedList reversed() const;
        LinkedList& reverse();
        Node<T> popHead();
        Node<T> popTail();
        LinkedList sorted(bool (*func)(T, T)=[](T a, T b){return a < b;});
        LinkedList& sort(bool (*func)(T, T)=[](T a, T b){return a < b;});
};

template <class T>
std::ostream& operator<<(std::ostream& os, const LinkedList<T>& list);


template <typename T>
Node<T>::Node(T data) : data{data}, next{nullptr}, prev{nullptr} {}

template <typename T>
Node<T>::~Node() {
    next = nullptr;
    prev = nullptr;
    data = T{};
}

template <class T>
LinkedList<T>::LinkedList() : _size(0), _head(nullptr), _tail(nullptr) {}

template <class T>
LinkedList<T>::LinkedList(const LinkedList& other) : _size(other._size), _head(nullptr), _tail(nullptr) {
    Node<T>* nodeToCopy = other._head;
    while(nodeToCopy != nullptr){
        pushBack(nodeToCopy->data);
        nodeToCopy = nodeToCopy->next;
    }
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other){
    if(this != &other){
        clear();
        Node<T>* nodeToCopy = other._head;
        while(nodeToCopy != nullptr){
            pushBack(nodeToCopy->data);
            nodeToCopy = nodeToCopy->next;
        }
    }
    return *this;
}

template <class T>
LinkedList<T>::~LinkedList(){
    clear();
}

template <class T>
size_t LinkedList<T>::size() const{
    return _size;
}

template <class T>
bool LinkedList<T>::empty() const{
    return _head == nullptr;
}

template <class T>
Node<T>* LinkedList<T>::head() const{
    return _head;
}

template <class T>
Node<T>* LinkedList<T>::tail() const{
    return _tail;
}

template <class T>
void LinkedList<T>::pushBack(T data) {
    Node<T>* nodeTopushBack = new Node<T>(data);
    if(_head == nullptr){
        _head = nodeTopushBack;
        _tail = nodeTopushBack;
    }else{
        nodeTopushBack->prev = _tail;
        _tail->next = nodeTopushBack;
        _tail = nodeTopushBack;
    }
    _size++;
}

template <class T>
void LinkedList<T>::pushFront(T data) {
    Node<T>* nodeTopushFront = new Node<T>(data);
    if(_head == nullptr){
        _head = nodeTopushFront;
        _tail = nodeTopushFront;
    }else{
        nodeTopushFront->next = _head;
        _head->prev = nodeTopushFront;
        _head = nodeTopushFront;
    }
    _size++;
}


template <class T>
bool LinkedList<T>::remove(T data){
    Node<T>* nodeToRemove = _head;
    while(nodeToRemove != nullptr){
        if(nodeToRemove->data == data){
            if(nodeToRemove == _head){
                _head = nodeToRemove->next;
                _head->prev = nullptr;
            }else if(nodeToRemove == _tail){
                _tail = nodeToRemove->prev;
                _tail->next = nullptr;
            }else{
                nodeToRemove->prev->next = nodeToRemove->next;
                nodeToRemove->next->prev = nodeToRemove->prev;
            }
            delete nodeToRemove;
            _size--;
            return true;
        }
        nodeToRemove = nodeToRemove->next;
    }

    return false;
}

template <class T>
bool LinkedList<T>::insertData(T data, size_t index) {
    if(index > _size){
        return false;
    }
    if(_head == nullptr || index == _size){
        pushBack(data);
        return true;
    }else if(index == 0){
        pushFront(data);
        return true;
    }else{
        Node<T>* nodeToInsert = new Node<T>(data);
        Node<T>* nodeToInsertAfter = _head;
        for(size_t i = 0; i < index - 1; i++){
            nodeToInsertAfter = nodeToInsertAfter->next;
        }
        nodeToInsert->next = nodeToInsertAfter->next;
        nodeToInsert->prev = nodeToInsertAfter;
        nodeToInsertAfter->next->prev = nodeToInsert;
        nodeToInsertAfter->next = nodeToInsert;
        _size++;
        return true;
    }
    return false;
}

template <class T>
void LinkedList<T>::insertFunc(T data,  bool (*func)(T , T)){
    if(_head == nullptr){
        pushBack(data);
        return;
    }else if(func(data, _head->data)){
        pushFront(data);
        return;
    }else if(func(_tail->data, data)){
        pushBack(data);
        return;
    }else{
        Node<T>* nodeToInsertBefore = _head;
        while(nodeToInsertBefore != nullptr){
            if(func(data, nodeToInsertBefore->data)){
                Node<T>* nodeToInsert = new Node<T>(data);
                nodeToInsert->next = nodeToInsertBefore;
                nodeToInsert->prev = nodeToInsertBefore->prev;
                nodeToInsertBefore->prev->next = nodeToInsert;
                nodeToInsertBefore->prev = nodeToInsert;
                
                _size++;
                return;
            }
            nodeToInsertBefore = nodeToInsertBefore->next;
        }
        pushBack(data);
    }

}

template <class T>
bool LinkedList<T>::insertAfterData(T before, T data){
    Node<T>* nodeToInsertAfter = _head;
    if(_head == nullptr){
        return false;
    }else if(_head->data == before){
        Node<T>* nodeToInsert = new Node<T>(data);
        nodeToInsert->next = _head->next;
        nodeToInsert->prev = _head;
        _head->next = nodeToInsert;
        if(_tail == _head){
            _tail = nodeToInsert;
        }
        _size++;
        return true;
    }else if(_tail->data == before){
        pushBack(data);
        return true;
    }
    while(nodeToInsertAfter != nullptr){
        if(nodeToInsertAfter->data == before){
            Node<T>* nodeToInsert = new Node<T>(data);
            nodeToInsert->next = nodeToInsertAfter->next;
            nodeToInsert->prev = nodeToInsertAfter;
            if(nodeToInsertAfter->next != nullptr){
                nodeToInsertAfter->next->prev = nodeToInsert;
            }
            nodeToInsertAfter->next = nodeToInsert;
            _size++;
            return true;
        }
        nodeToInsertAfter = nodeToInsertAfter->next;
    }
    return false;
}

template <class T>
bool LinkedList<T>::contains(T data) const{
    Node<T>* nodeToCheck = _head;
    while(nodeToCheck != nullptr){
        if(nodeToCheck->data == data){
            return true;
        }
        nodeToCheck = nodeToCheck->next;
    }
    return false;
}

template <class T>
void LinkedList<T>::clear(){
    Node<T>* nodeToClear = _head;
    while(nodeToClear != nullptr){
        Node<T>* nextNode = nodeToClear->next;
        delete nodeToClear;
        nodeToClear = nextNode;
    }
    _head = nullptr;
    _tail = nullptr;
    _size = 0;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const LinkedList<T>& list){
    Node<T> *_current = list.head();
    if (_current == nullptr) {
        os << "<empty>" << endl;
        return os;
    }

    os << "[ " << _current->data << " ]";
    _current = _current->next;
    while (_current != nullptr) {
        os << " <--> [ " << _current->data << " ]";
        _current = _current->next;
    }
    
    return os;
}

template <class T>
T& LinkedList<T>::operator[](size_t index) const{
    Node<T>* nodeToGet = _head;
    for(size_t i = 0; i < index; i++){
        nodeToGet = nodeToGet->next;
    }
    return nodeToGet->data;
}

template <class T>
LinkedList<T> LinkedList<T>::reversed() const{
    LinkedList<T> reversedList;
    Node<T>* nodeToPushFront = _head;
    while(nodeToPushFront != nullptr){
        reversedList.pushFront(nodeToPushFront->data);
        nodeToPushFront = nodeToPushFront->next;
    }

    return reversedList;
}

template <class T>
Node<T> LinkedList<T>::popHead(){
    Node<T>* nodeToPop = _head;
    _head = _head->next;
    _head->prev = nullptr;
    _size--;
    return nodeToPop;
}

template <class T>
Node<T> LinkedList<T>::popTail(){
    Node<T>* nodeToPop = _tail;
    _tail = _tail->prev;
    _tail->next = nullptr;
    _size--;
    return nodeToPop;
}

template <class T>
LinkedList<T>& LinkedList<T>::reverse(){
    (*this) = this->reversed(); 
    return *this;
}

template <class T>
LinkedList<T> LinkedList<T>::sorted(bool (*func)(T, T)){
    LinkedList<T> sortedList;
    Node<T>* nodeToSort = _head;
    while(nodeToSort != nullptr){
        sortedList.insertFunc(nodeToSort->data, func);
        nodeToSort = nodeToSort->next;
    }
    return sortedList;
}

template <class T>
LinkedList<T>& LinkedList<T>::sort(bool (*func)(T, T)){
    (*this) = this->sorted(func); 
    return *this;
}

# endif

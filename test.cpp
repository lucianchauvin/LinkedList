# include <iostream>
# include "linkedList.cpp"

using namespace std;

struct Pair {
    int x;
    int y;
};

ostream& operator<<(ostream& os, const Pair& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

bool operator<(const Pair& p1, const Pair& p2){
    return p1.x + p1.y < p2.x + p2.y;
}

int main(int argc, char const *argv[])
{
    LinkedList<Pair> list;
    list.pushBack({1, 90});
    list.pushBack({2, 90});
    list.pushBack({3, 98});
    list.pushBack({4, 95});
    list.insertData({5, 89}, 4);

    cout << list << endl << list.head()->data << endl << list.tail()->data << endl << list.size() << endl;


    list.sort();

    cout << list << endl << list.head()->data << endl << list.tail()->data << endl << list.size() << endl;



    return 0;
}
